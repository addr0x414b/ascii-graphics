#include "Screen.h"
#include <unistd.h>
#include <math.h>

/* Default constructor
 * @param w the screen width
 * @param h the screen height */
Screen::Screen(int w, int h) {
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
	usleep(10000);
}

// Clear the contents of the screen buffer
void Screen::clear() {
	buffer.clear();
	buffer.resize(height, std::vector<char>(width, fillChar));
}

/* Draw a line to the buffer
 * @param x1 the x position of point 1
 * @param y1 the y position of point 1
 * @param x2 the x position of point 2
 * @param y2 the y position of point 2
 * @param c the character we draw to the buffer */
void Screen::drawLine(int x1, int y1, int x2, int y2, char c) {
	if (x1 == x2) { // If the x's are the same, either vertical line or single point
		if (y1 == y2) {
			if (x1 < width && y2 < height) {
				buffer[y1][x1] = c;
			}
		} else if (y1 < y2) {
			for (int y = y1; y <= y2; y++) {
				if (x1 < width && y < height) {
					buffer[y][x1] = c;
				}
			}
		} else if (y2 < y1) {
			for (int y = y2; y <= y1; y++) {
				if (x1 < width && y < height) {
					buffer[y][x1] = c;
				}
			}
		}
	} else {
		float slope = (float)(y2 - y1) / (float)(x2 - x1);
		float intercept = y1 - (slope * x1);
		if (x1 < x2) {
			for (int x = x1; x <= x2; x++) {
				int y = round((slope * x) + intercept);
				if (x < width && y < height) {
					buffer[y][x] = c;
				}
			}
		}
	}
}
