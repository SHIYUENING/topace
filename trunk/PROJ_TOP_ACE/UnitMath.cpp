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
	Easy_quat_Mult(&UnitQuat,QuatRotExternal,UnitQuat);
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
	Easy_quat_Mult(&UnitQuat,UnitQuat,QuatRotInternal);
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
	/*if(!NewMatrix)
	{
		Easy_quat_to_matrix(UnitMatrix,UnitQuat);
		NewMatrix=true;
	}
	else
		UnitMatrix[3]=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);

	Easy_vector_sub(&UnitPosTMP,_mm_set_ps(1.0f,0.0f,0.0f,0.0f),TGTPos);
	Easy_matrix_mult_vector3X3(&UnitPosTMP,UnitMatrix,UnitPosTMP);
	Easy_vector_sub(&UnitPosTMP,UnitPos,UnitPosTMP);*/

	Easy_quat_to_matrix(UnitMatrix,UnitQuat);
	NewMatrix=true;
	UnitMatrix[3]=UnitPos;

	__m128 GetRelativePosMatrix[4];
	Easy_matrix_inv(UnitMatrix,GetRelativePosMatrix);
	Easy_matrix_mult_vector4X4(&UnitPosTMP,GetRelativePosMatrix,TGTPos);
	UnitPosTMP.m128_f32[3]=1.0f;
	return UnitPosTMP;
}


void CUnitMath::Reset(void)
{
	UnitQuat=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
	UnitPos=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
	NewMatrix=false;
}

void CUnitMath::PosTo(__m128 TGTPos)
{
	__m128 vecX,vecY,vecZ,vecNZ,vecTMP;
	Easy_vector_sub(&vecNZ,TGTPos,UnitPos);
	Easy_vector_normalize(&vecNZ,vecNZ);
	vecNZ.m128_f32[3]=0.0f;// vecNZ get

	Easy_vector_copy(&vecTMP,vecNZ);
	vecTMP.m128_f32[1]=0.0f;
	Easy_vector_normalize(&vecTMP,vecTMP);
	vecTMP.m128_f32[3]=0.0f;// vecNZ in xzFace shadow

	vecX.m128_f32[0]=-vecTMP.m128_f32[2];
	vecX.m128_f32[1]=0.0f;
	vecX.m128_f32[2]= vecTMP.m128_f32[0];
	vecX.m128_f32[3]=0.0f;// vecX get
	
	Easy_vector_sub(&vecZ,_mm_set_ps(0.0f,0.0f,0.0f,0.0f),vecNZ);
	//vecZ=vecNZ;
	vecZ.m128_f32[3]=0.0f;//vecZ=-vecNZ;

	Easy_vector_cross(&vecY,vecX,vecNZ);
	vecX.m128_f32[3]=0.0f;
	vecY.m128_f32[3]=0.0f;
	vecZ.m128_f32[3]=0.0f;
	Easy_vector_normalize(&vecX,vecX);
	Easy_vector_normalize(&vecY,vecY);
	Easy_vector_normalize(&vecZ,vecZ);

	Easy_matrix_identity(UnitMatrix);
	UnitMatrix[0]=vecX;
	UnitMatrix[1]=vecY;
	UnitMatrix[2]=vecZ;
	UnitMatrix[3]=UnitPos;

	NewMatrix=true;
	Easy_matrix_to_quat(&UnitQuat,UnitMatrix);
	Easy_quat_normalize(&UnitQuat,UnitQuat);

}

void CUnitMath::PosTo(__m128 TGTPos,float Angle)
{
	__m128 RelativePos=GetRelativePos(TGTPos);
	
	if(abs(RelativePos.m128_f32[0]*10.0f)<abs(RelativePos.m128_f32[2]))
	{
		if(RelativePos.m128_f32[1]>0.0f)
		{
		}
		else
		{
		}
	}
	else
	{
		if(RelativePos.m128_f32[1]>0.0f)
		{
			if(RelativePos.m128_f32[0]>0.0f)
				RotInternal(-Angle,0.0f,0.0f,1.0f);
			else
				RotInternal( Angle,0.0f,0.0f,1.0f);
		}
		else
		{
			if(RelativePos.m128_f32[0]>0.0f)
				RotInternal( Angle,0.0f,0.0f,1.0f);
			else
				RotInternal(-Angle,0.0f,0.0f,1.0f);
		}
	}

	if((abs(RelativePos.m128_f32[1]*10.0f)<abs(RelativePos.m128_f32[2]))&&(RelativePos.m128_f32[2]<0.0f))
	{
	}
	else
	{
		if(RelativePos.m128_f32[1]>=0.0f)
			RotInternal( Angle,1.0f,0.0f,0.0f);
		else
			RotInternal(-Angle,1.0f,0.0f,0.0f);
	}

}
