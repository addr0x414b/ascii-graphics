#include "agm.hpp"
#include <math.h>

/* Default constructor
 * @param xx our x position
 * @param yy our y position
 * @param zz our z position */
Vert::Vert(float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;
}
Vert::Vert() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

/* Default constructor
 * @param p1,p2,p3 vertices of the triangle */
Trig::Trig(Vert p1, Vert p2, Vert p3) {
	verts[0] = p1;
	verts[1] = p2;
	verts[2] = p3;
}

/* Returns a Mat4 with the perspective projection matrix values applied
 * @params aspect our screen aspect ratio
 * @params fov our field of view
 * @params zNear our near clipping plane
 * @params zFar our far clipping plane
 * @returns Mat4 matrix with projection values */
Mat4 perspective(float aspect, float fov, float zNear, float zFar) {
	Mat4 m;

	m.m[0][0] = 1.0f / (aspect * tan((fov * (3.141592f / 180.f))/2.f));
	m.m[1][1] = 1.0f / tan((fov * (3.141592f / 180.f)/2.f));
	m.m[2][2] = - ((zFar + zNear) / (zFar - zNear));
	m.m[2][3] = - ((2 * zFar * zNear) / (zFar - zNear));
	m.m[3][2] = -1.f;

	return m;
}
