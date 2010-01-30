#ifndef _EASYVECTOR_H
#define _EASYVECTOR_H
#include "Def.h"	
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <xmmintrin.h>


void inline Easy_quat_axis_angle(float c[4], float axis[3], float angle) 
{
    double omega, s;
    double l;

    l = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
    if (l < 1e-5) {
        c[0] = c[1] = c[2] = 0.0f;
        c[3] = 1.0f;
    } else {
        omega = -0.5 * angle;
        s = sin(omega) / l;
        c[0] = (float)s * axis[0];
        c[1] = (float)s * axis[1];
        c[2] = (float)s * axis[2];
        c[3] = (float)cos(omega);
    }
}
void inline Easy_vector_sub(float c[3], float a[3], float b[3]) 
{
    int i;
    for (i = 0; i < 3; ++i) {
        c[i] = a[i] - b[i];
    }
}
void inline Easy_vector_cross(float c[3], float a[3], float b[3]) {
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}
void inline Easy_vector_normalize(float c[3]) 
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
__forceinline   void   Easy_vector_normalize(__m128   vec)   
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
#endif