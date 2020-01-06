#pragma once

class Entity {
protected:
	double x, y, z;

public:
	Entity()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	Entity(double px, double py, double pz)
	{
		x = px;
		y = py;
		z = pz;
	}

	//Getters
	double getX()
	{
		return x;
	}
	double getY()
	{
		return y;
	}
	double getZ()
	{
		return z;
	}

	//Setters
	void setX(double px)
	{
		x = px;
	}
	void setY(double py)
	{
		y = py;
	}
	void setZ(double pz)
	{
		z = pz;
	}
};