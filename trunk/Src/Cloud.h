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
};
#endif