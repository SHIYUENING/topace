//#pragma once
#include "EasyMatrix.h"
#ifndef _EXCHANGETHREAD_H
#define _EXCHANGETHREAD_H
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
};
void ThreadUpdataToExchange();
void ThreadExchangeToDraw();
#endif
