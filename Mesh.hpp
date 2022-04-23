#pragma once

#include <iostream>
#include <vector>

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
