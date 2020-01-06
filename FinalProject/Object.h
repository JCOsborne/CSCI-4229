#pragma once

#include "Entity.h"
#include <math.h>
#include "basicShapes.h"

class Object : public Entity
{
public:
	Object() : Entity(){}
	Object(float px, float py, float pz) : Entity(px, py, pz){}

	virtual void draw() = 0;

	virtual bool collide(float px, float py, float pz) = 0;
};