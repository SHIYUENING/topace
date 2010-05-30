#include "UnitMath.h"

CUnitMath::CUnitMath(void)
: NewMatrix(false)
{
	UnitQuat=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
	UnitPos=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
}

CUnitMath::~CUnitMath(void)
{
}

void CUnitMath::RotExternal(__m128 QuatRotExternal)
{
	Easy_quat_Mult(&UnitQuat,UnitQuat,QuatRotExternal);
	NewMatrix=false;
}

void CUnitMath::RotInternal(__m128 QuatRotInternal)
{
	Easy_quat_Mult(&UnitQuat,QuatRotInternal,UnitQuat);
	NewMatrix=false;
}

void CUnitMath::MovExternal(__m128 PosMovExternal)
{
	Easy_vector_add(&UnitPos,UnitPos,PosMovExternal);
	UnitPos.m128_f32[3]=1.0f;
}

void CUnitMath::MovInternal(__m128 PosMovInternal)
{
	if(!NewMatrix)
	{
		Easy_quat_to_matrix(UnitMatrix,UnitQuat);
		NewMatrix=true;
	}
	UnitMatrix[3]=UnitPos;
	Easy_matrix_translate_Internal(UnitMatrix,PosMovInternal);
	UnitPos=UnitMatrix[3];
}

void CUnitMath::SetPos(__m128 Pos)
{
	UnitPos=Pos;
}

void CUnitMath::GetMatrix(__m128 MatrixOut[4])
{
	if(!NewMatrix)
	{
		Easy_quat_to_matrix(UnitMatrix,UnitQuat);
		NewMatrix=true;
	}
	UnitMatrix[3]=UnitPos;
	Easy_matrix_copy(MatrixOut,UnitMatrix);
}
