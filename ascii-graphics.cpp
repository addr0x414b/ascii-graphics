#include "Screen.hpp"
#include "agm.hpp"
#include "Camera.hpp"
#include <iostream>
#include <algorithm>

// Global variables
int gScreenWidth = 150;
int gScreenHeight = 50;
float gAspect = (float)gScreenWidth / gScreenHeight;

int main() {

	Camera camera(0.0f, 0.0f, 20.0f, gAspect);
	Screen screen(gScreenWidth, gScreenHeight, camera);

	Vert p1(1.35f, 1.0f, 0.0f);
	Vert p2(1.25f, -2.0f, 0.0f);
	Vert p3(-2.0f, 2.0f, 0.0f);
	Trig t1(p1, p2, p3, 0.0f, 0.0f, 1.0f);

	Mesh t;

	/*
	// Front Face
	Vert p1(-1.0f, 1.0f, 1.0f);
	Vert p2(-1.0f, -1.0f, 1.0f);
	Vert p3(1.0f, -1.0f, 1.0f);
	Trig t1(p1, p2, p3, 0.0f, 0.0f, 1.0f);
	Vert p4(1.0f, -1.0f, 1.0f);
	Vert p5(1.0f, 1.0f, 1.0f);
	Vert p6(-1.0f, 1.0f, 1.0f);
	Trig t2(p4, p5, p6, 0.0f, 0.0f, 1.0f);
	// Top Face
	Vert p7(-1.0f, 1.0f, 1.0f);
	Vert p8(1.0f, 1.0f, 1.0f);
	Vert p9(-1.0f, 1.0f, -1.0f);
	Trig t3(p7, p8, p9, 0.0f, 1.0f, 0.0f);
	Vert p10(1.0f, 1.0f, 1.0f);
	Vert p11(1.0f, 1.0f, -1.0f);
	Vert p12(-1.0f, 1.0f, -1.0f);
	Trig t4(p10, p11, p12, 0.0f, 1.0f, 0.0f);
	// Right Face
	Vert p13(1.0f, 1.0f, 1.0f);
	Vert p14(1.0f, -1.0f, 1.0f);
	Vert p15(1.0f, -1.0f, -1.0f);
	Trig t5(p13, p14, p15, 1.0f, 0.0f, 0.0f);
	Vert p16(1.0f, 1.0f, 1.0f);
	Vert p17(1.0f, 1.0f, -1.0f);
	Vert p18(1.0f, -1.0f, -1.0f);
	Trig t6(p16, p17, p18, 1.0f, 0.0f, 0.0f);
	// Left Face
	Vert p19(-1.0f, 1.0f, 1.0f);
	Vert p20(-1.0f, -1.0f, 1.0f);
	Vert p21(-1.0f, -1.0f, -1.0f);
	Trig t7(p19, p20, p21, -1.0f, 0.0f, 0.0f);
	Vert p22(-1.0f, 1.0f, 1.0f);
	Vert p23(-1.0f, 1.0f, -1.0f);
	Vert p24(-1.0f, -1.0f, -1.0f);
	Trig t8(p22, p23, p24, -1.0f, 0.0f, 0.0f);
	// Back Face
	Vert p25(-1.0f, 1.0f, -1.0f);
	Vert p26(-1.0f, -1.0f, -1.0f);
	Vert p27(1.0f, 1.0f, -1.0f);
	Trig t9(p25, p26, p27, 0.0f, 0.0f, -1.0f);
	Vert p28(1.0f, 1.0f, -1.0f);
	Vert p29(1.0f, -1.0f, -1.0f);
	Vert p30(-1.0f, -1.0f, -1.0f);
	Trig t10(p28, p29, p30, 0.0f, 0.0f, -1.0f);
	// Bottom Face
	Vert p31(-1.0f, -1.0f, 1.0f);
	Vert p32(-1.0f, -1.0f, -1.0f);
	Vert p33(1.0f, -1.0f, 1.0f);
	Trig t11(p31, p32, p33, 0.0f, -1.0f, 0.0f);
	Vert p34(1.0f, -1.0f, 1.0f);
	Vert p35(1.0f, -1.0f, -1.0f);
	Vert p36(-1.0f, -1.0f, -1.0f);
	Trig t12(p34, p35, p36, 0.0f, -1.0f, 0.0f);
	Mesh cube;
	Mesh cube2;
	Mesh cube3;
	float deg = 0.1f; */


	while (1) {
		/*
		cube.trigs = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12};
		cube2.trigs = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12};
		cube3.trigs = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12};
		cube.rotZ(deg);
		cube.rotX(deg);
		cube2.rotZ(-deg*1.5f);
		cube2.rotX(-deg*1.5f);
		cube3.rotZ(-deg*1.7f);
		cube3.rotX(-deg*1.7f);
		deg += 0.01f;
		cube.translate(-1.0f, 0.0f, -20.f);
		cube2.translate(3.0f, 0.0f, -40.f);
		cube3.translate(2.0f, 5.0f, -60.f);
		screen.drawMesh(cube, '*');
		screen.drawMesh(cube2, '*');
		screen.drawMesh(cube3, '*'); */

		t.trigs = {t1};

		t.translate(0.0f, 0.0f, -20.f);

		screen.drawMesh(t, '*');
		screen.fillMesh(t, '#');


		screen.print();
		screen.clear();
	}

	return 0;
}
