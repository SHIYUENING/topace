#include "ExchangeThread.h"
int CExchangeThread::ListCount=DEFDATANUM;
_ExchangeData * CExchangeThread::DataDraw = (_ExchangeData *)_aligned_malloc(sizeof(_ExchangeData)*CExchangeThread::ListCount,16);
_ExchangeData * CExchangeThread::DataUpdata = (_ExchangeData *)_aligned_malloc(sizeof(_ExchangeData)*CExchangeThread::ListCount,16);
_ExchangeData * CExchangeThread::DataExchange = (_ExchangeData *)_aligned_malloc(sizeof(_ExchangeData)*CExchangeThread::ListCount,16);
CExchangeThread::CExchangeThread(void)
{
}

CExchangeThread::~CExchangeThread(void)
{
}

bool CExchangeThread::AddListCount(void)
{
	_ExchangeData * ExchangeDataTMP;
	ExchangeDataTMP=CExchangeThread::DataDraw;
	CExchangeThread::DataDraw = (_ExchangeData *)_aligned_malloc(sizeof(_ExchangeData)*CExchangeThread::ListCount,16);
	memcpy_s(
		CExchangeThread::DataDraw,
		sizeof(_ExchangeData)*(CExchangeThread::ListCount+DEFDATANUM),
		ExchangeDataTMP,
		sizeof(_ExchangeData)*CExchangeThread::ListCount
		);
	_aligned_free(ExchangeDataTMP);
	ExchangeDataTMP=NULL;
	return false;
}
