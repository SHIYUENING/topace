//#pragma once
#ifndef _MGROUP_H
#define _MGROUP_H
#define GROUP_PATH L##"data\\Groups\\"
#include "TABTN.h"
#include<xstring>
#include<vector>
using namespace std;
struct _tMGroup
{
	vector<wstring> ModelNames;
	CTABTN BTN;
};
class CMGroup
{
public:
	CMGroup(void);
	~CMGroup(void);
	void LoadGroup(void);
	//vector<_tMGroup> MGroups;
	int AddOneGroup(wstring GroupPath);
	_tMGroup MGroup[4];
	void DrawBTN(void);
	bool CheakName(wchar_t * SceneName);
	bool CheakNameAll(wchar_t * SceneName);
	int GroupSetID;
	int CheckBTN(int x,int y);
	int GetGroup(wchar_t * SceneName);
};

#endif