#pragma once

/* Screen library for simulating screen in terminal */

#include <iostream>
#include <vector>
#include "agm.hpp"
#include "Camera.hpp"
#include "Lights.hpp"
#include "Mesh.hpp"
#include <chrono>

// Screen simulation that allows printing ascii characters to the terminal
class Screen {
	public:
		// 2D vector that stores the 'pixels' to be printed
		std::vector<std::vector<char>> buffer;
		// 2D vector that stores the z values of each pixel
		std::vector<std::vector<float>> zBuffer;

		int renderMode; // 0 to disable zBuffer, 1 to enable zBuffer;
		Vert zCross; // Our cross product for zBuffer calculation
		Vert zVert; // Our vert for interpolating Z for pixel

		Vert p1N; // Current triangle vertex normals. Used for smooth shading
		Vert p2N; // Only used when we call the shadeMeshSmooth function
		Vert p3N;

		Vert tP1; // Our current triangle points. Used for calculating bary coords
		Vert tP2;
		Vert tP3;

		// Screen width and height
		int width, height;

		float deltaTime; // Delta time of the program

		std::string shadeValues; // Store the different ascii characters for shading

		// What the screen buffer is filled with. By default it's an empty space, so
		// that the screen is empty. Can change for debug/style purposes
		char fillChar;

		// The camera that the screen will use
		Camera camera;

		// The light in the scene
		LightD light;

		/* Default constructor
		 * @param w: screen width
		 * @param h: screen height
		 * @param c: screens camera
		 * @param l: scenes light */
		Screen(int w, int h, Camera& c, LightD l);

		// Print the contents of the screen buffer
		void print();

		// Clear the contents of the screen buffer and z buffer
		void clear();

		// Calculate deltaTime
		void start();

		// Used to calculate the deltaTime
		std::chrono::steady_clock::time_point lastTime;
		std::chrono::steady_clock::time_point currTime;

		/* Draw a line to the buffer using individual coordinates
		 * @param x1: x position of point 1
		 * @param y1: y position of point 1
		 * @param x2: x position of point 2
		 * @param y2: y position of point 2
		 * @param c: character to draw to the buffer */
		void drawLine(float x1, float y1, float x2, float y2, char c);

		/* Draw a line to the buffer using verts
		 * @param a: first vertex
		 * @param b: second vertex
		 * @param c: character to draw to the buffer */
		void drawLine(Vert a, Vert b, char c);

		/* Draw a triangle to the buffer
		 * @param t: triangle to draw
		 * @param c: character to draw to the buffer */
		void drawTrig(Trig t, char c);

		/* Draw all of the triangles in a mesh to the buffer
		 * @param m: mesh
		 * @param c: draw character */
		void drawMesh(Mesh m, char c);

		/* Draw all of the triangles in wireframe. DOESN'T consider normals
		 * @param m: mesh
		 * @param c: draw character */
		void drawMeshWire(Mesh m, char c);

		/* Fill in a mesh via a character
		 * @param m: mesh
		 * @param c: draw character */
		void fillMesh(Mesh m, char c);

		/* Shade in the mesh based on the light direction. FLAT SHADED!
		 * @param m: mesh */
		void shadeMesh(Mesh m);

		/* Shade in the mesh smooth based on the light direction
		 * @param m: SMOOTHED mesh */
		void shadeMeshSmooth(Mesh m);

		/* Fill a flat bottom triangle
		 * @param t: triangle
		 * @param c: draw character */
		void fillFb(Trig t, char c);

		/* Fill a flat top triangle
		 * @param t: triangle
		 * @param c: draw character */
		void fillFt(Trig t, char c);

	private:
		/* Draw to the buffer at a specific point. Does bounds checking
		 * @param x: x position
		 * @param y: y position
		 * @param c: character to draw to the buffer */
		void drawToBuffer(float x, float y, char c);

		/* Center the triangles to the middle of the screen, flip the triangles so
		 * +y is up, and scale the x based on aspect ratio
		 * @param t: triangle */
		void centerFlipY(Trig& t);

		/* Check the Z Buffer at a specific location
		 * @params x,y: the x and y coordinate in z buffer
		 * @param z: z we want to check with
		 * @return bool: if the z we check with is < than z in z buffer */
		bool checkZB(float x, float y, float z);

};
