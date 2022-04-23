#include "Mesh.hpp"

/* Default constructor
 * @param xx our x position
 * @param yy our y position
 * @param zz our z position */
Vert::Vert(float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;
}

/* Default constructor - create a vertex
 * Default values: x,y,z = 0 */
Vert::Vert() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

/* Default constructor
 * @params p1,p2,p3 vertices of the triangle
 * @params x,y,z the face normal of the triangle */
Trig::Trig(Vert p1, Vert p2, Vert p3, float x, float y, float z) {
	verts[0] = p1;
	verts[1] = p2;
	verts[2] = p3;

	Vert n(x, y, z);
	fNormal = n;
}

/* Default constructor - creates a simple unit cube. Inherits from mesh */
Cube::Cube() {
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

	trigs = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12};

}
