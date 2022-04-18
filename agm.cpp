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

/* Multiply a vertex by a 4x4 matrix
 * @params v our vertex
 * @params m our 4x4 matrix */
void mult4(Vert& v, Mat4 m) {
	// Temporary variables to multiply with
	float tx = v.x;
	float ty = v.y;
	float tz = v.z;

	v.x = tx * m.m[0][0] + ty * m.m[1][0] + tz * m.m[2][0] + m.m[3][0];
	v.y = tx * m.m[0][1] + ty * m.m[1][1] + tz * m.m[2][1] + m.m[3][1];
	v.z = tx * m.m[0][2] + ty * m.m[1][2] + tz * m.m[2][2] + m.m[3][2];
	float w = tx * m.m[0][3] + ty * m.m[1][3] + tz * m.m[2][3] + m.m[3][3];

	if (w != 0.0f) {
		v.x /= w;
		v.y /= w;
		v.z /= w;
	}
}
