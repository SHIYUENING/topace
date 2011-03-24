#include"Draw.h"
#include "UnitsList.h"
#include <stdlib.h>
#include <GL/glew.h>
#include <math.h>
#include <stdio.h>	
#include "Glsl.h"
//#include <lib3ds.h>
#include <string.h>	
//#include "Load3DS.h"
#include "Font2D.h"
#include "FONTS2D.h"
#include "Textures.h"
#include "IniFile.h"
#include "FBO.h"
//#include "UnitMath.h"
#include "TopAceModel.h"
#include "ExchangeThread.h"
#include "DrawQUAD.h"
#include "Common.h"
#include "TAMFT3D.h"
float extern angleR;
float extern Test3dsFrame;
float extern maxFreme;
float extern moveZ;
float extern moveY;
float extern moveX;
int extern ReadingThreadNum;
CFont2D * Font2D=NULL; 
CFONTS2D FONTS2D;
CTAMFT3D TAMFT3D;
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
float PosOrgY=0.0f;
float PosOrgZ=0.0f;
extern float moveZSpeed;
__m128 MatrixDrawTestUnit[4];
CExchangeThread ThreadDataDraw;
GLuint TestModelVAO=0;
extern GLuint ShadowFBOID;
extern GLuint ShadowTex;
extern GLuint ShadowTexDepth;
extern int ShadowTexSize;
struct _TestMeshVBOID
{
	unsigned int VerticeID;
	unsigned int NormalID;
	unsigned int TexCoordID;
	unsigned int ColorID;
	unsigned int FaceID;
};
_TestMeshVBOID TestMeshVBOID;
extern int TessLevel;
extern bool DrawFrame;
__m128 CameraMatrix[4];
__m128 ShadowMatrix[4];
float WorldMatrix[16];
GLuint RefCubeTexID=0;
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
	SetOmniLightData.Color[0]=0.8f;
	SetOmniLightData.Color[1]=0.8f;
	SetOmniLightData.Color[2]=0.8f;
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

	GLfloat GlobalAmbient_Set[]={0.4f,0.4f,0.4f,1.0f};
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
void LoadCubeTexTga(wchar_t * filename,GLenum target)
{
	TGA * CubeTGA=new TGA;
	CubeTGA->LoadFile(filename);
	if(CubeTGA->TGAerror!=TGA_NO_ERROR) 
	{
		unsigned char DefTexData[64*64*4];
		for(int i=0;i<64*64*4;i++)
			DefTexData[i]=255;
		glTexImage2D(target, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, DefTexData);
	}
	else
		glTexImage2D(target, 0, CubeTGA->type, CubeTGA->width, CubeTGA->height, 0, CubeTGA->type, GL_UNSIGNED_BYTE, CubeTGA->imageData);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}
void LoadCubeTex()
{
	
	glGenTextures(1, &RefCubeTexID);
	glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, RefCubeTexID);
	LoadCubeTexTga(L"data/SkyBox/LF.tga",GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT);
	LoadCubeTexTga(L"data/SkyBox/RT.tga",GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT);

	LoadCubeTexTga(L"data/SkyBox/UP.tga",GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT);
	LoadCubeTexTga(L"data/SkyBox/DN.tga",GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT);

	LoadCubeTexTga(L"data/SkyBox/FR.tga",GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT);
	LoadCubeTexTga(L"data/SkyBox/BK.tga",GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT);
}
void InitDraw()
{
	glewInit();

	WritePrivateProfileStringA("PC Info","Video Card",(char *)glGetString(GL_RENDERER),".\\gameset.ini");
	WritePrivateProfileStringA("PC Info","GL_VERSION",(char *)glGetString(GL_VERSION),".\\gameset.ini");
	//WritePrivateProfileString("PC Info","GL_EXTENSIONS",(char *)glGetString(GL_EXTENSIONS),".\\gameset.ini");
	wchar_t  TestModelPath[512];
	GetPrivateProfileStringW(L"other",L"TestModelPath",L"data/1234.tam",TestModelPath,512,L".\\gameset.ini");
	if(!glewIsSupported("GL_ARB_tessellation_shader")) GameSet.Light=min(3,GameSet.Light);
	if (!glewIsSupported("GL_VERSION_3_0")) GameSet.Light=min(2,GameSet.Light);
	if (!glewIsSupported("GL_VERSION_2_0"))
	{
		MessageBoxA( NULL, "Please Updata Video Card Driver", "OpenGL Ver error", MB_OK|MB_ICONEXCLAMATION );
		GameSet.Light=1;
	}
	if((!glewIsSupported("GL_ARB_pixel_buffer_object"))&&(!glewIsSupported("GL_EXT_pixel_buffer_object")))
	{
		GameSet.SSAO=0;
		GameSet.Light=min(2,GameSet.Light);
	}
	if (!glewIsSupported("GL_ARB_texture_float"))
		GameSet.Bloom=0;

	Textures::LoadDefineTex();ADD_LOG_Q("LoadDefineTex OK");
	LoadingTex.loadfile(L"data/loading");ADD_LOG_Q("LoadingTex OK");
	LoadingTex.LoadToVRAM(GL_LINEAR);ADD_LOG_Q("LoadingTex.LoadToVRAM(GL_LINEAR) OK");
	DrawLoadingTex(&LoadingTex);ADD_LOG_Q("DrawLoadingTex OK");
	LoadCubeTex();ADD_LOG_Q("LoadCubeTex OK");
	if(GameSet.Light>1)
	{
		InitFBO(GameSet.winW,GameSet.winH,GameSet.Bloom);
		ADD_LOG_Q("InitFBO OK");
	}
	InitGLSL();ADD_LOG_Q("InitGLSL OK");
	CDDS::SetAFNum(GameSet.AF);
	InitTestModel();ADD_LOG_Q("InitTestModel OK");
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.5f, 0.5f, 0.0f);
	InitTestLight();ADD_LOG_Q("InitTestLight OK");

	TopAceModelTest.ReadTAMFile(TestModelPath);
	TopAceModelTest.LoadToVRAM();
	if(TopAceModelTest.TAM_FileData)
	{
		PosOrgZ=-max(max(max(abs(TopAceModelTest.pTAM_FileHead->BoxMax[0]),abs(TopAceModelTest.pTAM_FileHead->BoxMin[0])),
			max(abs(TopAceModelTest.pTAM_FileHead->BoxMax[1]),abs(TopAceModelTest.pTAM_FileHead->BoxMin[1]))),
			max(abs(TopAceModelTest.pTAM_FileHead->BoxMax[2]),abs(TopAceModelTest.pTAM_FileHead->BoxMin[2])));
		//PosOrgZ=PosOrgZ*0.285f;
		//PosOrgY=(TopAceModelTest.pTAM_FileHead->BoxMax[2]-(TopAceModelTest.pTAM_FileHead->BoxMax[2]-TopAceModelTest.pTAM_FileHead->BoxMin[2])/2.0f);
		//PosOrgY=500.0f;
		moveZSpeed=PosOrgZ/60.0f;
		maxFreme=(float)TopAceModelTest.testMAXFrame;
	}
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
		Test3dsModelHanger->LoadToVRAM();ARIAL.TTF
	}*/
	
	char szPath[MAX_PATH];
	char FontPath[MAX_PATH];
	GetWindowsDirectoryA(szPath,sizeof(szPath));
	sprintf(FontPath,"%s/Fonts/simsun.ttc",szPath);
	FONTS2D.LoadFullWidthFont(FontPath,16,16);
	sprintf(FontPath,"%s/Fonts/ARIAL.TTF",szPath);
	FONTS2D.LoadHalfWidthFont(FontPath,16,16);
	/*if(!Font2D)
	{
		Font2D=new CFont2D;
		Font2D->LoadFont(FontPath,32,32);
	}*/
	TAMFT3D.LoadFontFile();
	swprintf_s(ShowFPS,64,L"-");
	Easy_matrix_identity(CameraMatrix);
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
	ThreadExchangeToDraw(&ThreadDataDraw);
	Easy_matrix_copy(CameraMatrix,ThreadDataDraw.DataList[1].Matrix);
	Easy_matrix_copy(MatrixDrawTestUnit,ThreadDataDraw.DataList[2].Matrix);
	
	Easy_matrix_copy(WorldMatrix,CameraMatrix);
	Easy_matrix_inv(CameraMatrix,CameraMatrix);
	glLoadMatrixf(&(CameraMatrix[0].m128_f32[0]));
//	CO_SetMMatrix(CameraMatrix[0].m128_f32);
	CommonMatrixs[CO_Matrix_ModelView].LoadF(CameraMatrix[0].m128_f32);
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
	_OmniLightData SetOmniLightData;
	float LightPosTest[]={5000000.0f,7000000.0f,9000000.0f,1.0f};
	__m128 LightPosTestMatrix[4];
	__m128 LightPosTestM;
	Easy_matrix_copy(LightPosTestMatrix,ThreadDataDraw.DataList[5].Matrix);
	Easy_matrix_mult_vector4X4(&LightPosTestM,LightPosTestMatrix,_mm_set_ps(1.0f,0.0f,0.0f,0.0f));
	for(int i=0;i<OmniLightNumBase;i++)
	{
		CO_GetOmniLight(&SetOmniLightData,i);
		Easy_matrix_mult_vector4X4(SetOmniLightData.Pos,CameraMatrix,ThreadDataDraw.DataList[5].Matrix+12);
		/*SetOmniLightData.Pos[0]=LightPosTestM.m128_f32[0];
		SetOmniLightData.Pos[1]=LightPosTestM.m128_f32[1];
		SetOmniLightData.Pos[2]=LightPosTestM.m128_f32[2];
		SetOmniLightData.Pos[3]=1.0f;*/
		CO_SetOmniLight(&SetOmniLightData,i);
		//SetOmniLightData.Pos
	}
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
		swprintf_s(ShowFPS,64,L"操作说明:方向键改变视角,PAGE UP/PAGE DN前进后退\nFPS:%d",FPSNumShow);
		//swprintf_s(ShowFPS,64,L"FPS:%d, CPU:%3.3f%%, CPUDraw:%3.3f%%,\nGPU:%3.3f%%,GPU Tess:%d",FPSNumShow,oneframetimepointCPUSYS,oneframetimepointCPUDraw,oneframetimepointGPU,TessLevel);
		//Font2D->inputTxt(ShowFPS);
	}
	FPSNum=FPSNum+1;
	glColor4f(1.0f,1.0f,0.0f,1.0f);
	glEnable( GL_TEXTURE_2D );
	//Font2D->DrawTXT(GameSet.winW,GameSet.winH,0,0,24,24,GameSet.winW,3);
	FONTS2D.DrawTexts(ShowFPS,4,GameSet.winH-22,GameSet.winW,GameSet.winH,GameSet.winW,20,1.0f);
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
	
	if(GameSet.Light<4) glEnable(GL_MULTISAMPLE_ARB);
	
	glPolygonMode(GL_FRONT_AND_BACK,DrawFrame?GL_LINE:GL_FILL);
	//DrawTestLines();
	//if(GameSet.Light==1) glEnable(GL_LIGHTING);
	//GLSL_Enable_PhoneLight(OmniLightNumBase,SpotLightNumBase);
	

	if(GameSet.Shadow>0) 
	{
		DrawShadowMap();
	}
	//glGetFloatv(GL_PROJECTION_MATRIX,&DrawMatrixTMP[0]);
	//SetPMatrix(DrawMatrixTMP);

	if(GameSet.Light>=4)
		glPatchParameteri(GL_PATCH_VERTICES, 3);
	int GLSLver=min(max(GameSet.Light-2,0),2);
	//glLoadMatrixf(&MatrixTMPF4X4[0]);
	//glMultMatrixf(MatrixDrawTestUnit[0].m128_f32);
//	CO_SetMMatrix(CameraMatrix[0].m128_f32);
	CommonMatrixs[CO_Matrix_ModelView].LoadF(CameraMatrix[0].m128_f32);
//	CO_MultMMatrix(ThreadDataDraw.DataList[4].Matrix);
	CommonMatrixs[CO_Matrix_World].LoadF(ThreadDataDraw.DataList[4].Matrix);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	TopAceModelTest.TAMDrawMode=GL_TRIANGLES;
	GLSL_Enable_Light(SINGLBONE,min(GLSL150,GLSLver),OmniLightNumBase,SpotLightNumBase,TessLevel);
	TopAceModelTest.Draw(false,true);
	TopAceModelTest.TAMDrawMode=GameSet.Light>=4?GL_PATCHES:GL_TRIANGLES;
	GLSL_Enable_Light(SINGLBONE,GLSLver,OmniLightNumBase,SpotLightNumBase,TessLevel);
	TopAceModelTest.Draw(false,false);
	glDepthMask(GL_FALSE);
	TopAceModelTest.TAMDrawMode=GameSet.Light>=4?GL_PATCHES:GL_TRIANGLES;
	GLSL_Enable_Light(SINGLBONE,GLSLver,OmniLightNumBase,SpotLightNumBase,TessLevel);
	TopAceModelTest.Draw(true,false);
	TopAceModelTest.TAMDrawMode=GL_TRIANGLES;
	GLSL_Enable_Light(SINGLBONE,min(GLSL150,GLSLver),OmniLightNumBase,SpotLightNumBase,TessLevel);
	TopAceModelTest.Draw(true,true);
	glDepthMask(GL_TRUE);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	/*CO_MultMMatrix(ThreadDataDraw.DataList[3].Matrix);
	GLSL_SetMMatrixToGlsl();
	GLSL_SetMVPMatrixToGlsl();
	DrawTestModel(GameSet.Light>=4?GL_PATCHES:GL_TRIANGLES);
	*/
	GLSL_Disable();
	
	//if(GameSet.Light==1) glDisable(GL_LIGHTING);
	
	RenderPass2Units();
	
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
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
void DrawShadowMap()
{
	if(GameSet.Shadow<=0) return;
	glBindTexture(GL_TEXTURE_2D, ShadowTexDepth);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LUMINANCE);
	//DrawQUADEX(ShadowTexDepth,GameSet.winW/2-GameSet.winH/2,GameSet.winW/2+GameSet.winH/2,0,GameSet.winH,GameSet.winW,GameSet.winH);
	float Shadowdepth=1.05f*max(TopAceModelTest.pTAM_FileHead->BoxMax[3],-TopAceModelTest.pTAM_FileHead->BoxMin[3]);
	glBindTexture(GL_TEXTURE_2D, 0);
	CUnitMath ShadowUnitMath;
	ShadowUnitMath.UnitPos.m128_f32[0]=ThreadDataDraw.DataList[4].Matrix[12];
	ShadowUnitMath.UnitPos.m128_f32[1]=ThreadDataDraw.DataList[4].Matrix[13];
	ShadowUnitMath.UnitPos.m128_f32[2]=ThreadDataDraw.DataList[4].Matrix[14];
	ShadowUnitMath.UnitPos.m128_f32[3]=1.0f;
	__m128 ShadowUnitMathTGT;
	Easy_vector_copy(&ShadowUnitMathTGT,ThreadDataDraw.DataList[5].Matrix+12);
	ShadowUnitMath.PosTo(ShadowUnitMathTGT);
	ShadowUnitMath.RotInternal(180.0f,0.0f,1.0f,0.0f);
	ShadowUnitMath.MovInternal(_mm_set_ps(1.0f,Shadowdepth+50.0f,0.0f,0.0f));
	__m128 ShadowMM[4];ShadowUnitMath.GetMatrix(ShadowMM);
	Easy_matrix_inv(ShadowMM,ShadowMM);
	float ShadowMF[16];Easy_matrix_copy(ShadowMF,ShadowMM);

	CommonMatrixs[CO_Matrix_Proj].Push();
	CommonMatrixs[CO_Matrix_Proj].OrthogonalProjection(-Shadowdepth,Shadowdepth,-Shadowdepth,Shadowdepth,50.0f,50.0f+Shadowdepth*2.0f);
	GLdouble Biasmatrix[16]={
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0};
	CommonMatrixs[CO_Matrix_ShadowViewProj].LoadD(Biasmatrix);
	CommonMatrixs[CO_Matrix_ShadowViewProj].MultD(CommonMatrixs[CO_Matrix_Proj].LinkList->Matrix);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, ShadowFBOID);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, ShadowTex, 0); 
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,  GL_TEXTURE_2D, ShadowTexDepth,0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glClear (GL_DEPTH_BUFFER_BIT);
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0,0,ShadowTexSize, ShadowTexSize);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
	GLSL_Enable_Shadow();
//	CO_SetMMatrix(ShadowMF);
	CommonMatrixs[CO_Matrix_ModelView].LoadF(ShadowMF);
	CommonMatrixs[CO_Matrix_ShadowViewProj].MultF(ShadowMF);
//	CO_MultMMatrix(ThreadDataDraw.DataList[4].Matrix);
	CommonMatrixs[CO_Matrix_World].LoadF(ThreadDataDraw.DataList[4].Matrix);
	TopAceModelTest.TAMDrawMode=GL_TRIANGLES;
	TopAceModelTest.Draw(false,false);
	TopAceModelTest.Draw(false,true);


	GLSL_Disable();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glPopAttrib();
	glDepthFunc(GL_LEQUAL);
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	glCullFace(GL_BACK);
	glBindTexture(GL_TEXTURE_2D, ShadowTexDepth);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
	CommonMatrixs[CO_Matrix_Proj].Pop();
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
