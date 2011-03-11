

#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <windows.h>								// Header File For Windows

#include <process.h>
typedef struct {									// Structure For Keyboard Stuff
	BOOL keyDown [256];								// Holds TRUE / FALSE For Each Key
} Keys;												// Keys

typedef struct {									// Contains Information Vital To Applications
	HINSTANCE		hInstance;						// Application Instance
	const wchar_t*		className;						// Application ClassName
} Application;										// Application

typedef struct {									// Window Creation Info
	Application*		application;				// Application Structure
	wchar_t*				title;						// Window Title
	int					width;						// Width
	int					height;						// Height
	int					bitsPerPixel;				// Bits Per Pixel
	BOOL				isFullScreen;				// FullScreen?
} GL_WindowInit;									// GL_WindowInit

typedef struct {									// Contains Information Vital To A Window
	Keys*				keys;						// Key Structure
	HWND				hWnd;						// Window Handle
	HDC					hDC;						// Device Context
	HGLRC				hRC;						// Rendering Context
	GL_WindowInit		init;						// Window Init
	BOOL				isVisible;					// Window Visible?
	DWORD				lastTickCount;				// Tick Counter
} GL_Window;										// GL_Window

void TerminateApplication (GL_Window* window);		// Terminate The Application

void ToggleFullscreen (GL_Window* window);			// Toggle Fullscreen / Windowed Mode


void KeyUpdate ( Keys* keys);					// Perform Motion Updates
HANDLE InitRenderThread();
void ExitRenderThread();
unsigned int __stdcall RenderThread(LPVOID lpvoid);
void ExchangeData (void);
void Swap(void);
void LockFPS (void);
#endif												// GL_FRAMEWORK__INCLUDED
