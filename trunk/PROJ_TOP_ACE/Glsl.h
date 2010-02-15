#ifndef _GLSL_H
#define _GLSL_H
#include <GL/glew.h>
void InitGLSL();
//void GLSL_Enable_ATC();
//void GLSL_Disable_ATC();
void GLSL_Enable_PhoneLight(float* LightColor,float* LightPosEye);
void GLSL_Disable();
#endif