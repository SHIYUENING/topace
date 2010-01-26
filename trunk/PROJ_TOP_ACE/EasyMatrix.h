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
#endif
