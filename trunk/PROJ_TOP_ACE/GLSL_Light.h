//#pragma once
#ifndef GLSL_LIGHT_H
#define GLSL_LIGHT_H
#include "GLSLLoader.h"
#define GLSL120 0
#define GLSL150 1
#define GLSL400 2
#define SINGLBONE 0
#define MULTIBONE 1
void Init_GLSL_light(int LightSet);
void Deinit_GLSL_light();
void Init_GLSL_light_Uniform(int boneType,int GLSLver);
void GLSL_Enable_Light(int boneType,int GLSLver, int OmniLightNum,int SpotLightNum,int TessLevel);

#endif