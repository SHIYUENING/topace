#include "CommonMatrix.h"
static const GLdouble IdentityMatrixD[16]={1.0,0.0,0.0,0.0,
										   0.0,1.0,0.0,0.0,
										   0.0,0.0,1.0,0.0,
										   0.0,0.0,0.0,1.0};

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


void CO_IdentityMatrixD(GLdouble * MatrixD)
{
	if(MatrixD) memcpy(MatrixD, IdentityMatrixD, 16 * sizeof(GLdouble));
}

void CCommonMatrix::Load(GLdouble * MatrixD)
{
	if(MatrixD) memcpy(LinkList->Matrix,MatrixD,16*sizeof(GLdouble));
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


void CCommonMatrix::Mult(GLfloat * Matrix)
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


void CCommonMatrix::Get(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) Matrix[i]=LinkList->Matrix[i];
}
