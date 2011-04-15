#include "Common.h"
#include <math.h>
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
GLdouble MatrixTMP[16]={1.0,0.0,0.0,0.0,
					  0.0,1.0,0.0,0.0,
					  0.0,0.0,1.0,0.0,
					  0.0,0.0,0.0,1.0};
GLfloat MatrixTMPF[16];
static const GLdouble IdentityMatrixD[16]={1.0,0.0,0.0,0.0,
										   0.0,1.0,0.0,0.0,
										   0.0,0.0,1.0,0.0,
										   0.0,0.0,0.0,1.0};
int RenderFaces=0;
char FullWidthFontPath[MAX_PATH];
char HalfWidthFontPath[MAX_PATH];
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
/*
void CO_SetMMatrixToGLSL(GLint UniformLoc,GLfloat * Matrix)
{
	if(Matrix)
		for (int i=0;i<16;i++) MatrixTMPF[i]=(GLfloat)Matrix[i];
	else
		for (int i=0;i<16;i++) MatrixTMPF[i]=(GLfloat)MMatrix[i];
	glUniformMatrix4fv(UniformLoc,1,false,MatrixTMPF);
}
void CO_SetPMatrixToGLSL(GLint UniformLoc,GLfloat * Matrix)
{
	if(Matrix)
		for (int i=0;i<16;i++) MatrixTMPF[i]=(GLfloat)Matrix[i];
	else
		for (int i=0;i<16;i++) MatrixTMPF[i]=(GLfloat)PMatrix[i];
	glUniformMatrix4fv(UniformLoc,1,false,MatrixTMPF);
}
void CO_SetMVPMatrixToGLSL(GLint UniformLoc,GLfloat * Matrix)
{
	if(Matrix)
		for (int i=0;i<16;i++) MatrixTMPF[i]=(GLfloat)Matrix[i];
	else
		for (int i=0;i<16;i++) MatrixTMPF[i]=(GLfloat)MVPMatrix[i];
	glUniformMatrix4fv(UniformLoc,1,false,MatrixTMPF);
}
*/
void CO_SetMMatrix(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) MMatrix[i]=Matrix[i];
}
void CO_SetPMatrix(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) PMatrix[i]=Matrix[i];
}
void CO_SetMVPMatrix(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) MVPMatrix[i]=Matrix[i];
}
void CO_SetMMatrixD(GLdouble * Matrix)
{
	if(!Matrix) return ;
	memcpy(MMatrix,Matrix,16*sizeof(GLdouble));
}
void CO_SetPMatrixD(GLdouble * Matrix)
{
	if(!Matrix) return ;
	memcpy(PMatrix,Matrix,16*sizeof(GLdouble));
}
void CO_SetMVPMatrixD(GLdouble * Matrix)
{
	if(!Matrix) return ;
	memcpy(MVPMatrix,Matrix,16*sizeof(GLdouble));
}
void CO_IdentityMVPMatrix()
{
	memcpy(MVPMatrix, IdentityMatrixD, 16 * sizeof(GLdouble));
}
void CO_IdentityMMatrix()
{
	memcpy(MMatrix, IdentityMatrixD, 16 * sizeof(GLdouble));
}
void CO_IdentityPMatrix()
{
	memcpy(PMatrix, IdentityMatrixD, 16 * sizeof(GLdouble));
}
void CO_GetMMatrix(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) Matrix[i]=(GLfloat)MMatrix[i];
}
void CO_GetPMatrix(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) Matrix[i]=(GLfloat)PMatrix[i];
}
void CO_GetMVPMatrix(GLfloat * Matrix)
{
	if(!Matrix) return ;
	Easy_matrix_mult_Double(MVPMatrix,PMatrix,MMatrix);
	for (int i=0;i<16;i++) Matrix[i]=(GLfloat)MVPMatrix[i];
}
void CO_GetMMatrixD(GLdouble * Matrix)
{
	if(!Matrix) return ;
	memcpy(Matrix,MMatrix,16*sizeof(GLdouble));
}
void CO_GetPMatrixD(GLdouble * Matrix)
{
	if(!Matrix) return ;
	memcpy(Matrix,PMatrix,16*sizeof(GLdouble));
}
void CO_GetMVPMatrixD(GLdouble * Matrix)
{
	if(!Matrix) return ;
	Easy_matrix_mult_Double(MVPMatrix,PMatrix,MMatrix);
	memcpy(Matrix,MVPMatrix,16*sizeof(GLdouble));
}
void CO_MatrixOrthogonalProjection(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble n, GLdouble f)
{
	PMatrix[0] = 2 / (right - left);	PMatrix[4] = 0;						PMatrix[8] = 0;					PMatrix[12] = -(right + left) / (right - left);
	PMatrix[1] = 0;						PMatrix[5] = 2 / (top - bottom);	PMatrix[9] = 0;					PMatrix[13] = -(top + bottom) / (top - bottom);
	PMatrix[2] = 0;						PMatrix[6] = 0;						PMatrix[10] = -2 / (f - n);		PMatrix[14] = -(f + n) / (f - n);
	PMatrix[3] = 0;						PMatrix[7] = 0;						PMatrix[11] = 0;				PMatrix[15] = 1;
}
void CO_MatrixOrthogonalProjection(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat n, GLfloat f, GLfloat * Matrix)
{
	Matrix[0] = 2 / (right - left);	Matrix[4] = 0;						Matrix[8] = 0;					Matrix[12] = -(right + left) / (right - left);
	Matrix[1] = 0;						Matrix[5] = 2 / (top - bottom);	Matrix[9] = 0;					Matrix[13] = -(top + bottom) / (top - bottom);
	Matrix[2] = 0;						Matrix[6] = 0;						Matrix[10] = -2 / (f - n);		Matrix[14] = -(f + n) / (f - n);
	Matrix[3] = 0;						Matrix[7] = 0;						Matrix[11] = 0;				Matrix[15] = 1;
}
void CO_MatrixPerspectiveProjection(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble n, GLdouble f)
{
	PMatrix[0] = (2 * n) / (right - left);		PMatrix[4] = 0;								PMatrix[8] = (right + left) / (right - left);		PMatrix[12] = 0;
	PMatrix[1] = 0;								PMatrix[5] = (2 * n) / (top - bottom);		PMatrix[9] = (top + bottom) / (top - bottom);		PMatrix[13] = 0;
	PMatrix[2] = 0;								PMatrix[6] = 0;								PMatrix[10] = -(f + n) / (f - n);					PMatrix[14] = -(2 * f * n) / (f - n);
	PMatrix[3] = 0;								PMatrix[7] = 0;								PMatrix[11] = -1;									PMatrix[15] = 0;
}

GLuint GlslPO=0;
void CO_SetGlslPO(GLuint SetGlslPO)
{
	GlslPO=SetGlslPO;
}
GLuint CO_GetGlslPO()
{
	return GlslPO;
}
void CO_MultMMatrix(GLfloat * Matrix)
{
	if(!Matrix) return ;
	for (int i=0;i<16;i++) MatrixTMP[i]=Matrix[i];
	Easy_matrix_mult_Double(MMatrix,MMatrix,MatrixTMP);
}
/*
void glhFrustumf2(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                  GLdouble znear, GLdouble zfar)
{
    GLdouble temp, temp2, temp3, temp4;
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    PMatrix[0] = temp / temp2;
    PMatrix[1] = 0.0;
    PMatrix[2] = 0.0;
    PMatrix[3] = 0.0;
    PMatrix[4] = 0.0;
    PMatrix[5] = temp / temp3;
    PMatrix[6] = 0.0;
    PMatrix[7] = 0.0;
    PMatrix[8] = (right + left) / temp2;
    PMatrix[9] = (top + bottom) / temp3;
    PMatrix[10] = (-zfar - znear) / temp4;
    PMatrix[11] = -1.0;
    PMatrix[12] = 0.0;
    PMatrix[13] = 0.0;
    PMatrix[14] = (-temp * zfar) / temp4;
    PMatrix[15] = 0.0;
}
void MatrixPerspectiveProjectionFov(GLdouble fovyInDegrees, GLdouble aspectRatio,
                      GLdouble znear, GLdouble zfar)
{
    GLdouble ymax, xmax;
    GLdouble temp, temp2, temp3, temp4;
    ymax = znear * tan(fovyInDegrees * 3.14159265358979323846 / 360.0);
    //ymin = -ymax;
    //xmin = -ymax * aspectRatio;
    xmax = ymax * aspectRatio;
    glhFrustumf2(-xmax, xmax, -ymax, ymax, znear, zfar);
}
*/
void CO_MatrixPerspectiveProjectionFov(GLdouble fovyInDegrees, GLdouble aspectRatio,
                      GLdouble znear, GLdouble zfar)
{
    GLdouble ymax, xmax;
    ymax = znear * tan(fovyInDegrees * 3.14159265358979323846 / 360.0);
    xmax = ymax * aspectRatio;

	PMatrix[0] = znear / xmax;
    PMatrix[1] = 0.0;
    PMatrix[2] = 0.0;
    PMatrix[3] = 0.0;
    PMatrix[4] = 0.0;
    PMatrix[5] = znear / ymax;
    PMatrix[6] = 0.0;
    PMatrix[7] = 0.0;
    PMatrix[8] = 0.0;
    PMatrix[9] = 0.0;
    PMatrix[10] = (-zfar - znear) / (zfar - znear);
    PMatrix[11] = -1.0;
    PMatrix[12] = 0.0;
    PMatrix[13] = 0.0;
    PMatrix[14] = (-2.0*znear * zfar) /  (zfar - znear);
    PMatrix[15] = 0.0;
}

void CO_MatrixPerspectiveProjectionFov(GLfloat fovyInDegrees, GLfloat aspectRatio,
                      GLfloat znear, GLfloat zfar,GLfloat * Matrix)
{
    GLfloat ymax, xmax;
    ymax = znear * tan(fovyInDegrees * 3.14159265358979323846f / 360.0f);
    xmax = ymax * aspectRatio;

	Matrix[0] = znear / xmax;
    Matrix[1] = 0.0;
    Matrix[2] = 0.0;
    Matrix[3] = 0.0;
    Matrix[4] = 0.0;
    Matrix[5] = znear / ymax;
    Matrix[6] = 0.0;
    Matrix[7] = 0.0;
    Matrix[8] = 0.0;
    Matrix[9] = 0.0;
    Matrix[10] = (-zfar - znear) / (zfar - znear);
    Matrix[11] = -1.0;
    Matrix[12] = 0.0;
    Matrix[13] = 0.0;
    Matrix[14] = (-2.0f*znear * zfar) /  (zfar - znear);
    Matrix[15] = 0.0;
}


GLfloat CO_OmniLight_Pos[OmniLightDataNum*4];
GLfloat CO_OmniLight_Color[OmniLightDataNum*4];
GLint CO_OmniLight_Pos_Loc=-1;
GLint CO_OmniLight_Color_Loc=-1;
void CO_SetOmniLight(_OmniLightData * Light,unsigned int LightNum)
{
	if((!Light)||(LightNum>=OmniLightDataNum))
		return;
	memcpy(&(CO_OmniLight_Pos[LightNum*4]),Light->Pos,sizeof(GLfloat)*4);
	memcpy(&(CO_OmniLight_Color[LightNum*4]),Light->Color,sizeof(GLfloat)*4);
}
void CO_GetOmniLight(_OmniLightData * Light,unsigned int LightNum)
{
	if((!Light)||(LightNum>=OmniLightDataNum))
		return;
	memcpy(Light->Pos,&(CO_OmniLight_Pos[LightNum*4]),sizeof(GLfloat)*4);
	memcpy(Light->Color,&(CO_OmniLight_Color[LightNum*4]),sizeof(GLfloat)*4);
}
void CO_SetOmniLightGLSLLoc(GLint OmniLight_Pos_Loc,GLint OmniLight_Color_Loc)
{
	CO_OmniLight_Pos_Loc=OmniLight_Pos_Loc;
	CO_OmniLight_Color_Loc=OmniLight_Color_Loc;
}
void CO_SetOmniLightToGLSL()
{
	glUniform4fv(CO_OmniLight_Pos_Loc,OmniLightDataNum,CO_OmniLight_Pos);
	glUniform4fv(CO_OmniLight_Color_Loc,OmniLightDataNum,CO_OmniLight_Color);
}

_MaterialData CO_MaterialData;
GLint CO_Material_Loc=-1;
void CO_SetMaterial(_MaterialData * Material)
{
	if(Material)
		memcpy(&CO_MaterialData,Material,sizeof(_MaterialData));
}
void CO_GetMaterial(_MaterialData * Material)
{
	if(Material)
		memcpy(Material,&CO_MaterialData,sizeof(_MaterialData));
}
void CO_SetMaterialGLSLLoc(GLint Material_Loc)
{
	CO_Material_Loc=Material_Loc;
}
void CO_SetMaterialToGLSL(_MaterialData * Material)
{
	if(Material)
		glUniform4fv(CO_Material_Loc,3,(GLfloat * )Material);
	else
		glUniform4fv(CO_Material_Loc,3,(GLfloat * )(&CO_MaterialData));
}

GLfloat CO_GlobalAmbient[4]={0.0f,0.0f,0.0f,0.0f};
GLint CO_GlobalAmbient_Loc=-1;
void CO_SetGlobalAmbient(GLfloat * GlobalAmbient)
{
	if(GlobalAmbient)
		memcpy(CO_GlobalAmbient,GlobalAmbient,sizeof(CO_GlobalAmbient));
}
void CO_GetGlobalAmbient(GLfloat * GlobalAmbient)
{
	if(GlobalAmbient)
		memcpy(GlobalAmbient,CO_GlobalAmbient,sizeof(CO_GlobalAmbient));
}
void CO_SetGlobalAmbientGLSLLoc(GLint GlobalAmbient_Loc)
{
	CO_GlobalAmbient_Loc=GlobalAmbient_Loc;
}
void CO_SetGlobalAmbientToGLSL(GLfloat * GlobalAmbient)
{
	if(GlobalAmbient)
		glUniform4fv(CO_GlobalAmbient_Loc,1,GlobalAmbient);
	else
		glUniform4fv(CO_GlobalAmbient_Loc,1,CO_GlobalAmbient);
}

GLint CO_MMatrixGLSLLoc=-1;
GLint CO_PMatrixGLSLLoc=-1;
GLint CO_MVPMatrixGLSLLoc=-1;
void CO_SetMatrixsGLSLLoc(GLint MMatrixGLSLLoc,GLint PMatrixGLSLLoc,GLint MVPMatrixGLSLLoc)
{
	if(MMatrixGLSLLoc!=-1) CO_MMatrixGLSLLoc=MMatrixGLSLLoc;
	if(PMatrixGLSLLoc!=-1) CO_PMatrixGLSLLoc=PMatrixGLSLLoc;
	if(MVPMatrixGLSLLoc!=-1) CO_MVPMatrixGLSLLoc=MVPMatrixGLSLLoc;
}
void CO_SetMMatrixToGlsl(GLfloat * Matrix)
{
	if(Matrix)
		glUniformMatrix4fv(CO_MMatrixGLSLLoc,1,false,Matrix);
	else
	{
		for (int i=0;i<16;i++) MatrixTMPF[i]=(GLfloat)MMatrix[i];
		glUniformMatrix4fv(CO_MMatrixGLSLLoc,1,false,MatrixTMPF);
	}
}
void CO_SetPMatrixToGlsl(GLfloat * Matrix)
{
	if(Matrix)
		glUniformMatrix4fv(CO_PMatrixGLSLLoc,1,false,Matrix);
	else
	{
		for (int i=0;i<16;i++) MatrixTMPF[i]=(GLfloat)PMatrix[i];
		glUniformMatrix4fv(CO_PMatrixGLSLLoc,1,false,MatrixTMPF);
	}
}
void CO_SetMVPMatrixToGlsl(GLfloat * Matrix)
{
	if(Matrix)
		glUniformMatrix4fv(CO_MVPMatrixGLSLLoc,1,false,Matrix);
	else
	{
		Easy_matrix_mult_Double(MVPMatrix,PMatrix,MMatrix);
		for (int i=0;i<16;i++) MatrixTMPF[i]=(GLfloat)MVPMatrix[i];
		glUniformMatrix4fv(CO_MVPMatrixGLSLLoc,1,false,MatrixTMPF);
	}
}
GLint CO_TexTurnY=-1;

void CO_SetTexTurnYGLSLLoc(GLint TexTurnY_Loc)
{
	CO_TexTurnY=TexTurnY_Loc;
}

void CO_SetTexTurnYToGLSL(GLfloat * TexTurnY)
{
	glUniform4fv(CO_TexTurnY,1,TexTurnY);
}