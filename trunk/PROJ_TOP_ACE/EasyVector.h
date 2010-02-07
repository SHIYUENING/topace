#ifndef _EASYVECTOR_H
#define _EASYVECTOR_H
#include "Def.h"	
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <xmmintrin.h>

inline void Easy_vector_add(float c[3], float a[3], float b[3]) {
    int i;
    for (i = 0; i < 3; ++i) {
        c[i] = a[i] + b[i];
    }
}
inline void Easy_vector_add(__m128 * c, const __m128 a, const __m128 b) 
{
	_asm 
	{
		movaps xmm0, a
		movaps xmm1, b
		addps xmm0, xmm1
		mov    ecx, c
		movups [ecx], xmm0
	}
}
inline void Easy_vector_sub(float c[3], float a[3], float b[3]) 
{
    int i;
    for (i = 0; i < 3; ++i) {
        c[i] = a[i] - b[i];
    }
}

inline void Easy_vector_sub(__m128 * c, const __m128 a, const __m128 b) 
{
	_asm 
	{
		movaps xmm0, a
		movaps xmm1, b
		subps xmm0, xmm1
		mov    ecx, c
		movups [ecx], xmm0
	}
}
inline void Easy_vector_scalar_mul(float out[3],const float inVec[3],const float in)
{
	int i;
    for (i = 0; i < 3; ++i) {
        out[i] = inVec[i] *in;
    }
}
inline void Easy_vector_scalar_mul(__m128 * outVec,const __m128 inVec,const float in)
{
	__m128 scalar;
	scalar=_mm_set_ps1(in);
	_asm
	{
		movaps xmm0, inVec
		movaps xmm1, scalar
		mulps xmm0, xmm1
		mov    ecx, outVec
		movups [ecx], xmm0
	}

}
inline void Easy_vector_cross(float c[3], float a[3], float b[3]) 
{
#ifdef USE_SSE

	__m128 INa,INb,OUTc;
	INa.m128_f32[0]=a[0];
	INa.m128_f32[1]=a[1];
	INa.m128_f32[2]=a[2];
	INa.m128_f32[3]=0.0f;

	INb.m128_f32[0]=b[0];
	INb.m128_f32[1]=b[1];
	INb.m128_f32[2]=b[2];
	INb.m128_f32[3]=0.0f;
	_asm 
	{
		movups xmm0, INa
		movups xmm1, INb
		movaps xmm2, xmm0
		movaps xmm3, xmm1
		shufps xmm0, xmm0, 0xc9
		shufps xmm1, xmm1, 0xd2
		mulps xmm0, xmm1
		shufps xmm2, xmm2, 0xd2
		shufps xmm3, xmm3, 0xc9
		mulps xmm2, xmm3
		subps xmm0, xmm2
		movups OUTc, xmm0
	}
	c[0]=OUTc.m128_f32[0];
	c[1]=OUTc.m128_f32[1];
	c[2]=OUTc.m128_f32[2];
#else
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
#endif
}
inline void Easy_vector_cross(__m128 * OUTc,const __m128 INa,const __m128 INb) 
{
	_asm 
	{
		movaps xmm0, INa
		movaps xmm1, INb
		movaps xmm2, xmm0
		movaps xmm3, xmm1
		shufps xmm0, xmm0, 0xc9
		shufps xmm1, xmm1, 0xd2
		mulps xmm0, xmm1
		shufps xmm2, xmm2, 0xd2
		shufps xmm3, xmm3, 0xc9
		mulps xmm2, xmm3
		subps xmm0, xmm2
		mov    ecx, OUTc
		movups [ecx], xmm0
	}
}
inline void Easy_vector_normalize(float c[3]) 
{
#ifdef USE_SSE
	__m128 tmp;
	tmp.m128_f32[0]=c[0];
	tmp.m128_f32[1]=c[1];
	tmp.m128_f32[2]=c[2];
	tmp.m128_f32[3]=0.0f;
  _asm   {   
  movaps   xmm1,   tmp   
  movaps   xmm0,   xmm1   
  mulps     xmm1,   xmm1   
    
  movaps   xmm2,   xmm1   
  shufps   xmm2,   xmm1,   0x09   
  movaps   xmm3,   xmm2   
  shufps   xmm3,   xmm2,   0x09   
  addps     xmm1,   xmm2   
  addps     xmm1,   xmm3   
    
  sqrtps   xmm1,   xmm1   
  divps     xmm0,   xmm1   
    
  movaps   tmp,   xmm0   
  } 
  c[0]=tmp.m128_f32[0];
  c[1]=tmp.m128_f32[1];
  c[2]=tmp.m128_f32[2];
#else
    float l, m;

    l = (float)sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    if (fabs(l) < 1e-5) {
        if ((c[0] >= c[1]) && (c[0] >= c[2])) {
            c[0] = 1.0f;
            c[1] = c[2] = 0.0f;
        } else
            if (c[1] >= c[2]) {
                c[1] = 1.0f;
                c[0] = c[2] = 0.0f;
            } else {
                c[2] = 1.0f;
                c[0] = c[1] = 0.0f;
            }
    } else {
        m = 1.0f / l;
        c[0] *= m;
        c[1] *= m;
        c[2] *= m;
    }
#endif
}
inline void Easy_vector_norm2(float * lenOut,float vecIn[3])
{
	*lenOut=(float)sqrt(vecIn[0] * vecIn[0] + vecIn[1] * vecIn[1] + vecIn[2] * vecIn[2]);
}
inline float Easy_vector_norm2(float vecIn[3]) 
{
    return((float)sqrt(vecIn[0]*vecIn[0] + vecIn[1]*vecIn[1] + vecIn[2]*vecIn[2]));
}

inline void Easy_vector_norm2(__m128 * lenOut,const __m128 vecIn)
{
	_asm   
	{    
	movaps   xmm0,   vecIn 
	movaps	 xmm1,   xmm0 
	mulps	 xmm1,   xmm0   
    
	movaps   xmm2,   xmm1   
	movaps   xmm3,   xmm1  
	//shufps   xmm1,   xmm1,   0x55 
	shufps   xmm2,   xmm2,   0x55  
	shufps   xmm3,   xmm2,   0xaa   
	addss	 xmm1,   xmm2   
	addss    xmm1,   xmm3   
	sqrtss   xmm1,   xmm1  
	//movss    eax,    xmm1

	mov		 ecx,    lenOut
	movaps	     [ecx],  xmm1  
  }   
}
inline float Easy_vector_norm2(__m128 vecIn) 
{
	_asm   
	{    
	movaps   xmm0,   vecIn 
	movaps	 xmm1,   xmm0 
	mulps	 xmm1,   xmm0   
    
	movaps   xmm2,   xmm1   
	movaps   xmm3,   xmm1  
	//shufps   xmm1,   xmm1,   0x55 
	shufps   xmm2,   xmm2,   0x55  
	shufps   xmm3,   xmm2,   0xaa   
	addss	 xmm1,   xmm2   
	addss    xmm1,   xmm3   
	
	sqrtss   xmm1,   xmm1  
	movaps	 vecIn,	 xmm1
	//movss    eax,    xmm1

	//mov		 ecx,    lenOut
	//movups	     [ecx],  xmm1  
	} 
	return(vecIn.m128_f32[0]);
}
inline void Easy_vector_normalize(__m128 * vecOut,const __m128 vecIn)   
  {   
	_asm   
	{    
	movaps   xmm1,   vecIn
	movaps   xmm0,   xmm1   
	mulps	 xmm1,   xmm1   
    
	movaps   xmm2,   xmm1   
	shufps   xmm2,   xmm1,   0x09   
	movaps   xmm3,   xmm2   
	shufps   xmm3,   xmm2,   0x09   
	addps	 xmm1,   xmm2   
	addps    xmm1,   xmm3   
    
	sqrtps   xmm1,   xmm1   
	divps    xmm0,   xmm1   

	mov		 ecx,    vecOut
	movups	 [ecx],  xmm0  
  }   
  } 
inline void Easy_vector_transform(float c[3], float m[4][4], float a[3]) {
    c[0] = m[0][0] * a[0] + m[1][0] * a[1] + m[2][0] * a[2] + m[3][0];
    c[1] = m[0][1] * a[0] + m[1][1] * a[1] + m[2][1] * a[2] + m[3][1];
    c[2] = m[0][2] * a[0] + m[1][2] * a[1] + m[2][2] * a[2] + m[3][2];
}
inline void Easy_vector_transform(__m128 * vOut, const __m128 MatrixIn[4], const __m128 vIN) {
	//Out[0].m128_f32[0] = Matrix[0].m128_f32[0] * Pos.m128_f32[0] + Matrix[1].m128_f32[0] * Pos.m128_f32[1] + Matrix[2].m128_f32[0] * Pos.m128_f32[2] + Matrix[3].m128_f32[0];
	//Out[0].m128_f32[1] = Matrix[0].m128_f32[1] * Pos.m128_f32[0] + Matrix[1].m128_f32[1] * Pos.m128_f32[1] + Matrix[2].m128_f32[1] * Pos.m128_f32[2] + Matrix[3].m128_f32[1];
	//Out[0].m128_f32[2] = Matrix[0].m128_f32[2] * Pos.m128_f32[0] + Matrix[1].m128_f32[2] * Pos.m128_f32[1] + Matrix[2].m128_f32[2] * Pos.m128_f32[2] + Matrix[3].m128_f32[2];
	_asm
	{
		mov edx,MatrixIn
		movups xmm4,[edx]
		movups xmm5,[edx+16]
		movups xmm6,[edx+32]
		movups xmm7,[edx+48]

		movups xmm0,vIN
		movups xmm1,xmm0
		movups xmm2,xmm0
		//movups xmm3,xmm0

		//shufps xmm3,xmm3,0xff
		shufps xmm2,xmm2,0xaa
		shufps xmm1,xmm1,0x55
		shufps xmm0,xmm0,0x00

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		//mulps xmm3,xmm7

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm7//addps xmm0,xmm3
		mov    ecx, vOut
		movups [ecx], xmm0
	}

}
inline float Easy_vector_dot(float a[3], float b[3]) {
    return(a[0]*b[0] + a[1]*b[1] + a[2]*b[2]);
}
inline float Easy_vector_dot(__m128 v1, __m128 v2)
{
	__asm
	{
	  movaps   xmm0,   v1   
	  movaps   xmm1,   v2  
	  mulps	   xmm0,   xmm1
	  movaps   xmm1,xmm0
	  movaps   xmm2,xmm0
	  shufps   xmm0,xmm0,0x00
	  shufps   xmm1,xmm1,0x55
	  shufps   xmm2,xmm2,0xaa
	  addps  xmm0,xmm1 
	  addps  xmm0,xmm2 
	  movaps v1,xmm0

	}
//	__m128 mul0,swp0,add0,swp1,add1;
//	 mul0 = _mm_mul_ps(v1, v2);
//	 swp0 = _mm_shuffle_ps(mul0, mul0, _MM_SHUFFLE(2, 3, 0, 1));
//	 add0 = _mm_add_ps(mul0, swp0);
//	 swp1 = _mm_shuffle_ps(add0, add0, _MM_SHUFFLE(0, 1, 2, 3));
//	 add1 = _mm_add_ps(add0, swp1);

	return v1.m128_f32[0];
}
inline void Easy_vector_copy(float vecOut[3], float vecIn[3])
{
	vecOut[0]=vecIn[0];
	vecOut[1]=vecIn[1];
	vecOut[2]=vecIn[2];
}
inline void Easy_vector_copy(__m128 * vecOut, __m128 vecIn)
{
	__asm
	{
		movaps xmm0,vecIn
		mov ecx,vecOut
		movaps [ecx],xmm0
	}
}
inline void Easy_vector_copy(float vecOut[3], __m128 vecIn)
{
	vecOut[0]=vecIn.m128_f32[0];
	vecOut[1]=vecIn.m128_f32[1];
	vecOut[2]=vecIn.m128_f32[2];
}
inline void Easy_vector_copy(__m128 * vecOut, float vecIn[3],float w=1.0f)
{
	vecOut->m128_f32[0]=vecIn[0];
	vecOut->m128_f32[1]=vecIn[1];
	vecOut->m128_f32[2]=vecIn[2];
	vecOut->m128_f32[3]=w;
}
#endif