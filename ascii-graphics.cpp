#include "Screen.hpp"
#include "agm.hpp"
#include <iostream>

// Global variables
int gScreenWidth = 100;
int gScreenHeight = 40;
float gAspect = (float)gScreenWidth / gScreenHeight;

int main() {

	Screen screen(gScreenWidth, gScreenHeight);

	Vert p1(25, 30, 20);
	Vert p2(75, 30, 20);
	Vert p3(50, 5, 20);

	Trig t1(p1, p2, p3);

	Mat4 projection = perspective(gAspect, 45.f, 0.1f, 1000.f);

	while (1) {
		std::system("clear");
		//screen.drawLine(80.3f, 35.2131f, 2.6f, 2.32f, '*');
		screen.drawTrig(t1, '*');
		screen.print();
		screen.clear();
	}

	return 0;
}
