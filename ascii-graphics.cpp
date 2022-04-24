#include "Screen.hpp"
#include "agm.hpp"
#include "Camera.hpp"
#include <iostream>
#include <algorithm>
#include "Lights.hpp"
#include "Mesh.hpp"
#include <chrono>
#include <ctime>

// Global variables
int gScreenWidth = 150;
int gScreenHeight = 50;
float gAspect = (float)gScreenHeight / (float)gScreenWidth;

int main() {

	Camera camera(0.0f, 0.0f, 20.0f, gAspect, 10.0f, 0.1f, 1000.f);
	LightD light;
	Screen screen(gScreenWidth, gScreenHeight, camera, light);

	Vert a(-0.5f, 0.5f, -4.f);
	Vert b(0.5, 0.5f, -4.f);
	Vert c(0.0f, -0.5f, -20.f);
	Trig t(a, b, c, 0.0f, 0.0f, 1.0f);
	Mesh test;
	test.trigs = {t};

	Mesh monkey("monkey.obj");
	monkey.translate(0.0f, 0.0f, -5.f);

	while (1) {
		screen.start();

		//screen.shadeMesh(test);
		monkey.rotate(0.0f, 1.0f*screen.deltaTime, 0.0f);
		screen.shadeMesh(monkey);

		screen.print();
		screen.clear();
	}

	return 0;
}
