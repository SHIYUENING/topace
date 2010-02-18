#include "FBO.h"	
GLuint FBOID=0;	
GLuint StarTex1=0;
GLuint StarTex2=0;
GLuint StarTexDepth=0;
bool SuppotFBO=false;
void CheckFBOError()
{
		GLenum status = (GLenum) glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		switch(status) 
		{
			case GL_FRAMEBUFFER_COMPLETE_EXT:
				break;
			case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
				MessageBox (HWND_DESKTOP, "Unsupported framebuffer format\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, missing attachment\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, attached images must have same dimensions\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, attached images must have same format\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, missing draw buffer\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, missing read buffer\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			default:
				MessageBox (HWND_DESKTOP, "unknown error !!!!\n", "Error", MB_OK | MB_ICONEXCLAMATION);
	         
		}
}
GLuint InitTex2D(int TexSizeX,int TexSizeY,GLfloat FILTER,GLuint FormatI,GLuint Format,GLuint DataType)
{
	GLuint Tex2DID=0;
	glGenTextures(1, &Tex2DID);
	glBindTexture(GL_TEXTURE_2D, Tex2DID);
	glTexImage2D(GL_TEXTURE_2D, 0, FormatI,  TexSizeX, TexSizeY, 0, Format, DataType, NULL);//GL_RGBA16F_ARB
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FILTER);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FILTER);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	return Tex2DID;
}
GLuint InitFBO()
{
	if(SuppotFBO)
		return 0;
	if (glewIsSupported("GL_EXT_framebuffer_object"))
		SuppotFBO=true;
	else
	{
		SuppotFBO=false;
		return 0;
	}
	glGenFramebuffersEXT(1, &FBOID);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOID);
	StarTex1=InitTex2D(StarTexSizeX, StarTexSizeY,GL_LINEAR,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE);
	StarTex2=InitTex2D(StarTexSizeX, StarTexSizeY,GL_LINEAR,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE);
	StarTexDepth=InitTex2D(StarTexSizeX, StarTexSizeY,GL_NEAREST,GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	//FBOS_Star_Begin();
	//FBOS_Star_End();
	return FBOID;
}
void DeinitFBO()
{
	if(!SuppotFBO)
		return;
	SuppotFBO=false;

	if(FBOID)
		glDeleteFramebuffersEXT(1,&FBOID);
	if(StarTex1)
		glDeleteTextures(1,&StarTex1);
	if(StarTex2)
		glDeleteTextures(1,&StarTex2);
	if(StarTexDepth)
		glDeleteTextures(1,&StarTexDepth);
}
void FBOS_Star_Begin()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOID);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex1, 0);
	CheckFBOError();
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, StarTexDepth, 0);
	CheckFBOError();
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	/*
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0,0,1024, 1024);
	glClear (GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();	
	glLoadIdentity();	
	*/
}
void FBOS_Star_End()
{
	/*
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();	
	glPopAttrib();
	*/
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}