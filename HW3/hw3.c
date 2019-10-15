/*
 *  Homework 3
 * 
 *  Create a scene in 3D
 *
 *  Key bindings:
 *  m          Toggle between perspective and orthogonal
 *  +/-        Changes field of view for perspective
 *  a          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#define PI 3.14
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int mode=1;       //  Projection mode
int th=-45;         //  Azimuth of view angle
int ph=15;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=15.0;   //  Size of world

//  Macro for sin & cos in degrees
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 *  Set projection
 */
static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (mode)
      gluPerspective(fov,asp,dim/4,4*dim);
   //  Orthogonal projection
   else
      glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th,
				 int r, int g, int b)
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Cube
   glBegin(GL_QUADS);
   glColor3ub(r, g, b);
   //  Front
   glVertex3f(-1,-1, 1);
   glVertex3f(+1,-1, 1);
   glVertex3f(+1,+1, 1);
   glVertex3f(-1,+1, 1);
   //  Back
   glVertex3f(+1,-1,-1);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,+1,-1);
   glVertex3f(+1,+1,-1);
   //  Right
   glVertex3f(+1,-1,+1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,+1,-1);
   glVertex3f(+1,+1,+1);
   //  Left
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,-1,+1);
   glVertex3f(-1,+1,+1);
   glVertex3f(-1,+1,-1);
   //  Top
   glVertex3f(-1,+1,+1);
   glVertex3f(+1,+1,+1);
   glVertex3f(+1,+1,-1);
   glVertex3f(-1,+1,-1);
   //  Bottom
   glVertex3f(-1,-1,-1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,-1,+1);
   glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transofrmations
   glPopMatrix();
}

void cylinder(double x, double y, double z,
	double dx, double dy, double dz,
	double th,
	int r, int g, int b) 
{
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
	int d = 15;
	glColor3ub(r, g, b);

	// Tube
	glBegin(GL_QUAD_STRIP);
	ph = 0.0;
	while (ph < 2 * PI) {
		i = cos(ph);
		j = sin(ph);
		glVertex3f(i, j, 1.0);
		glVertex3f(i, j, 0.0);
		ph += d / 360.0;
	}
	glVertex3f(1.0, 0.0, 1.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();

	// Top
	glBegin(GL_POLYGON);
	ph = 0.0;
	while (ph < 2 * PI) {
		i = cos(ph);
		j = sin(ph);
		glVertex3f(i, j, 1.0);
		ph += d / 360.0;
	}
	glVertex3f(1, 0.0, 1);
	glEnd();

	// Bottom
	glBegin(GL_POLYGON);
	ph = 0.0;
	while (ph < 2 * PI) {
		i = cos(ph);
		j = sin(ph);
		glVertex3f(i, j, 0.0);
		ph += d / 360.0;
	}
	glVertex3f(1, 0.0, 1);
	glEnd();

	//  End
	
	//  Undo transofrmations
	glPopMatrix();

}

void barrel(double x, double y, double z)
{
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);

	// Bottom
	cylinder(0, .2, 0, 1, 1, .2, 90, 200, 0, 50);
	// First Layer 
	cylinder(0, 1.2, 0, .9, .9, 1, 90, 255, 0, 0);
	// Middle
	cylinder(0, 1.4, 0, 1, 1, 0.2, 90, 200, 0, 50);
	//Second Layer
	cylinder(0, 2.4, 0, .9, .9, 1, 90, 255, 0, 0);
	// Top
	cylinder(0, 2.6, 0, 1, 1, 0.2, 90, 200, 0, 50);

	//  Undo transofrmations
	glPopMatrix();
}

void crate(double x, double y, double z,
	double dx, double dy, double dz,
	double th)
{
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y+(1.1 * dy), z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);

	// Box
	cube(0, 0, 0, 1, 1, 1, 0, 153, 102, 0);

	// Top Frame
	cube(1, 1.05, 0, .1, .1, 1.1, 0, 102, 51, 0);
	cube(-1, 1.05, 0, .1, .1, 1.1, 0, 102, 51, 0);
	cube(0, 1.05, 1, .1, .1, 1, 90, 102, 51, 0);
	cube(0, 1.05, -1, .1, .1, 1, 90, 102, 51, 0);

	// Bottom Frame
	cube(1, -1.05, 0, .1, .1, 1.1, 0, 102, 51, 0);
	cube(-1, -1.05, 0, .1, .1, 1.1, 0, 102, 51, 0);
	cube(0, -1.05, 1, .1, .1, 1, 90, 102, 51, 0);
	cube(0, -1.05, -1, .1, .1, 1, 90, 102, 51, 0);

	// Front Frame
	cube(1, 0, 1, .1, 1, .1, 0, 102, 51, 0);
	cube(1, 0, 0, .1, 1, .1, 0, 102, 51, 0);
	cube(1, 0, -1, .1, 1, .1, 0, 102, 51, 0);
	cube(0, 0, 1, .1, 1, .1, 0, 102, 51, 0);

	// Back Frame
	cube(-1, 0, 1, .1, 1, .1, 0, 102, 51, 0);
	cube(-1, 0, 0, .1, 1, .1, 0, 102, 51, 0);
	cube(-1, 0, -1, .1, 1, .1, 0, 102, 51, 0);
	cube(0, 0, -1, .1, 1, .1, 0, 102, 51, 0);

	//  Undo transofrmations
	glPopMatrix();
}

void cone(double x, double y, double z,
	double dx, double dy, double dz)
{
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y + (1.1 * dy), z);
	glScaled(dx, dy, dz);

	// Cylinder
	float i = 0.0;
	float j = 0.0;
	float ph = 0.0;
	int d = 15;
	glColor3ub(255, 0, 0);

	// Cone
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 1, 0);
	ph = 0.0;
	while (ph < 2 * PI) {
		i = cos(ph);
		j = sin(ph);
		//printf("%.3f", j);
		glVertex3f(i, 0, j);
		ph += d / 360.0;
	}
	glVertex3f(1, 0, 0);
	glEnd();

	//  Undo transofrmations
	glPopMatrix();
}

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
	cone(0, 0, 0, 1, 2, 1);

	// Body
	cylinder(0, 2.25, 0, 1, 1, 7, 90, 150, 150, 150);

	// Fins
	glColor3ub(255, 255, 255);
	glBegin(GL_POLYGON);
	glVertex3d(0, -4.75, 0);
	glVertex3d(0, -4.75, 3);
	glVertex3d(0, 0, 0);
	glEnd();
	glColor3ub(255, 255, 255);
	glBegin(GL_POLYGON);
	glVertex3d(0, -4.75, 0);
	glVertex3d(0, -4.75, -3);
	glVertex3d(0, 0, 0);
	glEnd();
	glColor3ub(0, 0, 255);
	glBegin(GL_POLYGON);
	glVertex3d(0, -4.75, 0);
	glVertex3d(3, -4.75, 0);
	glVertex3d(0, 0, 0);
	glEnd();
	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(0, -4.75, 0);
	glVertex3d(-3, -4.75, 0);
	glVertex3d(0, 0, 0);
	glEnd();

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
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }
   //  Draw scene
   // Floor
   cube(0, -.5, 0, 10, .5, 10, 0, 100, 100, 100);

   // Back Wall
   cube(0, 10, -9.5, 10, 10, .5, 0, 100, 100, 150);

   // Left Wall
   cube(-9.5, 10, -7, .5, 10, 3, 0, 100, 125, 10);
   cube(-9.5, 10, 7, .5, 10, 3, 0, 100, 125, 10);
   cube(-9.5, 3, 0, .5, 3, 4, 0, 100, 125, 10);
   cube(-9.5, 17, 0, .5, 3, 4, 0, 100, 125, 10);

   // Window
   cube(-9.5, 10, 0, .5, 4, 4, 0, 100, 100, 200);
   cube(-9.5, 10, 0, .7, 4, .1, 0, 100, 100, 100);
   cube(-9.5, 10, 0, .7, .1, 4, 0, 100, 100, 100);
   cube(-8.9, 6, 0, .4, .1, 4, 0, 150, 51, 3);

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

   //  Display parameters
   glColor3f(1, 1, 1);
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,mode?"Perpective":"Orthogonal");
   //  Render the scene and make it visible
   glFlush();
   glutSwapBuffers();
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
   else if (key == GLUT_KEY_PAGE_UP)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project();
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
   //  Switch display mode
   else if (ch == 'm' || ch == 'M')
      mode = 1-mode;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Reproject
   Project();
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
   Project();
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
   glutInitWindowSize(600,600);
   glutCreateWindow("Projections");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
