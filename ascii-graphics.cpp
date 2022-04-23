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
float gAspect = (float)gScreenHeight / gScreenWidth;

int main() {

	Camera camera(0.0f, 0.0f, 20.0f, gAspect);
	LightD light;
	Screen screen(gScreenWidth, gScreenHeight, camera, light);

	Cube cube;
	Cube cube2;

	cube.translate(0.0f, 0.0f, -3.f);
	cube.rotate(0.5f, 0.0f, 0.0f);
	cube2.translate(1.0f, 0.0f, -4.f);

	while (1) {
		screen.start();


		screen.shadeMesh(cube2);
		screen.shadeMesh(cube);
		screen.print();
		screen.clear();
	}

	return 0;
}
