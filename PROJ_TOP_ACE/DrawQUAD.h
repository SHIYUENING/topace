//#pragma once
#ifndef _DRAWQUAD_H
#define _DRAWQUAD_H

#include <GL/glew.h>
void DrawQUAD(GLuint Left,GLuint Right,GLuint Up,GLuint Down);
//void DrawQUAD_Att(GLuint Left,GLuint Right,GLuint Up,GLuint Down,GLint AttIndexTexCoord,GLint AttIndexVertex);
void DrawQUAD(GLfloat Left,GLfloat Right,GLfloat Up,GLfloat Down,GLfloat QUADW,GLfloat QUADH);
void DrawQUAD_Att(GLuint Left,GLuint Right,GLuint Up,GLuint Down,GLint AttIndexTexCoord,GLint AttIndexVertex,int winW=1,int winH=1);
void DrawQUADF(GLfloat Left,GLfloat Right,GLfloat Up,GLfloat Down);
void DrawQUADEX(GLuint TexID,GLuint Left,GLuint Right,GLuint Up,GLuint Down,GLuint winW,GLuint winH);
void DrawQUADEX_NOTEX(GLuint Left,GLuint Right,GLuint Up,GLuint Down,GLuint winW,GLuint winH);
void DrawQUADEX_RECT(GLuint TexID,GLuint Left,GLuint Right,GLuint Up,GLuint Down,GLuint winW,GLuint winH);
#endif
