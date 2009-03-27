//#pragma once
#ifndef _CLOUD_H
#define _CLOUD_H
#define MAX_Cloud_NUM 1500
#include "Mathematics.h"
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
	tCloudsPos CloudsPos[MAX_Cloud_NUM];
	unsigned int CloudsPos_index;
	Vector3d Pos3d;
	float CloudSize;
	float tmpx;
	float tmpy;
	float tmpz;
	float tmpl;
	float tmpAlpha;

	void Draw(const Vector3d& ViewPos,Transform& would,float LookRenge);
};
#endif