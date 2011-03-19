//#pragma once
#ifndef _CCOMMONMATRIX_H
#define _CCOMMONMATRIX_H
#define CO_Matrix_ModelViewProj 0
#define CO_Matrix_Proj 1
#define CO_Matrix_ModelView 2
#define CO_Matrix_World 3
#define CO_Matrix_ShadowViewProj 4
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
	GLfloat MatrixTMPF[16];
	unsigned int List_Count;
	GLint GLSLLoc;
	void LoadF(GLfloat * Matrix);
	void LoadD(GLdouble * Matrix);
	void Identity(void);
	void Push(void);
	void Pop(void);
	void Clear(void);
	void MultF(GLfloat * Matrix);
	void MultD(GLdouble * Matrix);
	void GetF(GLfloat * Matrix);
	void GetD(GLdouble * Matrix);
	void SetMatrixToGlsl(void);
	void PerspectiveProjectionFov(GLdouble fovyInDegrees, GLdouble aspectRatio,
                      GLdouble znear, GLdouble zfar);
	void OrthogonalProjection(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble n, GLdouble f);
};
extern CCommonMatrix CommonMatrixs[CO_MatrixCount];
/*
static int text;
void CO_Matrix_LoadF(GLfloat * Matrix,unsigned int CO_Matrix_ID);
void CO_Matrix_LoadD(GLdouble * Matrix,unsigned int CO_Matrix_ID);
void CO_Matrix_Identity(unsigned int CO_Matrix_ID);
void CO_Matrix_Push(unsigned int CO_Matrix_ID);
void CO_Matrix_Pop(unsigned int CO_Matrix_ID);
void CO_Matrix_Clear(unsigned int CO_Matrix_ID);
void CO_Matrix_MultF(GLfloat * Matrix,unsigned int CO_Matrix_ID);
void CO_Matrix_MultD(GLdouble * Matrix,unsigned int CO_Matrix_ID);
void CO_Matrix_GetF(GLfloat * Matrix,unsigned int CO_Matrix_ID);
void CO_Matrix_GetD(GLdouble * Matrix,unsigned int CO_Matrix_ID);*/
#endif