#pragma once

#include "Object.h"
#include "basicShapes.h"

class LaunchRoom : public Object
{
private:
	//Dimensions of cube are centered around the middle of the bottom pannel
	float radius = 9;
public:
	LaunchRoom() : Object()
	{

	}
	LaunchRoom(double px, double py, double pz) : Object(px, py, pz)
	{

	}

	void draw()
	{
		basicShapes::launchRoom(x, y, z);
	}

	bool collide(float px, float py, float pz)
	{
		double xDist = x - px;
		double zDist = z - pz;
		double dist = sqrt((xDist*xDist) + (zDist * zDist));
		if (dist < radius)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};