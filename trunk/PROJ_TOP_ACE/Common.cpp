#include "Common.h"

GLdouble MVPMatrix[16]={1.0,0.0,0.0,0.0,
						0.0,1.0,0.0,0.0,
						0.0,0.0,1.0,0.0,
						0.0,0.0,0.0,1.0};
GLdouble MMatrix[16]={1.0,0.0,0.0,0.0,
					  0.0,1.0,0.0,0.0,
					  0.0,0.0,1.0,0.0,
					  0.0,0.0,0.0,1.0};
GLdouble PMatrix[16]={1.0,0.0,0.0,0.0,
					  0.0,1.0,0.0,0.0,
					  0.0,0.0,1.0,0.0,
					  0.0,0.0,0.0,1.0};
static const GLdouble IdentityMatrixD[16]={1.0,0.0,0.0,0.0,
										   0.0,1.0,0.0,0.0,
										   0.0,0.0,1.0,0.0,
										   0.0,0.0,0.0,1.0};
void Easy_matrix_mult_Double(GLdouble Matrix[4][4], GLdouble a[4][4], GLdouble b[4][4]) 
{
    GLdouble tmp[4][4];
    int i, j, k;
    GLdouble ab;

    memcpy(tmp, a, 16 * sizeof(GLdouble));
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            ab = 0.0f;
            for (k = 0; k < 4; k++) ab += tmp[k][i] * b[j][k];
            Matrix[j][i] = ab;
        }
    }
}
void Easy_matrix_mult_Double(GLdouble * Matrix, GLdouble * a, GLdouble * b) 
{
    GLdouble tmp[16];
    int i, j, k;
    GLdouble ab;

    memcpy(tmp, a, 16 * sizeof(GLdouble));
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            ab = 0.0f;
            for (k = 0; k < 4; k++) ab += tmp[k*4+i] * b[j*4+k];
            Matrix[j*4+i] = ab;
        }
    }
}
void SetMMatrix(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) MMatrix[i]=Matrix[i];
}
void SetPMatrix(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) PMatrix[i]=Matrix[i];
}
void IdentityMVPMatrix()
{
	memcpy(MVPMatrix, IdentityMatrixD, 16 * sizeof(GLdouble));
}
void IdentityMMatrix()
{
	memcpy(MMatrix, IdentityMatrixD, 16 * sizeof(GLdouble));
}
void IdentityPMatrix()
{
	memcpy(PMatrix, IdentityMatrixD, 16 * sizeof(GLdouble));
}
void GetMMatrix(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) Matrix[i]=(GLfloat)MMatrix[i];
}
void GetPMatrix(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) Matrix[i]=(GLfloat)PMatrix[i];
}
void GetMVPMatrix(GLfloat * Matrix)
{
	if(!Matrix) return ;
	Easy_matrix_mult_Double(MVPMatrix,PMatrix,MMatrix);
	for (int i=0;i<16;i++) Matrix[i]=(GLfloat)MVPMatrix[i];
}
void MatrixOrthogonalProjection(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble n, GLdouble f)
{
	PMatrix[0] = 2 / (right - left);	PMatrix[4] = 0;						PMatrix[8] = 0;					PMatrix[12] = -(right + left) / (right - left);
	PMatrix[1] = 0;						PMatrix[5] = 2 / (top - bottom);	PMatrix[9] = 0;					PMatrix[13] = -(top + bottom) / (top - bottom);
	PMatrix[2] = 0;						PMatrix[6] = 0;						PMatrix[10] = -2 / (f - n);		PMatrix[14] = -(f + n) / (f - n);
	PMatrix[3] = 0;						PMatrix[7] = 0;						PMatrix[11] = 0;				PMatrix[15] = 1;
}
void MatrixPerspectiveProjection(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble n, GLdouble f)
{
	PMatrix[0] = (2 * n) / (right - left);		PMatrix[4] = 0;								PMatrix[8] = (right + left) / (right - left);		PMatrix[12] = 0;
	PMatrix[1] = 0;								PMatrix[5] = (2 * n) / (top - bottom);		PMatrix[9] = (top + bottom) / (top - bottom);		PMatrix[13] = 0;
	PMatrix[2] = 0;								PMatrix[6] = 0;								PMatrix[10] = -(f + n) / (f - n);					PMatrix[14] = -(2 * f * n) / (f - n);
	PMatrix[3] = 0;								PMatrix[7] = 0;								PMatrix[11] = -1;									PMatrix[15] = 0;
}
GLuint GlslPO=0;
void SetGlslPO(GLuint SetGlslPO)
{
	GlslPO=SetGlslPO;
}
GLuint GetGlslPO()
{
	return GlslPO;
}