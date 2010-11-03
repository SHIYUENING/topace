#include "DrawQUAD.h"
GLfloat QUADArrayTexCoord[]={0.0f,0.0f,
							 1.0f,0.0f,
							 1.0f,1.0f,
							 0.0f,1.0f};
GLint QUADArrayVertex[]={0,0,1,0,1,1,0,1};
void DrawQUAD(GLuint Left,GLuint Right,GLuint Up,GLuint Down)
{
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer( 2, GL_FLOAT, 0, QUADArrayTexCoord );
	glVertexPointer( 2, GL_INT, 0, QUADArrayVertex );
	glDrawArrays(GL_QUADS,0,4);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}