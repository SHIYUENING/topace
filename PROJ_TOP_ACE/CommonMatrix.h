//#pragma once
#ifndef _CCOMMONMATRIX_H
#define _CCOMMONMATRIX_H
#define CO_Matrix_ModelViewProj 0
#define CO_Matrix_Proj 1
#define CO_Matrix_ModelView 2
#define CO_Matrix_World 3
#define CO_Matrix_ShadowView 4
#define CO_MatrixCount 5
#include <GL/glew.h>
#include <windows.h>
class CCommonMatrix
{
public:
	CCommonMatrix(void);
	~CCommonMatrix(void);
};

#endif