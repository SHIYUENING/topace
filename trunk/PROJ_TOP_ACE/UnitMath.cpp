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
void CUnitMath::RotExternal(float angle,float axisX, float axisY, float axisZ)
{
	Easy_quat_axis_angle(&UnitPosTMP,axisX,axisY,axisZ,-angle*3.1415926f/180.0f);
	Easy_quat_normalize(&UnitPosTMP,UnitPosTMP);
	RotExternal(UnitPosTMP);
}

void CUnitMath::RotExternal(__m128 QuatRotExternal)
{
	Easy_quat_Mult(&UnitQuat,UnitQuat,QuatRotExternal);
	Easy_quat_normalize(&UnitQuat,UnitQuat);
	NewMatrix=false;
}

void CUnitMath::RotInternal(float angle,float axisX, float axisY, float axisZ)
{
	Easy_quat_axis_angle(&UnitPosTMP,axisX,axisY,axisZ,-angle*3.1415926f/180.0f);
	Easy_quat_normalize(&UnitPosTMP,UnitPosTMP);
	RotInternal(UnitPosTMP);
}

void CUnitMath::RotInternal(__m128 QuatRotInternal)
{
	Easy_quat_Mult(&UnitQuat,QuatRotInternal,UnitQuat);
	Easy_quat_normalize(&UnitQuat,UnitQuat);
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

void CUnitMath::GetMatrix(float MatrixOut[16])
{
	if(!NewMatrix)
	{
		Easy_quat_to_matrix(UnitMatrix,UnitQuat);
		NewMatrix=true;
	}
	UnitMatrix[3]=UnitPos;
	Easy_matrix_copy(MatrixOut,UnitMatrix);
}

__m128 CUnitMath::GetRelativePos(__m128 TGTPos)
{
	if(!NewMatrix)
	{
		Easy_quat_to_matrix(UnitMatrix,UnitQuat);
		NewMatrix=true;
	}
	else
		UnitMatrix[3]=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
	Easy_vector_sub(&UnitPosTMP,TGTPos,UnitPos);
	Easy_matrix_mult_vector3X3(&UnitPosTMP,UnitMatrix,UnitPosTMP);
	UnitPosTMP.m128_f32[3]=1.0f;
	return UnitPosTMP;
}


void CUnitMath::Reset(void)
{
	UnitQuat=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
	UnitPos=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
	NewMatrix=false;
}
