#pragma once
#include "shaders.h"
GLuint bloomTexId1,bloomTexId2;
int bloomTexSize,DrawbloomTexSize;

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
			cgGLDisableProfile( g_CGprofile_pixel );
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
			cgGLDisableProfile( g_CGprofile_pixel );
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
			cgGLDisableProfile( g_CGprofile_pixel );
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
		glBindTexture(GL_TEXTURE_2D, bloomTexId2);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, -(bloomTexSize-winW)/2, -(bloomTexSize-winH)/2, bloomTexSize, bloomTexSize, 0);
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
			cgGLDisableProfile( g_CGprofile_pixel );
		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glPopMatrix();										// Restore The Old Projection Matrix
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPopMatrix();										// Restore The Old Projection Matrix
		glEnable(GL_DEPTH_TEST);

}