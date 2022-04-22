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

		/* Default constructor - uses default values for projection
		 * @params x,y,z position of our camera
		 * @param aspect the screen aspect ratio
		 * Default value: fov = 20.0f
		 * Default value: zNear = 0.1f
		 * Default value: zFar = 1000.f */
		Camera(float x, float y, float z, float aspect);

		/* Default constructor - create camera w/o any projection
		 * Default values: x,y,z = 0 */
		Camera();

};
