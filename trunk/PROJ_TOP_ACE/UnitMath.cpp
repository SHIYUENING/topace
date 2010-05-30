#include "UnitMath.h"

CUnitMath::CUnitMath(void)
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
	//Easy_quat_to_matrix(UnitMatrix,QuatRotExternal);
	//Easy_matrix_mult_vector3X3(&UnitPos,UnitMatrix,UnitPos);
	//UnitPos.m128_f32[0]=1.0f;
}

void CUnitMath::RotInternal(__m128 QuatRotInternal)
{
	Easy_quat_Mult(&UnitQuat,QuatRotInternal,UnitQuat);
}

void CUnitMath::MovExternal(__m128 PosMovExternal)
{
	Easy_vector_add(&UnitPos,UnitPos,PosMovExternal);
	UnitPos.m128_f32[3]=1.0f;
}

void CUnitMath::MovInternal(__m128 PosMovInternal)
{
}
