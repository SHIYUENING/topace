//#pragma once
#include "EasyMatrix.h"
#ifndef _EXCHANGETHREAD_H
#define _EXCHANGETHREAD_H
#define DEFDATANUM 200
struct _ExchangeData
{
	__m128 Matrix[4];
};
class CExchangeThread
{
public:
	CExchangeThread(void);
	~CExchangeThread(void);
	static int ListCount;
	static _ExchangeData * DataUpdata;
	static _ExchangeData * DataDraw;
	static _ExchangeData * DataExchange;
	static bool AddListCount(void);
};
#endif