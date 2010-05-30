//#pragma once
#ifndef _UNITMATH_H
#define _UNITMATH_H
#include "Def.h"	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "EasyMatrix.h"
class CUnitMath
{
public:
	CUnitMath(void);
	~CUnitMath(void);
	__m128 UnitQuat;
	__m128 UnitPos;
	__m128 UnitMatrix[4];
	void RotExternal(__m128 QuatRotExternal);
	void RotInternal(__m128 QuatRotInternal);
	void MovExternal(__m128 PosMovExternal);
	void MovInternal(__m128 PosMovInternal);
	void SetPos(__m128 Pos);
	void GetMatrix(__m128 MatrixOut[4]);
private:
	bool NewMatrix;
	
};
#endif