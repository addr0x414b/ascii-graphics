#pragma once

#include "agm.hpp"

// Simple directional light
class LightD {
	public:
		Vert position; // Light position
		Vert direction; // Light direction vector

		/* Default Constructor - Create directional light
		 * @param x,y,z light location
		 * @param xd,yd,zd light directional vector */
		LightD(float x, float y, float z, float xd, float yd, float zd);

		/* Default Constructor - Create directional light
		 * Default value: pos = 0,0,0
		 * Default value: dir = 0,0,-1 */
		LightD();
};

