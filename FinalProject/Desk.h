
#include "Object.h"
#include "basicShapes.h"

class Desk : public Object
{
private:
	//Dimensions of cube are centered around the middle of the bottom pannel
	float xSize, ySize, zSize;
public:
	Desk() : Object()
	{
		xSize = 1;
		ySize = 2;
		zSize = 3;
	}
	Desk(double px, double py, double pz) : Object(px, py, pz)
	{
		xSize = 1;
		ySize = 2;
		zSize = 3;
	}

	void draw()
	{
		basicShapes::desk(x, y + ySize, z);
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