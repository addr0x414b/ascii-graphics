#include "Screen.hpp"
#include "agm.hpp"
#include <iostream>

// Global variables
int gScreenWidth = 100;
int gScreenHeight = 40;
float gAspect = (float)gScreenWidth / gScreenHeight;

int main() {

	Screen screen(gScreenWidth, gScreenHeight);

	Vert p1(0.5f, 0.5f, 0.0f);
	Vert p2(1.0f, 0.5f, 0.0f);
	Vert p3(0.75f, 1.0f, 0.0f);

	Mat4 projection = perspective(gAspect, 45.f, 0.1f, 1000.f);

	float deg = 1.0f;
	while (1) {
		std::system("clear");
		//screen.drawLine(80.3f, 35.2131f, 2.6f, 2.32f, '*');
		Mat4 rot = rotZ(deg);
		deg += 0.005f;

		Vert pc1 = p1;
		Vert pc2 = p2;
		Vert pc3 = p3;

		mult4(pc1, rot);
		mult4(pc2, rot);
		mult4(pc3, rot);

		pc1.z -= 11.0f;
		pc2.z -= 11.0f;
		pc3.z -= 11.0f;

		mult4(pc1, projection);
		mult4(pc2, projection);
		mult4(pc3, projection);

		pc1.x += 0.9f;
		pc2.x += 0.9f;
		pc3.x += 0.9f;
		pc1.y += 0.5f;
		pc2.y += 0.5f;
		pc3.y += 0.5f;

		pc1.x *= 0.5f * (float)gScreenWidth;
		pc1.y *= 0.5f * (float)gScreenHeight;
		pc2.x *= 0.5f * (float)gScreenWidth;
		pc2.y *= 0.5f * (float)gScreenHeight;
		pc3.x *= 0.5f * (float)gScreenWidth;
		pc3.y *= 0.5f * (float)gScreenHeight;

		std::cout << "P1: " << pc1.x << ", " << pc1.y << ", " << pc1.z << std::endl;
		std::cout << "P2: " << pc2.x << ", " << pc2.y << ", " << pc1.z << std::endl;
		std::cout << "P3: " << pc3.x << ", " << pc3.y << ", " << pc3.z << std::endl;
		Trig t1(pc1, pc2, pc3);
		screen.drawTrig(t1, '*');
		screen.print();
		screen.clear();
	}

	return 0;
}
