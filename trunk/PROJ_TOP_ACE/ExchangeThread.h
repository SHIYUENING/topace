//#pragma once
#include "EasyMatrix.h"
#ifndef _EXCHANGETHREAD_H
#define _EXCHANGETHREAD_H
#define DEFDATANUM 500

struct _UnitData
{
	__m128 Matrix[4];
};
class CExchangeThread
{
public:
	CExchangeThread(void);
	~CExchangeThread(void);
	_UnitData * DataList;
	int ListCount;
	bool AddListCount(int AddCount=DEFDATANUM);
	bool AddListToCount(int Count);
	bool AddData(_UnitData * UnitData,int Count=1);
	int DataNum;
};
#endif
