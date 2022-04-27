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

	Vert p1(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f);
	Vert p2(0.5f, -0.5f, 0.0f, -1.0f, 1.0f, 1.0f);
	Vert p3(0.0f, 0.5f, 0.0f, 1.0f, -1.0f, 1.0f);
	Trig t1(p1, p2, p3, 0.0f, 0.0f, 1.0f);
	Mesh t;
	t.trigs = {t1};

	t.translate(0.0f, 0.0f, -2.f);

	float deg = 0.1f;
	while (1) {
		screen.start();


		screen.shadeMeshSmooth(t);

		screen.print();
		screen.clear();
	}

	return 0;
}
