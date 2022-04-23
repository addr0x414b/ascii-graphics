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
