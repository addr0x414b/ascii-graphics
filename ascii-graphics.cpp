#include <iostream>
#include <algorithm>
#include "src/Screen.hpp"
#include "src/agm.hpp"
#include "src/Camera.hpp"
#include "src/Lights.hpp"
#include "src/Mesh.hpp"

// Global variables
int gScreenWidth = 220*2.1f;
int gScreenHeight = 50*2.5f;
float gAspect = (float)gScreenWidth / (float)gScreenHeight;

int main() {

	Camera camera(0.0f, 0.0f, 0.0f, gAspect);
	LightD light;
	Screen screen(gScreenWidth, gScreenHeight, camera, light);

	Cube cube;
	cube.translate(0.0f, 0.0f, -2.5f);


	float deg = 0.1f;
	while (1) {
		screen.start();

		cube.rotate(deg, deg, 0.0f);
		deg += 30 * screen.deltaTime;

		screen.shadeMesh(cube);

		screen.print();
		screen.clear();
	}

	return 0;
}
