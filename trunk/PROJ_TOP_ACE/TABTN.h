//#pragma once
#ifndef _TABTN_H
#define _TABTN_H
#include "Textures.h"
#include "DrawQUAD.h"
class CTABTN
{
public:
	CTABTN(void);
	~CTABTN(void);
	Textures Tex;
	int size[2];
	int Pos[2];
	void loadfile(wchar_t * filename);
	void ScaleSize(float W,float H);
	void Draw(void);
	void SetPos(int W,int H);
	bool GetCheck(int x,int y);
};

#endif