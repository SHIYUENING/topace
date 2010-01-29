#ifndef _EASYMATRIX_H
#define _EASYMATRIX_H
#define USE_SSE 1
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <xmmintrin.h>
const float IdentityMatrix[4][4]={1.0f,0.0f,0.0f,0.0f,
									0.0f,1.0f,0.0f,0.0f,
									0.0f,0.0f,1.0f,0.0f,
									0.0f,0.0f,0.0f,1.0f};
void inline Easy_matrix_identity(float Matrix[4][4])
{
	memcpy(Matrix,IdentityMatrix,4*4*sizeof(float));
}
void inline Easy_matrix_translate(float Matrix[4][4], float x, float y, float z)
{
	Matrix[3][0] += Matrix[0][0] * x + Matrix[1][0] * y + Matrix[2][0] * z;
	Matrix[3][1] += Matrix[0][1] * x + Matrix[1][1] * y + Matrix[2][1] * z;
	Matrix[3][2] += Matrix[0][2] * x + Matrix[1][2] * y + Matrix[2][2] * z;
}
void inline Easy_matrix_mult(float Matrix[4][4], float a[4][4], float b[4][4]) {

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
void inline Easy_matrix_mult(float * Matrix, const float * a, const float * b) 
{
#if USE_SSE
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
        out[ 0] = b[ 0]*a[ 0] + b[ 1]*a[ 4] + b[ 2]*a[ 8] + b[ 3]*a[12];
        out[ 1] = b[ 0]*a[ 1] + b[ 1]*a[ 5] + b[ 2]*a[ 9] + b[ 3]*a[13];
		out[ 2] = b[ 0]*a[ 2] + b[ 1]*a[ 6] + b[ 2]*a[10] + b[ 3]*a[14];
		out[ 3] = b[ 0]*a[ 3] + b[ 1]*a[ 7] + b[ 2]*a[11] + b[ 3]*a[15];

		out[ 4] = b[ 4]*a[ 0] + b[ 5]*a[ 4] + b[ 6]*a[ 8] + b[ 7]*a[12];
		out[ 5] = b[ 4]*a[ 1] + b[ 5]*a[ 5] + b[ 6]*a[ 9] + b[ 7]*a[13];
		out[ 6] = b[ 4]*a[ 2] + b[ 5]*a[ 6] + b[ 6]*a[10] + b[ 7]*a[14];
		out[ 7] = b[ 4]*a[ 3] + b[ 5]*a[ 7] + b[ 6]*a[11] + b[ 7]*a[15];

		out[ 8] = b[ 8]*a[ 0] + b[ 9]*a[ 4] + b[10]*a[ 8] + b[11]*a[12];
		out[ 9] = b[ 8]*a[ 1] + b[ 9]*a[ 5] + b[10]*a[ 9] + b[11]*a[13];
		out[10] = b[ 8]*a[ 2] + b[ 9]*a[ 6] + b[10]*a[10] + b[11]*a[14];
		out[11] = b[ 8]*a[ 3] + b[ 9]*a[ 7] + b[10]*a[11] + b[11]*a[15];

		out[12] = b[12]*a[ 0] + b[13]*a[ 4] + b[14]*a[ 8] + b[15]*a[12];
		out[13] = b[12]*a[ 1] + b[13]*a[ 5] + b[14]*a[ 9] + b[15]*a[13];
		out[14] = b[12]*a[ 2] + b[13]*a[ 6] + b[14]*a[10] + b[15]*a[14];
		out[15] = b[12]*a[ 3] + b[13]*a[ 7] + b[14]*a[11] + b[15]*a[15];
#endif

}
void inline Easy_matrix_rotate_quat(float m[4][4], float q[4]) {
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
void inline Easy_matrix_scale(float m[4][4], float x, float y, float z) {
    int i;

    for (i = 0; i < 4; i++) {
        m[0][i] *= x;
        m[1][i] *= y;
        m[2][i] *= z;
    }
}
void inline Easy_matrix_copy(float dest[4][4], float src[4][4]) {
    memcpy(dest, src, 16 * sizeof(float));
}
#endif
