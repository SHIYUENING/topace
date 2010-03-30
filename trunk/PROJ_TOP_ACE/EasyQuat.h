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
/*
#define assert_16_byte_aligned( pointer ) assert( (((UINT_PTR)(pointer))&15) == 0 ); 
 */
#define ALIGN16( x ) __declspec(align(16)) x 

#define ALIGN4_INIT1( X, I ) ALIGN16( static X[4] = { I, I, I, I } ) 
#define ALIGN4_INIT4( X, I0,I1,I2,I3 ) ALIGN16( static X[4] = { I0,I1,I2,I3 } ) 
#define R_SHUFFLE_PS( x, y, z, w ) (( (w) & 3 ) << 6 | ( (z) & 3 ) << 4 | ( (y) & 3 ) << 2 | ( (x) & 3 )) 
#define R_SHUFFLE_D R_SHUFFLE_PS


#define IEEE_SP_ZERO 0 

#define IEEE_SP_SIGN ((unsigned long) ( 1 << 31 )) 

 

//ALIGN4_INIT4( unsigned long SIMD_SP_quat2mat_x0, IEEE_SP_ZERO, IEEE_SP_SIGN, IEEE_SP_SIGN, IEEE_SP_SIGN ); 

//ALIGN4_INIT4( unsigned long SIMD_SP_quat2mat_x1, IEEE_SP_SIGN, IEEE_SP_ZERO, IEEE_SP_SIGN, IEEE_SP_SIGN ); 

//ALIGN4_INIT4( unsigned long SIMD_SP_quat2mat_x2, IEEE_SP_ZERO, IEEE_SP_SIGN, IEEE_SP_SIGN, IEEE_SP_SIGN ); 
//static const __m128 SIMD_SP_quat2mat_x0={IEEE_SP_ZERO,IEEE_SP_SIGN,IEEE_SP_SIGN,IEEE_SP_SIGN};
//static const __m128 SIMD_SP_quat2mat_x1={IEEE_SP_SIGN,IEEE_SP_ZERO,IEEE_SP_SIGN,IEEE_SP_SIGN};
//static const __m128 SIMD_SP_quat2mat_x2={IEEE_SP_ZERO,IEEE_SP_SIGN,IEEE_SP_SIGN,IEEE_SP_SIGN};
__declspec(align(16)) static const unsigned long SIMD_SP_quat2mat_x0[4] ={IEEE_SP_ZERO, IEEE_SP_SIGN, IEEE_SP_SIGN, IEEE_SP_SIGN};
__declspec(align(16)) static const unsigned long SIMD_SP_quat2mat_x1[4] ={IEEE_SP_SIGN, IEEE_SP_SIGN, IEEE_SP_SIGN, IEEE_SP_SIGN};
__declspec(align(16)) static const unsigned long SIMD_SP_quat2mat_x2[4] ={IEEE_SP_ZERO, IEEE_SP_SIGN, IEEE_SP_SIGN, IEEE_SP_SIGN};
static const __m128 SIMD_SP_one = _mm_set_ps(0.0f,0.0f,0.0f,1.0f);
static const __m128 SIMD_SP_one1 = _mm_set_ps(1.0f,1.0f,1.0f,1.0f);
static const __m128 SIMD_SP_one3 = _mm_set_ps(1.0f,0.0f,0.0f,0.0f);
inline void Easy_quat_to_matrix(__m128 MatrixOut[4],const __m128 QuatIn)
{
	_asm   
	{
		PUSHAD
			mov eax,MatrixOut
			movaps xmm0,QuatIn
			movaps xmm6,SIMD_SP_one3

			movaps xmm1, xmm0 // xmm1 = x, y, z, w 
			addps xmm1, xmm1 // xmm1 = x2, y2, z2, w2 

			pshufd xmm2, xmm0, R_SHUFFLE_D( 1, 0, 0, 1 ) // xmm2 = y, x, x, y 
			pshufd xmm3, xmm1, R_SHUFFLE_D( 1, 1, 2, 2 ) // xmm3 = y2, y2, z2, z2 
			mulps xmm2, xmm3 // xmm2 = yy2, xy2, xz2, yz2 

			pshufd xmm4, xmm0, R_SHUFFLE_D( 2, 3, 3, 3 ) // xmm4 = z, w, w, w 
			pshufd xmm5, xmm1, R_SHUFFLE_D( 2, 2, 1, 0 ) // xmm5 = z2, z2, y2, x2 
			mulps xmm4, xmm5 // xmm4 = zz2, wz2, wy2, wx2 

			mulss xmm0, xmm1 // xmm0 = xx2, y2, z2, w2 

			
 // calculate the last two elements of the third row 

			movss xmm7, SIMD_SP_one1 // xmm7 = 1, 0, 0, 0 
			subss xmm7, xmm0 // xmm7 = -xx2+1, 0, 0, 0 
			subss xmm7, xmm2 // xmm7 = -xx2-yy2+1, 0, 0, 0 
			shufps xmm7, xmm6, R_SHUFFLE_PS( 0, 1, 2, 3 ) // xmm7 = -xx2-yy2+1, 0, t.z, t.w 

 // calcluate first row 

			xorps xmm2, SIMD_SP_quat2mat_x0 // xmm2 = yy2, -xy2, -xz2, -yz2 
			xorps xmm4, SIMD_SP_quat2mat_x1 // xmm4 = -zz2, wz2, -wy2, -wx2 
			addss xmm4, SIMD_SP_one1 // xmm4 = -zz2+1, wz2, -wy2, -wx2 
			movaps xmm3, xmm4 // xmm3 = -zz2+1, wz2, -wy2, -wx2 
			subps xmm3, xmm2 // xmm3 = -yy2-zz2+1, xy2+wz2, xz2-wy2, yz2-wx2 
			movaps [eax+0*16+0*4], xmm3 // row0 = -yy2-zz2+1, xy2+wz2, xz2-wy2, yz2-wx2 
			movss [eax+0*16+3*4], xmm6 // row0 = -yy2-zz2+1, xy2+wz2, xz2-wy2, t.x 

 // calculate second row 

			movss xmm2, xmm0 // xmm2 = xx2, -xy2, -xz2, -yz2 
			xorps xmm4, SIMD_SP_quat2mat_x2 // xmm4 = -zz2+1, -wz2, wy2, wx2 
			subps xmm4, xmm2 // xmm4 = -xx2-zz2+1, xy2-wz2, xz2+wy2, yz2+wx2 
			shufps xmm6, xmm6, R_SHUFFLE_PS( 1, 2, 3, 0 ) // xmm6 = t.y, t.z, t.w, t.x 
			shufps xmm4, xmm4, R_SHUFFLE_PS( 1, 0, 3, 2 ) // xmm4 = xy2-wz2, -xx2-zz2+1, yz2+wx2, xz2+wy2 
			movaps [eax+1*16+0*4], xmm4 // row1 = xy2-wz2, -xx2-zz2+1, yz2+wx2, xz2+wy2 
			movss [eax+1*16+3*4], xmm6 // row1 = xy2-wz2, -xx2-zz2+1, yz2+wx2, t.y 

 // calculate third row 

			movhlps xmm3, xmm4 // xmm3 = yz2+wx2, xz2+wy2, xz2-wy2, yz2-wx2 
			shufps xmm3, xmm7, R_SHUFFLE_PS( 1, 3, 0, 2 ) // xmm3 = xz2+wy2, yz2-wx2, -xx2-yy2+1, t.z 
			movaps [eax+2*16+0*4], xmm3 // row2 = xz2+wy2, yz2-wx2, -xx2-yy2+1, t.z 
			movaps xmm6,SIMD_SP_one3
			movaps [eax+3*16+0*4], xmm6

		POPAD
	}
}
#endif