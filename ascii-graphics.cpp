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

	Mesh c("monkey.obj");

	c.translate(0.0f, 0.0f, -5.f);
	//c.rotate(0.0f, 1.0f, 0.0f);

	while (1) {
		screen.start();

		c.rotate(0.0f, 1.0f*screen.deltaTime, 0.0f);

		screen.shadeMesh(c);
		screen.print();
		screen.clear();
	}

	return 0;
}
