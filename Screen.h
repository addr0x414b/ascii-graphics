#pragma once

#include <iostream>
#include <vector>

/* Screen that allows printing ascii characters to the terminal */
class Screen {
	public:
		// 2D Vector that stores the 'pixels' we print
		std::vector<std::vector<char>> buffer;

		// Screen width and height
		int width, height;

		/* Default constructor
		 * @param w the screen width
		 * @param h the screen height */
		Screen(int w, int h);
};
