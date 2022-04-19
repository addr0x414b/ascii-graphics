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

		/* Default constructor
		 * @param xx our x position
		 * @param yy our y position
		 * @param zz our z position */
		Vert(float xx, float yy, float zz);
		Vert();
};

// Triangle, consists of vertices
class Trig {
	public:
		Vert verts[3];

		/* Default constructor
		 * @param p1,p2,p3 vertices of the triangle */
		Trig(Vert p1, Vert p2, Vert p3);
		Trig();
};

// Mesh consists of triangles
class Mesh {
	public:
		std::vector<Trig> trigs;

		/* Rotate the mesh along the Z axis
		 * @params degrees how much we rotate by in degrees */
		void rotZ(float degrees);

		/* Rotate the mesh along the X axis
		 * @params degrees how much we rotate by in degrees */
		void rotX(float degrees);

		/* Project the points of the mesh onto a 2d plane
		 * @params aspect our screen aspect ratio
		 * @params fov our field of view
		 * @params zNear our near clipping plane
		 * @params zFar our far clipping plane */
		void project(float aspect, float fov, float zNear, float zFar);


		/* Translate the mesh in any direction
		 * @param x amount in x axis
		 * @param y amount in y axis
		 * @param z amount in z axis */
		void translate(float x, float y, float z);

		void scale(float x, float y, float z);
};

/* Returns a Mat4 with the perspective projection matrix values applied
 * @params aspect our screen aspect ratio
 * @params fov our field of view
 * @params zNear our near clipping plane
 * @params zFar our far clipping plane
 * @returns Mat4 matrix with projection values */
Mat4 perspective(float aspect, float fov, float zNear, float zFar);

/* Returns a Mat4 with the rotation matrix along the Z axis
 * @params degrees the number of degrees to rotate */
Mat4 rotZ(float degrees);

/* Returns a Mat4 with the rotation matrix along the X axis
 * @params degrees the number of degrees to rotate */
Mat4 rotX(float degrees);

/* Multiply a vertex by a 4x4 matrix
 * @params v our vertex
 * @params m our 4x4 matrix */
Vert mult4(Vert v, Mat4 m);
