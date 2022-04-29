#include "Camera.hpp"

/* Default constructor
 * @params x,y,z: position of our camera
 * @param aspect: the screen aspect ratio
 * @param fov: the field of view
 * @param zNear: the z near clipping
 * @param zFar: the z far clipping */
Camera::Camera(float x, float y, float z, float aspect,
		float fov, float zNear, float zFar) {
	pos.x = x; // Set camera position
	pos.y = y;
	pos.z = z;

	/* Create the projection matrix based on the inputted values */
	projMat = perspective(aspect, fov, zNear, zFar);

	/* Assign the camera values */
	a = aspect;
	f = fov;
	zN = zNear;
	zF = zFar;

}

/* Default constructor - uses default values for projection
 * @params x,y,z: position of our camera
 * @param aspect: the screen aspect ratio
 * Default value: fov = 30.0f
 * Default value: zNear = 0.1f
 * Default value: zFar = 1000.f */
Camera::Camera(float x, float y, float z, float aspect) {
	pos.x = x;
	pos.y = y;
	pos.z = z;

	projMat = perspective(aspect, 30.f, 0.1f, 1000.f);

	a = aspect;
	f = 30.f;
	zN = 0.1f;
	zF = 1000.f;
}

/* Default constructor - create camera w/o any projection
 * Default values: x,y,z = 0 */
Camera::Camera() {
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}
