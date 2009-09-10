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
LARGE_INTEGER t1,t2,feq,t3;//����ÿ������ʱ�����
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
float Updown= 0.0f;
float angle2=0.0f;
double oneframetime=0.0;//ÿ������ʱ�䣬����0.016��Ϸ�Ͳ��ܱ���ȫ����
double oneframetimeT=0.0;
double oneframetimelimit=1.0/60.0;//ÿ�����ʱ��
CLoadVBMD *m_VBMD = NULL;//VBMDģ�Ͷ���
GLuint AsciiFontTexId;
GLuint base;
extern int winwidth,winheight;
extern char * LoadCameraName;
float posX,posY,posZ;
Transform MView(Vector3d(0, 0, -40));//�۲����
Transform MWorld;//�������
Transform MFighter;//���
Transform Msky;
CSkyBox SkyBox;
extern float eyePositionSea[3];
extern GLuint AmbientReflectiveTexture;
extern bool ShaderWater;//�Ƿ�ʹ��shader
GLuint SeaTexID=0;
float globalAmbientGL[4]={0.3f,0.3f,0.3f,1.0f};
float lightColor[4]={0.7f,0.7f,0.7f,1.0f};
float lightPosition[]= { 0.0f, 0.0f, 2.0f };
CMd5Camera CMd5CameraTest;
Missledata ViewPos;
Transform ViewTo;
double Getrotation(Transform& Input);
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
	glEnable(GL_BLEND);
	if( GetTickCount() - g_dwLastFPS >= 1000 )					// When A Second Has Passed...
	{
		g_dwLastFPS = GetTickCount();							// Update Our Time Variable
		g_nFPS = g_nFrames;										// Save The FPS
		g_nFrames = 0;											// Reset The FPS Counter
	}
	
	g_nFrames++;											
	sprintf( szTitle, "%4.8f time,%2.0d FPS MX%4.0d MY%4.0d %4.2f %4.2f %4.2f %4.2f" ,oneframetime,g_nFPS,mouse_x,mouse_y,angle,(float)MFighter.RefPos()(0),(float)MFighter.RefPos()(1),(float)MFighter.RefPos()(2));
	glPrints(0,winheight-16,winwidth,winheight,szTitle);
	char ShowMoveSpeed[32]={0};
	sprintf(ShowMoveSpeed,"Move Speed:%4.2f",movespeed);
	glPrints(0,winheight-32,winwidth,winheight,ShowMoveSpeed);
	
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
	QueryPerformanceFrequency(&feq);//ÿ����������
	QueryPerformanceCounter(&t2);//�����������
    if (t2.QuadPart >= t1.QuadPart)
	{
	    oneframetime=((double)(t2.QuadPart-t1.QuadPart))/((double)feq.QuadPart);//ʱ�����
		
    }
	else
		return;
	//QueryPerformanceCounter(&t1);//��ǰ��������

	double SleepTime=(oneframetimelimit-oneframetime)*1000.0;
	while(SleepTime>2.0)
	{
		Sleep(1);
		QueryPerformanceFrequency(&feq);//ÿ����������
		QueryPerformanceCounter(&t2);//�����������
		if (t2.QuadPart >= t1.QuadPart)
			waitTime=((double)(t2.QuadPart-t1.QuadPart))/((double)feq.QuadPart);//ʱ�����
		else
			return;
		SleepTime=(oneframetimelimit-waitTime)*1000.0;
	}
	QueryPerformanceFrequency(&feq);//ÿ����������
	QueryPerformanceCounter(&t2);//�����������
    if (t2.QuadPart >= t1.QuadPart)
	{
	    waitTime=((double)(t2.QuadPart-t1.QuadPart))/((double)feq.QuadPart);//ʱ�����
		
    }
	else
		return;

	Delay(__int64((oneframetimelimit-waitTime)*1000000));
	QueryPerformanceCounter(&t1);//��ǰ��������
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
	m_VBMD = new CLoadVBMD;
	m_VBMD->m_IsSupportFBO=true;

	loadmodels();
	//angle=-90.0f;
	posX=posY=posZ=0;
	//posY=-500.0f;
	
	InitCG();

	SkyBox.Init();
	AmbientReflectiveTexture=SkyBox.SunCubeID;
	CDDS loadDDS;
	SeaTexID=loadDDS.loadCompressedTexture("Data/sea.dds",GL_LINEAR_MIPMAP_LINEAR);

	//CMd5CameraTest.LoadCamera("Data/123.md5camera");
	CMd5CameraTest.LoadCamera(LoadCameraName);
	

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

	glClearColor(0.0f, 0.0f, 0.0f, 0.5);						// Set The Clear Color To Black
	glEnable(GL_TEXTURE_2D);


	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbientGL);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,lightColor);
	glLightfv(GL_LIGHT1,GL_SPECULAR,lightColor);
	ViewPos.UDMplane.Reset();
	ViewPos.UDMplane.TranslateInternal(Vector3d(1979.6632,-583.7316,-1310.2708));
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

void Deinitialize (void)										// Any User DeInitialization Goes Here
{
}

void Update (DWORD milliseconds)								// Perform Motion Updates Here
{
	Updown=angle=angle2=posX=posY=posZ=0.0f;
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
		angle=-1.0f;
	if(g_keys->keyDown [VK_RIGHT] == TRUE)
		angle=+1.0f;
	if(g_keys->keyDown [VK_UP] == TRUE)
		Updown=-1.0f;
		//posY=-5.0f*(1.0f*doangle+0.05f);
	if(g_keys->keyDown [VK_DOWN] == TRUE)
		Updown=+1.0f;
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
		ToggleFullscreen (g_window);							// Toggle Fullscreen Mode
	}
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
	CMd5CameraTest.Play(double(t3.QuadPart)/double(feq.QuadPart));
	if(domulti)
		glEnable(GL_MULTISAMPLE_ARB);							// Enable Our Multisampling
	// ENDROACH

	glClearColor(0.0f, 0.0f, 0.0f, 0.5);						// Set The Clear Color To Black
	glClear (GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity();											// Reset The View	
	
	//MFighter.Reset();
	
	ViewPos.UDMplane.Reset();
	ViewPos.UDMplane.Translate(Vector3d(CMd5CameraTest.CameraPos[0],CMd5CameraTest.CameraPos[2],-CMd5CameraTest.CameraPos[1]));

	ViewPos.TurnTo(Vector3d(CMd5CameraTest.CameraView[0],CMd5CameraTest.CameraView[2],-CMd5CameraTest.CameraView[1]));
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
	if(CMd5CameraTest.numFrames>0)
		MFighter=ViewPos.UDMplane;
    MView = (MWorld * MFighter).Invert();
	glLoadMatrixd(MView.Matrix4());
	DrawSky(MFighter);
	
	
	//glDisable(GL_TEXTURE_2D);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT1);
	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
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
	//glPushMatrix();	
	//glTranslated(CMd5CameraTest.CameraView[0],CMd5CameraTest.CameraView[2],-CMd5CameraTest.CameraView[1]);
	//m_VBMD->ShowVBMD(ballModelID);
	//glPopMatrix();

	DrawUI();
	if(!doangle)
		angle-=0.5f;

	glFlush ();													// Flush The GL Rendering Pipeline

	// ROACH
	if(domulti)
		glDisable(GL_MULTISAMPLE_ARB);
	glColor3f(1.0f,1.0f,1.0f);
	DrawFPS();
	// ENDROACH
}