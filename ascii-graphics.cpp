#include <iostream>
#include <algorithm>
#include "src/Screen.hpp"
#include "src/agm.hpp"
#include "src/Camera.hpp"
#include "src/Lights.hpp"
#include "src/Mesh.hpp"

int gScreenWidth = 200; // Define the screens width and height
int gScreenHeight = 50;
float gAspect = (float)gScreenWidth / (float)gScreenHeight;

int main() {

	Camera camera(0.0f, 0.0f, 0.0f, gAspect); // Define the scenes camera
	LightD light; // Define the scenes light
	Screen screen(gScreenWidth, gScreenHeight, camera, light); // Define the
																														 // screen of the
																														 // scene

	Cube cube; // Library comes with one default mesh
	cube.translate(0.0f, 0.0f, -4.f); // Must translate the mesh away from the
																		// camera (-z is into the screen)

	float deg = 0.1f;
	while (1) { // Screen loop
		screen.start(); // Begin calculating the delta time per frame

		cube.rotate(0.0f, deg, deg); // Rotate our cube
		deg += 50 * screen.deltaTime; // Increase the degrees of rotation

		screen.drawMeshWire(cube, '#');

		screen.print(); // Print the entire screen
		screen.clear(); // Clear the screen
	}

	return 0;
}
