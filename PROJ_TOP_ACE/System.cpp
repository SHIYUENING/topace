
#include "Draw.h"
#include <windows.h>													// Header File For The Windows Library
#include <gl/glew.h>
#include <gl/wglew.h>
#include "LockFPS.h"

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
extern tGameSet GameSet;
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
HGLRC	 m_hrc;
CLockFPS LockFPSSYS,LockFPSRender;
CTALogSys MainLOG;
int TessLevel=1;
bool Gdown1=false;
bool Gdown2=false;
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
	if(g_keys->keyDown [VK_PRIOR] == TRUE)
		moveZ=moveZ+10.0f;
	if(g_keys->keyDown [VK_NEXT] == TRUE)
		moveZ=moveZ-10.0f;

	if((g_keys->keyDown ['1'] == TRUE)&&(!Gdown1))
	{
		Gdown1=true;
		TessLevel=TessLevel-1;
	}
	else Gdown1=false;
	if((g_keys->keyDown ['2'] == TRUE)&&(!Gdown2))
	{
		Gdown2=true;
		TessLevel=TessLevel+1;
	}
	else Gdown2=false;
	TessLevel=max(1,TessLevel);
	int TessLevelMAX=64;
	glGetIntegerv(GL_MAX_TESS_GEN_LEVEL,&TessLevelMAX);
	TessLevel=min(TessLevelMAX,TessLevel);

	if(g_keys->keyDown [VK_UP] == TRUE)
		moveY=moveY+10.0f;
	if(g_keys->keyDown [VK_DOWN] == TRUE)
		moveY=moveY-10.0f;


	if(g_keys->keyDown [VK_RIGHT] == TRUE)
		moveX=moveX+10.0f;
	if(g_keys->keyDown [VK_LEFT] == TRUE)
		moveX=moveX-10.0f;
	if(g_keys->keyDown [VK_HOME] == TRUE)
	{
		moveX=moveY=moveZ=0.0f;
	}
}


void TerminateApplication (GL_Window* window)							// Terminate The Application
{
	PostMessage (window->hWnd, WM_QUIT, 0, 0);							// Send A WM_QUIT Message
	g_isProgramLooping = FALSE;											// Stop Looping Of The Program
}

void ToggleFullscreen (GL_Window* window)								// Toggle Fullscreen/Windowed
{
	PostMessage (window->hWnd, WM_TOGGLEFULLSCREEN, 0, 0);				// Send A WM_TOGGLEFULLSCREEN Message
}

void ReshapeGL (int width, int height)									// Reshape The Window When It's Moved Or Resized
{
	GameSet.winW=WindowWidth=width;
	GameSet.winH=WindowHeight=height;
	CO_MatrixPerspectiveProjectionFov(45.0, (double)width/(double)height, 5.0,  100000.0); 
	GLdouble PMatrix[16];
	CO_GetPMatrixD(PMatrix);
	glViewport (0, 0, (GLsizei)(width), (GLsizei)(height));				// Reset The Current Viewport
	glMatrixMode (GL_PROJECTION);										// Select The Projection Matrix
	//glLoadIdentity ();													// Reset The Projection Matrix
	//gluPerspective(50, (float)width/(float)height, 5.0,  100000.0f);
	glLoadMatrixd(PMatrix);
	glMatrixMode (GL_MODELVIEW);										// Select The Modelview Matrix
	glLoadIdentity ();													// Reset The Modelview Matrix
}

BOOL ChangeScreenResolution (int width, int height, int bitsPerPixel)	// Change The Screen Resolution
{
	DEVMODE dmScreenSettings;											// Device Mode
	ZeroMemory (&dmScreenSettings, sizeof (DEVMODE));					// Make Sure Memory Is Cleared
	dmScreenSettings.dmSize				= sizeof (DEVMODE);				// Size Of The Devmode Structure
	dmScreenSettings.dmPelsWidth		= width;						// Select Screen Width
	dmScreenSettings.dmPelsHeight		= height;						// Select Screen Height
	dmScreenSettings.dmBitsPerPel		= bitsPerPixel;					// Select Bits Per Pixel
	dmScreenSettings.dmFields			= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	if (ChangeDisplaySettings (&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		return FALSE;													// Display Change Failed, Return False
	}
	return TRUE;														// Display Change Was Successful, Return True
}

BOOL CreateWindowGL (GL_Window* window)									// This Code Creates Our OpenGL Window
{
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;							// Define Our Window Style
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
			MessageBox (HWND_DESKTOP, "Mode Switch Failed.\nRunning In Windowed Mode.", "Error", MB_OK | MB_ICONEXCLAMATION);
			window->init.isFullScreen = FALSE;							// Set isFullscreen To False (Windowed Mode)
		}
		else															// Otherwise (If Fullscreen Mode Was Successful)
		{
			ShowCursor (FALSE);											// Turn Off The Cursor
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
	window->hWnd = CreateWindowEx (windowExtendedStyle,					// Extended Style
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
		ChangeDisplaySettings (NULL,0);									// Switch Back To Desktop Resolution
		ShowCursor (TRUE);												// Show The Cursor
	}	
	return TRUE;														// Return True
}

// Process Window Message Callbacks
LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Get The Window Context
	GL_Window* window = (GL_Window*)(GetWindowLong (hWnd, GWL_USERDATA));

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
			CREATESTRUCT* creation = (CREATESTRUCT*)(lParam);			// Store Window Structure Pointer
			window = (GL_Window*)(creation->lpCreateParams);
			SetWindowLong (hWnd, GWL_USERDATA, (LONG)(window));
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
			PostMessage (hWnd, WM_QUIT, 0, 0);
		break;															// Break
	}

	return DefWindowProc (hWnd, uMsg, wParam, lParam);					// Pass Unhandled Messages To DefWindowProc
}

BOOL RegisterWindowClass (Application* application)						// Register A Window Class For This Application.
{																		// TRUE If Successful
	// Register A Window Class
	WNDCLASSEX windowClass;												// Window Class
	ZeroMemory (&windowClass, sizeof (WNDCLASSEX));						// Make Sure Memory Is Cleared
	windowClass.cbSize			= sizeof (WNDCLASSEX);					// Size Of The windowClass Structure
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraws The Window For Any Movement / Resizing
	windowClass.lpfnWndProc		= (WNDPROC)(WindowProc);				// WindowProc Handles Messages
	windowClass.hInstance		= application->hInstance;				// Set The Instance
	windowClass.hbrBackground	= (HBRUSH)(COLOR_APPWORKSPACE);			// Class Background Brush Color
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	windowClass.lpszClassName	= application->className;				// Sets The Applications Classname
	if (RegisterClassEx (&windowClass) == 0)							// Did Registering The Class Fail?
	{
		// NOTE: Failure, Should Never Happen
		MessageBox (HWND_DESKTOP, "RegisterClassEx Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;													// Return False (Failure)
	}
	return TRUE;														// Return True (Success)
}

// Program Entry (WinMain)
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MainLOG.AddLOG("******TOP ACE LOG Start******");
	MainLOG.WriteLOGFile(false);
	CEXTLIBS_init();
	hInst=hInstance;
	InitRenderThread();
	InitThreadUpdata();
	InitDataThread();
	LockFPSSYS.Init(60);
	while(isRun)
	{
		DataUpdata();
		LockFPSSYS.LockFPS();
	}
	CEXTLIBS_deinit();
	DeinitThreadUpdata();
	MainLOG.ClearLOG();
	
	MainLOG.AddLOG("******TOP ACE LOG End******");
	MainLOG.WriteLOGFile(true);
	return 0;
}																		// End Of WinMain()
HANDLE InitRenderThread()
{
	isDraw=true;
	RenderThreadHANDLE = (HANDLE)_beginthreadex(0,0,(unsigned int (__stdcall *)(void *))RenderThread,0,CREATE_SUSPENDED,0); 
	//SetPriorityClass(RenderThreadHANDLE,THREAD_PRIORITY_TIME_CRITICAL);
	ResumeThread(RenderThreadHANDLE);
	return RenderThreadHANDLE;
}
void ExitRenderThread()
{
	isDraw=false;
}
unsigned int __stdcall RenderThread(LPVOID lpvoid)
{
	Application			application;
	GL_Window			window;
	Keys				keys;
	BOOL				isMessagePumpActive;
	MSG					msg;
	loadIniFile();
	application.className = "TOP_ACE";
	application.hInstance = hInst;

	// Fill Out Window
	ZeroMemory (&window, sizeof (GL_Window));							// Make Sure Memory Is Zeroed
	window.keys					= &keys;								// Window Key Structure
	window.init.application		= &application;							// Window Application
	window.init.title			= "TOP_ACE";
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

	gl_dll=LoadLibrary("OpenGL32.DLL");
	if(!gl_dll) MessageBox (HWND_DESKTOP, "Error Get OpenGL32.DLL!", "Error", MB_OK | MB_ICONEXCLAMATION);
	if(gl_dll) hglSwapBuffers=(int (__stdcall *)(void *))GetProcAddress(gl_dll,"wglSwapBuffers");
	g_isProgramLooping = TRUE;
	g_createFullScreen = window.init.isFullScreen;
	
	while (g_isProgramLooping)
	{
		window.init.isFullScreen = g_createFullScreen;
		if (CreateWindowGL (&window) == TRUE)
		{
			SwapHdc=window.hDC;
			if(GameSet.SYNC) wglSwapIntervalEXT(1);
			else wglSwapIntervalEXT(0);
			isMessagePumpActive = TRUE;
			InitDraw();
			LockFPSRender.Init(GameSet.FPS);
			while (isMessagePumpActive == TRUE)	
			{
				if (PeekMessage (&msg, window.hWnd, 0, 0, PM_REMOVE) != 0)
				{
					if (msg.message != WM_QUIT) DispatchMessage (&msg);
					else	isMessagePumpActive = FALSE;
				}
				else
				{
					UpdataKeyInput(&window.keys->keyDown[0]);
					KeyUpdate (&keys,&window);
					if (window.isVisible == FALSE) WaitMessage ();
					else
					{
						Draw (LockFPSSYS.oneframetimepoint,LockFPSRender.oneframetimepoint);
						glFlush();
						hglSwapBuffers (SwapHdc);
						if(GameSet.FPS>0) LockFPSRender.LockFPS();
					}
				}
			}
			ClearVRAM();
			DestroyWindowGL (&window);
		}
		else
		{
			MessageBox (HWND_DESKTOP, "Error Creating OpenGL Window", "Error", MB_OK | MB_ICONEXCLAMATION);
			g_isProgramLooping = FALSE;
		}
	}
	DeinitDraw();
	UnregisterClass (application.className, application.hInstance);
	isRun=false;
	return 0;
}
void ExchangeData (void)
{

}
