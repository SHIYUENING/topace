#pragma once
#include "unitmath.h"

class CSceneUnit :
	public CUnitMath
{
public:
	CSceneUnit(void);
	~CSceneUnit(void);
	unsigned int UnitType;
	unsigned int ModelType;
	// Move Speed
	float MoveSPD;
	// Turn Speed
	float TurnSPD;
	// Move Speed Resistance
	float MoveSPD_R;
	// Turn Speed Resistance
	float TurnSPD_R;
	float Life;
	unsigned int Status;
};
