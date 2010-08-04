//#pragma once
#ifndef _UNITMATH_H
#define _UNITMATH_H
#include "Def.h"	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "EasyMatrix.h"
/*typedef enum _PosTo_Dir{
	_PosTo_Dir_NO_Dir= 0,
	_PosTo_Dir_X_Positive = 1,
	_PosTo_Dir_X_Negative = 2,
	_PosTo_Dir_Y_Positive = 3,
	_PosTo_Dir_Y_Negative = 4,
	_PosTo_Dir_Z_Positive = 5,
	_PosTo_Dir_Z_Negative = 6
}_PosTo_Dir;*/
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
	void GetMatrix(float MatrixOut[16]);
private:
	bool NewMatrix;
	__m128 UnitPosTMP;
public:
	__m128 GetRelativePos(__m128 TGTPos);
	void RotExternal(float angle,float axisX, float axisY, float axisZ);
	void RotInternal(float angle,float axisX, float axisY, float axisZ);
	void Reset(void);
	void PosTo(__m128 TGTPos);
	void PosTo(__m128 TGTPos,float Angle);
	void PosToDir(__m128 TGTPos);
	float TurnX;
	float TurnY;
	float TurnZ;
	bool NoTurn;
};
#endif