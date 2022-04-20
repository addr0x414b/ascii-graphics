#pragma once

#include "agm.hpp"

// Camera class
class Camera {
	public:
		Vert pos; // Camera position

		Mat4 projMat;

		/* Default constructor
		 * @params x,y,z position of our camera
		 * @param aspect the screen aspect ratio
		 * @param fov the field of view
		 * @param zNear the z near clipping
		 * @param zFar the z far clipping */
		Camera(float x, float y, float z, float aspect,
				float fov, float zNear, float zFar);

		/* Default constructor, uses default values for projection
		 * @params x,y,z position of our camera
		 * @param aspect the screen aspect ratio */
		Camera(float x, float y, float z, float aspect);

		Camera();

};
