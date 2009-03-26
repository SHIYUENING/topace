//#pragma once
#ifndef _CLOUD_H
#define _CLOUD_H
#include "DDS.h"
#include "texture.h"
bool LoadTGA(Texture *, char *);

struct tCloudsPos{
	float Pos[3];
	GLuint CloudID;
	float CloudsL;
	bool islife;
};


class CCloud
{
public:
	CCloud(void);
	~CCloud(void);
	bool Init(void);
	void SetCloudPos(float posx, float posy, float posz);
	void addCloud(float x, float y, float z,GLuint CloudID);
	GLuint CloudTexID;
	GLuint base;//×Ö·ûÏÔÊ¾Ïà¹Ø±àºÅ
	tCloudsPos CloudsPos[1500];
	unsigned int CloudsPos_index;
	
};
#endif