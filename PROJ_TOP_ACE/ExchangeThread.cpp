#include "ExchangeThread.h"
CExchangeThread ThreadDataUpdata,ThreadDataDraw,ThreadDataExchange;
CExchangeThread::CExchangeThread(void)
: ListCount(DEFDATANUM)
, DataCount(0)
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
bool CExchangeThread::AddOneData(_UnitData * UnitData,int * DataNum)
{
	if((!UnitData)||(!DataList))
		return false;
	for(int ListNumTMP=0;ListNumTMP<ListCount;ListNumTMP++)
	{
		if(DataList[ListNumTMP].UnitData_States==_UnitData_States_NoUse)
		{
			DataList[ListNumTMP].UnitData_States=_UnitData_States_Use;
			memcpy_s(&(DataList[ListNumTMP]),sizeof(_UnitData),UnitData,sizeof(_UnitData));
			if(DataNum)
				DataNum[0]=ListNumTMP;
			return true;
		}
	}
	if(DataCount>=ListCount)
	{
		if(!AddListCount())
			return false;
	}
	memcpy_s(&(DataList[DataCount]),sizeof(_UnitData),UnitData,sizeof(_UnitData));
	if(DataNum)
		DataNum[0]=DataCount;
	DataCount++;
	return true;
}

bool CExchangeThread::UpdataOneData(_UnitData * UnitData,int DataNum)
{
	if((!UnitData)||(!DataList))
		return false;
	memcpy_s(&(DataList[DataNum]),sizeof(_UnitData),UnitData,sizeof(_UnitData));
	return true;
}
