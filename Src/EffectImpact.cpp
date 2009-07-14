#include "EffectImpact.h"

CEffectImpact::CEffectImpact(void)
: IsSupportFBO(false)
, TextureID(0)
, winW(0)
, winH(0)
, EffectTime(0)
{

}

CEffectImpact::~CEffectImpact(void)
{
	if(TextureID!=0)
		glDeleteLists(TextureID,1);
}

unsigned int CEffectImpact::EmptyTexture(int wh)
{
	if(wh<1)
		wh=256;
	GLuint txtnumber;							// 纹理ID
	unsigned int* data;						// 存储数据

	// 为纹理数据（wh*wh*4）建立存储区
	data = (unsigned int*)new GLuint[((wh * wh)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((wh * wh)* 4 * sizeof(unsigned int)));	// 清除存储区

	glGenTextures(1, &txtnumber);				// 创建一个纹理
	glBindTexture(GL_TEXTURE_2D, txtnumber);			// 构造纹理

	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, wh, wh,0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	if(IsSupportFBO)
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				}
				else
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				}

	delete [] data;						// 释放数据

	return txtnumber;						// 返回纹理ID
}

void CEffectImpact::EffectImpactDraw(bool DrawEffectImpact)
{
	if(TextureID==0)
		return;
	if(DrawEffectImpact)
		EffectTime=EffectTime+2;
	else
		EffectTime=EffectTime-2;
	if(EffectTime>90)
		EffectTime=90;
	if(EffectTime<0)
		EffectTime=0;

	if(EffectTime>0)
	{
		
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f,1.0f,1.0f,(float)EffectTime/120.0f);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glPushMatrix();										// Store The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix
		//glOrtho(0,winW,0,winH,-1,1);							// Set Up An Ortho Screen
		glOrtho(-winW/2,winW/2,-winH/2,winH/2,-1,1);							// Set Up An Ortho Screen
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPushMatrix();										// Store The Modelview Matrix
		glLoadIdentity();	
				glBegin(GL_QUADS);							// Use A Quad For Each Character

					glTexCoord2f(0.01f,0.01f);glVertex2i(-EffectImpactTextureSize/2,-EffectImpactTextureSize/2);			// Texture Coord (Bottom Left)
											// Vertex Coord (Bottom Left)
					glTexCoord2f(0.99f,0.01f);glVertex2i( EffectImpactTextureSize/2,-EffectImpactTextureSize/2);		// Texture Coord (Bottom Right)
										// Vertex Coord (Bottom Right)
					glTexCoord2f(0.99f,0.99f);glVertex2i( EffectImpactTextureSize/2, EffectImpactTextureSize/2);			// Texture Coord (Top Right)
											// Vertex Coord (Top Right)
					glTexCoord2f(0.01f,0.99f);glVertex2i(-EffectImpactTextureSize/2, EffectImpactTextureSize/2);					// Texture Coord (Top Left)
											// Vertex Coord (Top Left)
					
				/*
					glTexCoord2f(-0.499f,-0.499f);			// Texture Coord (Bottom Left)

					glVertex2i(0,0);						// Vertex Coord (Bottom Left)

					glTexCoord2f( 0.499f,-0.499f);	// Texture Coord (Bottom Right)

					glVertex2i(EffectImpactTextureSize,0);						// Vertex Coord (Bottom Right)

					glTexCoord2f( 0.499f, 0.499f);			// Texture Coord (Top Right)

					glVertex2i(EffectImpactTextureSize,EffectImpactTextureSize);						// Vertex Coord (Top Right)

					glTexCoord2f(-0.499f, 0.499f);					// Texture Coord (Top Left)

					glVertex2i(0,EffectImpactTextureSize);						// Vertex Coord (Top Left)
					*/
				glEnd();
		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glPopMatrix();										// Restore The Old Projection Matrix
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPopMatrix();										// Restore The Old Projection Matrix
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		glColor4f(1.0f,1.0f,1.0f,1.0f);
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, -(EffectImpactTextureSize-winW)/2, -(EffectImpactTextureSize-winH)/2, EffectImpactTextureSize, EffectImpactTextureSize, 0);
	}
}

int CEffectImpact::Init(void)
{
	EffectImpactTextureSize=1024;
	if((winW>1024)||(winH>1024))
		EffectImpactTextureSize=2048;
	if((winW>2048)||(winH>2048))
		EffectImpactTextureSize=4096;
	TextureID=EmptyTexture(EffectImpactTextureSize);
	return 0;
}
