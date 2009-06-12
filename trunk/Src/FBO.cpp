#include "FBO.h"
#include <gl\glew.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
GLuint fbo;					// Our handle to the FBO
GLuint depthBuffer;			// Our handle to the depth render buffer
GLuint img=0;
GLuint dtex=0;//,fboBloomImg					// Our handle to a texture
void initFBO(bool IsSupportFBO)
{
/*	int gpuType=0;//0δ֪ 1NV 2ATI
	char szGPU[128]={0};
	sprintf(szGPU,"%s",(char *)glGetString(GL_VENDOR));
	if(szGPU[0]=='A')
	{
		gpuType=2;
	}
	if(szGPU[0]=='N')
	{
		gpuType=1;
	}*/
	if(IsSupportFBO)
	{
		int imagesize=1024;

		glGenFramebuffersEXT(1, &fbo);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);

		glGenTextures(1, &img);
		glBindTexture(GL_TEXTURE_2D, img);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  imagesize, imagesize, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);//GL_RGBA16F_ARB
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
/*
		glGenTextures(1, &fboBloomImg);
		glBindTexture(GL_TEXTURE_2D, fboBloomImg);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  imagesize, imagesize, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);//GL_RGBA16F_ARB
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

*/
			
		glGenTextures(1, &dtex);
		glBindTexture(GL_TEXTURE_2D, dtex);
	/*	if(gpuType==0)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, imagesize, imagesize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		if(gpuType==2)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, imagesize, imagesize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		if(gpuType==1)
			*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, imagesize, imagesize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, img, 0);
		//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, fboBloomImg, 0);

		GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
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

		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, dtex, 0);


		status = (GLenum) glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
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

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	// Unbind the FBO for now
	}


}