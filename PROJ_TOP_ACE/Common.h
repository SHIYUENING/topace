//#pragma once
#ifndef _COMMON_H
#define _COMMON_H

#include <GL/glew.h>
#include <windows.h>
#define OmniLightDataNum 8
struct _OmniLightData{
	GLfloat Pos[4];
	GLfloat Color[4];
};
struct _MaterialData{
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat emission[4];//shininess in emission[3]
	//GLfloat shininess;
};
void CO_SetGlobalAmbient(GLfloat * GlobalAmbient);
void CO_GetGlobalAmbient(GLfloat * GlobalAmbient);
void CO_SetGlobalAmbientToGLSL(GLint UniformLoc,GLfloat * GlobalAmbient=NULL);
void CO_SetOmniLight(_OmniLightData * Light,unsigned int LightNum);
void CO_GetOmniLight(_OmniLightData * Light,unsigned int LightNum);
void CO_SetOmniLightToGLSL(GLint UniformLoc_Pos,GLint UniformLoc_Color);
void CO_SetMaterial(_MaterialData * Material);
void CO_GetMaterial(_MaterialData * Material);
void CO_SetMaterialToGLSL(GLint UniformLoc,_MaterialData * Material=NULL);
void CO_SetMMatrix(GLfloat * Matrix);
void CO_SetPMatrix(GLfloat * Matrix);
void CO_SetMVPMatrix(GLfloat * Matrix);
void CO_SetMMatrixD(GLdouble * Matrix);
void CO_SetPMatrixD(GLdouble * Matrix);
void CO_SetMVPMatrixD(GLdouble * Matrix);
void CO_IdentityMVPMatrix();
void CO_IdentityMMatrix();
void CO_IdentityPMatrix();
void CO_GetMMatrix(GLfloat * Matrix);
void CO_GetPMatrix(GLfloat * Matrix);
void CO_GetMVPMatrix(GLfloat * Matrix);
void CO_GetMMatrixD(GLdouble * Matrix);
void CO_GetPMatrixD(GLdouble * Matrix);
void CO_GetMVPMatrixD(GLdouble * Matrix);
void CO_MatrixOrthogonalProjection(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble n, GLdouble f);
void CO_MatrixOrthogonalProjection(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat n, GLfloat f, GLfloat * Matrix);
void CO_MatrixPerspectiveProjection(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble n, GLdouble f);
void CO_MatrixPerspectiveProjectionFov(GLdouble fovyInDegrees, GLdouble aspectRatio,
                      GLdouble znear, GLdouble zfar);
void CO_MatrixPerspectiveProjectionFov(GLfloat fovyInDegrees, GLfloat aspectRatio,
                      GLfloat znear, GLfloat zfar,GLfloat * Matrix);
void CO_SetGlslPO(GLuint SetGlslPO);
void CO_MultMMatrix(GLfloat * Matrix);
void CO_SetMMatrixToGlsl(GLint UniformLoc,GLfloat * Matrix);
void CO_SetPMatrixToGlsl(GLint UniformLoc,GLfloat * Matrix);
void CO_SetMVPMatrixToGlsl(GLint UniformLoc,GLfloat * Matrix);
GLuint CO_GetGlslPO();
#endif
