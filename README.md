<div id="top"></div>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <img src="https://i.postimg.cc/X757pjH4/rocket-man-cube.gif" alt="Logo" width="800">

  <h3 align="center">ASCII Graphics</h3>

  <p align="center">
    C++ 3D graphics library that runs in a Linux terminal
  </p>
</div>

<!-- ABOUT THE PROJECT -->
## About The Project

<img src="https://i.postimg.cc/vM3K80qK/terminal-cube.gif" width=500>

Ascii-graphics is a basic 3D graphics library designed to run in a linux terminal.

<!-- GETTING STARTED -->
## Features

Below shows some key features of the ascii-graphics library.

### Custom OBJ Model Loading

<img src="https://i.postimg.cc/GtNvxSQy/cat.gif" width=800>

### Smooth Lighting

<img src="https://i.postimg.cc/4NcGGL02/smooth-sphere.png" width=400>

### Z Buffering

<img src="https://i.postimg.cc/k4fTkbKv/zbuffer.gif" width=800>

### Other Features
* Outline meshes
* Wireframe mode
* Fill entire mesh with single character
* Basic lighting

## Installation

1. Clone the repo
   ```
   git clone https://github.com/addr0x414b/ascii-graphics.git
   ```
2. In the cloned folder, create a build directory and cd to it
   ```
   mkdir build && cd build
   ```
3. Run cmake
   ```
   cmake ../
   ```
4. Run make
   ```
   make
   ```
5. Run the program
   ```
   ./Ascii-Graphics
   ```

<!-- USAGE EXAMPLES -->
## Usage

Below is the default code the repo comes with:

```c++
//ascii-graphics.cpp

int gScreenWidth = 200; // Define the screens width and height
int gScreenHeight = 50;
float gAspect = (float)gScreenWidth / (float)gScreenHeight;

int main() {

	Camera camera(0.0f, 0.0f, 0.0f, gAspect); // Define the scenes camera
	LightD light; // Define the scenes light
	Screen screen(gScreenWidth, gScreenHeight, camera, light); // Define the screen of the scene

	Cube cube; // Library comes with one default mesh
	cube.translate(0.0f, 0.0f, -4.f); // Must translate the mesh away from the camera (-z is into the screen)

	float deg = 0.1f;
	while (1) { // Screen loop
		screen.start(); // Begin calculating the delta time per frame

		cube.rotate(0.0f, deg, deg); // Rotate cube
		deg += 50 * screen.deltaTime; // Increase the degrees of rotation

		screen.shadeMesh(cube); // Print the cube into the buffer

		screen.print(); // Print the buffer
		screen.clear(); // Clear the screen
	}

	return 0;
}
```

### Create Scene

1. Define size of the screen
```c++
int gScreenWidth = 200; // Width and height should be no larger than terminal
int gScreenHeight = 50; // Can increase size with decreased terminal font size
float gAspect = (float)gScreenWidth / (float)gScreenHeight;
```
2. Define camera, light, and screen
```c++
Camera camera(0.0f, 0.0f, 0.0f, gAspect); // Constructor uses default projection values
LightD light; // Define the scenes light
Screen screen(gScreenWidth, gScreenHeight, camera, light); // Define the screen
```

### To Load a Custom Mesh

1. Mesh MUST be in OBJ format
2. Mesh MUST be triangulated, with normals
3. OBJ file should be in the same directory as the ascii-graphics.cpp file
4. File path MUST have "../" in front (assuming file is in the same directory as ascii-graphics.cpp)

* Flat Shaded Mesh:
```c++
Mesh meshName("../path_to_flat_mesh.obj"); // Load a FLAT SHADED mesh
meshName.translate(0.0f, 0.0f, -4.0f); // Translate the mesh away from the camera
```

* Smooth Shaded Mesh:
```c++
Mesh meshName(1, "../path_to_smooth_mesh.obj") // Load a SMOOTH SHADED mesh
meshName.translate(0.0f, 0.0f, -4.0f); // Translate the mesh away from the camera
```

### Display the Graphics

```c++
float deg = 0.1f;
while (1) { // Screen loop
	screen.start(); // Begin calculating the delta time per frame

	cube.rotate(0.0f, deg, deg); // Rotate cube
	deg += 50 * screen.deltaTime; // Increase the degrees of rotation

	screen.shadeMesh(cube); // Print the cube into the buffer

	screen.print(); // Print the buffer
	screen.clear(); // Clear the screen
}

```

### Different Display Methods

* Display a smooth shaded mesh
```c++
screen.shadeMeshSmooth(meshName);
```

* Display a flat shaded mesh
```c++
screen.shadeMesh(meshName);
```

* Fill entire mesh with a single character, no shading
```c++
screen.fillMesh(meshName, '*'); // Pick character here
```

* Show mesh triangles
```c++
screen.drawMesh(meshName, '*'); // Pick character here
```

* Display wireframe of mesh
```c++
screen.drawMeshWire(meshName, '*'); // Pick character here
```

* Can combine different methods
```c++
// Results in an outlined cube
screen.drawMesh(cube, '#'); // Draw the triangles of the cube
screen.fillMesh(cube, '*'); // Fill in the cube
```

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact

YouTube: https://www.youtube.com/watch?v=X4QSm_p7Cy4

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Thanks to the following for allowing use of their 3D models:

* [Man model by printable_models](https://free3d.com/3d-model/male-base-mesh-6682.html)
* [Rocket model by Paul Chen uploaded by nixor](https://free3d.com/3d-model/rocket-ship-v1--579030.html)
* [Cat model by snippysnappets](https://free3d.com/3d-model/low-poly-cat-46138.html)


