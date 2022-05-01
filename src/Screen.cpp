#include "Screen.hpp"
#include <unistd.h>
#include <math.h>
#include <algorithm>

/* Default constructor
 * @param w: screen width
 * @param h: screen height
 * @param c: screens camera
 * @param l: scenes light */
Screen::Screen(int w, int h, Camera& c, LightD l) {
	camera = c;
	width = w;
	height = h;
	fillChar = ' ';
	light = l;
	shadeValues = ".:+*=#%@";
	// Allocate memory to our screen buffer. Fill with empty chars
	buffer.resize(height, std::vector<char>(width, fillChar));
	zBuffer.resize(height, std::vector<float>(width, 100000.f));
	lastTime = std::chrono::steady_clock::now();
	currTime = std::chrono::steady_clock::now();
	renderMode = 1; // Use z buffering by default
}

// Calculate deltaTime
void Screen::start() {
		lastTime = currTime;
		currTime = std::chrono::steady_clock::now();
		auto dT = std::chrono::duration_cast<std::chrono::milliseconds>
			(currTime - lastTime);
		deltaTime = dT.count() / 1000.f;
}

// Print the contents of the screen buffer
void Screen::print() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			std::cout << buffer[y][x];
		}
		std::cout << "\n";
	}
	// Sleep values slow the program down so it is less jittery
	//usleep(8500);
	//usleep(9000);
	usleep(11000);
	//usleep(15000);
}

// Clear the contents of the screen buffer and z buffer
void Screen::clear() {
	buffer.clear();
	buffer.resize(height, std::vector<char>(width, fillChar));
	zBuffer.clear();
	zBuffer.resize(height, std::vector<float>(width, 100000.f));
}

/* Draw to the buffer at a specific point. Does bounds checking
 * @param x: x position
 * @param y: y position
 * @param c: character to draw to the buffer */
void Screen::drawToBuffer(float x, float y, char c) {
	if (x < width && y < height && x >= 0 && y >= 0) {
		x = round(x);
		y = round(y);
		if (renderMode == 0) { // Z buffer disabled, simply draw
			buffer[y][x] = c;
		} else if (renderMode == 1) {
			float z = calcZ(x, y, zCross, zVert); // Calculate the z value
			if(checkZB(x, y, z)) { // Check if z is < than current z buffer value
				zBuffer[y][x] = z; // Replace with new z value
				if (c == 'S') { // If smooth shading
					// All that's happening is calculating the shade of the pixel
					float w1, w2, w3;
					calcBary(tP1, tP2, tP3, x, y, w1, w2, w3);

					/* Use barycentric coords to calculate the weights between the normals
					 * of the triangle */
					float xx = ((w1 * p1N.x) + (w2 * p2N.x) + (w3 * p3N.x));
					float yy = ((w1 * p1N.y) + (w2 * p2N.y) + (w3 * p3N.y));
					float zz = ((w1 * p1N.z) + (w2 * p2N.z) + (w3 * p3N.z));
					float l = sqrtf(xx*xx + yy*yy + zz*zz);
					xx /= l;
					yy /= l;
					zz /= l;
					Vert pNormal(xx, yy, zz); // The normal vector of the pixel

					float shade = round((abs(dot(pNormal, light.direction)) * 8)) - 1;
					if (shade <= 0) {
						shade = 0;
					} else if (shade >= 7) {
						shade = 7;
					} else if (std::isnan(shade)) {
						shade = 0;
					}
					c = shadeValues[shade];
				}
				buffer[y][x] = c;
			}
		}
	}
}

/* Check the Z Buffer at a specific location
 * @params x,y: the x and y coordinate in z buffer
 * @param z: z we want to check with
 * @return bool: if the z we check with is < than z in z buffer */
bool Screen::checkZB(float x, float y, float z) {
	return z < zBuffer[y][x];
}

/* Draw a line to the buffer using individual coordinates
 * @param x1: x position of point 1
 * @param y1: y position of point 1
 * @param x2: x position of point 2
 * @param y2: y position of point 2
 * @param c: character to draw to the buffer */
void Screen::drawLine(float x1, float y1, float x2, float y2, char c) {
	x1 = round(x1);
	y1 = round(y1);
	x2 = round(x2);
	y2 = round(y2);
	if (x1 == x2) { // If the x's are the same, either vertical line or point
		if (y1 == y2) {
			drawToBuffer(x1, y1, c);
		} else {
			if (y1 > y2) {
				std::swap(y1, y2); // Make sure y1 is smaller than y2 for the loop
			}
			for (int y = y1; y <= y2; y++) {
				drawToBuffer(x1, y, c);
			}
		}
	} else {
		float slope = (float)(y2 - y1) / (float)(x2 - x1);
		float intercept = y1 - (slope * x1);
		if (x1 > x2) {
			std::swap(x1, x2); // Make sure x1 is smaller than x2 so we loop properly
		}
		for (int x = x1; x <= x2; x++) {
			int y = round((slope * x) + intercept);
			drawToBuffer(x, y, c);
		}
		if (y1 > y2) {
			std::swap(y1, y2);
		}
		for (int y = y1; y <= y2; y++) {
			int x = round((y-intercept) / slope);
			drawToBuffer(x, y, c);
		}
	}
}

/* Draw a line to the buffer using verts
 * @param a: first vertex
 * @param b: second vertex
 * @param c: character to draw to the buffer */
void Screen::drawLine(Vert a, Vert b, char c) {
	drawLine(a.x, a.y, b.x, b.y, c);
}

/* Draw a triangle to the buffer
 * @param t: triangle to draw
 * @param c: character to draw to the buffer */
void Screen::drawTrig(Trig t, char c) {
	drawLine(t.verts[0], t.verts[1], c);
	drawLine(t.verts[1], t.verts[2], c);
	drawLine(t.verts[2], t.verts[0], c);
}

/* Draw all of the triangles in a mesh to the buffer
 * @param m: mesh
 * @param c: draw character */
void Screen::drawMesh(Mesh m, char c) {
	for (auto &trig : m.trigs) {
		// Check if the triangle is visible to the camera via its normal
		if (dot(trig.fNormal, direc(trig.verts[0], camera.pos)) < 0.0f) {

			project(trig, camera.projMat);

			centerFlipY(trig);

			// Get zCross and zVert, which is used for z buffer calculations
			Vert v1 = direc(trig.verts[1], trig.verts[0]);
			Vert v2 = direc(trig.verts[2], trig.verts[0]);
			zCross = cross(v1, v2);
			zVert = trig.verts[0];

			drawTrig(trig, c);
		}
	}
}

/* Draw all of the triangles in wireframe. DOESN'T consider normals
 * @param m: mesh
 * @param c: draw character */
void Screen::drawMeshWire(Mesh m, char c) {
	for (auto &trig : m.trigs) {
		project(trig, camera.projMat);

		centerFlipY(trig);

		// Get zCross and zVert, which is used for z buffer calculations
		Vert v1 = direc(trig.verts[1], trig.verts[0]);
		Vert v2 = direc(trig.verts[2], trig.verts[0]);
		zCross = cross(v1, v2);
		zVert = trig.verts[0];

		drawTrig(trig, c);
	}
}

/* Fill in a mesh via a character
 * @param m: mesh
 * @param c: draw character */
void Screen::fillMesh(Mesh m, char c) {
	for (auto &trig : m.trigs) {
		// Check if triangle is visible to camera via its normal
		if (dot(trig.fNormal, direc(trig.verts[0], camera.pos)) < 0.0f) {
			project(trig, camera.projMat);

			centerFlipY(trig);

			// Get zCross and zVert, which is used for z buffer calculations
			Vert v1 = direc(trig.verts[1], trig.verts[0]);
			Vert v2 = direc(trig.verts[2], trig.verts[0]);
			zCross = cross(v1, v2);
			zVert = trig.verts[0];

			// Triangles must be sorted basted on y value. This allows to determine
			// is it's a flat bottom, flat top, or to split it via the middle point
			std::sort(trig.verts, trig.verts + 3,
					[](Vert const& a, Vert const& b) -> bool {
					return a.y < b.y;
					});

			if (trig.verts[1].y == trig.verts[2].y) {
				fillFb(trig, c);
			} else if (trig.verts[0].y == trig.verts[1].y) {
				fillFt(trig, c);
			} else {
				// Not flat bottom or top, thus split the triangle in half via mid point
				float m1 = (trig.verts[0].y - trig.verts[2].y) /
					(trig.verts[0].x - trig.verts[2].x);

				float b1 = trig.verts[0].y - (m1 * trig.verts[0].x);
				Vert n((trig.verts[1].y-b1)/m1, trig.verts[1].y, 0.0f);
				Trig fb(trig.verts[0], n, trig.verts[1], 0.0f, 0.0f, 0.0f);
				Trig ft(n, trig.verts[1], trig.verts[2], 0.0f, 0.0f, 0.0f);
				fillFt(ft, c);
				fillFb(fb, c);
			}
			drawTrig(trig, c);
		}
	}
}

/* Fill a flat bottom triangle
 * @param t: triangle
 * @param c: draw character */
void Screen::fillFb(Trig t, char c) {

	float m1 = (t.verts[0].y - t.verts[1].y) / (t.verts[0].x - t.verts[1].x);
	float b1 = t.verts[0].y - (m1 * t.verts[0].x);

	float m2 = (t.verts[0].y - t.verts[2].y) / (t.verts[0].x - t.verts[2].x);
	float b2 = t.verts[0].y - (m2 * t.verts[0].x);

	drawLine(t.verts[0].x, t.verts[0].y, t.verts[0].x, t.verts[0].y, c);

	float x1;
	float x2;

	for (int y = t.verts[0].y+1; y <= t.verts[2].y; y++) {
		if (std::isfinite(m1)) { // If divide by 0 (vertical line)
			x1 = (y - b1) / m1;
		} else {
			x1 = t.verts[0].x;
		}

		if (std::isfinite(m2)) {
			x2 = (y - b2) / m2;
		} else {
			x2 = t.verts[0].x;
		}
		drawLine(x1, y, x2, y, c);
	}
}

/* Fill a flat top triangle
 * @param t: triangle
 * @param c: draw character */
void Screen::fillFt(Trig t, char c) {
	float m1 = (t.verts[2].y - t.verts[0].y) / (t.verts[2].x - t.verts[0].x);
	float b1 = t.verts[2].y - (m1 * t.verts[2].x);

	float m2 = (t.verts[2].y - t.verts[1].y) / (t.verts[2].x - t.verts[1].x);
	float b2 = t.verts[2].y - (m2 * t.verts[2].x);

	drawLine(t.verts[2].x, t.verts[2].y, t.verts[2].x, t.verts[2].y, c);

	float x1;
	float x2;
	for (int y = t.verts[2].y; y >= t.verts[0].y; y--) {
		if (std::isfinite(m1)) { // If divide by 0 (vertical line)
			x1 = (y - b1) / m1;
		} else {
			x1 = t.verts[2].x;
		}

		if (std::isfinite(m2)) {
			x2 = (y - b2) / m2;
		} else {
			x2 = t.verts[2].x;
		}
		drawLine(x1, y, x2, y, c);
	}
}

/* Shade in the mesh based on the light direction. FLAT SHADED!
 * @param m: mesh */
void Screen::shadeMesh(Mesh m) {
	for (auto &trig : m.trigs) {
		// Check if the triangle is visible via its normal vector
		if (dot(trig.fNormal, direc(trig.verts[0], camera.pos)) < 0.0f) {

			project(trig, camera.projMat);

			centerFlipY(trig);

			// zCross and zVert used for z buffer calculations
			Vert v1 = direc(trig.verts[1], trig.verts[0]);
			Vert v2 = direc(trig.verts[2], trig.verts[0]);
			zCross = cross(v1, v2);
			zVert = trig.verts[0];

			// Calculate the shade character based on the light direction
			float shade = round((abs(dot(trig.fNormal, light.direction)) * 8)) - 1;
			if (shade <= 0) {
				shade = 0;
			} else if(shade >= 7) {
				shade = 7;
			} else if (std::isnan(shade)) {
				shade = 0;
			}
			char c = shadeValues[shade];

			// Triangles must be sorted basted on y value. This allows to determine
			// is it's a flat bottom, flat top, or to split it via the middle point
			std::sort(trig.verts, trig.verts + 3,
					[](Vert const& a, Vert const& b) -> bool {
					return a.y < b.y;
					});

			if (trig.verts[1].y == trig.verts[2].y) {
				fillFb(trig, c);
			} else if (trig.verts[0].y == trig.verts[1].y) {
				fillFt(trig, c);
			} else {
				float m1 = (trig.verts[0].y - trig.verts[2].y) /
					(trig.verts[0].x - trig.verts[2].x);

				float b1 = trig.verts[0].y - (m1 * trig.verts[0].x);
				Vert n((trig.verts[1].y-b1)/m1, trig.verts[1].y, 0.0f);
				n.z = calcZ(n.x, n.y, zCross, zVert);
				Trig fb(trig.verts[0], n, trig.verts[1], 0.0f, 0.0f, 0.0f);
				Trig ft(n, trig.verts[1], trig.verts[2], 0.0f, 0.0f, 0.0f);
				fillFt(ft, c);
				fillFb(fb, c);
			}
			drawTrig(trig, c);
		}
	}
}

/* Shade in the mesh smooth based on the light direction
 * @param m: SMOOTHED mesh */
void Screen::shadeMeshSmooth(Mesh m) {
	for (auto &trig : m.trigs) {
		// Check if the triangle is visible via its normal vector
		if (dot(trig.fNormal, direc(trig.verts[0], camera.pos)) < 0.0f) {

			project(trig, camera.projMat);

			centerFlipY(trig);

			// zCross and zVert used for z buffer calculations
			Vert v1 = direc(trig.verts[1], trig.verts[0]);
			Vert v2 = direc(trig.verts[2], trig.verts[0]);
			zCross = cross(v1, v2);
			zVert = trig.verts[0];

			// Store the triangle vertice normals and positions, this is used to
			// interpolate for each pixel and get the normals for each pixel
			p1N = trig.norms[0];
			p2N = trig.norms[1];
			p3N = trig.norms[2];
			tP1 = trig.verts[0];
			tP2 = trig.verts[1];
			tP3 = trig.verts[2];

			// Triangles must be sorted basted on y value. This allows to determine
			// is it's a flat bottom, flat top, or to split it via the middle point
			std::sort(trig.verts, trig.verts + 3,
					[](Vert const& a, Vert const& b) -> bool {
					return a.y < b.y;
					});

			// The draw character is set as 'S' to tell the draw functions it will
			// be a smooth shaded object
			if (trig.verts[1].y == trig.verts[2].y) {
				fillFb(trig, 'S');
			} else if (trig.verts[0].y == trig.verts[1].y) {
				fillFt(trig, 'S');
			} else {
				float m1 = (trig.verts[0].y - trig.verts[2].y) /
					(trig.verts[0].x - trig.verts[2].x);

				float b1 = trig.verts[0].y - (m1 * trig.verts[0].x);
				Vert n((trig.verts[1].y-b1)/m1, trig.verts[1].y, 0.0f);
				n.z = calcZ(n.x, n.y, zCross, zVert);
				Trig fb(trig.verts[0], n, trig.verts[1], 0.0f, 0.0f, 0.0f);
				Trig ft(n, trig.verts[1], trig.verts[2], 0.0f, 0.0f, 0.0f);
				fillFt(ft, 'S');
				fillFb(fb, 'S');
			}
			drawTrig(trig, 'S');
		}
	}
}

/* Center the triangles to the middle of the screen, flip the triangles so
 * +y is up, and scale the x based on aspect ratio
 * @param t: triangle */
void Screen::centerFlipY(Trig& t) {

	// Flip triangle verts
	t.verts[0].y *= -1.f;
	t.verts[1].y *= -1.f;
	t.verts[2].y *= -1.f;

	// Scale by aspect ratio
	t.verts[0].x *= camera.a*2.5;
	t.verts[1].x *= camera.a*2.5;
	t.verts[2].x *= camera.a*2.5f;

	// Move the very center of screen
	t.verts[0].x += (float)width/2;
	t.verts[0].y += (float)height/2.f;
	t.verts[1].x += (float)width/2;
	t.verts[1].y += (float)height/2.f;
	t.verts[2].x += (float)width/2;
	t.verts[2].y += (float)height/2.f;
}
