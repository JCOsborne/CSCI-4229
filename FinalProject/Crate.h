#pragma once

#include "Object.h"
#include "basicShapes.h"

class Crate : public Object
{
private:
	//Dimensions of cube are centered around the middle of the bottom pannel
	float xSize, ySize, zSize;

public:
	Crate() : Object()
	{
		xSize = 1;
		ySize = 1;
		zSize = 1;
	}
	Crate(float px, float py, float pz) : Object(px, py, pz)
	{
		xSize = 1;
		ySize = 1;
		zSize = 1;
	}
	Crate(float px, float py, float pz, float dx, float dy, float dz) : Object(px, py, pz)
	{
		xSize = dx;
		ySize = dy;
		zSize = dz;
	}

	void draw()
	{
		basicShapes::crate(x, y, z, xSize, ySize, zSize, 0);
	}

	bool collide(float px, float py, float pz)
	{
		//maybe bad
		float halfX = xSize;
		float halfZ = zSize;
		if (px >= x - halfX && px <= x + halfX && py >= y && py <= y + ySize && pz >= z - halfZ && pz <= z + halfZ)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};