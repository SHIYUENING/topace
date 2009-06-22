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
#include "VBMD.h"	
#include <windows.h>											// Header File For Windows
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glaux.h>											// Header File For The GLaux Library
#include "NeHeGL.h"												// Header File For NeHeGL
#include <math.h>												// We'll Need Some Math


// ROACH
#include "arb_multisample.h"
bool domulti = true;
bool doangle = true;
// ENDROACH

#pragma comment( lib, "opengl32.lib" )							// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )								// Search For GLu32.lib While Linking
#pragma comment( lib, "glaux.lib" )								// Search For GLaux.lib While Linking
#pragma comment( lib, "glew32.lib" )	
#pragma comment( lib, "glew32d.lib" )
#ifndef CDS_FULLSCREEN											// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4										// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors
LARGE_INTEGER t1,t2,feq,t3;//计算每桢运行时间相关
GL_Window*	g_window;
Keys*		g_keys;
int			g_nFPS = 0, g_nFrames = 0;							// FPS and FPS Counter
DWORD		g_dwLastFPS = 0;
char szTitle[256]={0};
int modelID[16];
int * pModelID=NULL;
int ModelNum=1;
int ModelNumLoaded=0;
float angle= 0.75f;
double oneframetime=0.0;//每桢运行时间，超过0.016游戏就不能保持全速了
double oneframetimeT=0.0;
double oneframetimelimit=1.0/60.0;//每桢最大时间
CLoadVBMD *m_VBMD = NULL;//VBMD模型对象
GLuint AsciiFontTexId;
GLuint base;
extern int winwidth,winheight;
float posX,posY,posZ;
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
	if( GetTickCount() - g_dwLastFPS >= 1000 )					// When A Second Has Passed...
	{
		g_dwLastFPS = GetTickCount();							// Update Our Time Variable
		g_nFPS = g_nFrames;										// Save The FPS
		g_nFrames = 0;											// Reset The FPS Counter
	}
	
	g_nFrames++;											
	sprintf( szTitle, "%4.8f time,%2.0d FPS %4.6f %4.6f %4.6f %4.6f" ,oneframetime,g_nFPS,angle,posX,posY,posZ);
	glPrints(0,winheight-16,winwidth,winheight,szTitle);
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
	QueryPerformanceFrequency(&feq);//每秒跳动次数
	QueryPerformanceCounter(&t2);//测后跳动次数
    if (t2.QuadPart >= t1.QuadPart)
	{
	    oneframetime=((double)(t2.QuadPart-t1.QuadPart))/((double)feq.QuadPart);//时间差秒
		
    }
	else
		return;
	//QueryPerformanceCounter(&t1);//测前跳动次数

	double SleepTime=(oneframetimelimit-oneframetime)*1000.0;
	while(SleepTime>2.0)
	{
		Sleep(1);
		QueryPerformanceFrequency(&feq);//每秒跳动次数
		QueryPerformanceCounter(&t2);//测后跳动次数
		if (t2.QuadPart >= t1.QuadPart)
			waitTime=((double)(t2.QuadPart-t1.QuadPart))/((double)feq.QuadPart);//时间差秒
		else
			return;
		SleepTime=(oneframetimelimit-waitTime)*1000.0;
	}
	QueryPerformanceFrequency(&feq);//每秒跳动次数
	QueryPerformanceCounter(&t2);//测后跳动次数
    if (t2.QuadPart >= t1.QuadPart)
	{
	    waitTime=((double)(t2.QuadPart-t1.QuadPart))/((double)feq.QuadPart);//时间差秒
		
    }
	else
		return;

	Delay(__int64((oneframetimelimit-waitTime)*1000000));
	QueryPerformanceCounter(&t1);//测前跳动次数
}

BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
{
	glewInit();
	m_VBMD = new CLoadVBMD;
	m_VBMD->m_IsSupportFBO=true;

	angle=-90.0f;
	posX=posY=posZ=0;
	posY=-500.0f;

	ModelNum=GetPrivateProfileInt("Set","ModelNum",50,".\\Model.ini");
	pModelID=new int[ModelNum];
	WIN32_FIND_DATA FindFileData = {0};
    char sTmp[256] = {0};
	sprintf(sTmp,"Data/Model/*.dds");
	HANDLE hFind = ::FindFirstFile(sTmp, &FindFileData);
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
				for(int i=0;i<strlen(FindFileData.cFileName);i++)
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



/*
	modelID[0]=m_VBMD->Init("Data/Model/ddm_2");
	modelID[1]=m_VBMD->Init("Data/Model/model03_2");
	modelID[2]=m_VBMD->Init("Data/Model/model03_12");
	modelID[3]=m_VBMD->Init("Data/Model/model03_23");
	modelID[4]=m_VBMD->Init("Data/Model/model03_52");
	modelID[5]=m_VBMD->Init("Data/Model/model03_53");
	modelID[6]=m_VBMD->Init("Data/Model/model03_54bbbbb");
	modelID[7]=m_VBMD->Init("Data/Model/model03_55");
	modelID[8]=m_VBMD->Init("Data/Model/model03_56");
	modelID[9]=m_VBMD->Init("Data/Model/model03_57");
	modelID[10]=m_VBMD->Init("Data/Model/model03_58");
	modelID[11]=m_VBMD->Init("Data/Model/hill2");
	modelID[12]=m_VBMD->Init("Data/Model/hill");*/
	g_window	= window;
	g_keys		= keys;

	BuildFont();
	glViewport(0 , 0,window->init.width ,window->init.height);	// Set Up A Viewport
	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glLoadIdentity();											// Reset The Projection Matrix
	gluPerspective(50, (float)window->init.width/(float)window->init.height, 10,  100000); // Set Our Perspective
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	glLoadIdentity();											// Reset The Modelview Matrix

	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing

	glShadeModel(GL_SMOOTH);									// Select Smooth Shading

	glClearColor(0.0f, 0.0f, 0.0f, 0.5);						// Set The Clear Color To Black
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	QueryPerformanceCounter(&t1);
	return TRUE;												// Return TRUE (Initialization Successful)
}

void Deinitialize (void)										// Any User DeInitialization Goes Here
{
}

void Update (DWORD milliseconds)								// Perform Motion Updates Here
{
	if(g_keys->keyDown ['A'] == TRUE)
		posX=posX-10.0f;
	if(g_keys->keyDown ['D'] == TRUE)
		posX=posX+10.0f;
	if(g_keys->keyDown ['W'] == TRUE)
		posY=posY-10.0f;
	if(g_keys->keyDown ['S'] == TRUE)
		posY=posY+10.0f;
	if(g_keys->keyDown ['Z'] == TRUE)
		posZ=posZ-10.0f;
	if(g_keys->keyDown ['X'] == TRUE)
		posZ=posZ+10.0f;
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
	LockFPS();
}

void Draw (void)												// Draw The Scene
{
	// ROACH
	if(domulti)
		glEnable(GL_MULTISAMPLE_ARB);							// Enable Our Multisampling
	// ENDROACH

	glClearColor(0.0f, 0.0f, 0.0f, 0.5);						// Set The Clear Color To Black
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity();											// Reset The View	
	
	
	
	//glRotatef(angle,1.f,0.f,0.f);
	glTranslatef(posX,posY,posZ);
	glRotatef(angle,0.f,1.f,0.f);
	for(int i=0;i<ModelNumLoaded;i++)
	m_VBMD->ShowVBMD(pModelID[i]);
/*
	for(float i=-10;i<10;i++)
		for(float j=-10;j<10;j++)
		{
			glPushMatrix();
			glTranslatef(i*2.0f,j*2.0f,-5.0f);
			
				glBegin(GL_QUADS);
				glColor3f(1.0f,0.0f,0.0f);glVertex3f(i,j,0.0f);
				glColor3f(0.0f,1.0f,0.0f);glVertex3f(i + 2.0f,j,0.0f);
				glColor3f(0.0f,0.0f,1.0f);glVertex3f(i + 2.0f,j + 2.0f,0.0f);
				glColor3f(1.0f,1.0f,1.0f);glVertex3f(i,j + 2.0f,0.0f);
				glEnd();
			glPopMatrix();
		}
*/
	if(!doangle)
		angle-=0.5f;

	glFlush ();													// Flush The GL Rendering Pipeline

	// ROACH
	if(domulti)
		glDisable(GL_MULTISAMPLE_ARB);
	DrawFPS();
	// ENDROACH
}
