﻿#include "UnitsList.h"


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
	for(unsigned int i=0;i<DataCount;i++)
	{
		if(!UnitsList[i])
		{
			UnitsList[i]=Unit_Add;
			if(!Unit_Add)
				UnitsList[i]=(CSceneUnit *) _aligned_malloc(sizeof(CSceneUnit),16);
			return i;
		}
	}
	unsigned int DataCountTMP=DataCount+1;
	if(DataCountTMP>=ListCount)
	{
		if(!AddListCount())
			return 0;
	}
	UnitsList[DataCount]=Unit_Add;
	if(!Unit_Add)
		UnitsList[DataCount]=(CSceneUnit *) _aligned_malloc(sizeof(CSceneUnit),16);
	DataCount=DataCountTMP;
	return DataCount-1;
}

void CUnitsList::DelOneUnit(unsigned int Unit_Del_Num)
{
	if((Unit_Del_Num==0)||(Unit_Del_Num>=DataCount))
		return;
	if(UnitsList)
		return;
	if(!UnitsList[Unit_Del_Num])
		return;
	_aligned_free(UnitsList[Unit_Del_Num]);
	UnitsList[Unit_Del_Num]=NULL;
}

void CUnitsList::UpdataList()
{
	CSceneUnit * SceneUnit;
	if(UnitsList)
		return;
	for(unsigned int i=1;i<DataCount;i++)
	{
		SceneUnit=UnitsList[i];
		if(!SceneUnit)
			continue;
		else
			AnalysisSceneUnitAction(SceneUnit);
		SceneUnit->Updata();
	}
}

void CUnitsList::AnalysisSceneUnitAction(CSceneUnit * SceneUnit)
{
	if(SceneUnit->Operator==AI)
	{
		switch(SceneUnit->UnitType)
		{
			case Fighter:
			{
				if(SceneUnit->Life>0.0f)
					AnalysisFighterAction(SceneUnit);
				break;
			}
		}
	}
}

void CUnitsList::AnalysisFighterAction(CSceneUnit * FighterUnit)
{
	switch (FighterUnit->ACT_Order)
	{
	case StandBy:
		{
			FighterUnit->TGT_Pos=FighterUnit->StandByPos;
			break;
		}
	case FollowTo:
		{
			if(FighterUnit->FollowTGT_ID)
			{
				if(GetOneUnitPos(FighterUnit->FollowTGT_ID,&FighterUnit->TGT_Pos))
				{
					FighterUnit->PosToTGT_ID=FighterUnit->FollowTGT_ID;
					break;
				}
			}
			else
			{
				if(FighterUnit->Leader_ID)
				{
					if(GetOneUnitPos(FighterUnit->Leader_ID,&FighterUnit->TGT_Pos)) 
					{
						FighterUnit->PosToTGT_ID=FighterUnit->Leader_ID;
						break;
					}
				}
			}
			break;
		}
	case AttackTo:
		{
			if(FighterUnit->AttackTGT_ID)
			{
				if(GetOneUnitPos(FighterUnit->AttackTGT_ID,&FighterUnit->TGT_Pos))
				{
					FighterUnit->PosToTGT_ID=FighterUnit->AttackTGT_ID;
					break;
				}
			}
			break;
		}
	case Avoid:
		{
			if(FighterUnit->ReAttackTGT_ID)
			{
				if(GetOneUnitPos(FighterUnit->ReAttackTGT_ID,&FighterUnit->TGT_Pos)) 
				{
					FighterUnit->PosToTGT_ID=FighterUnit->ReAttackTGT_ID;
					__m128 TGTdir;
					Easy_vector_sub(&TGTdir,FighterUnit->TGT_Pos,FighterUnit->UnitPos);
					if(Easy_vector_Getlenth_2(FighterUnit->TGT_Pos,FighterUnit->UnitPos)>0.01f)
					{
						Easy_vector_normalize(&TGTdir,TGTdir);
						float TGTdirDot=Easy_vector_dot(TGTdir,FighterUnit->UnitMatrix[2]);
					}
				}
				//if()

			}
			break;
		}
	}
	//if(FighterUnit->ACT_Order)
}

bool CUnitsList::SetOneUnitPos(unsigned int Unit_ID,__m128 Pos)
{
	if(Unit_ID<=0) return false;
	if(!UnitsList) return false;
	if(Unit_ID>=DataCount) return false;
	if(!(UnitsList[Unit_ID])) return false;
	UnitsList[Unit_ID]->SetPos(Pos);
	return true;
}

bool CUnitsList::GetOneUnitPos(unsigned int Unit_ID,__m128 * Pos)
{
	if(!Pos) return false;
	if(Unit_ID<=0) return false;
	if(!UnitsList) return false;
	if(Unit_ID>=DataCount) return false;
	if(!(UnitsList[Unit_ID])) return false;
	Pos[0]=UnitsList[Unit_ID]->UnitPos;
	return true;
}