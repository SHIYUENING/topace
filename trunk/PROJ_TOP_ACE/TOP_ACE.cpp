/**************************************
*                                     *
*   Jeff Molofee's Basecode Example   *
*          nehe.gamedev.net           *
*                2001                 *
*                                     *
*    All Code / Tutorial Commenting   *
*       by Jeff Molofee ( NeHe )      *
*                                     *
**************************************/

#include <windows.h>											// Header File For Windows
#include <gl\glew.h>												// Header File For The OpenGL32 Library
#include "System.h"												// Header File For NeHeGL
#include <math.h>												// We'll Need Some Math

// ROACH

#include "arb_multisample.h"
bool domulti = true;
bool doangle = true;
bool domultiR = true;
bool doangleR = true;
float moveZ=0.0f;
float moveY=0.0f;
float moveX=0.0f;
// ENDROACH



#ifndef CDS_FULLSCREEN											// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4										// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors

GL_Window*	g_window;
Keys*		g_keys;




BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
{
	g_window	= window;
	g_keys		= keys;

	// Start Of User Initialization

	glViewport(0 , 0,window->init.width ,window->init.height);	// Set Up A Viewport
	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glLoadIdentity();											// Reset The Projection Matrix
	gluPerspective(45, (float)window->init.width/(float)window->init.height, 5.0,  1000.0); // Set Our Perspective
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	glLoadIdentity();											// Reset The Modelview Matrix

	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing

	glShadeModel(GL_SMOOTH);									// Select Smooth Shading

	glClearColor(0.0f, 0.0f, 0.0f, 0.5);						// Set The Clear Color To Black

	return TRUE;												// Return TRUE (Initialization Successful)
}

void Deinitialize (void)										// Any User DeInitialization Goes Here
{

}

void KeyUpdate ()								// Perform Motion Updates Here
{
	// ROACH
	if(g_keys->keyDown [VK_SPACE] == TRUE)
		domulti=!domulti;

	if(g_keys->keyDown ['M'] == TRUE)
		doangle=!doangle;
	// ENDROACH

	if (g_keys->keyDown [VK_ESCAPE] == TRUE)					// Is ESC Being Pressed?
	{
		TerminateApplication (g_window);						// Terminate The Program
	}

	//if (g_keys->keyDown [VK_F1] == TRUE)						// Is F1 Being Pressed?
	//{
	//	ToggleFullscreen (g_window);							// Toggle Fullscreen Mode
	//}
	if(g_keys->keyDown [VK_PRIOR] == TRUE)
		moveZ=moveZ+1.0f;
	if(g_keys->keyDown [VK_NEXT] == TRUE)
		moveZ=moveZ-1.0f;

	if(g_keys->keyDown [VK_UP] == TRUE)
		moveY=moveY+1.0f;
	if(g_keys->keyDown [VK_DOWN] == TRUE)
		moveY=moveY-1.0f;


	if(g_keys->keyDown [VK_RIGHT] == TRUE)
		moveX=moveX+1.0f;
	if(g_keys->keyDown [VK_LEFT] == TRUE)
		moveX=moveX-1.0f;
}
void ExchangeData (void)
{
	domultiR=domulti;
	doangleR=doangle;
}
