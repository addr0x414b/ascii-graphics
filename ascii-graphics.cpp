#include "Screen.hpp"
#include "agm.hpp"
#include "Camera.hpp"
#include <iostream>

// Global variables
int gScreenWidth = 100;
int gScreenHeight = 50;
float gAspect = (float)gScreenWidth / gScreenHeight;

int main() {

	Camera camera(0.0f, 0.0f, 20.0f, gAspect);
	Screen screen(gScreenWidth, gScreenHeight, camera);

	Vert p1(-1.0f, 1.0f, 0.0f);
	Vert p2(-1.0f, -1.0f, 0.0f);
	Vert p3(1.0f, -1.0f, 0.0f);
	Trig t1(p1, p2, p3, 0.0f, 0.0f, 1.0f);

	Vert p4(1.0f, -1.0f, 0.0f);
	Vert p5(1.0f, 1.0f, 0.0f);
	Vert p6(-1.0f, 1.0f, 0.0f);
	Trig t2(p4, p5, p6, 0.0f, 0.0f, 1.0f);

	Mesh square;

	Mat4 projection = perspective(gAspect, 45.f, 0.1f, 1000.f);

	float deg = 0.1f;
	while (1) {
		square.trigs = {t1, t2};
		square.rotZ(deg);
		square.rotX(deg);
		deg += 0.01f;
		square.translate(3.0f, 1.5f, -20.f);

		//square.project(gAspect, 45.f, 0.1f, 1000.f);
		//square.scale(0.2f * (float)gScreenWidth, 0.2f * (float)gScreenHeight, 1.0f);

		screen.drawMesh(square, '*');
		screen.print();
		screen.clear();
	}

	return 0;
}
