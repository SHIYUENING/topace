//#pragma once

#ifndef _EXCHANGETHREAD_H
#define _EXCHANGETHREAD_H
#include "EasyMatrix.h"
#define DEFDATANUM 500
typedef enum _UnitData_States{
	_UnitData_States_NoUse = 0,
	_UnitData_States_Use = 1
}_UnitData_States;
typedef enum _ReadingThread_States{
	_ReadingThread_States_NoThread = 0,
	_ReadingThread_States_ThreadUpdataToExchange = 1,
	_ReadingThread_States_ThreadExchangeToDraw = 2
}_ReadingThread_States;
struct _UnitData
{
	float Matrix[16];
	_UnitData_States UnitData_States;
	int Type;
	char Name[8];
};

struct _Global_Data_Scene
{
	int PlayerID;
	int CamID;
};
struct _Global_Data_Sys
{
	int Tmp;
};
struct _Global_Data_Key
{
	BOOL keyDownLast [256];	
	BOOL keyDown_Now [256];	
};
struct _Global_Data
{
	_Global_Data_Scene Scene;
	_Global_Data_Sys Sys;
	int ChangePosOK;
};
struct _DrawToData
{
	_Global_Data_Key Global_Data_Key;
	float ViewTGTPos[3];
	float ViewPos[3];
	int ChangePos;
	float LimitZ[2];
};
class CExchangeThread
{
public:
	CExchangeThread(void);
	~CExchangeThread(void);
	_UnitData * DataList;
	int ListCount;
	int DataCount;
	bool AddListCount(int AddCount=DEFDATANUM);
	bool AddListToCount(int Count);
	bool AddOneData(_UnitData * UnitData,int * DataNum=NULL);
	bool UpdataOneData(_UnitData * UnitData,int DataNum);
	int GetOneUseAbleIndex(void);
	_Global_Data Global_Data;
	_DrawToData DrawToData;
};
void InitThreadUpdata();
void DeinitThreadUpdata();
void ThreadUpdataToExchange(CExchangeThread * ThreadDataUpdata);
void ThreadExchangeToDraw(CExchangeThread * ThreadDataDraw);
#endif
