#pragma once

#include "Object.h"
#include "basicShapes.h"

class GuardRail : public Object
{
private:
	float xSize, ySize, zSize, th;

public:
	GuardRail() : Object()
	{
		xSize = .5;
		ySize = 1;
		zSize = 2;
		th = 0;
	}
	GuardRail(double px, double py, double pz) : Object(px, py, pz)
	{
		xSize = .5;
		ySize = 1;
		zSize = 2;
		th = 0;
	}
	GuardRail(double px, double py, double pz, double pth) : Object(px, py, pz)
	{
		xSize = .5;
		ySize = 1;
		zSize = 2;
		th = pth;

		if (th == 90)
		{
			xSize = 2;
			zSize = .5;
		}
	}

	void draw()
	{
		basicShapes::guardRail(x, y + ySize, z, th);
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