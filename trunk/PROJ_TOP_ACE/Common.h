//#pragma once
#ifndef _COMMON_H
#define _COMMON_H

#include <GL/glew.h>
#include <windows.h>
void SetMMatrix(GLfloat * Matrix);
void SetPMatrix(GLfloat * Matrix);
void IdentityMVPMatrix();
void IdentityMMatrix();
void IdentityPMatrix();
void GetMMatrix(GLfloat * Matrix);
void GetPMatrix(GLfloat * Matrix);
void GetMVPMatrix(GLfloat * Matrix);
void MatrixOrthogonalProjection(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble n, GLdouble f);
void MatrixOrthogonalProjection(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat n, GLfloat f, GLfloat * Matrix);
void MatrixPerspectiveProjection(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble n, GLdouble f);
void MatrixPerspectiveProjectionFov(GLdouble fovyInDegrees, GLdouble aspectRatio,
                      GLdouble znear, GLdouble zfar);
void MatrixPerspectiveProjectionFov(GLfloat fovyInDegrees, GLfloat aspectRatio,
                      GLfloat znear, GLfloat zfar,GLfloat * Matrix);
void SetGlslPO(GLuint SetGlslPO);
void MultMMatrix(GLfloat * Matrix);
GLuint GetGlslPO();
#endif
