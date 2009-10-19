/*
When creating your project, uncheck OWL,
uncheck Class Library, select Static
instead of Dynamic and change the target
model to Console from GUI.
Also link glut.lib to your project once its done.
*/
//#define STRICT
//#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>   // Standard Header For Most Programs
#include <GL/glew.h>
#include <GL/gl.h>     // The GL Header File
#include <GL/freeglut.h>   // The GL Utility Toolkit (Glut) Header
#include <pthread.h>
#include "tga.h"
#include "AsciiFont.h"
#include"Textures.h"
#include"Draw.h"
#include"IniFile.h"
//#include "JoyStick.h"
//#include "GamePads.h"
//#include "dinputd.h"
//#include <commctrl.h>
//#pragma comment( lib, "dinput8.lib" )	
//#pragma comment( lib, "dxguid.lib" )	
//#pragma comment( lib, "comctl32.lib" )	
#pragma comment( lib, "pthreadVC2.lib" )	
#pragma comment( lib, "glew32.lib" )	
#pragma comment( lib, "glew32d.lib" )
#ifdef _DEBUG
#pragma comment( linker, "/NODEFAULTLIB:LIBCMT.lib")
#endif
float	rtri;						// Angle For The Triangle
float	rquad;						// Angle For The Quad
int winW=800;
int winH=600;
pthread_mutex_t mutex;
struct timespec delay;
Textures * ASCFontTex = NULL;
LARGE_INTEGER t1,t2,feq,feqf,DataThread,DataThreadf;//计算每桢运行时间相关
int frameNumPs=0;
int frame=0;
char showfps[256]={0};
float turn1,turn2;
char TITLE[512]={0};
extern tGameSet GameSet;
extern tSoundSet SoundSet;
LONGLONG LLfeq;
void* DataFream(void* Param)
{
	while(true)
	{
		
		pthread_mutex_lock( &mutex );
		rtri+=0.2f;	
		rquad-=0.15f;
		pthread_mutex_unlock( &mutex );
/*	if(ispad&&ispadEffect)
	{
		g_pDevice->Acquire();

                if( g_pEffect )
                    g_pEffect->Start( 1, 0 ); // Start the effect
	}*/
	//UpdateInputState(hDlg);

		QueryPerformanceFrequency(&feqf);
		QueryPerformanceCounter(&DataThreadf);
		delay.tv_nsec=max(10000000-int((DataThreadf.QuadPart-DataThread.QuadPart)/feqf.QuadPart*1000000000.0),100);
		pthread_delay_np( &delay );
		QueryPerformanceCounter(&DataThread);
	}
	
	return NULL;
}
void InitGL ( GLvoid )     // Create Some Everyday Functions
{

	glewInit();
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable ( GL_COLOR_MATERIAL );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMatrixMode (GL_PROJECTION);										// Select The Projection Matrix
	glLoadIdentity ();													// Reset The Projection Matrix
	gluPerspective (45.0, (GLfloat)(winW)/(GLfloat)(winH),			// Calculate The Aspect Ratio Of The Window
					10.0f, 100000.0f);		
	glMatrixMode (GL_MODELVIEW);	
	
	ASCFontTex=new Textures;
	ASCFontTex->loadfile("Data/Font");
	ASCFontTex->LoadToVRAM();
	BuildFont(ASCFontTex->TexID);

	QueryPerformanceCounter(&t1);
	QueryPerformanceFrequency(&feq);//每秒跳动次数
	QueryPerformanceFrequency(&feqf);
	LLfeq=feq.QuadPart;
}

void display ( void )   // Create The Display Function
{
	QueryPerformanceFrequency(&feq);
	QueryPerformanceCounter(&t2);//测后跳动次数
	if(double((t2.QuadPart-t1.QuadPart)/feq.QuadPart)>=1.0)
	{
		QueryPerformanceCounter(&t1);//测前跳动次数
		frame=frameNumPs;
		frameNumPs=0;
		if(ASCFontTex->TexType==IS_DDS)
			sprintf(TITLE,"DDS");
		if(ASCFontTex->TexType==IS_TGA)
			sprintf(TITLE,"TGA");
		sprintf(showfps,"FPS:%d %s",frame,TITLE);
	}

	pthread_mutex_lock( &mutex );
	turn1=rtri;
	turn2=rquad;
	pthread_mutex_unlock( &mutex );

	Draw();

	glColor3f(0.0f,1.0f,0.0f);	
	glEnable( GL_TEXTURE_2D );
	glPrints(0, winH-16, winW,winH,showfps);

	glutSwapBuffers ( );
  // Swap The Buffers To Not Be Left With A Clear Screen
	frameNumPs=frameNumPs+1;
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

void isWindow()
{
	glutInitWindowPosition((GetSystemMetrics(SM_CXFULLSCREEN)-winW)/2,(GetSystemMetrics(SM_CYFULLSCREEN)-winH)/2);
	glutInitWindowSize  ( GameSet.winW, GameSet.winH );
	glutCreateWindow    ( "TEST PROJ" );
}
void isFullScreem()
{
	char GameModeString[64]={0};
	sprintf(GameModeString,"%dx%d:%d@60",GameSet.winW, GameSet.winH,GameSet.bits);
	glutGameModeString(GameModeString);
	glutEnterGameMode();
}
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	loadIniFile();

	char path[_MAX_PATH];
    GetModuleFileName(hInstance, path, _MAX_PATH);
	char* argv=(char *)path;

	glutInit            ( &nCmdShow, &argv ); // Erm Just Write It =)
	if(GameSet.AA>0)
		glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE ); // Display Mode
	else
		glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH );
	if(GameSet.AA>0)
		glutSetOption(GLUT_MULTISAMPLE,GameSet.AA);
	if(GameSet.isFullScreem)
		isFullScreem();
	else
		isWindow();
	InitGL ();
	
//	hDlg=*(HWND *) glutGetWindowData();
//	if( FAILED( InitDirectInput( hDlg ) ) )
//	{
//		MessageBox (HWND_DESKTOP, "Error DirectInput", "Error", MB_OK | MB_ICONEXCLAMATION);
	//	ispad=false;
//	}
	//if(ispad&&ispadEffect)
//	SetDeviceForcesXY();
	delay.tv_nsec=10000000;//1000000000
	delay.tv_sec=0;
    pthread_attr_t attr;
    pthread_attr_init(&attr); 
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_t reader;
	pthread_mutex_init(&mutex, NULL);
    pthread_create( &reader, &attr, DataFream,
                    NULL);
	glutDisplayFunc     ( display );  // Matching Earlier Functions To Their Counterparts
	glutReshapeFunc     ( reshape );
	glutKeyboardFunc    ( keyboard );
	glutSpecialFunc     ( arrow_keys );
	glutIdleFunc		  ( display );
	glutMainLoop        ( );          // Initialize The Main Loop
//	FreeDirectInput();


	if(ASCFontTex)
		delete ASCFontTex;
	
	return 0;
}
