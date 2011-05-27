#ifndef _FBO_H
#define _FBO_H
#include <windows.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "Glsl.h"
#include"IniFile.h"
#define StarTexSizeX 256
#define StarTexSizeY 256
bool CheckFBOError();
GLuint InitTex2D(int TexSizeX,int TexSizeY,GLfloat FILTER,GLuint FormatI,GLuint Format,GLuint DataType,int TexTGT=GL_TEXTURE_2D);
bool InitFBO(int winW,int winH);
void DeinitFBO();
void FBOS_BLOOM();
void DrawUnitText(wchar_t * UnitText);
//void FBOS_Star_Begin();
//void FBOS_Star_End();
//void TestTexFBO();
//void FBOS_SSAO();





#endif