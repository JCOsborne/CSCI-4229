/*
 *  Final Project
 *
 *  Key bindings:
 *	WASD	   Move Player
 *  arrows     Change view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
#include "Display.h"

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc, char* argv[])
{
	//  Initialize GLUT
	glutInit(&argc, argv);
	//  Request double buffered, true color window with Z buffering at 600x600
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("Final");
#ifdef USEGLEW
	//  Initialize GLEW
	if (glewInit() != GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
	//  Set callback
	glutDisplayFunc(Display::display);
	glutReshapeFunc(Display::reshape);
	glutSpecialFunc(Display::special);
	glutKeyboardFunc(Display::key);
	glutIdleFunc(Display::idle);
	//Load Stuff
	Display::init();
	//  Pass control to GLUT so it can interact with the user
	ErrCheck("init");
	glutMainLoop();
	return 0;
}