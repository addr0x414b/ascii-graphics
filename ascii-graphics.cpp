#include "Screen.h"
#include <iostream>

// Global variables
int gScreenWidth = 100;
int gScreenHeight = 40;

int main() {

	Screen screen(gScreenWidth, gScreenHeight);

	while (1) {
		std::system("clear");
		screen.drawLine(50, 10, 50, 10, '*');
		screen.print();
		screen.clear();
	}

	return 0;
}
