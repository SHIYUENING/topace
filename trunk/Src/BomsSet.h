//#pragma once
#ifndef _BOMSSET_H
#define _BOMSSET_H
#include "texture.h"

class CBomsSet
{
public:
	CBomsSet(void);
	~CBomsSet(void);
	GLuint Pnum;//ͼƬ���
	int SizeStart;
	int SizeEnd;
	int ShowTimeStart;//��ʼʱ��
	int ShowTimeEnd;//����ʱ��
	int ColorAlphaStart;//͸����
	int ColorAlphaEnd;//͸����
	bool LoadBoms(int BomsNum);
	bool m_IsSupportFBO;
};
#endif