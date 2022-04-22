#include "Screen.hpp"
#include <cmath>
#include <unistd.h>
#include <math.h>
#include <algorithm>

/* Default constructor
 * @param w the screen width
 * @param h the screen height
 * @param c our screens camera
 * @param l our scenes light */
Screen::Screen(int w, int h, Camera& c, LightD l) {
	camera = c;
	width = w;
	height = h;
	fillChar = ' ';
	light = l;
	shadeValues = ".:*+=%#@";
	// Allocate memory to our screen buffer. Fill with empty chars
	buffer.resize(height, std::vector<char>(width, fillChar));
}

// Print the contents of the screen buffer
void Screen::print() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			std::cout << buffer[y][x];
		}
		std::cout << "\n";
	}
	usleep(8500);
}

// Clear the contents of the screen buffer
void Screen::clear() {
	buffer.clear();
	buffer.resize(height, std::vector<char>(width, fillChar));
}

/* Draw to the buffer at a specific point. Does bounds checking
 * @param x our x position
 * @param y our y position
 * @param c the character we draw to the buffer */
void Screen::drawToBuffer(float x, float y, char c) {
	if (x < width && y < height && x >= 0 && y >= 0) {
		x = round(x);
		y = round(y);
		buffer[y][x] = c;
	}
}

/* Draw a line to the buffer using individual coordinates
 * @param x1 the x position of point 1
 * @param y1 the y position of point 1
 * @param x2 the x position of point 2
 * @param y2 the y position of point 2
 * @param c the character we draw to the buffer */
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
 * @param a our first vertex
 * @param b our second vertex
 * @param c the character we draw to the buffer */
void Screen::drawLine(Vert a, Vert b, char c) {
	drawLine(a.x, a.y, b.x, b.y, c);
}

/* Draw a triangle to the buffer
 * @param t our triangle to draw
 * @param c the character we draw to the buffer */
void Screen::drawTrig(Trig t, char c) {
	drawLine(t.verts[0], t.verts[1], c);
	drawLine(t.verts[1], t.verts[2], c);
	drawLine(t.verts[2], t.verts[0], c);
}

/* Draw all of the triangles in a mesh to the buffer
 * @param m our mesh
 * @param c our draw character */
void Screen::drawMesh(Mesh m, char c) {
	for (auto &trig : m.trigs) {
		if (dot(trig.fNormal, direc(trig.verts[0], camera.pos)) < 0.0f) {

			project(trig, camera.projMat);

			/*
			trig.verts[0].x *= 0.6f * (float)width;
			trig.verts[0].y *= -0.6f * (float)height/2;
			trig.verts[1].x *= 0.6f * (float)width;
			trig.verts[1].y *= -0.6f * (float)height/2;
			trig.verts[2].x *= 0.6f * (float)width;
			trig.verts[2].y *= -0.6f * (float)height/2;
			*/

			//trig.verts[0].x *= (float)width/2;
			//trig.verts[0].y *= (float)height/2/2;
			//trig.verts[1].x *= (float)width/2;
			//trig.verts[1].y *= (float)height/2/2;
			//trig.verts[2].x *= (float)width/2;
			//trig.verts[2].y *= (float)height/2/2;

			trig.verts[0].x *= 100.f;
			trig.verts[0].y *= -100.f/6;
			trig.verts[1].x *= 100.f;
			trig.verts[1].y *= -100.f/6;
			trig.verts[2].x *= 100.f;
			trig.verts[2].y *= -100.f/6;

			trig.verts[0].x += (float)width/2;
			trig.verts[0].y += (float)height/2;
			trig.verts[1].x += (float)width/2;
			trig.verts[1].y += (float)height/2;
			trig.verts[2].x += (float)width/2;
			trig.verts[2].y += (float)height/2;

			drawTrig(trig, c);
		}
	}
}

/* Draw all of the triangles not considering normals
 * @param m the mesh
 * @param c the draw character */
void Screen::drawMeshWire(Mesh m, char c) {
	for (auto &trig : m.trigs) {
		project(trig, camera.projMat);

		trig.verts[0].x *= 100.f;
		trig.verts[0].y *= -100.f/6;
		trig.verts[1].x *= 100.f;
		trig.verts[1].y *= -100.f/6;
		trig.verts[2].x *= 100.f;
		trig.verts[2].y *= -100.f/6;

		trig.verts[0].x += (float)width/2;
		trig.verts[0].y += (float)height/2;
		trig.verts[1].x += (float)width/2;
		trig.verts[1].y += (float)height/2;
		trig.verts[2].x += (float)width/2;
		trig.verts[2].y += (float)height/2;
		drawTrig(trig, c);
	}
}

/* Fill in a mesh via a character
 * @param m the mesh
 * @param c the draw character */
void Screen::fillMesh(Mesh m, char c) {
	for (auto &trig : m.trigs) {
		if (dot(trig.fNormal, direc(trig.verts[0], camera.pos)) < 0.0f) {
			project(trig, camera.projMat);

			trig.verts[0].x *= 100.f;
			trig.verts[0].y *= -100.f/6;
			trig.verts[1].x *= 100.f;
			trig.verts[1].y *= -100.f/6;
			trig.verts[2].x *= 100.f;
			trig.verts[2].y *= -100.f/6;

			trig.verts[0].x += (float)width/2;
			trig.verts[0].y += (float)height/2;
			trig.verts[1].x += (float)width/2;
			trig.verts[1].y += (float)height/2;
			trig.verts[2].x += (float)width/2;
			trig.verts[2].y += (float)height/2;

			std::sort(trig.verts, trig.verts + 3,
					[](Vert const& a, Vert const& b) -> bool {
					return a.y < b.y;
					});

			if (trig.verts[1].y == trig.verts[2].y) {
				fillFb(trig, c);
			} else if (trig.verts[0].y == trig.verts[1].y) {
				fillFt(trig, c);
			} else {
				float m1 = (trig.verts[0].y - trig.verts[2].y) / (trig.verts[0].x - trig.verts[2].x);
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
 * @param t the triangle
 * @param c the draw character */
void Screen::fillFb(Trig t, char c) {

	float m1 = (t.verts[0].y - t.verts[1].y) / (t.verts[0].x - t.verts[1].x);
	float b1 = t.verts[0].y - (m1 * t.verts[0].x);

	float m2 = (t.verts[0].y - t.verts[2].y) / (t.verts[0].x - t.verts[2].x);
	float b2 = t.verts[0].y - (m2 * t.verts[0].x);

	drawLine(t.verts[0].x, t.verts[0].y, t.verts[0].x, t.verts[0].y, c);

	float x1;
	float x2;

	for (int y = t.verts[0].y+1; y <= t.verts[2].y; y++) {
		if (std::isfinite(m1)) {
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
	//drawTrig(t, c);
}

/* Fill a flat top triangle
 * @param t the triangle
 * @param c the draw character */
void Screen::fillFt(Trig t, char c) {
	float m1 = (t.verts[2].y - t.verts[0].y) / (t.verts[2].x - t.verts[0].x);
	float b1 = t.verts[2].y - (m1 * t.verts[2].x);

	float m2 = (t.verts[2].y - t.verts[1].y) / (t.verts[2].x - t.verts[1].x);
	float b2 = t.verts[2].y - (m2 * t.verts[2].x);

	drawLine(t.verts[2].x, t.verts[2].y, t.verts[2].x, t.verts[2].y, c);

	float x1;
	float x2;
	for (int y = t.verts[2].y; y >= t.verts[0].y; y--) {
		if (std::isfinite(m1)) {
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
	//drawTrig(t, c);
}

/* Shade in the mesh based on the light
 * @param m the mesh */
void Screen::shadeMesh(Mesh m) {
	for (auto &trig : m.trigs) {
		if (dot(trig.fNormal, direc(trig.verts[0], camera.pos)) < 0.0f) {
			project(trig, camera.projMat);

			/*
			trig.verts[0].x *= 100.f;
			trig.verts[0].y *= -100.f/6;
			trig.verts[1].x *= 100.f;
			trig.verts[1].y *= -100.f/6;
			trig.verts[2].x *= 100.f;
			trig.verts[2].y *= -100.f/6; */

			//trig.verts[0].y /= -6;
			//trig.verts[1].y /= -6;
			//trig.verts[2].y /= -6;

			trig.verts[0].x += (float)width/2;
			trig.verts[0].y += (float)height/2;
			trig.verts[1].x += (float)width/2;
			trig.verts[1].y += (float)height/2;
			trig.verts[2].x += (float)width/2;
			trig.verts[2].y += (float)height/2;

			float shade = round((abs(dot(trig.fNormal, light.direction)) * 8)) - 1;

			if (shade <= 0) {
				shade = 0;
			}

			char c = shadeValues[shade];

			std::sort(trig.verts, trig.verts + 3,
					[](Vert const& a, Vert const& b) -> bool {
					return a.y < b.y;
					});

			if (trig.verts[1].y == trig.verts[2].y) {
				fillFb(trig, c);
			} else if (trig.verts[0].y == trig.verts[1].y) {
				fillFt(trig, c);
			} else {
				float m1 = (trig.verts[0].y - trig.verts[2].y) / (trig.verts[0].x - trig.verts[2].x);
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
