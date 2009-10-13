/*
When creating your project, uncheck OWL,
uncheck Class Library, select Static
instead of Dynamic and change the target
model to Console from GUI.
Also link glut.lib to your project once its done.
*/

#include <windows.h>   // Standard Header For Most Programs
#include <GL/glew.h>
#include <GL/gl.h>     // The GL Header File
#include <GL/freeglut.h>   // The GL Utility Toolkit (Glut) Header
#include <pthread.h>
#include "dinput.h"
#include "dinputd.h"
#include <commctrl.h>
#pragma comment( lib, "dinput8.lib" )	
#pragma comment( lib, "comctl32.lib" )	
#pragma comment( lib, "pthreadVC2.lib" )	
#pragma comment( lib, "glew32.lib" )	
#pragma comment( lib, "glew32d.lib" )
float	rtri;						// Angle For The Triangle
float	rquad;						// Angle For The Quad
int winW=800;
int winH=600;
pthread_mutex_t mutex;
struct timespec delay;
IDirectInput8 *g_pDInputInterface; //dinput interface
IDirectInputDevice8 *g_pKeyboardDevice; //keyboard device
void* DataFream(void* Param)
{
	while(true)
	{
	 pthread_mutex_lock( &mutex );
   rtri+=0.2f;						// Increase The Rotation Variable For The Triangle ( NEW )
	rquad-=0.15f;						// Decrease The Rotation Variable For The Quad     ( NEW )
	pthread_mutex_unlock( &mutex );
	pthread_delay_np( &delay );
	}
	return NULL;
}
void InitGL ( GLvoid )     // Create Some Everyday Functions
{

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable ( GL_COLOR_MATERIAL );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display ( void )   // Create The Display Function
{
	float turn1,turn2;

	pthread_mutex_lock( &mutex );
	turn1=rtri;
	turn2=rquad;
	pthread_mutex_unlock( &mutex );
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
   glLoadIdentity();									// Reset The Current Modelview Matrix
   glPushMatrix();
	glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
   glRotatef(turn1,0.0f,1.0f,0.0f);				// Rotate The Triangle On The Y axis
   glEnable(GL_MULTISAMPLE_ARB);
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
		glColor3f(1.0f,0.0f,0.0f);			// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Front)
		glColor3f(0.0f,1.0f,0.0f);			// Green
		glVertex3f(-1.0f,-1.0f, 1.0f);			// Left Of Triangle (Front)
		glColor3f(0.0f,0.0f,1.0f);			// Blue
		glVertex3f( 1.0f,-1.0f, 1.0f);			// Right Of Triangle (Front)
		glColor3f(1.0f,0.0f,0.0f);			// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Right)
		glColor3f(0.0f,0.0f,1.0f);			// Blue
		glVertex3f( 1.0f,-1.0f, 1.0f);			// Left Of Triangle (Right)
		glColor3f(0.0f,1.0f,0.0f);			// Green
		glVertex3f( 1.0f,-1.0f, -1.0f);			// Right Of Triangle (Right)
      glColor3f(1.0f,0.0f,0.0f);			// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Back)
		glColor3f(0.0f,1.0f,0.0f);			// Green
		glVertex3f( 1.0f,-1.0f, -1.0f);			// Left Of Triangle (Back)
		glColor3f(0.0f,0.0f,1.0f);			// Blue
		glVertex3f(-1.0f,-1.0f, -1.0f);			// Right Of Triangle (Back)
		glColor3f(1.0f,0.0f,0.0f);			// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Left)
		glColor3f(0.0f,0.0f,1.0f);			// Blue
		glVertex3f(-1.0f,-1.0f,-1.0f);			// Left Of Triangle (Left)
		glColor3f(0.0f,1.0f,0.0f);			// Green
		glVertex3f(-1.0f,-1.0f, 1.0f);			// Right Of Triangle (Left)
    glEnd();											// Finished Drawing The Triangle
glDisable(GL_MULTISAMPLE_ARB);
	glLoadIdentity();					// Reset The Current Modelview Matrix
    glTranslatef(1.5f,0.0f,-6.0f);				// Move Right 1.5 Units And Into The Screen 6.0
	glRotatef(turn2,1.0f,0.0f,0.0f);			// Rotate The Quad On The X axis
	glColor3f(0.5f,0.5f,1.0f);							// Set The Color To Blue One Time Only
	glBegin(GL_QUADS);									// Draw A Quad
		glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Blue
		glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, 1.0f);			// Bottom Left Of The Quad (Top)
		glVertex3f( 1.0f, 1.0f, 1.0f);			// Bottom Right Of The Quad (Top)
		glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
		glVertex3f( 1.0f,-1.0f, 1.0f);			// Top Right Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f, 1.0f);			// Top Left Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Bottom)
		glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Bottom)
		glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
		glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Front)
		glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Front)
		glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Front)
		glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Front)
		glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
		glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Back)
		glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Back)
		glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Back)
		glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Back)
		glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Left)
		glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Left)
		glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
		glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Right)
		glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Right)
	glEnd();						// Done Drawing The Quad
  												// Done Drawing The Quad
  glPopMatrix();
  // rtri+=0.2f;						// Increase The Rotation Variable For The Triangle ( NEW )
	//rquad-=0.15f;						// Decrease The Rotation Variable For The Quad     ( NEW )


  glutSwapBuffers ( );
  // Swap The Buffers To Not Be Left With A Clear Screen
}

void reshape ( int width , int height )   // Create The Reshape Function (the viewport)
{
  if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
  switch ( key ) {
    case 27:        // When Escape Is Pressed...
      exit ( 0 );   // Exit The Program
      break;        // Ready For Next Case
    default:        // Now Wrap It Up
      break;
  }
}

void arrow_keys ( int a_keys, int x, int y )  // Create Special Function (required for arrow keys)
{
  switch ( a_keys ) {
    case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
      glutFullScreen ( ); // Go Into Full Screen Mode
      break;
    case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
		glutFullScreen();
		glutPositionWindow((GetSystemMetrics(SM_CXFULLSCREEN)-winW)/2,(GetSystemMetrics(SM_CYFULLSCREEN)-winH)/2);
      glutReshapeWindow ( winW, winH ); // Go Into A 500 By 500 Window
	  
      break;
    default:
      break;
  }
}


//void main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	InitCommonControls();
	char path[_MAX_PATH];
    GetModuleFileName(hInstance, path, _MAX_PATH);
	char* argv=(char *)path;
	delay.tv_nsec=10000000;
	delay.tv_sec=0;
     pthread_t pid;
     pthread_attr_t attr;
     pthread_attr_init(&attr);
     pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_t reader;
	pthread_mutex_init(&mutex, NULL);
    pthread_create( &reader, &attr, DataFream,
                    NULL);
	glutInit            ( &nCmdShow, &argv ); // Erm Just Write It =)
//	glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE ); // Display Mode
	glutInitDisplayString("rgba double depth>=24 samples alpha");
	glutSetOption(GLUT_MULTISAMPLE,2);
	glutInitWindowPosition((GetSystemMetrics(SM_CXFULLSCREEN)-winW)/2,(GetSystemMetrics(SM_CYFULLSCREEN)-winH)/2);
	glutInitWindowSize  ( winW, winH ); // If glutFullScreen wasn't called this is the window size
	glutCreateWindow    ( "TOP_ACE" ); // Window Title (argv[0] for current directory as title)
//	glutFullScreen      ( );          // Put Into Full Screen
	InitGL ();
	glutDisplayFunc     ( display );  // Matching Earlier Functions To Their Counterparts
	glutReshapeFunc     ( reshape );
	glutKeyboardFunc    ( keyboard );
	glutSpecialFunc     ( arrow_keys );
	glutIdleFunc		  ( display );
	glutMainLoop        ( );          // Initialize The Main Loop
	return 0;
}

