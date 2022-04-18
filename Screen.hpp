#pragma once

/* Screen library for simulating screen in terminal */

#include <iostream>
#include <vector>
#include "agm.hpp"

// Screen simulation that allows printing ascii characters to the terminal
class Screen {
	public:
		// 2D Vector that stores the 'pixels' we print
		std::vector<std::vector<char>> buffer;

		// Screen width and height
		int width, height;

		// What our screen buffer is filled with. By default it's an empty space, so
		// that the screen is empty. Can change for debug/style purposes
		char fillChar;

		/* Default constructor
		 * @param w the screen width
		 * @param h the screen height */
		Screen(int w, int h);

		// Print the contents of the screen buffer
		void print();

		// Clear the contents of the screen buffer
		void clear();

		/* Draw a line to the buffer
		 * @param x1 the x position of point 1
		 * @param y1 the y position of point 1
		 * @param x2 the x position of point 2
		 * @param y2 the y position of point 2
		 * @param c the character we draw to the buffer */
		void drawLine(float x1, float y1, float x2, float y2, char c);

		/* Draw a line to the buffer using verts
		 * @param a our first vertex
		 * @param b our second vertex
		 * @param c the character we draw to the buffer */
		void drawLine(Vert a, Vert b, char c);

		/* Draw a triangle to the buffer
		 * @param t our triangle to draw
		 * @param c the character we draw to the buffer */
		void drawTrig(Trig t, char c);

	private:
		/* Draw to the buffer at a specific point. Does bounds checking
		 * @param x our x position
		 * @param y our y position
		 * @param c the character we draw to the buffer */
		void drawToBuffer(float x, float y, char c);

};
