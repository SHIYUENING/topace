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
class CGLSL_Light
{
public:
	CGLSL_Light(void);
	~CGLSL_Light(void);
};

#endif