//#include "ms3d.h"

#include <stdlib.h>

#include <GL/glew.h>
#include <math.h>
#include "testNum.h"
#include "initdata.h"
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input/Output
#include "NeHeGL.h"												// Header File For NeHeGL
//#include "ACMD.h"												// Header File For ACMD
#include "smoke.h"	
#include "KeyInput.h"
#include "shaders.h"
//#include "Textures.h"
//#include "Prints.h"
#include "lock.h"
//#include "redar.h"
//#include "UI.h"
#include "VBMD.h"
#include "Cpuid.h"
#include "sound.h"
#include "texture.h"
#include "EffectImpact.h"
#include "SkyBox.h"
#include "Bloom.h"
#include "Video.h"
#include "FBO.h"
#include "BomTeams.h"
//#include "Cloud.h"
//#include "MD5Model.h"
#include "ARB_MULTISAMPLE.h"
#pragma comment( lib, "opengl32.lib" )							// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )								// Search For GLu32.lib While Linking
#pragma comment( lib, "glaux.lib" )								// Search For GLaux.lib While Linking
#pragma comment( lib, "cg.lib" )	
#pragma comment( lib, "cgGL.lib" )	
#pragma comment( lib, "glew32.lib" )	
#pragma comment( lib, "glew32d.lib" )
#pragma comment( lib, "SDL.lib" )
#pragma comment( lib, "SDLmain.lib" )

extern GLuint fbo;					// Our handle to the FBO
extern GLuint depthBuffer;			// Our handle to the depth render buffer
extern GLuint img;
extern GLuint dtex;//,fboBloomImg	

LARGE_INTEGER t1,t2,feq,t3;//计算每桢运行时间相关
GL_Window*	g_window;
Keys*		g_keys;
CSmoke		PSmokes;

CKeyInput KeyInput;
CSkyBox SkyBox;
CVideo Video;
int gamestage=0;
CPUID cpu;//查询cpu
char cpubrand[128]={0};

int playTime=0;

CBomType PlaneBom[1];
CBom Bomings[MAXBom];
int Bomings_index=0;
bool IsUseJoyStick=false;
bool UseEffectImpact=false;
bool DrawEffectImpact=false;
bool GraphicsLOW=false;
CEffectImpact EffectImpact;
//用于等待时间以保持稳定速度
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


void InitFogAndLight(void)
{
	glClearColorR=(float)GetPrivateProfileInt("Fog","glClearColorR",184,".\\set.ini")/255.0f;
	glClearColorG=(float)GetPrivateProfileInt("Fog","glClearColorG",187,".\\set.ini")/255.0f;
	glClearColorB=(float)GetPrivateProfileInt("Fog","glClearColorB",210,".\\set.ini")/255.0f;
	glClearColorA=(float)GetPrivateProfileInt("Fog","glClearColorA",255,".\\set.ini")/255.0f;
	fogColorR=(float)GetPrivateProfileInt("Fog","fogColorR",184,".\\set.ini")/255.0f;
	fogColorG=(float)GetPrivateProfileInt("Fog","fogColorG",187,".\\set.ini")/255.0f;
	fogColorB=(float)GetPrivateProfileInt("Fog","fogColorB",210,".\\set.ini")/255.0f;
	fogColorA=(float)GetPrivateProfileInt("Fog","fogColorA",255,".\\set.ini")/255.0f;
	fogDENSITY=(float)GetPrivateProfileInt("Fog","fogDENSITY",90,".\\set.ini")/255.0f;
	Fog_Near=(float)GetPrivateProfileInt("Fog","Fog_Near",60000,".\\set.ini");
	Fog_Far=(float)GetPrivateProfileInt("Fog","Fog_Far",100000,".\\set.ini");
	LightAmbientR=(float)GetPrivateProfileInt("Light","LightAmbientR",150,".\\set.ini")/255.0f;
	LightAmbientG=(float)GetPrivateProfileInt("Light","LightAmbientG",150,".\\set.ini")/255.0f;
	LightAmbientB=(float)GetPrivateProfileInt("Light","LightAmbientB",150,".\\set.ini")/255.0f;
	LightAmbientA=(float)GetPrivateProfileInt("Light","LightAmbientA",255,".\\set.ini")/255.0f;
	LightDiffuseR=(float)GetPrivateProfileInt("Light","LightDiffuseR",106,".\\set.ini")/255.0f;
	LightDiffuseG=(float)GetPrivateProfileInt("Light","LightDiffuseG",106,".\\set.ini")/255.0f;
	LightDiffuseB=(float)GetPrivateProfileInt("Light","LightDiffuseB",106,".\\set.ini")/255.0f;
	LightDiffuseA=(float)GetPrivateProfileInt("Light","LightDiffuseA",255,".\\set.ini")/255.0f;

	LightSunPosR[0]=150000.0f;
	LightSunPosR[1]=150000.0f;
	LightSunPosR[2]=10.0f;
	LightSunPos[0]=150000.0f;
	LightSunPos[1]=150000.0f;
	LightSunPos[2]=10.0f;


	glCullFace(GL_BACK);
	glClearColor (glClearColorR, glClearColorG, glClearColorB, glClearColorA);						// Black Background
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate
	glEnable( GL_TEXTURE_2D );									// Enable Textures
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );						// Set The Color To White

	
	GLfloat fogColor[4]= {fogColorR, fogColorG, fogColorB, fogColorA};	
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);

	
	glFogf(GL_FOG_DENSITY, fogDENSITY);	
	glHint(GL_FOG_HINT, GL_NICEST);	
	glFogf(GL_FOG_START, Fog_Near);	
	glFogf(GL_FOG_END, Fog_Far);	
	//glEnable(GL_FOG);
	paraLightColor[0] = LightDiffuseR; 
	paraLightColor[1] = LightDiffuseG;
	paraLightColor[2] = LightDiffuseB;
	paraLightColor[3] = LightDiffuseA;

	lightColor[0] = LightDiffuseR*10; 
	lightColor[1] = LightDiffuseG*10;
	lightColor[2] = LightDiffuseB*10;
	lightColor[3] = LightDiffuseA;
	globalAmbient[0] = LightAmbientR; 
	globalAmbient[1] = LightAmbientG;
	globalAmbient[2] = LightAmbientB;
	globalAmbient[3] = LightAmbientA;

	 // Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);

	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,lightColor);
	
	glLightfv(GL_LIGHT1,GL_POSITION,lightPosition);
	glLightfv(GL_LIGHT1,GL_SPECULAR,lightColor);
	//
	 // Enable color tracking
	//glEnable(GL_COLOR_MATERIAL);
	
	 // Set Material properties to follow glColor values
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	GLfloat SHININESS[]={5.0};
	//glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,globalAmbient);

	//glMaterialfv(GL_FRONT,GL_SHININESS,SHININESS);

}
bool InitLoadfile(void)
{
	needloadfile=0;
	return true;
}
void InitTile(void)
{
	strcat( szVERSION, (char *)glGetString(GL_RENDERER) );
	strcat( szVERSION, " |" );
	strcat( szVERSION, (char *)glGetString(GL_VENDOR) );
	strcat( szVERSION, " |" );
	strcat( szVERSION, (char *)glGetString(GL_VERSION) );
	strcat( szVERSION, " |" );
	sprintf(szResolution,"%d*%d@%d",winwidth,winheight,GetPrivateProfileInt("Resolution","bits",16,".\\set.ini"));

	
	strcat( szVERSION, szResolution );
}
BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
{
	g_window	= window;
	g_keys		= keys;
	if(GetPrivateProfileInt("Graphics","LOW",0,".\\set.ini")!=0)
		GraphicsLOW=true;
	else
		GraphicsLOW=false;

#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","Begin","OK",".\\Log.ini");
#endif
	glewInit();
#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","glewInit","OK",".\\Log.ini");
#endif
	BuildFont(!GraphicsLOW);
#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","BuildFont","OK",".\\Log.ini");
#endif
	KeyInput.initJoyStick();
#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","initJoyStick","OK",".\\Log.ini");
#endif
	Video.InitVideo();
#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","InitVideo","OK",".\\Log.ini");
#endif	

	strcpy( cpubrand, cpu.GetBrand().c_str() );
	while(cpubrand[0]==' ')
	for(int i=0;i<126;i++)
	{
		cpubrand[i]=cpubrand[i+1];
	}
#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","getcpubrand","OK",".\\Log.ini");
#endif

	//GL_ARB_vertex_program
    if ((glewIsSupported(
        "GL_VERSION_2_0 "
		"GL_EXT_framebuffer_object "
        "GL_ARB_vertex_program "
        "GL_ARB_fragment_program "
        ))&&(!GraphicsLOW))
		IsSupportFBO=true;
	ShadowLevel=GetPrivateProfileInt("Light","Shadow",4,".\\set.ini");
	if(ShadowLevel<2)
		UseHighShadow=false;
	if(ShadowLevel<1)
	{
		UseShadow=false;
		img=EmptyTexture(64);
	}
	else
		initFBO(IsSupportFBO);
#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","GetglewSupported","OK",".\\Log.ini");
#endif
/*
	if (glewIsSupported("WGL_ARB_multisample"))
		Multisample=GetPrivateProfileInt("Resolution","AA",0,".\\set.ini");
	else
		::MessageBox(HWND_DESKTOP," no WGL_ARB_multisample","Error",MB_OK | MB_ICONEXCLAMATION);
*/


	if (glewIsSupported("GL_ARB_vertex_buffer_object"))
	VBOSupported=true;

	FrameSkip=GetPrivateProfileInt("Resolution","FrameSkip",0,".\\set.ini")+1;
	oneframetimelimit=(double)FrameSkip/60.0;
	SmallWindowType=GetPrivateProfileInt("UI","SmallWindowSet",0,".\\set.ini");

	moveSpeed=GetPrivateProfileInt("FlySet","moveSpeed",100,".\\set.ini")*0.0001f;
	MAXSpeed=GetPrivateProfileInt("FlySet","MAXSpeed",300,".\\set.ini")*0.0001f;
	MINSpeed=GetPrivateProfileInt("FlySet","MINSpeed",1,".\\set.ini")*0.0001f;
	Acceleration=GetPrivateProfileInt("FlySet","Acceleration",1,".\\set.ini")*0.00005f;
	SpeedShowPercentage=(float)GetPrivateProfileInt("FlySet","SpeedShowPercentage",30000,".\\set.ini");
	TurnRateX=GetPrivateProfileInt("FlySet","TurnRateX",50,".\\set.ini")*0.0001f;
	TurnRateY=GetPrivateProfileInt("FlySet","TurnRateY",500,".\\set.ini")*0.0001f;
	TurnRateZ=GetPrivateProfileInt("FlySet","TurnRateZ",50,".\\set.ini")*0.0001f;

	if((GetPrivateProfileInt("Effect","MoveBlur",0,".\\set.ini")==0)||(!IsSupportFBO))
		UseEffectImpact=false;
	else
		UseEffectImpact=true;

	glPrint(16,16,"Loading Textures",0);
	

//	BuildSmoke();
	if(!InitLoadfile())
		return false;
#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","InitLoadfile","OK",".\\Log.ini");
#endif
	InitFogAndLight();
	InitTile();

	if((GetPrivateProfileInt("Light","Use_openGL_Light",0,".\\set.ini")==0)&&IsSupportFBO)
	{
		InitShader();
#ifdef _RELEASELOG 
		WritePrivateProfileString("Initialize","InitCG","OK",".\\Log.ini");
#endif
	}
	else
	{
		ShaderWater=false;
		ShaderLight=false;
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	}
	if((GetPrivateProfileInt("Light","ShaderWater",0,".\\set.ini")==0)||(!IsSupportFBO))
		ShaderWater=false;

	if((GetPrivateProfileInt("Light","Use_Bloom",0,".\\set.ini")==0)||(!IsSupportFBO))
		ShaderBloom=false;
	pixelfogColor[0]=(float)GetPrivateProfileInt("Fog","fogColorR",201,".\\set.ini")/255.0f;
	pixelfogColor[1]=(float)GetPrivateProfileInt("Fog","fogColorG",207,".\\set.ini")/255.0f;
	pixelfogColor[2]=(float)GetPrivateProfileInt("Fog","fogColorB",210,".\\set.ini")/255.0f;
	
	lockX=winwidth/2;
	lockY=winheight/2;


	if(ShaderBloom)
	{
		InitBloom(winwidth,winheight);
#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","InitBloom","OK",".\\Log.ini");
#endif
	}
	RedarTexture=EmptyTexture();
	UItexture1=EmptyTexture();
	UItexture2=EmptyTexture(512);
	UItexture3=EmptyTexture(512);

	while(SmallWinSize<(winheight/6))
		SmallWinSize=SmallWinSize*2;
	SmallWinTexID=EmptyTexture(SmallWinSize);
#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","InitUItextures","OK",".\\Log.ini");
#endif
	initlocks();
#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","initlocks","OK",".\\Log.ini");
#endif
	initUnitdata(0);
	    
#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","initUnitdata","OK",".\\Log.ini");
#endif
	
	//glEnable(GL_LINE_SMOOTH);
	//glHint(GL_LINE_SMOOTH_HINT,GL_LINE_SMOOTH_HINT);

	EffectImpact.winW=winwidth;
	EffectImpact.winH=winheight;
	EffectImpact.IsSupportFBO=IsSupportFBO;
	if(UseEffectImpact)
	{
		EffectImpact.Init();
#ifdef _RELEASELOG 
	WritePrivateProfileString("Initialize","initEffectImpact","OK",".\\Log.ini");
#endif
	}
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	if(GameMode==1)
	{
		InertiaLimit=40.0f;
	}

	//const unsigned char *Extensions = glGetString( GL_EXTENSIONS );
	//WritePrivateProfileString("Extensions","Extensions",(char *)Extensions,".\\set.ini");
	QueryPerformanceCounter(&t1);
	return TRUE;												// Return TRUE (Initialization Successful)
}

void Deinitialize (void)										// Any User DeInitialization Goes Here
{
	DeleteFont();
	if(ShadowLevel>0)
	{
		glDeleteFramebuffersEXT(1, &fbo);
		glDeleteRenderbuffersEXT(1, &depthBuffer);
	}

	glDeleteTextures(1,&img);
/*
	for(int i=1;i<11;i++)
	{
		FMOD_Sound_Release(missleWarning[i-1]);
	}
	for(int i=1;i<4;i++)
	{
		FMOD_Sound_Release(fox2voice[i-1]);
	}
	for(int i=1;i<5;i++)
	{
		FMOD_Sound_Release(hitvoice[i-1]);
	}
	for(int i=1;i<8;i++)
	{
		FMOD_Sound_Release(killvoice[i-1]);
	}
	for(int i=1;i<5;i++)
	{
		FMOD_Sound_Release(missvoice[i-1]);
	}
	FMOD_Sound_Release(sound1);
	FMOD_Sound_Release(sound2);
	//FMOD_Sound_Release(voice1);
	//FMOD_Sound_Release(voice2);
	//FMOD_Sound_Release(voice3);
	//FMOD_Sound_Release(voice4);
	//FMOD_Sound_Release(voice5);
	//FMOD_Sound_Release(BGMsound);
	FMOD_System_Release(sys);
	*/
	BGMplayer->Clear();
	openal::CloseOpenALEE();
	//delete m_nj;
	delete m_VBMD;
	//delete m_VBMD;
	//SDL_JoystickClose(joystick);
	//SDL_Quit();
	KeyInput.de();
}


void Inertia()              //处理惯性
{
	//testNum=InertiaSpeed;
	if(!(InertiaSpeed==0.0f))
	{
		if(InertiaSpeed*InertiaSpeed<1.0f)
			InertiaSpeed=0.0f;
		if(InertiaSpeed>0.0f)
			InertiaSpeed=InertiaSpeed-0.5f;
		if(InertiaSpeed<0.0f)
			InertiaSpeed=InertiaSpeed+0.5f;
	}
	float Speedloss=max(0.0f,1.0f-moveSpeed*moveSpeed/(MAXSpeed*MAXSpeed*2.0f+0.000001f));

	float speedKmh=moveSpeed*60.0f*60.0f*60.0f*2000.0f/10000.0f;
	changeInertia= min(speedKmh/200.0f,1.0f);

	if(!(InertiaZ==0.0f))
	{
		if(InertiaZ*InertiaZ<1.0f)
			InertiaZ=0.0f;
		if(InertiaZ>0.0f)
			InertiaZ=InertiaZ-1.0f;
		if(InertiaZ<0.0f)
			InertiaZ=InertiaZ+1.0f;
	}
	turnZ=InertiaZ*TurnRateZ*changeInertia*Speedloss;

	if(!(InertiaY==0.0f))
	{
		if(InertiaY*InertiaY<1.0f)
			InertiaY=0.0f;
		if(InertiaY>0.0f)
			InertiaY=InertiaY-1.0f;
		if(InertiaY<0.0f)
			InertiaY=InertiaY+1.0f;
	}
	turnY=InertiaY*0.004f*changeInertia*Speedloss;

	if(!(InertiaX==0.0f))
	{
		if(InertiaX*InertiaX<1.0f)
			InertiaX=0.0f;
		if(InertiaX>0.0f)
			InertiaX=InertiaX-1.0f;
		if(InertiaX<0.0f)
			InertiaX=InertiaX+1.0f;
	}
	turnX=InertiaX*TurnRateX*changeInertia*Speedloss;
	moveSpeed=moveSpeed+moveSpeedT/4000000.0f-(InertiaX*InertiaX/60000000.0f)*min(1.0f,speedKmh/350.0f)+(1.0f-min(1.0f,speedKmh/600.0f))*Acceleration;

	shellturn=turnX*150.0f;
	if(changeInertia<1.0f)
	{
		UDfighers[0].UDMplane.Translate(Vector3d(0.0f,2.0f-2.0f*changeInertia,0.0f));
		if(moveSpeedT<85.0f)
		{
			Transform rallto;
			rallto=UDfighers[0].UDMplane;
			rallto.Translate(Vector3d(0.0f,50.0f,0.0f));
			UDfighers[0].TurnTom(rallto.RefPos());
			UDfighers[0].UDPstate.NextState();
			UDfighers[0].UDPstate.MaxAngleSpeed=CRad(3.0);

			//UDfighers[0].UDMplane.Rotate(Vector3d(1.0f,0.0f,0.0f)*CRad(changeInertia*6.0f-6.0f));
		}
	}
	

}

void DrawDataLine1 (void)
{
	glColor3f(0.0f,1.0f,0.0f);
	if( GetTickCount() - g_dwLastFPS >= 1000 )					// When A Second Has Passed...
	{
		g_dwLastFPS = GetTickCount();							// Update Our Time Variable
		g_nFPS = g_nFrames;										// Save The FPS
		g_nFrames = 0;											// Reset The FPS Counter
	}
	if(!IsSkip)
	g_nFrames++;												// Increment Our FPS Counter
									// Build The Title String
	sprintf( szTitle, "%4.8f time,%2.0d FPS",oneframetime,g_nFPS);
	
	//if( g_fVBOSupported )									// Include A Notice About VBOs
	//strcat( szTitle, ", VBO" );

	if(ShaderLight)
		strcat( szTitle, ", Light:Shader" );
	else
		strcat( szTitle, ", Light:glLight" );
	if((IsSupportFBO)&&(ShaderLight)&&UseShadow)
	{
		if(ShadowLevel>2)
			strcat( szTitle, ", Shadow:High" );
		else
			strcat( szTitle, ", Shadow:Low" );
	}
	else
		strcat( szTitle, ", Shadow:Off" );

	if(ShaderWater)
	{
		strcat( szTitle, ", Water:High" );
	}
	else
		strcat( szTitle, ", Water:Low" );
	char tmpDDL1[32]={0};
	sprintf(tmpDDL1,"Bloom");
	if(ShaderBloom)
		strcat( szTitle, tmpDDL1 );

	glColor3f(1.0f,1.0f,1.0f);
}
void DrawFightersData(float DFDX, float DFDY, float DFDZ, float DFDL=-1.0, char DFDname[64]=" ", int DFDflag = 1, bool DFDlockselect=false,int mLife=0)//飞机屏幕坐标XYZ,与玩家的距离,飞机名字,飞机标示:0为一般敌人/1为红色目标/2为友军/3为第三方势力,是否被锁定
{

	char DFDDistance[32]={0};
	char flag[16]={0};
	char strSpeed[64]={0};
	if(DFDZ < 1.0f )
	{
		if(DFDflag==0)
		{
			glColor3f(0.0f,1.0f,0.0f);
			if(DFDlockselect)
			{
				if(lockflash>15)
					glPrintW(DFDX,DFDY);
			}
			else
				glPrintW(DFDX,DFDY);
			
		}
		if(DFDflag==1)
		{
			glColor3f(1.0f,0.0f,0.0f);
			sprintf(flag,"   TGT");
			glPrint( (int)(DFDX  - 68.0f*((float)winheight/600.0f)) ,   (int)(DFDY   + 2.0f*((float)winheight/600.0f)),  flag   , 0 );
			glColor3f(0.0f,1.0f,0.0f);
			if(DFDlockselect)
			{
				if(lockflash>15)
					glPrintW(DFDX,DFDY);
			}
			else
				glPrintW(DFDX,DFDY);
			
		}
		if(DFDflag==2)
		{
			glColor3f(0.0f,0.5f,1.0f);
			sprintf(flag,"Friend");
			glPrint( (int)(DFDX  - 68.0f*((float)winheight/600.0f)) ,  (int)(DFDY   + 2.0f*((float)winheight/600.0f)) ,  flag   , 0 );
			glPrint( (int)(DFDX  + 8.0f*((float)winheight/600.0f)),   (int)(DFDY  + 2.0f*((float)winheight/600.0f)) ,   DFDname , 0 );
		}
		if(DFDflag==3)
		{
			glColor3f(1.0f,1.0f,0.0f);
			sprintf(flag,"NOdata");
			glPrint( (int)(DFDX  - 68.0f*((float)winheight/600.0f)),   (int)(DFDY   + 2.0f*((float)winheight/600.0f)) ,  flag   , 0 );
			if(DFDlockselect)
			{
				if(lockflash>15)
					glPrintW(DFDX,DFDY);
			}
			else
				glPrintW(DFDX,DFDY);
		
		}
	}
		

	sprintf(strSpeed,"%d%%",mLife);
	sprintf(DFDDistance,"%d",(int)(sqrt(DFDL)*0.10f-10.0f));
	if( DFDZ < 1.0f )		
	{
		glPrint( (int)(DFDX  - 40.0f*((float)winheight/600.0f)) ,   (int)(DFDY  - 18.0f*((float)winheight/600.0f)) ,  strSpeed   , 0 );
		glPrint( (int)(DFDX  + 8.0f*((float)winheight/600.0f)) ,   (int)(DFDY  - 18.0f*((float)winheight/600.0f)) ,  DFDDistance   , 0 );
		if(DFDlockselect)
			glPrint( (int)(DFDX  + 8.0f*((float)winheight/600.0f)) ,   (int)(DFDY  + 2.0f*((float)winheight/600.0f)) ,   DFDname , 0 );
	}
	glColor3f(1.0f,1.0f,1.0f);

	
}
/*
void ShowUNITSFlag(double SUFposX,double SUFposY,double SUFposZ,int SUFnum)
{
		GLint viewport[4];
		GLdouble mvmatrix[16],projmatrix[16];
		GLdouble SUFwinX,SUFwinY,SUFwinZ;
		glGetIntegerv(GL_VIEWPORT,viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
		glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
		gluProject(0.0,0.0,0.0,mvmatrix,projmatrix,viewport,&SUFwinX,&SUFwinY,&SUFwinZ);


		float tmpX=(float)(MFighter.RefPos()(0)-SUFposX);
		float tmpY=(float)(MFighter.RefPos()(1)-SUFposY);
		float tmpZ=(float)(MFighter.RefPos()(2)-SUFposZ);
		float SUFDistance=tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ;
		//SUFDistance=sqrt(SUFDistance);
		UDfighers[SUFnum].UDwinl=SUFDistance;
		UDfighers[SUFnum].UDwinx=(float)SUFwinX;
		UDfighers[SUFnum].UDwiny=(float)SUFwinY;
		UDfighers[SUFnum].UDwinz=(float)SUFwinZ;

		glEnable(GL_BLEND);
		if((SUFwinZ<1.0)&&(SUFDistance<(tmpredarRenge*tmpredarRenge)))
			DrawFightersData((float)SUFwinX,(float)SUFwinY,(float)SUFwinZ,SUFDistance,UDfighers[SUFnum].UDname,UDfighers[SUFnum].UDflag,false,UDfighers[SUFnum].UDlife);
		
		//if(UDfighers[SUFnum].UDlockselect)
			//lockmove(SUFwinX,SUFwinY,SUFwinZ);
		//glDisable(GL_BLEND);

		if(UDfighers[SUFnum].UDwinl<(tmpredarRenge*tmpredarRenge))//目标距离
		{
			if(UDfighers[SUFnum].UDwinz<1.0f)//目标在屏幕前方
			if(!(UDfighers[SUFnum].UDflag==2))//目标不是友军
			if(UDfighers[SUFnum].UDlife>0)//目标还存在
			if( (UDfighers[SUFnum].UDwinx<winwidth) && (UDfighers[SUFnum].UDwinx>0.0) && (UDfighers[SUFnum].UDwiny<winheight) && (UDfighers[SUFnum].UDwiny>0.0) )//目标可见
			{

				locklists[locklists_index].TGTnum=SUFnum;
				//locklists[locklists_index].TGTwinL=UDfighers[SUFnum].UDwinl;
				//locklists[locklists_index].TGTwinLin=(UDfighers[SUFnum].UDwinx-winwidth*0.5)*(UDfighers[SUFnum].UDwinx-winwidth*0.5)+(UDfighers[SUFnum].UDwiny-winheight*0.5)*(UDfighers[SUFnum].UDwiny-winheight*0.5);
				locklists_index=locklists_index+1;
			}
		}
		else
		{
			UDfighers[SUFnum].UDlockselect=false;
		}

		

}
*/
void DrawDataLine2 (double high,double news,double latitude)
{
	char szshowSpeed[16]={0};
	char szshowHigh[16]={0};
	//char szshowPitch[16]={0};
	char szshownews[512]={0};
	char szshowflag1[4]={0};
	char szshowflag2[4]={0};
	char test[128]={0};
	char PlayerHP[128]={0};
	char StrWarning[128]={0};
	

	//testNum=UDfighers[0].UDMplane.RefPos()(2);
	
	sprintf(PlayerHP,"%d%%",UDfighers[0].UDlife);
	sprintf(StrWarning,"WARNING");
	sprintf(test,"%f %f %f",testNum,testNum2,testNum3);

	sprintf(szshowflag1,"|");
	sprintf(szshowflag2,"|");
	//sprintf(szshownews,"|");
	//sprintf(szshowPitch,"Pitch:%3.0f",latitude);
	/*
	for(int i=11;i>0;i--)
	{
		int tmp= (int)news-23+i*4;
		char tmpC[8]={0};
		if(tmp>180)
			tmp=tmp-360;
		if(tmp<-179)
			tmp=tmp+360;


		switch (tmp)
		{
			case -1:sprintf(tmpC,"  N |");break;
			case 0:sprintf(tmpC,"  N |");break;
			case 1:sprintf(tmpC,"  N |");break;
			case 2:sprintf(tmpC,"  N |");break;
			case 44:sprintf(tmpC,"  NE|");break;
			case 45:sprintf(tmpC,"  NE|");break;
			case 46:sprintf(tmpC,"  NE|");break;
			case 47:sprintf(tmpC,"  NE|");break;
			case 89:sprintf(tmpC,"  E |");break;
			case 90:sprintf(tmpC,"  E |");break;
			case 91:sprintf(tmpC,"  E |");break;
			case 92:sprintf(tmpC,"  E |");break;
			case 134:sprintf(tmpC,"  EW|");break;
			case 135:sprintf(tmpC,"  EW|");break;
			case 136:sprintf(tmpC,"  EW|");break;
			case 137:sprintf(tmpC,"  EW|");break;
			case 179:sprintf(tmpC,"  W |");break;
			case 180:sprintf(tmpC,"  W |");break;
			case -179:sprintf(tmpC,"  W |");break;
			case -178:sprintf(tmpC,"  W |");break;
			case -136:sprintf(tmpC,"  WS|");break;
			case -135:sprintf(tmpC,"  WS|");break;
			case -134:sprintf(tmpC,"  WS|");break;
			case -133:sprintf(tmpC,"  WS|");break;
			case -91:sprintf(tmpC,"  S |");break;
			case -90:sprintf(tmpC,"  S |");break;
			case -89:sprintf(tmpC,"  S |");break;
			case -88:sprintf(tmpC,"  S |");break;
			case -46:sprintf(tmpC,"  SE|");break;
			case -45:sprintf(tmpC,"  SE|");break;
			case -44:sprintf(tmpC,"  SE|");break;
			case -43:sprintf(tmpC,"  SE|");break;
			default:sprintf(tmpC,"%4.0d|",tmp);
		}


		
		strcat(szshownews,tmpC);
		

	}
	*/

	
	sprintf(szshowSpeed,"%4.0f-",moveSpeed*60.0f*60.0f*60.0f*2000.0f/10000.0f);
	sprintf(szshowHigh,"-%d",(int)(high*0.1));
	
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
	


	
	
	//sprintf(szshownews,"-%3.0f-%3.0f-%3.0f-%3.0f-%3.0f-%3.0f-%3.0f-%3.0f-%3.0f-%3.0f-%3.0f-",szshownews-5.0,,szshownews-4.0,szshownews-3.0,szshownews-2.0,szshownews-1.0,szshownews,szshownews+1.0,szshownews+2.0,szshownews+3.0,szshownews+4.0,szshownews+5.0);
	//glDisable(GL_BLEND);
	//glPrint(winwidth*0.7f,winheight*0.5-16,szshowSpeed,0,true);
	//glPrint(winwidth*0.25f,winheight*0.5-16,szshowHigh,0,true);
	//glPrint(winwidth*0.25f,winheight*0.5-32,szshowPitch,0);
	//glEnable(GL_BLEND);
	//glPrint(130,400,szshownews,0);
	//glPrint(402,416,szshowflag1,0);
	//glPrint(402,384,szshowflag2,0);

	glColor3f(0.0f,1.0f,0.0f);
	if(PlayerLocked)
		glColor3f(1.0f,0.0f,0.0f);
	glPrint((GLint)(winwidth*0.65f),winheight/2-16,szshowSpeed,0,true);
	glPrint((GLint)(winwidth*0.29f),winheight/2-16,szshowHigh,0,true);
	glPrint((GLint)(winwidth*0.85f),winheight/5-16,PlayerHP,0,true);
	if(voiceSourceAWACS->State!=AL_PLAYING)
	{
		glPrint(0,winheight-16,szTitle,0);
		glPrint(0,winheight-32,szVERSION,0);
		glPrint(0,winheight-48,cpubrand,0);
	}
	glPrint(winwidth/4,0,test,0);
	glColor3f(1.0f,1.0f,1.0f);

	glColor3f(1.0f,0.0f,0.0f);
	if(PlayerLocking)
	glPrint((GLint)(winwidth*0.47f),winheight*3/5-16,StrWarning,0,true);

	glColor3f(1.0f,1.0f,1.0f);
	//int txtpringsize=((winheight/30)/8)*8;
	//MyFont.DrawTXT(winwidth,winheight,128,128,txtpringsize,txtpringsize,winwidth);
}


void fireShell()
{

	Transform tmp2=UDfighers[0].UDMplane;
	//tmp2.RotateInternal(Vector3d(1.0f, 0.0f, 0.0f) * CRad(-turnX * 8));
	tmp2.TranslateInternal(Vector3d(5.0f, -5.8f+turnX*143.2f*0.0f, -50.0f));
	
	//testNum2=turnX;
	Transform tmp=tmp2;
	tmp.TranslateInternal(Vector3d((float(rand()%10)-5.0f)/5.0f, (float(rand()%10)-5.0f)/5.0f+shellturn, 200.0f+moveSpeed * 2000));
	
	if(lockflash%3==0)
	{
		Shell.AddNewShell(float(tmp2.RefPos()(0)),float(tmp2.RefPos()(1)),float(tmp2.RefPos()(2)),float(tmp2.RefPos()(0) - tmp.RefPos()(0)),float(tmp2.RefPos()(1) - tmp.RefPos()(1)),float(tmp2.RefPos()(2) - tmp.RefPos()(2)),0,0);
		for(int i=0;i<locklists_index;i++)
			Shell.AddNewShell(float(tmp2.RefPos()(0)),float(tmp2.RefPos()(1)),float(tmp2.RefPos()(2)),float(tmp2.RefPos()(0) - tmp.RefPos()(0)),float(tmp2.RefPos()(1) - tmp.RefPos()(1)),float(tmp2.RefPos()(2) - tmp.RefPos()(2)),locklists[i].TGTnum,0);

		if(!GunFiresound)
		{
			GunFiresound=true;
			voiceSourceGunFire->Play(true);
//			FMOD_System_PlaySound(sys, FMOD_CHANNEL_REUSE, soundGunFire, 0, &channelGunFire);
		
		}
		
	}

}
void PlayerControl()
{




/*
	if (g_keys->keyDown [VK_F1] == TRUE)						// Is F1 Being Pressed?
	{
		ToggleFullscreen (g_window);							// Toggle Fullscreen Mode
	}*/
	if (g_keys->keyDown [VK_PRIOR] == TRUE)	
		testNum=testNum+0.003f;
	if (g_keys->keyDown [VK_NEXT] == TRUE)
		testNum=testNum-0.003f;

	if (g_keys->keyDown [VK_HOME] == TRUE)	
		testNum2=testNum2+0.003f;
	if (g_keys->keyDown [VK_END] == TRUE)
		testNum2=testNum2-0.003f;


	if ((g_keys->keyDown [KeyInput.m_keyboardLeft] == TRUE)||KeyInput.m_IskeyLeft)					
	{
		if(KeyInput.m_IskeyLeft)
			InertiaZ=InertiaZ-InertiaDir*KeyInput.m_Left;
		else
			InertiaZ=InertiaZ-InertiaDir;
		if(InertiaZ<-InertiaLimit)
			InertiaZ=-InertiaLimit;
	}
	
	if ((g_keys->keyDown [KeyInput.m_keyboardRight] == TRUE)||KeyInput.m_IskeyRight)					
	{
		
		if(KeyInput.m_IskeyRight)
			InertiaZ=InertiaZ+InertiaDir*KeyInput.m_Right;
		else
			InertiaZ=InertiaZ+InertiaDir;
		if(InertiaZ>InertiaLimit)
			InertiaZ=InertiaLimit;
	}
	//testNum=KeyInput.m_keyboardUp;
	if ((g_keys->keyDown [KeyInput.m_keyboardUp] == TRUE)||KeyInput.m_IskeyUp)					
	{
//		testNum=KeyInput.m_keyboardUp*10;
		if(KeyInput.m_IskeyUp)
			InertiaX=InertiaX+InertiaDir*KeyInput.m_Up;
		else
			InertiaX=InertiaX+InertiaDir;
		if(InertiaX>InertiaLimit)
			InertiaX=InertiaLimit;
	}
	if ((g_keys->keyDown [KeyInput.m_keyboardDown] == TRUE)||KeyInput.m_IskeyDown)					
	{
		if(KeyInput.m_IskeyDown)
			InertiaX=InertiaX-InertiaDir*KeyInput.m_Down;
		else
			InertiaX=InertiaX-InertiaDir;
		if(InertiaX<-InertiaLimit)
			InertiaX=-InertiaLimit;
	}
	if ((g_keys->keyDown [KeyInput.m_keyboardSpeedUp] == TRUE)||KeyInput.m_IskeySpeedUp)					
	{
		moveSpeed=moveSpeed+Acceleration;
		if(moveSpeed>MAXSpeed)
			moveSpeed=MAXSpeed;
		else
			InertiaSpeed=InertiaSpeed+1.0f;
		if(InertiaSpeed>InertiaSpeedLimit)
			InertiaSpeed=InertiaSpeedLimit;
		//DrawEffectImpact=true;
	}
	if ((g_keys->keyDown [KeyInput.m_keyboardSpeedDown] == TRUE)||KeyInput.m_IskeySpeedDown)					
	{
		moveSpeed=moveSpeed-Acceleration;
		if(moveSpeed<MINSpeed)
			moveSpeed=MINSpeed;
		else
			InertiaSpeed=InertiaSpeed-1.0f;
		if(InertiaSpeed<-InertiaSpeedLimit)
			InertiaSpeed=-InertiaSpeedLimit;
	}
	if ((g_keys->keyDown [KeyInput.m_keyboardL] == TRUE)||KeyInput.m_IskeyL)
	{
		turnY=-TurnRateY;
	}
	if ((g_keys->keyDown [KeyInput.m_keyboardR] == TRUE)||KeyInput.m_IskeyR)
	{
		turnY=TurnRateY;
	}
	if (g_keys->keyDown [VK_SPACE] && !KeySPACE )
	{
		KeySPACE=true;
	}
	if(!g_keys->keyDown [VK_SPACE])
		KeySPACE=false;

	if(g_keys->keyDown[KeyInput.m_keyboardGun]||KeyInput.m_IskeyGun)
	{
		//Shell.AddNewShell(,,,,,,0,0);
		fireShell();
	
	}
	else
	{
		GunFiresound=false;
		if(isinitsound)
			voiceSourceGunFire->Stop();
//		FMOD_Channel_Stop(channelGunFire);
	
	}
	if ((g_keys->keyDown [KeyInput.m_keyboardMap]||KeyInput.m_IskeyMap) && !KeyT )
	{
		KeyT=true;

	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardMap]||KeyInput.m_IskeyMap))
		KeyT=false;
	if ((g_keys->keyDown [KeyInput.m_keyboardMissle]||KeyInput.m_IskeyMissle) && !KeyF )
	{
		KeyF=true;
		if(timer[0]<1)
		{
			timer[0]=60;
			fireMissle();
		}
	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardMissle]||KeyInput.m_IskeyMissle))
		KeyF=false;

	if ((g_keys->keyDown [KeyInput.m_keyboardLock]||KeyInput.m_IskeyLock) && !KeyQ )	
	{
		KeyQ=true;
		lockselect=!lockselect;
		initlocks();
		selectLockTGT();

	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardLock]||KeyInput.m_IskeyLock))
		KeyQ=false;

	
	
	
	
	if ((g_keys->keyDown [KeyInput.m_keyboardViewUp] == TRUE)||KeyInput.m_IskeyViewUp)	
	{
		ViewTurnY=ViewTurnY+0.005f;
		if(ViewTurnY>1.0f)
			ViewTurnY=1.0f;
		if(KeyInput.m_IskeyViewUp)
			if(ViewTurnY>KeyInput.m_ViewUp)
				ViewTurnY=ViewTurnY-0.005f;
	}/*
	else
	{
		if(ViewTurnY>=0.02f)
			ViewTurnY=ViewTurnY-0.02f;
		if((ViewTurnY<0.02f)&&(ViewTurnY>0.0f))
			ViewTurnY=0.0f;
	}*/
	if ((g_keys->keyDown [KeyInput.m_keyboardViewDown] == TRUE)||KeyInput.m_IskeyViewDown)	
	{
		ViewTurnY=ViewTurnY-0.005f;
		if(ViewTurnY<-1.0f)
			ViewTurnY=-1.0f;
		if(KeyInput.m_IskeyViewDown)
			if(ViewTurnY<-KeyInput.m_ViewDown)
				ViewTurnY=ViewTurnY+0.005f;
	}/*
	else
	{
		if(ViewTurnY<=-0.02f)
			ViewTurnY=ViewTurnY+0.02f;
		if((ViewTurnY>-0.02f)&&(ViewTurnY<0.0f))
			ViewTurnY=0.0f;
	}*/
	if ((g_keys->keyDown [KeyInput.m_keyboardViewLeft] == TRUE)||KeyInput.m_IskeyViewLeft)	
	{
			ViewTurnX=ViewTurnX+0.005f;
		if(ViewTurnX>1.0f)
			ViewTurnX=1.0f;
		if(KeyInput.m_IskeyViewLeft)
			if(ViewTurnX>KeyInput.m_ViewLeft)
				ViewTurnX=ViewTurnX-0.005f;
	}/*
	else
	{
		if(ViewTurnX>=0.02f)
			ViewTurnX=ViewTurnX-0.02f;
		if((ViewTurnX<0.02f)&&(ViewTurnX>0.0f))
			ViewTurnX=0.0f;
	}*/
	if ((g_keys->keyDown [KeyInput.m_keyboardViewRight] == TRUE)||KeyInput.m_IskeyViewRight)	
	{
			ViewTurnX=ViewTurnX-0.005f;
		if(ViewTurnX<-1.0f)
			ViewTurnX=-1.0f;
		if(KeyInput.m_IskeyViewRight)
			if(ViewTurnX<-KeyInput.m_ViewRight)
				ViewTurnX=ViewTurnX+0.005f;
	}/*
	else
	{
		if(ViewTurnX<=-0.02f)
			ViewTurnX=ViewTurnX+0.02f;
		if((ViewTurnX>-0.02f)&&(ViewTurnX<0.0f))
			ViewTurnX=0.0f;
	}
*/
	if ((g_keys->keyDown [KeyInput.m_keyboardViewReset] == TRUE)||KeyInput.m_IskeyViewReset)	
	{
		ViewTurnX=0.0f;
		ViewTurnY=0.0f;
	}
/*
	if (g_keys->keyDown ['R'] && !KeyR )	
	{
		FILE	*m_Filefighter;
		
		if(ModelsNO==707)
			ModelsNO=499;

		KeyR=true;
		
		char tmpNum1[16]={0};
		sprintf(tmpNum1,"0%d",ModelsNO);
		char tmpNum2[16]={0};
		sprintf(tmpNum2,"0020/",ModelsNO);
		strcat(tmpNum2,tmpNum1);
		strcat(tmpNum2,"/0002");

		if (!((m_Filefighter=fopen(tmpNum2,"rb"))==NULL))
		{
			delete m_nj;
			m_nj= new CLoadACMD;
			m_nj->Init(tmpNum2,0,1);
		}
		ModelsNO=ModelsNO+1;

	}
	if(!g_keys->keyDown ['R'])
		KeyR=false;
*/

	if ((g_keys->keyDown [KeyInput.m_keyboardSetHUD]||KeyInput.m_IskeySetHUD) && !pushkeyHUD )
	{
		pushkeyHUD=true;
		IsHUD=!IsHUD;

	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardSetHUD]||KeyInput.m_IskeySetHUD))
		pushkeyHUD=false;

	if ((g_keys->keyDown [KeyInput.m_keyboardStart]||KeyInput.m_IskeyStart) && !KeyStart )
	{
		KeyStart=true;
		GamePause=!GamePause;
		SoundPause();
	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardStart]||KeyInput.m_IskeyStart))
		KeyStart=false;

	if ((g_keys->keyDown [KeyInput.m_keyboardSelect]||KeyInput.m_IskeySelect) && !KeySelect )
	{
		KeySelect=true;
	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardSelect]||KeyInput.m_IskeySelect))
		KeySelect=false;
	
	if ((g_keys->keyDown [KeyInput.m_keyboardOther]||KeyInput.m_IskeyOther) && !KeyOther )
	{
		KeyOther=true;
	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardOther]||KeyInput.m_IskeyOther))
		KeyOther=false;
}
void UIPlayerControl()
{
	if ((g_keys->keyDown [KeyInput.m_keyboardLeft] == TRUE)||KeyInput.m_IskeyLeft)					
	{}
	
	if ((g_keys->keyDown [KeyInput.m_keyboardRight] == TRUE)||KeyInput.m_IskeyRight)					
	{}

	if ((g_keys->keyDown [KeyInput.m_keyboardUp] == TRUE)||KeyInput.m_IskeyUp)					
	{}

	if ((g_keys->keyDown [KeyInput.m_keyboardDown] == TRUE)||KeyInput.m_IskeyDown)					
	{}

	if ((g_keys->keyDown [KeyInput.m_keyboardSpeedUp] == TRUE)||KeyInput.m_IskeySpeedUp)					
	{}

	if ((g_keys->keyDown [KeyInput.m_keyboardSpeedDown] == TRUE)||KeyInput.m_IskeySpeedDown)					
	{}

	if ((g_keys->keyDown [KeyInput.m_keyboardL] == TRUE)||KeyInput.m_IskeyL)
	{}

	if ((g_keys->keyDown [KeyInput.m_keyboardR] == TRUE)||KeyInput.m_IskeyR)
	{}

	if(g_keys->keyDown[KeyInput.m_keyboardGun]||KeyInput.m_IskeyGun)
	{}

	if ((g_keys->keyDown [KeyInput.m_keyboardMap]||KeyInput.m_IskeyMap) && !KeyT )
	{
		KeyT=true;
	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardMap]||KeyInput.m_IskeyMap))
		KeyT=false;

	if ((g_keys->keyDown [KeyInput.m_keyboardMissle]||KeyInput.m_IskeyMissle) && !KeyF )
	{
		KeyF=true;
	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardMissle]||KeyInput.m_IskeyMissle))
		KeyF=false;


	if ((g_keys->keyDown [KeyInput.m_keyboardLock]||KeyInput.m_IskeyLock) && !KeyQ )	
	{
		KeyQ=true;
	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardLock]||KeyInput.m_IskeyLock))
		KeyQ=false;

	if ((g_keys->keyDown [KeyInput.m_keyboardViewUp] == TRUE)||KeyInput.m_IskeyViewUp)
	{}
	if ((g_keys->keyDown [KeyInput.m_keyboardViewDown] == TRUE)||KeyInput.m_IskeyViewDown)
	{}
	if ((g_keys->keyDown [KeyInput.m_keyboardViewLeft] == TRUE)||KeyInput.m_IskeyViewLeft)
	{}
	if ((g_keys->keyDown [KeyInput.m_keyboardViewRight] == TRUE)||KeyInput.m_IskeyViewRight)
	{}

	if ((g_keys->keyDown [KeyInput.m_keyboardViewReset] == TRUE)||KeyInput.m_IskeyViewReset)	
	{}

	if ((g_keys->keyDown [KeyInput.m_keyboardSetHUD]||KeyInput.m_IskeySetHUD) && !pushkeyHUD )
	{
		pushkeyHUD=true;
	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardSetHUD]||KeyInput.m_IskeySetHUD))
		pushkeyHUD=false;

	if ((g_keys->keyDown [KeyInput.m_keyboardStart]||KeyInput.m_IskeyStart) && !KeyStart )
	{
		KeyStart=true;
		GamePause=!GamePause;
		SoundPause();
	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardStart]||KeyInput.m_IskeyStart))
		KeyStart=false;

	if ((g_keys->keyDown [KeyInput.m_keyboardSelect]||KeyInput.m_IskeySelect) && !KeySelect )
	{
		KeySelect=true;
	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardSelect]||KeyInput.m_IskeySelect))
		KeySelect=false;
	
	if ((g_keys->keyDown [KeyInput.m_keyboardOther]||KeyInput.m_IskeyOther) && !KeyOther )
	{
		KeyOther=true;
	}
	if(!(g_keys->keyDown [KeyInput.m_keyboardOther]||KeyInput.m_IskeyOther))
		KeyOther=false;
}
void StartShow()
{
	StartShowTime=StartShowTime-1;
	if(StartShowTime<=0)
		isPlayerControl=true;
	ViewTurnX=(float)StartShowTime/150.0f;

}
void Update (DWORD milliseconds)								// Perform Motion Updates Here
{
	playTime=playTime+1;
	if((playTime%FrameSkip)!=0)
		IsSkip=true;
	else
		IsSkip=false;
	
	if(playTime%4==0)
		Video.DrawVideo();
//	FMOD_System_Update(sys);
	
	if(StartShowTime>0)
		StartShow();
	if (g_keys->keyDown [VK_ESCAPE] == TRUE)					// Is ESC Being Pressed?
	{
		TerminateApplication (g_window);						// Terminate The Program
	}
	KeyInput.UpData();
	if(!GamePause)
	{
		Inertia();
		if(isPlayerControl)
			PlayerControl();
	}
	else
		UIPlayerControl();


	

	//	MissleSign.UDMplane=MFighter;
	//	MissleSign.UDMplane.TranslateInternal(Vector3d(0.0f, 0.0f, -100.0f));
	//ViewPoint.UDPstate.MaxSpeed=0.0;
	//ViewPoint.UDPstate.MaxAngleSpeed=50.0;
	//ViewPoint.UDPstate.VelocityResistance=0.0;
	//ViewPoint.UDPstate.AngleVelocityResistance=0.1;
	//	MissleSign.TurnTo(MisslePosition);
	//	MissleSign.UDPstate.NextState();


	
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
/*
void testFPS (void)
{
	QueryPerformanceFrequency(&feq);//每秒跳动次数
	QueryPerformanceCounter(&t3);//测后跳动次数 
	oneframetimeT=((double)t3.QuadPart-(double)t1.QuadPart)/((double)feq.QuadPart);//时间差秒
	//Delay((oneframetimelimit-oneframetime)*1000000);
	//QueryPerformanceCounter(&t1);//测前跳动次数
}
*/

void DrawRadioTXT(void)
{

	if(voiceSourceAWACS->State!=AL_PLAYING)
		return;
	glEnable(GL_BLEND);
	glColor3f(0.0f,0.0f,1.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
	glPrint(winwidth/2-20,winheight-winheight/36,"AWACS",0,false);
	MyFont.DrawTXT(winwidth,winheight,winwidth/8,winheight/16,((winheight/30)/8)*12,((winheight/30)/8)*12,0);
	glColor3f(1.0f,1.0f,1.0f);
}
void DrawBom(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glEnable(GL_BLEND);
	glPushMatrix();	
	for(int i=0;i<MAXBom;i++)
	{
		if(Bomings[i].life>0)
		{
			Vector3d bompos;
			bompos = MView.Matrix() * Vector3d(Bomings[i].x,Bomings[i].y,Bomings[i].z)+MView.RefPos();
			Bomings[i].DrawBom((float)bompos(0),(float)bompos(1),(float)bompos(2),&PlaneBom[0]);
		}
		/*
		if(Boms[i].Frame>-1)
		{
			Vector3d bompos;
			bompos = MView.Matrix() * Boms[i].pos+MView.RefPos();
			for(int j=0;j<BomsNumber;j++)
			{
				if((BomsSets[j].ShowTimeStart <= Boms[i].Frame) && (BomsSets[j].ShowTimeEnd >= Boms[i].Frame))
				{
					int tmptime1=BomsSets[j].ShowTimeEnd-BomsSets[j].ShowTimeStart;
					int tmptime2=BomsSets[j].ShowTimeEnd-Boms[i].Frame;
					if(tmptime1<1)
						tmptime1=tmptime2;
					float tmpbili=(float)tmptime2/(float)tmptime1;

					int tmpsize1=BomsSets[j].SizeEnd-BomsSets[j].SizeStart;
					int tmpsize2=BomsSets[j].SizeEnd-(int)((float)tmpsize1*tmpbili);

					int tmpalpha1=BomsSets[j].ColorAlphaEnd-BomsSets[j].ColorAlphaStart;
					float tmpalpha2=((float)BomsSets[j].ColorAlphaEnd-(float)tmpalpha1*tmpbili)/255.0f;

					if(BomsSets[j].SizeEnd==BomsSets[j].SizeStart)
						tmpsize2=BomsSets[j].SizeEnd;
					if(BomsSets[j].ColorAlphaEnd==BomsSets[j].ColorAlphaStart)
						tmpalpha2=(float)BomsSets[j].ColorAlphaEnd;

					glPrintBom1((float)bompos(0),(float)bompos(1),(float)bompos(2),tmpsize2,tmpalpha2,BomsSets[j].Pnum);
				}
			}
			Boms[i].Frame=Boms[i].Frame+1;
			if(Boms[i].Frame>BomsSets[BomsNumber-1].ShowTimeEnd )
				Boms[i].Frame=-1;
		}
		*/
		/*
		if(Boms[i].Frame>-1)
		{
			Vector3d bompos;
			bompos = MView.Matrix() * Boms[i].pos+MView.RefPos();
			glPrintBom((float)bompos(0),(float)bompos(1),(float)bompos(2),Boms[i].Frame);
			if(lockflash%4==0)
			Boms[i].Frame=Boms[i].Frame+1;
			if(Boms[i].Frame>11)
				Boms[i].Frame=-1;
		}
		*/
	}
	for(int num=1;num<maxUnits;num++)
	{
		if((UDfighers[num].smokeTime>70)&&((UDfighers[num].smokeTime%5)==0))
		{
			UDfighers[num].UDMplane.TranslateInternal(Vector3d(0.0,0.0,5.0));
			Bomings[Bomings_index].NewBom((float)UDfighers[num].UDMplane.RefPos()(0),(float)UDfighers[num].UDMplane.RefPos()(1),(float)UDfighers[num].UDMplane.RefPos()(2),&PlaneBom[0]);
			Bomings_index=Bomings_index+1;
			if(Bomings_index==MAXBom)
			Bomings_index=0;
		}
	}
	glPopMatrix();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

	//glEnable(GL_DEPTH_TEST);
}
void DrawSmoke(void)
{



	//PSmokes.DrawSmoke(UDfighers[0].UDMplane.RefPos(),MView,winwidth,winheight,tmpLookRenge);

	//glEnable(GL_CULL_FACE);

//	smokeArray_index=0;
	//glDisable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);

	//glEnable(GL_BLEND);
//	if(SmokeNumber==0)
//		return;
//	for(int num=1;num<maxUnits;num++)
//	{
		
//		if((UDfighers[num].UDlife>0)||(UDfighers[num].smokeTime>0))
//		{
//			UDfighers[num].smokeTime=UDfighers[num].smokeTime-1;
			//if(((lockflash%3)==0)&&(UDfighers[num].UDlife>0))
			//UDfighers[num].setLinePos();
			//UDfighers[num].setpos(((int)rand())%SmokeNumber);
/*
			if(UDfighers[num].UDwinl<(tmpLookRenge*tmpLookRenge*1.5))
			{
				
				UDfighers[num].PrintLinePos(MView);
				//qsort((void *) &UDfighers->UDposz, 100, sizeof(float UDfighers), (compfn)Compare );
				/*
				for(int i=0;i<MAXUNITSMOKE;i++)
				{
					GLint viewport[4];
					GLdouble mvmatrix[16],projmatrix[16];
					GLdouble SUFwinX,SUFwinY,SUFwinZ;
					glGetIntegerv(GL_VIEWPORT,viewport);
					glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
					glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
					gluProject(UDfighers[num].UDposx[i],UDfighers[num].UDposy[i],UDfighers[num].UDposz[i],mvmatrix,projmatrix,viewport,&SUFwinX,&SUFwinY,&SUFwinZ);
					Smokes[i].x=UDfighers[num].UDposx[i];
					Smokes[i].y=UDfighers[num].UDposy[i];
					Smokes[i].z=UDfighers[num].UDposz[i];
					Smokes[i].smokeNum=UDfighers[num].smokeNum[i];
					Smokes[i].winx=(float)SUFwinX;
					Smokes[i].winy=(float)SUFwinY;
					Smokes[i].winz=(float)SUFwinZ;
					UDfighers[num].UDposx[i]=UDfighers[num].UDposx[i]+UDfighers[num].UDposxMove[i];
					UDfighers[num].UDposy[i]=UDfighers[num].UDposy[i]+UDfighers[num].UDposyMove[i];
					UDfighers[num].UDposz[i]=UDfighers[num].UDposz[i]+UDfighers[num].UDposzMove[i];
				}
				//qsort((void *) &Smokes, 100, sizeof(struct Smoke), (compfn)Compare );


				for(int i=0;i<MAXUNITSMOKE;i++)
				{
					//int tmp=i+UDfighers[num].UDposflag;
					int tmp=i;
					if(tmp==MAXUNITSMOKE)
						tmp=0;



					//float tmpx=
					//if(UDfighers[i].)
					if((Smokes[i].winz<1.0)&&(Smokes[i].winz>0.0))//可视范围内
					if((Smokes[i].winx>(-0.1*winwidth))&&(Smokes[i].winy>(-0.1*winheight))&&(Smokes[i].winx<(winwidth*1.1))&&(Smokes[i].winy<(winheight*1.1)))//窗口内
					{
						int smokelife=i-UDfighers[num].UDposflag;
						if(smokelife<0)
							smokelife=smokelife+MAXUNITSMOKE;
						if(smokelife>(MAXUNITSMOKE-10))
							smokelife=MAXUNITSMOKE-(smokelife-(MAXUNITSMOKE-10))*(MAXUNITSMOKE/10);
						else
						{
							if(smokelife<(MAXUNITSMOKE/2))
								smokelife=smokelife*2;
							else
								smokelife=MAXUNITSMOKE;
						
						}
						float alpha1;
						if(UDfighers[num].UDlife>0)
							alpha1=smokelife/(float)MAXUNITSMOKE;
						else
							alpha1=smokelife*(UDfighers[num].smokeTime/(float)MAXUNITSMOKE)/(float)MAXUNITSMOKE;
						Vector3d tmp3d;
						//tmp3d=MView.Matrix() * Vector3d(UDfighers[num].UDposx[tmp],UDfighers[num].UDposy[tmp],UDfighers[num].UDposz[tmp]) + MView.RefPos();
						tmp3d=MView.Matrix() * Vector3d(Smokes[tmp].x,Smokes[tmp].y,Smokes[tmp].z) + MView.RefPos();
						//if(!GraphicsLOW)
						//glPrintSmoke((float)tmp3d(0),(float)tmp3d(1),(float)tmp3d(2),alpha1,Smokes[i].smokeNum);
						

					}
				}*/
		//	}
//		}
//	}
	/*
	for(int num=0;num<maxUnits;num++)
	{
		for(int num2=0;num2<MAXUNITMISSLES;num2++)
		{
			if((UDfighers[num].UNITMissles[num2].UDlife>0)||(UDfighers[num].UNITMissles[num2].smokeTime>0))
			{
				UDfighers[num].UNITMissles[num2].smokeTime = UDfighers[num].UNITMissles[num2].smokeTime - 1;
				if(UDfighers[num].UNITMissles[num2].UDlife>0)
					UDfighers[num].UNITMissles[num2].setpos(((int)rand())%SmokeNumber);
				if(UDfighers[num].UNITMissles[num2].UDwinl<(tmpLookRenge*tmpLookRenge))
				{
					for(int i=0;i<MAXMISSLESMOKE;i++)
					{
						float SmokePosX;
						float SmokePosY;
						float SmokePosZ;
						float SmokeAlpha;
						float SmokeMAlpha;
						UDfighers[num].UNITMissles[num2].m_DrawSmoke(winwidth,winheight,i,SmokePosX,SmokePosY,SmokePosZ,SmokeAlpha,SmokeMAlpha);
						if((SmokeMAlpha>0.0f)||(SmokeAlpha>0.0f))
						{
							Vector3d tmp3d;
							tmp3d=MView.Matrix() * Vector3d(SmokePosX,SmokePosY,SmokePosZ) + MView.RefPos();
							if(SmokeMAlpha>0.0f)
							{

								glPrintSmokeM((float)tmp3d(0),(float)tmp3d(1),(float)tmp3d(2),SmokeMAlpha);
							
							
							}
							if(SmokeAlpha>0.0f)
							{
								if(!GraphicsLOW)
									glPrintSmoke((float)tmp3d(0),(float)tmp3d(1),(float)tmp3d(2),SmokeAlpha,UDfighers[num].UNITMissles[num2].smokeNum[i],UDfighers[num].UNITMissles[num2].UDposzSIZE[i]);
							}
						}
					}
				}
			}
		
		}
	
	}

*/
	/*
	for(int num=0;num<maxMissles;num++)
	{
		
		if((missle[num].UDlife>0)||(missle[num].smokeTime>0))
		{
			missle[num].smokeTime=missle[num].smokeTime-1;
			
			if(missle[num].UDlife>0)
			missle[num].setpos(((int)rand())%SmokeNumber);
			if(missle[num].UDlife>0)
			missle[num].setposF();
	
			if(missle[num].UDwinl<(tmpLookRenge*tmpLookRenge))
			{
				for(int i=0;i<MAXMISSLESMOKE;i++)
				{
					GLint viewport[4];
					GLdouble mvmatrix[16],projmatrix[16];
					GLdouble SUFwinX,SUFwinY,SUFwinZ;
					glGetIntegerv(GL_VIEWPORT,viewport);
					glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
					glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
					gluProject(missle[num].UDposx[i],missle[num].UDposy[i],missle[num].UDposz[i],mvmatrix,projmatrix,viewport,&SUFwinX,&SUFwinY,&SUFwinZ);
					Smokes[i].x=missle[num].UDposx[i];
					Smokes[i].y=missle[num].UDposy[i];
					Smokes[i].z=missle[num].UDposz[i];
					Smokes[i].smokeNum=missle[num].smokeNum[i];
					Smokes[i].winx=(float)SUFwinX;
					Smokes[i].winy=(float)SUFwinY;
					Smokes[i].winz=(float)SUFwinZ;
					Smokes[i].SmokeSize=missle[num].UDposzSIZE[i];
					missle[num].UDposzSIZE[i]=missle[num].UDposzSIZE[i]+0.001f;
					
					
					missle[num].UDposx[i]=missle[num].UDposx[i]+missle[num].UDposxMove[i];
					missle[num].UDposy[i]=missle[num].UDposy[i]+missle[num].UDposyMove[i];
					missle[num].UDposz[i]=missle[num].UDposz[i]+missle[num].UDposzMove[i];
					
				}


				for(int i=0;i<MAXMISSLESMOKE;i++)
				{
					//int tmp=i+missle[num].UDposflag;
					int tmp=i;
					if(tmp==100)
						tmp=0;




					if((Smokes[i].winz<1.0)&&(Smokes[i].winz>0.0))//可视范围内
					if((Smokes[i].winx>(-0.1*winwidth))&&(Smokes[i].winy>(-0.1*winheight))&&(Smokes[i].winx<(winwidth*1.1))&&(Smokes[i].winy<(winheight*1.1)))//窗口内
					{
						Vector3d tmp3d;
						tmp3d=MView.Matrix() * Vector3d(Smokes[tmp].x,Smokes[tmp].y,Smokes[tmp].z) + MView.RefPos();
						int smokelife=i-missle[num].UDposflag;
						if(smokelife<0)
							smokelife=smokelife+MAXMISSLESMOKE;
						if(smokelife<(MAXMISSLESMOKE-1))
						{
							if(smokelife>(MAXMISSLESMOKE-10))
							{
								//if(missle[num].UDlife>0)
								//glPrintSmokeM((float)tmp3d(0),(float)tmp3d(1),(float)tmp3d(2),(smokelife-(MAXMISSLESMOKE-10))/9.0f);
								smokelife=MAXMISSLESMOKE-(smokelife-(MAXMISSLESMOKE-10))*(MAXMISSLESMOKE/10);

								
							}
							else
							{
								if(smokelife<(MAXMISSLESMOKE/2))
									smokelife=smokelife*2;
								else
									smokelife=MAXMISSLESMOKE;

								
								
							
							}
							float alpha1;
							if(missle[num].UDlife>0)
								alpha1=(float)smokelife/(float)MAXMISSLESMOKE;
							else
								alpha1=smokelife*((float)missle[num].smokeTime/100.0f)/(float)MAXMISSLESMOKE;
							//if(!GraphicsLOW)
							//	glPrintSmoke((float)tmp3d(0),(float)tmp3d(1),(float)tmp3d(2),alpha1,Smokes[i].smokeNum,Smokes[i].SmokeSize);
						}
						
						
					}
				}
			}
		}
	}
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

	glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);
	*/
}
void DrawMissle(void)
{
	/*
	for(int num=1;num<maxUnits;num++)
	{
		UDfighers[num].m_DrawMissle(MFighter.RefPos(),winwidth,winheight,tmpLookRenge);
		
		if(UDfighers[num].UDlife>0)
		for(int i=0;i<MAXUNITMISSLES;i++)
		{
			if(UDfighers[num].UNITMissles[i].UDlife>0)
			{
				UDfighers[num].UNITMissles[i].UDlife=UDfighers[num].UNITMissles[i].UDlife-1;
				UDfighers[num].UNITMissles[i].timer=UDfighers[num].UNITMissles[i].timer+1;

				float tmpX=(float)(MFighter.RefPos()(0)-UDfighers[num].UNITMissles[i].UDMplane.RefPos()(0));
				float tmpY=(float)(MFighter.RefPos()(1)-UDfighers[num].UNITMissles[i].UDMplane.RefPos()(1));
				float tmpZ=(float)(MFighter.RefPos()(2)-UDfighers[num].UNITMissles[i].UDMplane.RefPos()(2));
				UDfighers[num].UNITMissles[i].UDwinl=tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ;
				if(UDfighers[num].UNITMissles[i].UDwinl<tmpLookRenge*tmpLookRenge)
				{
					glPushMatrix();
						glMultMatrixd(UDfighers[num].UNITMissles[i].UDMplane.Matrix4());	
						GLint viewport[4];
						GLdouble mvmatrix[16],projmatrix[16];
						GLdouble SUFwinX,SUFwinY,SUFwinZ;
						glGetIntegerv(GL_VIEWPORT,viewport);
						glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
						glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
						gluProject(0.0,0.0,0.0,mvmatrix,projmatrix,viewport,&SUFwinX,&SUFwinY,&SUFwinZ);
						UDfighers[num].UNITMissles[i].UDwinx=(float)SUFwinX;
						UDfighers[num].UNITMissles[i].UDwiny=(float)SUFwinY;
						UDfighers[num].UNITMissles[i].UDwinz=(float)SUFwinZ;
						if(UDfighers[num].UNITMissles[i].UDwinz<1.0f)//目标在屏幕前方
						if(((UDfighers[num].UNITMissles[i].UDwinx>-winwidth*0.1f)&&(UDfighers[num].UNITMissles[i].UDwinx<winwidth*1.1f)&&(UDfighers[num].UNITMissles[i].UDwiny>-winheight*0.1f)&&(UDfighers[num].UNITMissles[i].UDwiny<winheight*1.1f)))
						{
								glDisable(GL_BLEND);
								glPushMatrix();

								//glScaled(10, 10, 10);
								glRotatef(180.0, 0.0, 1.0, 0.0);
								m_VBMD->ShowVBMD(4);
								//m_nj->ShowACMD(0,2,0,0,0,0,180,0,1.0,1.0,1.0);

								glPopMatrix();
								glEnable(GL_BLEND);
				
						}



					glPopMatrix();
				}

			}

		}
		
	}
*/

	PMissleList.DrawMissle(MFighter.RefPos(),winwidth,winheight,tmpLookRenge);
	/*
	for(int i=0;i<maxMissles;i++)
	{
		if(missle[i].UDlife>0)
		{
			missle[i].UDlife=missle[i].UDlife-1;
			missle[i].timer=missle[i].timer+1;
			if(missle[i].UDlife==0)
			{
				FMOD_System_PlaySound(sys, FMOD_CHANNEL_REUSE, missvoice[rand()%4], 0, &missvoicechannel);
				missle[i].smokeTime=100;
				UDfighers[missle[i].TGTnum].waringde=false;
			}
			float tmpX=(float)(MFighter.RefPos()(0)-missle[i].UDMplane.RefPos()(0));
			float tmpY=(float)(MFighter.RefPos()(1)-missle[i].UDMplane.RefPos()(1));
			float tmpZ=(float)(MFighter.RefPos()(2)-missle[i].UDMplane.RefPos()(2));
			missle[i].UDwinl=tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ;
			if(missle[i].UDwinl<tmpLookRenge*tmpLookRenge)
			{
				glPushMatrix();
					glMultMatrixd(missle[i].UDMplane.Matrix4());	
					GLint viewport[4];
					GLdouble mvmatrix[16],projmatrix[16];
					GLdouble SUFwinX,SUFwinY,SUFwinZ;
					glGetIntegerv(GL_VIEWPORT,viewport);
					glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
					glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
					gluProject(0.0,0.0,0.0,mvmatrix,projmatrix,viewport,&SUFwinX,&SUFwinY,&SUFwinZ);
					missle[i].UDwinx=(float)SUFwinX;
					missle[i].UDwiny=(float)SUFwinY;
					missle[i].UDwinz=(float)SUFwinZ;
					if(missle[i].UDwinz<1.0f)//目标在屏幕前方
					if(((missle[i].UDwinx>-winwidth*0.1f)&&(missle[i].UDwinx<winwidth*1.1f)&&(missle[i].UDwiny>-winheight*0.1f)&&(missle[i].UDwiny<winheight*1.1f)))
					{
							glDisable(GL_BLEND);
							glPushMatrix();

							//glScaled(10, 10, 10);
							glRotatef(180.0, 0.0, 1.0, 0.0);
							m_VBMD->ShowVBMD(4);
							//m_nj->ShowACMD(0,2,0,0,0,0,180,0,1.0,1.0,1.0);

							glPopMatrix();
							glEnable(GL_BLEND);
			
					}



				glPopMatrix();
			}
		}
	}
	*/
}
void DrawUnit(void)
{


	//glPushMatrix();
	//	glMultMatrixd(LightSun.UDMplane.Matrix4());
	//	m_VBMD->ShowVBMD(4);
	//glPopMatrix();

	glEnable(GL_CULL_FACE);
	locklists_index=0;
	for(int i=1;i<maxUnits;i++)
	{
		if(UDfighers[i].m_DrawSelf(MFighter.RefPos(),winwidth,winheight,tmpLookRenge)&&UDfighers[i].UDwinl<(tmpredarRenge*tmpredarRenge))
		{

			DrawFightersData(UDfighers[i].UDwinx,UDfighers[i].UDwiny,UDfighers[i].UDwinz,UDfighers[i].UDwinl,UDfighers[i].UDname,UDfighers[i].UDflag,UDfighers[i].UDlockselect,UDfighers[i].UDlife);
			if(!(UDfighers[i].UDflag==2))
			{
				locklists[locklists_index].TGTnum=i;
				locklists_index=locklists_index+1;
				if(locklists_index==maxUnits)
					locklists_index=0;
			}
		}
		/*
		if((UDfighers[i].UDlife>0)||(UDfighers[i].smokeTime>90))
		{
			glPushMatrix();
				//glScaled(0.01, 0.01, 0.01);
				glMultMatrixd(UDfighers[i].UDMplane.Matrix4());		
				
				if(UDfighers[i].UDwinl<(tmpLookRenge*tmpLookRenge))//目标距离
				{
					if(UDfighers[i].UDwinz<1.0f)
					{
						if(((UDfighers[i].UDwinx>-winwidth*0.1f)&&(UDfighers[i].UDwinx<winwidth*1.1f)&&(UDfighers[i].UDwiny>-winheight*0.1f)&&(UDfighers[i].UDwiny<winheight*1.1f))||(UDfighers[i].UDwinl<tmpLookRenge*tmpLookRenge))
						{
							glDisable(GL_BLEND);
							glPushMatrix();
							if(UDfighers[i].UDfighterType==1)
							{//glScaled(0.01, 0.01, 0.01);
								m_VBMD->ShowVBMD(2);
							}
							if(UDfighers[i].UDfighterType==2)
								m_nj->ShowACMD(0,7,0,0,0,0,180,0,1.0,1.0,1.0);
							glPopMatrix();
							glEnable(GL_BLEND);
						}
					}
					
					
				}

				ShowUNITSFlag(UDfighers[i].UDMplane.RefPos()(0),UDfighers[i].UDMplane.RefPos()(1),UDfighers[i].UDMplane.RefPos()(2),i);
			glPopMatrix();
			//DrawSmoke(i);
		}
		*/
	}
	glDisable(GL_CULL_FACE);
}

void DrawMisslesign(const Vector3d& MisslePosition)
{
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glLoadIdentity();
		MissleSign.UDMplane=MFighter;
		MissleSign.UDMplane.TranslateInternal(Vector3d(0.0f, 0.0f, -100.0f));
		MissleSign.UDPstate.MaxSpeed=0.0;
		MissleSign.UDPstate.MaxAngleSpeed=50.0;
		MissleSign.UDPstate.VelocityResistance=0.0;
		MissleSign.UDPstate.AngleVelocityResistance=0.1;
		MissleSign.TurnTo(MisslePosition);
		MissleSign.UDPstate.NextState();
		glLoadMatrixd(MView.Matrix4());
		glMultMatrixd(MissleSign.UDMplane.Matrix4());
		
		float TmpX=float(MFighter.RefPos()(0) - MisslePosition(0));
		float TmpY=float(MFighter.RefPos()(1) - MisslePosition(1));
		float TmpZ=float(MFighter.RefPos()(2) - MisslePosition(2));
		float TmpL=TmpX*TmpX+TmpY*TmpY+TmpZ*TmpZ;
		char missleLL[32]={0};
		sprintf(missleLL,"%d",(int)(sqrt(TmpL)*0.10f-10.0f));
		GLint viewport[4];
		GLdouble mvmatrix[16],projmatrix[16];
		GLdouble SUFwinX,SUFwinY,SUFwinZ;
		glGetIntegerv(GL_VIEWPORT,viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
		glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
		gluProject(0.0,0.0,35.0,mvmatrix,projmatrix,viewport,&SUFwinX,&SUFwinY,&SUFwinZ);
		

		glColor3f(1.0f,0.0f,0.0f);

		glBegin(GL_TRIANGLES);
			glVertex3f(1.0f, 0.0f, 30.0f);
			glVertex3f(0.0f, 0.0f, 35.0f);
			glVertex3f(-1.0f, 0.0f, 30.0f);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(0.0f, 1.0f, 30.0f);
			glVertex3f(0.0f, 0.0f, 35.0f);
			glVertex3f(0.0f, -1.0f, 30.0f);
		glEnd();
		
		
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glPrint((int)SUFwinX,(int)SUFwinY,missleLL,0,true);

	glColor3f(1.0f,1.0f,1.0f);

}
void Drawlocksign(void)
{
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	for(int i=0;i<8;i++)
	{
		if(lockUnits[i].locksTGT>-1)
		if(UDfighers[lockUnits[i].locksTGT].UDlockselect||lockUnits[i].lockON)
		{	
			//::MessageBox(HWND_DESKTOP,"123","123",MB_OK | MB_ICONEXCLAMATION);
			//testNum=lockUnits[i].locksTGT;
			glPushMatrix();
			LockSign[i].UDMplane=MFighter;
			LockSign[i].UDMplane.TranslateInternal(Vector3d(0.0f, 0.0f, -100.0f));
			LockSign[i].UDPstate.MaxSpeed=0.0;
			LockSign[i].UDPstate.MaxAngleSpeed=50.0;
			LockSign[i].UDPstate.VelocityResistance=0.0;
			LockSign[i].UDPstate.AngleVelocityResistance=0.1;
			LockSign[i].TurnTo(UDfighers[lockUnits[i].locksTGT].UDMplane.RefPos());
			LockSign[i].UDPstate.NextState();
			//glLoadIdentity();
			glMultMatrixd(LockSign[i].UDMplane.Matrix4());
			//glScaled(0.001, 0.001, 0.005);
			//glRotatef(180.0, 0.0, 1.0, 0.0);
			//m_VBMD->ShowVBMD(8);
			glColor3f(0.0f,1.0f,0.0f);
			glBegin(GL_TRIANGLES);
			   glVertex3f(1.0f, 0.0f, 30.0f);
			   glVertex3f(0.0f, 0.0f, 35.0f);
			   glVertex3f(-1.0f, 0.0f, 30.0f);
			glEnd();
			glBegin(GL_TRIANGLES);
			   glVertex3f(0.0f, 1.0f, 30.0f);
			   glVertex3f(0.0f, 0.0f, 35.0f);
			   glVertex3f(0.0f, -1.0f, 30.0f);
			glEnd();
			//testNum=LockSign[i].UDMplane.RefPos()(0);
			//testNum2=MFighter.RefPos()(0);

			glColor3f(1.0f,1.0f,1.0f);
			glPopMatrix();
		}
	}

	glEnable(GL_TEXTURE_2D);
	
}
bool UnitAIBefore(int i)
{
	if(GameMode==1)
	{
		
		//testNum=UDfighers[0].UDMplane.RefPos()(2)-UDfighers[i].UDMplane.RefPos()(2);
		if(UDfighers[i].UDMplane.RefPos()(1)>1000.0)
		{
			if(UDfighers[i].isAttacking)
			{

				if(UDfighers[i].isAttackReady)
				{
					if((UDfighers[0].UDMplane.RefPos()(2)-UDfighers[i].UDMplane.RefPos()(2))<7500.0)
					{
						//UDfighers[i].UDPstate.MaxSpeed=10.0;
						UDfighers[i].isAttacking=false;
						UDfighers[i].isAttackReady=false;
						PMissleList.AddMissle(UDfighers[i].UDMplane,0,i,UDfighers[i].mSpeed);
					}
					else
					{
						UDfighers[i].mSpeed=moveSpeed * 2500.0f;
						//UDfighers[i].UDPstate.MaxSpeed=3.0;
						UDfighers[i].TurnTo(Vector3d(UDfighers[0].UDMplane.RefPos()(0),max(UDfighers[0].UDMplane.RefPos()(1),1000.0),UDfighers[0].UDMplane.RefPos()(2)));
						UDfighers[i].UDPstate.NextState();
					}
				}
				else
				{
					if((UDfighers[0].UDMplane.RefPos()(2)-UDfighers[i].UDMplane.RefPos()(2))>10000.0)
					{
						UDfighers[i].isAttackReady=true;
						
					}
					else
					{
						UDfighers[i].mSpeed=moveSpeed * 4000.0f;
						UDfighers[i].TurnTo(Vector3d(UDfighers[i].UDMplane.RefPos()(0),max(UDfighers[0].UDMplane.RefPos()(1),1000.0),UDfighers[0].UDMplane.RefPos()(2)-11000.0));
						UDfighers[i].UDPstate.NextState();
					}
				}
			}
			else
			{
				if(UDfighers[i].UDMplane.RefPos()(2)>UDfighers[0].UDMplane.RefPos()(2))
				{
					//UDfighers[i].UDPstate.MaxSpeed=10.0;
					UDfighers[i].isAttacking=true;
				}
				else
				{
					UDfighers[i].TurnTo(Vector3d(UDfighers[i].UDMplane.RefPos()(0),max(UDfighers[0].UDMplane.RefPos()(1),1000.0),UDfighers[0].UDMplane.RefPos()(2)));
					UDfighers[i].UDPstate.NextState();
				}
			}
		}
		else
		{
			UDfighers[i].TurnTo(Vector3d(UDfighers[i].UDMplane.RefPos()(0),max(UDfighers[0].UDMplane.RefPos()(1),1500.0),UDfighers[0].UDMplane.RefPos()(2)));
			UDfighers[i].UDPstate.NextState();
		}
	
		return false;
	}
	if((UDfighers[i].attackTGTNum==0)&&(UDfighers[i].LockTimer>30)&&(UDfighers[i].AIact==2))
	{
		PlayerLocking=true;
	
	
	}
	if((UDfighers[i].UDMplane.RefPos()(1)>100000)||(UDfighers[i].UDMplane.RefPos()(1)<30000))
	{
		UDfighers[i].LockTimer=0;
		UDfighers[i].AIactTimer2=0;
		UDfighers[i].TurnTo(Vector3d(UDfighers[i].UDMplane.RefPos()(0),50000,UDfighers[i].UDMplane.RefPos()(2)));
		UDfighers[i].UDPstate.NextState();
		return false;
	}


	if(UDfighers[i].waringde)
	{
		UDfighers[i].LockTimer=0;
		if(UDfighers[i].attackedMissleNum>-1)
		{
			UDfighers[i].AIactTimer2=0;
			UDfighers[i].WaringTo(PMissleList.Missles[UDfighers[i].attackedMissleNum].UDMplane.RefPos());
			UDfighers[i].UDPstate.NextState();
			UDfighers[i].attackTGTNum=PMissleList.Missles[UDfighers[i].attackedMissleNum].onwer;
			return false;
		}		
	}


	float TmpX=float(UDfighers[i].UDMplane.RefPos()(0) - UDfighers[i].MoveToPos(0));
	float TmpY=float(UDfighers[i].UDMplane.RefPos()(1) - UDfighers[i].MoveToPos(1));
	float TmpZ=float(UDfighers[i].UDMplane.RefPos()(2) - UDfighers[i].MoveToPos(2));
	float TmpL=TmpX*TmpX+TmpY*TmpY+TmpZ*TmpZ;
	if((TmpL>tmpredarRenge*tmpredarRenge)||(TmpL<10000.0f))
	{
		UDfighers[i].LockTimer=0;
		UDfighers[i].AIact=1;
		return true;
	
	}
	

	if((UDfighers[i].attackTGTNum>=0)&&(UDfighers[i].attackTGTNum<maxUnits))
	if((GetLength_2f(UDfighers[i].UDMplane.RefPos(),UDfighers[UDfighers[i].attackTGTNum].UDMplane.RefPos())<500*500))
	{
		UDfighers[i].LockTimer=0;
		Transform tmp=UDfighers[i].UDMplane;
		tmp.TranslateInternal(Vector3d(0, 1000, -10));
		UDfighers[i].TurnTo(Vector3d(tmp.RefPos()(0),tmp.RefPos()(1),tmp.RefPos()(2)));
		UDfighers[i].UDPstate.NextState();
		return false;
	}

	if((UDfighers[i].AIactTimer2>900)&&(UDfighers[i].AIactTimer2<1200))
	{
		UDfighers[i].LockTimer=0;
		if(UDfighers[i].attackedMissleNum>-1)
			UDfighers[i].WaringTo(PMissleList.Missles[UDfighers[i].attackedMissleNum].UDMplane.RefPos());
		UDfighers[i].UDPstate.NextState();
		return false;
	}
			


	return true;
}
void UnitAI(int i)
{

	if(UDfighers[i].AIact==1)
	{
		UDfighers[i].LockTimer=0;
		UDfighers[i].AIactTimer2=0;
		UDfighers[i].TurnTo(UDfighers[i].MoveToPos);
		//UDfighers[i].UDMplane.RotateInternal(Vector3d(0.0, 1.0, 0.0) * 0.002*(4));
		UDfighers[i].UDPstate.NextState();
		UDfighers[i].AIactTimer1=UDfighers[i].AIactTimer1+1;

	}


	if((UDfighers[i].AIactTimer1>300)||(UDfighers[i].AIactTimer2>2000))
	{
		UDfighers[i].LockTimer=0;
		UDfighers[i].AIactTimer1=0;
		UDfighers[i].AIactTimer2=0;
		int j=rand()%maxUnits;//
		while(((UDfighers[i].UDflag==UDfighers[j].UDflag)||(UDfighers[j].UDlife<1))&&(j<maxUnits))
		{
			j=j+1;
		}
		if((j<maxUnits)&&(j>-1))
		{
			UDfighers[i].attackTGTNum=j;
			UDfighers[i].AIact=2;
		}
		else
		{
								//UDfighers[i].attackTGTNum=-1;
			UDfighers[i].AIact=1;
		}
					
					
	}


	if(UDfighers[i].AIact==2)
	{
		UDfighers[i].AIactTimer2=UDfighers[i].AIactTimer2+1;
		if((UDfighers[i].attackTGTNum>-1)&&(UDfighers[i].attackTGTNum<maxUnits))
		{
			UDfighers[i].AIactTimer1=0;

			if(UDfighers[UDfighers[i].attackTGTNum].UDlife>0)
			{

				UDfighers[i].TurnTo(UDfighers[UDfighers[i].attackTGTNum].UDMplane.RefPos());
				UDfighers[i].UDPstate.NextState();
				UDfighers[i].AttackTo(UDfighers[UDfighers[i].attackTGTNum].UDMplane.RefPos());
						

				if(UDfighers[i].inGunRange&&(lockflash%10==0))
				{
					Transform tmp2=UDfighers[i].UDMplane;
					tmp2.TranslateInternal(Vector3d(5.0f, -10.0f, -30.0f));
					Transform tmp=tmp2;
					tmp.TranslateInternal(Vector3d((float(rand()%10)-5.0f)/5.0f, (float(rand()%10)-5.0f)/5.0f, -200.0f-UDfighers[i].mSpeed));
					Shell.AddNewShell(float(tmp2.RefPos()(0)),float(tmp2.RefPos()(1)),float(tmp2.RefPos()(2)),float(tmp2.RefPos()(0) - tmp.RefPos()(0)),float(tmp2.RefPos()(1) - tmp.RefPos()(1)),float(tmp2.RefPos()(2) - tmp.RefPos()(2)),UDfighers[i].attackTGTNum,i);
				
				}
				
				if((UDfighers[i].LockTimer>UDfighers[i].LockOnTime)&&(UDfighers[i].fireTimer<1))
				{
					UDfighers[i].LockTimer=0;
					UDfighers[i].fireTimer=UDfighers[i].RefireTime;
					UDfighers[UDfighers[i].attackTGTNum].attackedMissleNum=PMissleList.AddMissle(UDfighers[i].UDMplane,UDfighers[i].attackTGTNum,i,UDfighers[i].mSpeed);

				}
					
					
			}
			else
			{
				UDfighers[i].LockTimer=0;
				UDfighers[i].AIact=1;
				UDfighers[i].attackTGTNum=-1;
			}
		}
	}

}
void UnitMove(void)
{
   
/*
    for(int i=1;i<4;i++)
	{
       // UDfighers[i].UDPstate.Acceleration = UDfighers[i].UDMplane.Matrix() * Vector3d(0, 0, 1) * 0.2;
		//UDfighers[i].UDPstate.NextState();
		if(UDfighers[i].UDlife>0)
		{
			UDfighers[i].TurnTo(UDfighers[0].UDMplane.RefPos());
		//UDfighers[i].UDPstate.NextState();
		//UDfighers[i].UDMplane.TranslateInternal(Vector3d(0.0,0.0,5.0*3));
		}
	}
*/
	for(int i=0;i<MAXSMOKESLIST;i++)
	{
		if(PSmokes.SmokesList[i].life>0.0f)//存在
		{
			PSmokes.SmokesList[i].pos[0]=PSmokes.SmokesList[i].pos[0]+PSmokes.SmokesList[i].posMove[0];
			PSmokes.SmokesList[i].pos[1]=PSmokes.SmokesList[i].pos[1]+PSmokes.SmokesList[i].posMove[1];
			PSmokes.SmokesList[i].pos[2]=PSmokes.SmokesList[i].pos[2]+PSmokes.SmokesList[i].posMove[2];
			PSmokes.SmokesList[i].size=PSmokes.SmokesList[i].size+PSmokes.SmokesList[i].sizeMove;
			if(PSmokes.SmokesList[i].type!=2)
				PSmokes.SmokesList[i].life=PSmokes.SmokesList[i].life-1.0f;
		}
	}

    PlayerLocking=false;
	for(int i=1;i<maxUnits;i++)
	{
		if(UDfighers[i].smokeTime>0)
		UDfighers[i].smokeTime=UDfighers[i].smokeTime-1;

		if(UDfighers[i].UDlife>0)
		{
			if((i%4)==(playTime%4))
				UDfighers[i].addTrack();
			UDfighers[i].MoveSpeed();
			if(UDfighers[i].fireTimer>0)
				UDfighers[i].fireTimer--;

			if(UnitAIBefore(i))
				UnitAI(i);


			if(UDfighers[i].UDflag==2)
				UDfighers[i].MoveToPos=UDfighers[0].UDMplane.RefPos();
			UDfighers[i].UDMplane.TranslateInternal(Vector3d(0.0,0.0,UDfighers[i].mSpeed));
		}
		
		
	}
	float tmpL;
	float tmpX;
	float tmpY;
	float tmpZ;
	float shellHitRange=1000.0f;
	for(int i=0;i<MAXSHELLSLIST;i++)
	{
		if(Shell.ShellList[i].life>0)
		{
			Shell.ShellList[i].life=Shell.ShellList[i].life-1;

			Shell.ShellList[i].FrontPos[0]=Shell.ShellList[i].FrontPos[0]+Shell.ShellList[i].posMove[0];
			Shell.ShellList[i].FrontPos[1]=Shell.ShellList[i].FrontPos[1]+Shell.ShellList[i].posMove[1];
			Shell.ShellList[i].FrontPos[2]=Shell.ShellList[i].FrontPos[2]+Shell.ShellList[i].posMove[2];
			Shell.ShellList[i].BackPos[0]=Shell.ShellList[i].BackPos[0]+Shell.ShellList[i].posMove[0];
			Shell.ShellList[i].BackPos[1]=Shell.ShellList[i].BackPos[1]+Shell.ShellList[i].posMove[1];
			Shell.ShellList[i].BackPos[2]=Shell.ShellList[i].BackPos[2]+Shell.ShellList[i].posMove[2];
			if(Shell.ShellList[i].onwer!=Shell.ShellList[i].TGTNum)
			if((Shell.ShellList[i].TGTNum>=0)&&(Shell.ShellList[i].TGTNum<MAXSHELLSLIST))
			if(UDfighers[Shell.ShellList[i].TGTNum].UDlife>0)
			{
				tmpX=Shell.ShellList[i].FrontPos[0]-float(UDfighers[Shell.ShellList[i].TGTNum].UDMplane.RefPos()(0));
				tmpY=Shell.ShellList[i].FrontPos[1]-float(UDfighers[Shell.ShellList[i].TGTNum].UDMplane.RefPos()(1));
				tmpZ=Shell.ShellList[i].FrontPos[2]-float(UDfighers[Shell.ShellList[i].TGTNum].UDMplane.RefPos()(2));
				tmpL=tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ;
				if(Shell.ShellList[i].onwer==0)
					shellHitRange=10000.0f;
				if(tmpL<shellHitRange)
				{
					if(Shell.ShellList[i].onwer==0)
						UDfighers[Shell.ShellList[i].TGTNum].UDlife=UDfighers[Shell.ShellList[i].TGTNum].UDlife-5;
					else
						UDfighers[Shell.ShellList[i].TGTNum].UDlife=UDfighers[Shell.ShellList[i].TGTNum].UDlife-1;

					if(UDfighers[Shell.ShellList[i].TGTNum].UDlife==UDfighers[Shell.ShellList[i].TGTNum].UDlife<1)
					{
						UDfighers[Shell.ShellList[i].TGTNum].smokeTime=100;
						Playkillvoice(rand()%10);
	//					FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, killvoice[rand()%7], 0, &killvoicechannel);			
					}
					if(Shell.ShellList[i].TGTNum==0)
					{
						hited=5;
						AddSound(3,UDfighers[0].UDMplane.RefPos());
				//		FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, soundGunHited, 0, &channelGunHited);
					}

					Shell.ShellList[i].life=0;

				}
			}
		}
	}

	PlayerLocked=false;
/*
	for(int num=1;num<maxUnits;num++)
	{
		for(int i=0;i<MAXUNITMISSLES;i++)
		{
			if(UDfighers[num].UNITMissles[i].UDlife>0)
			{
				int MISSLETGTnum=UDfighers[num].UNITMissles[i].TGTnum;
				if(UDfighers[MISSLETGTnum].UDlife>0)
				{
					float tmpX=(float)(UDfighers[MISSLETGTnum].UDMplane.RefPos()(0) - UDfighers[num].UNITMissles[i].UDMplane.RefPos()(0));
					float tmpY=(float)(UDfighers[MISSLETGTnum].UDMplane.RefPos()(1) - UDfighers[num].UNITMissles[i].UDMplane.RefPos()(1));
					float tmpZ=(float)(UDfighers[MISSLETGTnum].UDMplane.RefPos()(2) - UDfighers[num].UNITMissles[i].UDMplane.RefPos()(2));
					float tmpD=tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ;
					if((tmpD<8000000)&&(!UDfighers[MISSLETGTnum].waringde))
					{
						UDfighers[MISSLETGTnum].waringde=true;
					}
					UDfighers[num].UNITMissles[i].TurnTo(UDfighers[MISSLETGTnum].UDMplane.RefPos());
					if(UDfighers[num].UNITMissles[i].timer>15)
						UDfighers[num].UNITMissles[i].UDPstate.NextState();
					UDfighers[num].UNITMissles[i].UDMplane.TranslateInternal(Vector3d(0.0,0.0,5.0*10));
					if(tmpD<10000)
					{
						FMOD_System_PlaySound(sys, FMOD_CHANNEL_REUSE, sound1, 0, &channel1);
						UDfighers[MISSLETGTnum].UDlife=UDfighers[MISSLETGTnum].UDlife-55;
						if(UDfighers[MISSLETGTnum].UDlife<0)
						{
							UDfighers[MISSLETGTnum].smokeTime=100;
						}
						UDfighers[num].UNITMissles[i].UDlife=-1;
						UDfighers[num].UNITMissles[i].smokeTime=100;
						Boms[Bom_index].Frame=0;
						UDfighers[MISSLETGTnum].waringde=false;
						Bomings[Bomings_index].NewBom((float)UDfighers[num].UNITMissles[i].UDMplane.RefPos()(0),(float)UDfighers[num].UNITMissles[i].UDMplane.RefPos()(1),(float)UDfighers[num].UNITMissles[i].UDMplane.RefPos()(2),&PlaneBom[0]);
						Bomings_index=Bomings_index+1;
						if(Bomings_index==MAXBom)
							Bomings_index=0;
					}
				}
				else
					UDfighers[num].UNITMissles[i].UDMplane.TranslateInternal(Vector3d(0.0,0.0,5.0*8));
			}

		}
	}
*/
	for(int i=0;i<MAXMISSLE;i++)
	{
		if(PMissleList.Missles[i].UDlife>0)
		{
			
			if(PMissleList.Missles[i].TGTnum==0)
			{
				PlayerLocked=true;
				DrawMisslesign(PMissleList.Missles[i].UDMplane.RefPos());
			}

			PMissleList.Missles[i].UDlife=PMissleList.Missles[i].UDlife-1;
			PMissleList.Missles[i].timer=PMissleList.Missles[i].timer+1;
			if(PMissleList.Missles[i].UDlife<1)
			{
				if(PMissleList.Missles[i].onwer==0)
					Playmissvoice(rand()%4);
//				FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, missvoice[rand()%4], 0, &missvoicechannel);
				PMissleList.Missles[i].smokeTime=100;
				UDfighers[PMissleList.Missles[i].TGTnum].waringde=false;
			}
			float MisslePos[3];
			MisslePos[0]=(float)PMissleList.Missles[i].UDMplane.RefPos()(0);
			MisslePos[1]=(float)PMissleList.Missles[i].UDMplane.RefPos()(1);
			MisslePos[2]=(float)PMissleList.Missles[i].UDMplane.RefPos()(2);


			PSmokes.AddSmoke(MisslePos[0],MisslePos[1],MisslePos[2],(float)(rand()%40+80)/100.0f);
			if(!GraphicsLOW)
			PSmokes.AddSmoke(MisslePos[0],MisslePos[1],MisslePos[2],0.4f,0.1f,15.0f,1);
			
			if((UDfighers[PMissleList.Missles[i].TGTnum].UDlife>=1)&&(PMissleList.Missles[i].UDlife>0))
			{
				float tmpX=(float)(UDfighers[PMissleList.Missles[i].TGTnum].UDMplane.RefPos()(0)-PMissleList.Missles[i].UDMplane.RefPos()(0));
				float tmpY=(float)(UDfighers[PMissleList.Missles[i].TGTnum].UDMplane.RefPos()(1)-PMissleList.Missles[i].UDMplane.RefPos()(1));
				float tmpZ=(float)(UDfighers[PMissleList.Missles[i].TGTnum].UDMplane.RefPos()(2)-PMissleList.Missles[i].UDMplane.RefPos()(2));
				float tmpD=tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ;
				if((tmpD<8000000)&&(!UDfighers[PMissleList.Missles[i].TGTnum].waringde))
				{
					PlaymissleWarning(rand()%(MAX_missleWarning*3));
					//if(PMissleList.Missles[i].onwer==0)
//						FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, missleWarning[rand()%10], 0, &missleWarningchannel);
					UDfighers[PMissleList.Missles[i].TGTnum].waringde=true;
				}

				PMissleList.Missles[i].TurnTo(UDfighers[PMissleList.Missles[i].TGTnum].UDMplane.RefPos());
				PMissleList.Missles[i].Move();

				float BoomRange=10000.0f;
				if(PMissleList.Missles[i].onwer==0)
					BoomRange=20000.0f;
				if(tmpD<BoomRange)//临时爆炸范围
				{
					if(GetLength_2f(PMissleList.Missles[i].UDMplane.RefPos(),MFighter.RefPos())<tmpLookRenge*tmpLookRenge*2)
					AddSound(1,PMissleList.Missles[i].UDMplane.RefPos());
//					FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound1, 0, &channel1);
					if(PMissleList.Missles[i].onwer==0)
					{
						UDfighers[PMissleList.Missles[i].TGTnum].UDlife=UDfighers[PMissleList.Missles[i].TGTnum].UDlife-50-rand()%5;
					}
					else
					{
						UDfighers[PMissleList.Missles[i].TGTnum].UDlife=UDfighers[PMissleList.Missles[i].TGTnum].UDlife-5-rand()%2;
					}

					if(UDfighers[PMissleList.Missles[i].TGTnum].UDlife>0)
					{
					
						if(PMissleList.Missles[i].onwer==0)
							Playhitvoice(rand()%4);
						//FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, hitvoice[rand()%4], 0, &hitvoicechannel);
					}
					else
					{
						UDfighers[PMissleList.Missles[i].TGTnum].smokeTime=100;
						Playkillvoice(rand()%10);
//						FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, killvoice[rand()%7], 0, &killvoicechannel);
					}
					PMissleList.Missles[i].UDlife=-1;
					PMissleList.Missles[i].smokeTime=100;
					//Boms[Bom_index].Frame=0;
					
	
					if(PMissleList.Missles[i].TGTnum==0)
					hited=30;
					UDfighers[PMissleList.Missles[i].TGTnum].waringde=false;
	
					Bomings[Bomings_index].NewBom((float)PMissleList.Missles[i].UDMplane.RefPos()(0),(float)PMissleList.Missles[i].UDMplane.RefPos()(1),(float)PMissleList.Missles[i].UDMplane.RefPos()(2),&PlaneBom[0]);
					Bomings_index=Bomings_index+1;
					if(Bomings_index==MAXBom)
						Bomings_index=0;
/*
					//Boms[missle_index].pos=MView.Matrix() * missle[i].UDMplane.RefPos()+MView.RefPos();
					Boms[Bom_index].pos=missle[i].UDMplane.RefPos();
					Bom_index=Bom_index+1;
						if(Bom_index==MAXBom)
							Bom_index=0;
						*/
				}
			
			
			}
			else
			{
				PMissleList.Missles[i].UDMplane.TranslateInternal(Vector3d(0.0,0.0,70.0));
			}
		}
	
	}
/*
	for(int i=0;i<maxMissles;i++)
	{
		if(missle[i].UDlife>0)
		{
			float MisslePos[3];
			MisslePos[0]=(float)missle[i].UDMplane.RefPos()(0);
			MisslePos[1]=(float)missle[i].UDMplane.RefPos()(1);
			MisslePos[2]=(float)missle[i].UDMplane.RefPos()(2);

			PSmokes.AddSmoke(MisslePos,(float)(rand()%40+80)/100.0f);
			if(!GraphicsLOW)
			PSmokes.AddSmoke(MisslePos,0.4f,0.06f,15.0f,1);
			if(UDfighers[missle[i].TGTnum].UDlife>0)
			{
				float tmpX=(float)(UDfighers[missle[i].TGTnum].UDMplane.RefPos()(0)-missle[i].UDMplane.RefPos()(0));
				float tmpY=(float)(UDfighers[missle[i].TGTnum].UDMplane.RefPos()(1)-missle[i].UDMplane.RefPos()(1));
				float tmpZ=(float)(UDfighers[missle[i].TGTnum].UDMplane.RefPos()(2)-missle[i].UDMplane.RefPos()(2));
				float tmpD=tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ;
				if((tmpD<8000000)&&(!UDfighers[missle[i].TGTnum].waringde))
				{
						FMOD_System_PlaySound(sys, FMOD_CHANNEL_REUSE, missleWarning[rand()%10], 0, &missleWarningchannel);
						UDfighers[missle[i].TGTnum].waringde=true;
				}
				
				missle[i].TurnTo(UDfighers[missle[i].TGTnum].UDMplane.RefPos());
				if(missle[i].timer>15)
				missle[i].UDPstate.NextState();
				missle[i].UDMplane.TranslateInternal(Vector3d(0.0,0.0,5.0*10));
				if(tmpD<10000)//临时爆炸范围
				{
					FMOD_System_PlaySound(sys, FMOD_CHANNEL_REUSE, sound1, 0, &channel1);
					UDfighers[missle[i].TGTnum].UDlife=UDfighers[missle[i].TGTnum].UDlife-55;
					if(UDfighers[missle[i].TGTnum].UDlife>0)
					
						FMOD_System_PlaySound(sys, FMOD_CHANNEL_REUSE, hitvoice[rand()%4], 0, &hitvoicechannel);
					else
					{
						UDfighers[missle[i].TGTnum].smokeTime=100;
						FMOD_System_PlaySound(sys, FMOD_CHANNEL_REUSE, killvoice[rand()%7], 0, &killvoicechannel);
					}
					missle[i].UDlife=-1;
					missle[i].smokeTime=100;
					Boms[Bom_index].Frame=0;
					
	
					UDfighers[missle[i].TGTnum].waringde=false;
	
					Bomings[Bomings_index].NewBom((float)missle[i].UDMplane.RefPos()(0),(float)missle[i].UDMplane.RefPos()(1),(float)missle[i].UDMplane.RefPos()(2),&PlaneBom[0]);
					Bomings_index=Bomings_index+1;
					if(Bomings_index==MAXBom)
						Bomings_index=0;

				}
			}
			else
			{
				missle[i].UDMplane.TranslateInternal(Vector3d(0.0,0.0,5.0*8));
				//missle[i].UDlife=-1;
			}
		}
	}
*/
}


float GetSunHDlight(float x,float y,float z,int winwidth,int winheight)
{
	if(!isDraw)
		return 1.0f;

	glPushMatrix();	
	glLoadIdentity();
	GLint viewport[4];
	GLdouble mvmatrix[16],projmatrix[16];
	GLdouble SUFwinX,SUFwinY,SUFwinZ;
	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
	gluProject(x,y,z,mvmatrix,projmatrix,viewport,&SUFwinX,&SUFwinY,&SUFwinZ);
	glPopMatrix();	

	if(SUFwinZ>1.0001)
		return 1.0f;
	SUFwinX=SUFwinX-winwidth/2;
	SUFwinY=SUFwinY-winheight/2;
	float SunWinPos_2=float(SUFwinX*SUFwinX+SUFwinY*SUFwinY);
	float winheight_2=float(winheight*winheight);

	return min(1.0f,(SunWinPos_2/winheight_2)*0.5f+0.5f);

}
void DrawPlayer(void)
{
	//glGetFloatv(GL_MODELVIEW_MATRIX,Worldmatrix);
	for(int i=0;i<16;i++)
	Worldmatrix[i]=UDfighers[0].UDMplane.Matrix4()[i];
	glEnable(GL_CULL_FACE);
	//glPushMatrix();
    //glLoadIdentity();
	

    //paraLightDirection = MView * d
    //d = {200.0f, 0.0f, 0.0f}

	Vector3d tmp3d;
	tmp3d=MView.Matrix() * Vector3d(0.0,100000.0,0.0) + MView.RefPos();
	lightPosition[0]=(float)tmp3d(0);
	lightPosition[1]=(float)tmp3d(1);
	lightPosition[2]=(float)tmp3d(2);
	glLightfv(GL_LIGHT1,GL_POSITION,lightPosition);

		
	//BasicLight();
	//cgGLDisableProfile( g_CGprofile_vertex );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	
	//HighLight();
/*
	glPushMatrix();
    //glLoadIdentity();
		glBindTexture(GL_TEXTURE_2D, RedarTexture);	
		glTranslatef(0.0, 0.0, -10*testNum);
		glScaled(0.002, 0.002, 0.002);
		
		m_VBMD->ShowVBMD(6,false);
	glPopMatrix();
*/
	if(ShaderLight)
	{
		glPushMatrix();										
		//	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		//	glPushMatrix();	
		//		glLoadIdentity();									// Reset The Modelview Matrix
		//		gluPerspective (45.0f, (GLfloat)(winwidth)/(GLfloat)(winheight),			// Calculate The Aspect Ratio Of The Window
		//					10.0f,265.0f);	
		//		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		//		glPushMatrix();										// Store The Modelview Matrix
					glLoadIdentity();	

					glLoadMatrixd(MView.Matrix4());
	//				Transform ViewPlayer;
	//				ViewPlayer=UDfighers[0].UDMplane;
	//				ViewPlayer.RotateInternal(Vector3d(CRad(270.0f), 0.0f, 0.0f));
					glMultMatrixd(UDfighers[0].UDMplane.Matrix4());
					//glRotatef(270.0, 1.0, 0.0, 0.0);

					
					if(hited>0)
						glTranslated(float(rand()%4-2)*0.5,float(rand()%4-2)*0.5,0);
					//glTranslatef(0, -Ppos1, -Ppos2);
					glRotatef(-InertiaX*0.5f, 1.0, 0.0, 0.0);
					//glRotatef(180.0, 0.0, 0.0, 1.0);
					//glRotatef(-InertiaZ*0.3f, 0.0, 0.0, 1.0);
					glRotatef(-InertiaZ*0.75f, 0.0, 0.0, 1.0);
					//glScaled(0.02, 0.02, 0.02);
					//m_nj->ShowACMD(0,1,0,0,0,0,180,0,1.0,1.0,1.0);
					//glRotatef(40.0f*testNum2+40.0f,0.0f,1.0f,0.0f);
					//glRotatef(90.0f,1.0f,0.0f,0.0f);	
					//glScaled(1.0, 1.0, 1.0);
					//shaderT(m_VBMD->GetNormalTexID(PlayerMainModel),m_VBMD->GetSpecularTexID(PlayerMainModel));
					
					//m_VBMD->ShowVBMD(PlayerMainModel);
					
					if(ShadowLevel>1)
					{
						glBindTexture(GL_TEXTURE_2D, dtex);
						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
					}
					if(ShadowLevel>1)
						shaderT(m_VBMD->GetTextureID(PlayerMainModel) ,m_VBMD->GetNormalTexID(PlayerMainModel),m_VBMD->GetSpecularTexID(PlayerMainModel),dtex,GetSunHDlight((float)SunPos3d(0),(float)SunPos3d(1),(float)SunPos3d(2),winwidth,winheight));
					else
						shaderT(m_VBMD->GetTextureID(PlayerMainModel) ,m_VBMD->GetNormalTexID(PlayerMainModel),m_VBMD->GetSpecularTexID(PlayerMainModel),img,GetSunHDlight((float)SunPos3d(0),(float)SunPos3d(1),(float)SunPos3d(2),winwidth,winheight));
					
					m_VBMD->ShowVBMD(PlayerMainModel);
/*					glPushMatrix();
						glMultMatrixd(MavePart_BackL.Matrix4());
						m_VBMD->ShowVBMD(ModelID_MavePart_BackL,false);
					glPopMatrix();
					glPushMatrix();
						glMultMatrixd(MavePart_BackR.Matrix4());
						m_VBMD->ShowVBMD(ModelID_MavePart_BackR,false);
					glPopMatrix();
					glPushMatrix();
						glMultMatrixd(MavePart_FL.Matrix4());
						m_VBMD->ShowVBMD(ModelID_MavePart_FL,false);
					glPopMatrix();
					glPushMatrix();
						glMultMatrixd(MavePart_FR.Matrix4());
						m_VBMD->ShowVBMD(ModelID_MavePart_FR,false);
					glPopMatrix();
					glPushMatrix();
						glMultMatrixd(MavePart_WL.Matrix4());
						m_VBMD->ShowVBMD(ModelID_MavePart_WL,false);
					glPopMatrix();
					glPushMatrix();
						glMultMatrixd(MavePart_WR.Matrix4());
						m_VBMD->ShowVBMD(ModelID_MavePart_WR,false);
					glPopMatrix();
*/

					glCullFace(GL_FRONT);
					md5_weiyiL.render();
					md5_weiyiR.render();
					md5_wingL.render();
					md5_wingR.render();
					md5_yayiL.render();
					md5_yayiR.render();
					md5_yinqingL.render();
					md5_yinqingR.render();
					md5_chuiweiL.render();
					md5_chuiweiR.render();
					md5_jinyiL.render();
					md5_jinyiR.render();
					md5_MissleBox.render();
					glGetDoublev(GL_MODELVIEW_MATRIX,DrawPlayermatrix);
					glDisable(GL_CULL_FACE);
					glEnable(GL_BLEND);
					glDepthMask(GL_FALSE);
					glColor4f(1.0f,1.0f,1.0f,0.0f);
					m_VBMD->ShowVBMD(ModelID_MavePart_Glass,false);
					glColor4f(1.0f,1.0f,1.0f,1.0f);
					glDepthMask(GL_TRUE);
					glCullFace(GL_BACK);

					CGDisableProfilePixel();
					CGDisableProfileVertex();
					CGDisableTextureParameterShadowMap();
					CGDisableTextureParameterAmbientReflective();
					CGDisableTextureParameterNormalMap();
					CGDisableTextureParameterSpecularMap();
					if(ShadowLevel>1)
					{
						glBindTexture(GL_TEXTURE_2D, dtex);
						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LUMINANCE);
					}

		//		glPopMatrix();
		//	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		//	glPopMatrix();										// Restore The Old Projection Matrix
		//glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPopMatrix();										

	}
	else
	{
		glPushMatrix();	
		glLoadIdentity();	
		glLoadMatrixd(MView.Matrix4());
		glMultMatrixd(UDfighers[0].UDMplane.Matrix4());
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);
		if(hited>0)
			glTranslated(float(rand()%4-2)*0.5,float(rand()%4-2)*0.5,0);
		//glTranslatef(0, -Ppos1, -Ppos2);
		glRotatef(-InertiaX*0.5f, 1.0, 0.0, 0.0);
		glRotatef(-InertiaZ*0.75f, 0.0, 0.0, 1.0);
		m_VBMD->ShowVBMD(ModelID_MavePart_Normal);

		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHTING);
		glPopMatrix();	
	}



   // glPopMatrix();

	glDisable(GL_CULL_FACE);

/*
	glEnable(GL_BLEND);
		glPushMatrix();										
			glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
			glPushMatrix();	
				glLoadIdentity();									// Reset The Modelview Matrix
				gluPerspective (45.0f, (GLfloat)(winwidth)/(GLfloat)(winheight),			// Calculate The Aspect Ratio Of The Window
							10.0f,265.0f);	
				glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
				glPushMatrix();										// Store The Modelview Matrix
					glLoadIdentity();	
					
					glTranslatef(0, -Ppos1, -Ppos2);
					glRotatef(-InertiaX*0.5f, 1.0, 0.0, 0.0);

					glRotatef(-InertiaZ*0.3f, 0.0, 0.0, 1.0);
				glDepthMask(GL_FALSE);
				glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_COLOR   );
				glColor4f(testNum2,testNum2,testNum2,1.0f);
					m_VBMD->ShowVBMD(ModelID[2].MainDD1);
					m_VBMD->ShowVBMD(ModelID[2].MainDD2);
				glColor4f(1.0f,1.0f,1.0f,1.0f);
				glDepthMask(GL_TRUE);
				glPopMatrix();
			glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
			glPopMatrix();										// Restore The Old Projection Matrix
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPopMatrix();
	glDisable(GL_BLEND);
*/
}
void DrawPlayerTranslucent(void)
{
	glEnable(GL_BLEND);
	if(ShaderLight)
	{
		glPushMatrix();	
			glLoadIdentity();
			glLoadMatrixd(DrawPlayermatrix);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);
			glDepthMask(GL_FALSE);
			glDisable(GL_TEXTURE_2D);
			BackFire();
			md5_weiyanL.render();
			md5_weiyanR.render();
			CGDisableProfilePixel();
			CGDisableProfileVertex();
			glEnable(GL_TEXTURE_2D);
			glDepthMask(GL_TRUE);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glPopMatrix();	
	}
}
void DrawSky(Transform viewSky,float ne=0.0)
{
	glDisable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_COLOR   );
	//glBindTexture(GL_TEXTURE_2D,SkyTexture);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_COLOR   );
	glPushMatrix();
	//Msky.Rotate(Vector3d(0.0f, 1.0f, 0.0f) * CRad(ne));
	double fogbackY;
	//double skybackY;
	if(viewSky.RefPos()(1)>20000.0)
		fogbackY=viewSky.RefPos()(1);
	else
	{
		fogbackY=20000.0;
		//skybackY=(10000.0-MFighter.RefPos()(1))/10.0;
	}
	Msky.Translate( Vector3d( viewSky.RefPos()(0) ,viewSky.RefPos()(1), viewSky.RefPos()(2) ) );
	glMultMatrixd(Msky.Matrix4());	

//glBindTexture(GL_TEXTURE_2D, PlayerSign);
	
	
	glScaled(5000.0,5000.0,5000.0);
	glDisable(GL_DEPTH_TEST);
	if(!IsSkip)
		SkyBox.Draw();
	//m_VBMD->ShowVBMD(3);
	/*
	glBindTexture(GL_TEXTURE_2D, SkyTex[2].texID);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		// 前面
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// 纹理和四边形的左上
	glEnd();
		// 后面
		glBindTexture(GL_TEXTURE_2D, SkyTex[0].texID);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// 纹理和四边形的左上
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// 纹理和四边形的左下
	glEnd();
		// 顶面
		glBindTexture(GL_TEXTURE_2D, SkyTex[5].texID);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// 纹理和四边形的左上
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// 纹理和四边形的右上
	glEnd();
		// 底面
		glBindTexture(GL_TEXTURE_2D, SkyTex[1].texID);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// 纹理和四边形的左上
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// 纹理和四边形的右下
	glEnd();
		// 右面
		glBindTexture(GL_TEXTURE_2D, SkyTex[4].texID);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// 纹理和四边形的左上
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// 纹理和四边形的左下
	glEnd();
		// 左面
		glBindTexture(GL_TEXTURE_2D, SkyTex[3].texID);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// 纹理和四边形的左上
	glEnd();
	*/
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	
	//Msky.Translate(MFighter.RefPos()*(-1.0));
	Msky.Translate( Vector3d( -viewSky.RefPos()(0) ,  -viewSky.RefPos()(1) , -viewSky.RefPos()(2) ) );
	//Msky.Rotate(Vector3d(0.0f, 1.0f, 0.0f) * CRad(-ne));
	glEnable(GL_BLEND);
}
void DrawUnitTrack(void)
{
	if(!VBOSupported)
		return;
	//if(!TrackTexID)
	//	return;
	//glBindTexture(GL_TEXTURE_2D, TrackTexID);	
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	glEnableClientState( GL_VERTEX_ARRAY );	
	glEnableClientState( GL_COLOR_ARRAY );
	//glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	for(int i=1;i<maxUnits;i++)
		UDfighers[i].DrawTrack();
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
	//glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDepthMask(GL_TRUE);
	glEnable(GL_TEXTURE_2D);
}
void showloading(void)
{
	glEnable(GL_BLEND);
	needloadfile=needloadfile+1;

	glClear (GL_COLOR_BUFFER_BIT );
	switch (needloadfile)
	{
	case 1:glPrint(16,16,"2/7 Loading Texture",0);LoadGLTextures(IsSupportFBO);break;
	case 2:glPrint(16,16,"3/7 Loading Bom",0);PlaneBom[0].m_IsSupportFBO=IsSupportFBO;PlaneBom[0].InitBomType(0);break;
	case 3:glPrint(16,16,"4/7 Loading Sky",0);SkyBox.IsSupportFBO=IsSupportFBO;SkyBox.Init();AmbientReflectiveTexture=SkyBox.SunCubeID;break;//Cloud.Init();
	case 4:glPrint(16,16,"5/7 Loading Smoke",0);PSmokes.Init(1,GetPrivateProfileInt("Effect","Cloud",1,".\\set.ini"));break;
	case 5:glPrint(16,16,"6/7 Loading Sound",0);initsound();break;
	case 6:glPrint(16,16,"7/7 Loading Model",0);LoadVBMDModels(IsSupportFBO);break;
	case 7:loadover=true;
	/*MavePart_BackL.TranslateInternal(Vector3d(0.0,-4.0,37.0));
	MavePart_BackR.TranslateInternal(Vector3d(0.0,-4.0,37.0));
	MavePart_FL.TranslateInternal(Vector3d(-8.5,3.5,-20.0));
	MavePart_FR.TranslateInternal(Vector3d( 8.5,3.5,-20.0));
	MavePart_WL.TranslateInternal(Vector3d(0.0,0.0,55.0));
	MavePart_WR.TranslateInternal(Vector3d(0.0,0.0,55.0));
*/
	if(!MyFont.LoadFont("Data/FontCH"))
		::MessageBox(HWND_DESKTOP,"Font error","Error",MB_OK | MB_ICONEXCLAMATION);
	break;
	
	}
	MyFont.inputTxt(C_TITLE);

	//MyFont.inputTxt("测试单纹理字库。测试单纹理字库。测试单纹理字库。测试单纹理字库。测试单纹理字库。测试单纹理字库。");
	/*
	
	if(needloadfile==1)
	{

		LoadGLTextures();
		
//		glPrint(16,16,"Loading Bom",0);
		PlaneBom[0].m_IsSupportFBO=IsSupportFBO;
		if(!PlaneBom[0].InitBomType(0))
		::MessageBox(HWND_DESKTOP,"InitBom Error","Error",MB_OK | MB_ICONEXCLAMATION);
//		glPrint(16,16,"Loading Sky",0);
		SkyBox.IsSupportFBO=IsSupportFBO;
		SkyBox.Init();
		Cloud.Init();
//		glPrint(16,16,"Loading Smoke",0);
		PSmokes.Init(1);
//		glPrint(16,16,"Loading Sound",0);
		initsound();

	//	glPrint(16,16,"Loading Model",0);
		LoadVBMDModels(IsSupportFBO);
		needloadfile=2;
		
	
	}
		
	if(needloadfile<2)
	{
		//char loadingFileName[128];
		//sprintf(loadingFileName,"Now Loading");
		glEnable(GL_BLEND);
		glPrint(16,16,"Now Loading",0);
		needloadfile=1;
	}
*/


}
void DrawShadowMap(void)
{
	if(ShadowLevel==0)
	{
		return;
	}
	if(IsSupportFBO)
	{
		//glBindTexture(GL_TEXTURE_2D, dtex);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LUMINANCE);
		//glClearColor (1.0f, 1.0f, 1.0f, 1.0f);	

		glDisable(GL_TEXTURE_2D);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
		glPushAttrib(GL_VIEWPORT_BIT);
		glViewport(0,0,1024, 1024);
		glClear (GL_DEPTH_BUFFER_BIT);
				glPushMatrix();										
					glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
					glPushMatrix();	
						glLoadIdentity();									// Reset The Modelview Matrix
						gluPerspective (60.0f, (GLfloat)(winwidth)/(GLfloat)(winheight),60.0f,315.0f);	
						//glOrtho(-90.0,90.0,-90.0,90.0,10.0,500.0);		
						glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
						glPushMatrix();										// Store The Modelview Matrix
																// Reset The Modelview Matrix
							//glRotatef(-135.0f,0.0f,1.0f,0.0f);
							//glTranslatef(-100.0f,-10,100.0f);
							
							LightSun.UDMplane=UDfighers[0].UDMplane;
							LightSun.UDPstate.MaxSpeed=0.0;
							LightSun.UDPstate.MaxAngleSpeed=50.0;
							LightSun.UDPstate.VelocityResistance=0.0;
							LightSun.UDPstate.AngleVelocityResistance=0.1;
							LightSun.TurnTo(Vector3d(LightSunPos[0],LightSunPos[1],LightSunPos[2]));
							LightSun.UDPstate.NextState();
							LightSun.UDMplane.TranslateInternal(Vector3d(0.0f, 0.0f, -187.5f));
							LightSun.TurnTo(UDfighers[0].UDMplane.RefPos());
							LightSun.UDPstate.NextState();
							Transform LMView;
							LMView = (MWorld * UDfighers[0].UDMplane).Invert();
							glLoadIdentity();
							glLoadMatrixd(LMView.Matrix4());
							glMultMatrixd(LightSun.UDMplane.Matrix4());
							glRotated(180.0,0.0,0.0,1.0);
		
							//glTranslatef(0.0f,-10.0f*testNum,-100.0f);
							//glTranslatef(0.0f,0.0f,-137.5f);
							//double tmp=paraLightDirection[0]*paraLightDirection[0]+paraLightDirection[1]*paraLightDirection[1]+paraLightDirection[2]*paraLightDirection[2];
							//glRotated(90.0f,-paraLightDirection[1]/tmp,paraLightDirection[0]/tmp,paraLightDirection[2]/tmp);
							//glRotatef(90.0f,1.0f,0.0f,0.0f);
							//glRotatef(40.0f*2.05f+40.0f,0.0f,1.0f,0.0f);
							glDisable(GL_BLEND);
							GLfloat MVmatrix[16],Projmatrix[16];
							GLfloat Biasmatrix[16]={0.5f, 0.0f, 0.0f, 0.0f,
													0.0f, 0.5f, 0.0f, 0.0f,
													0.0f, 0.0f, 0.5f, 0.0f,
													0.5f, 0.5f, 0.5f, 1.0f};
							glGetFloatv(GL_MODELVIEW_MATRIX,MVmatrix);
							glGetFloatv(GL_PROJECTION_MATRIX,Projmatrix);
							if(ShadowLevel>1)
							{
								glPushMatrix();
									glLoadIdentity();	
									glLoadMatrixf(Biasmatrix);
									glMultMatrixf(Projmatrix);
									glMultMatrixf(MVmatrix);
									glGetFloatv(GL_MODELVIEW_MATRIX,ShadowMapMVPmatrix);
								glPopMatrix();
							}
							else
							{
								glPushMatrix();
									glLoadIdentity();	
									glLoadMatrixf(Projmatrix);
									glMultMatrixf(MVmatrix);
									glGetFloatv(GL_MODELVIEW_MATRIX,ShadowMapMVPmatrix);
								glPopMatrix();
								RenderShadowMap();
							}

							
							//m_VBMD->ShowVBMD(PlayerMainModel);
							m_VBMD->ShowVBMD(PlayerMainModel);
	/*						glPushMatrix();
							glMultMatrixd(MavePart_BackL.Matrix4());
								m_VBMD->ShowVBMD(ModelID_MavePart_BackL,false);
							glPopMatrix();
							glPushMatrix();
								glMultMatrixd(MavePart_BackR.Matrix4());
								m_VBMD->ShowVBMD(ModelID_MavePart_BackR,false);
							glPopMatrix();
							glPushMatrix();
								glMultMatrixd(MavePart_FL.Matrix4());
								m_VBMD->ShowVBMD(ModelID_MavePart_FL,false);
							glPopMatrix();
							glPushMatrix();
								glMultMatrixd(MavePart_FR.Matrix4());
								m_VBMD->ShowVBMD(ModelID_MavePart_FR,false);
							glPopMatrix();
							glPushMatrix();
								glMultMatrixd(MavePart_WL.Matrix4());
								m_VBMD->ShowVBMD(ModelID_MavePart_WL,false);
							glPopMatrix();
							glPushMatrix();
								glMultMatrixd(MavePart_WR.Matrix4());
								m_VBMD->ShowVBMD(ModelID_MavePart_WR,false);
							glPopMatrix();
				*/
							glDisable(GL_CULL_FACE);
							md5_weiyiL.render();
							md5_weiyiR.render();
							md5_wingL.render();
							md5_wingR.render();
							md5_yayiL.render();
							md5_yayiR.render();
							md5_yinqingL.render();
							md5_yinqingR.render();
							md5_chuiweiL.render();
							md5_chuiweiR.render();
							md5_jinyiL.render();
							md5_jinyiR.render();
							md5_MissleBox.render();
							if(!(ShadowLevel>1))
							{
								CGDisableProfilePixel();
								CGDisableProfileVertex();
							}
						glPopMatrix();
						glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
					glPopMatrix();										// Restore The Old Projection Matrix
					glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix

				glPopMatrix();										

		glEnable(GL_BLEND);
		/*
		if(ShaderBloom)
		{
			glDrawBuffer(GL_COLOR_ATTACHMENT1_EXT);
			glPushMatrix();	
				glClearColor (0.0f, 0.0f, 0.0f, 0.0f);	
				glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
				glLoadIdentity();	
				glLoadMatrixd(MView.Matrix4());
				glMultMatrixd(UDfighers[0].UDMplane.Matrix4());

				//glTranslatef(0, -Ppos1, -Ppos2);
				glRotatef(-InertiaX*0.5f, 1.0, 0.0, 0.0);
				glRotatef(-InertiaZ*0.3f, 0.0, 0.0, 1.0);
				//BasicLight();
				glBindTexture(GL_TEXTURE_2D, img);	
				HighLight();

				glEnable(GL_DEPTH_TEST);
				m_VBMD->ShowVBMD(PlayerMainModel,false);
				cgGLDisableProfile( g_CGprofile_vertex );
				cgGLDisableProfile( g_CGprofile_pixel );
				glDepthMask(GL_FALSE);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glColor4f((InertiaSpeed+50.0f)/100.0f,(InertiaSpeed+50.0f)/100.0f,(InertiaSpeed+50.0f)/100.0f,1.0f);
					m_VBMD->ShowVBMD(ModelID[2].MainDD1);
					m_VBMD->ShowVBMD(ModelID[2].MainDD2);
				glColor4f(1.0f,1.0f,1.0f,1.0f);
				glDepthMask(GL_TRUE);


				
			glPopMatrix();
		}
		*/
		glPopAttrib();
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		glEnable(GL_TEXTURE_2D);
		//glClearColor (glClearColorR, glClearColorG, glClearColorB, glClearColorA);	
	}
}
/*
void DrawHighLight(void)
{
	
	glDisable(GL_BLEND);
	glPushAttrib(GL_VIEWPORT_BIT);
		glViewport(0,0,bloomMAPSize, bloomMAPSize);
		glPushMatrix();	
			//glLoadIdentity();	
			//glTranslatef(0, -Ppos1, -Ppos2);
			//glRotatef(-InertiaX*0.5f, 1.0, 0.0, 0.0);
			//glRotatef(-InertiaZ*0.3f, 0.0, 0.0, 1.0);
			//BasicLight();
			//glBindTexture(GL_TEXTURE_2D, img);	
			HighLight();
			//m_VBMD->ShowVBMD(0,false);

			cgGLDisableProfile( g_CGprofile_vertex );
			cgGLDisableProfile( g_CGprofile_pixel );
		glPopMatrix();
		//glBindTexture(GL_TEXTURE_2D,blurtexture2);
		//glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, bloomMAPSize, bloomMAPSize, 0);
	glPopAttrib();
	glEnable(GL_BLEND);
	

}
*/
/*
void glPrintHighLight(void)
{



	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,winwidth,0,winheight,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	glEnable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, fboBloomImg);	

	glTranslated(winwidth/2.0,winheight/2.0,0.0);
	glScaled(winwidth/2.0,winheight/2.0,1.0);
	BasicLight();
	m_VBMD->ShowVBMD(ModelID_smoke,false);
	cgGLDisableProfile( g_CGprofile_pixel );
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glBindTexture(GL_TEXTURE_2D,0);
}
*/
void DrawGround(void)
{

	eyePositionSea[0]=(float)MFighter.RefPos()(0);
	eyePositionSea[1]=(float)MFighter.RefPos()(1);
	eyePositionSea[2]=(float)MFighter.RefPos()(2);

	glEnable(GL_FOG);
	glDisable(GL_BLEND);
	m_VBMD->ShowVBMD(ModelID_Stage1Ship_Normal);
	glDisable(GL_FOG);
	if(ShaderWater)
	{
		glBindTexture(GL_TEXTURE_2D,SeaTexID);
		DrawSea(oneframetimelimit);
		glPushMatrix();
			
			glScaled(1000.0,1000.0,1000.0);
			glDisable(GL_BLEND);
			//m_VBMD->ShowVBMD(ModelID_SHAN);
			int mapx,mapz;
			mapx=int(MFighter.RefPos()(0))/40000;
			mapz=int(MFighter.RefPos()(2))/40000;
			
			for(int i=-3;i<4;i++)
				for(int j=-3;j<4;j++)
				{
					glBegin(GL_QUADS);
						glNormal3f(0.0f,1.0f,0.0f);glTexCoord2f(0.0f,1.0f);glVertex3f(-25.0f+(i+mapx)*50.0f,0.0f, 25.0f+(j+mapz)*50.0f);
						glNormal3f(0.0f,1.0f,0.0f);glTexCoord2f(0.0f,0.0f);glVertex3f(-25.0f+(i+mapx)*50.0f,0.0f,-25.0f+(j+mapz)*50.0f);
						glNormal3f(0.0f,1.0f,0.0f);glTexCoord2f(1.0f,0.0f);glVertex3f( 25.0f+(i+mapx)*50.0f,0.0f,-25.0f+(j+mapz)*50.0f);
						glNormal3f(0.0f,1.0f,0.0f);glTexCoord2f(1.0f,1.0f);glVertex3f( 25.0f+(i+mapx)*50.0f,0.0f, 25.0f+(j+mapz)*50.0f);
					glEnd();
				}
		
		glPopMatrix();
		CGDisableProfilePixel();
		CGDisableProfileVertex();
		CGDisableTextureParameterAmbientReflectiveSea();
	}
	else
	{
		glPushMatrix();
			glEnable(GL_FOG);
			glScaled(1000.0,1000.0,1000.0);
			glDisable(GL_BLEND);
			//m_VBMD->ShowVBMD(ModelID_SHAN);
			int mapx,mapz;
			mapx=int(MFighter.RefPos()(0))/40000;
			mapz=int(MFighter.RefPos()(2))/40000;
			glBindTexture(GL_TEXTURE_2D,SeaTexID);
			glColor4f(0.0f,0.2f,0.6f,1.0f);
			for(int i=-3;i<4;i++)
				for(int j=-3;j<4;j++)
				{
					glBegin(GL_QUADS);
						glTexCoord2f( 0.0f,10.0f);glVertex3f(-20.0f+(i+mapx)*40.0f,0.0f, 20.0f+(j+mapz)*40.0f);
						glTexCoord2f( 0.0f, 0.0f);glVertex3f(-20.0f+(i+mapx)*40.0f,0.0f,-20.0f+(j+mapz)*40.0f);
						glTexCoord2f(10.0f, 0.0f);glVertex3f( 20.0f+(i+mapx)*40.0f,0.0f,-20.0f+(j+mapz)*40.0f);
						glTexCoord2f(10.0f,10.0f);glVertex3f( 20.0f+(i+mapx)*40.0f,0.0f, 20.0f+(j+mapz)*40.0f);
					glEnd();
				}
			glColor4f(1.0f,1.0f,1.0f,1.0f);
			glDisable(GL_FOG);
		glPopMatrix();	
	}
}
void SetMD5Frame(void)
{
	EnginePower=(InertiaSpeed+50.0f)*0.01f;
	EnginePower=1.0-(1.0-EnginePower)*(1.0-EnginePower);
	if((InertiaX_Last!=InertiaX)||(InertiaZ_Last!=InertiaZ))
	{
		md5_weiyiL.setFrame(int((-InertiaX-InertiaZ)*3.0/5.0)+30);
		md5_weiyiR.setFrame(int((-InertiaX+InertiaZ)*3.0/5.0)+30);
		md5_yinqingL.setFrame(int((-InertiaX-InertiaZ)*3.0/5.0)+30);
		md5_yinqingR.setFrame(int((-InertiaX+InertiaZ)*3.0/5.0)+30);
		md5_jinyiL.setFrame(int((-InertiaX-InertiaZ)*3.0/5.0)+30);
		md5_jinyiR.setFrame(int((-InertiaX+InertiaZ)*3.0/5.0)+30);
	}
	if(wingFrame_Last!=wingFrame)
	{
		md5_wingL.setFrame(wingFrame);
		md5_wingR.setFrame(wingFrame);
	}
	if(InertiaX_Last!=InertiaX)
	{
		md5_yayiL.setFrame(-int(InertiaX*6.0/5.0)+30);
		md5_yayiR.setFrame(-int(InertiaX*6.0/5.0)+30);
		md5_chuiweiL.setFrame(-int(InertiaX*6.0/5.0)+30);
		md5_chuiweiR.setFrame(-int(InertiaX*6.0/5.0)+30);
	}
	if((InertiaX_Last!=InertiaX)||(InertiaZ_Last!=InertiaZ)||(EnginePower_Last!=EnginePower))
	{
		md5_weiyanL.setFrame(int((-InertiaX-InertiaZ)*3.0/5.0)+30,EnginePower,EnginePower,EnginePower);
		md5_weiyanR.setFrame(int((-InertiaX+InertiaZ)*3.0/5.0)+30,EnginePower,EnginePower,EnginePower);
	}
	if(MissleBoxFrame_Last!=MissleBoxFrame)
		md5_MissleBox.setFrame(MissleBoxFrame);
	InertiaX_Last=InertiaX;
	InertiaZ_Last=InertiaZ;
	wingFrame_Last=wingFrame;
	EnginePower_Last=EnginePower;
	MissleBoxFrame_Last=MissleBoxFrame;
}
void SetPlayerTransform(void)
{/*
	MavePart_BackL.Reset();
	MavePart_BackR.Reset();
	MavePart_FL.Reset();
	MavePart_FR.Reset();
	MavePart_WL.Reset();
	MavePart_WR.Reset();
	MavePart_BackL.TranslateInternal(Vector3d(0.0,-4.0,37.0));
	MavePart_BackR.TranslateInternal(Vector3d(0.0,-4.0,37.0));
	MavePart_FL.TranslateInternal(Vector3d(-8.5,3.5,-20.0));
	MavePart_FR.TranslateInternal(Vector3d( 8.5,3.5,-20.0));
	MavePart_WL.TranslateInternal(Vector3d(0.0,0.0,55.0));
	MavePart_WR.TranslateInternal(Vector3d(0.0,0.0,55.0));
	MavePart_BackL.RotateInternal(Vector3d(InertiaX/256.0f+InertiaZ/256.0f, 0.0f, 0.0f) );
	MavePart_BackR.RotateInternal(Vector3d(InertiaX/256.0f-InertiaZ/256.0f, 0.0f, 0.0f) );
	MavePart_FL.RotateInternal(Vector3d(-InertiaX/128.0f-InertiaZ/128.0f, 0.0f, 0.0f) );
	MavePart_FR.RotateInternal(Vector3d(-InertiaX/128.0f+InertiaZ/128.0f, 0.0f, 0.0f) );
	MavePart_WL.RotateInternal(Vector3d(InertiaX/128.0f+InertiaZ/128.0f, 0.0f, 0.0f) );
	MavePart_WR.RotateInternal(Vector3d(InertiaX/128.0f-InertiaZ/128.0f, 0.0f, 0.0f) );
*/


	SetMD5Frame();

	ViewPoint.UDMplane=UDfighers[0].UDMplane;
	if(!IsHUD)
	ViewPoint.UDMplane.TranslateInternal(Vector3d(0.0f, 30.0f, 0.0f));
	//ViewPoint.UDMplane.RotateInternal(Vector3d(0.0f, 1.0f, 0.0f) * CRad(testNum * 360));
	ViewPoint.UDMplane.RotateInternal(Vector3d(CRad(ViewTurnY* 180.0f), 0.0f, 0.0f));
	ViewPoint.UDMplane.RotateInternal(Vector3d(0.0f, CRad(ViewTurnX* 180.0f), 0.0f));
	if(!IsHUD)
	{
		if(GameMode==1)
		{
			//ViewPoint.UDMplane.TranslateInternal(Vector3d(-turnZ*200.0, turnX*200.0, 150.0f));
			ViewPoint.UDMplane.TranslateInternal(Vector3d(0.0, 0.0, -150.0));
			ViewPoint.UDMplane.RotateInternal(Vector3d(turnX*0.75, turnZ*0.75, 0.0));
			ViewPoint.UDMplane.TranslateInternal(Vector3d(0.0, 0.0, 400.0));
		}
		else
			ViewPoint.UDMplane.TranslateInternal(Vector3d(0.0f, 0.0f, 150.0f));//-float(max(EffectImpact.EffectTime-45,0))turnZ*750.0, -turnX*750.0
	}
		
	MFighter=ViewPoint.UDMplane;


    // Position, Velocity Direction
    
    // q = MView * MWorld * MFighter * p, where p is a point in the fighter local coordsystem, and q is the point in the screen coordsystem.
    MView = (MWorld * MFighter).Invert();

	LightSunPos[0]=100000+(float)MFighter.RefPos()(0);
	LightSunPos[1]=100000+(float)MFighter.RefPos()(1);
	LightSunPos[2]=100000+(float)MFighter.RefPos()(2);
	Transform LMView;
	LMView = (MWorld * UDfighers[0].UDMplane).Invert();
	Vector3d Pos3d;
	Pos3d=LMView.Matrix() * Vector3d(LightSunPos[0],LightSunPos[1],LightSunPos[2]) + LMView.RefPos();
	paraLightDirection[0] = (float)Pos3d(0);
    paraLightDirection[1] = (float)Pos3d(1);
    paraLightDirection[2] = (float)Pos3d(2);



	Transform EyeMView;
	EyeMView = (MWorld * UDfighers[0].UDMplane).Invert();
	Vector3d EyePos3d;
	EyePos3d=EyeMView.Matrix() * MFighter.RefPos() + EyeMView.RefPos();
	eyePosition[0] = (float)EyePos3d(0);
    eyePosition[1] = (float)EyePos3d(1);
    eyePosition[2] = (float)EyePos3d(2);
	Vector3d eyeNormal=Vector3d(normalize(cross(Vector3d(0.0,0.0,1.0),Vector3d(normalize(EyePos3d)))));
	BackFireEyeDir[0]=(float)eyeNormal(0);
	BackFireEyeDir[1]=(float)eyeNormal(1);
	BackFireEyeDir[2]=(float)eyeNormal(2);
	BackFireEyeDir[3]=abs(dot(Vector3d(0.0,0.0,1.0),Vector3d(normalize(EyePos3d))));
	
	SunPos3d=MView.Matrix() * Vector3d(LightSunPos[0],LightSunPos[1],LightSunPos[2]) + MView.RefPos();

	if((MissleFireLightNum>=0)&&(MissleFireLightNum<MAXMISSLE))
	{
		Vector3d MisslePos;
		MisslePos=PMissleList.Missles[MissleFireLightNum].UDMplane.RefPos();
		double MissleLightL=sqrt(GetLength_2d(MisslePos,MFighter.RefPos()));
		if(MissleLightL<2000.0)
		{
			Vector3d MissleLightPos;
			MissleLightPos=EyeMView.Matrix() * MisslePos + EyeMView.RefPos();
			MissleLightDirection[0]=(float)MissleLightPos(0);
			MissleLightDirection[1]=(float)MissleLightPos(1);
			MissleLightDirection[2]=(float)MissleLightPos(2);
			MissleLightDirection[3]=MissleLightL;
			MissleLightColor[0]=float(1.0-MissleLightL/2000.0);
			MissleLightColor[1]=float(1.0-MissleLightL/2000.0)*0.5;
			MissleLightColor[2]=0.0f;
		
		}
		else
		{
			MissleLightColor[0]=0.0f;
			MissleLightColor[1]=0.0f;
			MissleLightColor[2]=0.0f;
			MissleFireLightNum=-1;
			MissleLightDirection[0]=0.0f;
			MissleLightDirection[1]=0.0f;
			MissleLightDirection[2]=0.0f;
			MissleLightDirection[3]=1000000.0f;
		}
	
	}
}

void DrawHP(int HPset,Transform& FighterModel,Transform& tfWorld)
{
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix winwidth,winheight
	glOrtho(-400,400,-400*winheight/winwidth,400*winheight/winwidth,-1000,2000);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();
	glEnable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, ShowHPTexID);	
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	float colorR,colorG;
	if(HPset>50)
	{
		colorR=float(100-HPset)*0.02f;
		colorG=1.0f;
	
	}
	else
	{
		colorG=float(HPset)*0.02f;
		colorR=1.0f;
	
	}

	glColor4f(colorR*0.5,colorG*0.5,0.0f,0.5f);

	Missledata HPmodel;
	Transform FModel;
	FModel=FighterModel;
	HPmodel.UDMplane.Translate(FModel.RefPos());
	HPmodel.UDPstate.MaxSpeed=0.0;
	HPmodel.UDPstate.MaxAngleSpeed=50.0;
	HPmodel.UDPstate.VelocityResistance=0.0;
	HPmodel.UDPstate.AngleVelocityResistance=0.1;
	HPmodel.UDMplane.Translate(Vector3d(0.0, 50.0, 0.0));
	HPmodel.TurnTo(FModel.RefPos());
	HPmodel.UDPstate.NextState();
	Transform LMView;
	LMView = (tfWorld * HPmodel.UDMplane).Invert();
	FModel.Rotate(Vector3d(1.0f, 0.0f, 0.0f) * CRad(90));
	FModel.Translate(Vector3d(300.0,-150.0*winheight/winwidth,0.0));
	glLoadIdentity();
	glLoadMatrixd(LMView.Matrix4());
	glMultMatrixd(FModel.Matrix4());

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	m_VBMD->ShowVBMD(ShowHPmodel);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void stage0(void)
{

	glMatrixMode (GL_PROJECTION);										// Select The Projection Matrix
	glLoadIdentity ();													// Reset The Projection Matrix
	gluPerspective (60.0f+float(max(EffectImpact.EffectTime-45,0))*0.1, (GLfloat)(winwidth)/(GLfloat)(winheight),			// Calculate The Aspect Ratio Of The Window
					10.0f, 100000.0f);		
	glMatrixMode (GL_MODELVIEW);										// Select The Modelview Matrix
	glLoadIdentity ();	
	glClearColor (0.0, 0.0, 0.0, 0.0);	
	glClear (GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer										// Reset The Modelview Matrix
	Vector3d pos;
	pos = UDfighers[0].UDMplane.RefPos();
    Vector3d dir;
    dir = UDfighers[0].UDMplane.Matrix() * Vector3d(0, 0, -1);
    Vector3d dir2;
    dir2 = UDfighers[0].UDMplane.Matrix() * Vector3d(1, 0, 0);
    // latitude is the angle between the fighter velocity and the ground (xOz). latitude = ArcCos[Sqrt[dir[0] ^ 2 + dir[2] ^ 2]] * Sign[dir[1]]
    double r = sqrt(pow(dir(0), 2) + pow(dir(2), 2));
    if (abs(r)>1){ r = 1.0f; }
    double latitude = acos_s(r) * 180.0f / PI;
    if (dir(1) < 0){ latitude = -latitude; }
	moveSpeedT=-latitude;
    // longitude is the rotation angle against y-axis. longitude = ArcCos[dir[2] / Sqrt[dir[0] ^ 2 + dir[2] ^ 2]] * Sign[dir[0]]
    double longitude = acos_s(dir(2) / r) * 180.0f / PI;
    if (dir(0) < 0){ longitude = -longitude; }
    // rotation is the rotation angle against the fighter velocity. rotation = ArcCos[dir2 * xOz.FindIntersect[dir].Normalize] * Sign[dir2[1]]
    double intersect[3] = {-dir(2) / r, 0, dir(0) / r};
    double rotation = acos_s(dir2(0) * intersect[0] + dir2(1) * intersect[1] + dir2(2) * intersect[2]) * 180.0f / PI;
    if (dir2(1) < 0){ rotation = -rotation; }
	SetPlayerTransform();
	//if(ShaderBloom)
	//	DrawHighLight();
	if(!IsSkip)
	{
		//glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(ShaderBloom)
			DrawBloomTex(winwidth,winheight);
		if(IsHUD)
		{
			glEnable(GL_BLEND);
			glClear (GL_COLOR_BUFFER_BIT );
			DrawUI1totexture(latitude);
			glClear (GL_COLOR_BUFFER_BIT );
			DrawUI2totexture(moveSpeed*60.0f*60.0f*60.0f*2000.0f/10000.0f);
			glClear (GL_COLOR_BUFFER_BIT );
			DrawUI3totexture(MFighter.RefPos()(1)*0.1);
			glClear (GL_COLOR_BUFFER_BIT );
		}
		if(!KeyT)
			DrawRedarToTexture();
		glClearColor (glClearColorR, glClearColorG, glClearColorB, glClearColorA);	
		DrawDataLine1();
		if(!IsHUD)
		DrawShadowMap();
	
	}
	
    glPushMatrix();
		glLoadMatrixd(MView.Matrix4());
		if(!IsSkip)
		{
			DrawSky(MFighter,(float)longitude);
			SkyBox.DrawSun((float)SunPos3d(0),(float)SunPos3d(1),(float)SunPos3d(2),winwidth,winheight);
			DrawGround();
			if(!IsHUD)
			{
				glEnable(GL_MULTISAMPLE_ARB);
				DrawPlayer();
				glDisable(GL_MULTISAMPLE_ARB);
			}
			DrawUnit();
			Shell.DrawShell(MFighter.RefPos(),MView,winwidth,winheight,tmpLookRenge);
			DrawMissle();
			if(ShaderBloom)
			{
				GetBloomTex(winwidth,winheight);

			}
			if(!GraphicsLOW)
				PSmokes.DrawSmoke(MFighter.RefPos(),MView,winwidth,winheight,tmpLookRenge);
			if(!IsHUD)
			if(!GraphicsLOW)
				DrawPlayerTranslucent();
			Drawlocksign();
			glEnable(GL_MULTISAMPLE_ARB);
			DrawUnitTrack();
			glDisable(GL_MULTISAMPLE_ARB);
			
		}
	glPopMatrix();
	glEnable(GL_BLEND);
	if((UseEffectImpact)&&(!IsSkip))
		EffectImpact.EffectImpactDraw(DrawEffectImpact);
	DrawEffectImpact=false;

		
	if(!IsSkip)
	{
		if(ShaderBloom)
			DrawBloom(winwidth,winheight);

		if(IsHUD)
		{
			glEnable(GL_BLEND);
			DrawUI2();
			DrawUI3();
			DrawUI4((float)InertiaX,(float)InertiaY,(float)InertiaZ);
			DrawUI1(rotation);
		}
		DrawHP(UDfighers[0].UDlife,UDfighers[0].UDMplane,MWorld);
		DrawDataLine2(MFighter.RefPos()(1),longitude,latitude);

		if(KeyT)
			DrawAREARedarToTexture((float)longitude);
		else
			DrawRedar((float)longitude);
	}
	
	//Maptexture=bloomTexId1;
	//Maptexture=Video.VideoTexID;
	//Maptexture=MyFont.TXTTexID;
//	Maptexture=img;


}
void DrawSmallWindow (Transform MSmallWindowIn,int winposX,int winposY,int SmallWindowW,int SmallWindowH,float SmallWindowLookRenge,int Windowtype)
{
	glMatrixMode (GL_PROJECTION);										// Select The Projection Matrix
	glLoadIdentity ();													// Reset The Projection Matrix
	gluPerspective (45, (GLfloat)(SmallWindowW)/(GLfloat)(SmallWindowH),			// Calculate The Aspect Ratio Of The Window
					10.0f, 100000.0f);		
	glMatrixMode (GL_MODELVIEW);										// Select The Modelview Matrix
	glLoadIdentity ();
	
	glPushAttrib(GL_VIEWPORT_BIT);
		glViewport(winposX,winposY,SmallWindowW, SmallWindowH);
		glClear (GL_DEPTH_BUFFER_BIT);
		Transform MSmallWindowView;
		Transform MSmallWindow;
		MSmallWindow=MSmallWindowIn;
		MSmallWindow.RotateInternal(Vector3d(0.0f, 1.0f, 0.0f) * CRad(180.0+float(playTime%1800)/1800.0f));
		MSmallWindow.TranslateInternal(Vector3d(0.0f, 0.0f, 250.0f));
		MSmallWindowView=(MWorld * MSmallWindow).Invert();
		glPushMatrix();
		bool locking=false;
			glLoadMatrixd(MSmallWindowView.Matrix4());
			if(Windowtype==0)
			{
				glClearColor (0.0, 0.0, 0.0, 1.0);	
				glClear (GL_COLOR_BUFFER_BIT );
				glDisable(GL_TEXTURE_2D);
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				//DrawGround();
				glColor3f(0.0f,1.0f,0.0f);
				if((PMissleList.Missles[SmallWindowTGT].TGTnum>=0)&&(PMissleList.Missles[SmallWindowTGT].TGTnum<MAXMISSLE))
					locking=UDfighers[PMissleList.Missles[SmallWindowTGT].TGTnum].m_DrawSelf( MSmallWindow.RefPos() ,SmallWindowW ,SmallWindowH ,SmallWindowLookRenge );
				if((PMissleList.Missles[SmallWindowTGT].onwer>=0)&&(PMissleList.Missles[SmallWindowTGT].onwer<MAXMISSLE))
					UDfighers[PMissleList.Missles[SmallWindowTGT].onwer].m_DrawSelf( MSmallWindow.RefPos() ,SmallWindowW ,SmallWindowH ,SmallWindowLookRenge );
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				glEnable(GL_TEXTURE_2D);
				glClearColor (glClearColorR, glClearColorG, glClearColorB, glClearColorA);	
			}
			if(Windowtype==1)
			{
				DrawSky(MSmallWindow);
				Vector3d SunPos3ds;
				SunPos3ds=MSmallWindowView.Matrix() * Vector3d(100000.0+MSmallWindow.RefPos()(0),100000.0+MSmallWindow.RefPos()(1),100000.0+MSmallWindow.RefPos()(2)) + MSmallWindowView.RefPos();
				SkyBox.DrawSun((float)SunPos3ds(0),(float)SunPos3ds(1),(float)SunPos3ds(2), SmallWindowW , SmallWindowH );
				DrawGround();
				glEnable(GL_CULL_FACE);
				for(int i=0;i<maxUnits;i++)
				{
					bool lockingt=UDfighers[i].m_DrawSelf( MSmallWindow.RefPos() ,SmallWindowW ,SmallWindowH ,SmallWindowLookRenge );
					if(i==PMissleList.Missles[SmallWindowTGT].TGTnum)
						locking=lockingt;
				}
				
				Shell.DrawShell( MSmallWindow.RefPos() ,MSmallWindowView ,SmallWindowW ,SmallWindowH ,SmallWindowLookRenge );
				//PMissleList.DrawMissle( MSmallWindow.RefPos() ,SmallWindowW ,SmallWindowH ,SmallWindowLookRenge );
				if(!GraphicsLOW)
					PSmokes.DrawSmoke( MSmallWindow.RefPos() ,MSmallWindowView ,SmallWindowW ,SmallWindowH ,SmallWindowLookRenge );
				glDisable(GL_CULL_FACE);
			}
			glEnable(GL_BLEND);
			if(locking)
			{
				glColor3f(0.0f,1.0f,0.0f);
				glPrints(0,0,128,128,"LOCK");
			}
			else
			{
				glColor3f(1.0f,0.0f,0.0f);
				if(lockflash>15)
					glPrints(0,0,128,128,"LOST");
			}
			glColor3f(1.0f,1.0f,1.0f);
		glPopMatrix();
	glPopAttrib();
	glBindTexture(GL_TEXTURE_2D, SmallWinTexID);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, winposX, winposY, SmallWinSize, SmallWinSize, 0);

}
void AfterDraw (void)
{

	 if (turnX != 0 || turnY != 0 || turnZ != 0)
	 {
		//Msky.RotateInternal(Vector3d(0.0f, 1.0f, 0.0f) * CRad(turnY * 6));
		if(GameMode==1)
		{
			Transform PlayerMoveTMP;
			PlayerMoveTMP=UDfighers[0].UDMplane;
			PlayerMoveTMP.Translate(Vector3d(turnZ*500.0, -turnX*500.0, 0.0f));
			if((PlayerMoveTMP.RefPos()(1)>1500.0)&&(PlayerMoveTMP.RefPos()(1)<10000.0))
				UDfighers[0].UDMplane.Translate(Vector3d(0.0, -turnX*500.0, 0.0f));
			if((PlayerMoveTMP.RefPos()(0)>-10000.0)&&(PlayerMoveTMP.RefPos()(0)<10000.0))
				UDfighers[0].UDMplane.Translate(Vector3d(turnZ*500.0, 0.0, 0.0f));
		}
		else
		{
			UDfighers[0].UDMplane.RotateInternal(Vector3d(0.0f, 1.0f, 0.0f) * CRad(-turnY * 6));
			UDfighers[0].UDMplane.RotateInternal(Vector3d(1.0f, 0.0f, 0.0f) * CRad(-turnX * 8));
			UDfighers[0].UDMplane.RotateInternal(Vector3d(0.0f, 0.0f, 1.0f) * CRad(-turnZ * 16+turnY*0.1));
		}
    }
//Acceleration
	if(moveSpeed>(MAXSpeed/3.0f))
		moveSpeed=moveSpeed-Acceleration*(moveSpeed-(MAXSpeed/3.0f))/(MAXSpeed-(MAXSpeed/3.0f));

	if(hited>0)
	{
		hited=hited-1;	
	}
	UDfighers[0].UDMplane.TranslateInternal(Vector3d(0.0f, 0.0f, -moveSpeed * 2000.0f));

	float playerSpeed=moveSpeed*60.0f*60.0f*60.0f*2000.0f/10000.0f;

	if(playerSpeed>1000.0f)
		DrawEffectImpact=true;
	if((playerSpeed>1000.0f)&&(wingFrame<60))
		wingFrame=wingFrame+1;
	if((playerSpeed<1000.0f)&&(wingFrame>0))
		wingFrame=wingFrame-1;
	if(wingFrame>60)
		wingFrame=60;
	if(wingFrame<0)
		wingFrame=0;


	DrawBom();	
	locksmove();
	DrawRadioTXT();
	MoveSound(MView,tmpLookRenge);
	UnitMove();
	if((SmallWindowTGT>=0)&&(SmallWindowTGT<MAXMISSLE))
		if(PMissleList.Missles[SmallWindowTGT].UDlife>1)
			DrawTex(SmallWinTexID,winheight/20,winheight-winheight/4-winheight/20,winheight/4,winheight/4,winwidth,winheight,1.0f,1.0f,1.0f,0.8f);
	if(PlayerLocked)
	{
		if(!lockedsound)
		{
			lockedsound=true;
			voiceSourceLocked->Play(true);
//			FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, soundLocked, 0, &channelLocked);
		}
	
	}
	else
	{
		if(lockedsound)
		{
			voiceSourceLocked->Stop();
			lockedsound=false;
//			FMOD_Channel_Stop(channelLocked);
		}
	
	}
	//testFPS();
	lockflash=lockflash+1;
	if(lockflash==30)
		lockflash=0;


	for(int i=0;i<100;i++)
	{
		if(timer[i]>0)
			timer[i]=timer[i]-1;
	}
}
void WaitKeyToStart(void)
{
		globalAmbient[0] = 0.05f; 
		globalAmbient[1] = 0.0f;
		globalAmbient[2] = 0.0f;
		globalAmbient[3] = 1.0f;

		paraLightColor[0] = 1.0f; 
		paraLightColor[1] = 1.0f;
		paraLightColor[2] = 1.0f;
		paraLightColor[3] = 1.0f;


	ViewPoint.UDMplane=UDfighers[0].UDMplane;
	ViewPoint.UDMplane.TranslateInternal(Vector3d(0.0f, 20.0f, 0.0f));
	ViewPoint.UDMplane.RotateInternal(Vector3d(0.0f, CRad((ViewTurnX+0.5f)* 180.0f), 0.0f));
	ViewPoint.UDMplane.TranslateInternal(Vector3d(0.0f, 0.0f, 120.0f));
	//ViewPoint.UDMplane.RotateInternal(Vector3d(CRad(-45.0f), 0.0f, 0.0f));
	MFighter=ViewPoint.UDMplane;

    MView = (MWorld * MFighter).Invert();

	LightSunPos[0]=-10000.0+(float)MFighter.RefPos()(0);
	LightSunPos[1]=10000.0+(float)MFighter.RefPos()(1);
	LightSunPos[2]=0.0+(float)MFighter.RefPos()(2);
	Transform LMView;
	LMView = (MWorld * UDfighers[0].UDMplane).Invert();
	Vector3d Pos3d;
	Pos3d=LMView.Matrix() * Vector3d(LightSunPos[0],LightSunPos[1],LightSunPos[2]) + LMView.RefPos();
	paraLightDirection[0] = (float)Pos3d(0);
    paraLightDirection[1] = (float)Pos3d(1);
    paraLightDirection[2] = (float)Pos3d(2);


	ViewTurnX=(float)playTime*0.00075;

	Transform EyeMView;
	EyeMView = (MWorld * UDfighers[0].UDMplane).Invert();
	Vector3d EyePos3d;
	EyePos3d=EyeMView.Matrix() * MFighter.RefPos() + EyeMView.RefPos();
	eyePosition[0] = (float)EyePos3d(0);
    eyePosition[1] = (float)EyePos3d(1);
    eyePosition[2] = (float)EyePos3d(2);

	
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	//StartShow();
	DrawShadowMap();
	DrawPlayer();
	glEnable(GL_BLEND);
	MyFont.DrawTXT(winwidth,winheight,winwidth/2-224,winheight/7,64,64,winwidth);
	glPrint(16,16,"Push Any Key To Start ",0);
	glDisable(GL_BLEND);
	if(isKeyDown||KeyInput.isAnyKeyDown)
	{
		isDraw=true;
		StartShowTime=300;
		BGMplayer->Play(true);

		paraLightColor[0] = LightDiffuseR; 
		paraLightColor[1] = LightDiffuseG;
		paraLightColor[2] = LightDiffuseB;
		paraLightColor[3] = LightDiffuseA;

		globalAmbient[0] = LightAmbientR; 
		globalAmbient[1] = LightAmbientG;
		globalAmbient[2] = LightAmbientB;
		globalAmbient[3] = LightAmbientA;
		ViewTurnX=0.0f;
		md5_weiyiL.setFrame(int((-InertiaX-InertiaZ)*3.0/5.0)+30);
		md5_weiyiR.setFrame(int((-InertiaX+InertiaZ)*3.0/5.0)+30);
		md5_yinqingL.setFrame(int((-InertiaX-InertiaZ)*3.0/5.0)+30);
		md5_yinqingR.setFrame(int((-InertiaX+InertiaZ)*3.0/5.0)+30);
		md5_jinyiL.setFrame(int((-InertiaX-InertiaZ)*3.0/5.0)+30);
		md5_jinyiR.setFrame(int((-InertiaX+InertiaZ)*3.0/5.0)+30);
		md5_wingL.setFrame(wingFrame);
		md5_wingR.setFrame(wingFrame);
		md5_yayiL.setFrame(-int(InertiaX*6.0/5.0)+30);
		md5_yayiR.setFrame(-int(InertiaX*6.0/5.0)+30);
		md5_chuiweiL.setFrame(-int(InertiaX*6.0/5.0)+30);
		md5_chuiweiR.setFrame(-int(InertiaX*6.0/5.0)+30);
		md5_weiyanL.setFrame(int((-InertiaX-InertiaZ)*3.0/5.0)+30,EnginePower,EnginePower,EnginePower);
		md5_weiyanR.setFrame(int((-InertiaX+InertiaZ)*3.0/5.0)+30,EnginePower,EnginePower,EnginePower);
		md5_MissleBox.setFrame(MissleBoxFrame);
//		Video.LoadVideo("Data/video/AFI_Panic01.avi",true);
	
	}

}
void Draw (void)
{

	if(UDfighers[0].UDlife<0)
		initUnitdata();

	glClearColor (0.0, 0.0, 0.0, 0.0);


	if(isDraw)
	{
		if(!IsSkip)
		{
			if((SmallWindowTGT>=0)&&(SmallWindowTGT<MAXMISSLE))
				if(PMissleList.Missles[SmallWindowTGT].UDlife>2)
					DrawSmallWindow(PMissleList.Missles[SmallWindowTGT].UDMplane,0,0,SmallWinSize,SmallWinSize,tmpLookRenge,SmallWindowType);
			stage0();
			
		}
		if(!GamePause)
			AfterDraw();
		else
		{
			if((playTime%40)>20)
			{
				glColor3f(0.0f,1.0f,0.0f);
				glPrints(winwidth/2-40,winheight/2,winwidth,winheight,"Pause");
				glColor3f(1.0f,1.0f,1.0f);
			}
		}

	}
	else
	{
		if(loadover)
			WaitKeyToStart();
	}

	if(!loadover)
	showloading();

	if(!IsSkip)
	LockFPS();

	
}






