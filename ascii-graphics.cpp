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

	Mesh smoothMonkey(1, "../monkey-smooth.obj");
	smoothMonkey.translate(-1.5f, 0.0f, -2.f);

	//Mesh smoothSkull(1, "../skull-smooth.obj");
	//smoothSkull.translate(3.5f, 0.0f, -5.f);

	Cube cube;
	cube.scale(2.f);
	cube.translate(0.0f, -5.f, -7.f);

	float deg = 0.1f;
	while (1) {
		screen.start();

		smoothMonkey.rotate(deg*0.5f, deg, 0.f);
		//smoothSkull.rotate(0.f, deg, 0.f);
		cube.rotate(deg, deg*2.f, 0.f);
		deg += 25.f * screen.deltaTime;

		screen.shadeMeshSmooth(smoothMonkey);
		//screen.shadeMeshSmooth(smoothSkull);
		screen.shadeMesh(cube);

		screen.print();
		screen.clear();
	}

	return 0;
}
