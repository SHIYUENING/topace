#ifndef _FBO_H
#define _FBO_H
#include <windows.h>
#include <stdlib.h>
#include <GL/glew.h>
#define StarTexSizeX 64
#define StarTexSizeY 1024
void CheckFBOError();
GLuint InitTex2D(int TexSizeX,int TexSizeY,GLfloat FILTER,GLuint FormatI,GLuint Format,GLuint DataType);
GLuint InitFBO();
void DeinitFBO();
void FBOS_Star_Begin();
void FBOS_Star_End();






#endif