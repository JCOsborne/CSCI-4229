#pragma once
#include "Entity.h"
#include "CSCIx229.h"
#include "Level.h"
#include "Object.h"

#include <iostream>
using namespace std;

class Player : public Entity {
private:
	double eyeHeight;
	int ph, th;
	Level* l;
	bool noClip = false;

public:
	//Constructors
	Player(Level* pl) : Entity() 
	{
		eyeHeight = 0;
		th = 0;
		ph = 0;
		l = pl;
	}
	Player(Level* pl, double eH) : Entity()
	{
		eyeHeight = eH;
		th = 0;
		ph = 0;
		l = pl;
	}
	Player(Level* pl, double px, double py, double pz) : Entity(px, py, pz)
	{
		eyeHeight = 0;
		th = 0;
		ph = 0;
		l = pl;
	}
	Player(Level* pl, double px, double py, double pz, double eH) : Entity(px, py, pz)
	{
		eyeHeight = eH;
		th = 0;
		ph = 0;
		l = pl;
	}
	Player(Level* pl, double px, double py, double pz, double eH, double pPH, double pTH) : Entity(px, py, pz)
	{
		eyeHeight = eH;
		th = pTH;
		ph = pPH;
		l = pl;
	}

	//Getters
	double getHeight()
	{
		return eyeHeight;
	}
	int getPh()
	{
		return ph;
	}
	int getTh()
	{
		return th;
	}

	//Setters
	void setPh(int pPH)
	{
		ph = pPH;
	}
	void setTh(int pTH)
	{
		th = pTH;
	}

	//Steps
	void step(double step, int rot)
	{
		double dx = x + (step * Cos(th + rot));
		double dz = z + (step * Sin(th + rot));

		Object* o = NULL;
		if(!noClip)
			o = l->checkCollision(dx, y, dz);

		if (o == NULL)
		{
			x = dx;
			z = dz;
		}
	}
	void stepPh(int step)
	{
		ph += step;

		// Keep angle in bounds
		if (ph > 90)
			ph = 90;
		else if (ph < -90)
			ph = -90;
	}
	void stepTh(int step)
	{
		th += step;
		th %= 360;
	}

	void setNoClip()
	{
		if (noClip)
			noClip = false;
		else
			noClip = true;
	}
};
