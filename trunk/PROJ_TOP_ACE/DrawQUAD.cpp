#include "DrawQUAD.h"
GLfloat QUADArrayTexCoord[]={
	1.0f,1.0f,
	0.0f,1.0f,
	1.0f,0.0f,
	0.0f,0.0f};
GLint QUADArrayVertex[]={
	1,1,
	0,1,
	1,0,
	0,0};
void DrawQUAD(GLuint Left,GLuint Right,GLuint Up,GLuint Down)
{
	QUADArrayVertex[2]=QUADArrayVertex[6]=Left;
	QUADArrayVertex[0]=QUADArrayVertex[4]=Right;
	QUADArrayVertex[1]=QUADArrayVertex[3]=Up;
	QUADArrayVertex[5]=QUADArrayVertex[7]=Down;
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer( 2, GL_FLOAT, 0, QUADArrayTexCoord );
	glVertexPointer( 2, GL_INT, 0, QUADArrayVertex );
	glDrawArrays(GL_TRIANGLE_STRIP,0,4);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}
void DrawQUADEX(GLuint TexID,GLuint Left,GLuint Right,GLuint Up,GLuint Down)
{
}