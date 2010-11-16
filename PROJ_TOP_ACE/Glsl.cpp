#include "Glsl.h"
#include <stdio.h>	
#include <windows.h>
#include"IniFile.h"
#include "FileSysBace.h"
#include "TALogSys.h"
#include "GLSLLoader.h"
#include "CharSysBace.h"
int GlslVer = 0;
int GLSLLightSet=0;
CTALogSys GLSLLOG;
CGLSLLoader GLSL_Sea;
CGLSLLoader GLSL_PhoneLight;
CGLSLLoader GLSL_StarPass0,GLSL_StarPass1;
CGLSLLoader GLSL_ToneMapping;
CGLSLLoader GLSL_DrawBloomMap;
CGLSLLoader GLSL_SSAOPass0,GLSL_SSAOPass1;
CGLSLLoader GLSL_BlurTex;
extern tGameSet GameSet;
void InitGLSL()
{

	if(glewIsSupported("GL_ARB_shading_language_100")) GlslVer=100;
	else return;
	GLSLLightSet = GameSet.Light;
	if(GameSet.Light<2) { GlslVer=0;return;}
	const char* verstr = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	//GLSL_Sea.LoadShader(L"data/shader/GLSL_Sea.vs",L"data/shader/GLSL_Sea.ps");
	GLSL_PhoneLight.LoadShader(L"Light",GameSet.Light);

	//GLSL_StarPass0.LoadShader(NULL,L"data/shader/Glsl_StarPass0_Pixel.ps");
	//GLSL_StarPass1.LoadShader(NULL,L"data/shader/Glsl_StarPass1_Pixel.ps");
	
	if(GameSet.Bloom>0)
	{
		GLSL_DrawBloomMap.LoadShader(L"BloomMap",GameSet.Light);
		GLSL_ToneMapping.LoadShader(L"ToneMapping",GameSet.Light);
		//GLSL_DrawBloomMap.LoadShader(NULL,L"data/shader/BloomMap_pixel.glsl");
		//GLSL_ToneMapping.LoadShader(NULL,L"data/shader/ToneMapping_pixel.glsl");
	}
	if(GameSet.SSAO>0)
	{
		GLSL_SSAOPass0.LoadShader(NULL,L"data/shader/Glsl_SSAO_Pass0.ps");
		GLSL_SSAOPass1.LoadShader(NULL,L"data/shader/Glsl_SSAO_Pass1.ps");
	}
	//GLSL_BlurTex.LoadShader(NULL,L"data/shader/BlurTex.ps");
	GLSL_BlurTex.LoadShader(L"BlurTex",GameSet.Light);
}
void DeinitGLSL()
{
	if(GlslVer<100) return;
	GLSL_StarPass0.ClearShader();
	GLSL_StarPass1.ClearShader();
	GLSL_SSAOPass0.ClearShader();
	GLSL_SSAOPass1.ClearShader();

	GLSL_BlurTex.ClearShader();
	GLSL_Sea.ClearShader();
	GLSL_PhoneLight.ClearShader();
	GLSL_DrawBloomMap.ClearShader();
	GLSL_ToneMapping.ClearShader();
}
void GLSL_Enable_PhoneLight(int OmniLightNum,int SpotLightNum)
{
	int LightNums[2]={OmniLightNum,SpotLightNum};
	if(GlslVer<100) return;
	glUseProgramObjectARB( GLSL_PhoneLight.g_PO );
	glUniform1i(glGetUniformLocation(GLSL_PhoneLight.g_PO,"DiffuseTex"),0);
	glUniform2iv(glGetUniformLocation(GLSL_PhoneLight.g_PO,"LightNums"),1,LightNums);
}
void GLSL_Disable()
{
	if(GlslVer<100) return;
	glUseProgramObjectARB( NULL );
}
void GLSL_Enable_StarPass1()
{
	if(GlslVer<100) return;
	glUseProgramObjectARB( GLSL_StarPass1.g_PO );
	glUniform1i(glGetUniformLocation(GLSL_StarPass1.g_PO,"StarTex1"),0);
}
void GLSL_Enable_StarPass0()
{
	if(GlslVer<100) return;
	glUseProgramObjectARB( GLSL_StarPass0.g_PO );
	glUniform1i(glGetUniformLocation(GLSL_StarPass0.g_PO,"StarTex1"),0);
}
void DrawBloomMapGLSL(int WinW,int WinH)
{
	if(GlslVer<100) return;
	glUseProgramObjectARB( GLSL_DrawBloomMap.g_PO );
	glUniform1i(glGetUniformLocation(GLSL_DrawBloomMap.g_PO,"texColor"),0);
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomMap.g_PO,"AveLum"),0.23f);
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomMap.g_PO,"imgW"),(float)WinW);
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomMap.g_PO,"imgH"),(float)WinH);
}

void ToneMappingGLSL()
{
	if(GlslVer<100) return;
	glUseProgramObjectARB( GLSL_ToneMapping.g_PO );
	glUniform1i(glGetUniformLocation(GLSL_ToneMapping.g_PO,"_texSrc1"),0);
}
void SSAOPass0()
{
	if(GlslVer<100) return;
	glUseProgramObjectARB(GLSL_SSAOPass0.g_PO);
	glUniform1i(glGetUniformLocation(GLSL_SSAOPass0.g_PO,"DepthTex"),0);
	
}
void SSAOPass1(float SSAOset[4])
{
	if(GlslVer<100) return;
	glUseProgramObjectARB(GLSL_SSAOPass1.g_PO);
	glUniform1i(glGetUniformLocation(GLSL_SSAOPass1.g_PO,"DepthTex"),0);
	glUniform4fv(glGetUniformLocation(GLSL_SSAOPass1.g_PO,"SSAOset"),1,SSAOset);
	
}

void BlurTex(int Size,bool WorH)
{
	if(GlslVer<100) return;
	float BlurTexSet[2]={0.0f,0.0f};
	if(WorH)
		BlurTexSet[0]=1.0f/float(Size);
	else
		BlurTexSet[1]=1.0f/float(Size);
	glUseProgramObjectARB(GLSL_BlurTex.g_PO);
	glUniform1i(glGetUniformLocation(GLSL_BlurTex.g_PO,"BlurTex"),0);
	glUniform2fv(glGetUniformLocation(GLSL_BlurTex.g_PO,"BlurTexSet"),1,BlurTexSet);

}
