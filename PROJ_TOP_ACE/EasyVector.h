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
inline void Easy_vector_add(__m128 c, const __m128 a, const __m128 b) 
{
	_asm 
	{
		movups xmm0, a
		movups xmm1, b
		addps xmm0, xmm1
		movups c,xmm0
	}
}
inline void Easy_vector_sub(float c[3], float a[3], float b[3]) 
{
    int i;
    for (i = 0; i < 3; ++i) {
        c[i] = a[i] - b[i];
    }
}

inline void Easy_vector_sub(__m128 c, const __m128 a, const __m128 b) 
{
	_asm 
	{
		movups xmm0, a
		movups xmm1, b
		subps xmm0, xmm1
		movups c,xmm0
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
inline void Easy_vector_cross(__m128 OUTc,const __m128 INa,const __m128 INb) 
{
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
inline void Easy_vector_normalize(__m128 vec)   
  {   
  _asm   {    
  movaps   xmm1,   vec
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
    
  movaps   vec,   xmm0   
  }   
  } 
inline void Easy_vector_transform(float c[3], float m[4][4], float a[3]) {
    c[0] = m[0][0] * a[0] + m[1][0] * a[1] + m[2][0] * a[2] + m[3][0];
    c[1] = m[0][1] * a[0] + m[1][1] * a[1] + m[2][1] * a[2] + m[3][1];
    c[2] = m[0][2] * a[0] + m[1][2] * a[1] + m[2][2] * a[2] + m[3][2];
}
inline void Easy_vector_transform(__m128 Out, const __m128 Matrix[4], const __m128 Pos) {
	Out.m128_f32[0] = Matrix[0].m128_f32[0] * Pos.m128_f32[0] + Matrix[1].m128_f32[0] * Pos.m128_f32[1] + Matrix[2].m128_f32[0] * Pos.m128_f32[2] + Matrix[3].m128_f32[0];
	Out.m128_f32[1] = Matrix[0].m128_f32[1] * Pos.m128_f32[0] + Matrix[1].m128_f32[1] * Pos.m128_f32[1] + Matrix[2].m128_f32[1] * Pos.m128_f32[2] + Matrix[3].m128_f32[1];
	Out.m128_f32[2] = Matrix[0].m128_f32[2] * Pos.m128_f32[0] + Matrix[1].m128_f32[2] * Pos.m128_f32[1] + Matrix[2].m128_f32[2] * Pos.m128_f32[2] + Matrix[3].m128_f32[2];
}
#endif