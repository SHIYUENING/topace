//#pragma once
#ifndef _SKYBOX_H
#define _SKYBOX_H
#include "DDS.h"
#include "texture.h"
bool LoadTGA(Texture *, char *);
class CSkyBox
{
public:
	CSkyBox(void);
	~CSkyBox(void);
	bool Init(void);
	GLuint SkyTexID[6];
	Texture SkyTex[6];
	bool IsSupportFBO;
	void Draw(void);
};
#endif