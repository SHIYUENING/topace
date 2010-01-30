#ifndef _EASYMATRIX_H
#define _EASYMATRIX_H
#include "Def.h"	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <xmmintrin.h>
#include "EasyVector.h"
#include "EasyQuat.h"
static const float IdentityMatrix[4][4]={1.0f,0.0f,0.0f,0.0f,
									0.0f,1.0f,0.0f,0.0f,
									0.0f,0.0f,1.0f,0.0f,
									0.0f,0.0f,0.0f,1.0f};
inline void Easy_matrix_identity(float Matrix[4][4])
{
	memcpy(Matrix,IdentityMatrix,4*4*sizeof(float));
}
inline void Easy_matrix_translate(float Matrix[4][4], float x, float y, float z)
{
	Matrix[3][0] += Matrix[0][0] * x + Matrix[1][0] * y + Matrix[2][0] * z;
	Matrix[3][1] += Matrix[0][1] * x + Matrix[1][1] * y + Matrix[2][1] * z;
	Matrix[3][2] += Matrix[0][2] * x + Matrix[1][2] * y + Matrix[2][2] * z;
}
inline void Easy_matrix_mult(float Matrix[4][4], float a[4][4], float b[4][4]) {

    float tmp[4][4];
    int i, j, k;
    float ab;

    memcpy(tmp, a, 16 * sizeof(float));
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            ab = 0.0f;
            for (k = 0; k < 4; k++) ab += tmp[k][i] * b[j][k];
            Matrix[j][i] = ab;
        }
    }
}
inline void Easy_matrix_mult(float * Matrix, const float * a, const float * b) 
{
#ifdef USE_SSE
	int				i;
	__m128			_t0, _t1, _t2, _t3, _t4, _t5, _t6, _t7;

	_t4 = _mm_loadu_ps(&a[0]);
	_t5 = _mm_loadu_ps(&a[4]);
	_t6 = _mm_loadu_ps(&a[8]);
	_t7 = _mm_loadu_ps(&a[12]);

	for(i = 0; i < 4; i++)
	{
		_t0 = _mm_load1_ps(&b[i * 4 + 0]);
		_t0 = _mm_mul_ps(_t4, _t0);

		_t1 = _mm_load1_ps(&b[i * 4 + 1]);
		_t1 = _mm_mul_ps(_t5, _t1);

		_t2 = _mm_load1_ps(&b[i * 4 + 2]);
		_t2 = _mm_mul_ps(_t6, _t2);

		_t3 = _mm_load1_ps(&b[i * 4 + 3]);
		_t3 = _mm_mul_ps(_t7, _t3);

		_t1 = _mm_add_ps(_t0, _t1);
		_t2 = _mm_add_ps(_t1, _t2);
		_t3 = _mm_add_ps(_t2, _t3);

		_mm_storeu_ps(&Matrix[i * 4], _t3);
	}

#else
    float tmp[16];
    int j;
    memcpy(tmp, a, 16 * sizeof(float));
    for (j = 0; j < 4; j++) {
		Matrix[j*4+0] = tmp[0] * b[j*4+0]+tmp[4] * b[j*4+1]+tmp[8] * b[j*4+2]+tmp[12] * b[j*4+3];
		Matrix[j*4+1] = tmp[1] * b[j*4+0]+tmp[5] * b[j*4+1]+tmp[9] * b[j*4+2]+tmp[13] * b[j*4+3];
		Matrix[j*4+2] = tmp[2] * b[j*4+0]+tmp[6] * b[j*4+1]+tmp[10] * b[j*4+2]+tmp[14] * b[j*4+3];
		Matrix[j*4+3] = tmp[3] * b[j*4+0]+tmp[7] * b[j*4+1]+tmp[11] * b[j*4+2]+tmp[15] * b[j*4+3];
    }
#endif

}

inline void Easy_matrix_mult(__m128 Matrix[4], const __m128 a, const __m128 b)
{
}
inline void Easy_matrix_rotate_quat(float m[4][4], float q[4]) {
    float s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz, l;
    float R[4][4];

    l = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
    if (fabs(l) < 1e-5) {
        s = 1.0f;
    } else {
        s = 2.0f / l;
    }

    xs = q[0] * s;
    ys = q[1] * s;
    zs = q[2] * s;
    wx = q[3] * xs;
    wy = q[3] * ys;
    wz = q[3] * zs;
    xx = q[0] * xs;
    xy = q[0] * ys;
    xz = q[0] * zs;
    yy = q[1] * ys;
    yz = q[1] * zs;
    zz = q[2] * zs;

    R[0][0] = 1.0f - (yy + zz);
    R[1][0] = xy - wz;
    R[2][0] = xz + wy;
    R[0][1] = xy + wz;
    R[1][1] = 1.0f - (xx + zz);
    R[2][1] = yz - wx;
    R[0][2] = xz - wy;
    R[1][2] = yz + wx;
    R[2][2] = 1.0f - (xx + yy);
    R[3][0] = R[3][1] = R[3][2] = R[0][3] = R[1][3] = R[2][3] = 0.0f;
    R[3][3] = 1.0f;

    //Easy_matrix_mult(m, m, R);
	Easy_matrix_mult(&m[0][0],&m[0][0],&R[0][0]);
}
inline void Easy_matrix_rotate(float m[4][4], float angle, float ax, float ay, float az) {
    float q[4];
	float axis[3]={ax,ay,az};

   // lib3ds_vector_make(axis, ax, ay, az);
    Easy_quat_axis_angle(q, axis, angle);
    Easy_matrix_rotate_quat(m, q);
}
inline void Easy_matrix_scale(float m[4][4], float x, float y, float z) {
    int i;

    for (i = 0; i < 4; i++) {
        m[0][i] *= x;
        m[1][i] *= y;
        m[2][i] *= z;
    }
}
inline void Easy_matrix_copy(__m128 dest[4], __m128 src[4]) {
    memcpy(dest, src, 16 * sizeof(float));
}
inline void Easy_matrix_copy(float dest[4][4], float src[4][4]) {
    memcpy(dest, src, 16 * sizeof(float));
}
//http://www.devmaster.net/forums/showthread.php?t=14569
static const __m128 one = _mm_set_ps1(1.0f);
inline __m128 _mm_dot_ps(__m128 v1, __m128 v2)
{
	__m128 mul0,swp0,add0,swp1,add1;
	 mul0 = _mm_mul_ps(v1, v2);
	 swp0 = _mm_shuffle_ps(mul0, mul0, _MM_SHUFFLE(2, 3, 0, 1));
	 add0 = _mm_add_ps(mul0, swp0);
	 swp1 = _mm_shuffle_ps(add0, add0, _MM_SHUFFLE(0, 1, 2, 3));
	 add1 = _mm_add_ps(add0, swp1);
	return add1;
}
inline void _mm_mul_ps(__m128 in1[4], __m128 in2[4], __m128 out[4])
{
	{
		__m128 e0 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[0] = a2;
	}

	{
		__m128 e0 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[1] = a2;
	}

	{
		__m128 e0 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[2] = a2;
	}

	{
		//(__m128&)_mm_shuffle_epi32(__m128i&)in2[0], _MM_SHUFFLE(3, 3, 3, 3))
		__m128 e0 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[3] = a2;
	}
}
inline void _mm_inverse_ps(__m128 const in[4], __m128 out[4])
{
	__m128 Fac0;
	{
		//	valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		//	valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		//	valType SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		//	valType SubFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		__m128 Swp0a = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(3, 3, 3, 3));
		__m128 Swp0b = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(2, 2, 2, 2));

		__m128 Swp00 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac0 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 Fac1;
	{
		//	valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		//	valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		//	valType SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		//	valType SubFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		__m128 Swp0a = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(3, 3, 3, 3));
		__m128 Swp0b = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(1, 1, 1, 1));

		__m128 Swp00 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac1 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}


	__m128 Fac2;
	{
		//	valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		//	valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		//	valType SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		//	valType SubFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		__m128 Swp0a = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Swp0b = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(1, 1, 1, 1));

		__m128 Swp00 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(2, 2, 2, 2));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac2 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 Fac3;
	{
		//	valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		//	valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		//	valType SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		//	valType SubFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		__m128 Swp0a = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(3, 3, 3, 3));
		__m128 Swp0b = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(0, 0, 0, 0));

		__m128 Swp00 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac3 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 Fac4;
	{
		//	valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		//	valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		//	valType SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		//	valType SubFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		__m128 Swp0a = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Swp0b = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(0, 0, 0, 0));

		__m128 Swp00 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(2, 2, 2, 2));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac4 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 Fac5;
	{
		//	valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		//	valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		//	valType SubFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		//	valType SubFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		__m128 Swp0a = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Swp0b = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(0, 0, 0, 0));

		__m128 Swp00 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(1, 1, 1, 1));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac5 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 SignA = _mm_set_ps( 1.0f,-1.0f, 1.0f,-1.0f);
	__m128 SignB = _mm_set_ps(-1.0f, 1.0f,-1.0f, 1.0f);

	// m[1][0]
	// m[0][0]
	// m[0][0]
	// m[0][0]
	__m128 Temp0 = _mm_shuffle_ps(in[1], in[0], _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Vec0 = _mm_shuffle_ps(Temp0, Temp0, _MM_SHUFFLE(2, 2, 2, 0));

	// m[1][1]
	// m[0][1]
	// m[0][1]
	// m[0][1]
	__m128 Temp1 = _mm_shuffle_ps(in[1], in[0], _MM_SHUFFLE(1, 1, 1, 1));
	__m128 Vec1 = _mm_shuffle_ps(Temp1, Temp1, _MM_SHUFFLE(2, 2, 2, 0));

	// m[1][2]
	// m[0][2]
	// m[0][2]
	// m[0][2]
	__m128 Temp2 = _mm_shuffle_ps(in[1], in[0], _MM_SHUFFLE(2, 2, 2, 2));
	__m128 Vec2 = _mm_shuffle_ps(Temp2, Temp2, _MM_SHUFFLE(2, 2, 2, 0));

	// m[1][3]
	// m[0][3]
	// m[0][3]
	// m[0][3]
	__m128 Temp3 = _mm_shuffle_ps(in[1], in[0], _MM_SHUFFLE(3, 3, 3, 3));
	__m128 Vec3 = _mm_shuffle_ps(Temp3, Temp3, _MM_SHUFFLE(2, 2, 2, 0));

	// col0
	// + (Vec1[0] * Fac0[0] - Vec2[0] * Fac1[0] + Vec3[0] * Fac2[0]),
	// - (Vec1[1] * Fac0[1] - Vec2[1] * Fac1[1] + Vec3[1] * Fac2[1]),
	// + (Vec1[2] * Fac0[2] - Vec2[2] * Fac1[2] + Vec3[2] * Fac2[2]),
	// - (Vec1[3] * Fac0[3] - Vec2[3] * Fac1[3] + Vec3[3] * Fac2[3]),
	__m128 Mul00 = _mm_mul_ps(Vec1, Fac0);
	__m128 Mul01 = _mm_mul_ps(Vec2, Fac1);
	__m128 Mul02 = _mm_mul_ps(Vec3, Fac2);
	__m128 Sub00 = _mm_sub_ps(Mul00, Mul01);
	__m128 Add00 = _mm_add_ps(Sub00, Mul02);
	__m128 Inv0 = _mm_mul_ps(SignB, Add00);

	// col1
	// - (Vec0[0] * Fac0[0] - Vec2[0] * Fac3[0] + Vec3[0] * Fac4[0]),
	// + (Vec0[0] * Fac0[1] - Vec2[1] * Fac3[1] + Vec3[1] * Fac4[1]),
	// - (Vec0[0] * Fac0[2] - Vec2[2] * Fac3[2] + Vec3[2] * Fac4[2]),
	// + (Vec0[0] * Fac0[3] - Vec2[3] * Fac3[3] + Vec3[3] * Fac4[3]),
	__m128 Mul03 = _mm_mul_ps(Vec0, Fac0);
	__m128 Mul04 = _mm_mul_ps(Vec2, Fac3);
	__m128 Mul05 = _mm_mul_ps(Vec3, Fac4);
	__m128 Sub01 = _mm_sub_ps(Mul03, Mul04);
	__m128 Add01 = _mm_add_ps(Sub01, Mul05);
	__m128 Inv1 = _mm_mul_ps(SignA, Add01);

	// col2
	// + (Vec0[0] * Fac1[0] - Vec1[0] * Fac3[0] + Vec3[0] * Fac5[0]),
	// - (Vec0[0] * Fac1[1] - Vec1[1] * Fac3[1] + Vec3[1] * Fac5[1]),
	// + (Vec0[0] * Fac1[2] - Vec1[2] * Fac3[2] + Vec3[2] * Fac5[2]),
	// - (Vec0[0] * Fac1[3] - Vec1[3] * Fac3[3] + Vec3[3] * Fac5[3]),
	__m128 Mul06 = _mm_mul_ps(Vec0, Fac1);
	__m128 Mul07 = _mm_mul_ps(Vec1, Fac3);
	__m128 Mul08 = _mm_mul_ps(Vec3, Fac5);
	__m128 Sub02 = _mm_sub_ps(Mul06, Mul07);
	__m128 Add02 = _mm_add_ps(Sub02, Mul08);
	__m128 Inv2 = _mm_mul_ps(SignB, Add02);

	// col3
	// - (Vec1[0] * Fac2[0] - Vec1[0] * Fac4[0] + Vec2[0] * Fac5[0]),
	// + (Vec1[0] * Fac2[1] - Vec1[1] * Fac4[1] + Vec2[1] * Fac5[1]),
	// - (Vec1[0] * Fac2[2] - Vec1[2] * Fac4[2] + Vec2[2] * Fac5[2]),
	// + (Vec1[0] * Fac2[3] - Vec1[3] * Fac4[3] + Vec2[3] * Fac5[3]));
	__m128 Mul09 = _mm_mul_ps(Vec0, Fac2);
	__m128 Mul10 = _mm_mul_ps(Vec1, Fac4);
	__m128 Mul11 = _mm_mul_ps(Vec2, Fac5);
	__m128 Sub03 = _mm_sub_ps(Mul09, Mul10);
	__m128 Add03 = _mm_add_ps(Sub03, Mul11);
	__m128 Inv3 = _mm_mul_ps(SignA, Add03);

	__m128 Row0 = _mm_shuffle_ps(Inv0, Inv1, _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Row1 = _mm_shuffle_ps(Inv2, Inv3, _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Row2 = _mm_shuffle_ps(Row0, Row1, _MM_SHUFFLE(2, 0, 2, 0));

	//	valType Determinant = m[0][0] * Inverse[0][0] 
	//						+ m[0][1] * Inverse[1][0] 
	//						+ m[0][2] * Inverse[2][0] 
	//						+ m[0][3] * Inverse[3][0];
	__m128 Det0 = _mm_dot_ps(in[0], Row2);
	__m128 Rcp0 = _mm_div_ps(one, Det0);
	//__m128 Rcp0 = _mm_rcp_ps(Det0);

	//	Inverse /= Determinant;
	out[0] = _mm_mul_ps(Inv0, Rcp0);
	out[1] = _mm_mul_ps(Inv1, Rcp0);
	out[2] = _mm_mul_ps(Inv2, Rcp0);
	out[3] = _mm_mul_ps(Inv3, Rcp0);
}

inline void Easy_matrix_inv(float m[4][4]) 
{
#ifdef USE_SSE
	__m128 matrixIN[4],matrixOUT[4];
	matrixIN[0]=_mm_loadu_ps(&m[0][0]);
	matrixIN[1]=_mm_loadu_ps(&m[1][0]);
	matrixIN[2]=_mm_loadu_ps(&m[2][0]);
	matrixIN[3]=_mm_loadu_ps(&m[3][0]);
	_mm_inverse_ps(matrixIN,matrixOUT);
	_mm_storeu_ps(&m[0][0],matrixOUT[0]);
	_mm_storeu_ps(&m[1][0],matrixOUT[1]);
	_mm_storeu_ps(&m[2][0],matrixOUT[2]);
	_mm_storeu_ps(&m[3][0],matrixOUT[3]);
#else
    int i, j, k;
    int pvt_i[4], pvt_j[4];            /* Locations of pivot elements */
    float pvt_val;               /* Value of current pivot element */
    float hold;                  /* Temporary storage */
    float determinat;

    determinat = 1.0f;
    for (k = 0; k < 4; k++)  {
        /* Locate k'th pivot element */
        pvt_val = m[k][k];          /* Initialize for search */
        pvt_i[k] = k;
        pvt_j[k] = k;
        for (i = k; i < 4; i++) {
            for (j = k; j < 4; j++) {
                if (fabs(m[i][j]) > fabs(pvt_val)) {
                    pvt_i[k] = i;
                    pvt_j[k] = j;
                    pvt_val = m[i][j];
                }
            }
        }

        /* Product of pivots, gives determinant when finished */
        determinat *= pvt_val;
        if (fabs(determinat) < 1e-5) {
            return;  /* Matrix is singular (zero determinant) */
        }

        /* "Interchange" rows (with sign change stuff) */
        i = pvt_i[k];
        if (i != k) {             /* If rows are different */
            for (j = 0; j < 4; j++) {
                hold = -m[k][j];
                m[k][j] = m[i][j];
                m[i][j] = hold;
            }
        }

        /* "Interchange" columns */
        j = pvt_j[k];
        if (j != k) {            /* If columns are different */
            for (i = 0; i < 4; i++) {
                hold = -m[i][k];
                m[i][k] = m[i][j];
                m[i][j] = hold;
            }
        }

        /* Divide column by minus pivot value */
        for (i = 0; i < 4; i++) {
            if (i != k) m[i][k] /= (-pvt_val) ;
        }

        /* Reduce the matrix */
        for (i = 0; i < 4; i++) {
            hold = m[i][k];
            for (j = 0; j < 4; j++) {
                if (i != k && j != k) m[i][j] += hold * m[k][j];
            }
        }

        /* Divide row by pivot */
        for (j = 0; j < 4; j++) {
            if (j != k) m[k][j] /= pvt_val;
        }

        /* Replace pivot by reciprocal (at last we can touch it). */
        m[k][k] = 1.0f / pvt_val;
    }

    /* That was most of the work, one final pass of row/column interchange */
    /* to finish */
    for (k = 4 - 2; k >= 0; k--) { /* Don't need to work with 1 by 1 corner*/
        i = pvt_j[k];          /* Rows to swap correspond to pivot COLUMN */
        if (i != k) {          /* If rows are different */
            for (j = 0; j < 4; j++) {
                hold = m[k][j];
                m[k][j] = -m[i][j];
                m[i][j] = hold;
            }
        }

        j = pvt_i[k];         /* Columns to swap correspond to pivot ROW */
        if (j != k)           /* If columns are different */
            for (i = 0; i < 4; i++) {
                hold = m[i][k];
                m[i][k] = -m[i][j];
                m[i][j] = hold;
            }
    }
#endif
}

inline void Easy_matrix_camera(float matrix[4][4], float pos[3], float tgt[3], float roll) {
    float M[4][4];
    float x[3], y[3], z[3];

	y[0]=tgt[0]-pos[0];
	y[1]=tgt[1]-pos[1];
	y[2]=tgt[2]-pos[2];
    //Easy_vector_sub(y, tgt, pos);
    Easy_vector_normalize(y);

    if (y[0] != 0. || y[1] != 0) {
        z[0] = 0;
        z[1] = 0;
        z[2] = 1.0;
    } else { /* Special case:  looking straight up or down z axis */
        z[0] = -1.0;
        z[1] = 0;
        z[2] = 0;
    }

    Easy_vector_cross(x, y, z);
    Easy_vector_cross(z, x, y);
    Easy_vector_normalize(x);
    Easy_vector_normalize(z);

    Easy_matrix_identity(M);
    M[0][0] = x[0];
    M[1][0] = x[1];
    M[2][0] = x[2];
    M[0][1] = y[0];
    M[1][1] = y[1];
    M[2][1] = y[2];
    M[0][2] = z[0];
    M[1][2] = z[1];
    M[2][2] = z[2];

    Easy_matrix_identity(matrix);
    Easy_matrix_rotate(matrix, roll, 0, 1, 0);
    Easy_matrix_mult(&matrix[0][0], &matrix[0][0], &M[0][0]);
    Easy_matrix_translate(matrix, -pos[0], -pos[1], -pos[2]);
}

#endif
