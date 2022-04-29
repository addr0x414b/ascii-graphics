#include "agm.hpp"
#include <iostream>
#include <math.h>

Mat4::Mat4() {
	m.resize(4, std::vector<float>(4, 0.0f));
}

/* Creates a Mat4 with the perspective projection matrix values applied
 * @param aspect: the screen aspect ratio
 * @param fov: the field of view
 * @param zNear: the near clipping plane
 * @param zFar: the far clipping plane
 * @return Mat4: matrix with projection values */
Mat4 perspective(float aspect, float fov, float zNear, float zFar) {
	Mat4 m;

	float fovRad = (fov/2.f) * (3.141592f / 180.f);

	m.m[0][0] = (1.f / (tan(fovRad))) / aspect;
	m.m[1][1] = 1.f / tanf(fovRad);
	m.m[2][2] = ((-2.f * zNear) / (zFar - zNear)) - 1.f;
	m.m[3][2] = (-zNear * zFar) / (zFar - zNear);
	m.m[2][3] = -1.0f;

	/*
	m.m[0][0] = 1.0f / (tanf((fov * (3.141592f / 180.f))/2.f)) / aspect;
	m.m[1][1] = 1.0f / tanf((fov * (3.141592f / 180.f)/2.f));
	m.m[2][2] = - ((zFar + zNear) / (zFar - zNear));
	m.m[2][3] = - ((2 * zFar * zNear) / (zFar - zNear));
	m.m[3][2] = -1.f;*/

	return m;
}

/* Creates a Mat4 with the rotation matrix along the X axis
 * @param degrees the number of degrees to rotate
 * @return Mat4 rotation matrix */
Mat4 rotX(float degrees) {
	Mat4 m;

	degrees = (degrees) * (3.141592f / 180.f);

	m.m[0][0] = 1.0f;
	m.m[1][1] = cosf(degrees);
	m.m[1][2] = -sinf(degrees);
	m.m[2][1] = sinf(degrees);
	m.m[2][2] = cosf(degrees);
	m.m[3][3] = 1.0f;

	return m;
}

/* Creates a Mat4 with the rotation matrix along the Y axis
 * @param degrees the number of degrees to rotate
 * @return Mat4 rotation matrix */
Mat4 rotY(float degrees) {
	Mat4 m;

	degrees = (degrees) * (3.141592f / 180.f);

	m.m[0][0] = cosf(degrees);
	m.m[0][2] = sinf(degrees);
	m.m[1][1] = 1.0f;
	m.m[2][0] = -sinf(degrees);
	m.m[2][2] = cosf(degrees);
	m.m[3][3] = 1.0f;

	return m;
}

/* Creates a Mat4 with the rotation matrix along the Z axis
 * @param degrees the number of degrees to rotate
 * @return Mat4 rotation matrix */
Mat4 rotZ(float degrees) {
	Mat4 m;

	degrees = (degrees) * (3.141592f / 180.f);

	m.m[0][0] = cosf(degrees);
	m.m[0][1] = -sinf(degrees);
	m.m[1][0] = sinf(degrees);
	m.m[1][1] = cosf(degrees);
	m.m[2][2] = 1.f;
	m.m[3][3] = 1.f;

	return m;
}

/* Rotate the mesh
 * @params x,y,z amount in each axis */
void Mesh::rotate(float x, float y, float z) {

	Mat4 xMat = ::rotX(x);
	Mat4 yMat = ::rotY(y);
	Mat4 zMat = ::rotZ(z);

	unTranslate();
	unRotateZ();
	unRotateX();
	unRotateY();
	for (auto &trig : trigs) {
		trig.verts[0] = mult4(trig.verts[0], yMat);
		trig.verts[1] = mult4(trig.verts[1], yMat);
		trig.verts[2] = mult4(trig.verts[2], yMat);
		trig.norms[0] = mult4(trig.norms[0], yMat);
		trig.norms[1] = mult4(trig.norms[1], yMat);
		trig.norms[2] = mult4(trig.norms[2], yMat);
		trig.fNormal = mult4(trig.fNormal, yMat);

		trig.verts[0] = mult4(trig.verts[0], xMat);
		trig.verts[1] = mult4(trig.verts[1], xMat);
		trig.verts[2] = mult4(trig.verts[2], xMat);
		trig.norms[0] = mult4(trig.norms[0], xMat);
		trig.norms[1] = mult4(trig.norms[1], xMat);
		trig.norms[2] = mult4(trig.norms[2], xMat);
		trig.fNormal = mult4(trig.fNormal, xMat);

		trig.verts[0] = mult4(trig.verts[0], zMat);
		trig.verts[1] = mult4(trig.verts[1], zMat);
		trig.verts[2] = mult4(trig.verts[2], zMat);
		trig.norms[0] = mult4(trig.norms[0], zMat);
		trig.norms[1] = mult4(trig.norms[1], zMat);
		trig.norms[2] = mult4(trig.norms[2], zMat);
		trig.fNormal = mult4(trig.fNormal, zMat);
	}
	staticTranslate(transAmt.x, transAmt.y, transAmt.z);
	rotAmt.x = x;
	rotAmt.y = y;
	rotAmt.z = z;

}

/* Translate the mesh
 * @params x,y,z amount to translate in the x,y,z axis */
void Mesh::translate(float x, float y, float z) {
	transAmt.x += x;
	transAmt.y += y;
	transAmt.z += z;
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

/* Translate the mesh statically, as in set the points and that's it
 * @params x,y,z amount to translate in the x,y,z axis */
void Mesh::staticTranslate(float x, float y, float z) {
	//transAmt.x = x;
	//transAmt.y = y;
	//transAmt.z = z;
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
 * @params x,y,z amount to scale in the x,y,z axis */
void Mesh::scale(float x, float y, float z) {
	unTranslate();
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

		// I'm adding this comment to remind me that for uneven scaling (such as
		// scaling y by 0.5 and x/z by 2) will mess with the normals, thus focing
		// you multiply by the inverse transpose of the transformation
		/*trig.fNormal.x *= x;
		trig.fNormal.y *= y;
		trig.fNormal.z *= z;

		float l = sqrtf(trig.fNormal.x*trig.fNormal.x + trig.fNormal.y*
		trig.fNormal.y + trig.fNormal.z*trig.fNormal.z);

		trig.fNormal.x /= l;
		trig.fNormal.y /= l;
		trig.fNormal.z /= l;*/
	}
	staticTranslate(transAmt.x, transAmt.y, transAmt.z);
}

/* Undo rotation on the X axis */
void Mesh::unRotateX() {

	Mat4 m = ::rotX(-rotAmt.x);

	for (auto &trig : trigs) {
		trig.verts[0] = mult4(trig.verts[0], m);
		trig.verts[1] = mult4(trig.verts[1], m);
		trig.verts[2] = mult4(trig.verts[2], m);
		trig.norms[0] = mult4(trig.norms[0], m);
		trig.norms[1] = mult4(trig.norms[1], m);
		trig.norms[2] = mult4(trig.norms[2], m);
		trig.fNormal = mult4(trig.fNormal, m);
	}
	rotAmt.x = 0.0f;
}

/* Undo rotation on the Y axis */
void Mesh::unRotateY() {
	Mat4 m = ::rotY(-rotAmt.y);
	for (auto &trig : trigs) {
		trig.verts[0] = mult4(trig.verts[0], m);
		trig.verts[1] = mult4(trig.verts[1], m);
		trig.verts[2] = mult4(trig.verts[2], m);
		trig.norms[0] = mult4(trig.norms[0], m);
		trig.norms[1] = mult4(trig.norms[1], m);
		trig.norms[2] = mult4(trig.norms[2], m);
		trig.fNormal = mult4(trig.fNormal, m);
	}
	rotAmt.y = 0.0f;

}

/* Undo rotation on the Z axis */
void Mesh::unRotateZ() {

	Mat4 m = ::rotZ(-rotAmt.z);
	for (auto &trig : trigs) {
		trig.verts[0] = mult4(trig.verts[0], m);
		trig.verts[1] = mult4(trig.verts[1], m);
		trig.verts[2] = mult4(trig.verts[2], m);
		trig.norms[0] = mult4(trig.norms[0], m);
		trig.norms[1] = mult4(trig.norms[1], m);
		trig.norms[2] = mult4(trig.norms[2], m);
		trig.fNormal = mult4(trig.fNormal, m);
	}
	rotAmt.z = 0.0f;
}

/* Undo translation */
void Mesh::unTranslate() {

	for (auto &trig : trigs) {
		trig.verts[0].x -= transAmt.x;
		trig.verts[0].y -= transAmt.y;
		trig.verts[0].z -= transAmt.z;

		trig.verts[1].x -= transAmt.x;
		trig.verts[1].y -= transAmt.y;
		trig.verts[1].z -= transAmt.z;

		trig.verts[2].x -= transAmt.x;
		trig.verts[2].y -= transAmt.y;
		trig.verts[2].z -= transAmt.z;

	}
	//transAmt.x = 0.0f;
	//transAmt.y = 0.0f;
	//transAmt.z = 0.0f;
}

/* Multiply a vertex by a 4x4 matrix
 * @param v our vertex
 * @param m our 4x4 matrix
 * @return product of multiplcation */
Vert mult4(Vert v, Mat4& m) {

	Vert a;

	// Temporary variables to multiply with
	float tx = v.x;
	float ty = v.y;
	float tz = v.z;

	a.x = (tx * m.m[0][0]) + (ty * m.m[0][1]) + (tz * m.m[0][2]) + m.m[0][3];
	a.y = tx * m.m[1][0] + ty * m.m[1][1] + tz * m.m[1][2] + m.m[1][3];
	a.z = tx * m.m[2][0] + ty * m.m[2][1] + tz * m.m[2][2] + m.m[2][3];
	float w = tx * m.m[3][0] + ty * m.m[3][1] + tz * m.m[3][2] + m.m[3][3];

	if (w != 0.0f) {
		a.x /= w;
		a.y /= w;
		a.z /= w;
	}

	a.xn = v.xn;
	a.yn = v.yn;
	a.zn = v.zn;

	return a;
}

/* Calculate the dot product between two vertices
 * @params a,b vertices
 * @return float result */
float dot(Vert a, Vert b) {
	return ((a.x*b.x) + (a.y*b.y) + (a.z*b.z));
}

/* Calculate the direction vector b->a
 * @params a,b vertices
 * @return Vert direction vector result */
Vert direc(Vert a, Vert b) {
	Vert r(a.x-b.x, a.y-b.y, a.z-b.z);
	return r;
}

/* Calculate the cross product of two vectors
 * @params a,b vertices
 * @return Vert cross product result */
Vert cross(Vert a, Vert b) {
	Vert c((a.y*b.z)-(a.z*b.y), (a.z*b.x)-(a.x*b.z), (a.x*b.y)-(a.y*b.x));
	return c;
}

/* Project a triangle with a perspective matrix
 * @param t the triangle
 * @param m the perspective matrix */
void project(Trig& t, Mat4 m) {
	t.verts[0] = mult4(t.verts[0], m);
	t.verts[1] = mult4(t.verts[1], m);
	t.verts[2] = mult4(t.verts[2], m);
}

/* Calculate the Z value from x,y using cross and vert of equation of plane
 * @params x,y our input x and y values
 * @param c cross product vertex from equation of plane
 * @param v point from our original triangle from equation of plane */
float calcZ(float x, float y, Vert c, Vert v) {
	float k = dot(c, v);
	float z = ((c.x*x + c.y*y - k) / (-c.z));
	//float z = (1.f/c.z)*(c.x*v.x + c.y*v.y + c.z*v.z - c.x*x - c.y*y);
	return z;
}

/* Calculate the bary coordinates given 3 points of a triangle and and x and y
 * inside of the triangle
 * @params p1,p2,p3 vertices of the triangle
 * @params x,y current point within the triangle
 * @params w1,w2,w3 store the bary outputs */
void calcBary(Vert p1, Vert p2, Vert p3, int x, int y, float& w1, float& w2,
		float& w3) {
	w1 = (((p2.y - p3.y) * (x - p3.x)) + (p3.x - p2.x) * (y - p3.y)) /
		(((p2.y - p3.y) * (p1.x - p3.x)) + ((p3.x - p2.x) * (p1.y - p3.y)));
	w2 = (((p3.y - p1.y) * (x - p3.x)) + ((p1.x - p3.x) * (y - p3.y))) /
		(((p2.y - p3.y) * (p1.x - p3.x)) + ((p3.x - p2.x) * (p1.y - p3.y)));
	w3 = 1 - w1 - w2;
}
