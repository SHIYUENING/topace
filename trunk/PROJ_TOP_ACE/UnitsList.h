//#pragma once
#ifndef _UNITSLIST_H
#define _UNITSLIST_H
#include "SceneUnit.h"
#define DEFLISTADDCOUNT 500
class CUnitsList
{
public:
	CUnitsList(void);
	~CUnitsList(void);
	CSceneUnit ** UnitsList;
	unsigned int ListCount;
	unsigned int DataCount;
	bool AddListCount(unsigned int AddNum=DEFLISTADDCOUNT);
	unsigned int AddOneUnit(CSceneUnit * Unit_Add=NULL);
	void DelOneUnit(unsigned int Unit_Del_Num);
	void UpdataList();
	void AnalysisSceneUnitAction(CSceneUnit * SceneUnit);
	void AnalysisFighterAction(CSceneUnit * FighterUnit);
	bool SetOneUnitPos(unsigned int Unit_ID,__m128 Pos);
	bool GetOneUnitPos(unsigned int Unit_ID,__m128 * Pos);

};

#endif