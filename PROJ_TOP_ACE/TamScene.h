//#pragma once
#ifndef _TAMSENE_H
#define _TAMSENE_H
#include "TopAceModel.h"
#include"IniFile.h"
struct _TamUnit
{
	CTopAceModel Model;
	float Pos[3];
	float scale[3];
	wchar_t * Name;
	float Limitfar;
	float Limitnear;
	bool DrawModel;
	bool DrawText;
	bool DrawName;
};

class CTamScene
{
public:
	CTamScene(void);
	~CTamScene(void);
	_TamUnit * Tams;
	void LoadFile(void);
	int ModelNum;
};

#endif