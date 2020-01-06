#pragma once

#include "Object.h"
#include "CSCIx229.h"
#include "basicShapes.h"

class Barrel : public Object
{
private:
	float barrelHeight = 3.6;
	float radius = 1.5;

public:
	Barrel() : Object(){}
	Barrel(double px, double py, double pz) : Object(px, py, pz){}

	void draw()
	{
		basicShapes::barrel(x, y, z);
	}

	bool collide(float px, float py, float pz)
	{
		double xDist = x - px;
		double zDist = z - pz;
		double dist = sqrt((xDist*xDist) + (zDist * zDist));
		if (dist < radius && py >= y && py <= y + barrelHeight)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};