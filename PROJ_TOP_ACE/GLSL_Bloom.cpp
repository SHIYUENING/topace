#include "GLSL_Bloom.h"
#include "FileSysBace.h"
#include "CharSysBace.h"
#include "Glsl.h"
#include "Common.h"
GLhandleARB Bloom_VS;
GLhandleARB Bloom_PS[3];
GLhandleARB Bloom_PO[3];
GLint GLSL_Bloom_Map_texColor=-1;
GLint GLSL_Bloom_Map_AveLum=-1;
//GLint GLSL_Bloom_Map_imgW=-1;
//GLint GLSL_Bloom_Map_imgH=-1;

GLint GLSL_Bloom_ToneMapping_texSrc1=-1;

GLint GLSL_Bloom_BlurTex_BlurTex=-1;
GLint GLSL_Bloom_BlurTex_BlurTexSet=-1;
void Init_GLSL_Bloom()
{
	Bloom_VS	  =CompileShader(L"data/shader/GLSL/Bloom/VS_common.glsl",GL_VERTEX_SHADER);
	Bloom_PS[BMAP]=CompileShader(L"data/shader/GLSL/Bloom/PS_BloomMap.glsl",GL_FRAGMENT_SHADER);
	Bloom_PS[TONE]=CompileShader(L"data/shader/GLSL/Bloom/PS_ToneMapping.glsl",GL_FRAGMENT_SHADER);
	Bloom_PS[BLUR]=CompileShader(L"data/shader/GLSL/Bloom/PS_BlurTex.glsl",GL_FRAGMENT_SHADER);
	CGLSL_Light_Attach(Bloom_PO+BMAP,Bloom_VS,0,0,0,Bloom_PS[BMAP]);GLSL_Bloom_BindAttrib(Bloom_PO[BMAP]);CGLSL_Light_Link_ProgramObject(Bloom_PO[BMAP]);
	CGLSL_Light_Attach(Bloom_PO+TONE,Bloom_VS,0,0,0,Bloom_PS[TONE]);GLSL_Bloom_BindAttrib(Bloom_PO[TONE]);CGLSL_Light_Link_ProgramObject(Bloom_PO[TONE]);
	CGLSL_Light_Attach(Bloom_PO+BLUR,Bloom_VS,0,0,0,Bloom_PS[BLUR]);GLSL_Bloom_BindAttrib(Bloom_PO[BLUR]);CGLSL_Light_Link_ProgramObject(Bloom_PO[BLUR]);
	Init_GLSL_Bloom_Uniform();
}
void GLSL_Bloom_BindAttrib(GLhandleARB GLSL_PO)
{
	glBindAttribLocation(GLSL_PO,AbLoc_Pos, "Position_in" );
	glBindAttribLocation(GLSL_PO,AbLoc_Tex0, "TexCoord0_in" );
}
void Deinit_GLSL_Bloom()
{
	ClearShaderObject(Bloom_PO[BMAP],Bloom_VS,0,0,0,Bloom_PS[BMAP]);
	ClearShaderObject(Bloom_PO[TONE],Bloom_VS,0,0,0,Bloom_PS[TONE]);
	ClearShaderObject(Bloom_PO[BLUR],Bloom_VS,0,0,0,Bloom_PS[BLUR]);
	DelShader(Bloom_VS);
	DelShader(Bloom_PS[BMAP]);
	DelShader(Bloom_PS[TONE]);
	DelShader(Bloom_PS[BLUR]);
}
void Init_GLSL_Bloom_Uniform()
{
	GLSL_Bloom_Map_texColor=glGetUniformLocation(Bloom_PO[BMAP],"texColor");
	GLSL_Bloom_Map_AveLum=glGetUniformLocation(Bloom_PO[BMAP],"AveLum");
	//GLSL_Bloom_Map_imgW=glGetUniformLocation(Bloom_PO[BMAP],"imgW");
	//GLSL_Bloom_Map_imgH=glGetUniformLocation(Bloom_PO[BMAP],"imgH");

	GLSL_Bloom_ToneMapping_texSrc1=glGetUniformLocation(Bloom_PO[TONE],"_texSrc1");

	GLSL_Bloom_BlurTex_BlurTex=glGetUniformLocation(Bloom_PO[BLUR],"BlurTex");
	GLSL_Bloom_BlurTex_BlurTexSet=glGetUniformLocation(Bloom_PO[BLUR],"BlurTexSet");
}
void GLSL_Enable_Bloom_Map()
{
	CO_SetGlslPO(Bloom_PO[BMAP]);
	glUseProgramObjectARB( Bloom_PO[BMAP]);
	glUniform1i(GLSL_Bloom_Map_texColor,0);
	glUniform1f(GLSL_Bloom_Map_AveLum,0.23f);
	//glUniform1f(GLSL_Bloom_Map_imgW,(float)WinW);
	//glUniform1f(GLSL_Bloom_Map_imgH,(float)WinH);
}
void GLSL_Enable_Bloom_ToneMapping()
{
	CO_SetGlslPO(Bloom_PO[TONE]);
	glUseProgramObjectARB( Bloom_PO[TONE] );
	glUniform1i(GLSL_Bloom_ToneMapping_texSrc1,0);
}
void GLSL_Enable_Bloom_BlurTex(float Size,bool WorH)
{
	float BlurTexSet[2]={0.0f,0.0f};
	if(WorH)
		BlurTexSet[0]=Size;
	else
		BlurTexSet[1]=Size;
	CO_SetGlslPO(Bloom_PO[BLUR]);
	glUseProgramObjectARB(Bloom_PO[BLUR]);
	glUniform1i(GLSL_Bloom_BlurTex_BlurTex,0);
	glUniform2fv(GLSL_Bloom_BlurTex_BlurTexSet,1,BlurTexSet);

}