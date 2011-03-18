#include "Glsl.h"
#include <stdio.h>	
#include <windows.h>
#include"IniFile.h"
#include "FileSysBace.h"
#include "TALogSys.h"
#include "CharSysBace.h"
#include "Common.h"
int GlslVer = 0;
int GLSLLightSet=0;
CTALogSys GLSLLOG;
CGLSLLoader GLSL_Sea;
CGLSLLoader GLSL_StarPass0,GLSL_StarPass1;
CGLSLLoader GLSL_SSAOPass0,GLSL_SSAOPass1;
extern tGameSet GameSet;
GLfloat GlslMatrixTMP[16];


extern int TessLevel;
void InitGLSL()
{
	if(glewIsSupported("GL_ARB_shading_language_100")) GlslVer=100;
	else return;
	GLSLLightSet = GameSet.Light;
	if(GameSet.Light<2) { GlslVer=0;return;}
	Init_GLSL_light(GameSet.Light);
	if(GameSet.Bloom>0) Init_GLSL_Bloom();
	if(GameSet.Shadow>0) Init_GLSL_Shadow();
	//GLSL_Sea.LoadShader(L"data/shader/GLSL_Sea.vs",L"data/shader/GLSL_Sea.ps");
	
	
	//GLSL_StarPass0.LoadShader(NULL,L"data/shader/Glsl_StarPass0_Pixel.ps");
	//GLSL_StarPass1.LoadShader(NULL,L"data/shader/Glsl_StarPass1_Pixel.ps");

	/*if(GameSet.SSAO>0)
	{
		GLSL_SSAOPass0.LoadShader(NULL,L"data/shader/Glsl_SSAO_Pass0.ps");
		GLSL_SSAOPass1.LoadShader(NULL,L"data/shader/Glsl_SSAO_Pass1.ps");
	}*/
}
void DeinitGLSL()
{
	if(GlslVer<100) return;
	GLSL_StarPass0.ClearShader();
	GLSL_StarPass1.ClearShader();
	GLSL_SSAOPass0.ClearShader();
	GLSL_SSAOPass1.ClearShader();

	GLSL_Sea.ClearShader();

	Deinit_GLSL_light();
	Deinit_GLSL_Bloom();
	Deinit_GLSL_Shadow();
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

void GLSL_SetMMatrixToGlsl(GLfloat * MMatrix)
{
	if(MMatrix)
		memcpy(GlslMatrixTMP, MMatrix, 16 * sizeof(GLfloat));
	else
	{
		CommonMatrixs[CO_Matrix_ModelView].GetF(GlslMatrixTMP);
		CO_GetMMatrix(GlslMatrixTMP);
	}
	glUniformMatrix4fv(glGetUniformLocation(CO_GetGlslPO(),"MMatrix"),1,false,GlslMatrixTMP);
}
void GLSL_SetPMatrixToGlsl(GLfloat * PMatrix)
{
	if(PMatrix)
		memcpy(GlslMatrixTMP, PMatrix, 16 * sizeof(GLfloat));
	else
	{
		CommonMatrixs[CO_Matrix_Proj].GetF(GlslMatrixTMP);
		CO_GetPMatrix(GlslMatrixTMP);
	}
	glUniformMatrix4fv(glGetUniformLocation(CO_GetGlslPO(),"PMatrix"),1,false,GlslMatrixTMP);
}
void GLSL_SetMVPMatrixToGlsl(GLfloat * MVPMatrix)
{
	if(MVPMatrix)
		memcpy(GlslMatrixTMP, MVPMatrix, 16 * sizeof(GLfloat));
	else
	{
		CommonMatrixs[CO_Matrix_ModelViewProj].GetF(GlslMatrixTMP);
		CO_GetMVPMatrix(GlslMatrixTMP);
	}
	glUniformMatrix4fv(glGetUniformLocation(CO_GetGlslPO(),"MVPMatrix"),1,false,GlslMatrixTMP);
}