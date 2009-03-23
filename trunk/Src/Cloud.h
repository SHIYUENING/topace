//#pragma once
#ifndef _CLOUD_H
#define _CLOUD_H
#include "DDS.h"
#include "texture.h"
bool LoadTGA(Texture *, char *);

class CCloud
{
public:
	CCloud(void);
	~CCloud(void);
	bool Init(void);
	GLuint CloudTexID;
	GLuint base;//�ַ���ʾ��ر��
	int SetCloudPos(float posx, float posy, float posz);
	float CloudsPos[100][16][3];
};
#endif