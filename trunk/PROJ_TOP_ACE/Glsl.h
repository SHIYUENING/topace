#ifndef _GLSL_H
#define _GLSL_H
#include <GL/glew.h>
#define AbLoc_Pos 1
#define AbLoc_Tex0 2
#define AbLoc_Normal 3
#define AbLoc_Color 4
void InitGLSL();
void DeinitGLSL();
void GLSL_Enable_PhoneLight(int OmniLightNum=1,int SpotLightNum=0);
void GLSL_Disable();
void GLSL_Enable_StarPass0();
void GLSL_Enable_StarPass1();
void GLSL_Enable_DrawBloomMapGLSL(int WinW,int WinH);
void GLSL_Enable_ToneMappingGLSL();
void GLSL_Enable_SSAOPass0();
void GLSL_Enable_SSAOPass1(float SSAOset[4]);
void GLSL_Enable_BlurTex(int Size,bool WorH);

void GLSL_SetMMatrixToGlsl(GLfloat * MMatrix=0);
void GLSL_SetPMatrixToGlsl(GLfloat * PMatrix=0);
void GLSL_SetMVPMatrixToGlsl(GLfloat * MVPMatrix=0);

#endif