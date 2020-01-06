#pragma once

#include "CSCIx229.h"

float shiny = 10;  // Shininess (value)
unsigned int barrelSide, barrelEnd, wood, concrete, wall, wall2, rocketBody, noseCone, boltedMetal, glass, reflector, plastic, darkWood, carpet, gratedMetal;

class basicShapes
{
public:
	static void loadBasicTex()
	{
		//1
		barrelSide = LoadTexBMP("barrel_sb.bmp");
		//2
		barrelEnd = LoadTexBMP("barrel_end.bmp");
		//3
		wood = LoadTexBMP("wood.bmp");
		//4
		concrete = LoadTexBMP("concrete.bmp");
		//5
		wall = LoadTexBMP("wall.bmp");
		//6
		rocketBody = LoadTexBMP("rocket.bmp");
		//7
		noseCone = LoadTexBMP("noseCone.bmp");
		//8
		boltedMetal = LoadTexBMP("boltedMetal.bmp");
		//9
		glass = LoadTexBMP("glass.bmp");
		//10
		reflector = LoadTexBMP("reflector.bmp");
		//11
		plastic = LoadTexBMP("plastic.bmp");
		//12
		darkWood = LoadTexBMP("darkwood.bmp");
		//13
		carpet = LoadTexBMP("carpet.bmp");
		//14
		gratedMetal = LoadTexBMP("gratedMetal.bmp");
		//15
		wall2 = LoadTexBMP("wall2.bmp");
	}

	/*
	*  Draw vertex in polar coordinates with normal
	*/
	static void Vertex(double th, double ph)
	{
		double x = Sin(th)*Cos(ph);
		double y = Cos(th)*Cos(ph);
		double z = Sin(ph);
		//  For a sphere at the origin, the position
		//  and normal vectors are the same
		glNormal3d(x, y, z);
		glVertex3d(x, y, z);
	}

	/*
	 *  Draw a ball
	 *     at (x,y,z)
	 *     radius (r)
	 */
	static void ball(double x, double y, double z, double r)
	{
		int th, ph, inc;
		float yellow[] = { 1.0,1.0,0.0,1.0 };
		float Emission[] = { 0.0,0.0,0.0,1.0 };
		//  Save transformation
		glPushMatrix();
		//  Offset, scale and rotate
		glTranslated(x, y, z);
		glScaled(r, r, r);
		//  White ball
		glColor3f(1, 1, 1);
		glMaterialf(GL_FRONT, GL_SHININESS, shiny);
		glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
		glMaterialfv(GL_FRONT, GL_EMISSION, Emission);
		//  Bands of latitude
		inc = 10;
		for (ph = -90; ph < 90; ph += inc)
		{
			glBegin(GL_QUAD_STRIP);
			for (th = 0; th <= 360; th += 2 * inc)
			{
				Vertex(th, ph);
				Vertex(th, ph + inc);
			}
			glEnd();
		}
		//  Undo transofrmations
		glPopMatrix();
	}

	/*
	 *  Draw a cube
	 *     at (x,y,z)
	 *     dimensions (dx,dy,dz)
	 *     rotated th about the y axis
	 *	   with color defined by uByte r, g, b
	 */
	static void cube(double x, double y, double z,
		double dx, double dy, double dz,
		double th,
		int r, int g, int b,
		unsigned int texture = concrete)
	{
		glEnable(GL_TEXTURE_2D);

		//  Set specular color to white
		float white[] = { 1,1,1,1 };
		float black[] = { 0,0,0,1 };
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z);
		glRotated(th, 0, 1, 0);
		glScaled(dx, dy, dz);
		//  Cube
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glColor3ub(r, g, b);
		//  Front
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 1);
		glVertex3f(-1, -1, 1);
		glTexCoord2f(1, 1);
		glVertex3f(+1, -1, 1);
		glTexCoord2f(1, 0);
		glVertex3f(+1, +1, 1);
		glTexCoord2f(0, 0);
		glVertex3f(-1, +1, 1);
		//  Back
		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 1);
		glVertex3f(+1, -1, -1);
		glTexCoord2f(1, 1);
		glVertex3f(-1, -1, -1);
		glTexCoord2f(1, 0);
		glVertex3f(-1, +1, -1);
		glTexCoord2f(0, 0);
		glVertex3f(+1, +1, -1);
		//  Right
		glNormal3f(+1, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3f(+1, -1, +1);
		glTexCoord2f(1, 1);
		glVertex3f(+1, -1, -1);
		glTexCoord2f(1, 0);
		glVertex3f(+1, +1, -1);
		glTexCoord2f(0, 0);
		glVertex3f(+1, +1, +1);
		//  Left
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3f(-1, -1, -1);
		glTexCoord2f(1, 1);
		glVertex3f(-1, -1, +1);
		glTexCoord2f(1, 0);
		glVertex3f(-1, +1, +1);
		glTexCoord2f(0, 0);
		glVertex3f(-1, +1, -1);
		//  Top
		glNormal3f(0, +1, 0);
		glTexCoord2f(0, 1);
		glVertex3f(-1, +1, +1);
		glTexCoord2f(1, 1);
		glVertex3f(+1, +1, +1);
		glTexCoord2f(1, 0);
		glVertex3f(+1, +1, -1);
		glTexCoord2f(0, 0);
		glVertex3f(-1, +1, -1);
		//  Bottom
		glNormal3f(0, -1, 0);
		glTexCoord2f(0, 1);
		glVertex3f(-1, -1, -1);
		glTexCoord2f(1, 1);
		glVertex3f(+1, -1, -1);
		glTexCoord2f(1, 0);
		glVertex3f(+1, -1, +1);
		glTexCoord2f(0, 0);
		glVertex3f(-1, -1, +1);
		//  End
		glEnd();
		//  Undo transofrmations
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	}

	/*
	 *  Draw a cube with a tesselating surface that scales
	 *     at (x,y,z)
	 *     dimensions (dx,dy,dz)
	 *     rotated th about the y axis
	 *	   with color defined by uByte r, g, b
	 */
	static void cube2(double x, double y, double z,
		double dx, double dy, double dz,
		double th,
		int r, int g, int b,
		unsigned int texture)
	{
		glEnable(GL_TEXTURE_2D);

		//  Set specular color to white
		float white[] = { 1,1,1,1 };
		float black[] = { 0,0,0,1 };
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z);
		glRotated(th, 0, 1, 0);
		glScaled(dx, dy, dz);
		//  Cube
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glColor3ub(r, g, b);

		float d = .5;
		float sx = d / dx;
		float sz = d / dz;
		float sy = d / dy;

		//  Front
		glNormal3f(0, 0, 1);

		for (float i = -1; i < 1; i += sx)
		{
			for (float j = -1; j < 1; j += sy)
			{
				glTexCoord2f((i + 1) / 2, 1 - ((j + 1) / 2));
				glVertex3f(i, j, 1);
				glTexCoord2f((i + sx + 1) / 2, 1 - ((j + 1) / 2));
				glVertex3f(i + sx, j, 1);
				glTexCoord2f((i + sx + 1) / 2, 1 - (j + 1 + sy) / 2);
				glVertex3f(i + sx, j + sy, 1);
				glTexCoord2f((i + 1) / 2, 1 - (j + sy + 1) / 2);
				glVertex3f(i, j + sy, 1);
			}
		}
		//  Back
		glNormal3f(0, 0, -1);

		for (float i = -1; i < 1; i += sx)
		{
			for (float j = -1; j < 1; j += sy)
			{
				glTexCoord2f((i + 1) / 2, 1 - (j + sy + 1) / 2);
				glVertex3f(i, j + sy, -1);
				glTexCoord2f((i + sx + 1) / 2, 1 - (j + 1 + sy) / 2);
				glVertex3f(i + sx, j + sy, -1);
				glTexCoord2f((i + sx + 1) / 2, 1 - ((j + 1) / 2));
				glVertex3f(i + sx, j, -1);
				glTexCoord2f((i + 1) / 2, 1 - ((j + 1) / 2));
				glVertex3f(i, j, -1);
			}
		}
		//  Right
		glNormal3f(+1, 0, 0);

		for (float i = -1; i < 1; i += sz)
		{
			for (float j = -1; j < 1; j += sy)
			{
				glTexCoord2f((i + sz + 1) / 2, 1 - ((j + 1) / 2));
				glVertex3f(1, j, i + sz);
				glTexCoord2f((i + 1) / 2, 1 - ((j + 1) / 2));
				glVertex3f(1, j, i);
				glTexCoord2f((i + 1) / 2, 1 - (j + sy + 1) / 2);
				glVertex3f(1, j + sy, i);
				glTexCoord2f((i + sz + 1) / 2, 1 - (j + 1 + sy) / 2);
				glVertex3f(1, j + sy, i + sz);
			}
		}
		//  Left
		glNormal3f(-1, 0, 0);

		for (float i = -1; i < 1; i += sz)
		{
			for (float j = -1; j < 1; j += sy)
			{
				glTexCoord2f((i + 1) / 2, 1 - ((j + 1) / 2));
				glVertex3f(-1, j, i);
				glTexCoord2f((i + sz + 1) / 2, 1 - ((j + 1) / 2));
				glVertex3f(-1, j, i + sz);
				glTexCoord2f((i + sz + 1) / 2, 1 - (j + 1 + sy) / 2);
				glVertex3f(-1, j + sy, i + sz);
				glTexCoord2f((i + 1) / 2, 1 - (j + sy + 1) / 2);
				glVertex3f(-1, j + sy, i);
			}
		}
		//  Top
		glNormal3f(0, +1, 0);

		for (float i = -1; i < 1; i += sx)
		{
			for (float j = -1; j < 1; j += sz)
			{
				glTexCoord2f((i + 1) / 2, 1 - (j + sz + 1) / 2);
				glVertex3f(i, 1, j + sz);
				glTexCoord2f((i + sx + 1) / 2, 1 - (j + 1 + sz) / 2);
				glVertex3f(i + sx, 1, j + sz);
				glTexCoord2f((i + sx + 1) / 2, 1 - ((j + 1) / 2));
				glVertex3f(i + sx, 1, j);
				glTexCoord2f((i + 1) / 2, 1 - ((j + 1) / 2));
				glVertex3f(i, 1, j);
			}
		}
		//  Bottom
		glNormal3f(0, -1, 0);

		for (float i = -1; i < 1; i += sx)
		{
			for (float j = -1; j < 1; j += sz)
			{
				glTexCoord2f((i + 1) / 2, 1 - ((j + 1) / 2));
				glVertex3f(i, -1, j);
				glTexCoord2f((i + sx + 1) / 2, 1 - ((j + 1) / 2));
				glVertex3f(i + sx, -1, j);
				glTexCoord2f((i + sx + 1) / 2, 1 - (j + 1 + sz) / 2);
				glVertex3f(i + sx, -1, j + sz);
				glTexCoord2f((i + 1) / 2, 1 - (j + sz + 1) / 2);
				glVertex3f(i, -1, j + sz);
			}
		}
		//  End
		glEnd();
		//  Undo transofrmations
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	}

	/*
	 *  Draw a cylinder
	 *     at (x,y,z)
	 *     dimensions (dx,dy,dz)
	 *     rotated th about the x axis
	 *	   with color defined by uByte r, g, b
	 */
	static void cylinder(double x, double y, double z,
		double dx, double dy, double dz,
		double th,
		int r, int g, int b,
		unsigned int side, unsigned int ends)
	{
		glEnable(GL_TEXTURE_2D);

		//  Set specular color to white
		float white[] = { 1,1,1,1 };
		float black[] = { 0,0,0,1 };
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z);
		glRotated(th, 1, 0, 0);
		glScaled(dx, dy, dz);

		// Cylinder
		float i = 0.0;
		float j = 0.0;
		float ph = 0.0;
		int d = 10;
		glColor3ub(r, g, b);

		// Tube
		glBindTexture(GL_TEXTURE_2D, side);
		glBegin(GL_QUAD_STRIP);
		ph = 0.0;
		while (ph <= 360) {
			i = Cos(ph);
			j = Sin(ph);
			glNormal3f(i, j, 0);
			glTexCoord2f((ph / 360.0), 0);
			glVertex3f(i, j, 1.0);
			glTexCoord2f((ph / 360.0), 1);
			glVertex3f(i, j, 0.0);
			ph += d;
		}
		glEnd();

		glBindTexture(GL_TEXTURE_2D, ends);

		// Bottom
		glNormal3f(0, 0, 1);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0, 1);
		for (ph = 0; ph <= 360; ph += d)
		{
			glTexCoord2f(0.5*Cos(ph) + 0.5, 0.5*Sin(ph) + 0.5);
			glVertex3f(i*Cos(ph), Sin(ph), i);
		}
		glEnd();

		// Top
		glNormal3f(0, 0, -1);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0, 0);
		for (ph = 360; ph >= 0; ph -= d)
		{
			glTexCoord2f(0.5*Cos(ph) + 0.5, 0.5*Sin(ph) + 0.5);
			glVertex3f(Cos(ph), Sin(ph), 0);
		}
		glEnd();

		//  End

		//  Undo transofrmations
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);

	}

	// Octagonal Disc
	static void octagonalDisc(double x, double y, double z,
		double dx, double dy, double dz,
		double r,
		unsigned int side, unsigned int ends, bool openSided = false)
	{
		glEnable(GL_TEXTURE_2D);

		//  Set specular color to white
		float white[] = { 1,1,1,1 };
		float black[] = { 0,0,0,1 };
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z);
		glRotated(90, 1, 0, 0);
		glRotated(22.5, 0, 0, 1);
		glScaled(dx, dz, dy);

		// Disc
		float i = 0.0;
		float j = 0.0;
		float ph = 0.0;
		int d = 45;
		int limit = 360;
		if (openSided)
		{
			limit -= d;
		}
		glColor3ub(255, 0, 255);

		// Outside
		glBindTexture(GL_TEXTURE_2D, side);
		glBegin(GL_QUAD_STRIP);
		ph = 0.0;
		while (ph <= limit) {
			i = Cos(ph);
			j = Sin(ph);
			glNormal3f(i, j, 0);
			glTexCoord2f((ph / 360.0), 0);
			glVertex3f(i, j, 1.0);
			glTexCoord2f((ph / 360.0), 1);
			glVertex3f(i, j, 0.0);
			ph += d;
		}
		glEnd();

		// Inside
		ph -= d;
		glBegin(GL_QUAD_STRIP);
		while (ph >= 0) {
			i = r*Cos(ph);
			j = r*Sin(ph);
			glNormal3f(-i, -j, 0);
			glTexCoord2f((ph / 360.0), 0);
			glVertex3f(i, j, 1.0);
			glTexCoord2f((ph / 360.0), 1);
			glVertex3f(i, j, 0.0);
			ph -= d;
		}
		glEnd();

		glBindTexture(GL_TEXTURE_2D, ends);

		// Bottom
		glNormal3f(0, 0, 1);
		glBegin(GL_QUADS);
		for (ph = 0; ph <= limit; ph += d)
		{
			glTexCoord2f((r/2)*Cos(ph) + (r/2), (r/2)*Sin(ph) + (r/2));
			glVertex3f(r*Cos(ph), r*Sin(ph), 1);

			glTexCoord2f(0.5*Cos(ph) + 0.5, 0.5*Sin(ph) + 0.5);
			glVertex3f(Cos(ph), Sin(ph), 1);

			glTexCoord2f(0.5*Cos(ph + d) + 0.5, 0.5*Sin(ph + d) + 0.5);
			glVertex3f(Cos(ph + d), Sin(ph + d), 1);

			glTexCoord2f((r / 2)*Cos(ph + d) + (r / 2), (r / 2)*Sin(ph + d) + (r / 2));
			glVertex3f(r*Cos(ph + d), r*Sin(ph + d), 1);
		}
		glEnd();

		// Top
		glNormal3f(0, 0, -1);
		glBegin(GL_QUADS);
		for (ph = limit; ph >= 0; ph -= d)
		{
			glTexCoord2f((r / 2)*Cos(ph + d) + (r / 2), (r / 2)*Sin(ph + d) + (r / 2));
			glVertex3f(r*Cos(ph + d), r*Sin(ph + d), 0);

			glTexCoord2f(0.5*Cos(ph + d) + 0.5, 0.5*Sin(ph + d) + 0.5);
			glVertex3f(Cos(ph + d), Sin(ph + d), 0);

			glTexCoord2f(0.5*Cos(ph) + 0.5, 0.5*Sin(ph) + 0.5);
			glVertex3f(Cos(ph), Sin(ph), 0);

			glTexCoord2f((r / 2)*Cos(ph) + (r / 2), (r / 2)*Sin(ph) + (r / 2));
			glVertex3f(r*Cos(ph), r*Sin(ph), 0);
		}
		glEnd();

		//  End

		//  Undo transofrmations
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);

	}

	// Bent Cylinder
	static void bentCylinder(double x, double y, double z,
		double dx, double dy, double dz, double r,
		double th,
		unsigned int side)
	{
		glEnable(GL_TEXTURE_2D);

		//  Set specular color to white
		float white[] = { 1,1,1,1 };
		float black[] = { 0,0,0,1 };
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z);
		glRotated(90, 1, 0, 0);
		glRotated(90, 0, 1, 0);
		glRotated(th, 0, 0, 1);
		glScaled(dx, dy, dz);

		// Disc
		float i = 0.0;
		float j = 0.0;
		int d = 36;
		glColor3ub(255, 0, 255);

		// Pipe
		glBindTexture(GL_TEXTURE_2D, side);
		glBegin(GL_QUADS);
		for (i = 0; i < d; i++)
		{
			float th0 = i * 90.0 / d;
			float th1 = (i + 1)*90.0 / d;
			//  Loop around ring
			for (j = 0; j < d; j++)
			{
				float ph0 = j * 360.0 / d;
				float ph1 = (j + 1)*360.0 / d;
				glNormal3d(Cos(th1)*Cos(ph0), -Sin(th1)*Cos(ph0), Sin(ph0)); glTexCoord2d(th1 / 30.0, ph0 / 180.0); glVertex3d(Cos(th1)*(1 + r * Cos(ph0)), -Sin(th1)*(1 + r * Cos(ph0)), r*Sin(ph0));
				glNormal3d(Cos(th0)*Cos(ph0), -Sin(th0)*Cos(ph0), Sin(ph0)); glTexCoord2d(th0 / 30.0, ph0 / 180.0); glVertex3d(Cos(th0)*(1 + r * Cos(ph0)), -Sin(th0)*(1 + r * Cos(ph0)), r*Sin(ph0));
				glNormal3d(Cos(th0)*Cos(ph1), -Sin(th0)*Cos(ph1), Sin(ph1)); glTexCoord2d(th0 / 30.0, ph1 / 180.0); glVertex3d(Cos(th0)*(1 + r * Cos(ph1)), -Sin(th0)*(1 + r * Cos(ph1)), r*Sin(ph1));
				glNormal3d(Cos(th1)*Cos(ph1), -Sin(th1)*Cos(ph1), Sin(ph1)); glTexCoord2d(th1 / 30.0, ph1 / 180.0); glVertex3d(Cos(th1)*(1 + r * Cos(ph1)), -Sin(th1)*(1 + r * Cos(ph1)), r*Sin(ph1));
			}
		}
		glEnd();

		//  Undo transofrmations
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	}

	/*
	 *  Draw a barrel
	 *     at (x,y,z)
	 */
	static void barrel(double x, double y, double z)
	{
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z);

		shiny = 128;

		// Bottom
		cylinder(0, .2, 0, 1, 1, .2, 90, 255, 255, 255, barrelSide, barrelEnd);
		// First Layer 
		cylinder(0, 1.2, 0, .9, .9, 1, 90, 255, 255, 255, barrelSide, barrelEnd);
		// Middle
		cylinder(0, 1.4, 0, 1, 1, 0.2, 90, 255, 255, 255, barrelSide, barrelEnd);
		//Second Layer
		cylinder(0, 2.4, 0, .9, .9, 1, 90, 255, 255, 255, barrelSide, barrelEnd);
		// Top
		cylinder(0, 2.6, 0, 1, 1, 0.2, 90, 255, 255, 255, barrelSide, barrelEnd);

		shiny = 10;

		//  Undo transofrmations
		glPopMatrix();
	}

	/*
	 *  Draw a crate
	 *     at (x,y,z)
	 *     dimensions (dx,dy,dz)
	 *     rotated th about the y axis
	 */
	static void crate(double x, double y, double z,
		double dx, double dy, double dz,
		double th)
	{
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y + (1.1 * dy), z);
		glRotated(th, 0, 1, 0);
		glScaled(dx, dy, dz);

		// Box
		cube(0, 0, 0, 1, 1, 1, 0, 153, 102, 0, wood);

		// Top Frame
		cube(1, 1.05, 0, .1, .1, 1.1, 0, 102, 51, 0, wood);
		cube(-1, 1.05, 0, .1, .1, 1.1, 0, 102, 51, 0, wood);
		cube(0, 1.05, 1, .1, .1, 1, 90, 102, 51, 0, wood);
		cube(0, 1.05, -1, .1, .1, 1, 90, 102, 51, 0, wood);

		// Bottom Frame
		cube(1, -1.05, 0, .1, .1, 1.1, 0, 102, 51, 0, wood);
		cube(-1, -1.05, 0, .1, .1, 1.1, 0, 102, 51, 0, wood);
		cube(0, -1.05, 1, .1, .1, 1, 90, 102, 51, 0, wood);
		cube(0, -1.05, -1, .1, .1, 1, 90, 102, 51, 0, wood);

		// Front Frame
		cube(1, 0, 1, .1, 1, .1, 0, 102, 51, 0, wood);
		cube(1, 0, 0, .1, 1, .1, 0, 102, 51, 0, wood);
		cube(1, 0, -1, .1, 1, .1, 0, 102, 51, 0, wood);
		cube(0, 0, 1, .1, 1, .1, 0, 102, 51, 0, wood);

		// Back Frame
		cube(-1, 0, 1, .1, 1, .1, 0, 102, 51, 0, wood);
		cube(-1, 0, 0, .1, 1, .1, 0, 102, 51, 0, wood);
		cube(-1, 0, -1, .1, 1, .1, 0, 102, 51, 0, wood);
		cube(0, 0, -1, .1, 1, .1, 0, 102, 51, 0, wood);

		//  Undo transofrmations
		glPopMatrix();
	}

	/*
	 *  Draw a cone
	 *     at (x,y,z)
	 *     dimensions (dx,dy,dz)
	 */
	static void cone(double x, double y, double z,
		double dx, double dy, double dz,
		unsigned int texture)
	{
		glEnable(GL_TEXTURE_2D);

		//  Set specular color to white
		float white[] = { 1,1,1,1 };
		float black[] = { 0,0,0,1 };
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y + (1.1 * dy), z);
		glScaled(dx, dy, dz);

		float ph = 0.0;
		int d = 5;
		glColor3ub(255, 255, 255);

		// Cone
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_TRIANGLE_STRIP);
		ph = 0.0;
		while (ph < 360) {
			glNormal3f(Cos(ph), Cos(45), Sin(ph));
			glTexCoord2f(0.5, 0.5);
			glVertex3f(0, 1, 0);
			glTexCoord2f(0.5*Cos(ph) + 0.5, 0.5*Sin(ph) + 0.5);
			glVertex3f(Cos(ph), 0, Sin(ph));
			glNormal3f(Cos(ph + d), Cos(45), Sin(ph + d));
			glTexCoord2f(0.5*Cos(ph + d) + 0.5, 0.5*Sin(ph + d) + 0.5);
			glVertex3f(Cos(ph + d), 0, Sin(ph + d));
			ph += d;
		}
		glEnd();

		//  Undo transofrmations
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	}

	/*
	 *  Draw a rocket
	 *     at (x,y,z)
	 *     dimensions (dx,dy,dz)
	 *     rotated th about the x axis, ph around z
	 */
	static void rocket(double x, double y, double z,
		double dx, double dy, double dz,
		double th, double ph)
	{

		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z);
		glRotated(th, 1, 0, 0);
		glRotated(ph, 0, 0, 1);
		glScaled(dx, dy, dz);

		// Nose Cone
		cone(0, 0, 0, 1, 2, 1, noseCone);

		// Body
		cylinder(0, 2.2, 0, 1, 1, 7, 90, 150, 150, 150, rocketBody, 0);

		// Fins
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, boltedMetal);
		glBegin(GL_TRIANGLES);

		//Fin 1
		glColor3ub(255, 255, 255);
		//Inside
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3d(0, -4.75, 0);
		glTexCoord2f(1, 0);
		glVertex3d(0, -4.75, 3);
		glTexCoord2f(1, 1);
		glVertex3d(0, 0, 0);
		//Outside
		glNormal3f(1, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3d(0, 0, 0);
		glTexCoord2f(1, 1);
		glVertex3d(0, -4.75, 3);
		glTexCoord2f(0, 1);
		glVertex3d(0, -4.75, 0);

		//Fin 2
		//Inside
		glNormal3f(1, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3d(0, -4.75, 0);
		glTexCoord2f(1, 1);
		glVertex3d(0, -4.75, -3);
		glTexCoord2f(0, 0);
		glVertex3d(0, 0, 0);
		//Outside
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3d(0, 0, 0);
		glTexCoord2f(1, 1);
		glVertex3d(0, -4.75, -3);
		glTexCoord2f(0, 1);
		glVertex3d(0, -4.75, 0);

		//Fin 3
		//Inside
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 1);
		glVertex3d(0, -4.75, 0);
		glTexCoord2f(1, 1);
		glVertex3d(3, -4.75, 0);
		glTexCoord2f(0, 0);
		glVertex3d(0, 0, 0);
		//Outside
		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 0);
		glVertex3d(0, 0, 0);
		glTexCoord2f(1, 1);
		glVertex3d(3, -4.75, 0);
		glTexCoord2f(0, 1);
		glVertex3d(0, -4.75, 0);

		//Fin 4
		//Inside
		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 1);
		glVertex3d(0, -4.75, 0);
		glTexCoord2f(1, 1);
		glVertex3d(-3, -4.75, 0);
		glTexCoord2f(0, 0);
		glVertex3d(0, 0, 0);
		//Outside
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 0);
		glVertex3d(0, 0, 0);
		glTexCoord2f(1, 1);
		glVertex3d(-3, -4.75, 0);
		glTexCoord2f(0, 1);
		glVertex3d(0, -4.75, 0);

		//End
		glEnd();

		//  Undo transofrmations
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	}

	// Office Windowed Walls
	static void officeWall(double x, double y, double z)
	{
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z - 7);
		glScaled(0.5, 0.5, 0.5);

		// Wall
		cube(0, 8, 0, .5, 8, 5, 0, 0, 0, 0, wall2);
		cube(0, 8, 30, .5, 8, 5, 0, 0, 0, 0, wall2);
		cube(0, 1, 15, .5, 1, 10, 0, 0, 0, 0, wall2);
		cube(0, 15, 15, .5, 1, 10, 0, 0, 0, 0, wall2);

		// Window Frame
		cube(0, 4, 15, .6, .11, 10, 0, 0, 0, 0, boltedMetal);
		cube(0, 12, 15, .6, .11, 10, 0, 0, 0, 0, boltedMetal);
		cube(0, 8, 7.5, .6, 6, .1, 0, 0, 0, 0, boltedMetal);
		cube(0, 8, 22.5, .6, 6, .1, 0, 0, 0, 0, boltedMetal);

		// Window
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		cube(0, 8, 15, .5, 6, 10, 0, 0, 0, 0, glass);
		glDisable(GL_BLEND);

		//  Undo transofrmations
		glPopMatrix();
	}

	// Desk
	static void desk(double x, double y, double z)
	{
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z);
		glScaled(.5, .75, .75);

		// Table
		cube(0, 0, 0, 2.5, .1, 4, 0, 0, 0, 0, darkWood);

		// Front Panel
		cube(-2.4, -.6, 0, .1, .5, 4, 0, 0, 0, 0, darkWood);

		// Legs
		cube(2, -1.5, -3, .15, 1.5, .15, 0, 0, 0, 0, boltedMetal);
		cube(-2, -1.5, -3, .15, 1.5, .15, 0, 0, 0, 0, boltedMetal);
		cube(2, -1.5, 3, .15, 1.5, .15, 0, 0, 0, 0, boltedMetal);
		cube(-2, -1.5, 3, .15, 1.5, .15, 0, 0, 0, 0, boltedMetal);


		//  Undo transofrmations
		glPopMatrix();
	}

	// Warning light
	static void warningLight(double x, double y, double z, double th)
	{
		glEnable(GL_TEXTURE_2D);

		//  Set specular color to white
		float red[] = { 80,0,0,1 };
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, red);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, red);
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z);
		glScaled(.3, .25, .4);
		glRotated(th, 0, 1, 0);

		// Cylinder
		float i = 0.0;
		float j = 0.0;
		float ph = 0.0;
		int d = 10;
		glColor3ub(255, 255, 255);

		// Tube
		glBindTexture(GL_TEXTURE_2D, reflector);
		glBegin(GL_QUAD_STRIP);
		ph = 0.0;
		while (ph <= 360) {
			i = Cos(ph);
			j = Sin(ph);
			glNormal3f(i, j, 0);
			glTexCoord2f((ph / 360.0), 0);
			glVertex3f(i * .75, j * .75, 1.0);
			glTexCoord2f((ph / 360.0), 1);
			glVertex3f(i, j, 0.0);
			ph += d;
		}
		glEnd();

		// Top
		glNormal3f(0, 0, 1);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0, 1);
		for (ph = 0; ph <= 360; ph += d)
		{
			glTexCoord2f(0.5*Cos(ph) + 0.5, 0.5*Sin(ph) + 0.5);
			glVertex3f(.75 * Cos(ph), .75 * Sin(ph), i);
		}
		glEnd();

		glBindTexture(GL_TEXTURE_2D, plastic);

		// Lower tube
		glBegin(GL_QUAD_STRIP);
		ph = 0.0;
		while (ph <= 360) {
			i = Cos(ph);
			j = Sin(ph);
			glNormal3f(i, j, 1);
			glTexCoord2f((ph / 360.0), 0);
			glVertex3f(i, j, 0.0);
			glTexCoord2f((ph / 360.0), 1);
			glVertex3f(i, j, -.6);
			ph += d;
		}
		glEnd();

		// Bottom
		glNormal3f(0, 0, -1);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0, 0);
		for (ph = 360; ph >= 0; ph -= d)
		{
			glTexCoord2f(0.5*Cos(ph) + 0.5, 0.5*Sin(ph) + 0.5);
			glVertex3f(Cos(ph), Sin(ph), -.6);
		}
		glEnd();

		//  End

		//  Undo transofrmations
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	}

	/*
	 *  Draw a warehouse
	 *     at (x,y,z)
	 */
	static void warehouse(double x, double y, double z)
	{
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z);
		glRotated(180, 0, 1, 0);

		// Floor
		cube(0, -.6, 0, 11, .6, 11, 0, 255, 255, 255, concrete);

		// Back Wall
		cube(0, 9.9, -9.49, 9.9, 10, .5, 0, 152, 101, 0, wall);
		cube(0, 9.9, 9.49, 9.9, 10, .5, 0, 152, 101, 0, wall);

		// Left Wall
		cube(-9.5, 10, -7, .49, 10, 3, 0, 255, 255, 255, wall);
		cube(-9.5, 10, 7, .49, 10, 3, 0, 255, 255, 255, wall);
		cube(-9.5, 3, 0, .49, 3, 4, 0, 255, 255, 255, wall);
		cube(-9.5, 17, 0, .49, 3, 4, 0, 255, 255, 255, wall);

		// Barrels
		barrel(0, 0, 0);
		barrel(1, 2.6, 0);
		barrel(2, 0, 0);
		barrel(8, 0, -8);
		barrel(-8, 0, 8);

		// Crates
		crate(6, 0, -3, 1, 1, 1, 45);
		crate(-3, 0, -4, 2, 2, 2, 10);
		crate(3, 0, -6, 3, 1, 1, 0);
		crate(1, 2.1, -6, .5, .5, .5, 20);
		crate(-8, 0, 9.3, .2, .2, .2, 45);

		// Rockets
		rocket(5, 4.5, 5, 1, 1, 1, 0, 0);
		rocket(8, .4, -6.5, .2, .1, .2, 0, 0);
		rocket(4, 2.3, -6, .2, .2, .2, 90, 45);
		rocket(-8, 2.3, -8, .3, .6, .3, 0, 0);
		rocket(-8, .2, -6, .2, .3, .2, 90, 45);
		rocket(-7.5, .5, -6, .2, .3, .2, 0, 80);

		// Window
		//Frame
		cube(-9.5, 10, 0, .7, 4, .1, 0, 100, 100, 100, 0);
		cube(-9.5, 10, 0, .7, .1, 4, 0, 100, 100, 100, 0);
		cube(-8.9, 6, 0, .4, .1, 4, 0, 150, 51, 3, 0);

		//Glass
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		cube(-9.5, 10, 0, .5, 4, 4, 0, 100, 100, 200, glass);
		glDisable(GL_BLEND);

		//  Undo transofrmations
		glPopMatrix();
	}

	// Guard Rail
	static void guardRail(double x, double y, double z, double th)
	{
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z);
		glRotated(th, 0, 1, 0);

		bentCylinder(0, 0, 0, 1, 1, 1, .15, 0, boltedMetal);
		bentCylinder(0, 0, 1, 1, 1, 1, .15, 90, boltedMetal);
		cylinder(0, 0, -1, .15, .15, 1, 90, 255, 0, 255, boltedMetal, 0);
		cylinder(0, 0, 2, .15, .15, 1, 90, 255, 0, 255, boltedMetal, 0);
		cylinder(0, 1, 0, .15, .15, 1, 0, 255, 0, 255, boltedMetal, 0);

		//  Undo transofrmations
		glPopMatrix();
	}

	// Launch Room
	static void launchRoom(double x, double y, double z)
	{
		//  Save transformation
		glPushMatrix();
		//  Offset
		glTranslated(x, y, z);

		octagonalDisc(0, 0, 0, 15, 10, 15, .6, concrete, concrete);
		octagonalDisc(0, 8, 0, 15, 8, 15, .9, concrete, concrete, true);
		octagonalDisc(0, -10, 0, 15, .25, 15, 0, concrete, concrete);
		octagonalDisc(0, 58, 0, 15, 50, 15, .6, concrete, concrete);

		rocket(0, 4, 0, 4, 4, 4, 0, 0);

		//  Undo transofrmations
		glPopMatrix();
	}
};