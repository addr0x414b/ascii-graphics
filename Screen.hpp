#pragma once

/* Screen library for simulating screen in terminal */

#include <iostream>
#include <vector>
#include "agm.hpp"
#include "Camera.hpp"

// Screen simulation that allows printing ascii characters to the terminal
class Screen {
	public:
		// 2D Vector that stores the 'pixels' we print
		std::vector<std::vector<char>> buffer;

		// Screen width and height
		int width, height;

		// What our screen buffer is filled with. By default it's an empty space, so
		// that the screen is empty. Can change for debug/style purposes
		char fillChar;

		// The camera that the screen will use
		Camera camera;

		// Our projection matrix for the screen
		Mat4 projMat;

		/* Default constructor
		 * @param w the screen width
		 * @param h the screen height
		 * @param c our screens camera */
		Screen(int w, int h, Camera c);

		// Print the contents of the screen buffer
		void print();

		// Clear the contents of the screen buffer
		void clear();

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

};
