#ifndef _GLSL_H
#define _GLSL_H
#include <GL/glew.h>
#include "GLSLLoader.h"
#define AbLoc_Pos 0
#define AbLoc_Tex0 1
#define AbLoc_Normal 2
#define AbLoc_Color 3
#define AbLoc_BID 4
#define AbLoc_BWG 5
void InitGLSL();
void DeinitGLSL();
void GLSL_Disable();
void GLSL_Enable_StarPass0();
void GLSL_Enable_StarPass1();
void GLSL_Enable_SSAOPass0();
void GLSL_Enable_SSAOPass1(float SSAOset[4]);

void GLSL_SetMMatrixToGlsl(GLfloat * MMatrix=0);
void GLSL_SetPMatrixToGlsl(GLfloat * PMatrix=0);
void GLSL_SetMVPMatrixToGlsl(GLfloat * MVPMatrix=0);
#endif