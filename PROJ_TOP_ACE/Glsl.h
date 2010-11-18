#ifndef _GLSL_H
#define _GLSL_H
#include <GL/glew.h>

void InitGLSL();
void DeinitGLSL();
void GLSL_Enable_PhoneLight(int OmniLightNum=1,int SpotLightNum=0);
void GLSL_Disable();
void GLSL_Enable_StarPass0();
void GLSL_Enable_StarPass1();
void DrawBloomMapGLSL(int WinW,int WinH);
void ToneMappingGLSL();
void SSAOPass0();
void SSAOPass1(float SSAOset[4]);
void BlurTex(int Size,bool WorH);

void SetMMatrixToGlsl(GLfloat * MMatrix=0);
void SetPMatrixToGlsl(GLfloat * PMatrix=0);
void SetMVPMatrixToGlsl(GLfloat * MVPMatrix=0);
#endif