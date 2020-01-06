/*
	4229 Final Project

	John Osborne

	WASD - Move Player
	Arrow Keys - Change Look Angle
	n/N - enable/disable collision detection
	Shift W - Sprint Forward
*/

#include "CSCIx229.h"
#include "Player.h"
#include "Level.h"
#include "basicShapes.h"

#define Tan(th) tan(3.1415926/180*(th))

int lightMove = 1;       // Move light
int fov = 55;       //  Field of view (for perspective)
double asp = 1;     //  Aspect ratio
double dim = 13.0;   //  Size of world

// Light values
int lightDistance = 5;  // Light distance
float inc = 0.1;  // Ball increment
int local = 0;  // Local Viewer Model
int emission = 0;  // Emission intensity (%)
int ambient = 20;  // Ambient intensity (%)
int diffuse = 100;  // Diffuse intensity (%)
int specular = 0;  // Specular intensity (%)
int shininess = 0;  // Shininess (power of two)
int zh = 90;  // Light azimuth
float ylight = 1;  // Elevation of light
float sco = 5;    //  Spot cutoff angle
float hazardsco = 45;    //  Spot cutoff angle
float Exp = 2;      //  Spot exponent
int at0 = 50;      //  Constant  attenuation %
int at1 = 15;        //  Linear    attenuation %
int at2 = 1;        //  Quadratic attenuation %

// Load Shader
int shader;
int hazard;

// Flashlight Model
int obj;

//Create Level
Level l = Level();
//Player
Player p = Player(&l, -10, 0, 0, 3);


class Display {
public:
	// Load Stuff
	static void init()
	{
		basicShapes::loadBasicTex();
		shader = CreateShaderProg("pixlight.vert", "pixlight.frag");
		hazard = CreateShaderProg("hazard.vert", "hazard.frag");
		obj = LoadOBJ("flashlight.obj");
	}

	/*
	 *  Read text file
	 */
	static char* ReadText(char *file)
	{
		int   n;
		char* buffer;
		//  Open file
		FILE* f = fopen(file, "rt");
		if (!f) Fatal("Cannot open text file %s\n", file);
		//  Seek to end to determine size, then rewind
		fseek(f, 0, SEEK_END);
		n = ftell(f);
		rewind(f);
		//  Allocate memory for the whole file
		buffer = (char*)malloc(n + 1);
		if (!buffer) Fatal("Cannot allocate %d bytes for text file %s\n", n + 1, file);
		//  Snarf the file
		if (fread(buffer, n, 1, f) != 1) Fatal("Cannot read %d bytes for text file %s\n", n, file);
		buffer[n] = 0;
		//  Close and return
		fclose(f);
		return buffer;
	}

	/*
	 *  Print Shader Log
	 */
	static void PrintShaderLog(int obj, char* file)
	{
		int len = 0;
		glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &len);
		if (len > 1)
		{
			int n = 0;
			char* buffer = (char *)malloc(len);
			if (!buffer) Fatal("Cannot allocate %d bytes of text for shader log\n", len);
			glGetShaderInfoLog(obj, len, &n, buffer);
			fprintf(stderr, "%s:\n%s\n", file, buffer);
			free(buffer);
		}
		glGetShaderiv(obj, GL_COMPILE_STATUS, &len);
		if (!len) Fatal("Error compiling %s\n", file);
	}

	/*
	 *  Print Program Log
	 */
	static void PrintProgramLog(int obj)
	{
		int len = 0;
		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &len);
		if (len > 1)
		{
			int n = 0;
			char* buffer = (char *)malloc(len);
			if (!buffer) Fatal("Cannot allocate %d bytes of text for program log\n", len);
			glGetProgramInfoLog(obj, len, &n, buffer);
			fprintf(stderr, "%s\n", buffer);
		}
		glGetProgramiv(obj, GL_LINK_STATUS, &len);
		if (!len) Fatal("Error linking program\n");
	}

	/*
	 *  Create Shader
	 */
	static int CreateShader(GLenum type, char* file)
	{
		//  Create the shader
		int shader = glCreateShader(type);
		//  Load source code from file
		char* source = ReadText(file);
		glShaderSource(shader, 1, (const char**)&source, NULL);
		free(source);
		//  Compile the shader
		fprintf(stderr, "Compile %s\n", file);
		glCompileShader(shader);
		//  Check for errors
		PrintShaderLog(shader, file);
		//  Return name
		return shader;
	}

	/*
	 *  Create Shader Program
	 */
	static int CreateShaderProg(char* VertFile, char* FragFile)
	{
		//  Create program
		int prog = glCreateProgram();
		//  Create and compile vertex shader
		int vert = CreateShader(GL_VERTEX_SHADER, VertFile);
		//  Create and compile fragment shader
		int frag = CreateShader(GL_FRAGMENT_SHADER, FragFile);
		//  Attach vertex shader
		glAttachShader(prog, vert);
		//  Attach fragment shader
		glAttachShader(prog, frag);
		//  Link program
		glLinkProgram(prog);
		//  Check for errors
		PrintProgramLog(prog);
		//  Return name
		return prog;
	}

	/*
	 *  OpenGL (GLUT) calls this routine to display the scene
	 */
	static void display()
	{
		//  Erase the window and the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//  Enable Z-buffering in OpenGL
		glEnable(GL_DEPTH_TEST);

		// Enable face culling to prevent z fighting on infinitely thin surfaces
		glEnable(GL_CULL_FACE);

		//  Undo previous transformations
		glLoadIdentity();

		//  Get Player Position
		double pX = p.getX();
		double pY = p.getY() + p.getHeight();
		double pZ = p.getZ();
		double ph = p.getPh();
		double th = p.getTh();

		// Flashlight Postition
		double flashlightX = pX + 2 * Cos(th + 30);
		double flashlightY = pY - (p.getHeight() / 3);
		double flashlightZ = pZ + 2 * Sin(th + 30);

		// Set eye position
		gluLookAt(pX, pY, pZ, pX + Cos(th), pY + Tan(ph), pZ + Sin(th), 0, 1, 0);
		//  Flat or smooth shading
		glShadeModel(GL_SMOOTH);

		//  Light switch
		//  Translate intensity to color vectors
		float Ambient[] = { 0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0 };
		float Diffuse[] = { 0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0 };
		float Specular[] = { 0.01*specular,0.01*specular,0.01*specular,1.0 };
		//  Light position
		float hazardPosition[] = { 20, 5, .25, 1.0 };
		float hazardDirection[] = { 0, Tan(zh), Sin(90), 0 };
		//Flashlight Position/Direction (added values to make to light come from the players hand)
		float Position[] = { flashlightX, flashlightY, flashlightZ,1.0 };
		float Direction[] = { Cos(th), Tan(ph), Sin(th),0 };	
		//  OpenGL should normalize normal vectors
		glEnable(GL_NORMALIZE);
		//  Enable lighting
		glEnable(GL_LIGHTING);
		//  Location of viewer for specular calculations
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, local);
		//  glColor sets ambient and diffuse color materials
		glColor3f(1, 1, 1);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);

		//  Enable light 0 | Flashlight
		glEnable(GL_LIGHT0);
		//  Set ambient, diffuse, specular components and position of light 0
		glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
		glLightfv(GL_LIGHT0, GL_POSITION, Position);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Direction);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, sco);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, Exp);
		//  Set attenuation
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, at0 / 100.0);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, at1 / 100.0);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, at2 / 100.0);

		//  Enable light 1 | Hazard Light
		glEnable(GL_LIGHT1);
		//  Set ambient, diffuse, specular components and position of light 0
		glLightfv(GL_LIGHT1, GL_AMBIENT, Ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, Specular);
		glLightfv(GL_LIGHT1, GL_POSITION, hazardPosition);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, hazardDirection);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, hazardsco);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Exp);
		//  Set attenuation
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, at0 / 100.0);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, at1 / 100.0);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, at2 / 100.0);

		//  Draw Exterior Scene
		glUseProgram(hazard);
		basicShapes::warehouse(11, 0, 0);
		basicShapes::warningLight(20, 5, .25, 90);

		// Draw Level
		glUseProgram(shader);
		l.draw();

		// Draw Flashlight
		glPushMatrix();
		glTranslated(flashlightX, flashlightY, flashlightZ);
		glScaled(.075, .075, .075);
		glRotated(-th, 0, 1, 0);
		glRotated(ph, 0, 0, 1);
		glCallList(obj);
		glPopMatrix();

		//  Render the scene and make it visible
		ErrCheck("display");
		glFlush();
		glutSwapBuffers();
	}

	/*
	 *  GLUT calls this routine when the window is resized
	 */
	static void idle()
	{
		//  Elapsed time in seconds
		double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
		zh = fmod(90 * t, 360.0);
		//  Tell GLUT it is necessary to redisplay the scene
		glutPostRedisplay();
	}

	/*
	 *  GLUT calls this routine when an arrow key is pressed
	 */
	static void special(int key, int x, int y)
	{
		//  Right arrow key - increase angle by 5 degrees
		if (key == GLUT_KEY_RIGHT)
			p.stepTh(5);
		//  Left arrow key - decrease angle by 5 degrees
		else if (key == GLUT_KEY_LEFT)
			p.stepTh(-5);
		//  Up arrow key - increase elevation by 5 degrees
		else if (key == GLUT_KEY_UP)
			p.stepPh(5);
		//  Down arrow key - decrease elevation by 5 degrees
		else if (key == GLUT_KEY_DOWN)
			p.stepPh(-5);
		//  Update projection
		Project(fov, asp, dim);
		//  Tell GLUT it is necessary to redisplay the scene
		glutPostRedisplay();
	}

	/*
	 *  GLUT calls this routine when a key is pressed
	 */
	static void key(unsigned char ch, int x, int y)
	{
		//  Exit on ESC
		if (ch == 27)
			exit(0);
		//Move Character
		// Move Forward
		else if (ch == 'w')
		{
			p.step(1, 0);
		}
		// Move Backwards
		else if (ch == 's' || ch == 'S')
		{
			p.step(1, 180);
		}
		// Strafe Left
		else if (ch == 'a' || ch == 'A')
		{
			p.step(1, -90);
		}
		// Strafe Right
		else if (ch == 'd' || ch == 'D')
		{
			p.step(1, 90);
		}
		// Sprint Forward
		else if (ch == 'W')
		{
			p.step(2, 0);
		}
		// Enable/Disable collision detection
		else if (ch == 'n' || ch == 'N')
		{
			p.setNoClip();
		}
		//  Reproject
		Project(fov, asp, dim);
		//  Animate if requested
		glutIdleFunc(lightMove ? idle : NULL);
		//  Tell GLUT it is necessary to redisplay the scene
		glutPostRedisplay();
	}

	/*
	 *  GLUT calls this routine when the window is resized
	 */
	static void reshape(int width, int height)
	{
		//  Ratio of the width to the height of the window
		asp = (height > 0) ? (double)width / height : 1;
		//  Set the viewport to the entire window
		glViewport(0, 0, width, height);
		//  Set projection
		Project(fov, asp, dim);
	}


};