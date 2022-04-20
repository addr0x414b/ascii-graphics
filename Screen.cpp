#include "Screen.hpp"
#include <unistd.h>
#include <math.h>

/* Default constructor
 * @param w the screen width
 * @param h the screen height
 * @param c our screens camera */
Screen::Screen(int w, int h, Camera c) {
	camera = c;
	width = w;
	height = h;
	fillChar = ' ';
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
			trig.verts[0].x *= 0.4f * (float)width;
			trig.verts[0].y *= 0.4f * (float)height;
			trig.verts[1].x *= 0.4f * (float)width;
			trig.verts[1].y *= 0.4f * (float)height;
			trig.verts[2].x *= 0.4f * (float)width;
			trig.verts[2].y *= 0.4f * (float)height;
			drawTrig(trig, c);
		}
	}
}
