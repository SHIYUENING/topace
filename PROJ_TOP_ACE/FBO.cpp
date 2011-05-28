#include "FBO.h"
#include "DrawQUAD.h"
#include "TALogSys.h"
#include "Common.h"
#include "TAMFT3D.h"
GLuint FBOID=0;	
GLuint ScreemTex=0;
GLuint ScreemTexDepth=0;
GLuint StarTex1=0;
GLuint StarTex2=0;
GLuint StarTexDepth=0;

GLuint BloomTex1=0;
GLuint BloomTex2=0;
GLuint BloomTexDepth=0;

GLuint SSAOTex1=0;
GLuint SSAOTex2=0;

GLuint ShadowFBOID=0;
GLuint ShadowTex=0;
GLuint ShadowTexDepth=0;
GLuint TextTex=0;
GLuint BlurTexID[2]={0};
bool SuppotFBO=false;
int ScreemTexW=0;
int ScreemTexH=0;
int FBOWinW=0;
int FBOWinH=0;
int BloomTexW=0;
int BloomTexH=0;
int ShadowTexSize=512;
float ShadowTexDepthSize[2];
CTALogSys FBOLOG;
GLint MAX_COLOR_ATTACHMENTS=0;

GLfloat FBOMatrixTMP[16];
extern CTAMFT3D TAMFT3D;
int next_p2 ( int a )
{
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}
bool CheckFBOError()
{
	FBOLOG.ADDhtmLog("******Check Framebuffer Status******","#00FF00");
	FBOLOG.ADDhtmLog("******ERROR******","#FF0000");
	GLenum status = (GLenum) glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch(status) 
	{
		case GL_FRAMEBUFFER_COMPLETE_EXT: 
			FBOLOG.ClearLOG(); 
			return true;
		case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
			FBOLOG.ADDhtmLog("Unsupported framebuffer format","#FF0000");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
			FBOLOG.ADDhtmLog("Framebuffer incomplete, missing attachment","#FF0000");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
			FBOLOG.ADDhtmLog("Framebuffer incomplete, attached images must have same dimensions","#FF0000");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
			FBOLOG.ADDhtmLog("Framebuffer incomplete, attached images must have same format","#FF0000");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
			FBOLOG.ADDhtmLog("Framebuffer incomplete, missing draw buffer","#FF0000");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
			FBOLOG.ADDhtmLog("Framebuffer incomplete, missing read buffer","#FF0000");
			break;
		default:
			FBOLOG.ADDhtmLog("unknown error");
	         
	}
	FBOLOG.WriteLOGFile(true);
	FBOLOG.ClearLOG();
	return false;
}//GL_TEXTURE_RECTANGLE
GLuint InitTex2D(int TexSizeX,int TexSizeY,GLfloat FILTER,GLuint FormatI,GLuint Format,GLuint DataType,int TexTGT)
{
	GLuint Tex2DID=0;
	glGenTextures(1, &Tex2DID);
	glBindTexture(TexTGT, Tex2DID);
	glTexImage2D(TexTGT, 0, FormatI,  TexSizeX, TexSizeY, 0, Format, DataType, NULL);//GL_RGBA16F_ARB
	glTexParameterf(TexTGT, GL_TEXTURE_MIN_FILTER, FILTER);
	glTexParameterf(TexTGT, GL_TEXTURE_MAG_FILTER, FILTER);
	glTexParameterf(TexTGT, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(TexTGT, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	return Tex2DID;
}
bool InitFBO(int winW,int winH)
{
	if (glewIsSupported("GL_EXT_framebuffer_object"))
		SuppotFBO=true;
	else
	{
		ADD_LOG_Q("Can not suppot GL_EXT_framebuffer_object,Shadow and Bloom disable","#0000FF");
		SuppotFBO=false;
		return SuppotFBO;
		GameSet.Bloom=0;
		GameSet.Shadow=0;
	}
	if(!(glewIsSupported("GL_ARB_texture_rectangle")||glewIsSupported("GL_EXT_texture_rectangle")))
	{
		
		ADD_LOG_Q("Can not suppot GL_ARB_texture_rectangle and GL_EXT_texture_rectangle,Bloom disable","#0000FF");
		GameSet.Bloom=0;
	}
	FBOWinW=winW;
	FBOWinH=winH;
	ScreemTexW=winW;
	ScreemTexH=winH;
	BloomTexW=480;
	BloomTexH=480*winH/winW;

	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT,&MAX_COLOR_ATTACHMENTS);

	/*if(GameSet.SSAO>0)
	{
		SSAOTex1=InitTex2D(ScreemTexW/2, ScreemTexH/2,GL_LINEAR,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE,GL_TEXTURE_RECTANGLE);
		SSAOTex2=InitTex2D(ScreemTexW/2, ScreemTexH/2,GL_LINEAR,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE,GL_TEXTURE_RECTANGLE);
	}*/
	glGenFramebuffersEXT(1, &FBOID);
	ScreemTex=InitTex2D(FBOWinW, FBOWinH,GL_LINEAR,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE,GL_TEXTURE_RECTANGLE);
	//ScreemTexDepth=InitTex2D(ScreemTexW, ScreemTexH,GL_LINEAR,GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE);
	TextTex=InitTex2D(2048,1024,GL_LINEAR,GL_RGBA,GL_RGBA,GL_UNSIGNED_BYTE);
	if((GameSet.Shadow>0)||(GameSet.Light>1))
	{ 
		ADD_LOG_Q("Create Shadow FBO Start");
		ShadowTexSize=512<<max(GameSet.Shadow-1,0);
		ShadowTexDepthSize[0]=float(ShadowTexSize);
		ShadowTexDepthSize[1]=float(ShadowTexSize);
		ShadowTex=InitTex2D(ShadowTexSize,ShadowTexSize,GL_LINEAR,GL_RED,GL_ALPHA,GL_UNSIGNED_BYTE);
		ShadowTexDepth=InitTex2D(ShadowTexSize, ShadowTexSize,GL_LINEAR,GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE);
		glGenFramebuffersEXT(1,&ShadowFBOID);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, ShadowFBOID);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, ShadowTex, 0); 
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,  GL_TEXTURE_2D, ShadowTexDepth,0);
		GameSet.Shadow=CheckFBOError()==true?GameSet.Shadow:0;
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		if(GameSet.Shadow==0) ADD_LOG_Q("Can not create Shadow FBO,Shadow disable","#0000FF");
		ADD_LOG_Q("Create Shadow FBO End");
	}
	if(GameSet.Shadow==0)
	{
		float ShadowTexData[]={1.0f};
		glGenTextures(1, &ShadowTexDepth);
		glBindTexture(GL_TEXTURE_2D, ShadowTexDepth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,  1, 1, 0, GL_DEPTH_COMPONENT, GL_FLOAT, ShadowTexData);//GL_RGBA16F_ARB
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	if(GameSet.Bloom>0)
	{
		ADD_LOG_Q("Create Bloom FBO Start");
		GLuint BloomTexFormatISet=GL_RGBA;
		/*if(BloomSet==2) BloomTexFormatISet=GL_RGBA16F_ARB;
		if(BloomSet>=3) BloomTexFormatISet=GL_RGBA32F_ARB;*/

		BloomTex1=InitTex2D(BloomTexW, BloomTexH,GL_LINEAR,BloomTexFormatISet,GL_ALPHA,GL_UNSIGNED_BYTE,GL_TEXTURE_RECTANGLE);
		BloomTex2=InitTex2D(BloomTexW, BloomTexH,GL_LINEAR,BloomTexFormatISet,GL_ALPHA,GL_UNSIGNED_BYTE,GL_TEXTURE_RECTANGLE);
		
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOID);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE, BloomTex1, 0); 
		GameSet.Bloom=CheckFBOError()==true?GameSet.Bloom:0;
		if(GameSet.Bloom==0) ADD_LOG_Q("Can not create Bloom FBO,Bloom disable","#0000FF");
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE, BloomTex2, 0);
		GameSet.Bloom=CheckFBOError()==true?GameSet.Bloom:0;
		if(GameSet.Bloom==0) ADD_LOG_Q("Can not create Bloom FBO,Bloom disable","#0000FF");
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		ADD_LOG_Q("Create Bloom FBO End");
	}
	BlurTexID[0]=InitTex2D(GameSet.winW, GameSet.winH,GL_LINEAR,GL_RGB,GL_RGB,GL_UNSIGNED_BYTE,GL_TEXTURE_RECTANGLE);
	BlurTexID[1]=InitTex2D(GameSet.winW, GameSet.winH,GL_LINEAR,GL_RGB,GL_RGB,GL_UNSIGNED_BYTE,GL_TEXTURE_RECTANGLE);


	//StarTex1=InitTex2D(StarTexSizeX, StarTexSizeY,GL_LINEAR,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE);
	//StarTex2=InitTex2D(StarTexSizeX, StarTexSizeY,GL_LINEAR,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE);
	//StarTexDepth=InitTex2D(StarTexSizeX, StarTexSizeY,GL_NEAREST,GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE);
//	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	//FBOS_Star_Begin();
	//FBOS_Star_End();
	return true;
}
void DeinitFBO()
{
	if(!SuppotFBO) return;
	SuppotFBO=false;

	if(FBOID) glDeleteFramebuffersEXT(1,&FBOID);

	if(ScreemTex) glDeleteTextures(1,&ScreemTex);
	if(ScreemTexDepth) glDeleteTextures(1,&ScreemTexDepth);

	if(StarTex1) glDeleteTextures(1,&StarTex1);
	if(StarTex2) glDeleteTextures(1,&StarTex2);
	if(StarTexDepth) glDeleteTextures(1,&StarTexDepth);

	if(BloomTex1) glDeleteTextures(1,&BloomTex1);
	if(BloomTex2) glDeleteTextures(1,&BloomTex2);

	if(SSAOTex1) glDeleteTextures(1,&SSAOTex1);
	if(SSAOTex2) glDeleteTextures(1,&SSAOTex2);

	if(ShadowFBOID) glDeleteFramebuffersEXT(1,&ShadowFBOID);
	
	if(ShadowTex) glDeleteTextures(1,&ShadowTex);
	if(ShadowTexDepth) glDeleteTextures(1,&ShadowTexDepth);
}
/*
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
		glBindTexture(GL_TEXTURE_2D, SSAOTex1);

		//glColor3f(0.1f,0.1f,1.0f);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,ScreemTexH);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i(ScreemTexW ,ScreemTexH);
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
}*/
void FBOS_BLOOM()
{
	if(!GameSet.Bloom) return;
	if(MAX_COLOR_ATTACHMENTS<1) return;

	glEnable(GL_TEXTURE_RECTANGLE);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_RECTANGLE, ScreemTex);
	glCopyTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, 0, 0,FBOWinW, FBOWinH, 0);

	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0,0,BloomTexW, BloomTexH);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOID);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE, BloomTex1, 0);

	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glClear (GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	
	glEnableVertexAttribArray(AbLoc_Tex0);
	glEnableVertexAttribArray(AbLoc_Pos);
	CO_MatrixOrthogonalProjection(0.0,float(BloomTexW),0.0,float(BloomTexH),-1.0,1.0,FBOMatrixTMP);
	GLSL_Enable_Bloom_Map();
	GLSL_SetMVPMatrixToGlsl(FBOMatrixTMP);
	DrawQUAD_Att(0,BloomTexW,BloomTexH,0,AbLoc_Tex0,AbLoc_Pos,FBOWinW,FBOWinH);

	
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE, BloomTex2, 0);
	glBindTexture(GL_TEXTURE_RECTANGLE, BloomTex1);
	GLSL_Enable_Bloom_BlurTex(1.0f,true);
	GLSL_SetMVPMatrixToGlsl(FBOMatrixTMP);
	DrawQUAD_Att(0,BloomTexW,BloomTexH,0,AbLoc_Tex0,AbLoc_Pos,BloomTexW,BloomTexH);
	
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE, BloomTex1, 0);
	glBindTexture(GL_TEXTURE_RECTANGLE, BloomTex2);
	GLSL_Enable_Bloom_BlurTex(1.0f,false);
	GLSL_SetMVPMatrixToGlsl(FBOMatrixTMP);
	DrawQUAD_Att(0,BloomTexW,BloomTexH,0,AbLoc_Tex0,AbLoc_Pos,BloomTexW,BloomTexH);
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	glPopAttrib();
	glBindTexture(GL_TEXTURE_RECTANGLE, BloomTex1);
	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );

	CO_MatrixOrthogonalProjection(0,float(FBOWinW),0,float(FBOWinH),-1.0,1.0,FBOMatrixTMP);
	GLSL_Enable_Bloom_ToneMapping();
	GLSL_SetMVPMatrixToGlsl(FBOMatrixTMP);
	DrawQUAD_Att(0,FBOWinW,FBOWinH,0,AbLoc_Tex0,AbLoc_Pos,BloomTexW,BloomTexH);
	GLSL_Disable();
	glDisableVertexAttribArray(AbLoc_Tex0);
	glDisableVertexAttribArray(AbLoc_Pos);

	glDisable(GL_TEXTURE_RECTANGLE);
	glEnable( GL_CULL_FACE );
	glEnable(GL_DEPTH_TEST);
	
}
/*
void FBOS_Star_Begin()
{
	
	glBindTexture(GL_TEXTURE_2D, ScreemTexDepth);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0 ,ScreemTexW, ScreemTexH, 0);

	glPushAttrib(GL_VIEWPORT_BIT);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOID);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, ScreemTex, 0);
	//CheckFBOError();
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, ScreemTexDepth, 0);
	//CheckFBOError();
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glClear (GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable( GL_BLEND );
	glEnable( GL_CULL_FACE );
	glViewport(0,0,FBOWinW, FBOWinH);
	
	//glPushAttrib(GL_VIEWPORT_BIT);
	//glViewport(0,0,1024, 1024);
	//glClear (GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();	
	//glLoadIdentity();	
	
}
void FBOS_Star_End()
{
	
	//glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	//glPopMatrix();	
	//glPopAttrib();
	
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex1, 0);
	//CheckFBOError();
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, StarTexDepth, 0);
	//CheckFBOError();
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
	//CheckFBOError();
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
	//CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex2);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i(StarTexSizeX ,StarTexSizeY);
				glTexCoord2f(1.0f,	0.0f);	glVertex2i(StarTexSizeX, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();
	glDisable(GL_BLEND);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex2, 0);
	//CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i(StarTexSizeX/4 ,StarTexSizeY);
				glTexCoord2f(1.0f,	0.0f);	glVertex2i(StarTexSizeX/4, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();
	glEnable(GL_BLEND);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex1, 0);
	//CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex2);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f/4.0f,	1.0f);	glVertex2i(StarTexSizeX ,StarTexSizeY);
				glTexCoord2f(1.0f/4.0f,	0.0f);	glVertex2i(StarTexSizeX, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();
	glDisable(GL_BLEND);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex2, 0);
	//CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i(StarTexSizeX/8 ,StarTexSizeY);
				glTexCoord2f(1.0f,	0.0f);	glVertex2i(StarTexSizeX/8, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();
	glEnable(GL_BLEND);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex1, 0);
	//CheckFBOError();
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
	//CheckFBOError();
	glBindTexture(GL_TEXTURE_2D, StarTex1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,	1.0f);	glVertex2i( 0,StarTexSizeY);
				glTexCoord2f(1.0f,	1.0f);	glVertex2i(StarTexSizeX/2 ,StarTexSizeY);
				glTexCoord2f(1.0f,	0.0f);	glVertex2i(StarTexSizeX/2, 0);
				glTexCoord2f(0.0f,	0.0f);	glVertex2i( 0, 0);
			glEnd();

	glEnable(GL_BLEND);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, StarTex1, 0);
	//CheckFBOError();
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
void FBOS_SSAO()
{
	glBindTexture(GL_TEXTURE_2D, ScreemTexDepth);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0 ,ScreemTexW, ScreemTexH, 0);
	glPushAttrib(GL_VIEWPORT_BIT);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOID);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, SSAOTex1, 0);
	//CheckFBOError();
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glViewport(0,0,FBOWinW/2, FBOWinH/2);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);					
	glPushMatrix();	
	glLoadIdentity();
	glOrtho(0,FBOWinW/2,0,FBOWinH/2,-1,1);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();	
	glLoadIdentity();

	float TCX=float(FBOWinW)/float(ScreemTexW);
	float TCY=float(FBOWinH)/float(ScreemTexH);
	float SSAOset[4]={float(FBOWinW),float(FBOWinH),5.0f,100000.0f};
	GLSL_Enable_SSAOPass1(SSAOset);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);glVertex2i(0,0);
				glTexCoord2f(TCX,0.0f);glVertex2i( FBOWinW/2,0);
				glTexCoord2f(TCX,TCY);glVertex2i( FBOWinW/2, FBOWinH/2);
				glTexCoord2f(0.0f,TCY);glVertex2i(0, FBOWinH/2);
			glEnd();
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, SSAOTex2, 0);
	glBindTexture(GL_TEXTURE_2D, SSAOTex1);
	GLSL_Enable_BlurTex(FBOWinW,true);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);glVertex2i(0,0);
				glTexCoord2f(TCX,0.0f);glVertex2i( FBOWinW/2,0);
				glTexCoord2f(TCX,TCY);glVertex2i( FBOWinW/2, FBOWinH/2);
				glTexCoord2f(0.0f,TCY);glVertex2i(0, FBOWinH/2);
			glEnd();
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, SSAOTex1, 0);
	glBindTexture(GL_TEXTURE_2D, SSAOTex2);
	GLSL_Enable_BlurTex(FBOWinH,false);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);glVertex2i(0,0);
				glTexCoord2f(TCX,0.0f);glVertex2i( FBOWinW/2,0);
				glTexCoord2f(TCX,TCY);glVertex2i( FBOWinW/2, FBOWinH/2);
				glTexCoord2f(0.0f,TCY);glVertex2i(0, FBOWinH/2);
			glEnd();

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glPopAttrib();

	GLSL_Disable();
	glEnable( GL_BLEND );
	glBlendFunc(GL_ZERO,GL_ONE_MINUS_SRC_ALPHA   );
	glBindTexture(GL_TEXTURE_2D, SSAOTex1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);glVertex2i(0,0);
				glTexCoord2f(TCX,0.0f);glVertex2i( FBOWinW/2,0);
				glTexCoord2f(TCX,TCY);glVertex2i( FBOWinW/2, FBOWinH/2);
				glTexCoord2f(0.0f,TCY);glVertex2i(0, FBOWinH/2);
			glEnd();
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();	
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();
	glEnable( GL_CULL_FACE );
	glEnable(GL_DEPTH_TEST);
}
*/
void DrawUnitText(wchar_t * UnitText)
{
	glEnable(GL_TEXTURE_2D);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOID);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE, TextTex, 0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glClear (GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0,0,2048, 1024);
	
	glMatrixMode(GL_PROJECTION);glPushMatrix();GLfloat DrawTextMatrix[16]; CO_MatrixOrthogonalProjection(0.0f,2048,0.0f,1024,-1.0f,1.0f,DrawTextMatrix); glLoadMatrixf(DrawTextMatrix);
	glMatrixMode(GL_MODELVIEW); glPushMatrix();glLoadIdentity(); //glTranslatef((float)PosX,(float)PosY,0.0f);
	
	//SceneFont.DrawTexts(UnitText,0,512-32,1024,512,1024,32);
	glEnable(GL_BLEND);
		glTranslatef(0.0f,1024.0f-64.0f,0.0f);
	TAMFT3D.Draw3DText(UnitText,64,64,2048);
	glEnable(GL_BLEND);

	
	glMatrixMode(GL_MODELVIEW);glPopMatrix();
	glMatrixMode(GL_PROJECTION);glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
	glEnable( GL_CULL_FACE );
	glEnable(GL_DEPTH_TEST);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}
void BlurPass(float blur)
{
	float BlurPassMatrixTMP[16];
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0,0,GameSet.winW, GameSet.winH);
	glEnable(GL_TEXTURE_RECTANGLE);
	glDisable(GL_TEXTURE_2D);
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOID);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE, BlurTexID[0], 0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	//glClear (GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glEnableVertexAttribArray(AbLoc_Tex0);
	glEnableVertexAttribArray(AbLoc_Pos);

	CO_MatrixOrthogonalProjection(0.0,float(GameSet.winW),0.0,float(GameSet.winH),-1.0,1.0,BlurPassMatrixTMP);
	glBindTexture(GL_TEXTURE_RECTANGLE, ScreemTex);
	GLSL_Enable_Bloom_BlurTex(blur,true);
	GLSL_SetMVPMatrixToGlsl(BlurPassMatrixTMP);
	DrawQUAD_Att(0,GameSet.winW,GameSet.winH,0,AbLoc_Tex0,AbLoc_Pos,GameSet.winW,GameSet.winH);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE, BlurTexID[1], 0);
	glBindTexture(GL_TEXTURE_RECTANGLE, BlurTexID[0]);
	GLSL_Enable_Bloom_BlurTex(blur,false);
	GLSL_SetMVPMatrixToGlsl(BlurPassMatrixTMP);
	DrawQUAD_Att(0,GameSet.winW,GameSet.winH,0,AbLoc_Tex0,AbLoc_Pos,GameSet.winW,GameSet.winH);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE, BlurTexID[0], 0);
	glBindTexture(GL_TEXTURE_RECTANGLE, BlurTexID[1]);
	GLSL_Enable_Bloom_BlurTex(blur/4.0f,true);
	GLSL_SetMVPMatrixToGlsl(BlurPassMatrixTMP);
	DrawQUAD_Att(0,GameSet.winW,GameSet.winH,0,AbLoc_Tex0,AbLoc_Pos,GameSet.winW,GameSet.winH);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE, BlurTexID[1], 0);
	glBindTexture(GL_TEXTURE_RECTANGLE, BlurTexID[0]);
	GLSL_Enable_Bloom_BlurTex(blur/4.0f,false);
	GLSL_SetMVPMatrixToGlsl(BlurPassMatrixTMP);
	DrawQUAD_Att(0,GameSet.winW,GameSet.winH,0,AbLoc_Tex0,AbLoc_Pos,GameSet.winW,GameSet.winH);

	GLSL_Disable();
	glDisableVertexAttribArray(AbLoc_Tex0);
	glDisableVertexAttribArray(AbLoc_Pos);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glPopAttrib();
	DrawQUADEX_RECT(BlurTexID[1],0,GameSet.winW,GameSet.winH,0,GameSet.winW,GameSet.winH);
	//DrawQUADEX_RECT(ScreemTex,0,GameSet.winW,GameSet.winH,0,GameSet.winW,GameSet.winH);
	//DrawQUADEX(BlurTexID[1],0,GameSet.winW,0,GameSet.winH,GameSet.winW,GameSet.winH);
	glDisable(GL_TEXTURE_RECTANGLE);
	glEnable( GL_CULL_FACE );
	glEnable(GL_DEPTH_TEST);
}
float blurtime=-1.0f;
extern float blurSet[4];
void BlurPass()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	float blurnumtmp1=blurSet[0]-blurSet[1];
	blurnumtmp1=blurnumtmp1*(blurSet[3]/blurSet[2]);
//	if(blurSet[3]>0.0f)
	blurnumtmp1=blurSet[1]+blurnumtmp1;
	if(blurnumtmp1>0.0f)
	BlurPass(blurnumtmp1);
	blurSet[3]=max(0.0f,blurSet[3]-1.0f);
	glPopAttrib();
}