#include "GLSL_Water.h"
#include "FileSysBace.h"
#include "CharSysBace.h"
#include "Glsl.h"
#include "Common.h"
GLhandleARB Water_VS;
GLhandleARB Water_PS;
GLhandleARB Water_PO;
GLint Water_MVPMatrix_Loc=-1;
GLint Water_MMatrix_Loc=-1;
GLint Water_ShadowMatrix_Loc=-1;
GLint Water_WMatrix_Loc=-1;

GLint Water_NormalTex=-1;
GLint Water_RefCubeTex=-1;
GLint Water_ShadowTex=-1;
GLint Water_ShadowTexSize=-1;
GLint Water_OmniLight_Pos=-1;
GLint Water_OmniLight_Color=-1;
GLint Water_Material=-1;
GLint Water_Global_Ambient=-1;
GLint Water_WaterSet=-1;
extern float WorldMatrix[16];
extern GLuint RefCubeTexID;
extern GLuint ShadowTexDepth;
void Init_GLSL_Water()
{
	Water_VS=CompileShader(L"data/shader/GLSL/Water/VS_120_SINGLBONE.glsl",GL_VERTEX_SHADER);
	Water_PS=CompileShader(L"data/shader/GLSL/Water/PS_120.glsl",GL_FRAGMENT_SHADER);
	
	CGLSL_Light_Attach(&Water_PO,Water_VS,0,0,0,Water_PS);
	glBindAttribLocation(Water_PO,AbLoc_Pos, "Position_in" );
	glBindAttribLocation(Water_PO,AbLoc_Tex0, "TexCoord0_in" );
	CGLSL_Light_Link_ProgramObject(Water_PO);
	Water_MVPMatrix_Loc=glGetUniformLocation(Water_PO,"MVPMatrix");
	Water_MMatrix_Loc = glGetUniformLocation(Water_PO,"MMatrix");
	Water_WMatrix_Loc = glGetUniformLocation(Water_PO,"WMatrix");
	Water_ShadowMatrix_Loc = glGetUniformLocation(Water_PO,"ShadowMatrix");

	Water_NormalTex = glGetUniformLocation(Water_PO,"NormalTex");
	Water_RefCubeTex = glGetUniformLocation(Water_PO,"RefCubeTex");
	Water_ShadowTex = glGetUniformLocation(Water_PO,"ShadowTex");
	//Water_ShadowTexSize = glGetUniformLocation(Water_PO,"ShadowTexSize");
	Water_OmniLight_Pos = glGetUniformLocation(Water_PO,"OmniLight_Pos");
	Water_OmniLight_Color = glGetUniformLocation(Water_PO,"OmniLight_Color");
	Water_Material = glGetUniformLocation(Water_PO,"Material");
	Water_Global_Ambient = glGetUniformLocation(Water_PO,"Global_Ambient");
	Water_WaterSet = glGetUniformLocation(Water_PO,"Water_WaterSet");
}
void Deinit_GLSL_Water()
{
	ClearShaderObject(Water_PO,Water_VS,0,0,0,Water_PS);
	DelShader(Water_VS);
	DelShader(Water_PS);
}
void GLSL_Enable_Water(float * WaterSet)
{
	
	CO_SetGlslPO(Water_PO);
	glUseProgramObjectARB( Water_PO );
	glUniform1i(Water_ShadowTex,ShaTexShot);
	glUniform1i(Water_RefCubeTex,RefTexShot);
	glUniform1i(Water_NormalTex,NorTexShot);
	glUniformMatrix4fv(Water_WMatrix_Loc,1,false,WorldMatrix);
	if(WaterSet)
		glUniform4fv(Water_WaterSet,1,WaterSet);
	glActiveTexture(GL_TEXTURE0+ShaTexShot);	
	glBindTexture(GL_TEXTURE_2D,ShadowTexDepth);
	glActiveTexture(GL_TEXTURE0+RefTexShot);	
	glBindTexture(GL_TEXTURE_CUBE_MAP_EXT,RefCubeTexID);
	glActiveTexture(GL_TEXTURE0);
		
	CommonMatrixs[CO_Matrix_ModelViewProj].GLSLLoc=Water_MVPMatrix_Loc;
	CommonMatrixs[CO_Matrix_Proj].GLSLLoc=-1;
	CommonMatrixs[CO_Matrix_ModelView].GLSLLoc=Water_MMatrix_Loc;
	CommonMatrixs[CO_Matrix_World].GLSLLoc=-1;
	CommonMatrixs[CO_Matrix_ShadowViewProj].GLSLLoc=Water_ShadowMatrix_Loc;

	CO_SetOmniLightGLSLLoc(Water_OmniLight_Pos,Water_OmniLight_Color);
	CO_SetOmniLightToGLSL();

	CO_SetMaterialGLSLLoc(Water_Material);
	CO_SetMaterialToGLSL(NULL);

	CO_SetGlobalAmbientGLSLLoc(Water_Global_Ambient);
	CO_SetGlobalAmbientToGLSL(NULL);

}