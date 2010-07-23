#include "ExchangeThread.h"
CExchangeThread::CExchangeThread(void)
: ListCount(DEFDATANUM)
, DataNum(0)
{
	DataList = (_UnitData *)_aligned_malloc(sizeof(_UnitData)*ListCount,16);
}

CExchangeThread::~CExchangeThread(void)
{
	_aligned_free(DataList);
}

bool CExchangeThread::AddListCount(int AddCount)
{
	if(AddCount<=0)
		return false;
	if(!DataList)
		return false;
	_UnitData * ListTMP=(_UnitData *)_aligned_malloc(sizeof(_UnitData)*(ListCount+AddCount),16);
	if(!ListTMP)
		return false;
	memcpy_s(ListTMP,sizeof(_UnitData)*(ListCount+AddCount),DataList,sizeof(_UnitData)*ListCount);
	_aligned_free(DataList);
	DataList=ListTMP;
	ListCount=ListCount+AddCount;
	return true;
}
bool CExchangeThread::AddListToCount(int Count)
{
	return AddListCount(Count-ListCount);
}
bool CExchangeThread::AddData(_UnitData * UnitData,int Count)
{
	if((!UnitData)||(Count<1))
		return false;
	while((DataNum+Count)>=ListCount)
	{
		AddListCount();
	}
	memcpy_s(&(DataList[DataNum]),sizeof(_UnitData)*(ListCount-DataNum),UnitData,sizeof(_UnitData)*Count);
	DataNum++;
	return true;
}
