#ifndef _EASYMATRIX_H
#define _EASYMATRIX_H
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>
#include <math.h>
#include <windows.h>
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

    Easy_matrix_mult(m, m, R);
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
