#pragma once

#include <vector>

/* Ascii Graphics Mathematics library */

// 4x4 matrix
class Mat4 {
	public:
		float m[4][4] = { 0 };
};

// Vertices used in a triangle
class Vert {
	public:
		float x, y, z; // Our points to the vertex

		/* Default constructor - create a vertex
		 * @param xx our x position
		 * @param yy our y position
		 * @param zz our z position */
		Vert(float xx, float yy, float zz);

		/* Default constructor - create a vertex
		 * Default values: x,y,z = 0 */
		Vert();
};

// Triangle, consists of vertices
class Trig {
	public:
		Vert verts[3];
		Vert fNormal; // Face normal vector

		/* Default constructor - create a triangle
		 * @params p1,p2,p3 vertices of the triangle
		 * @params x,y,z the face normal of the triangle */
		Trig(Vert p1, Vert p2, Vert p3, float x, float y, float z);
};

// Mesh, consists of triangles
class Mesh {
	public:
		std::vector<Trig> trigs; // All of the triangles in the mesh

		/* Rotate the mesh along the Z axis
		 * @param degrees how much we rotate by in degrees */
		void rotZ(float degrees);

		/* Rotate the mesh along the X axis
		 * @param degrees how much we rotate by in degrees */
		void rotX(float degrees);

		/* Translate the mesh
		 * @params x,y,z amount to translate in the x,y,z axis */
		void translate(float x, float y, float z);

		/* Scale the mesh
		 * @params x,y,z amount to scale in the x,y,z axis */
		void scale(float x, float y, float z);
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
