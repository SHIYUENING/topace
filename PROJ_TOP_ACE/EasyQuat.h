#ifndef _EASYQUAT_H
#define _EASYQUAT_H
#include "Def.h"	
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <xmmintrin.h>

inline void Easy_quat_axis_angle(float c[4], float axis[3], float angle) 
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
inline void Easy_quat_axis_angle(__m128 c, const __m128 axis_angle) 
{
    double omega, s;
    double l;

	l = sqrt(axis_angle.m128_f32[0] * axis_angle.m128_f32[0] + axis_angle.m128_f32[1] * axis_angle.m128_f32[1] + axis_angle.m128_f32[2] * axis_angle.m128_f32[2]);
    if (l < 1e-5) {
		c.m128_f32[0] = c.m128_f32[1] = c.m128_f32[2] = 0.0f;
        c.m128_f32[3] = 1.0f;
    } else {
        omega = -0.5 * axis_angle.m128_f32[3];
        s = sin(omega) / l;
        c.m128_f32[0] = (float)s * axis_angle.m128_f32[0];
        c.m128_f32[1] = (float)s * axis_angle.m128_f32[1];
        c.m128_f32[2] = (float)s * axis_angle.m128_f32[2];
        c.m128_f32[3] = (float)cos(omega);
    }
}
inline void Easy_quat_normalize(float c[4]) {
    double l, m;

    l = sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2] + c[3] * c[3]);
    if (fabs(l) < LIB3DS_EPSILON) {
        c[0] = c[1] = c[2] = 0.0f;
        c[3] = 1.0f;
    } else {
        int i;
        m = 1.0f / l;
        for (i = 0; i < 4; ++i) {
            c[i] = (float)(c[i] * m);
        }
    }
}
inline void Easy_quat_normalize(__m128 * QuatOut,const __m128 QuatIn)
{
	_asm   
	{    
	movaps   xmm1,   QuatIn
	movaps   xmm0,   xmm1   
	mulps	 xmm1,   xmm1   
    
	  
	movaps   xmm2,   xmm1   
	movaps   xmm3,   xmm1   
	movaps   xmm4,   xmm1   

	shufps   xmm1,   xmm1,   0x00 
	shufps   xmm2,   xmm2,   0x55   
	shufps   xmm3,   xmm3,   0xaa   
	shufps   xmm4,   xmm4,   0xff  

	addps	 xmm1,   xmm2   
	addps    xmm1,   xmm3  
	addps    xmm1,   xmm4
    
	sqrtps   xmm1,   xmm1   
	divps    xmm0,   xmm1   

	mov		 ecx,    QuatOut
	movups	 [ecx],  xmm0  
  } 
}
#endif