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
int gScreenWidth = 220*2.f;
int gScreenHeight = 50*2.1f;
float gAspect = (float)gScreenWidth / (float)gScreenHeight;

int main() {

	Camera camera(0.0f, 0.0f, 0.0f, gAspect, 30.0f, 0.1f, 1000.f);
	LightD light;
	Screen screen(gScreenWidth, gScreenHeight, camera, light);

	//Cube monkey;
	//monkey.scale(2.5f, 2.5f, 2.5f);
	//monkey.translate(0.0f, 0.0f, -7.f);

	float deg = 0.1f;
	while (1) {
		screen.start();

		Mesh monkey("monkey.obj");
		//monkey.scale(2.0f, 2.0f, 2.0f);
		monkey.rotate(0.0f, deg, 0.0f);
		monkey.translate(0.0f, 0.0f, -1.7f);
		deg += 0.015f;
		//monkey.rotate(0.0f, 1.0f*screen.deltaTime, 0.0f);

		screen.shadeMesh(monkey);

		screen.print();
		screen.clear();
	}

	return 0;
}
