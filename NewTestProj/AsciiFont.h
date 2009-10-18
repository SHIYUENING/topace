#ifndef _ASCIIFONT_H
#define _ASCIIFONT_H
#include <gl\glew.h>
#include <gl\gl.h>	
void BuildFont(GLuint FontTexId);
void glPrints(int x, int y, int winW,int winH,char *string);

#endif