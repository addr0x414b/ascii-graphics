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
int gScreenWidth = 220*2.1f;
int gScreenHeight = 50*2.5f;
float gAspect = (float)gScreenWidth / (float)gScreenHeight;

int main() {

	Camera camera(0.0f, 0.0f, 0.0f, gAspect, 30.f, 0.1f, 1000.f);
	LightD light;
	Screen screen(gScreenWidth, gScreenHeight, camera, light);

	Mesh smoothMonkey(1, "monkey-smooth.obj");
	//Mesh monkey("cube.obj");
	Cube monkey;
	smoothMonkey.translate(-1.5f, 0.0f, -2.f);
	monkey.translate(1.5f, 0.0f, -3.f);

	/*
	Vert p1(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f);
	Vert p2(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f);
	Vert p3(0.0f, 0.5f, 0.0f, 5.0f, 0.0f, 1.0f);
	Vert a = direc(p2, p1);
	Vert b = direc(p3, p1);
	Vert normal = cross(a, b);

	Trig t1(p1, p2, p3, normal.x, normal.y, normal.z);
	Mesh t;
	t.trigs = {t1};

	t.translate(500.0f, 0.0f, -2.f);*/

	float deg = 0.1f;
	while (1) {
		screen.start();

		smoothMonkey.rotate(0.f, deg*0.1f, 0.f);
		monkey.rotate(deg*0.2f, deg*0.1f, 0.f);
		deg += 0.1f;

		//t.rotate(0.0f, deg, 0.0f);
		//deg+= 0.01f;
		//screen.shadeMeshSmooth(t);
		//screen.shadeMesh(t);
		screen.shadeMeshSmooth(smoothMonkey);
		screen.shadeMesh(monkey);

		screen.print();
		screen.clear();
	}

	return 0;
}
