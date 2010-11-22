//#pragma once
#ifndef _COMMON_H
#define _COMMON_H

#include <GL/glew.h>
#include <windows.h>
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
GLuint CO_GetGlslPO();
#endif
