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
#include "Mathematics.h"
#include "missle.h"
#include "VBMD.h"	
#include <windows.h>											// Header File For Windows
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glaux.h>											// Header File For The GLaux Library
#include "NeHeGL.h"												// Header File For NeHeGL
#include <math.h>												// We'll Need Some Math
#include "SkyBox.h"
#include "Shader.h"
// ROACH
#include "arb_multisample.h"
#include "Md5Camera.h"
bool domulti = false;
bool doangle = true;
// ENDROACH
#define MAXCAMS 15
#pragma comment( lib, "opengl32.lib" )							// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )								// Search For GLu32.lib While Linking
#pragma comment( lib, "glaux.lib" )								// Search For GLaux.lib While Linking
#pragma comment( lib, "cg.lib" )	
#pragma comment( lib, "cgGL.lib" )	
#pragma comment( lib, "glew32.lib" )	
#pragma comment( lib, "glew32d.lib" )
#ifndef CDS_FULLSCREEN											// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4										// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors
LARGE_INTEGER t1,t2,feq,t3,t4;
GL_Window*	g_window;
Keys*		g_keys;
int			g_nFPS = 0, g_nFrames = 0;							// FPS and FPS Counter
DWORD		g_dwLastFPS = 0;
float movespeed=1.0f;
char szTitle[256]={0};
int modelID[16];
int * pModelID=NULL;
int * pModelIDWater=NULL;
int ModelNum=1;
int ModelNumWater=1;
int ModelNumLoaded=0;
int ModelNumLoadedWater=0;
int ModelAlphaNumLoaded=0;
int ballModelID=0;
int UImodelTest=0;
float angle= 0.75f;
float angleSpeed= 1.0f;
float Updown= 0.0f;
float angle2=0.0f;
double oneframetime=0.0;
double oneframetimeT=0.0;
double oneframetimelimit=1.0/60.0;
CLoadVBMD *m_VBMD = NULL;
GLuint AsciiFontTexId;
GLuint base;
extern int winwidth,winheight;
extern char * LoadCameraName;
float posX,posY,posZ;
Transform MView(Vector3d(0, 0, -40));
Transform MWorld;
Transform MFighter;
Transform Msky;
CSkyBox SkyBox;
extern float eyePositionSea[3];
extern GLuint AmbientReflectiveTexture;
extern bool ShaderWater;
GLuint SeaTexID=0;
float globalAmbientGL[4]={0.3f,0.3f,0.3f,1.0f};
float lightColor[4]={0.7f,0.7f,0.7f,1.0f};
float lightPosition[]= { 0.0f, 0.0f, 2.0f };
CMd5Camera CMd5CameraTest;
CMd5Camera Md5Cameras[MAXCAMS];
CMd5Camera Md5CamerasT[MAXCAMS];
int InMd5Camera=0;
Missledata ViewPos;
Transform ViewTo;
double Getrotation(Transform& Input);
extern int menuid=0;

bool isMAXSIZEWIN=false;

int _RenderMode =GL_FILL;
extern tSystemSet SystemSet;
extern HINSTANCE hIns;
CDDS ReadMeTex;
bool isDrawReadMeTex=false;
bool UseSence=true;
int SenceNum=0;
void SetFog()
{
	float FogColor[4]={
		float(SystemSet.FogColorR)/255.0f,
		float(SystemSet.FogColorG)/255.0f,
		float(SystemSet.FogColorB)/255.0f,
		1.0f};
	glFogi(GL_FOG_MODE,GL_EXP2);
	glFogfv(GL_FOG_COLOR,FogColor);
	glFogf(GL_FOG_DENSITY,float(SystemSet.FogDensity)/100000.0f);
	glHint(GL_FOG_HINT,GL_NICEST);
	glFogf(GL_FOG_START,1.0f);
	glFogf(GL_FOG_END,10000.0f);
}
void BuildFont()								// Build Our Font Display List
{

	CDDS loadDDS;
	AsciiFontTexId=loadDDS.loadCompressedTexture("Data/Font.dds");

	float	cx;											// Holds Our X Character Coord
	float	cy;											// Holds Our Y Character Coord

	base=glGenLists(256);								// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, AsciiFontTexId);			// Select Our Font Texture
	for (int loop=0; loop<256; loop++)						// Loop Through All 256 Lists
	{
		cx=float(loop%16)/16.0f;						// X Position Of Current Character
		cy=float(loop/16)/16.0f;						// Y Position Of Current Character

		glNewList(base+loop,GL_COMPILE);				// Start Building A List	
			glBegin(GL_QUADS);							// Use A Quad For Each Character
				glTexCoord2f(cx+0.015625f,1.0f-cy-0.0625f);			// Texture Coord (Bottom Left)
				glVertex2i(0,0);						// Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f+0.015625f,1.0f-cy-0.0625f);	// Texture Coord (Bottom Right)
				glVertex2i(16,0);						// Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f+0.015625f,1.0f-cy);			// Texture Coord (Top Right)
				glVertex2i(16,16);						// Vertex Coord (Top Right)
				glTexCoord2f(cx+0.015625f,1.0f-cy);					// Texture Coord (Top Left)
				glVertex2i(0,16);						// Vertex Coord (Top Left)
			glEnd();									// Done Building Our Quad (Character)
			glTranslated(10.0f,0.0f,0.0f);						// Move To The Right Of The Character
		glEndList();									// Done Building The Display List
	}													// Loop Until All 256 Are Built
}
void DrawReadme()
{
	if(!isDrawReadMeTex)
		return;
	glBindTexture(GL_TEXTURE_2D, ReadMeTex.g_compressedTextureID);			// Select Our Font Texture
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,winwidth,0,winheight,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( (winwidth-512)/2,(winheight-512)/2+512);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i((winwidth-512)/2+512 ,(winheight-512)/2+512);
				glTexCoord2f(1.0f,	0.0f);	glVertex2i((winwidth-512)/2+512, (winheight-512)/2+0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( (winwidth-512)/2, (winheight-512)/2+0);
			glEnd();

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}
void glPrints(int x, int y, int winW,int winH,char *string)	// Where The Printing Happens
{
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );

	glBindTexture(GL_TEXTURE_2D, AsciiFontTexId);			// Select Our Font Texture
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,winW,0,winH,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	
	glTranslated(x,y,0);								// Position The Text (0,0 - Bottom Left)

	glListBase(base-32);						// Choose The Font Set (0 or 1)
	glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}
void DrawFPS()
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glEnable(GL_BLEND);
	if( GetTickCount() - g_dwLastFPS >= 1000 )					// When A Second Has Passed...
	{
		g_dwLastFPS = GetTickCount();							// Update Our Time Variable
		g_nFPS = g_nFrames;										// Save The FPS
		g_nFrames = 0;											// Reset The FPS Counter
	}
	
	g_nFrames++;											
	//sprintf( szTitle, "%4.8f time,%2.0d FPS MX%4.0d MY%4.0d %4.2f %4.2f %4.2f %4.2f MID:%d" ,oneframetime,g_nFPS,mouse_x,mouse_y,angle,(float)MFighter.RefPos()(0),(float)MFighter.RefPos()(1),(float)MFighter.RefPos()(2),menuid);
	sprintf( szTitle, "%2.0d FPS Move Speed:%4.2f x:%4.2f y:%4.2f z:%4.2f" ,g_nFPS,movespeed,(float)MFighter.RefPos()(0),(float)MFighter.RefPos()(1),(float)MFighter.RefPos()(2));
	glPrints(0,winheight-16,winwidth,winheight,szTitle);
	//char ShowMoveSpeed[32]={0};
	//sprintf(ShowMoveSpeed,"Move Speed:%4.2f",movespeed);
	//glPrints(0,winheight-32,winwidth,winheight,ShowMoveSpeed);
	
}
void Delay(__int64 Us)
{
    LARGE_INTEGER CurrTicks, TicksCount; 

    QueryPerformanceFrequency(&TicksCount);
    QueryPerformanceCounter(&CurrTicks); 

    TicksCount.QuadPart = TicksCount.QuadPart * Us / 1000000i64;
    TicksCount.QuadPart += CurrTicks.QuadPart; 

    while(CurrTicks.QuadPart<TicksCount.QuadPart)
        QueryPerformanceCounter(&CurrTicks);
}
void LockFPS (void)
{
	double waitTime=0.0;
	QueryPerformanceFrequency(&feq);
	QueryPerformanceCounter(&t2);
    if (t2.QuadPart >= t1.QuadPart)
	{
	    oneframetime=((double)(t2.QuadPart-t1.QuadPart))/((double)feq.QuadPart);
		
    }
	else
		return;

	double SleepTime=(oneframetimelimit-oneframetime)*1000.0;
	while(SleepTime>30.0)
	{
		Sleep(1);
		QueryPerformanceFrequency(&feq);
		QueryPerformanceCounter(&t2);
		if (t2.QuadPart >= t1.QuadPart)
			waitTime=((double)(t2.QuadPart-t1.QuadPart))/((double)feq.QuadPart);
		else
			return;
		SleepTime=(oneframetimelimit-waitTime)*1000.0;
	}
	QueryPerformanceFrequency(&feq);
	QueryPerformanceCounter(&t2);
    if (t2.QuadPart >= t1.QuadPart)
	{
	    waitTime=((double)(t2.QuadPart-t1.QuadPart))/((double)feq.QuadPart);
		
    }
	else
		return;

	Delay(__int64((oneframetimelimit-waitTime)*1000000));
	QueryPerformanceCounter(&t1);
}

void loadmodels()
{
	WIN32_FIND_DATA FindFileData = {0};
    char sTmp[256] = {0};

	ModelNumWater=GetPrivateProfileInt("Set","ModelNumWater",10,".\\Model.ini");
	pModelIDWater=new int[ModelNumWater];
	sprintf(sTmp,"Data/Model/Waters/*.dds");
	HANDLE hFind = ::FindFirstFile(sTmp, &FindFileData);
	if(INVALID_HANDLE_VALUE != hFind)
	{		
		while(ModelNumLoadedWater<ModelNumWater)
		{
			if (FindFileData.cFileName[0] != '.')
			{
				pModelIDWater[ModelNumLoadedWater]=0;
				char sTmp2[256] = {0};
				char loadModelpathName[256] = {0};
				int tmpi=0;
				for(unsigned int i=0;i<strlen(FindFileData.cFileName);i++)
				{
					if(i<256)
					{
						if(FindFileData.cFileName[i]=='.')
							sTmp2[i]=0;
						else
							sTmp2[i]=FindFileData.cFileName[i];
					}
				}
				sprintf(loadModelpathName,"Data/Model/Waters/%s",sTmp2);
				pModelIDWater[ModelNumLoadedWater]=m_VBMD->Init(loadModelpathName);
				ModelNumLoadedWater=ModelNumLoadedWater+1;
			}
			if(!FindNextFile(hFind, &FindFileData))
				break;
		}
		FindClose(hFind);
	}



	ModelNum=GetPrivateProfileInt("Set","ModelNum",290,".\\Model.ini");
	pModelID=new int[ModelNum];

	sprintf(sTmp,"Data/Model/*.dds");
	hFind = ::FindFirstFile(sTmp, &FindFileData);
	if(INVALID_HANDLE_VALUE == hFind)
		MessageBox( NULL, "FindNoFile", "ERROR", MB_OK|MB_ICONEXCLAMATION );
	else
	{
		while(ModelNumLoaded<ModelNum)
		{
			if (FindFileData.cFileName[0] != '.')
			{
				pModelID[ModelNumLoaded]=0;
				char sTmp2[256] = {0};
				char loadModelpathName[256] = {0};
				int tmpi=0;
				for(unsigned int i=0;i<strlen(FindFileData.cFileName);i++)
				{
					if(i<256)
					{
						if(FindFileData.cFileName[i]=='.')
							sTmp2[i]=0;
						else
							sTmp2[i]=FindFileData.cFileName[i];
					}
				}
				sprintf(loadModelpathName,"Data/Model/%s",sTmp2);
				pModelID[ModelNumLoaded]=m_VBMD->Init(loadModelpathName);
				ModelNumLoaded=ModelNumLoaded+1;
			}
			if(!FindNextFile(hFind, &FindFileData))
				break;
		}
		FindClose(hFind);
	
	}

	sprintf(sTmp,"Data/Model/Alpha/*.dds");
	hFind = ::FindFirstFile(sTmp, &FindFileData);
	if(INVALID_HANDLE_VALUE != hFind)
	{		
		while(ModelNumLoaded<ModelNum)
		{
			if (FindFileData.cFileName[0] != '.')
			{
				pModelID[ModelNumLoaded]=0;
				char sTmp2[256] = {0};
				char loadModelpathName[256] = {0};
				int tmpi=0;
				for(unsigned int i=0;i<strlen(FindFileData.cFileName);i++)
				{
					if(i<256)
					{
						if(FindFileData.cFileName[i]=='.')
							sTmp2[i]=0;
						else
							sTmp2[i]=FindFileData.cFileName[i];
					}
				}
				sprintf(loadModelpathName,"Data/Model/Alpha/%s",sTmp2);
				pModelID[ModelNumLoaded]=m_VBMD->Init(loadModelpathName);
				ModelNumLoaded=ModelNumLoaded+1;
				ModelAlphaNumLoaded=ModelAlphaNumLoaded+1;
			}
			if(!FindNextFile(hFind, &FindFileData))
				break;
		}
		FindClose(hFind);
	}

	ballModelID=m_VBMD->Init("Data/ball");
	UImodelTest=m_VBMD->Init("Data/ta1");
}
BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
{
	glewInit();
	glClearColor(0.0f, 0.0f, 0.0f, 0.5);
	glClear (GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);	
	glEnable(GL_TEXTURE_2D);
	CDDS TitleDDS;
	TitleDDS.loadCompressedTexture("Data/Title.dds",GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, TitleDDS.g_compressedTextureID);			// Select Our Font Texture
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,winwidth,0,winheight,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i(0,winheight);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i(winwidth,winheight);
				glTexCoord2f(1.0f,	0.0f);	glVertex2i(winwidth, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i(0, 0);
			glEnd();

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

	SwapBuffers (window->hDC);
	m_VBMD = new CLoadVBMD;
	m_VBMD->m_IsSupportFBO=true;

	InitSound();
	loadmodels();
	//angle=-90.0f;
	posX=posY=posZ=0;
	//posY=-500.0f;
	
	InitCG();

	SkyBox.Init();
	AmbientReflectiveTexture=SkyBox.SunCubeID;
	CDDS loadDDS;
	SeaTexID=loadDDS.loadCompressedTexture("Data/sea.dds",GL_LINEAR_MIPMAP_LINEAR);

	ReadMeTex.loadCompressedTexture("Data/readme.dds",GL_LINEAR);
	//CMd5CameraTest.LoadCamera("Data/123.md5camera");
	CMd5CameraTest.LoadCamera(LoadCameraName);
	Md5Cameras[1].LoadCamera("Data/1.md5camera");
	Md5Cameras[2].LoadCamera("Data/2.md5camera");
	Md5Cameras[3].LoadCamera("Data/3.md5camera");
	Md5Cameras[4].LoadCamera("Data/4.md5camera");
	Md5Cameras[5].LoadCamera("Data/5.md5camera");
	Md5Cameras[6].LoadCamera("Data/6.md5camera");
	Md5Cameras[7].LoadCamera("Data/7.md5camera");
	Md5Cameras[8].LoadCamera("Data/8.md5camera");
	Md5Cameras[9].LoadCamera("Data/9.md5camera");
	Md5Cameras[10].LoadCamera("Data/10.md5camera");

	Md5CamerasT[1].LoadCamera("Data/1t.md5camera");
	Md5CamerasT[2].LoadCamera("Data/2t.md5camera");
	Md5CamerasT[3].LoadCamera("Data/3t.md5camera");
	Md5CamerasT[4].LoadCamera("Data/4t.md5camera");
	Md5CamerasT[5].LoadCamera("Data/5t.md5camera");
	Md5CamerasT[6].LoadCamera("Data/6t.md5camera");
	Md5CamerasT[7].LoadCamera("Data/7t.md5camera");
	Md5CamerasT[8].LoadCamera("Data/8t.md5camera");
	Md5CamerasT[9].LoadCamera("Data/9t.md5camera");
	Md5CamerasT[10].LoadCamera("Data/10t.md5camera");

	g_window	= window;
	g_keys		= keys;

	BuildFont();
	glViewport(0 , 0,window->init.width ,window->init.height);	// Set Up A Viewport
	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glLoadIdentity();											// Reset The Projection Matrix
	gluPerspective(50, (float)window->init.width/(float)window->init.height, 1,  10000); // Set Our Perspective
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	glLoadIdentity();											// Reset The Modelview Matrix

	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing

	glShadeModel(GL_SMOOTH);									// Select Smooth Shading

							// Set The Clear Color To Black
	glEnable(GL_TEXTURE_2D);


	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbientGL);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,lightColor);
	glLightfv(GL_LIGHT1,GL_SPECULAR,lightColor);
	glLineWidth(float(SystemSet.LineWidth));
	SetFog();
	ViewPos.UDMplane.Reset();
	ViewPos.UDMplane.TranslateInternal(Vector3d(1947.91 ,-585.33 ,-1310.41));
	ViewPos.TurnTo(Vector3d(1849.3800,-580.2999,-1313.8549));
	ViewPos.UDPstate.NextState();
	MFighter=ViewPos.UDMplane;
	MFighter.RotateInternal(Vector3d(0.0f, CRad(180.0f), 0.0f));
	MFighter.RotateInternal(Vector3d(0.0f,0.0f ,- CRad(Getrotation(MFighter))));
	//MFighter.RotateInternal(Vector3d(0.0f, CRad(45), 0.0f));
	QueryPerformanceCounter(&t1);
	QueryPerformanceFrequency(&feq);
	CMd5CameraTest.StartTime=double(t1.QuadPart)/double(feq.QuadPart);
	return TRUE;												// Return TRUE (Initialization Successful)
}
void SetCam(Vector3d Pos,Vector3d Tpos)
{
	ViewPos.UDMplane.Reset();
	ViewPos.UDMplane.TranslateInternal(Pos);
	ViewPos.TurnTo(Tpos);
	ViewPos.UDPstate.NextState();
	MFighter=ViewPos.UDMplane;
	MFighter.RotateInternal(Vector3d(0.0f, CRad(180.0f), 0.0f));
	MFighter.RotateInternal(Vector3d(0.0f,0.0f ,- CRad(Getrotation(MFighter))));
}
void Deinitialize (void)										// Any User DeInitialization Goes Here
{
	DeinitSound();
}

void Update (DWORD milliseconds)								// Perform Motion Updates Here
{
	Updown=angle=angle2=posX=posY=posZ=0.0f;
	if(g_keys->keyDown ['X'] == TRUE)
		posY=+movespeed;
	if(g_keys->keyDown ['Z'] == TRUE)
		posY=-movespeed;
	if(g_keys->keyDown ['A'] == TRUE)
		posX=-movespeed;
		//angle=-1.0f;
	if(g_keys->keyDown ['D'] == TRUE)
		//angle=+1.0f;
		posX=+movespeed;
	if(g_keys->keyDown ['W'] == TRUE)
		posZ=-movespeed;
	if(g_keys->keyDown ['S'] == TRUE)
		posZ=+movespeed;
	if(g_keys->keyDown [VK_LEFT] == TRUE)
		angle=-angleSpeed;
	if(g_keys->keyDown [VK_RIGHT] == TRUE)
		angle=+angleSpeed;
	if(g_keys->keyDown [VK_UP] == TRUE)
		Updown=-angleSpeed;
		//posY=-5.0f*(1.0f*doangle+0.05f);
	if(g_keys->keyDown [VK_DOWN] == TRUE)
		Updown=+angleSpeed;
		//posY=+5.0f*(1.0f*doangle+0.05f);
	/*if(g_keys->keyDown ['Z'] == TRUE)
		posZ=-10.0f;
	if(g_keys->keyDown ['X'] == TRUE)
		posZ=+10.0f;*/
	if(g_keys->keyDown [VK_SUBTRACT] == TRUE)
		movespeed=movespeed-0.025f;
	if(g_keys->keyDown [VK_ADD] == TRUE)
		movespeed=movespeed+0.025f;
	if(movespeed<0.0f)
		movespeed=0.0f;
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
		//ToggleFullscreen (g_window);							// Toggle Fullscreen Mode
	}
	if(g_keys->keyDown [VK_HOME] == TRUE)
	{
		InMd5Camera=0;
		SetCam(Vector3d(1974.1 ,-571.056 ,-1314.86),Vector3d(1822.22 ,-576.522 ,-1286.59));
	}
	if(menuid==ID_MENU_EXIT)
		TerminateApplication (g_window);
	if(menuid==ID_MENU_OPEN_WIN)
		OpenSelectWindow();
	if(menuid==ID_MENU_FULLS)
	{
		
		if(isMAXSIZEWIN)
			ShowWindow (g_window->hWnd, SW_NORMAL);
		else
			ShowWindow (g_window->hWnd, SW_SHOWMAXIMIZED);
		isMAXSIZEWIN=!isMAXSIZEWIN;
	}
	if(menuid==ID_MENU_FILL)
	{
		_RenderMode=GL_FILL;
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}
	if(menuid==ID__MENU_FRAME)
	{
		_RenderMode=GL_LINE;
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
	if(menuid==ID__MENU_FRAME_WIDTH)
	{
		DialogBox( hIns, MAKEINTRESOURCE( IDD_DIALOG_FRAME_WIDTH ), g_window->hWnd, LineWidthDlgProc );
	}
	if(menuid==ID_MENU_FOG_SET)
	{
		DialogBox( hIns, MAKEINTRESOURCE( IDD_DIALOG_SET_FOG ), g_window->hWnd, SetFogDlgProc );
	}
	if(menuid==ID_MENU_ROAMING_ROUTE_1)
	{
		InMd5Camera=1;
		QueryPerformanceCounter(&t4);
		Md5Cameras[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		Md5CamerasT[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		if(Md5Cameras[InMd5Camera].numFrames==0)
			InMd5Camera=0;
		if(Md5CamerasT[InMd5Camera].numFrames==0)
			InMd5Camera=0;
	}
	if(menuid==ID_MENU_ROAMING_ROUTE_2)
	{
		InMd5Camera=2;
		QueryPerformanceCounter(&t4);
		Md5Cameras[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		Md5CamerasT[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		if(Md5Cameras[InMd5Camera].numFrames==0)
			InMd5Camera=0;
		if(Md5CamerasT[InMd5Camera].numFrames==0)
			InMd5Camera=0;
	}
	if(menuid==ID_MENU_ROAMING_ROUTE_3)
	{
		InMd5Camera=3;
		QueryPerformanceCounter(&t4);
		Md5Cameras[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		Md5CamerasT[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		if(Md5Cameras[InMd5Camera].numFrames==0)
			InMd5Camera=0;
		if(Md5CamerasT[InMd5Camera].numFrames==0)
			InMd5Camera=0;
	}
	if(menuid==ID_MENU_ROAMING_ROUTE_4)
	{
		InMd5Camera=4;
		QueryPerformanceCounter(&t4);
		Md5Cameras[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		Md5CamerasT[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		if(Md5Cameras[InMd5Camera].numFrames==0)
			InMd5Camera=0;
		if(Md5CamerasT[InMd5Camera].numFrames==0)
			InMd5Camera=0;
	}
	if(menuid==ID_MENU_ROAMING_ROUTE_5)
	{
		InMd5Camera=5;
		QueryPerformanceCounter(&t4);
		Md5Cameras[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		Md5CamerasT[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		if(Md5Cameras[InMd5Camera].numFrames==0)
			InMd5Camera=0;
		if(Md5CamerasT[InMd5Camera].numFrames==0)
			InMd5Camera=0;
	}
	if(menuid==ID_MENU_ROAMING_ROUTE_6)
	{
		InMd5Camera=6;
		QueryPerformanceCounter(&t4);
		Md5Cameras[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		Md5CamerasT[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		if(Md5Cameras[InMd5Camera].numFrames==0)
			InMd5Camera=0;
		if(Md5CamerasT[InMd5Camera].numFrames==0)
			InMd5Camera=0;
	}
	if(menuid==ID_MENU_ROAMING_ROUTE_7)
	{
		InMd5Camera=7;
		QueryPerformanceCounter(&t4);
		Md5Cameras[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		Md5CamerasT[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		if(Md5Cameras[InMd5Camera].numFrames==0)
			InMd5Camera=0;
		if(Md5CamerasT[InMd5Camera].numFrames==0)
			InMd5Camera=0;
	}
	if(menuid==ID_MENU_ROAMING_ROUTE_8)
	{
		InMd5Camera=8;
		QueryPerformanceCounter(&t4);
		Md5Cameras[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		Md5CamerasT[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		if(Md5Cameras[InMd5Camera].numFrames==0)
			InMd5Camera=0;
		if(Md5CamerasT[InMd5Camera].numFrames==0)
			InMd5Camera=0;
	}
	if(menuid==ID_MENU_ROAMING_ROUTE_9)
	{
		InMd5Camera=9;
		QueryPerformanceCounter(&t4);
		Md5Cameras[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		Md5CamerasT[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		if(Md5Cameras[InMd5Camera].numFrames==0)
			InMd5Camera=0;
		if(Md5CamerasT[InMd5Camera].numFrames==0)
			InMd5Camera=0;
	}
	if(menuid==ID_MENU_ROAMING_ROUTE_10)
	{
		InMd5Camera=10;
		QueryPerformanceCounter(&t4);
		Md5Cameras[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		Md5CamerasT[InMd5Camera].StartTime=double(t4.QuadPart)/double(feq.QuadPart);
		if(Md5Cameras[InMd5Camera].numFrames==0)
			InMd5Camera=0;
		if(Md5CamerasT[InMd5Camera].numFrames==0)
			InMd5Camera=0;
	}
	if(menuid==ID_MENU_BGM_1)
	{
		PlaySound1();
	}
	if(menuid==ID_MENU_BGM_2)
	{
		PlaySound2();
	}
	if(menuid==ID_MENU_BGM_3)
	{
		PlaySound3();
	}
	if(menuid==ID_MENU_BGM_STOP)
	{
		StopSound();
	}
	if(menuid==ID_40031)
	{
		isDrawReadMeTex=!isDrawReadMeTex;
	}
	if(menuid==ID_MENU_ROAMING_SCENE_1)
	{
		InMd5Camera=0;
		SetCam(Vector3d(1947.91 ,-585.33 ,-1310.41),Vector3d(1822.22 ,-576.522 ,-1286.59));
	}

	if(menuid==ID_MENU_ROAMING_SCENE_2)
	{
		InMd5Camera=0;
		SetCam(Vector3d(2018.82 ,-558.228 ,-956.967),Vector3d(1933.39 ,-557.79 ,-932.265));
	}

	if(menuid==ID_MENU_ROAMING_SCENE_3)
	{
		InMd5Camera=0;
		SetCam(Vector3d(1634.25 ,-412.181 ,1305.57),Vector3d(1387.05 ,-450.88 ,787.698));
	}

	if(menuid==ID_MENU_ROAMING_SCENE_4)
	{
		InMd5Camera=0;
		//SetCam(Vector3d(-988.271 ,-137.959 ,421.266),Vector3d(-988.271 ,-137.959 ,421.266));
		SetCam(Vector3d(973.94 ,-403.52 ,240.215),Vector3d(336.267 ,-426.86 ,400.856));
	}

	if(menuid==ID_MENU_ROAMING_SCENE_5)
	{
		InMd5Camera=0;
		SetCam(Vector3d(-988.271 ,137.959 ,-421.266),Vector3d(-1140.5 ,-106.263 ,-813.717));
	}

	if(menuid==ID_MENU_ROAMING_SCENE_6)
	{
		InMd5Camera=0;
		//SetCam(Vector3d(1974.1 ,-571.056 ,-1314.86),Vector3d(1822.22 ,-576.522 ,-1286.59));
		SetCam(Vector3d(-211.127 ,-549.864 ,-168.501),Vector3d(-233.653 ,-549.864 ,-161.012));
	}

	if(menuid==ID_MENU_ROAMING_SCENE_7)
	{
		InMd5Camera=0;
		SetCam(Vector3d(-230.3 ,-556.198 ,-166.662),Vector3d(-244.503 ,-556.278 ,-162.667));
	}

	if(menuid==ID_MENU_ROAMING_SCENE_8)
	{
		InMd5Camera=0;
		SetCam(Vector3d(-318.782 ,-563.464 ,-135.023),Vector3d(-254.623 ,-563.485 ,-158.523));
	}
	if(menuid==ID_MENU_ROAMING_SCENE_9)
	{
		InMd5Camera=0;
		SetCam(Vector3d(-242.752 ,-558.432 ,-152.891),Vector3d(-232.269 ,-558.151 ,-125.493));
	}

	if(menuid==ID_MENU_ROAMING_SCENE_10)
	{
		InMd5Camera=0;
		SetCam(Vector3d(-282.958 ,-553.557 ,-43.5626),Vector3d(-279.114 ,-553.811 ,-41.512));
	}
	if(menuid==ID_MOVE_SPEED_LOW)
	{
		//angleSpeed=1.0;
		movespeed=1.0;
	}
	if(menuid==ID_MOVE_SPEED_MID)
	{
		//angleSpeed=2.0;
		movespeed=5.0;
	}
	if(menuid==ID_MOVE_SPEED_HIGH)
	{
		//angleSpeed=3.0;
		movespeed=25.0;
	}
	if(menuid==ID_ANGLE_SPEED_LOW)
	{
		angleSpeed=1.0;
		//movespeed=1.0;
	}
	if(menuid==ID_ANGLE_SPEED_MID)
	{
		angleSpeed=2.0;
		//movespeed=5.0;
	}
	if(menuid==ID_ANGLE_SPEED_HIGH)
	{
		angleSpeed=3.0;
		//movespeed=25.0;
	}



	menuid=0;
	LockFPS();
}
void DrawSky(Transform viewSky,float ne=0.0)
{
	glDisable(GL_BLEND);
	glPushMatrix();
	double fogbackY;
	if(viewSky.RefPos()(1)>50000.0)
		fogbackY=viewSky.RefPos()(1);
	else
	{
		fogbackY=50000.0;
	}
	Msky.Translate( Vector3d( viewSky.RefPos()(0) ,viewSky.RefPos()(1), viewSky.RefPos()(2) ) );
	glMultMatrixd(Msky.Matrix4());	
	glScaled(5000.0,5000.0,5000.0);
	glDisable(GL_DEPTH_TEST);
	SkyBox.Draw();
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	Msky.Translate( Vector3d( -viewSky.RefPos()(0) ,  -viewSky.RefPos()(1) , -viewSky.RefPos()(2) ) );
	glEnable(GL_BLEND);
}
void DrawGround(void)
{

	eyePositionSea[0]=(float)MFighter.RefPos()(0);
	eyePositionSea[1]=(float)MFighter.RefPos()(1);
	eyePositionSea[2]=(float)MFighter.RefPos()(2);


	if(ShaderWater)
	{
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glColor4f(1.0f,1.0f,1.0f,1.0f);
		DrawSea();
		glPushMatrix();
			//glDisable(GL_BLEND);
			glBindTexture(GL_TEXTURE_2D,SeaTexID);
			for(int i=0;i<ModelNumLoadedWater;i++)
				m_VBMD->ShowVBMD(pModelIDWater[i],false);
		glPopMatrix();
		CGDisableProfilePixel();
		CGDisableProfileVertex();
		CGDisableTextureParameterAmbientReflectiveSea();
		glEnable(GL_ALPHA_TEST);
	}
	else
	{
		glPushMatrix();
			glEnable(GL_FOG);
			glDisable(GL_BLEND);
			glBindTexture(GL_TEXTURE_2D,SeaTexID);
			glColor4f(0.0f,0.2f,0.6f,1.0f);
			for(int i=0;i<ModelNumLoadedWater;i++)
				m_VBMD->ShowVBMD(pModelIDWater[i],false);
			glColor4f(1.0f,1.0f,1.0f,1.0f);
			glDisable(GL_FOG);
		glPopMatrix();	
	}
}
double Getrotation(Transform& Input)
{
	Vector3d pos;
	pos = Input.RefPos();
    Vector3d dir;
    dir = Input.Matrix() * Vector3d(0, 0, -1);
    Vector3d dir2;
    dir2 = Input.Matrix() * Vector3d(1, 0, 0);
    double r = sqrt(pow(dir(0), 2) + pow(dir(2), 2));
    if (abs(r)>1){ r = 1.0f; }
    double latitude = acos_s(r) * 180.0f / PI;
    double longitude = acos_s(dir(2) / r) * 180.0f / PI;
    if (dir(0) < 0){ longitude = -longitude; }
    double intersect[3] = {-dir(2) / r, 0, dir(0) / r};
    double rotation = acos_s(dir2(0) * intersect[0] + dir2(1) * intersect[1] + dir2(2) * intersect[2]) * 180.0f / PI;
    if (dir2(1) < 0){ rotation = -rotation; }
	return rotation;
}
void DrawUI(void)
{
	GLint DRX=(GLint)(winwidth/2.0f);
	GLint DRY=(GLint)(winheight/2.0f);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(-DRX,DRX,-DRY,DRY,-1000,1000);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glEnable(GL_BLEND);
	//glScaled(0.7, 0.7, 1.0);
	//glRotated(-rotation,0.0f,0.0f,1.0f);

	m_VBMD->ShowVBMD(UImodelTest);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing


}
void Draw (void)												// Draw The Scene
{
	Vector3d tmp3d;
	tmp3d=MView.Matrix() * Vector3d(0.0,100000.0,0.0) + MView.RefPos();
	lightPosition[0]=(float)tmp3d(0);
	lightPosition[1]=(float)tmp3d(1);
	lightPosition[2]=(float)tmp3d(2);
	glLightfv(GL_LIGHT1,GL_POSITION,lightPosition);
	// ROACH
	QueryPerformanceCounter(&t3);
	if(InMd5Camera>=1)
	{
		Md5Cameras[InMd5Camera].Play(double(t3.QuadPart)/double(feq.QuadPart));
		Md5CamerasT[InMd5Camera].Play(double(t3.QuadPart)/double(feq.QuadPart));
	}
	//CMd5CameraTest.Play(double(t3.QuadPart)/double(feq.QuadPart));
	if(domulti)
		glEnable(GL_MULTISAMPLE_ARB);							// Enable Our Multisampling
	// ENDROACH

	glClearColor(0.0f, 0.0f, 0.0f, 0.5);						// Set The Clear Color To Black
	glClear (GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity();											// Reset The View	
	
	//MFighter.Reset();
	
	ViewPos.UDMplane.Reset();
	if(InMd5Camera>=1)
	{
		ViewPos.UDMplane.Translate(Vector3d(Md5Cameras[InMd5Camera].CameraPos[0],Md5Cameras[InMd5Camera].CameraPos[2],-Md5Cameras[InMd5Camera].CameraPos[1]));

		ViewPos.TurnTo(Vector3d(Md5CamerasT[InMd5Camera].CameraPos[0],Md5CamerasT[InMd5Camera].CameraPos[2],-Md5CamerasT[InMd5Camera].CameraPos[1]));
	}
	ViewPos.UDPstate.NextState();
	ViewPos.UDMplane.RotateInternal(Vector3d(0.0f, CRad(180.0f), 0.0f));

	/*	Vector3d pos;
	pos = ViewPos.UDMplane.RefPos();
    Vector3d dir;
    dir = ViewPos.UDMplane.Matrix() * Vector3d(0, 0, -1);
    Vector3d dir2;
    dir2 = ViewPos.UDMplane.Matrix() * Vector3d(1, 0, 0);
    double r = sqrt(pow(dir(0), 2) + pow(dir(2), 2));
    if (abs(r)>1){ r = 1.0f; }
    double latitude = acos_s(r) * 180.0f / PI;
    double longitude = acos_s(dir(2) / r) * 180.0f / PI;
    if (dir(0) < 0){ longitude = -longitude; }
    double intersect[3] = {-dir(2) / r, 0, dir(0) / r};
    double rotation = acos_s(dir2(0) * intersect[0] + dir2(1) * intersect[1] + dir2(2) * intersect[2]) * 180.0f / PI;
    if (dir2(1) < 0){ rotation = -rotation; }*/
	ViewPos.UDMplane.RotateInternal(Vector3d(0.0f,0.0f ,- CRad(Getrotation(ViewPos.UDMplane))));


	MFighter.RotateInternal(Vector3d(0.0f,0.0f ,- CRad(Getrotation(MFighter))));
	MFighter.RotateInternal(Vector3d(CRad(Updown), 0.0f, 0.0f));
	MFighter.RotateInternal(Vector3d(0.0f, -CRad(angle), 0.0f));
	MFighter.TranslateInternal(Vector3d(posX,-posY,posZ));
	if(InMd5Camera>=1)
		MFighter=ViewPos.UDMplane;
    MView = (MWorld * MFighter).Invert();
	glLoadMatrixd(MView.Matrix4());
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_FOG);
	DrawSky(MFighter);
	
	//glDisable(GL_TEXTURE_2D);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT1);
	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK,_RenderMode);
	for(int i=0;i<ModelNumLoaded;i++)
	{
		if(i==(ModelNumLoaded-ModelAlphaNumLoaded))
		{
			
			glDisable(GL_CULL_FACE);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GEQUAL, 0.9f);
			//glDisable(GL_LIGHT1);
			//glDisable(GL_LIGHTING);
		}

		m_VBMD->ShowVBMD(pModelID[i]);
	}
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	DrawGround();
	glAlphaFunc(GL_LESS, 0.9f);
	for(int i=(ModelNumLoaded-ModelAlphaNumLoaded);i<ModelNumLoaded;i++)
		m_VBMD->ShowVBMD(pModelID[i]);
	glColor3f(1.0f,1.0f,1.0f);
	glDepthMask(GL_TRUE);
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_FOG);
	//glPushMatrix();	
	//glTranslated(CMd5CameraTest.CameraView[0],CMd5CameraTest.CameraView[2],-CMd5CameraTest.CameraView[1]);
	//m_VBMD->ShowVBMD(ballModelID);
	//glPopMatrix();

	//DrawUI();
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	DrawReadme();
	if(!doangle)
		angle-=0.5f;

	glFlush ();													// Flush The GL Rendering Pipeline

	// ROACH
	if(domulti)
		glDisable(GL_MULTISAMPLE_ARB);
	glColor3f(1.0f,0.5f,0.0f);
	DrawFPS();
	glColor3f(1.0f,1.0f,1.0f);
	// ENDROACH
}
