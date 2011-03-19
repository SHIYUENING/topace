#include "GLSL_Shadow.h"
#include "FileSysBace.h"
#include "CharSysBace.h"
#include "Glsl.h"
#include "Common.h"

GLhandleARB Shadow_VS;
GLhandleARB Shadow_PS;
GLhandleARB Shadow_PO;
GLint Shadow_MVPMatrix_Loc=-1;
void Init_GLSL_Shadow()
{
	Shadow_VS=CompileShader(L"data/shader/GLSL/Shadow/VS_120_SINGLBONE.glsl",GL_VERTEX_SHADER);
	Shadow_PS=CompileShader(L"data/shader/GLSL/Shadow/PS_120.glsl",GL_FRAGMENT_SHADER);
	
	CGLSL_Light_Attach(&Shadow_PO,Shadow_VS,0,0,0,Shadow_PS);
	glBindAttribLocation(Shadow_PO,AbLoc_Pos, "Position_in" );
	CGLSL_Light_Link_ProgramObject(Shadow_PO);
	Shadow_MVPMatrix_Loc=glGetUniformLocation(CO_GetGlslPO(),"MVPMatrix");
}
void Deinit_GLSL_Shadow()
{
	ClearShaderObject(Shadow_PO,Shadow_VS,0,0,0,Shadow_PS);
	DelShader(Shadow_VS);
	DelShader(Shadow_PS);
}
void GLSL_Enable_Shadow()
{
	CO_SetGlslPO(Shadow_PO);
	glUseProgramObjectARB( Shadow_PO);
	CommonMatrixs[CO_Matrix_ModelViewProj].GLSLLoc=Shadow_MVPMatrix_Loc;
	CommonMatrixs[CO_Matrix_Proj].GLSLLoc=-1;
	CommonMatrixs[CO_Matrix_ModelView].GLSLLoc=-1;
	CommonMatrixs[CO_Matrix_World].GLSLLoc=-1;
	CommonMatrixs[CO_Matrix_ShadowViewProj].GLSLLoc=-1;
	/*CO_SetMatrixsGLSLLoc(
		glGetUniformLocation(CO_GetGlslPO(),"MMatrix"),
		glGetUniformLocation(CO_GetGlslPO(),"PMatrix"),
		glGetUniformLocation(CO_GetGlslPO(),"MVPMatrix"));*/
}