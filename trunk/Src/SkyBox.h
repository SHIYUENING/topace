//#pragma once
#ifndef _SKYBOX_H
#define _SKYBOX_H
#include "DDS.h"
#include "texture.h"
bool LoadTGA(Texture *, char *);
//extern float testNum;
//extern float testNum2;
//extern float testNum3;
class CSkyBox
{
public:
	CSkyBox(void);
	~CSkyBox(void);
	bool Init(void);
	GLuint SkyTexID[6];
	GLuint SunTexID;
	GLuint SunCubeID;
	Texture SkyTex[6];
	Texture SunCubeTex[6];
	bool IsSupportFBO;
	void Draw(void);
	void DrawSun(float x,float y,float z,int winwidth,int winheight);
};
#endif