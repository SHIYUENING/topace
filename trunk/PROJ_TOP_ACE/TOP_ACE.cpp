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
#include "Draw.h"
// ROACH
#include "Font2D.h"
#include "arb_multisample.h"
bool domulti = true;
bool doangle = true;
bool domultiR = true;
bool doangleR = true;
// ENDROACH



#ifndef CDS_FULLSCREEN											// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4										// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors

GL_Window*	g_window;
Keys*		g_keys;

float angle= 0.0f;
CFont2D * Font2D=NULL; 

BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
{
	g_window	= window;
	g_keys		= keys;

	// Start Of User Initialization
	angle		= 0.0f;											// Set Starting Angle To Zero

	glViewport(0 , 0,window->init.width ,window->init.height);	// Set Up A Viewport
	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glLoadIdentity();											// Reset The Projection Matrix
	gluPerspective(50, (float)window->init.width/(float)window->init.height, 5,  2000); // Set Our Perspective
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	glLoadIdentity();											// Reset The Modelview Matrix

	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing

	glShadeModel(GL_SMOOTH);									// Select Smooth Shading

	glClearColor(0.0f, 0.0f, 0.0f, 0.5);						// Set The Clear Color To Black
	if(!Font2D)
	{
		char szPath[MAX_PATH];
		GetWindowsDirectory(szPath,sizeof(szPath));
		char FontPath[MAX_PATH];
		sprintf(FontPath,"%s/Fonts/simsun.ttc",szPath);
	//FontsTest.LoadFont(FontPath,16,16,128,128);
	//FontsTest.inputTxt("qwerttyyuioop[]");
		Font2D=new CFont2D;
		Font2D->LoadFont(FontPath,32,32,256,256);
		Font2D->inputTxt("a²â");
	}

	return TRUE;												// Return TRUE (Initialization Successful)
}

void Deinitialize (void)										// Any User DeInitialization Goes Here
{
}

void Update ()								// Perform Motion Updates Here
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

	if (g_keys->keyDown [VK_F1] == TRUE)						// Is F1 Being Pressed?
	{
		ToggleFullscreen (g_window);							// Toggle Fullscreen Mode
	}
}
void ExchangeData (void)
{
	domultiR=domulti;
	doangleR=doangle;
}
void Render (void)												// Draw The Scene
{
	// ROACH
	if(domulti)
		glEnable(GL_MULTISAMPLE_ARB);							// Enable Our Multisampling
	// ENDROACH

	glClearColor(0.0f, 0.0f, 0.0f, 0.5);						// Set The Clear Color To Black
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity();											// Reset The View	

	//glDisable( GL_TEXTURE_2D );
	for(float i=-10;i<10;i++)
		for(float j=-10;j<10;j++)
		{
			glPushMatrix();
			glTranslatef(i*2.0f,j*2.0f,-5.0f);
			glRotatef(angle,0.f,0.f,1.f);
				glBegin(GL_QUADS);
				glColor3f(1.0f,0.0f,0.0f);glVertex3f(i,j,0.0f);glTexCoord2d(0,0);
				glColor3f(0.0f,1.0f,0.0f);glVertex3f(i + 2.0f,j,0.0f);glTexCoord2d(1,0);
				glColor3f(0.0f,0.0f,1.0f);glVertex3f(i + 2.0f,j + 2.0f,0.0f);glTexCoord2d(1,1);
				glColor3f(1.0f,1.0f,1.0f);glVertex3f(i,j + 2.0f,0.0f);glTexCoord2d(0,1);
				glEnd();
			glPopMatrix();
		}

	
	if(doangle)
		angle+=0.05f;

	//glFlush ();													// Flush The GL Rendering Pipeline

	glEnable( GL_TEXTURE_2D );
			
	Font2D->DrawTXT(800,600,400,300,32,32,0);
	if(domulti)
	glDisable(GL_MULTISAMPLE_ARB);
	// ROACH
	

	// ENDROACH
}
