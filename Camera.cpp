#include "Camera.hpp"

/* Default constructor
 * @params x,y,z position of our camera
 * @param aspect the screen aspect ratio
 * @param fov the field of view
 * @param zNear the z near clipping
 * @param zFar the z far clipping */
Camera::Camera(float x, float y, float z, float aspect,
		float fov, float zNear, float zFar) {
		pos.x = x;
		pos.y = y;
		pos.z = z;

		projMat = perspective(aspect, fov, zNear, zFar);
}

/* Default constructor, uses default values for projection
 * @params x,y,z position of our camera
 * @param aspect the screen aspect ratio */
Camera::Camera(float x, float y, float z, float aspect) {
	pos.x = x;
	pos.y = y;
	pos.z = z;

	projMat = perspective(aspect, 45.f, 0.1f, 1000.f);
}

Camera::Camera() {
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}
