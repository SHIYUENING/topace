//#pragma once
#ifndef _MISSLELIST_H
#define _MISSLELIST_H
#include "missle.h"
#define MAXMISSLE 400

class MissleList
{
public:
	MissleList(void);
	~MissleList(void);
	bool Init(void);
	int AddMissle(Transform & Fighter,int TGT,int onwer,float FighterSpeed);
	void DrawMissle(const Vector3d& m_world,int m_winwidth,int m_winheight,float m_tmpLookRenge);

	Missledata Missles[MAXMISSLE];
	int MissleNum;
	int totalMissleNum;
};
#endif
