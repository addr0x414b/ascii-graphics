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

		Vert transAmt;
		Vert rotAmt;

		/* Default constructor - Set default translation/rotation amounts */
		Mesh();

		/* Default constructor - load an obj file mesh */
		Mesh(std::string objFile);

		/* Translate the mesh
		 * @params x,y,z amount to translate in the x,y,z axis */
		void translate(float x, float y, float z);

		/* Translate the mesh statically, as in set the points and that's it
		 * @params x,y,z amount to translate in the x,y,z axis */
		void staticTranslate(float x, float y, float z);

		/* Scale the mesh
		 * @params x,y,z amount to scale in the x,y,z axis */
		void scale(float x, float y, float z);

		/* Undo translation */
		void unTranslate();

		/* Undo rotation on the Z axis */
		void unRotateZ();

		/* Undo rotation on the X axis */
		void unRotateX();

		/* Rotate the mesh
		 * @params x,y,z amount in each axis */
		void rotate(float x, float y, float z);
};

class Cube : public Mesh {
	public:
		/* Default constructor - creates a simple unit cube. Inherits from mesh */
		Cube();
};
