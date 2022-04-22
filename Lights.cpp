#include "Lights.hpp"


/* Default Constructor - Create directional light
 * @param x,y,z light location
 * @param xd,yd,zd light directional vector */
LightD::LightD(float x, float y, float z, float xd, float yd, float zd) {
	Vert p(x, y, z);
	position = p;
	Vert d(xd, yd, zd);
	direction = d;
}

/* Default Constructor - Create directional light
 * Default value: pos = 0,0,0
 * Default value: dir = 0,0,-1 */
LightD::LightD() {
	Vert p(0.0f, 0.0f, 0.0f);
	position = p;
	Vert d(0.0f, 0.0f, -1.0f);
	direction = d;
}
