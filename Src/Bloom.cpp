#include <GL/glew.h>
#include <windows.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <gl/glaux.h>
#include "Bloom.h"
#include "shaders.h"

GLuint bloomTexId1,bloomTexId2;
int bloomTexSize,DrawbloomTexSize;
unsigned int EmptyTexture(int wh)							// 创建一个空的纹理
{
	GLuint txtnumber;							// 纹理ID
	unsigned int* data;						// 存储数据

	// 为纹理数据（128*128*4）建立存储区
	data = (unsigned int*)new GLuint[((wh * wh)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((wh * wh)* 4 * sizeof(unsigned int)));	// 清除存储区

	glGenTextures(1, &txtnumber);				// 创建一个纹理
	glBindTexture(GL_TEXTURE_2D, txtnumber);			// 构造纹理

	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, wh, wh,0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


	delete [] data;						// 释放数据

	return txtnumber;						// 返回纹理ID
}

void InitBloom(int winW,int winH)
{
	bloomTexSize=1024;
	if((winW>1024)||(winH>1024))
	bloomTexSize=2048;
	if((winW>2048)||(winH>2048))
	bloomTexSize=4096;
	DrawbloomTexSize=bloomTexSize/8;
	bloomTexId1=EmptyTexture(DrawbloomTexSize);
	bloomTexId2=EmptyTexture(bloomTexSize);

}
void GetBloomTex(int winW,int winH)
{
	glBindTexture(GL_TEXTURE_2D, bloomTexId2);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, -(bloomTexSize-winW)/2, -(bloomTexSize-winH)/2, bloomTexSize, bloomTexSize, 0);
}
void DrawBloomTex(int winW,int winH)
{
		
		glBindTexture(GL_TEXTURE_2D, bloomTexId2);

		glDisable(GL_BLEND);	
		glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glPushMatrix();										// Store The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix
		glOrtho(-winW/2,winW/2,-winH/2,winH/2,-1,1);							// Set Up An Ortho Screen
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPushMatrix();										// Store The Modelview Matrix
		glLoadIdentity();	


			DrawBloomMap(winW,winH);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);glVertex2i(-DrawbloomTexSize/2,-DrawbloomTexSize/2);
				glTexCoord2f(1.0f,0.0f);glVertex2i( DrawbloomTexSize/2,-DrawbloomTexSize/2);
				glTexCoord2f(1.0f,1.0f);glVertex2i( DrawbloomTexSize/2, DrawbloomTexSize/2);
				glTexCoord2f(0.0f,1.0f);glVertex2i(-DrawbloomTexSize/2, DrawbloomTexSize/2);
			glEnd();
			CGDisableProfilePixel();
			glBindTexture(GL_TEXTURE_2D, bloomTexId1);
			glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, -(DrawbloomTexSize-winW)/2, -(DrawbloomTexSize-winH)/2, DrawbloomTexSize, DrawbloomTexSize, 0);
			//glClear (GL_COLOR_BUFFER_BIT );

			DrawBloomW(winW);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);glVertex2i(-DrawbloomTexSize/2,-DrawbloomTexSize/2);
				glTexCoord2f(1.0f,0.0f);glVertex2i( DrawbloomTexSize/2,-DrawbloomTexSize/2);
				glTexCoord2f(1.0f,1.0f);glVertex2i( DrawbloomTexSize/2, DrawbloomTexSize/2);
				glTexCoord2f(0.0f,1.0f);glVertex2i(-DrawbloomTexSize/2, DrawbloomTexSize/2);
			glEnd();
			CGDisableProfilePixel();
			glBindTexture(GL_TEXTURE_2D, bloomTexId1);
			glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, -(DrawbloomTexSize-winW)/2, -(DrawbloomTexSize-winH)/2, DrawbloomTexSize, DrawbloomTexSize, 0);
			//glClear (GL_COLOR_BUFFER_BIT );

			DrawBloomH(winH);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);glVertex2i(-DrawbloomTexSize/2,-DrawbloomTexSize/2);
				glTexCoord2f(1.0f,0.0f);glVertex2i( DrawbloomTexSize/2,-DrawbloomTexSize/2);
				glTexCoord2f(1.0f,1.0f);glVertex2i( DrawbloomTexSize/2, DrawbloomTexSize/2);
				glTexCoord2f(0.0f,1.0f);glVertex2i(-DrawbloomTexSize/2, DrawbloomTexSize/2);
			glEnd();
			CGDisableProfilePixel();
			glBindTexture(GL_TEXTURE_2D, bloomTexId1);
			glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, -(DrawbloomTexSize-winW)/2, -(DrawbloomTexSize-winH)/2, DrawbloomTexSize, DrawbloomTexSize, 0);
			//glClear (GL_COLOR_BUFFER_BIT );
			
		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glPopMatrix();										// Restore The Old Projection Matrix
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPopMatrix();										// Restore The Old Projection Matrix
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

		glEnable(GL_BLEND);
	
}
void DrawBloom(int winW,int winH)
{

		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, bloomTexId1);

		glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glPushMatrix();										// Store The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix
		glOrtho(-winW/2,winW/2,-winH/2,winH/2,-1,1);							// Set Up An Ortho Screen
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPushMatrix();										// Store The Modelview Matrix
		
		glLoadIdentity();	
			ToneMapping();
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);glVertex2i(-bloomTexSize/2,-bloomTexSize/2);
				glTexCoord2f(1.0f,0.0f);glVertex2i( bloomTexSize/2,-bloomTexSize/2);
				glTexCoord2f(1.0f,1.0f);glVertex2i( bloomTexSize/2, bloomTexSize/2);
				glTexCoord2f(0.0f,1.0f);glVertex2i(-bloomTexSize/2, bloomTexSize/2);
			glEnd();
			CGDisableProfilePixel();
		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glPopMatrix();										// Restore The Old Projection Matrix
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPopMatrix();										// Restore The Old Projection Matrix
		glEnable(GL_DEPTH_TEST);

}