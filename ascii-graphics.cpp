#include "Screen.hpp"
#include "agm.hpp"
#include "Camera.hpp"
#include <iostream>
#include <algorithm>
#include "Lights.hpp"

// Global variables
int gScreenWidth = 150;
int gScreenHeight = 50;
float gAspect = (float)gScreenHeight / gScreenWidth;

int main() {

	Camera camera(0.0f, 0.0f, 20.0f, gAspect);
	LightD light;
	Screen screen(gScreenWidth, gScreenHeight, camera, light);

	/*
	Vert p1(0.0f, 0.5f, 0.0f);
	Vert p2(-0.5f, -0.5f, 0.0f);
	Vert p3(0.5f, -0.5f, 0.0f);
	Trig t1(p1, p2, p3, 0.0f, 0.0f, 1.0f);

	Vert p4(0.0f, 0.5f, 0.0f);
	Vert p5(-0.5f, -0.5f, 0.0f);
	Vert p6(0.5f, -0.5f, 0.0f);
	Trig t2(p4, p5, p6, 0.0f, 0.0f, 1.0f);

	Mesh t;
	Mesh tt; */

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
	float deg = 0.1f;


	while (1) {
		cube.trigs = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12};
		cube2.trigs = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12};
		cube3.trigs = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12};
		//cube.scale(0.5f, 0.5f, 0.5f);
		cube.rotZ(45);
		cube.rotX(45);
		cube2.rotZ(deg);
		cube2.rotX(deg);
		//cube3.rotZ(-deg*1.7f);
		//cube3.rotX(-deg*1.7f);
		deg += 0.01f;
		cube.translate(-1.0f, 0.0f, -4.f);
		cube2.translate(1.0f, 0.0f, -8.f);
		//cube3.translate(2.0f, 8.0f, -12.f);
		//screen.fillMesh(cube, '#');
		screen.shadeMesh(cube2);
		screen.shadeMesh(cube);
		//screen.shadeMesh(cube3);
		//screen.drawMesh(cube, '*');
		//screen.fillMesh(cube2, '#');
		//screen.drawMesh(cube2, '*');
		//screen.fillMesh(cube3, '#');
		//screen.drawMesh(cube3, '*');

		/*
		t.trigs = {t1};
		tt.trigs = {t2};

		t.rotX(45.0f);
		//deg += 0.005f;
		t.translate(-0.0f, 0.0f, -1.5f);
		tt.translate(0.0f, 0.0f, -3.00f);
		//deg += 0.001f;

		//screen.drawMesh(t, '*');
		//screen.fillMesh(t, '#');
		screen.shadeMesh(t);
		screen.shadeMesh(tt);*/


		screen.print();
		screen.clear();
	}

	return 0;
}
