#pragma once

#include <vector>
#include "Mesh.hpp"

/* Ascii Graphics Mathematics library */

/* 4x4 matrix of float values. Uses std vector */
class Mat4 {
	public:
		std::vector<std::vector<float>> m;

		/* Default constructor - Create 4x4 matrix with 0.0f */
		Mat4();
};


/* Creates a Mat4 with the perspective projection matrix values applied
 * @param aspect: the screen aspect ratio
 * @param fov: the field of view
 * @param zNear: the near clipping plane
 * @param zFar: the far clipping plane
 * @return Mat4: matrix with projection values */
Mat4 perspective(float aspect, float fov, float zNear, float zFar);

/* Creates a Mat4 with the rotation matrix along the Z axis
 * @param degrees: the number of degrees to rotate
 * @return Mat4: rotation matrix */
Mat4 rotZ(float degrees);

/* Creates a Mat4 with the rotation matrix along the Y axis
 * @param degrees: the number of degrees to rotate
 * @return Mat4: rotation matrix */
Mat4 rotY(float degrees);

/* Creates a Mat4 with the rotation matrix along the X axis
 * @param degrees: the number of degrees to rotate
 * @return Mat4: rotation matrix */
Mat4 rotX(float degrees);

/* Multiply a vertex by a 4x4 matrix - performs division by w
 * @param v: the vertex
 * @param m: the 4x4 matrix
 * @return Vert: product of multiplcation */
Vert mult4(Vert v, Mat4& m);

/* Calculate the dot product between two vertices
 * @params a,b: vertices
 * @return float: result */
float dot(Vert a, Vert b);

/* Calculate the direction vector a-b
 * @params a,b: vertices
 * @return Vert: direction vector result */
Vert direc(Vert a, Vert b);

/* Calculate the cross product of two vectors
 * @params a,b: vertices
 * @return Vert: cross product result */
Vert cross(Vert a, Vert b);

/* Calculate the Z value from x,y using cross and vert of equation of plane
 * @params x,y: the input x and y values
 * @param c: cross product vertex from equation of plane
 * @param v: point from our original triangle from equation of plane
 * @return float: the z value */
float calcZ(float x, float y, Vert c, Vert v);

/* Project a triangle with a perspective matrix
 * @param t: the triangle
 * @param m: the perspective matrix */
void project(Trig& t, Mat4 m);

/* Calculate the bary coordinates given 3 points of a triangle and x and y
 * inside of the triangle
 * @params p1,p2,p3: vertices of the triangle
 * @params x,y: current point within the triangle
 * @params w1,w2,w3: store the bary outputs */
void calcBary(Vert p1, Vert p2, Vert p3, int x, int y, float& w1, float& w2,
		float& w3);

