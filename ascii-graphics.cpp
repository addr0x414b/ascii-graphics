#include "Screen.hpp"
#include "agm.hpp"
#include <iostream>

// Global variables
int gScreenWidth = 100;
int gScreenHeight = 40;
float gAspect = (float)gScreenWidth / gScreenHeight;

int main() {

	Screen screen(gScreenWidth, gScreenHeight);

	Vert p1(10+70, 30, -11);
	Vert p2(100+70, 30, -11);
	Vert p3(50+70, 5, -11);

	Mat4 projection = perspective(gAspect, 45.f, 0.1f, 1000.f);
	mult4(p1, projection);
	mult4(p2, projection);
	mult4(p3, projection);
	Trig t1(p1, p2, p3);

	while (1) {
		std::system("clear");
		std::cout << "P1: " << p1.x << ", " << p1.y << ", " << p1.z << std::endl;
		std::cout << "P2: " << p2.x << ", " << p2.y << ", " << p1.z << std::endl;
		std::cout << "P3: " << p3.x << ", " << p3.y << ", " << p3.z << std::endl;
		//screen.drawLine(80.3f, 35.2131f, 2.6f, 2.32f, '*');
		screen.drawTrig(t1, '*');
		screen.print();
		screen.clear();
	}

	return 0;
}
