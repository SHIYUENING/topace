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
	wchar_t text[2048];
	wchar_t  Name[64];
	float Pos[3];
	float scale[3];
	float Limitfar;
	float Limitnear;
	CTopAceModel * Model;
	bool DrawModel;
	bool DrawText;
	bool DrawName;
	int DrawScene;
	float Matrix[16];
	float UnitNamePos[4];
	float UnitNamePos2[4];
	float MoveSpeed;
	float UnitWinPosF[3];
	float WinPosDraw[3];
	float WinPosOut[3];//out Screem
	float WinPosIn[3];//in Screem
	bool PosInScreem;
	float NamePosDraw[4];
	float DrawSizehalf[2];
	Textures * NameTex;
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
	void GetUnitWinPos(float * UnitWinPos,int UnitID);
	void DrawUnitLine(int UnitID,int winW,int winH);
	void DrawUnitLineAll(int winW,int winH);
	void SetUnitNamePos(int winW,int winH,int Wnum=4);
	void DrawUnitName(int winW,int winH);
	int GetCheck(int Posx,int Posy);
	void UpdataPos(void);
	void DrawUnitName(void);
	float NameScale[2];
	float NameMove[2];
};

#endif