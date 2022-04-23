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

	float deg = 0.1f;

	Cube cube;


	while (1) {
		screen.start();

		cube.rotX(deg);
		cube.rotZ(deg);
		cube.translate(0.0f, 0.0f, -4.f);
		deg += 1.f * screen.deltaTime;
		screen.shadeMesh(cube);

		screen.print();
		screen.clear();
	}

	return 0;
}
