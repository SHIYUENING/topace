#ifndef _GLSL_H
#define _GLSL_H
#include <GL/glew.h>
void InitGLSL(int LightSet=2);
void DeinitGLSL();
//void GLSL_Enable_ATC();
//void GLSL_Disable_ATC();
void GLSL_Enable_PhoneLight(int OmniLightNum=1,int SpotLightNum=0);
void GLSL_Disable();
#endif