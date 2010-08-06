#include "UnitsList.h"


CUnitsList::CUnitsList(void)
: UnitsList(NULL)
, ListCount(DEFLISTADDCOUNT)
, DataCount(1)
{
	int ListIndexSize=4;
	while(ListIndexSize<sizeof(CSceneUnit *))
		ListIndexSize=ListIndexSize*2;
	UnitsList = (CSceneUnit **) _aligned_malloc(sizeof(CSceneUnit *)*ListCount,ListIndexSize);
	for(unsigned int i=0;i<ListCount;i++)
	{
		UnitsList[i]=NULL;
	}
	for(unsigned int i=0;i<DataCount;i++)
	{
		UnitsList[i]= (CSceneUnit *) _aligned_malloc(sizeof(CSceneUnit ),16);
	}
}


CUnitsList::~CUnitsList(void)
{
	if(UnitsList)
	{
		for(unsigned int i=0;i<ListCount;i++)
			if(UnitsList[i]) _aligned_free(UnitsList[i]);
		_aligned_free(UnitsList);
	}
}


bool CUnitsList::AddListCount(unsigned int AddNum)
{
	if(AddNum<=0)
		return false;
	if(!UnitsList)
		return false;
	int ListIndexSize=4;
	while(ListIndexSize<sizeof(CSceneUnit *))
		ListIndexSize=ListIndexSize*2;
	
	CSceneUnit ** ListTMP=(CSceneUnit **) _aligned_malloc(ListIndexSize*(ListCount+AddNum),ListIndexSize);
	if(ListTMP=NULL)
		return false;
	memcpy_s(ListTMP,ListIndexSize*(ListCount+AddNum),UnitsList,ListIndexSize*ListCount);
	_aligned_free(UnitsList);
	UnitsList=ListTMP;
	for(unsigned int i=0;i<AddNum;i++)
		UnitsList[i+ListCount]=NULL;
	ListCount=ListCount+AddNum;
	return true;
}


unsigned int CUnitsList::AddOneUnit(CSceneUnit * Unit_Add)
{
	int DataCountTMP=DataCount+1;
	if(DataCountTMP>=ListCount)
	{
		if(!AddListCount())
			return 0;
	}
	UnitsList[DataCount]=Unit_Add;
	DataCount=DataCountTMP;
	return DataCount-1;
}