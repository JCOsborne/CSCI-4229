#pragma once

#include "Object.h"
#include "barrel.h"
#include "Crate.h"
#include "Floor.h"
#include "Cuboid.h"
#include "OfficeWall.h"
#include "Desk.h"
#include "GuardRail.h"
#include "LaunchRoom.h"

#include <vector>
#include <iostream>
using namespace std;

class Level
{
private:
	vector<Object*> objects;

public:
	Level()
	{
		// Office
		Object* ceiling = new Cuboid(-7.75, 8, 0.5, 7.5, .25, 10, 9);
		Object* eastWall = new Cuboid(-7.75, 0, 10, 7.5, 4, .25, 15);
		Object* northWall = new OfficeWall(0, 0, 0);
		Object* southWall = new OfficeWall(-15, 0, 0);
		Object* officeFloor = new Floor(-7.75, 0, 0.5, 7.5, .25, 10, 13);

		Object* desk = new Desk(-4, 0, .25);

		Object* c1 = new Crate(-9.7, 0, 8);
		Object* c2 = new Crate(-10, 0, 5.5);
		Object* c3 = new Crate(-12.4, 0, 6.3);
		Object* c4 = new Crate(-11, 2.3, 6.3);

		Object* b1 = new Barrel(-13, 0, -7.5);

		// Corridor
		Object* corridorFloor = new Floor(-12.25, 0, -14.5, 13, .25, 5, 4);
		Object* corridorNWall = new Cuboid(0, 0, -14.5, .25, 4, 5, 5);
		Object* corridorSWall = new Cuboid(-25.5, 0, -14.75, .25, 4, 4.75, 5);
		Object* corridorCeiling = new Cuboid(-12.25, 8, -14.5, 13, .25, 5, 4);
		Object* corridorSideWall = new Cuboid(-12.25, 0, -19.5, 13, 4, .25, 5);

		Object* b2 = new Barrel(-2, 0, -18);
		Object* b3 = new Barrel(-2, 0, -15.9);
		Object* b4 = new Barrel(-2, 2.6, -16.9);
		Object* b5 = new Barrel(-4.1, 0, -18);

		Object* c5 = new Crate(-4.1, 2.6, -18, .7, .3, .5);
		Object* c6 = new Crate(-24, 0, -16, .7, 1, 3);

		// Hallway
		Object* hallwayFloor = new Floor(-43, 0, 0.5, 27.75, .25, 5, 8);
		Object* hallwayWEnd = new Floor(-72, 8, -9.5, 1.5, 8, 5, 8);
		Object* hallwayEEnd = new Floor(-72, 8, 10.5, 1.5, 8, 5, 8);
		Object* hallwayCeiling = new Cuboid(-43, 8, 0.5, 27.75, .25, 10, 4);
		Object* hallwaySideFloor = new Floor(-20.25, 0, -7, 5, .25, 2.5, 14);
		Object* hallwayEWall = new Cuboid(-43, -4, 10, 27.75, 8, .25, 15);
		Object* hallwayWWall = new Cuboid(-48, -4, -9.75, 22.75, 8, .25, 15);
		Object* hallwayBottom = new Cuboid(-43, -4, 0.5, 27.75, .25, 10, 9);

		Object* r1 = new GuardRail(-25, 0, -7.25, 0);

		Object* r2 = new GuardRail(-17.5, 0, 5.25, 90);
		Object* r3 = new GuardRail(-21, 0, 5.25, 90);
		Object* r4 = new GuardRail(-24.5, 0, 5.25, 90);
		Object* r5 = new GuardRail(-28, 0, 5.25, 90);
		Object* r6 = new GuardRail(-31.5, 0, 5.25, 90);
		Object* r7 = new GuardRail(-35, 0, 5.25, 90);
		Object* r8 = new GuardRail(-38.5, 0, 5.25, 90);
		Object* r9 = new GuardRail(-42, 0, 5.25, 90);
		Object* r10 = new GuardRail(-45.5, 0, 5.25, 90);
		Object* r11 = new GuardRail(-49, 0, 5.25, 90);
		Object* r12 = new GuardRail(-52.5, 0, 5.25, 90);
		Object* r13 = new GuardRail(-56, 0, 5.25, 90);
		Object* r14 = new GuardRail(-59.5, 0, 5.25, 90);
		Object* r15 = new GuardRail(-63, 0, 5.25, 90);
		Object* r16 = new GuardRail(-66.5, 0, 5.25, 90);

		Object* r17 = new GuardRail(-28, 0, -4.25, 90);
		Object* r18 = new GuardRail(-31.5, 0, -4.25, 90);
		Object* r19 = new GuardRail(-35, 0, -4.25, 90);
		Object* r20 = new GuardRail(-38.5, 0, -4.25, 90);
		Object* r21 = new GuardRail(-42, 0, -4.25, 90);
		Object* r22 = new GuardRail(-45.5, 0, -4.25, 90);
		Object* r23 = new GuardRail(-49, 0, -4.25, 90);
		Object* r24 = new GuardRail(-52.5, 0, -4.25, 90);
		Object* r25 = new GuardRail(-56, 0, -4.25, 90);
		Object* r26 = new GuardRail(-59.5, 0, -4.25, 90);
		Object* r27 = new GuardRail(-63, 0, -4.25, 90);
		Object* r28 = new GuardRail(-66.5, 0, -4.25, 90);

		Object* b6 = new Barrel(-16.7, 0, 3);
		Object* b7 = new Barrel(-66.5, 0, -3);

		Object* c7 = new Crate(-22, 0, 3, 3, 1, 1);

		//Launch Room
		Object* launchRoom = new LaunchRoom(-84.5, 0, .5);
		
		// Add Office Geometry
		objects.push_back(ceiling);
		objects.push_back(eastWall);
		objects.push_back(officeFloor);

		objects.push_back(desk);

		objects.push_back(c1);
		objects.push_back(c2);
		objects.push_back(c3);
		objects.push_back(c4);

		objects.push_back(b1);

		// Add Corridor Geometry
		objects.push_back(corridorFloor);
		objects.push_back(corridorNWall);
		objects.push_back(corridorSWall);
		objects.push_back(corridorCeiling);
		objects.push_back(corridorSideWall);

		objects.push_back(b2);
		objects.push_back(b3);
		objects.push_back(b4);
		objects.push_back(b5);

		objects.push_back(c5);
		objects.push_back(c6);

		// Add Hallway Geometry
		objects.push_back(hallwayFloor);
		objects.push_back(hallwayWEnd);
		objects.push_back(hallwayEEnd);
		objects.push_back(hallwaySideFloor);
		objects.push_back(hallwayCeiling);
		objects.push_back(hallwayEWall);
		objects.push_back(hallwayWWall);
		objects.push_back(hallwayBottom);

		objects.push_back(r1);

		objects.push_back(r2);
		objects.push_back(r3);
		objects.push_back(r4);
		objects.push_back(r5);
		objects.push_back(r6);
		objects.push_back(r7);
		objects.push_back(r8);
		objects.push_back(r9);
		objects.push_back(r10);
		objects.push_back(r11);
		objects.push_back(r12);
		objects.push_back(r13);
		objects.push_back(r14);
		objects.push_back(r15);
		objects.push_back(r16);

		objects.push_back(r17);
		objects.push_back(r18);
		objects.push_back(r19);
		objects.push_back(r20);
		objects.push_back(r21);
		objects.push_back(r22);
		objects.push_back(r23);
		objects.push_back(r24);
		objects.push_back(r25);
		objects.push_back(r26);
		objects.push_back(r27);
		objects.push_back(r28);

		objects.push_back(b6);
		objects.push_back(b7);

		objects.push_back(c7);

		// Launch Room
		objects.push_back(launchRoom);

		// Objects with tranparency
		objects.push_back(northWall);
		objects.push_back(southWall);
	}
	void addObject(Object* obj)
	{
		objects.push_back(obj);
	}
	Object* checkCollision(double px, double py, double pz)
	{

		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i)->collide(px, py, pz))
			{
				return objects.at(i);
			}
		}

		return NULL;
	}
	void draw()
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			objects.at(i)->draw();
		}
	}
};