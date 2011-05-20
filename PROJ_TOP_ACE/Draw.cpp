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
#include "DrawTests.h"
#include "TamScene.h"
float extern angleR;
float extern Test3dsFrame;
float extern maxFreme;
float extern moveZ;
float extern moveY;
float extern moveX;
extern float Touchang;
extern float TouchangY;
int extern ReadingThreadNum;
CFONTS2D FONTS2D;
CFONTS2D FONTS2DSimple;
CTAMFT3D TAMFT3D;
bool Inited=false;
bool IsFirstInit=true;
LARGE_INTEGER TimeStart,TimeEnd,Timefeq,RunTimeStart,RunTimeEnd,CPUTestStart,CPUTestEnd;
int FPSNum=0;
int FPSNumShow=0; 
wchar_t ShowFPS[768]={0};
//CLoad3DS  * Test3dsModelHanger=NULL;

int OmniLightNumBase=0;
int SpotLightNumBase=0;
CTopAceModel TopAceModelTest;
Textures LoadingTex;
Textures WaterNormalTex;
//Textures TestTEX;
extern HDC SwapHdc; 
float PosOrgY=0.0f;
float PosOrgZ=0.0f;
extern float moveZSpeed;
__m128 MatrixDrawTestUnit[4];
CExchangeThread ThreadDataDraw;
extern GLuint ShadowFBOID;
extern GLuint ShadowTex;
extern GLuint ShadowTexDepth;
extern int ShadowTexSize;

extern int TessLevel;
extern bool DrawFrame;
__m128 CameraMatrix[4];
__m128 ShadowMatrix[4];
float WorldMatrix[16];
GLuint RefCubeTexID=0;
wchar_t GPUName[512];
extern BYTE nInputs;
extern unsigned int nInputsNow;
extern __m128 TouchInputposs[4];
float WaterTimeSet[4]={0.0f,0.0f,0.0f,0.0f};
CTamScene TamScene;
extern float zoomsize;
void DrawShadowMap(CTopAceModel * Model,float * UnitMatrix,float * LightMatrix,float ShadowScale=1.0f);
void DrawShadowMapNULL();
extern int InputPos[3];
UINT uMsgDraw=0;
float TestNum=0.0f;
int SceneSelect=-1;
inline void SetTamSceneCheck()
{
	//int ChechID=-1;
	if(ThreadDataDraw.Global_Data.ChangePosOK)
		ThreadDataDraw.DrawToData.ChangePos=0;
	if(InputPos[2])
	{
		if(InputPos[0]>GameSet.winW-64)
		if(InputPos[1]>GameSet.winH-64)
		{
			moveZSpeed=25.0f;
			ThreadDataDraw.DrawToData.ViewTGTPos[0]=0.0f;
			ThreadDataDraw.DrawToData.ViewTGTPos[1]=0.0f;
			ThreadDataDraw.DrawToData.ViewTGTPos[2]=0.0f;
			ThreadDataDraw.DrawToData.ViewPos[0]=1200.0f;
			ThreadDataDraw.DrawToData.ViewPos[1]=1200.0f;
			ThreadDataDraw.DrawToData.ViewPos[2]=1200.0f;
			ThreadDataDraw.DrawToData.LimitZ[0]=3500.0f;
			ThreadDataDraw.DrawToData.LimitZ[1]=100.0f;
			ThreadDataDraw.DrawToData.ChangePos=1;
			SceneSelect=-1;
			InputPos[2]=0;
			return;
		}
		int Checked=TamScene.GetCheck(InputPos[0],InputPos[1]);
		SceneSelect=Checked>-1?Checked:SceneSelect;
		if(Checked>=0)
		{
			moveZSpeed=TamScene.TamList[SceneSelect].MoveSpeed;
			float ScenePosTMP[3];
			Easy_matrix_mult_vector3X3(ScenePosTMP,ThreadDataDraw.DataList[4].Matrix,TamScene.TamList[SceneSelect].Pos);
			ThreadDataDraw.DrawToData.ViewTGTPos[0]=ScenePosTMP[0];
			ThreadDataDraw.DrawToData.ViewTGTPos[1]=ScenePosTMP[1];
			ThreadDataDraw.DrawToData.ViewTGTPos[2]=ScenePosTMP[2];
			ThreadDataDraw.DrawToData.ViewPos[0]=ScenePosTMP[0]-20.0f;
			ThreadDataDraw.DrawToData.ViewPos[1]=ScenePosTMP[1]+50.0f;
			ThreadDataDraw.DrawToData.ViewPos[2]=ScenePosTMP[2]-70.0f;
			ThreadDataDraw.DrawToData.LimitZ[0]=TamScene.TamList[SceneSelect].Limitfar;
			ThreadDataDraw.DrawToData.LimitZ[1]=TamScene.TamList[SceneSelect].Limitnear;
			ThreadDataDraw.DrawToData.ChangePos=1;
		}
		
	}
	InputPos[2]=0;
	
}
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

	GLfloat GlobalAmbient_Set[]={0.5f,0.5f,0.5f,1.0f};
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
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
bool InitDraw()
{
	glewInit();
	if((GetCharLenth((char *)glGetString(GL_RENDERER))+GetCharLenth((char *)glGetString(GL_VERSION)))>=512)
	{
		GPUName[0]=L' ';
		GPUName[1]=0;
	}
	else
	{
		char GPUNameTMP[512];
		sprintf_s(GPUNameTMP,"%s %s",(char *)glGetString(GL_RENDERER),(char *)glGetString(GL_VERSION));
		int dwNum=MultiByteToWideChar(CP_ACP,0,GPUNameTMP,-1,NULL,0);
		MultiByteToWideChar(CP_ACP,0,GPUNameTMP,-1,GPUName,dwNum);
	}
	ADD_LOG_Q((char *)glGetString(GL_RENDERER));
	ADD_LOG_Q((char *)glGetString(GL_VERSION));
	ADD_OGLEX_LOG((char *)glGetString(GL_EXTENSIONS));
	wchar_t  TestModelPath[512];
	GetPrivateProfileStringW(L"other",L"TestModelPath",L"data/1234.tam",TestModelPath,512,L".\\gameset.ini");
	if(!glewIsSupported("GL_ARB_tessellation_shader")) GameSet.Light=min(3,GameSet.Light);
	if (!glewIsSupported("GL_VERSION_3_0"))
	{
		if(GameSet.Light>2) ADD_LOG_Q("Opengl ver low,Light set to lower.","#0000FF");
		GameSet.Light=min(2,GameSet.Light);
	}
	if (!glewIsSupported("GL_VERSION_2_0"))
	{
		GameSet.Light=1;
		ADD_LOG_Q("Opengl Ver too Low,maybe Video Card too old.","#FF0000");
		MessageBoxW( NULL, L"Opengl Ver too Low,maybe Video Card too old.\nPlease Updata Video Card Driver.", L"Error!", MB_OK|MB_ICONEXCLAMATION );
		return false;
	}//
	if (!glewIsSupported("GL_ARB_vertex_array_object"))
	{
		if(GameSet.Light>2) ADD_LOG_Q("Can not suppot GL_ARB_vertex_array_object. maybe OpenGL Driver too old . Please Updata Video Card Driver","#0000FF");
		//MessageBoxW( NULL, L"Can not suppot GL_ARB_vertex_array_object,\nmaybe OpenGL Driver too old.\nPlease Updata Video Card Driver", L"Waring", MB_OK|MB_ICONEXCLAMATION );
	}
	if((!glewIsSupported("GL_ARB_pixel_buffer_object"))&&(!glewIsSupported("GL_EXT_pixel_buffer_object")))
	{
		GameSet.SSAO=0;
		if(GameSet.Light>2) ADD_LOG_Q("Opengl ver low,Light set to lower.","#0000FF");
		GameSet.Light=min(2,GameSet.Light);
	}
	//if (!glewIsSupported("GL_ARB_texture_float"))
	//	GameSet.Bloom=0;
	Textures::LoadDefineTex();ADD_LOG_Q("LoadDefineTex OK");
	LoadingTex.loadfile(L"data/loading");ADD_LOG_Q("LoadingTex OK");
	LoadingTex.LoadToVRAM(GL_LINEAR);ADD_LOG_Q("LoadingTex.LoadToVRAM(GL_LINEAR) OK");
	//DrawLoadingTex(&LoadingTex);ADD_LOG_Q("DrawLoadingTex OK");
	LoadCubeTex();ADD_LOG_Q("LoadCubeTex OK");
	
	
	WaterNormalTex.loadfile(L"data/sea/sea");
	WaterNormalTex.LoadToVRAM();
	WaterNormalTexID=WaterNormalTex.TexID;
	//TestTEX.loadfile(L"data/test");
	//TestTEX.LoadToVRAM();
	if(GameSet.Light>1)
	{
		InitFBO(GameSet.winW,GameSet.winH)==true?ADD_LOG_Q("InitFBO OK"):ADD_LOG_Q("InitFBO false");
		
	}
	InitGLSL();ADD_LOG_Q("InitGLSL OK");
	CDDS::SetAFNum(GameSet.AF);ADD_LOG_Q("SetAFNum OK");
	//InitTestModel();ADD_LOG_Q("InitTestModel OK");
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	InitTestLight();ADD_LOG_Q("InitTestLight OK");

	TopAceModelTest.ReadTAMFile(TestModelPath)?ADD_LOG_Q("TopAceModelTest.ReadTAMFile(TestModelPath) OK"):ADD_LOG_Q("TopAceModelTest.ReadTAMFile(TestModelPath) fail","#FF0000");
	TopAceModelTest.LoadToVRAM()?ADD_LOG_Q("TopAceModelTest.LoadToVRAM() OK"):ADD_LOG_Q("TopAceModelTest.LoadToVRAM() fail","#FF0000");
	if(TopAceModelTest.TAM_FileData)
	{
		/*PosOrgZ=-max(max(max(abs(TopAceModelTest.pTAM_FileHead->BoxMax[0]),abs(TopAceModelTest.pTAM_FileHead->BoxMin[0])),
			max(abs(TopAceModelTest.pTAM_FileHead->BoxMax[1]),abs(TopAceModelTest.pTAM_FileHead->BoxMin[1]))),
			max(abs(TopAceModelTest.pTAM_FileHead->BoxMax[2]),abs(TopAceModelTest.pTAM_FileHead->BoxMin[2])));
		//PosOrgZ=PosOrgZ*0.285f;
		//PosOrgY=(TopAceModelTest.pTAM_FileHead->BoxMax[2]-(TopAceModelTest.pTAM_FileHead->BoxMax[2]-TopAceModelTest.pTAM_FileHead->BoxMin[2])/2.0f);
		//PosOrgY=500.0f;
		moveZSpeed=PosOrgZ/360.0f;*/
		maxFreme=1.4f*(float)TopAceModelTest.testMAXFrame;
	}

	
	char szPath[MAX_PATH];
	char FontPath[MAX_PATH];
	GetWindowsDirectoryA(szPath,sizeof(szPath));
	sprintf(FontPath,"%s/Fonts/simhei.ttf",szPath);
	FONTS2D.LoadFullWidthFont(FontPath,16,16)?ADD_LOG_Q("FONTS2D.LoadFullWidthFont(FontPath,16,16) OK"):ADD_LOG_Q("FONTS2D.LoadFullWidthFont(FontPath,16,16) fail","#FF0000");
	FONTS2DSimple.LoadFullWidthFont(FontPath,256,256);
	sprintf(FontPath,"%s/Fonts/ARIAL.TTF",szPath);
	FONTS2D.LoadHalfWidthFont(FontPath,16,16)?ADD_LOG_Q("FONTS2D.LoadHalfWidthFont(FontPath,16,16) OK"):ADD_LOG_Q("FONTS2D.LoadHalfWidthFont(FontPath,16,16) fail","#FF0000");
	
	TamScene.LoadFile(L"data\\model\\");
	TamScene.ToVRAM();
	TamScene.SetUnitNamePos(GameSet.winW,GameSet.winH);
	//TAMFT3D.LoadFontFile()?ADD_LOG_Q("TAMFT3D.LoadFontFile() OK"):ADD_LOG_Q("TAMFT3D.LoadFontFile() fail","#FF0000");
	swprintf_s(ShowFPS,64,L"-");
	Easy_matrix_identity(CameraMatrix);
	ADD_LOG_Q("InitDraw() OK");
	QueryPerformanceCounter(&TimeStart);
	if(IsFirstInit)
	{
		QueryPerformanceCounter(&RunTimeStart);
		IsFirstInit=false;
	}
	QueryPerformanceFrequency(&Timefeq);
	return true;
}
void ClearVRAM()
{
	/*if(Test3dsModelHanger)
	{
		Test3dsModelHanger->Del_VRAM();
	}*/
}
void DeinitDraw()
{
	if(GameSet.Light>1)
		DeinitFBO();
	DeinitGLSL();
	TopAceModelTest.DeleteVRAM();
	Inited=false;
	TamScene.ClearScene();
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
		swprintf_s(
			ShowFPS,
			sizeof(ShowFPS)/sizeof(ShowFPS[0]),
			L"FPS:%d %s\n当前触摸点数/最大触摸点数：%d/%d,触点位置1/2: %d %d / %d %d\nCPU:%3.2f%%/%3.2f%% GPU:%3.2f%%\n %f",
			FPSNumShow,
			GPUName,
			nInputsNow,
			nInputs,
			TouchInputposs[0].m128_i32[0],
			TouchInputposs[0].m128_i32[1],
			TouchInputposs[1].m128_i32[0],
			TouchInputposs[1].m128_i32[1],
			oneframetimepointCPUDraw,
			oneframetimepointCPUSYS,
			oneframetimepointGPU,
			TestNum
			);
		//swprintf_s(ShowFPS,64,L"FPS:%d, CPU:%3.3f%%, CPUDraw:%3.3f%%,\nGPU:%3.3f%%,GPU Tess:%d",FPSNumShow,oneframetimepointCPUSYS,oneframetimepointCPUDraw,oneframetimepointGPU,TessLevel);
		//Font2D->inputTxt(ShowFPS);
	}
	FPSNum=FPSNum+1;
	glColor4f(1.0f,1.0f,0.0f,1.0f);
	glEnable( GL_TEXTURE_2D );
	//Font2D->DrawTXT(GameSet.winW,GameSet.winH,0,0,24,24,GameSet.winW,3);
	FONTS2D.DrawTexts(ShowFPS,4,GameSet.winH-22,GameSet.winW,GameSet.winH,GameSet.winW,20,1.0f);
	glColor4f(1.0f,1.0f,0.0f,0.3f);
	//FONTS2DSimple.DrawTexts(L"样品",16,256-272*GameSet.winH/GameSet.winW,544,544*GameSet.winH/GameSet.winW,544,20,32.0f);
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	RenderFaces=0;
}

void Draw(float oneframetimepointCPUSYS,float oneframetimepointGPU)
{
	glClear ( GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);//
	
	if(GameSet.Light<4) glEnable(GL_MULTISAMPLE_ARB);
	
	glPolygonMode(GL_FRONT_AND_BACK,DrawFrame?GL_LINE:GL_FILL);
	//DrawTestLines();
	
	//TAMFT3D.Draw3DText(L"测试",20,20,600);
	WaterTimeSet[0]=WaterTimeSet[0]+0.0001f;
	WaterTimeSet[1]=WaterTimeSet[1]+0.0002f;
	WaterTimeSet[2]=WaterTimeSet[2]+0.0004f;
	WaterTimeSet[3]=WaterTimeSet[3]+0.0006f;
	if(GameSet.Shadow>0) 
	{
		if(SceneSelect<0)
		{
			DrawShadowMapNULL();
			//DrawShadowMap(&TopAceModelTest,ThreadDataDraw.DataList[4].Matrix,ThreadDataDraw.DataList[5].Matrix);
		}
		else if(TamScene.TamList.size()>SceneSelect)
		{
			float ShadowUnitMatrixTMP[16];
			Easy_matrix_mult(ShadowUnitMatrixTMP,ThreadDataDraw.DataList[4].Matrix,TamScene.TamList[SceneSelect].Matrix);
			DrawShadowMap(TamScene.TamList[SceneSelect].Model,ShadowUnitMatrixTMP,ThreadDataDraw.DataList[5].Matrix,TamScene.TamList[SceneSelect].scale[0]);
		}
	}

	int GLSLver=min(max(GameSet.Light-2,0),2);
	CommonMatrixs[CO_Matrix_ModelView].LoadF(CameraMatrix[0].m128_f32);
	CommonMatrixs[CO_Matrix_World].LoadF(ThreadDataDraw.DataList[4].Matrix);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	GLSL_Enable_Light(SINGLBONE,min(GLSL150,GLSLver),OmniLightNumBase,SpotLightNumBase,TessLevel);
	TopAceModelTest.Draw(false);
	TamScene.Draw(false);
	if(SceneSelect==-1)
	TopAceModelTest.Draw(false,_TAM_Mesh_EXT_Type_Tree);
	if(SceneSelect>-1)
	TamScene.Draw(false,_TAM_Mesh_EXT_Type_Tree);
	glDepthMask(GL_FALSE);
	TopAceModelTest.Draw(true);
	if(SceneSelect==-1)
	TopAceModelTest.Draw(true,_TAM_Mesh_EXT_Type_Tree);
	TamScene.Draw(true);
	if(SceneSelect>-1)
	TamScene.Draw(true,_TAM_Mesh_EXT_Type_Tree);
	GLSL_Enable_Water(WaterTimeSet);
	TopAceModelTest.Draw(true,_TAM_Mesh_EXT_Type_Water);
	TamScene.Draw(true,_TAM_Mesh_EXT_Type_Water);
	glDepthMask(GL_TRUE);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	GLSL_Disable();

	RenderPass2Units();
	//glDisable(GL_BLEND);
	//DrawQUADEX(TestTEX.TexID,0,TestTEX.TexW,0,TestTEX.TexH,GameSet.winW,GameSet.winH);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	DrawFPS(oneframetimepointCPUSYS, oneframetimepointGPU);
	glDisable(GL_MULTISAMPLE_ARB);

	
	TamScene.DrawUnitName(GameSet.winW,GameSet.winH);
	SetTamSceneCheck();
	QueryPerformanceCounter(&CPUTestStart);
	ThreadExchangeToDraw(&ThreadDataDraw);
	UnitMatrix();
	SetCameraMatrix();
	SetLights();
	Test_matrix();
	//TopAceModelTest.FrameTAMBoneMatrixs(max(0.0f,Test3dsFrame-0.3f*TopAceModelTest.testMAXFrame));
	if(Test3dsFrame>TopAceModelTest.testMAXFrame) Test3dsFrame=Test3dsFrame-TopAceModelTest.testMAXFrame;
	TopAceModelTest.FrameTAMBoneMatrixs(Test3dsFrame);
	RenderFaces=RenderFaces+TAMFT3D.RenderFaceNum+TopAceModelTest.TotelFaceNum;
	QueryPerformanceCounter(&CPUTestEnd);
}
void DrawShadowMap(CTopAceModel * Model,float * UnitMatrix,float * LightMatrix,float ShadowScale)
{
	if(GameSet.Shadow<=0) return;
	if(!Model) return;
	if(!ShadowTexDepth) return;
	if(!UnitMatrix) return;
	if(!LightMatrix) return;
	if(Model->pTAM_FileHead==NULL) return;
	
	glBindTexture(GL_TEXTURE_2D, ShadowTexDepth);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LUMINANCE);
	glBindTexture(GL_TEXTURE_2D, 0);
	//DrawQUADEX(ShadowTexDepth,GameSet.winW/2-GameSet.winH/2,GameSet.winW/2+GameSet.winH/2,0,GameSet.winH,GameSet.winW,GameSet.winH);
	float Shadowdepth=1.05f*max(Model->pTAM_FileHead->BoxMax[3],-Model->pTAM_FileHead->BoxMin[3])*ShadowScale;
	CUnitMath ShadowUnitMath;
	ShadowUnitMath.UnitPos.m128_f32[0]=UnitMatrix[12];
	ShadowUnitMath.UnitPos.m128_f32[1]=UnitMatrix[13];
	ShadowUnitMath.UnitPos.m128_f32[2]=UnitMatrix[14];
	ShadowUnitMath.UnitPos.m128_f32[3]=1.0f;
	__m128 ShadowUnitMathTGT;
	Easy_vector_copy(&ShadowUnitMathTGT,LightMatrix+12);
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
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
		
	glClear (GL_DEPTH_BUFFER_BIT);
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0,0,ShadowTexSize, ShadowTexSize);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_TRUE);

	GLSL_Enable_Shadow();
	CommonMatrixs[CO_Matrix_ModelView].LoadF(ShadowMF);
	CommonMatrixs[CO_Matrix_ShadowViewProj].MultF(ShadowMF);
	CommonMatrixs[CO_Matrix_World].LoadF(UnitMatrix);
	Model->TAMDrawMode=GL_TRIANGLES;
	Model->Draw(false);
	Model->Draw(false,_TAM_Mesh_EXT_Type_Tree);

	GLSL_Disable();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glPopAttrib();
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	glCullFace(GL_BACK);
	glBindTexture(GL_TEXTURE_2D, ShadowTexDepth);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
	CommonMatrixs[CO_Matrix_Proj].Pop();
}
void DrawShadowMapNULL()
{
	glBindTexture(GL_TEXTURE_2D, ShadowTexDepth);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LUMINANCE);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, ShadowFBOID);
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glClear (GL_DEPTH_BUFFER_BIT);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindTexture(GL_TEXTURE_2D, ShadowTexDepth);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

}
/*
void DrawShadowMap()
{
	if(GameSet.Shadow<=0) return;
	glBindTexture(GL_TEXTURE_2D, ShadowTexDepth);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LUMINANCE);
	glBindTexture(GL_TEXTURE_2D, 0);

	//DrawQUADEX(ShadowTexDepth,GameSet.winW/2-GameSet.winH/2,GameSet.winW/2+GameSet.winH/2,0,GameSet.winH,GameSet.winW,GameSet.winH);
	
	float Shadowdepth=1.05f*max(TopAceModelTest.pTAM_FileHead->BoxMax[3],-TopAceModelTest.pTAM_FileHead->BoxMin[3]);
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
	//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, ShadowTex, 0); 
	//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,  GL_TEXTURE_2D, ShadowTexDepth,0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);

	glClear (GL_DEPTH_BUFFER_BIT);
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0,0,ShadowTexSize, ShadowTexSize);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_TRUE);


	GLSL_Enable_Shadow();
	CommonMatrixs[CO_Matrix_ModelView].LoadF(ShadowMF);
	CommonMatrixs[CO_Matrix_ShadowViewProj].MultF(ShadowMF);
	CommonMatrixs[CO_Matrix_World].LoadF(ThreadDataDraw.DataList[4].Matrix);
	TopAceModelTest.TAMDrawMode=GL_TRIANGLES;
	TopAceModelTest.Draw(false);
	
	//TopAceModelTest.Draw(false,_TAM_Mesh_EXT_Type_Tree);

	GLSL_Disable();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glPopAttrib();
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	glCullFace(GL_BACK);
	glBindTexture(GL_TEXTURE_2D, ShadowTexDepth);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
	CommonMatrixs[CO_Matrix_Proj].Pop();
}
*/