#include "Screen.h"

/* Default constructor
 * @param w the screen width
 * @param h the screen height */
Screen::Screen(int w, int h) {
	width = w;
	height = h;
	// Allocate memory to our screen buffer. Fill with empty chars
	buffer.resize(height, std::vector<char>(width, ' '));
}
