/*
 *  Homework 6
 *
 *  Implement Textures

 *
 *  Key bindings:
 *  l          Toggles lighting
 *  a/A        Decrease/increase ambient light
 *  d/D        Decrease/increase diffuse light
 *  s/S        Decrease/increase specular light
 *  e/E        Decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  F1         Toggle smooth/flat shading
 *  F2         Toggle local viewer mode
 *  F3         Toggle light distance (1/5)
 *  F8         Change ball increment
 *  F9         Invert bottom normal
 *  m          Toggles light movement
 *  []         Lower/rise light
 *  +/-        Change field of view of perspective
 *  v		   Change Display Mode
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"

int move=1;       //  Move light
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int light=1;      //  Lighting
double asp=1;     //  Aspect ratio
double dim=13.0;   //  Size of world
// Light values
int one       =   1;  // Unit value
int distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   10;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   1;  // Elevation of light
// Display
int displayMode = 0;

unsigned int barrelSide, barrelEnd, wood, concrete, wall, rocketBody, noseCone, boltedMetal;

/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
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
			glTexCoord2f((i+1)/2, 1-((j+1)/2));
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
			glVertex3f(1, j + sy, i+ sz);
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
void cylinder(double x, double y, double z,
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

/*
 *  Draw a barrel
 *     at (x,y,z)
 */
void barrel(double x, double y, double z)
{
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);

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

	//  Undo transofrmations
	glPopMatrix();
}

/*
 *  Draw a crate
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void crate(double x, double y, double z,
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
	cube2(0, 0, 0, 1, 1, 1, 0, 153, 102, 0, wood);

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
void cone(double x, double y, double z,
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
void rocket(double x, double y, double z,
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
	//glColor3ub(255, 255, 255);
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
	//glColor3ub(0, 0, 255);
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
	//glColor3ub(255, 0, 0);
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

/*
 *  Draw a warehouse
 *     at (x,y,z)
 */
void warehouse(double x, double y, double z)
{
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);

	// Floor
	cube2(0, -.6, 0, 11, .6, 11, 0, 255, 255, 255, concrete);

	// Back Wall
	cube2(0, 9.9, -9.49, 9.9, 10, .5, 0, 152, 101, 0, wall);

	// Left Wall
	cube2(-9.5, 10, -7, .49, 10, 3, 0, 255, 255, 255, wall);
	cube2(-9.5, 10, 7, .49, 10, 3, 0, 255, 255, 255, wall);
	cube2(-9.5, 3, 0, .49, 3, 4, 0, 255, 255, 255, wall);
	cube2(-9.5, 17, 0, .49, 3, 4, 0, 255, 255, 255, wall);

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
	//Glass
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	cube2(-9.5, 10, 0, .5, 4, 4, 0, 100, 100, 200, 0);
	glDisable(GL_BLEND);
	//Frame
	cube(-9.5, 10, 0, .7, 4, .1, 0, 100, 100, 100, 0);
	cube(-9.5, 10, 0, .7, .1, 4, 0, 100, 100, 100, 0);
	cube(-8.9, 6, 0, .4, .1, 4, 0, 150, 51, 3, 0);

	//  Undo transofrmations
	glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   // Enable face culling to prevent z fighting on infinitely thin surfaces
   glEnable(GL_CULL_FACE);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = +2*dim        *Sin(ph);
   double Ez = +2*dim*Cos(th)*Cos(ph);
   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);


   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light position
      float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  Location of viewer for specular calculations
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
      glDisable(GL_LIGHTING);

   //  Draw scene
   if (!displayMode)
   {
	   warehouse(0, 0, 0);
   }
   else if (displayMode == 1)
   {
	   barrel(0, 0, 0);
   }
   else if (displayMode == 2)
   {
	   crate(0, 0, 0, 1, 1, 1, 0);
   }
   else
   {
	   rocket(0, 0, 0, 1, 1, 1, 0, 0);
   }

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Smooth color model
   else if (key == GLUT_KEY_F1)
      smooth = 1-smooth;
   //  Local Viewer
   else if (key == GLUT_KEY_F2)
      local = 1-local;
   else if (key == GLUT_KEY_F3)
      distance = (distance==1) ? 5 : 1;
   //  Toggle ball increment
   else if (key == GLUT_KEY_F8)
      inc = (inc==10)?3:10;
   //  Flip sign
   else if (key == GLUT_KEY_F9)
      one = -one;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(fov,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Toggle light movement
   else if (ch == 'm' || ch == 'M')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='a' && ambient>0)
      ambient -= 5;
   else if (ch=='A' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   // Display mode
   else if (ch == 'v')
   {
	   if (displayMode < 3)
	   {
		   displayMode++;
	   }
	   else
	   {
		   displayMode = 0;
	   }
   }
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(fov,asp,dim);
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(fov,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(400,400);
   glutCreateWindow("Lighting");
   //  Set callback s
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   barrelSide = LoadTexBMP("barrel_sb.bmp");
   barrelEnd = LoadTexBMP("barrel_end.bmp");
   wood = LoadTexBMP("wood.bmp");
   concrete = LoadTexBMP("concrete.bmp");
   wall = LoadTexBMP("wall.bmp");
   rocketBody = LoadTexBMP("rocket.bmp");
   noseCone = LoadTexBMP("noseCone.bmp");
   boltedMetal = LoadTexBMP("boltedMetal.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
