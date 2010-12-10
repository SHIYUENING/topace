#include"Draw.h"
#include <stdlib.h>
#include <GL/glew.h>
#include <math.h>
#include <stdio.h>	
#include "Glsl.h"
//#include <lib3ds.h>
#include <string.h>	
//#include "Load3DS.h"
#include "Font2D.h"
#include "Textures.h"
#include "IniFile.h"
#include "FBO.h"
//#include "UnitMath.h"
#include "TopAceModel.h"
#include "ExchangeThread.h"
#include "DrawQUAD.h"
#include "Common.h"
float extern angleR;
float extern Test3dsFrame;
float extern maxFreme;
float extern moveZ;
float extern moveY;
float extern moveX;
int extern ReadingThreadNum;
CFont2D * Font2D=NULL; 
bool Inited=false;
bool IsFirstInit=true;
LARGE_INTEGER TimeStart,TimeEnd,Timefeq,RunTimeStart,RunTimeEnd,CPUTestStart,CPUTestEnd;
int FPSNum=0;
int FPSNumShow=0; 
wchar_t ShowFPS[64]={0};
//CLoad3DS  * Test3dsModelHanger=NULL;
extern tGameSet GameSet;
int OmniLightNumBase=0;
int SpotLightNumBase=0;
CTopAceModel TopAceModelTest;
Textures LoadingTex;
extern HDC SwapHdc; 
//CUnitMath ViewUnit;
//CUnitMath UnitMath1;
float PosOrgY=0.0f;
float PosOrgZ=0.0f;
__m128 MatrixDrawTestUnit[4];
CExchangeThread ThreadDataDraw;
//float MatrixTMPF4X4[16];
//GLfloat DrawMatrixTMP[16];
GLuint TestModelVAO=0;
struct _TestMeshVBOID
{
	unsigned int VerticeID;
	unsigned int NormalID;
	unsigned int TexCoordID;
	unsigned int ColorID;
	unsigned int FaceID;
};
_TestMeshVBOID TestMeshVBOID;

void DrawLoadingTex(Textures * pLoadingTex)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawQUADEX(pLoadingTex->TexID,GameSet.winW/2-GameSet.winH/2,GameSet.winW/2+GameSet.winH/2,0,GameSet.winH,GameSet.winW,GameSet.winH);
	SwapBuffers (SwapHdc);	
}
void InitTestLight()
{
	_OmniLightData SetOmniLightData;
	SetOmniLightData.Color[0]=0.7f;
	SetOmniLightData.Color[1]=0.7f;
	SetOmniLightData.Color[2]=0.7f;
	SetOmniLightData.Color[3]=1.0f;
	SetOmniLightData.Pos[0]=0.0f;
	SetOmniLightData.Pos[1]=0.0f;
	SetOmniLightData.Pos[2]=0.0f;
	SetOmniLightData.Pos[3]=0.0f;
	CO_SetOmniLight(&SetOmniLightData,0);

	_MaterialData MaterialData;
	MaterialData.emission[0]=0.0f;
	MaterialData.emission[1]=0.0f;
	MaterialData.emission[2]=0.0f;
	MaterialData.emission[3]=5.0f;//shininess
	MaterialData.diffuse[0]=0.7f;
	MaterialData.diffuse[1]=0.7f;
	MaterialData.diffuse[2]=0.7f;
	MaterialData.diffuse[3]=1.0f;
	MaterialData.specular[0]=0.5f;
	MaterialData.specular[1]=0.5f;
	MaterialData.specular[2]=0.5f;
	MaterialData.specular[3]=1.0f;
	CO_SetMaterial(&MaterialData);

	GLfloat GlobalAmbient_Set[]={0.7f,0.7f,0.7f,1.0f};
	CO_SetGlobalAmbient(GlobalAmbient_Set);
	OmniLightNumBase=1;

	/*
	GLfloat LightPos[]={0.0f,00000.0f,0.0f,0.0f};
	glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
	GLfloat mat_specular[]={0.5f,0.5f,0.5f,1.0f};
	GLfloat mat_ambient[]={0.7f,0.7f,0.7f,1.0f};
	GLfloat mat_diffuse[]={0.7f,0.7f,0.7f,1.0f};
	GLfloat mat_shininess[]={5.0f};
	glLightfv(GL_LIGHT0,GL_SPECULAR,mat_specular);
	glLightfv(GL_LIGHT0,GL_AMBIENT,mat_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,mat_diffuse);
	glLightfv(GL_LIGHT0,GL_SHININESS,mat_shininess);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mat_shininess);
	*/
}
void InitDraw()
{
	glewInit();

	WritePrivateProfileString("PC Info","Video Card",(char *)glGetString(GL_RENDERER),".\\gameset.ini");
	WritePrivateProfileString("PC Info","GL_VERSION",(char *)glGetString(GL_VERSION),".\\gameset.ini");
	//WritePrivateProfileString("PC Info","GL_EXTENSIONS",(char *)glGetString(GL_EXTENSIONS),".\\gameset.ini");
	if(!glewIsSupported("GL_ARB_tessellation_shader")) GameSet.Light=3;
	if (!glewIsSupported("GL_VERSION_3_0")) GameSet.Light=2;
	if (!glewIsSupported("GL_VERSION_2_0"))
	{
		MessageBox( NULL, "Please Updata Video Card Driver", "OpenGL Ver error", MB_OK|MB_ICONEXCLAMATION );
		GameSet.Light=1;
	}
	if((!glewIsSupported("GL_ARB_pixel_buffer_object"))&&(!glewIsSupported("GL_EXT_pixel_buffer_object")))
	{
		GameSet.SSAO=0;
		GameSet.Light=2;
	}
	if (!glewIsSupported("GL_ARB_texture_float"))
		GameSet.Bloom=0;

	Textures::LoadDefineTex();
	LoadingTex.loadfile(L"data/loading");
	LoadingTex.LoadToVRAM(GL_LINEAR);
	DrawLoadingTex(&LoadingTex);
	if(GameSet.Light>1)
		InitFBO(GameSet.winW,GameSet.winH,GameSet.Bloom);
	InitGLSL();
	CDDS::SetAFNum(GameSet.AF);
	InitTestModel();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	//glPolygonMode(GL_BACK,GL_LINE);
	glClearColor(0.0f, 0.5f, 0.5f, 0.0f);
	InitTestLight();


	TopAceModelTest.ReadTAMFile(L"data/1234.tam");
	TopAceModelTest.LoadToVRAM();
	/*if(TopAceModelTest.TAM_FileData)
	{
		PosOrgZ=2*max(max(max(abs(TopAceModelTest.pTAM_FileHead->BoxMax[0]),abs(TopAceModelTest.pTAM_FileHead->BoxMin[0])),
			max(abs(TopAceModelTest.pTAM_FileHead->BoxMax[1]),abs(TopAceModelTest.pTAM_FileHead->BoxMin[1]))),
			max(abs(TopAceModelTest.pTAM_FileHead->BoxMax[2]),abs(TopAceModelTest.pTAM_FileHead->BoxMin[2])));
		PosOrgY=-(TopAceModelTest.pTAM_FileHead->BoxMax[2]-(TopAceModelTest.pTAM_FileHead->BoxMax[2]-TopAceModelTest.pTAM_FileHead->BoxMin[2])/2.0f);
	}*/
	/*
	if(GameSet.Light==1)
	{
		glEnable(GL_LIGHTING);
		glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
		//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
		//glEnable(GL_LIGHT0);
	}
	if(!Test3dsModelHanger)
	{
		
		Test3dsModelHanger=new CLoad3DS;
		//Test3dsModelHanger->Loadfile("data/model/hanger/Test3dsModelHanger.3DS");
		//if(!Test3dsModelHanger->isRAM)
		//	MessageBox( NULL, "Cannot open data/model/hanger/Test3dsModelHanger.3DS!", "ERROR",MB_OK | MB_ICONEXCLAMATION );
		Test3dsModelHanger->LoadToVRAM();
		if(Test3dsModelHanger->Model3ds)
			maxFreme=float(Test3dsModelHanger->Model3ds->frames);
	}
	if(!Test3dsModelHanger->isVRAM)
	{
		Test3dsModelHanger->LoadToVRAM();
	}*/

	if(!Font2D)
	{
		char szPath[MAX_PATH];
		GetWindowsDirectory(szPath,sizeof(szPath));
		char FontPath[MAX_PATH];
		sprintf(FontPath,"%s/Fonts/simsun.ttc",szPath);
		Font2D=new CFont2D;
		Font2D->LoadFont(FontPath,32,32);
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
	/*if(Test3dsModelHanger)
	{
		Test3dsModelHanger->Del_VRAM();
	}*/
	if(Font2D)
	{
		delete Font2D;
		Font2D=NULL;
	}
}
void DeinitDraw()
{
	if(GameSet.Light>1)
		DeinitFBO();
	DeinitGLSL();
	if(Font2D)
	{
		delete Font2D;
		Font2D=NULL;
	}
	TopAceModelTest.DeleteVRAM();
	Inited=false;
	DeinitTestModel();
}
void UnitMatrix()
{
	/*float NodesFrameIn[MAX_TYPE_3DS_NODE];
	NodesFrameIn[0]=Test3dsFrame;
	for(int i=1;i<MAX_TYPE_3DS_NODE;i++)
		NodesFrameIn[i]=Test3dsFrame;*/
	/*if(Test3dsModelHanger)
	if(Test3dsModelHanger->Model3ds)
	{
		Test3dsModelHanger->ModelMatrix(NodesFrameIn,Test3dsFrame);
	}*/
}
void SetCameraMatrix()
{
	__m128 MatrixOut[4];
	ThreadExchangeToDraw(&ThreadDataDraw);
	Easy_matrix_copy(MatrixOut,ThreadDataDraw.DataList[1].Matrix);
	Easy_matrix_copy(MatrixDrawTestUnit,ThreadDataDraw.DataList[2].Matrix);
	
	Easy_matrix_inv(MatrixOut,MatrixOut);
	glLoadMatrixf(&(MatrixOut[0].m128_f32[0]));
	CO_SetMMatrix(MatrixOut[0].m128_f32);
	CO_MultMMatrix(ThreadDataDraw.DataList[4].Matrix);
}
void SetLights()
{
	//OmniLightNumBase=0;
	//SpotLightNumBase=0;
	/*if(Test3dsModelHanger)
	if(Test3dsModelHanger->Model3ds)
	{
		Test3dsModelHanger->SetLightsPos(OmniLightNumBase+SpotLightNumBase);
		OmniLightNumBase+=Test3dsModelHanger->OmniLightNum;
		SpotLightNumBase+=Test3dsModelHanger->SpotLightNum;
	}*/
	/*if((OmniLightNumBase+SpotLightNumBase)==0)
	{
		OmniLightNumBase=1;
		float TMPLightColor[4]={0.75,0.75,0.75,1.0};
		float TMPLightPos[4]={0.0,-3000.0,0000.0,1.0};
		//glEnable(GL_LIGHT0);
		//glLightfv(GL_LIGHT0,GL_POSITION,TMPLightPos);
		//glLightfv(GL_LIGHT0,GL_SPECULAR,TMPLightColor);
		//glLightfv(GL_LIGHT0,GL_DIFFUSE,TMPLightColor);
		//glLightfv(GL_LIGHT0,GL_AMBIENT,TMPLightColor);
	}*/
}
void RenderUnits(bool OnlySelfIllumUnit=false)
{
	/*if(Test3dsModelHanger)
	if(Test3dsModelHanger->isRAM)
	{
		Test3dsModelHanger->OnlySelfIllum=OnlySelfIllumUnit;
		Test3dsModelHanger->Render();
	}*/
}
void RenderPass2Units()
{
	//FBOS_Star_Begin();
	//RenderUnits(true);
	//FBOS_Star_End();
	
	if(GameSet.Bloom>0)
		FBOS_BLOOM();
	//if(GameSet.SSAO>0)
	//	FBOS_SSAO();
	//TestTexFBO();
}
void DrawFPS(float oneframetimepointCPUSYS,float oneframetimepointGPU)
{
	float oneframetimepointCPUDraw=0.0f;
	oneframetimepointCPUDraw=(float(CPUTestEnd.QuadPart-CPUTestStart.QuadPart)/float(Timefeq.QuadPart));
	if(GameSet.FPS>0)
		oneframetimepointCPUDraw=100.0f*oneframetimepointCPUDraw/(1.0f/float(GameSet.FPS));
	else
		oneframetimepointCPUDraw=100.0f;
	QueryPerformanceFrequency(&Timefeq);
	QueryPerformanceCounter(&TimeEnd);
	QueryPerformanceCounter(&RunTimeEnd);
	float runtime;
	if((double(TimeEnd.QuadPart-TimeStart.QuadPart)/double(Timefeq.QuadPart))>=1.0)
	{
		QueryPerformanceCounter(&TimeStart);
		FPSNumShow=FPSNum;
		FPSNum=0;
		runtime=float((RunTimeEnd.QuadPart-RunTimeStart.QuadPart)/Timefeq.QuadPart);
		swprintf_s(ShowFPS,64,L"FPS:%d, CPU:%3.3f%%, CPUDraw:%3.3f%%, GPU:%3.3f%%",FPSNumShow,oneframetimepointCPUSYS,oneframetimepointCPUDraw,oneframetimepointGPU);
		Font2D->inputTxt(ShowFPS);
	}
	FPSNum=FPSNum+1;
	glColor4f(1.0f,1.0f,0.0f,1.0f);
	glEnable( GL_TEXTURE_2D );
	Font2D->DrawTXT(GameSet.winW,GameSet.winH,0,0,24,24,GameSet.winW,3);
	glColor4f(1.0f,1.0f,1.0f,1.0f);
}
void DrawTestLines()
{
	glDisable( GL_TEXTURE_2D );
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f( 0.0f, 0.0f, 100000.0f);
		glVertex3f( 0.0f, 0.0f,      0.0f);

		glColor3f(1.0f,0.0f,1.0f);
		glVertex3f( 0.0f, 0.0f,      0.0f);
		glVertex3f( 0.0f, 0.0f,-100000.0f);

		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f( 0.0f, 100000.0f, 0.0f);
		glVertex3f( 0.0f,      0.0f, 0.0f);

		glColor3f(0.0f,0.0f,0.0f);
		glVertex3f( 0.0f,      0.0f, 0.0f);
		glVertex3f( 0.0f,-100000.0f, 0.0f);

		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 100000.0f, 0.0f, 0.0f);
		glVertex3f(      0.0f, 0.0f, 0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-100000.0f, 0.0f, 0.0f);
		glVertex3f(      0.0f, 0.0f, 0.0f);


		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f( 100.0f, 100.0f, 100.0f);
		glVertex3f(-100.0f, 100.0f, 100.0f);

		glVertex3f( 100.0f, 100.0f, 100.0f);
		glVertex3f( 100.0f,-100.0f, 100.0f);

		glVertex3f(-100.0f,-100.0f, 100.0f);
		glVertex3f(-100.0f, 100.0f, 100.0f);

		glVertex3f(-100.0f,-100.0f, 100.0f);
		glVertex3f( 100.0f,-100.0f, 100.0f);


		glVertex3f( 100.0f, 100.0f,-100.0f);
		glVertex3f(-100.0f, 100.0f,-100.0f);

		glVertex3f( 100.0f, 100.0f,-100.0f);
		glVertex3f( 100.0f,-100.0f,-100.0f);

		glVertex3f(-100.0f,-100.0f,-100.0f);
		glVertex3f(-100.0f, 100.0f,-100.0f);

		glVertex3f(-100.0f,-100.0f,-100.0f);
		glVertex3f( 100.0f,-100.0f,-100.0f);



		glVertex3f( 100.0f, 100.0f,-100.0f);
		glVertex3f( 100.0f, 100.0f, 100.0f);

		glVertex3f(-100.0f, 100.0f,-100.0f);
		glVertex3f(-100.0f, 100.0f, 100.0f);

		glVertex3f( 100.0f,-100.0f,-100.0f);
		glVertex3f( 100.0f,-100.0f, 100.0f);

		glVertex3f(-100.0f,-100.0f,-100.0f);
		glVertex3f(-100.0f,-100.0f, 100.0f);

	glEnd();

	glEnable( GL_TEXTURE_2D );
}
void Draw(float oneframetimepointCPUSYS,float oneframetimepointGPU)
{
	//glGetFloatv(GL_MODELVIEW_MATRIX,&MatrixTMPF4X4[0]);

	glClear ( GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);//
	//glEnable(GL_MULTISAMPLE_ARB);

	DrawTestLines();
	if(GameSet.Light==1) glEnable(GL_LIGHTING);
	GLSL_Enable_PhoneLight(OmniLightNumBase,SpotLightNumBase);

	//glGetFloatv(GL_PROJECTION_MATRIX,&DrawMatrixTMP[0]);
	//SetPMatrix(DrawMatrixTMP);
	

	if(GameSet.Light>=4)
		glPatchParameteri(GL_PATCH_VERTICES, 3);
	//glLoadMatrixf(&MatrixTMPF4X4[0]);
	//glMultMatrixf(MatrixDrawTestUnit[0].m128_f32);

	TopAceModelTest.Draw();
	/*CO_MultMMatrix(ThreadDataDraw.DataList[3].Matrix);
	GLSL_SetMMatrixToGlsl();
	GLSL_SetMVPMatrixToGlsl();
	DrawTestModel(GameSet.Light>=4?GL_PATCHES:GL_TRIANGLES);
	*/
	GLSL_Disable();
	
	if(GameSet.Light==1) glDisable(GL_LIGHTING);
	
	RenderPass2Units();
	DrawFPS(oneframetimepointCPUSYS, oneframetimepointGPU);

	glDisable(GL_MULTISAMPLE_ARB);
	QueryPerformanceCounter(&CPUTestStart);
	UnitMatrix();
	SetCameraMatrix();
	SetLights();
	Test_matrix();
	TopAceModelTest.FrameTAMBoneMatrixs(Test3dsFrame);
	QueryPerformanceCounter(&CPUTestEnd);
}
void InitTestModel()
{
	int TestModelFaces[]={
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17
	};
	float TestModelPos[]={
			0.0f,   0.0f,-050.0f,
			050.0f,   0.0f, 050.0f,
			0.0f, 050.0f, 050.0f,

			0.0f,   0.0f,-050.0f,
			-050.0f,   0.0f, 050.0f,
			0.0f, 050.0f, 050.0f,

			0.0f,   0.0f,-050.0f,
			050.0f,   0.0f, 050.0f,
			0.0f,-050.0f, 050.0f,

			0.0f,   0.0f,-050.0f,
			-050.0f,   0.0f, 050.0f,
			0.0f,-050.0f, 050.0f,

			-050.0f,   0.0f, 050.0f,
			0.0f,-050.0f, 050.0f,
			0.0f, 050.0f, 050.0f,

			0.0f, 050.0f, 050.0f,
			050.0f,   0.0f, 050.0f,
			0.0f,-050.0f, 050.0f
	};
	float TestModelNormal[]={
			0.0f, 0.0f,-1.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			0.0f, 0.0f,-1.0f,
			-1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			0.0f, 0.0f,-1.0f,
			1.0f, 0.0f, 0.0f,
			0.0f,-1.0f, 0.0f,

			0.0f, 0.0f,-1.0f,
			-1.0f, 0.0f, 0.0f,
			0.0f,-1.0f, 0.0f,
	
			-1.0f, 0.0f, 0.0f,
			0.0f,-1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			0.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f,-1.0f, 0.0f
	};
	float TestModelColor[]={
			0.0f,1.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,

			0.0f,1.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,

			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,

			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,

			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,

			0.0f,1.0f,0.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f
	};

	float TestModelTexCoord[]={
		0.0f,   0.0f,
		1.0f,   0.0f,
		0.0f,   1.0f,

		0.0f,   0.0f,
		1.0f,   0.0f,
		0.0f,   1.0f,

		0.0f,   0.0f,
		1.0f,   0.0f,
		0.0f,   1.0f,

		0.0f,   0.0f,
		1.0f,   0.0f,
		0.0f,   1.0f,

		0.0f,   0.0f,
		1.0f,   0.0f,
		0.0f,   1.0f,

		0.0f,   0.0f,
		1.0f,   0.0f,
		0.0f,   1.0f
	};
	
	glGenBuffersARB( 1,&TestMeshVBOID.VerticeID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.VerticeID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(TestModelPos), TestModelPos, GL_STATIC_DRAW_ARB );
	glGenBuffersARB( 1,&TestMeshVBOID.NormalID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.NormalID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(TestModelNormal), TestModelNormal, GL_STATIC_DRAW_ARB );
	glGenBuffersARB( 1,&TestMeshVBOID.ColorID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.ColorID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(TestModelColor), TestModelColor, GL_STATIC_DRAW_ARB );
	glGenBuffersARB( 1,&TestMeshVBOID.TexCoordID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.TexCoordID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(TestModelTexCoord), TestModelTexCoord, GL_STATIC_DRAW_ARB );
	//glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glGenBuffersARB( 1,&TestMeshVBOID.FaceID);
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, TestMeshVBOID.FaceID );
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER, sizeof(TestModelFaces), TestModelFaces, GL_STATIC_DRAW_ARB );
	
	glGenVertexArrays(1,&TestModelVAO);
	glBindVertexArray(TestModelVAO);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.VerticeID );
	glVertexAttribPointer(AbLoc_Pos,3,GL_FLOAT,0,0,0);
	glEnableVertexAttribArray(AbLoc_Pos);
	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.NormalID );
	glVertexAttribPointer(AbLoc_Normal,3,GL_FLOAT,0,0,0);
	glEnableVertexAttribArray(AbLoc_Normal);
	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.ColorID );
	glVertexAttribPointer(AbLoc_Color,4,GL_FLOAT,0,0,0);
	glEnableVertexAttribArray(AbLoc_Color);

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.TexCoordID );
	glVertexAttribPointer(AbLoc_Tex0,2,GL_FLOAT,0,0,0);
	glEnableVertexAttribArray(AbLoc_Tex0);
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, TestMeshVBOID.FaceID );
	glBindVertexArray(0);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, 0);

}
void DrawTestModel(unsigned int TestModelDrawMode)
{
	glBindTexture(GL_TEXTURE_2D, LoadingTex.TexID);//
	//glDisable( GL_TEXTURE_2D );
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glBindVertexArray(TestModelVAO);
    glDrawElements(TestModelDrawMode, 18, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(AbLoc_Color);
	glDisableVertexAttribArray(AbLoc_Normal);
	glDisableVertexAttribArray(AbLoc_Pos);
	glDisableVertexAttribArray(AbLoc_Tex0);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_CULL_FACE);
}
void DeinitTestModel()
{
	glDeleteBuffersARB(1,&TestMeshVBOID.VerticeID);
	glDeleteBuffersARB(1,&TestMeshVBOID.NormalID);
	glDeleteBuffersARB(1,&TestMeshVBOID.ColorID);
	glDeleteBuffersARB(1,&TestMeshVBOID.TexCoordID);
}