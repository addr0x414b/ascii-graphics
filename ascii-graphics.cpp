#include "Screen.hpp"
#include "agm.hpp"
#include <iostream>

// Global variables
int gScreenWidth = 100;
int gScreenHeight = 50;
float gAspect = (float)gScreenWidth / gScreenHeight;

int main() {

	Screen screen(gScreenWidth, gScreenHeight);

	Vert p1(-1.0f, 1.0f, -20.0f);
	Vert p2(-1.0f, -1.0f, -20.0f);
	Vert p3(1.0f, -1.0f, -20.0f);
	Trig t1(p1, p2, p3);

	Vert p4(1.0f, -1.0f, -20.0f);
	Vert p5(1.0f, 1.0f, -20.0f);
	Vert p6(-1.0f, 1.0f, -20.0f);
	Trig t2(p4, p5, p6);

	Mesh square;


	Mat4 projection = perspective(gAspect, 45.f, 0.1f, 1000.f);

	float deg = 0.1f;
	while (1) {
		square.trigs = {t1, t2};
		square.rotZ(deg);
		deg += 0.01f;
		square.project(gAspect, 45.f, 0.1f, 1000.f);
		square.translate(0.9f, 0.9f, 0.0f);
		square.scale(0.5f * (float)gScreenWidth, 0.5f * (float)gScreenHeight, 1.0f);
		//std::system("clear");
		//std::cout << square.trigs[0].verts[0].x << std::endl;
		//std::cout << "P1: " << p1.x << ", " << p1.y << ", " << p1.z << std::endl;
		//std::cout << "P2: " << p2.x << ", " << p2.y << ", " << p2.z << std::endl;
		//std::cout << "P3: " << p3.x << ", " << p3.y << ", " << p3.z << std::endl;
		//screen.drawLine(80.3f, 35.2131f, 2.6f, 2.32f, '*');
		/*
		Mat4 rot = rotZ(deg);
		deg += 0.005f;

		Vert rot1 = mult4(p1, rot);
		Vert rot2 = mult4(p2, rot);
		Vert rot3 = mult4(p3, rot);

		//rot1.z = p1.z - 20.0f;
		//rot2.z = p2.z - 20.0f;
		//rot3.z = p3.z - 20.0f;

		Vert proj1 = mult4(rot1, projection);
		Vert proj2 = mult4(rot2, projection);
		Vert proj3 = mult4(rot3, projection);

		proj1.x += 0.9f;
		proj2.x += 0.9f;
		proj3.x += 0.9f;
		proj1.y += 0.9f;
		proj2.y += 0.9f;
		proj3.y += 0.9f;

		proj1.x *= 0.5f * (float)gScreenWidth;
		proj1.y *= 0.5f * (float)gScreenHeight;
		proj2.x *= 0.5f * (float)gScreenWidth;
		proj2.y *= 0.5f * (float)gScreenHeight;
		proj3.x *= 0.5f * (float)gScreenWidth;
		proj3.y *= 0.5f * (float)gScreenHeight;

		//std::cout << "P1: " << proj1.x << ", " << proj1.y << ", " << proj1.z << std::endl;
		//std::cout << "P2: " << proj2.x << ", " << proj2.y << ", " << proj1.z << std::endl;
		//std::cout << "P3: " << proj3.x << ", " << proj3.y << ", " << proj3.z << std::endl;
		Trig t1(proj1, proj2, proj3);
		screen.drawTrig(t1, '*');
		*/

		screen.drawMesh(square, '*');
		screen.print();
		screen.clear();
	}

	return 0;
}
