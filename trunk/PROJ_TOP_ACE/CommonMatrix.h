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
struct _CO_Matrix_LinkList{
	GLdouble Matrix[16];
	_CO_Matrix_LinkList * pLastMatrix;
};
class CCommonMatrix
{
public:
	CCommonMatrix(void);
	~CCommonMatrix(void);
	_CO_Matrix_LinkList * LinkList;
	GLdouble MatrixTMP[16];
	unsigned int List_Count;
	void Load(GLdouble * MatrixD);
	void Identity(void);
	void Push(void);
	void Pop(void);
	void Clear(void);
	void Mult(GLfloat * Matrix);
	void Get(GLfloat * Matrix);
};
void CO_IdentityMatrixD(GLdouble * MatrixD);
#endif