#pragma once

#include <iostream>
#include <vector>

/* Vertices used in a triangle
 * Contains the vertex position and normal (if a smooth mesh) */
class Vert {
	public:
		float x, y, z; // Points to the vertex
		float xn, yn, zn; // Vertex normal

		/* Default constructor - create a vertex with NO normal
		 * @param xx: x position
		 * @param yy: y position
		 * @param zz: z position */
		Vert(float xx, float yy, float zz);

		/* Default constructor - create a vertex WITH a normal
		 * @param xx: x position
		 * @param yy: y position
		 * @param zz: z position
		 * @param nx: x normal location
		 * @param ny: y normal location
		 * @param nz: z normal location */
		Vert(float xx, float yy, float zz, float nx, float ny, float nz);

		/* Default constructor - create a vertex
		 * Default values: x,y,z, xn,yn,zn = 0 */
		Vert();
};

// Triangle, consists of vertices along with their normals (if smooth mesh)
class Trig {
	public:
		Vert verts[3]; // Vertices of the triangle
		Vert norms[3]; // The vertex normals
		Vert fNormal; // Face normal vector

		/* Default constructor - create a triangle
		 * @params p1,p2,p3: vertices of the triangle
		 * @params x,y,z: the face normal of the triangle */
		Trig(Vert p1, Vert p2, Vert p3, float x, float y, float z);
};

// Mesh, consists of triangles
class Mesh {
	public:
		std::vector<Trig> trigs; // All of the triangles in the mesh

		/* When the mesh is rotated or translated, set the amount. Then use it when
		 * the mesh is untranslated or unrotated */
		Vert transAmt;
		Vert rotAmt;

		/* Default constructor - Set default translation/rotation amounts */
		Mesh();

		/* Default constructor - load an obj file mesh (MUST BE FLAT SHADED)
		 * @param objFile: path to file */
		Mesh(std::string objFile);

		/* Default constructor - load an obj file mesh thats smoothed
		 * @param s: any random number, doesn't matter - doesn't do anything
		 * @param objFile: path to file */
		Mesh(int s, std::string objFile);

		/* Translate the mesh
		 * @params x,y,z: amount to translate in the x,y,z axis */
		void translate(float x, float y, float z);

		/* Translate the mesh statically, as in set the points and that's it
		 * @params x,y,z: amount to translate in the x,y,z axis */
		void staticTranslate(float x, float y, float z);

		/* Scale the mesh
		 * @param amt: the amount to scale in x,y,z */
		void scale(float amt);

		/* Undo translation */
		void unTranslate();

		/* Undo rotation on the Z axis */
		void unRotateZ();

		/* Undo rotation on the Y axis */
		void unRotateY();

		/* Undo rotation on the X axis */
		void unRotateX();

		/* Rotate the mesh
		 * @params x,y,z: degrees in each axis */
		void rotate(float x, float y, float z);
};

class Cube : public Mesh {
	public:
		/* Default constructor - creates a simple unit cube. Inherits from mesh */
		Cube();
};
