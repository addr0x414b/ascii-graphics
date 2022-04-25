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
		// 2D Vector that stores the 'pixels' we print
		std::vector<std::vector<char>> buffer;
		std::vector<std::vector<float>> zBuffer;

		int renderMode; // 0 to disable zBuffer, 1 to enable zBuffer;
		Vert zCross; // Our cross product for zBuffer calculation
		Vert zVert; // Our vert for interpolating Z for pixel

		// Screen width and height
		int width, height;

		float deltaTime;

		std::string shadeValues;

		// What our screen buffer is filled with. By default it's an empty space, so
		// that the screen is empty. Can change for debug/style purposes
		char fillChar;

		// The camera that the screen will use
		Camera camera;

		// Our projection matrix for the screen
		Mat4 projMat;

		// The light in the scene
		LightD light;

		/* Default constructor
		 * @param w the screen width
		 * @param h the screen height
		 * @param c our screens camera
		 * @param l our scenes light */
		Screen(int w, int h, Camera& c, LightD l);

		// Print the contents of the screen buffer
		void print();

		// Clear the contents of the screen buffer
		void clear();

		// Calculate deltaTime and FPS
		void start();

		std::chrono::steady_clock::time_point lastTime;
		std::chrono::steady_clock::time_point currTime;

		/* Draw a line to the buffer using individual coordinates
		 * @param x1 the x position of point 1
		 * @param y1 the y position of point 1
		 * @param x2 the x position of point 2
		 * @param y2 the y position of point 2
		 * @param c the character we draw to the buffer */
		void drawLine(float x1, float y1, float x2, float y2, char c);

		/* Draw a line to the buffer using verts
		 * @param a our first vertex
		 * @param b our second vertex
		 * @param c the character we draw to the buffer */
		void drawLine(Vert a, Vert b, char c);

		/* Draw a triangle to the buffer
		 * @param t our triangle to draw
		 * @param c the character we draw to the buffer */
		void drawTrig(Trig t, char c);

		/* Draw all of the triangles in a mesh to the buffer
		 * @param m our mesh
		 * @param c our draw character */
		void drawMesh(Mesh m, char c);

		/* Draw all of the triangles not considering normals
		 * @param m the mesh
		 * @param c the draw character */
		void drawMeshWire(Mesh m, char c);

		/* Fill in a mesh via a character
		 * @param m the mesh
		 * @param c the draw character */
		void fillMesh(Mesh m, char c);

		/* Shade in the mesh based on the light
		 * @param m the mesh */
		void shadeMesh(Mesh m);

		/* Fill a flat bottom triangle
		 * @param t the triangle
		 * @param c the draw character */
		void fillFb(Trig t, char c);

		/* Fill a flat top triangle
		 * @param t the triangle
		 * @param c the draw character */
		void fillFt(Trig t, char c);

	private:
		/* Draw to the buffer at a specific point. Does bounds checking
		 * @param x our x position
		 * @param y our y position
		 * @param c the character we draw to the buffer */
		void drawToBuffer(float x, float y, char c);

		/* Bring the triangle to the center of the screen. This makes the global
		 * coord of (0,0,0) in the center of the screen. Also flip the y coordinates
		 * to make the +y direction go up instead of down
		 * @param t the triangle */
		void centerFlipY(Trig& t);

		/* Check the Z Buffer at a specific location
		 * @params x,y the x and y coordinate in z buffer
		 * @param z the z we want to check with
		 * @return if the z we check with is > than z in z buffer */
		bool checkZB(float x, float y, float z);

};
