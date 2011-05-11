//#pragma once
#ifndef _TAMSENE_H
#define _TAMSENE_H
#include "TopAceModel.h"
#include"IniFile.h"
#include<xstring>
#include<vector>
using namespace std;
//#define MODEL_PATH L##"data\\model\\"
struct _TamUnit
{
	wchar_t  Name[64];
	float Pos[3];
	float scale[3];
	float Limitfar;
	float Limitnear;
	CTopAceModel * Model;
	bool DrawModel;
	bool DrawText;
	bool DrawName;
};

class CTamScene
{
public:
	CTamScene(void);
	~CTamScene(void);
	void LoadFile(wchar_t * ModelFolder);
	int ModelNum;
	void ClearScene(void);
	bool AddUnit(wstring  ModelPath,_TamUnit * TamUnit);
	vector<_TamUnit> TamList;
	void ToVRAM(void);
	void Draw(bool Translucent,_TAM_Mesh_EXT_Type DrawType=_TAM_Mesh_EXT_Type_NoType);
};

#endif