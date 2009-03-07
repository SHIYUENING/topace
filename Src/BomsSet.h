//#pragma once
#ifndef _BOMSSET_H
#define _BOMSSET_H
#include "texture.h"

class CBomsSet
{
public:
	CBomsSet(void);
	~CBomsSet(void);
	GLuint Pnum;//图片编号
	int SizeStart;
	int SizeEnd;
	int ShowTimeStart;//开始时间
	int ShowTimeEnd;//结束时间
	int ColorAlphaStart;//透明度
	int ColorAlphaEnd;//透明度
	bool LoadBoms(int BomsNum);
	bool m_IsSupportFBO;
};
#endif