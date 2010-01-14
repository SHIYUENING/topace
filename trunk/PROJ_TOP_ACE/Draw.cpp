#include"Draw.h"
#include <stdlib.h>
#include <GL/glew.h>
#include <math.h>
#include <stdio.h>	
#include "Glsl.h"
#include <lib3ds.h>
#include <string.h>	
#include "Load3DS.h"
#include "Font2D.h"
#include "Textures.h"
bool extern domultiR ;
bool extern doangleR ;
float extern angleR;
float extern Test3dsFrame;
float extern moveZ;
float extern moveY;
float extern moveX;
CFont2D * Font2D=NULL; 
bool Inited=false;
bool IsFirstInit=true;
LARGE_INTEGER TimeStart,TimeEnd,Timefeq,RunTimeStart,RunTimeEnd;
int FPSNum=0;
int FPSNumShow=0; 
wchar_t ShowFPS[64]={0};
CLoad3DS  * Test3DSModel=NULL;
Textures * Test3DSTex=NULL;
Textures * Test3dsModel_Glass=NULL;
void InitDraw()
{
	glewInit();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.5f, 0.5f, 0.5);	
	if(!Test3DSModel)
	{
		Test3DSModel=new CLoad3DS;
		Test3DSModel->Loadfile("data/model/test/Test3dsModel.3DS");
		Test3DSModel->LoadToVRAM();
	}
	if(!Test3DSModel->isVRAM)
	{
		Test3DSModel->LoadToVRAM();
	}
	if(!Test3DSTex)
	{
		Test3DSTex =new Textures;
		Test3DSTex->loadfile("data/model/test/Test3dsModel");
		Test3DSTex->LoadToVRAM(GL_LINEAR_MIPMAP_LINEAR);
	}
	if(!Test3DSTex->isVRAM())
	{
		Test3DSTex->LoadToVRAM(GL_LINEAR_MIPMAP_LINEAR);
	}
	if(!Test3dsModel_Glass)
	{
		Test3dsModel_Glass =new Textures;
		Test3dsModel_Glass->loadfile("data/model/test/Test3dsModel_Glass");
		Test3dsModel_Glass->LoadToVRAM(GL_LINEAR_MIPMAP_LINEAR);
	}
	if(!Test3dsModel_Glass->isVRAM())
	{
		Test3dsModel_Glass->LoadToVRAM(GL_LINEAR_MIPMAP_LINEAR);
	}
	//if(Inited)
	//	return;
	//Inited=true;
	if((Test3DSModel)&&(Test3dsModel_Glass))
	{
		Test3DSModel->GrassTexID=Test3dsModel_Glass->TexID;
		Test3DSModel->DiffuseTexID=Test3DSTex->TexID;
	}
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
		//Font2D->inputTxt("ab");
	}
	swprintf_s(ShowFPS,64,L"-");
	QueryPerformanceCounter(&TimeStart);
	if(IsFirstInit)
	{
		QueryPerformanceCounter(&RunTimeStart);
		IsFirstInit=false;
	}
	QueryPerformanceFrequency(&Timefeq);

}
void ClearVRAM()
{
	if(Test3DSModel)
	{
		Test3DSModel->Del_VRAM();
	}
	if(Test3DSTex)
	{
		Test3DSTex->Del_VRAM();
	}
	if(Test3dsModel_Glass)
	{
		Test3dsModel_Glass->Del_VRAM();
	}
	if(Font2D)
	{
		delete Font2D;
		Font2D=NULL;
	}
}
void DeinitDraw()
{
	if(Font2D)
	{
		delete Font2D;
		Font2D=NULL;
	}
	Inited=false;
	if(Test3DSModel)
	{
		delete Test3DSModel;
		Test3DSModel = NULL;
	}
	if(Test3DSTex)
	{
		delete Test3DSTex;
		Test3DSTex=NULL;
	}
	if(Test3dsModel_Glass)
	{
		delete Test3dsModel_Glass;
		Test3dsModel_Glass=NULL;
	}
}
void Draw()
{
	QueryPerformanceFrequency(&Timefeq);
	QueryPerformanceCounter(&TimeEnd);
	QueryPerformanceCounter(&RunTimeEnd);
	float runtime;
	if(double((TimeEnd.QuadPart-TimeStart.QuadPart)/Timefeq.QuadPart)>=1.0)
	{
		QueryPerformanceCounter(&TimeStart);
		FPSNumShow=FPSNum;
		FPSNum=0;
		runtime=float((RunTimeEnd.QuadPart-RunTimeStart.QuadPart)/Timefeq.QuadPart);
		swprintf_s(ShowFPS,64,L"FPS:%d",FPSNumShow);
		Font2D->inputTxt(ShowFPS);
	}
	FPSNum=FPSNum+1;


	// ROACH
	if(domultiR)
		glEnable(GL_MULTISAMPLE_ARB);							// Enable Our Multisampling
	// ENDROACH
					// Set The Clear Color To Black
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity();											// Reset The View	

	glTranslatef(moveX,moveY,-150.0f-moveZ);
	glRotatef(angleR,0.0f,1.0f,0.0f);
	//glRotatef(-90,1.0f,0.0f,0.0f);
	//glDisable( GL_TEXTURE_2D );
	//glColor3f(1.0f,0.0f,0.0f);
	if(Test3DSTex)
		glBindTexture(GL_TEXTURE_2D, Test3DSTex->TexID);
	if(Test3DSModel)
		Test3DSModel->Render(Test3dsFrame);
	/*
	//
	for(float i=-3;i<3;i++)
		for(float j=-3;j<3;j++)
		{
			glPushMatrix();
			glTranslatef(i*2.0f,j*2.0f,-5.0f);
			glRotatef(angleR,0.f,0.f,1.f);
				glBegin(GL_QUADS);
				glColor3f(1.0f,0.0f,0.0f);glVertex3f(i,j,0.0f);glTexCoord2d(0,0);
				glColor3f(0.0f,1.0f,0.0f);glVertex3f(i + 2.0f,j,0.0f);glTexCoord2d(1,0);
				glColor3f(0.0f,0.0f,1.0f);glVertex3f(i + 2.0f,j + 2.0f,0.0f);glTexCoord2d(1,1);
				glColor3f(1.0f,1.0f,1.0f);glVertex3f(i,j + 2.0f,0.0f);glTexCoord2d(0,1);
				glEnd();
			glPopMatrix();
		}
*/
	
	//if(doangleR)
	//	angleR+=0.05f;

	//glFlush ();													// Flush The GL Rendering Pipeline
	glEnable( GL_TEXTURE_2D );
	Font2D->DrawTXT(800,600,0,0,24,24,800,3);

	if(domultiR)
	glDisable(GL_MULTISAMPLE_ARB);
	// ROACH
	

	// ENDROACH

}
