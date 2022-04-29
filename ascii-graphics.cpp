#include "Screen.hpp"
#include "agm.hpp"
#include "Camera.hpp"
#include <iostream>
#include <algorithm>
#include "Lights.hpp"
#include "Mesh.hpp"

// Global variables
int gScreenWidth = 220*2.1f;
int gScreenHeight = 50*2.5f;
float gAspect = (float)gScreenWidth / (float)gScreenHeight;

int main() {

	Camera camera(0.0f, 0.0f, 0.0f, gAspect, 30.f, 0.1f, 1000.f);
	LightD light(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.f);
	Screen screen(gScreenWidth, gScreenHeight, camera, light);

	Mesh smoothMonkey(1, "monkey-smooth.obj");
	smoothMonkey.translate(-1.5f, 0.0f, -2.f);

	Mesh smoothSkull(1, "skull-smooth.obj");
	smoothSkull.translate(3.5f, 0.0f, -5.f);

	Cube cube;
	cube.translate(0.0f, -5.f, -7.f);

	float deg = 0.1f;
	while (1) {
		screen.start();

		smoothMonkey.rotate(deg*0.5f, deg, 0.f);
		smoothSkull.rotate(0.f, deg, 0.f);
		cube.rotate(deg, deg*2.f, 0.f);
		deg += 1.f * screen.deltaTime;

		screen.shadeMeshSmooth(smoothMonkey);
		screen.shadeMeshSmooth(smoothSkull);
		screen.shadeMesh(cube);

		screen.print();
		screen.clear();
	}

	return 0;
}
