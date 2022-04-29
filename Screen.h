#pragma once

#include <iostream>
#include <vector>

// Screen simulation that allows printing ascii characters to the terminal
class Screen {
	public:
		// 2D Vector that stores the 'pixels' we print
		std::vector<std::vector<char>> buffer;

		int smoothShading;

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
		void drawLine(int x1, int y1, int x2, int y2, char c);

};
