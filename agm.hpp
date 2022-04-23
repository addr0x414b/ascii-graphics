#pragma once

#include <vector>
#include "Mesh.hpp"

/* Ascii Graphics Mathematics library */

// 4x4 matrix
class Mat4 {
	public:
		float m[4][4] = { 0 };
};


/* Creates a Mat4 with the perspective projection matrix values applied
 * @param aspect our screen aspect ratio
 * @param fov our field of view
 * @param zNear our near clipping plane
 * @param zFar our far clipping plane
 * @return Mat4 matrix with projection values */
Mat4 perspective(float aspect, float fov, float zNear, float zFar);

/* Creates a Mat4 with the rotation matrix along the Z axis
 * @param degrees the number of degrees to rotate
 * @return Mat4 rotation matrix */
Mat4 rotZ(float degrees);

/* Creates a Mat4 with the rotation matrix along the X axis
 * @param degrees the number of degrees to rotate
 * @return Mat4 rotation matrix */
Mat4 rotX(float degrees);

/* Multiply a vertex by a 4x4 matrix
 * @param v our vertex
 * @param m our 4x4 matrix
 * @return product of multiplcation */
Vert mult4(Vert v, Mat4 m);

/* Calculate the dot product between two vertices
 * @params a,b vertices
 * @return float result */
float dot(Vert a, Vert b);

/* Calculate the direction vector b->a
 * @params a,b vertices
 * @return Vert direction vector result */
Vert direc(Vert a, Vert b);

/* Calculate the cross product of two vectors
 * @params a,b vertices
 * @return Vert cross product result */
Vert cross(Vert a, Vert b);

/* Calculate the Z value from x,y using cross and vert of equation of plane
 * @params x,y our input x and y values
 * @param c cross product vertex from equation of plane
 * @param v point from our original triangle from equation of plane */
float calcZ(float x, float y, Vert c, Vert v);

/* Project a triangle with a perspective matrix
 * @param t the triangle
 * @param m the perspective matrix */
void project(Trig& t, Mat4 m);
