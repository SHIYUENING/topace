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
};

#endif