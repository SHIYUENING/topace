#include "CommonMatrix.h"
static const GLdouble IdentityMatrixD[16]={1.0,0.0,0.0,0.0,
										   0.0,1.0,0.0,0.0,
										   0.0,0.0,1.0,0.0,
										   0.0,0.0,0.0,1.0};
static CCommonMatrix CommonMatrixs[CO_MatrixCount];

CCommonMatrix::CCommonMatrix(void)
	:List_Count(0)
{
	LinkList=new _CO_Matrix_LinkList;
	LinkList->pLastMatrix=NULL;
	this->Identity();
}

CCommonMatrix::~CCommonMatrix(void)
{
	this->Clear();
	delete LinkList;
}

void CCommonMatrix::LoadD(GLdouble * Matrix)
{
	if(Matrix) memcpy(LinkList->Matrix,Matrix,16*sizeof(GLdouble));
}

void CCommonMatrix::LoadF(GLfloat * Matrix)
{
	if(Matrix) for (int i=0;i<16;i++) LinkList->Matrix[i]=Matrix[i];
}

void CCommonMatrix::Identity(void)
{
	memcpy(LinkList->Matrix, IdentityMatrixD, 16 * sizeof(GLdouble));
}

void CCommonMatrix::Push(void)
{
	_CO_Matrix_LinkList * CO_Matrix_LinkList_TMP=new _CO_Matrix_LinkList;
	CO_Matrix_LinkList_TMP->pLastMatrix=LinkList;
	LinkList=CO_Matrix_LinkList_TMP;
	memcpy(LinkList->Matrix, LinkList->pLastMatrix->Matrix, 16 * sizeof(GLdouble));
	List_Count++;
}

void CCommonMatrix::Pop(void)
{
	if(!LinkList->pLastMatrix) return;
	_CO_Matrix_LinkList * CO_Matrix_LinkList_TMP=LinkList;
	LinkList=LinkList->pLastMatrix;
	delete CO_Matrix_LinkList_TMP;
	List_Count--;
}

void CCommonMatrix::Clear(void)
{
	while(LinkList->pLastMatrix)
	{
		this->Push();
		List_Count--;
	}
	this->Identity();
}

void CCommonMatrix::MultF(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) MatrixTMP[i]=Matrix[i];

	GLdouble tmp[16];
    int i, j, k;
    GLdouble ab;

	memcpy(tmp, LinkList->Matrix, 16 * sizeof(GLdouble));
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            ab = 0.0f;
            for (k = 0; k < 4; k++) ab += tmp[k*4+i] * MatrixTMP[j*4+k];
            LinkList->Matrix[j*4+i] = ab;
        }
    }
}

void CCommonMatrix::MultD(GLdouble * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) MatrixTMP[i]=Matrix[i];

	GLdouble tmp[16];
    int i, j, k;
    GLdouble ab;

	memcpy(tmp, LinkList->Matrix, 16 * sizeof(GLdouble));
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            ab = 0.0f;
            for (k = 0; k < 4; k++) ab += tmp[k*4+i] * MatrixTMP[j*4+k];
            LinkList->Matrix[j*4+i] = ab;
        }
    }
}

void CCommonMatrix::GetF(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) Matrix[i]=GLfloat(LinkList->Matrix[i]);
}

void CCommonMatrix::GetD(GLdouble * Matrix)
{
	if(Matrix) memcpy(Matrix,LinkList->Matrix,16*sizeof(GLdouble));
}

void CO_Matrix_LoadF(GLfloat * Matrix,unsigned int CO_Matrix_ID)
{
	if(CO_Matrix_ID>=CO_MatrixCount) return;
	CommonMatrixs[CO_Matrix_ID].LoadF(Matrix);
}

void CO_Matrix_LoadD(GLdouble * Matrix,unsigned int CO_Matrix_ID)
{
	if(CO_Matrix_ID>=CO_MatrixCount) return;
	CommonMatrixs[CO_Matrix_ID].LoadD(Matrix);
}

void CO_Matrix_Identity(unsigned int CO_Matrix_ID)
{
	if(CO_Matrix_ID>=CO_MatrixCount) return;
	CommonMatrixs[CO_Matrix_ID].Identity();
}

void CO_Matrix_Push(unsigned int CO_Matrix_ID)
{
	if(CO_Matrix_ID>=CO_MatrixCount) return;
	CommonMatrixs[CO_Matrix_ID].Push();
}

void CO_Matrix_Pop(unsigned int CO_Matrix_ID)
{
	if(CO_Matrix_ID>=CO_MatrixCount) return;
	CommonMatrixs[CO_Matrix_ID].Pop();
}

void CO_Matrix_Clear(unsigned int CO_Matrix_ID)
{
	if(CO_Matrix_ID>=CO_MatrixCount) return;
	CommonMatrixs[CO_Matrix_ID].Clear();
}

void CO_Matrix_MultF(GLfloat * Matrix,unsigned int CO_Matrix_ID)
{
	if(CO_Matrix_ID>=CO_MatrixCount) return;
	CommonMatrixs[CO_Matrix_ID].MultF(Matrix);
}

void CO_Matrix_MultD(GLdouble * Matrix,unsigned int CO_Matrix_ID)
{
	if(CO_Matrix_ID>=CO_MatrixCount) return;
	CommonMatrixs[CO_Matrix_ID].MultD(Matrix);
}

void CO_Matrix_GetF(GLfloat * Matrix,unsigned int CO_Matrix_ID)
{
	if(CO_Matrix_ID>=CO_MatrixCount) return;
	CommonMatrixs[CO_Matrix_ID].GetF(Matrix);
}

void CO_Matrix_GetD(GLdouble * Matrix,unsigned int CO_Matrix_ID)
{
	if(CO_Matrix_ID>=CO_MatrixCount) return;
	CommonMatrixs[CO_Matrix_ID].GetD(Matrix);
}