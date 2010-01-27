#ifndef _EASYMATRIX_H
#define _EASYMATRIX_H
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>
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
#endif
