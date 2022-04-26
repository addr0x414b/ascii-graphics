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
int gScreenWidth = 220;
int gScreenHeight = 50;
float gAspect = (float)gScreenWidth / (float)gScreenHeight;

int main() {

	Camera camera(0.0f, 0.0f, 0.0f, gAspect, 30.0f, 0.1f, 1000.f);
	LightD light;
	Screen screen(gScreenWidth, gScreenHeight, camera, light);

	Mesh cube("skull.obj");
	cube.translate(0.0f, 0.0f, -9.f);
	cube.scale(1.0f, 1.0f, 1.0f);

	float deg = 0.1f;
	while (1) {
		screen.start();

		cube.rotate(deg, deg, deg);
		deg += 0.02f;

		screen.shadeMesh(cube);

		screen.print();
		screen.clear();
	}

	return 0;
}
