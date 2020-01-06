#pragma once

#include "Object.h"
#include "basicShapes.h"

class OfficeWall : public Object
{
private:
	//Dimensions of cube are centered around the middle of the bottom pannel
	float xSize, ySize, zSize;

public:
	OfficeWall() : Object()
	{
		xSize = 1;
		ySize = 4;
		zSize = 10;
	}
	OfficeWall(double px, double py, double pz) : Object(px, py, pz)
	{
		xSize = 1;
		ySize = 4;
		zSize = 10;
	}

	void draw()
	{
		basicShapes::officeWall(x, y, z);
	}

	bool collide(float px, float py, float pz)
	{
		if (px >= x - xSize && px <= x + xSize && py >= y && py <= y + ySize && pz >= z - zSize && pz <= z + zSize)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};