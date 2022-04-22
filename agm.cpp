#include "agm.hpp"
#include <iostream>
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
 * @params p1,p2,p3 vertices of the triangle
 * @params x,y,z the face normal of the triangle */
Trig::Trig(Vert p1, Vert p2, Vert p3, float x, float y, float z) {
	verts[0] = p1;
	verts[1] = p2;
	verts[2] = p3;

	Vert n(x, y, z);
	fNormal = n;
}

/* Creates a Mat4 with the perspective projection matrix values applied
 * @param aspect our screen aspect ratio
 * @param fov our field of view
 * @param zNear our near clipping plane
 * @param zFar our far clipping plane
 * @return Mat4 matrix with projection values */
Mat4 perspective(float aspect, float fov, float zNear, float zFar) {
	Mat4 m;

	m.m[0][0] = 1.0f / (aspect * tan((fov * (3.141592f / 180.f))/2.f));
	m.m[1][1] = 1.0f / tan((fov * (3.141592f / 180.f)/2.f));
	m.m[2][2] = - ((zFar + zNear) / (zFar - zNear));
	m.m[2][3] = - ((2 * zFar * zNear) / (zFar - zNear));
	m.m[3][2] = -1.f;

	return m;
}

/* Creates a Mat4 with the rotation matrix along the X axis
 * @param degrees the number of degrees to rotate
 * @return Mat4 rotation matrix */
Mat4 rotX(float degrees) {
	Mat4 m;

	m.m[0][0] = 1.0f;
	m.m[1][1] = cosf(degrees);
	m.m[1][2] = -sinf(degrees);
	m.m[2][1] = sinf(degrees);
	m.m[2][2] = cosf(degrees);
	m.m[3][3] = 1.0f;

	return m;
}

/* Creates a Mat4 with the rotation matrix along the Z axis
 * @param degrees the number of degrees to rotate
 * @return Mat4 rotation matrix */
Mat4 rotZ(float degrees) {
	Mat4 m;

	m.m[0][0] = cosf(degrees);
	m.m[0][1] = -sinf(degrees);
	m.m[1][0] = sinf(degrees);
	m.m[1][1] = cosf(degrees);
	m.m[2][2] = 1.f;
	m.m[3][3] = 1.f;

	return m;
}

/* Rotate the mesh along the X axis
 * @param degrees how much we rotate by in degrees */
void Mesh::rotX(float degrees) {
	Mat4 m = ::rotX(degrees);

	for (auto &trig : trigs) {
		trig.verts[0] = mult4(trig.verts[0], m);
		trig.verts[1] = mult4(trig.verts[1], m);
		trig.verts[2] = mult4(trig.verts[2], m);
		trig.fNormal = mult4(trig.fNormal, m);
	}

}

/* Rotate the mesh along the Z axis
 * @param degrees how much we rotate by in degrees */
void Mesh::rotZ(float degrees) {
	Mat4 m = ::rotZ(degrees);

	for (auto &trig : trigs) {
		trig.verts[0] = mult4(trig.verts[0], m);
		trig.verts[1] = mult4(trig.verts[1], m);
		trig.verts[2] = mult4(trig.verts[2], m);
		trig.fNormal = mult4(trig.fNormal, m);
	}
}

/* Translate the mesh in any direction
 * @param x amount in x axis
 * @param y amount in y axis
 * @param z amount in z axis */
void Mesh::translate(float x, float y, float z) {
	for (auto &trig : trigs) {
		trig.verts[0].x += x;
		trig.verts[0].y += y;
		trig.verts[0].z += z;

		trig.verts[1].x += x;
		trig.verts[1].y += y;
		trig.verts[1].z += z;

		trig.verts[2].x += x;
		trig.verts[2].y += y;
		trig.verts[2].z += z;
	}
}

/* Scale the mesh
 * @param x amount in x axis
 * @param y amount in y axis
 * @param z amount in z axis */
void Mesh::scale(float x, float y, float z) {
	for (auto &trig : trigs) {
		trig.verts[0].x *= x;
		trig.verts[0].y *= y;
		trig.verts[0].z *= z;

		trig.verts[1].x *= x;
		trig.verts[1].y *= y;
		trig.verts[1].z *= z;

		trig.verts[2].x *= x;
		trig.verts[2].y *= y;
		trig.verts[2].z *= z;

		trig.fNormal.x *= x;
		trig.fNormal.y *= y;
		trig.fNormal.z *= z;

		float l = sqrtf(trig.fNormal.x*trig.fNormal.x + trig.fNormal.y*trig.fNormal.y + trig.fNormal.z*trig.fNormal.z);

		trig.fNormal.x /= l;
		trig.fNormal.y /= l;
		trig.fNormal.z /= l;
	}
}

/* Multiply a vertex by a 4x4 matrix
 * @param v our vertex
 * @param m our 4x4 matrix
 * @return product of multiplcation */
Vert mult4(Vert v, Mat4 m) {

	Vert a;

	// Temporary variables to multiply with
	float tx = v.x;
	float ty = v.y;
	float tz = v.z;

	a.x = tx * m.m[0][0] + ty * m.m[1][0] + tz * m.m[2][0] + m.m[3][0];
	a.y = tx * m.m[0][1] + ty * m.m[1][1] + tz * m.m[2][1] + m.m[3][1];
	a.z = tx * m.m[0][2] + ty * m.m[1][2] + tz * m.m[2][2] + m.m[3][2];
	float w = tx * m.m[0][3] + ty * m.m[1][3] + tz * m.m[2][3] + m.m[3][3];

	if (w != 0.0f) {
		a.x /= w;
		a.y /= w;
		a.z /= w;
	}

	return a;
}

/* Calculate the dot product between two vertices
 * @params a,b vertices
 * @return float result */
float dot(Vert a, Vert b) {
	return ((a.x*b.x) + (a.y*b.y) + (a.z*b.z));
}

/* Calculate the direction vector a->b
 * @params a,b vertices
 * @return Vert direction vector result */
Vert direc(Vert a, Vert b) {
	Vert r(a.x-b.x, a.y-b.y, a.z-b.y);
	return r;
}

/* Project a triangle with a perspective matrix
 * @param t the triangle
 * @param m the perspective matrix */
void project(Trig& t, Mat4 m) {
		t.verts[0] = mult4(t.verts[0], m);
		t.verts[1] = mult4(t.verts[1], m);
		t.verts[2] = mult4(t.verts[2], m);
}
