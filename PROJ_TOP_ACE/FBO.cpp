#include "FBO.h"	
GLuint FBOID=0;	
GLuint ScreemTex=0;
GLuint ScreemTexDepth=0;
GLuint StarTex1=0;
GLuint StarTex2=0;
GLuint StarTexDepth=0;

GLuint BloomTex1=0;
GLuint BloomTex2=0;
GLuint BloomTexDepth=0;

bool SuppotFBO=false;
int ScreemTexW=0;
int ScreemTexH=0;
int FBOWinW=0;
int FBOWinH=0;
int next_p2 ( int a )
{
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}
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
GLuint InitFBO(int winW,int winH)
{
	FBOWinW=winW;
	FBOWinH=winH;
	ScreemTexW=next_p2(winW);
	ScreemTexH=next_p2(winH);

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
//	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOID);
	ScreemTex=InitTex2D(ScreemTexW, ScreemTexH,GL_LINEAR,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE);
	ScreemTexDepth=InitTex2D(ScreemTexW, ScreemTexH,GL_NEAREST,GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE);

	BloomTex1=InitTex2D(ScreemTexW/8, ScreemTexH/8,GL_LINEAR,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE);
	BloomTex2=InitTex2D(ScreemTexW/8, ScreemTexH/8,GL_LINEAR,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE);
	BloomTexDepth=InitTex2D(ScreemTexW/8, ScreemTexH/8,GL_NEAREST,GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE);

	StarTex1=InitTex2D(StarTexSizeX, StarTexSizeY,GL_LINEAR,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE);
	StarTex2=InitTex2D(StarTexSizeX, StarTexSizeY,GL_LINEAR,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE);
	StarTexDepth=InitTex2D(StarTexSizeX, StarTexSizeY,GL_NEAREST,GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE);
//	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

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

	if(ScreemTex)
		glDeleteTextures(1,&ScreemTex);
	if(ScreemTexDepth)
		glDeleteTextures(1,&ScreemTexDepth);

	if(StarTex1)
		glDeleteTextures(1,&StarTex1);
	if(StarTex2)
		glDeleteTextures(1,&StarTex2);
	if(StarTexDepth)
		glDeleteTextures(1,&StarTexDepth);

	if(BloomTex1)
		glDeleteTextures(1,&BloomTex1);
	if(BloomTex2)
		glDeleteTextures(1,&BloomTex2);
	if(BloomTexDepth)
		glDeleteTextures(1,&BloomTexDepth);
}
void TestTexFBO()
{
	glEnable( GL_TEXTURE_2D );
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,ScreemTexW,0,ScreemTexH,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();	
	glLoadIdentity();
	glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_COLOR   );
		glBindTexture(GL_TEXTURE_2D, BloomTex1);

		//glColor3f(0.1f,0.1f,1.0f);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,ScreemTexH/2);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i(ScreemTexW ,ScreemTexH/2);
				glTexCoord2f(1.0f,	0.0f);	glVertex2i(ScreemTexW, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();	
	glEnable(GL_DEPTH_TEST);
	glEnable( GL_BLEND );
	glEnable( GL_CULL_FACE );
}
void FBOS_BLOOM()
{
	glBindTexture(GL_TEXTURE_2D, ScreemTex);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0 ,FBOWinW, FBOWinH, 0);
	//glBindTexture(GL_TEXTURE_2D, BloomTex1);
	glPushAttrib(GL_VIEWPORT_BIT);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOID);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, BloomTex1, 0);
	CheckFBOError();
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, BloomTexDepth, 0);
	CheckFBOError();

	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glClear (GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glViewport(0,0,ScreemTexW/8, ScreemTexH/8);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);					
	glPushMatrix();	
	glLoadIdentity();
	glOrtho(0,ScreemTexW/8,0,ScreemTexH/8,-1,1);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();	
	glLoadIdentity();

	DrawBloomMapGLSL(FBOWinW,FBOWinH);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);glVertex2i(0,0);
				glTexCoord2f(1.0f,0.0f);glVertex2i( ScreemTexW/8,0);
				glTexCoord2f(1.0f,1.0f);glVertex2i( ScreemTexW/8, ScreemTexH/8);
				glTexCoord2f(0.0f,1.0f);glVertex2i(0, ScreemTexH/8);
			glEnd();

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, BloomTex2, 0);
	CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, BloomTex1);
	DrawBloomWGLSL(FBOWinW);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);glVertex2i(0,0);
				glTexCoord2f(1.0f,0.0f);glVertex2i( ScreemTexW/8,0);
				glTexCoord2f(1.0f,1.0f);glVertex2i( ScreemTexW/8, ScreemTexH/8);
				glTexCoord2f(0.0f,1.0f);glVertex2i(0, ScreemTexH/8);
			glEnd();
	
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, BloomTex1, 0);
	glBindTexture(GL_TEXTURE_2D, BloomTex2);
	DrawBloomHGLSL(FBOWinH);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);glVertex2i(0,0);
				glTexCoord2f(1.0f,0.0f);glVertex2i( ScreemTexW/8,0);
				glTexCoord2f(1.0f,1.0f);glVertex2i( ScreemTexW/8, ScreemTexH/8);
				glTexCoord2f(0.0f,1.0f);glVertex2i(0, ScreemTexH/8);
			glEnd();
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glPopAttrib();
	glBindTexture(GL_TEXTURE_2D, BloomTex1);
	
	glEnable( GL_BLEND );
	ToneMappingGLSL();
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);glVertex2i(0,0);
				glTexCoord2f(1.0f,0.0f);glVertex2i( ScreemTexW/8,0);
				glTexCoord2f(1.0f,1.0f);glVertex2i( ScreemTexW/8, ScreemTexH/8);
				glTexCoord2f(0.0f,1.0f);glVertex2i(0, ScreemTexH/8);
			glEnd();

	GLSL_Disable();
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();	
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();
	glEnable( GL_CULL_FACE );
	glEnable(GL_DEPTH_TEST);
	
}
void FBOS_Star_Begin()
{
	
	glBindTexture(GL_TEXTURE_2D, ScreemTexDepth);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0 ,ScreemTexW, ScreemTexH, 0);

	glPushAttrib(GL_VIEWPORT_BIT);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOID);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, ScreemTex, 0);
	CheckFBOError();
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, ScreemTexDepth, 0);
	CheckFBOError();
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glClear (GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable( GL_BLEND );
	glEnable( GL_CULL_FACE );
	glViewport(0,0,FBOWinW, FBOWinH);
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
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex1, 0);
	CheckFBOError();
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, StarTexDepth, 0);
	CheckFBOError();
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glViewport(0,0,StarTexSizeX, StarTexSizeY);
	//glClear (GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();	
	glLoadIdentity();
	glOrtho(0,StarTexSizeX,0,StarTexSizeY,-1,1);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();	
	glLoadIdentity();
		GLSL_Enable_StarPass0();
		glBindTexture(GL_TEXTURE_2D, ScreemTex);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	float(FBOWinH)/float(ScreemTexH));	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(float(FBOWinW)/float(ScreemTexW),	float(FBOWinH)/float(ScreemTexH));	glVertex2i(StarTexSizeX ,StarTexSizeY);
				glTexCoord2f(float(FBOWinW)/float(ScreemTexW),	0.0f);	glVertex2i(StarTexSizeX, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();
		

	GLSL_Enable_StarPass1();
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex2, 0);
	CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i(StarTexSizeX ,StarTexSizeY);
				glTexCoord2f(1.0f,	0.0f);	glVertex2i(StarTexSizeX, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();

	glDisable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_COLOR   );
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex1, 0);
	CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex2);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i(StarTexSizeX ,StarTexSizeY);
				glTexCoord2f(1.0f,	0.0f);	glVertex2i(StarTexSizeX, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();
	glDisable(GL_BLEND);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex2, 0);
	CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i(StarTexSizeX/4 ,StarTexSizeY);
				glTexCoord2f(1.0f,	0.0f);	glVertex2i(StarTexSizeX/4, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();
	glEnable(GL_BLEND);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex1, 0);
	CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex2);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f/4.0f,	1.0f);	glVertex2i(StarTexSizeX ,StarTexSizeY);
				glTexCoord2f(1.0f/4.0f,	0.0f);	glVertex2i(StarTexSizeX, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();
	glDisable(GL_BLEND);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex2, 0);
	CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i(StarTexSizeX/8 ,StarTexSizeY);
				glTexCoord2f(1.0f,	0.0f);	glVertex2i(StarTexSizeX/8, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();
	glEnable(GL_BLEND);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex1, 0);
	CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex2);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f/8.0f,	1.0f);	glVertex2i(StarTexSizeX ,StarTexSizeY);
				glTexCoord2f(1.0f/8.0f,	0.0f);	glVertex2i(StarTexSizeX, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();

	GLSL_Enable_StarPass0();
	glDisable(GL_BLEND);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex2, 0);
	CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i(StarTexSizeX/2 ,StarTexSizeY);
				glTexCoord2f(1.0f,	0.0f);	glVertex2i(StarTexSizeX/2, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();

	glEnable(GL_BLEND);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex1, 0);
	CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex2);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f/2.0f,	1.0f);	glVertex2i(StarTexSizeX ,StarTexSizeY);
				glTexCoord2f(1.0f/2.0f,	0.0f);	glVertex2i(StarTexSizeX, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();
	GLSL_Disable();
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();	
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();
	glEnable( GL_BLEND );
	glEnable( GL_CULL_FACE );
	glEnable(GL_DEPTH_TEST);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glPopAttrib();
}