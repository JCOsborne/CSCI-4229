#pragma once

#include "Object.h"
#include "basicShapes.h"

class Floor : public Object
{
private:
	//Dimensions of cube are centered around the middle of the top pannel
	float xSize, ySize, zSize;
	int texture;
public:
	Floor() : Object()
	{
		xSize = 1;
		ySize = 1;
		zSize = 1;
		texture = 1;
	}
	Floor(double px, double py, double pz) : Object(px, py, pz)
	{
		xSize = 1;
		ySize = 1;
		zSize = 1;
		texture = 1;
	}
	Floor(double px, double py, double pz, float dx, float dy, float dz) : Object(px, py, pz)
	{
		xSize = dx;
		ySize = dy;
		zSize = dz;
		texture = 1;
	}
	Floor(double px, double py, double pz, float dx, float dy, float dz, int pTexture) : Object(px, py, pz)
	{
		xSize = dx;
		ySize = dy;
		zSize = dz;
		texture = pTexture;
	}

	void draw()
	{
		basicShapes::cube(x, y - ySize, z, xSize, ySize, zSize, 0, 0, 0, 0, texture);
	}

	bool collide(float px, float py, float pz)
	{
		return false;
	}

};