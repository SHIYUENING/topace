#include "Glsl.h"
#include <stdio.h>	
#include <windows.h>
#include"IniFile.h"
#include "FileSysBace.h"
#include "TALogSys.h"
#include "GLSLLoader.h"
#include "CharSysBace.h"
#include "Common.h"
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
CGLSLLoader GLSL_Common;
extern tGameSet GameSet;
GLfloat GlslMatrixTMP[16];
void InitGLSL()
{

	if(glewIsSupported("GL_ARB_shading_language_100")) GlslVer=100;
	else return;
	GLSLLightSet = GameSet.Light;
	if(GameSet.Light<2) { GlslVer=0;return;}
	const char* verstr = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLSL_Common.LoadShader(L"common",2);
	//GLSL_Sea.LoadShader(L"data/shader/GLSL_Sea.vs",L"data/shader/GLSL_Sea.ps");
	GLSL_PhoneLight.LoadShader(L"Light",GameSet.Light);
	glBindAttribLocation(GLSL_PhoneLight.g_PO,AbLoc_Pos, "Position_in" );
	glBindAttribLocation(GLSL_PhoneLight.g_PO,AbLoc_Tex0, "TexCoord0_in" );
	glBindAttribLocation(GLSL_PhoneLight.g_PO,AbLoc_Normal, "Normal_in" );
	glBindAttribLocation(GLSL_PhoneLight.g_PO,AbLoc_Color, "Color_in" );
	GLSL_PhoneLight.GetGLSLLinkSTATUS(GLSL_PhoneLight.g_PO);

	//GLSL_StarPass0.LoadShader(NULL,L"data/shader/Glsl_StarPass0_Pixel.ps");
	//GLSL_StarPass1.LoadShader(NULL,L"data/shader/Glsl_StarPass1_Pixel.ps");
	
	if(GameSet.Bloom>0)
	{
		GLSL_DrawBloomMap.g_VS=GLSL_Common.g_VS;
		GLSL_DrawBloomMap.LoadShader(L"BloomMap",2);
		glBindAttribLocation( GLSL_DrawBloomMap.g_PO, AbLoc_Tex0, "TexCoord0_in" );
		glBindAttribLocation( GLSL_DrawBloomMap.g_PO, AbLoc_Pos, "Position_in" );
		GLSL_DrawBloomMap.GetGLSLLinkSTATUS(GLSL_DrawBloomMap.g_PO);

		
	//GLint success=0;
	//glGetProgramiv(GLSL_DrawBloomMap.g_PO,  GL_ACTIVE_ATTRIBUTES, &success);
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &success);
		GLSL_ToneMapping.g_VS=GLSL_Common.g_VS;
		GLSL_ToneMapping.LoadShader(L"ToneMapping",2);
		glBindAttribLocation( GLSL_ToneMapping.g_PO, AbLoc_Tex0, "TexCoord0_in" );
		glBindAttribLocation( GLSL_ToneMapping.g_PO, AbLoc_Pos, "Position_in" );
		GLSL_ToneMapping.GetGLSLLinkSTATUS(GLSL_ToneMapping.g_PO);
	}
	if(GameSet.SSAO>0)
	{
		GLSL_SSAOPass0.LoadShader(NULL,L"data/shader/Glsl_SSAO_Pass0.ps");
		GLSL_SSAOPass1.LoadShader(NULL,L"data/shader/Glsl_SSAO_Pass1.ps");
	}
	GLSL_BlurTex.g_VS=GLSL_Common.g_VS;
	GLSL_BlurTex.LoadShader(L"BlurTex",2);
	glBindAttribLocation( GLSL_BlurTex.g_PO, AbLoc_Tex0, "TexCoord0_in" );
	glBindAttribLocation( GLSL_BlurTex.g_PO, AbLoc_Pos, "Position_in" );
	GLSL_BlurTex.GetGLSLLinkSTATUS(GLSL_BlurTex.g_PO);
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
	GLSL_Common.ClearShader();
}
void GLSL_Enable_PhoneLight(int OmniLightNum,int SpotLightNum)
{
	int LightNums[2]={OmniLightNum,SpotLightNum};
	if(GlslVer<100) return;
	CO_SetGlslPO(GLSL_PhoneLight.g_PO);
	glUseProgramObjectARB( GLSL_PhoneLight.g_PO );
	glUniform1i(glGetUniformLocation(GLSL_PhoneLight.g_PO,"DiffuseTex"),0);
	glUniform2iv(glGetUniformLocation(GLSL_PhoneLight.g_PO,"LightNums"),1,LightNums);
}
void GLSL_Disable()
{
	if(GlslVer<100) return;
	CO_SetGlslPO(0);
	glUseProgramObjectARB( NULL );
}
void GLSL_Enable_StarPass1()
{
	if(GlslVer<100) return;
	CO_SetGlslPO(GLSL_StarPass1.g_PO);
	glUseProgramObjectARB( GLSL_StarPass1.g_PO );
	glUniform1i(glGetUniformLocation(GLSL_StarPass1.g_PO,"StarTex1"),0);
}
void GLSL_Enable_StarPass0()
{
	if(GlslVer<100) return;
	CO_SetGlslPO(GLSL_StarPass0.g_PO);
	glUseProgramObjectARB( GLSL_StarPass0.g_PO );
	glUniform1i(glGetUniformLocation(GLSL_StarPass0.g_PO,"StarTex1"),0);
}
void GLSL_Enable_DrawBloomMapGLSL(int WinW,int WinH)
{
	if(GlslVer<100) return;
	CO_SetGlslPO(GLSL_DrawBloomMap.g_PO);
	glUseProgramObjectARB( GLSL_DrawBloomMap.g_PO );
	glUniform1i(glGetUniformLocation(GLSL_DrawBloomMap.g_PO,"texColor"),0);
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomMap.g_PO,"AveLum"),0.23f);
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomMap.g_PO,"imgW"),(float)WinW);
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomMap.g_PO,"imgH"),(float)WinH);
}

void GLSL_Enable_ToneMappingGLSL()
{
	if(GlslVer<100) return;
	CO_SetGlslPO(GLSL_ToneMapping.g_PO);
	glUseProgramObjectARB( GLSL_ToneMapping.g_PO );
	glUniform1i(glGetUniformLocation(GLSL_ToneMapping.g_PO,"_texSrc1"),0);
}
void GLSL_Enable_SSAOPass0()
{
	if(GlslVer<100) return;
	CO_SetGlslPO(GLSL_SSAOPass0.g_PO);
	glUseProgramObjectARB(GLSL_SSAOPass0.g_PO);
	glUniform1i(glGetUniformLocation(GLSL_SSAOPass0.g_PO,"DepthTex"),0);
	
}
void GLSL_Enable_SSAOPass1(float SSAOset[4])
{
	if(GlslVer<100) return;
	CO_SetGlslPO(GLSL_SSAOPass1.g_PO);
	glUseProgramObjectARB(GLSL_SSAOPass1.g_PO);
	glUniform1i(glGetUniformLocation(GLSL_SSAOPass1.g_PO,"DepthTex"),0);
	glUniform4fv(glGetUniformLocation(GLSL_SSAOPass1.g_PO,"SSAOset"),1,SSAOset);
	
}

void GLSL_Enable_BlurTex(int Size,bool WorH)
{
	if(GlslVer<100) return;
	float BlurTexSet[2]={0.0f,0.0f};
	if(WorH)
		BlurTexSet[0]=1.0f/float(Size);
	else
		BlurTexSet[1]=1.0f/float(Size);
	CO_SetGlslPO(GLSL_BlurTex.g_PO);
	glUseProgramObjectARB(GLSL_BlurTex.g_PO);
	glUniform1i(glGetUniformLocation(GLSL_BlurTex.g_PO,"BlurTex"),0);
	glUniform2fv(glGetUniformLocation(GLSL_BlurTex.g_PO,"BlurTexSet"),1,BlurTexSet);

}
void GLSL_SetMMatrixToGlsl(GLfloat * MMatrix)
{
	if(MMatrix)
		memcpy(GlslMatrixTMP, MMatrix, 16 * sizeof(GLfloat));
	else
		CO_GetMMatrix(GlslMatrixTMP);
	glUniformMatrix4fv(glGetUniformLocation(CO_GetGlslPO(),"MMatrix"),1,false,GlslMatrixTMP);
}
void GLSL_SetPMatrixToGlsl(GLfloat * PMatrix)
{
	if(PMatrix)
		memcpy(GlslMatrixTMP, PMatrix, 16 * sizeof(GLfloat));
	else
		CO_GetPMatrix(GlslMatrixTMP);
	glUniformMatrix4fv(glGetUniformLocation(CO_GetGlslPO(),"PMatrix"),1,false,GlslMatrixTMP);
}
void GLSL_SetMVPMatrixToGlsl(GLfloat * MVPMatrix)
{
	if(MVPMatrix)
		memcpy(GlslMatrixTMP, MVPMatrix, 16 * sizeof(GLfloat));
	else
		CO_GetMVPMatrix(GlslMatrixTMP);
	glUniformMatrix4fv(glGetUniformLocation(CO_GetGlslPO(),"MVPMatrix"),1,false,GlslMatrixTMP);
}