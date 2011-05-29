
#include "Draw.h"
#include <windows.h>													// Header File For The Windows Library
#include <gl/glew.h>
#include <gl/wglew.h>
#include "LockFPS.h"
#include "resource.h"
#include "System.h"														// Header File For The NeHeGL Basecode
#include "IniFile.h"
#include "DataUpdata.h"
#include "KeyInput.h"
#include "EXTLIBS.h"
#include "ExchangeThread.h"
//ROACH
#include "ARB_MULTISAMPLE.h"
#include "TALogSys.h"
#include "Common.h"
#include "GFXUI.h"
#pragma comment( lib, "glew32s.lib" )							// Search For glew32s.lib While Linking
#pragma comment( lib, "opengl32.lib" )							// Search For OpenGL32.lib While Linking
//#pragma comment( lib, "glu32.lib" )								// Search For GLu32.lib While Linking
//#pragma comment( lib, "glaux.lib" )								// Search For GLaux.lib While Linking

#ifdef _DEBUG
#pragma comment( linker, "/NODEFAULTLIB:LIBCMT.lib")
#endif
#pragma comment( linker, "/NODEFAULTLIB:LIBC.lib")
BOOL DestroyWindowGL (GL_Window* window);
BOOL CreateWindowGL (GL_Window* window);
//ENDROACH

#define WM_TOGGLEFULLSCREEN (WM_USER+1)									// Application Define Message For Toggling

static BOOL g_isProgramLooping;											// Window Creation Loop, For FullScreen/Windowed Toggle																		// Between Fullscreen / Windowed Mode
static BOOL g_createFullScreen;											// If TRUE, Then Create Fullscreen
int (__stdcall *hglSwapBuffers)(void *)=NULL;
HMODULE gl_dll=false;
HDC SwapHdc; 
double oneframetimelimit=1.0/60.0;
double oneframetime=0.0;
bool isDraw=true;
bool isRun=true;
bool RenderThreadisSuspend=false;
HANDLE RenderThreadHANDLE=NULL;

HINSTANCE hInst;
int WindowWidth=800;
int WindowHeight=600;
float moveZ=-250.0f;
float moveY=0.0f;
float moveX=0.0f;
float moveZSpeed=25.0f;
float GoX=0.0f;
float GoZ=0.0f;
HGLRC	 m_hrc;
CLockFPS LockFPSSYS,LockFPSRender;
CTALogSys MainLOG;
int TessLevel=1;
bool Gdown1=false;
bool Gdown2=false;
bool GdownSPACE=false;
bool DrawFrame=false;
extern CExchangeThread ThreadDataDraw;
BYTE nInputs=0;
unsigned int nInputsNow=0;
bool TouchInput=false;
__m128 TouchInputposs[4];
float zoomsize=0.0f;
float touchX=0.0f;
float touchY=0.0f;
float Touchang=0.0f;
float TouchangY=0.0f;
bool Touchings[4]={false,false,false,false};
extern float NoTouchMoveTimes;

extern float TouchMoveOverride;
extern float TouchZoomOverride;
int DoubleTouchTime=0;
__m128 TouchPointOrg;
int InputPos[3]={0};
CGFXUI * pGfxUI=NULL;
float framegfxtmp=0.0f;
void KeyUpdate ( Keys* g_keys,GL_Window* g_window)								// Perform Motion Updates Here
{


	if (g_keys->keyDown [VK_ESCAPE] == TRUE)					// Is ESC Being Pressed?
	{
		TerminateApplication (g_window);						// Terminate The Program
	}

	//if (g_keys->keyDown [VK_F1] == TRUE)						// Is F1 Being Pressed?
	//{
	//	ToggleFullscreen (g_window);							// Toggle Fullscreen Mode
	//}
	//if(g_keys->keyDown [VK_PRIOR] == TRUE)
	//	moveZ=moveZ+moveZSpeed;
	//if(g_keys->keyDown [VK_NEXT] == TRUE)
	//	moveZ=moveZ-moveZSpeed;
	//if(g_keys->keyDown ['W'] == TRUE) GoZ=GoZ+moveZSpeed;
	//if(g_keys->keyDown ['S'] == TRUE) GoZ=GoZ-moveZSpeed;
	//if(g_keys->keyDown ['A'] == TRUE) GoX=GoX+moveZSpeed;
	//if(g_keys->keyDown ['D'] == TRUE) GoX=GoX-moveZSpeed;
	if((g_keys->keyDown ['1'] == TRUE)&&(!Gdown1))
	{
		Gdown1=true;
		TessLevel=TessLevel-1;
	}
	if(g_keys->keyDown ['1'] != TRUE)  Gdown1=false;
	if((g_keys->keyDown ['2'] == TRUE)&&(!Gdown2))
	{
		Gdown2=true;
		TessLevel=TessLevel+1;
	}
	if(g_keys->keyDown ['2'] != TRUE)  Gdown2=false;
	TessLevel=max(1,TessLevel);
	int TessLevelMAX=64;
	glGetIntegerv(GL_MAX_TESS_GEN_LEVEL,&TessLevelMAX);
	TessLevel=min(TessLevelMAX,TessLevel);

	//if(g_keys->keyDown [VK_UP] == TRUE)
	//	moveY=moveY+2.0f;
	//if(g_keys->keyDown [VK_DOWN] == TRUE)
	//	moveY=moveY-2.0f;


	//if(g_keys->keyDown [VK_RIGHT] == TRUE)
	//	moveX=moveX+2.0f;
	//if(g_keys->keyDown [VK_LEFT] == TRUE)
	//	moveX=moveX-2.0f;
	if(g_keys->keyDown [VK_HOME] == TRUE)
	{
		GoX=GoZ=moveX=moveY=moveZ=0.0f;
	}

	if((g_keys->keyDown [VK_SPACE] == TRUE)&&(!GdownSPACE))
	{
		GdownSPACE=true;
		DrawFrame=!DrawFrame;
	}
	if(g_keys->keyDown [VK_SPACE] != TRUE)  GdownSPACE=false;
}


void TerminateApplication (GL_Window* window)							// Terminate The Application
{
	PostMessageW (window->hWnd, WM_QUIT, 0, 0);							// Send A WM_QUIT Message
	g_isProgramLooping = FALSE;											// Stop Looping Of The Program
}

void ToggleFullscreen (GL_Window* window)								// Toggle Fullscreen/Windowed
{
	PostMessageW (window->hWnd, WM_TOGGLEFULLSCREEN, 0, 0);				// Send A WM_TOGGLEFULLSCREEN Message
}

void ReshapeGL (int width, int height)									// Reshape The Window When It's Moved Or Resized
{
	GameSet.winW=WindowWidth=width;
	GameSet.winH=WindowHeight=height;
	CommonMatrixs[CO_Matrix_Proj].PerspectiveProjectionFov(45.0, (double)width/(double)height, 1.0,  12000.0);
	//CO_MatrixPerspectiveProjectionFov(45.0, (double)width/(double)height, 5.0,  100000.0); 
	//CO_SetPMatrixD(CommonMatrixs[CO_Matrix_Proj].LinkList->Matrix);
	//GLdouble PMatrix[16];
	//CO_GetPMatrixD(PMatrix);
	glViewport (0, 0, (GLsizei)(width), (GLsizei)(height));				// Reset The Current Viewport
	glMatrixMode (GL_PROJECTION);										// Select The Projection Matrix
	//glLoadIdentity ();													// Reset The Projection Matrix
	//gluPerspective(50, (float)width/(float)height, 5.0,  100000.0f);
	//glLoadMatrixd(PMatrix);
	glLoadMatrixd(CommonMatrixs[CO_Matrix_Proj].LinkList->Matrix);
	glMatrixMode (GL_MODELVIEW);										// Select The Modelview Matrix
	glLoadIdentity ();													// Reset The Modelview Matrix
}

BOOL ChangeScreenResolution (int width, int height, int bitsPerPixel)	// Change The Screen Resolution
{
	DEVMODEW dmScreenSettings;											// Device Mode
	ZeroMemory (&dmScreenSettings, sizeof (DEVMODEW));					// Make Sure Memory Is Cleared
	dmScreenSettings.dmSize				= sizeof (DEVMODEW);				// Size Of The Devmode Structure
	dmScreenSettings.dmPelsWidth		= width;						// Select Screen Width
	dmScreenSettings.dmPelsHeight		= height;						// Select Screen Height
	dmScreenSettings.dmBitsPerPel		= bitsPerPixel;					// Select Bits Per Pixel
	dmScreenSettings.dmFields			= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	if (ChangeDisplaySettingsW (&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		return FALSE;													// Display Change Failed, Return False
	}
	return TRUE;														// Display Change Was Successful, Return True
}

BOOL CreateWindowGL (GL_Window* window)									// This Code Creates Our OpenGL Window
{
	//DWORD windowStyle = WS_OVERLAPPEDWINDOW;							// Define Our Window Style
	DWORD windowStyle =		 WS_OVERLAPPED     | \
                             WS_CAPTION        | \
                             WS_SYSMENU        | \
                             WS_THICKFRAME     | \
                             WS_MINIMIZEBOX;
                             //WS_MAXIMIZEBOX;
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;						// Define The Window's Extended Style

	PIXELFORMATDESCRIPTOR pfd =											// pfd Tells Windows How We Want Things To Be
	{
		sizeof (PIXELFORMATDESCRIPTOR),									// Size Of This Pixel Format Descriptor
		1,																// Version Number
		PFD_DRAW_TO_WINDOW |											// Format Must Support Window
		PFD_SUPPORT_OPENGL |											// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,												// Must Support Double Buffering
		PFD_TYPE_RGBA,													// Request An RGBA Format
		window->init.bitsPerPixel,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,												// Color Bits Ignored
		1,																// Alpha Buffer
		0,																// Shift Bit Ignored
		0,																// No Accumulation Buffer
		0, 0, 0, 0,														// Accumulation Bits Ignored
		24,																// 16Bit Z-Buffer (Depth Buffer)  
		8,																// No Stencil Buffer
		0,																// No Auxiliary Buffer
		PFD_MAIN_PLANE,													// Main Drawing Layer
		0,																// Reserved
		0, 0, 0															// Layer Masks Ignored
	};

	RECT windowRect = {0, 0, window->init.width, window->init.height};	// Define Our Window Coordinates

	GLuint PixelFormat;													// Will Hold The Selected Pixel Format

	if (window->init.isFullScreen == TRUE)								// Fullscreen Requested, Try Changing Video Modes
	{
		if (ChangeScreenResolution (window->init.width, window->init.height, window->init.bitsPerPixel) == FALSE)
		{
			// Fullscreen Mode Failed.  Run In Windowed Mode Instead
			MessageBoxA (HWND_DESKTOP, "Mode Switch Failed.\nRunning In Windowed Mode.", "Error", MB_OK | MB_ICONEXCLAMATION);
			window->init.isFullScreen = FALSE;							// Set isFullscreen To False (Windowed Mode)
		}
		else															// Otherwise (If Fullscreen Mode Was Successful)
		{
			//ShowCursor (FALSE);											// Turn Off The Cursor
			windowStyle = WS_POPUP;										// Set The WindowStyle To WS_POPUP (Popup Window)
			windowExtendedStyle |= WS_EX_TOPMOST;						// Set The Extended Window Style To WS_EX_TOPMOST
		}																// (Top Window Covering Everything Else)
	}
	else																// If Fullscreen Was Not Selected
	{
		// Adjust Window, Account For Window Borders
		AdjustWindowRectEx (&windowRect, windowStyle, 0, windowExtendedStyle);
	}

	// Create The OpenGL Window
	int CWX=(GetSystemMetrics(SM_CXFULLSCREEN)-WindowWidth)/2;
	int CWY=(GetSystemMetrics(SM_CYFULLSCREEN)-WindowHeight)/2;
	if(GameSet.isFullScreem)
	{
		CWX=0;
		CWY=0;
	}
	window->hWnd = CreateWindowExW (windowExtendedStyle,					// Extended Style
								   window->init.application->className,	// Class Name
								   window->init.title,					// Window Title
								   windowStyle,							// Window Style
								   CWX,CWY,								// Window X,Y Position
								   windowRect.right - windowRect.left,	// Window Width
								   windowRect.bottom - windowRect.top,	// Window Height
								   HWND_DESKTOP,						// Desktop Is Window's Parent
								   0,									// No Menu
								   window->init.application->hInstance, // Pass The Window Instance
								   window);

	if (window->hWnd == 0)												// Was Window Creation A Success?
	{
		return FALSE;													// If Not Return False
	}

	window->hDC = GetDC (window->hWnd);									// Grab A Device Context For This Window
	if (window->hDC == 0)												// Did We Get A Device Context?
	{
			// Failed
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

//ROACH
	/*
	Our first pass, Multisampling hasn't been created yet, so we create a window normally
	If it is supported, then we're on our second pass
	that means we want to use our pixel format for sampling
	so set PixelFormat to arbMultiSampleformat instead
  */
	if(!arbMultisampleSupported)
	{
		PixelFormat = ChoosePixelFormat (window->hDC, &pfd);				// Find A Compatible Pixel Format
		if (PixelFormat == 0)												// Did We Find A Compatible Format?
		{
			// Failed
			ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
			window->hDC = 0;												// Zero The Device Context
			DestroyWindow (window->hWnd);									// Destroy The Window
			window->hWnd = 0;												// Zero The Window Handle
			return FALSE;													// Return False
		}

	}
	else
	{
		PixelFormat = arbMultisampleFormat;
	}
//ENDROACH

	if (SetPixelFormat (window->hDC, PixelFormat, &pfd) == FALSE)		// Try To Set The Pixel Format
	{
		// Failed
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	window->hRC = wglCreateContext (window->hDC);						// Try To Get A Rendering Context
	if (window->hRC == 0)												// Did We Get A Rendering Context?
	{
		// Failed
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	// Make The Rendering Context Our Current Rendering Context
	if (wglMakeCurrent (window->hDC, window->hRC) == FALSE)
	{
		// Failed
		wglDeleteContext (window->hRC);									// Delete The Rendering Context
		window->hRC = 0;												// Zero The Rendering Context
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

//ROACH
	/*
	Now that our window is created, we want to queary what samples are available
	we call our InitMultiSample window
	if we return a valid context, we want to destroy our current window
	and create a new one using the multisample interface.
	*/
	if(!arbMultisampleSupported && CHECK_FOR_MULTISAMPLE)
	{
	
		if(InitMultisample(window->init.application->hInstance,window->hWnd,pfd))
		{
			
			DestroyWindowGL (window);
			return CreateWindowGL(window);
		}
	}
	glewInit();

//ENDROACH

	ShowWindow (window->hWnd, SW_NORMAL);								// Make The Window Visible
	window->isVisible = TRUE;											// Set isVisible To True

	ReshapeGL (window->init.width, window->init.height);				// Reshape Our GL Window

	ZeroMemory (window->keys, sizeof (Keys));							// Clear All Keys

	window->lastTickCount = GetTickCount ();							// Get Tick Count

	return TRUE;														// Window Creating Was A Success
																		// Initialization Will Be Done In WM_CREATE
}

BOOL DestroyWindowGL (GL_Window* window)								// Destroy The OpenGL Window & Release Resources
{
	if (window->hWnd != 0)												// Does The Window Have A Handle?
	{	
		if (window->hDC != 0)											// Does The Window Have A Device Context?
		{
			wglMakeCurrent (window->hDC, 0);							// Set The Current Active Rendering Context To Zero
			if (window->hRC != 0)										// Does The Window Have A Rendering Context?
			{
				wglDeleteContext (window->hRC);							// Release The Rendering Context
				window->hRC = 0;										// Zero The Rendering Context

			}
			ReleaseDC (window->hWnd, window->hDC);						// Release The Device Context
			window->hDC = 0;											// Zero The Device Context
		}
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
	}

	if (window->init.isFullScreen)										// Is Window In Fullscreen Mode
	{
		ChangeDisplaySettingsW (NULL,0);									// Switch Back To Desktop Resolution
		ShowCursor (TRUE);												// Show The Cursor
	}	
	return TRUE;														// Return True
}
void DoDoubleTouch()
{
	float movePosTMP[2]={
	sqrt((float)Easy_vector_Getlenth_2i(
	TouchPointOrg.m128_i32[0],
	TouchInputposs[0].m128_i32[0],
	TouchPointOrg.m128_i32[1],
	TouchInputposs[0].m128_i32[1])),

	sqrt((float)Easy_vector_Getlenth_2i(
	TouchPointOrg.m128_i32[2],
	TouchInputposs[1].m128_i32[0],
	TouchPointOrg.m128_i32[3],
	TouchInputposs[1].m128_i32[1]))
	};
	if((movePosTMP[0]>3000)&&(movePosTMP[1]>3000))
	{
	zoomsize=sqrt(float(Easy_vector_Getlenth_2i(
					TouchPointOrg.m128_i32[0],
					TouchPointOrg.m128_i32[2],
					TouchPointOrg.m128_i32[1],
					TouchPointOrg.m128_i32[3]
					)))-
			sqrt(float(Easy_vector_Getlenth_2i(
					TouchInputposs[0].m128_i32[0],
					TouchInputposs[1].m128_i32[0],
					TouchInputposs[0].m128_i32[1],
					TouchInputposs[1].m128_i32[1])));
	zoomsize=zoomsize/3000.0f;
	if(zoomsize>3.0f)
		return;
	}
	if((movePosTMP[0]<3000)&&(movePosTMP[1]>5000))
	{
		Touchang=float(TouchPointOrg.m128_i32[2]-TouchInputposs[1].m128_i32[0]);
		TouchangY=float(TouchPointOrg.m128_i32[3]-TouchInputposs[1].m128_i32[1]);
		zoomsize=0.0f;
	}
	if((movePosTMP[1]<3000)&&(movePosTMP[0]>5000))
	{
		Touchang=float(TouchPointOrg.m128_i32[0]-TouchInputposs[0].m128_i32[0]);
		TouchangY=float(TouchPointOrg.m128_i32[1]-TouchInputposs[0].m128_i32[1]);
		zoomsize=0.0f;
	}
/*
	int movePosTMP[2]={
			Easy_vector_Getlenth_2i(
					TouchInputposs[0].m128_i32[0],
					TouchInputposs[0].m128_i32[2],
					TouchInputposs[0].m128_i32[1],
					TouchInputposs[0].m128_i32[3]),
			Easy_vector_Getlenth_2i(
					TouchInputposs[1].m128_i32[0],
					TouchInputposs[1].m128_i32[2],
					TouchInputposs[1].m128_i32[1],
					TouchInputposs[1].m128_i32[3])};
	if((movePosTMP[0]-movePosTMP[1]-250*250)>0)
		if(movePosTMP[1]<300*300)
	{
		zoomsize=0.0f;
		return;
	}
	if((movePosTMP[1]-movePosTMP[0]-300*300)>0)
		if(movePosTMP[0]<300*300)
	{
		zoomsize=0.0f;
		return;
	}
	if((movePosTMP[0]>200*200)&&(movePosTMP[1]>200*200))
	{
		//zoomsize=max(-0.1f,min(0.1f,zoomsize));
		NoTouchMoveTimes=20.0f;
		return;
	}
	else
	{
		zoomsize=0.0f;
	}*/
	
					//TouchInputposs[0].m128_i32[0]-TouchInputposs[1].m128_i32[0]
	
}
// Process Window Message Callbacks
LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Get The Window Context
	GL_Window* window = (GL_Window*)(GetWindowLong (hWnd, GWL_USERDATA));
	pGfxUI->SetInput(uMsg,wParam,lParam);
	switch (uMsg)														// Evaluate Window Message
	{
		case WM_SYSCOMMAND:												// Intercept System Commands
		{
			switch (wParam)												// Check System Calls
			{
				case SC_SCREENSAVE:										// Screensaver Trying To Start?
				case SC_MONITORPOWER:									// Monitor Trying To Enter Powersave?
				return 0;												// Prevent From Happening
			}
			break;														// Exit
		}
		return 0;														// Return

		case WM_CREATE:													// Window Creation
		{
			CREATESTRUCTW* creation = (CREATESTRUCTW*)(lParam);			// Store Window Structure Pointer
			window = (GL_Window*)(creation->lpCreateParams);
			SetWindowLongW (hWnd, GWL_USERDATA, (LONG)(window));
		}
		return 0;														// Return

		case WM_CLOSE:													// Closing The Window
			TerminateApplication(window);								// Terminate The Application
		return 0;														// Return

		case WM_SIZE:													// Size Action Has Taken Place
			switch (wParam)												// Evaluate Size Action
			{
				case SIZE_MINIMIZED:									// Was Window Minimized?
					window->isVisible = FALSE;							// Set isVisible To False
				return 0;												// Return

				case SIZE_MAXIMIZED:									// Was Window Maximized?
					window->isVisible = TRUE;							// Set isVisible To True
					ReshapeGL (LOWORD (lParam), HIWORD (lParam));		// Reshape Window - LoWord=Width, HiWord=Height
				return 0;												// Return

				case SIZE_RESTORED:										// Was Window Restored?
					window->isVisible = TRUE;							// Set isVisible To True
					ReshapeGL (LOWORD (lParam), HIWORD (lParam));		// Reshape Window - LoWord=Width, HiWord=Height
				return 0;												// Return
			}
		break;															// Break

		case WM_KEYDOWN:												// Update Keyboard Buffers For Keys Pressed
			if ((wParam >= 0) && (wParam <= 255))						// Is Key (wParam) In A Valid Range?
			{
				window->keys->keyDown [wParam] = TRUE;					// Set The Selected Key (wParam) To True
				return 0;												// Return
			}
		break;															// Break

		case WM_ACTIVATE:
		case WM_KEYUP:													// Update Keyboard Buffers For Keys Released
			if ((wParam >= 0) && (wParam <= 255))						// Is Key (wParam) In A Valid Range?
			{
				window->keys->keyDown [wParam] = FALSE;					// Set The Selected Key (wParam) To False
				return 0;												// Return
			}
		break;															// Break

		case WM_TOGGLEFULLSCREEN:										// Toggle FullScreen Mode On/Off
			GameSet.isFullScreem = (g_createFullScreen == TRUE) ? FALSE : TRUE;
			g_createFullScreen = (g_createFullScreen == TRUE) ? FALSE : TRUE;
			window->init.isFullScreen = (g_createFullScreen == TRUE) ? FALSE : TRUE;
			PostMessageW (hWnd, WM_QUIT, 0, 0);
		break;															// Break
		case WM_LBUTTONUP:
			InputPos[0]=LOWORD(lParam);
			InputPos[1]=HIWORD(lParam);
			InputPos[1]=GameSet.winH-InputPos[1];
			InputPos[2]=1;
			break;
		case WM_TOUCH:
			{
				if(nInputs<=0) break;
				nInputsNow=(unsigned int)wParam;
				TOUCHINPUT * ti=new TOUCHINPUT[nInputs];
				GetTouchInputInfo((HTOUCHINPUT)lParam, nInputs,ti,sizeof(TOUCHINPUT));
					
				for (unsigned int i=0;i<nInputsNow;i++)
				{
					TouchInputposs[i].m128_i32[2]=TouchInputposs[i].m128_i32[0];
					TouchInputposs[i].m128_i32[3]=TouchInputposs[i].m128_i32[1];
					TouchInputposs[i].m128_i32[0]=0;
					TouchInputposs[i].m128_i32[1]=0;
					if ((ti[i].dwFlags & TOUCHEVENTF_DOWN)||(ti[i].dwFlags & TOUCHEVENTF_MOVE))
					{
						if(i<=1)
						{
							TouchInputposs[i].m128_i32[0]=(int)ti[i].x;
							TouchInputposs[i].m128_i32[1]=(int)ti[i].y;
							Touchings[i]=true;
						}
					}
					else
					{
						Touchings[i]=false;
					}
					if (ti[i].dwFlags & TOUCHEVENTF_UP)
					{
						Touchings[i]=false;
					}

					
				}
				if(nInputsNow>1)
				{
					/*zoomsize=float(Easy_vector_Getlenth_2i(
						TouchInputposs[0].m128_i32[2],
						TouchInputposs[1].m128_i32[2],
						TouchInputposs[0].m128_i32[3],
						TouchInputposs[1].m128_i32[3]
						)-
					Easy_vector_Getlenth_2i(
						TouchInputposs[0].m128_i32[0],
						TouchInputposs[1].m128_i32[0],
						TouchInputposs[0].m128_i32[1],
						TouchInputposs[1].m128_i32[1]
						));
						zoomsize=max(-0.1f,min(0.1f,zoomsize));
						NoTouchMoveTimes=20.0f;*/
					if(DoubleTouchTime==0)
					{
						TouchPointOrg.m128_i32[0]=TouchInputposs[0].m128_i32[0];
						TouchPointOrg.m128_i32[1]=TouchInputposs[0].m128_i32[1];
						TouchPointOrg.m128_i32[2]=TouchInputposs[1].m128_i32[0];
						TouchPointOrg.m128_i32[3]=TouchInputposs[1].m128_i32[1];
					}
					DoubleTouchTime=DoubleTouchTime+1;
					if(DoubleTouchTime>10)
					{
						DoDoubleTouch();
						DoubleTouchTime=0;
					}
					//TouchInputposs[0].m128_i32[0]-TouchInputposs[1].m128_i32[0]
				}
				else
				{
					DoubleTouchTime=0;
					if(Touchings[0])
					if(!((TouchInputposs[0].m128_i32[0]==0)&&(TouchInputposs[0].m128_i32[1]==0)))
					{
						touchX=float(TouchInputposs[0].m128_i32[0]-TouchInputposs[0].m128_i32[2]);
						touchX=max(-0.1f,min(0.1f,touchX));
						touchY=float(TouchInputposs[0].m128_i32[1]-TouchInputposs[0].m128_i32[3]);
						touchY=max(-0.1f,min(0.1f,touchY));
					}
				}
				
				//WM_GESTURE
			
				//MessageBoxW (HWND_DESKTOP, L"检测到触摸消息", L" ", MB_OK | MB_ICONEXCLAMATION);
				
				CloseTouchInputHandle((HTOUCHINPUT)lParam);
				delete [] ti;
			}
		break;
	}
	return DefWindowProcW (hWnd, uMsg, wParam, lParam);					// Pass Unhandled Messages To DefWindowProc
}

BOOL RegisterWindowClass (Application* application)						// Register A Window Class For This Application.
{																		// TRUE If Successful
	// Register A Window Class
	WNDCLASSEXW windowClass;												// Window Class
	ZeroMemory (&windowClass, sizeof (WNDCLASSEXW));						// Make Sure Memory Is Cleared
	windowClass.cbSize			= sizeof (WNDCLASSEXW);					// Size Of The windowClass Structure
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraws The Window For Any Movement / Resizing
	windowClass.lpfnWndProc		= (WNDPROC)(WindowProc);				// WindowProc Handles Messages
	windowClass.hInstance		= application->hInstance;				// Set The Instance
	windowClass.hbrBackground	= (HBRUSH)(COLOR_APPWORKSPACE);			// Class Background Brush Color
	windowClass.hCursor			= LoadCursorW(NULL, MAKEINTRESOURCEW(32512));			// Load The Arrow Pointer IDC_ARROW
	windowClass.lpszClassName	= application->className;				// Sets The Applications Classname
	windowClass.hIcon			= (HICON)LoadImageW(GetModuleHandle(NULL), L"data\\TOP_ACE.ico",IMAGE_ICON,16,16,LR_LOADFROMFILE);
	if (RegisterClassExW (&windowClass) == 0)							// Did Registering The Class Fail?
	{
		// NOTE: Failure, Should Never Happen
		MessageBoxA (HWND_DESKTOP, "RegisterClassEx Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;													// Return False (Failure)
	}
	return TRUE;														// Return True (Success)
}

// Program Entry (WinMain)
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MainLOG.AddLOG("<HTML>");
	MainLOG.AddLOG("<head>");
	MainLOG.AddLOG("<TITLE>TOP ACE LOG</TITLE>");
	MainLOG.AddLOG("</head>");
	MainLOG.AddLOG("<BODY>");
	MainLOG.AddLOG("******TOP ACE LOG Start******");
	MainLOG.WriteLOGFile(false);
	CEXTLIBS_init(); ADD_LOG_Q("CEXTLIBS_init() OK");
	hInst=hInstance;
	InitRenderThread(); ADD_LOG_Q("InitRenderThread() OK");
	InitThreadUpdata(); ADD_LOG_Q("InitThreadUpdata() OK");
	InitDataThread();ADD_LOG_Q("InitDataThread() OK");
	LockFPSSYS.Init(60);
	ADD_LOG_Q("MainThread Start");
	ResumeThread(RenderThreadHANDLE);
	while(isRun)
	{
		DataUpdata();
		LockFPSSYS.LockFPS();
	}
	CEXTLIBS_deinit();ADD_LOG_Q("CEXTLIBS_deinit() OK");
	DeinitThreadUpdata();ADD_LOG_Q("DeinitThreadUpdata() OK");
	MainLOG.ClearLOG();
	
	MainLOG.AddLOG("******TOP ACE LOG End******");
	MainLOG.AddLOG("</BODY>");
	MainLOG.AddLOG("</HTML>");
	MainLOG.WriteLOGFile(true);
	return 0;
}																		// End Of WinMain()
HANDLE InitRenderThread()
{
	isDraw=true;
	RenderThreadHANDLE = (HANDLE)_beginthreadex(0,0,(unsigned int (__stdcall *)(void *))RenderThread,0,CREATE_SUSPENDED,0); 
	//SetPriorityClass(RenderThreadHANDLE,THREAD_PRIORITY_TIME_CRITICAL);
	//ResumeThread(RenderThreadHANDLE);
	return RenderThreadHANDLE;
}
void ExitRenderThread()
{
	isDraw=false;
}
unsigned int __stdcall RenderThread(LPVOID lpvoid)
{
	ADD_LOG_Q("RenderThread Start");
	Application			application;
	GL_Window			window;
	Keys				keys;
	BOOL				isMessagePumpActive;
	MSG					msg;
	
	ADD_LOG_Q("loadIniFile Start");
	loadIniFile();
	
	TouchMoveOverride=::GameSet.TouchMoveOverride;
	TouchZoomOverride=::GameSet.TouchZoomOverride;
	ADD_LOG_Q("loadIniFile End");
	application.className = L"TOP_ACE";
	application.hInstance = hInst;

	// Fill Out Window
	ZeroMemory (&window, sizeof (GL_Window));							// Make Sure Memory Is Zeroed
	window.keys					= &keys;								// Window Key Structure
	window.init.application		= &application;							// Window Application
	window.init.title			= L"TOP_ACE";
	window.init.width			= GameSet.winW;									// Window Width
	window.init.height			= GameSet.winH;									// Window Height
	window.init.bitsPerPixel	= GameSet.bits;									// Bits Per Pixel
	window.init.isFullScreen	= GameSet.isFullScreem;									// Fullscreen? (Set To TRUE)

	WindowWidth=GameSet.winW;
	WindowHeight=GameSet.winH;

	ZeroMemory (&keys, sizeof (Keys));

	if (RegisterWindowClass (&application) == FALSE)					// Did Registering A Class Fail?
	{
		MainLOG.AddLOG("******TOP ACE Error******");
		MainLOG.AddLOG("Error Registering Window Class");
		MainLOG.WriteLOGFile(false);
		return -1;														// Terminate Application
	}
	ADD_LOG_Q("Registering Window Class OK",NULL,NULL,NULL,NULL,true);
	gl_dll=LoadLibraryW(L"OpenGL32.DLL");
	if(!gl_dll) MessageBoxW (HWND_DESKTOP, L"Error Get OpenGL32.DLL!", L"Error", MB_OK | MB_ICONEXCLAMATION);
	if(gl_dll) hglSwapBuffers=(int (__stdcall *)(void *))GetProcAddress(gl_dll,"wglSwapBuffers");
	g_isProgramLooping = TRUE;
	g_createFullScreen = window.init.isFullScreen;
	
	ADD_LOG_Q("Render Loop Start",NULL,NULL,NULL,NULL,true);
	while (g_isProgramLooping)
	{
		window.init.isFullScreen = g_createFullScreen;
		if (CreateWindowGL (&window) == TRUE)
		{

			ADD_LOG_Q("CreateWindow OK",NULL,NULL,NULL,NULL,true);
			SwapHdc=window.hDC;
			if(glewIsSupported("WGL_EXT_swap_control"))
			{
				if(GameSet.SYNC) wglSwapIntervalEXT(1);
				else wglSwapIntervalEXT(0);
			}
			else
			{
				GameSet.SYNC=0;
				MainLOG.AddLOG("Can not suppot WGL_EXT_swap_control. SYNC no set.","#0000FF");
			}
			isMessagePumpActive = TRUE;
			if(!InitDraw()) TerminateApplication(&window);
			
			BYTE digitizerStatus = (BYTE)GetSystemMetrics(SM_DIGITIZER);
			TouchInput=true;
			if ((digitizerStatus & (0x80 + 0x40)) == 0)
			{
				//MessageBoxW (HWND_DESKTOP, L"没检测到多点触控设备或设备没有就绪", L"Error", MB_OK | MB_ICONEXCLAMATION);
				TouchInput=false;
				//TerminateApplication(&window);
			}
			nInputs = (BYTE)GetSystemMetrics(SM_MAXIMUMTOUCHES);
			if(nInputs<2)
			{
				//MessageBoxW (HWND_DESKTOP, L"触控设备不支持多点触摸", L"Error", MB_OK | MB_ICONEXCLAMATION);
				TouchInput=false;
				//TerminateApplication(&window);
			}
			nInputs=TouchInput?nInputs:0;
			if(TouchInput)
			TouchInput=RegisterTouchWindow(window.hWnd,0)==0?false:true;
			
			CGFXUI::Init();
			if(pGfxUI) delete pGfxUI;
			pGfxUI =new CGFXUI;
			pGfxUI->InitGFX();
			LockFPSRender.Init(GameSet.FPS);
			while (isMessagePumpActive == TRUE)	
			{
				if (PeekMessageW (&msg, window.hWnd, 0, 0, PM_REMOVE) != 0)
				{
					if (msg.message != WM_QUIT) DispatchMessageW (&msg);
					else	isMessagePumpActive = FALSE;
				}
				else
				{
					UpdataKeyInput(&window.keys->keyDown[0]);
					memcpy_s(
						ThreadDataDraw.DrawToData.Global_Data_Key.keyDownLast,
						sizeof(ThreadDataDraw.DrawToData.Global_Data_Key.keyDownLast),
						ThreadDataDraw.DrawToData.Global_Data_Key.keyDown_Now,
						sizeof(ThreadDataDraw.DrawToData.Global_Data_Key.keyDown_Now)
						);
					memcpy_s(
						ThreadDataDraw.DrawToData.Global_Data_Key.keyDown_Now,
						sizeof(ThreadDataDraw.DrawToData.Global_Data_Key.keyDown_Now),
						keys.keyDown,
						sizeof(keys.keyDown)
						);
					KeyUpdate (&keys,&window);
					if (window.isVisible == FALSE) WaitMessage ();
					else
					{
						framegfxtmp=framegfxtmp+1.0f;
						Draw (LockFPSSYS.oneframetimepoint,LockFPSRender.oneframetimepoint);
						glPushAttrib(GL_ALL_ATTRIB_BITS);
						glColor4f(1.0f,1.0f,1.0f,1.0f);
						if(framegfxtmp>30.0f)
						pGfxUI->Draw();
						glPopAttrib();
						glFlush();
						hglSwapBuffers (SwapHdc);
						if(GameSet.FPS>0) LockFPSRender.LockFPS();
					}
				}
			}
			if(pGfxUI) delete pGfxUI; pGfxUI=NULL;
			ClearVRAM();
			DestroyWindowGL (&window);
		}
		else
		{
			MessageBoxA (HWND_DESKTOP, "Error Creating OpenGL Window", "Error", MB_OK | MB_ICONEXCLAMATION);
			g_isProgramLooping = FALSE;
		}
	}
	DeinitDraw();
	UnregisterClassW (application.className, application.hInstance);
	isRun=false;
	
	ADD_LOG_Q("RenderThread End",NULL,NULL,NULL,NULL,true);
	return 0;
}
void ExchangeData (void)
{

}
