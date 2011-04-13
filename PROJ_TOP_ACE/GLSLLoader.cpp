#include "GLSLLoader.h"
#include <stdio.h>	
#include <windows.h>
#include "FileSysBace.h"
#include "CharSysBace.h"
#include "Glsl.h"
char * GetGLSLInfoLog(GLhandleARB GLSLShaderObject)
{
	int logreadsize=0;
	int logbuffersize=0x800;
	glGetObjectParameterivARB(GLSLShaderObject, GL_OBJECT_INFO_LOG_LENGTH_ARB,&logbuffersize);
	if(logbuffersize<=0) return 0;
	char * logbuffer=new char [logbuffersize+1];
	glGetInfoLogARB(GLSLShaderObject, logbuffersize,&logreadsize, logbuffer);
	logbuffer[logbuffersize]=0;
	return logbuffer;
}
GLhandleARB CompileShader(const wchar_t* shaderfilename,GLenum ShaderObject)
{
	CTALogSys TALogSysCS;
	GLhandleARB GLhandleARBTMP=0;
	char * GLSLFileBuffer=ReadLocFullFile_ANSI_TXT(shaderfilename);
	int dwNum=WideCharToMultiByte(CP_ACP,0,shaderfilename,-1,NULL,0,NULL,NULL);
	char * shaderfilenameANSI=new char[dwNum];
	WideCharToMultiByte(CP_ACP,0,shaderfilename,-1,shaderfilenameANSI,dwNum,NULL,NULL);
	if(!GLSLFileBuffer)
	{
		TALogSysCS.ADDLinkLOG("ERROR:Cannot open shader file ","#FF0000",shaderfilenameANSI);
		TALogSysCS.WriteLOGFile(true);
		TALogSysCS.ClearLOG();
		delete [] shaderfilenameANSI;
		return 0;
	}
	TALogSysCS.ADDLinkLOG("Loading File :","#000000",shaderfilenameANSI);
	GLint bCompiled=0;
	GLhandleARBTMP = CompileShader(GLSLFileBuffer,ShaderObject,&bCompiled);
	if(!bCompiled) TALogSysCS.ADDhtmLog("ERROR: GLSL Compile Fail.","#FF0000");
	TALogSysCS.ADDhtmLog("GLSL Compile LOG:");
	char * logbuffer=GetGLSLInfoLog(GLhandleARBTMP);
	TALogSysCS.ADDhtmLog(logbuffer);
	TALogSysCS.WriteLOGFile(true);
	TALogSysCS.ClearLOG();
	delete [] logbuffer;
	delete [] shaderfilenameANSI;
	delete [] GLSLFileBuffer;
	return GLhandleARBTMP;
}
GLhandleARB CompileShader(char *ShaderAssembly,GLenum ShaderObject,GLint * bCompiled)
{
	GLhandleARB GLSLShaderObject=glCreateShaderObjectARB(ShaderObject);
	glShaderSourceARB( GLSLShaderObject, 1, (const GLcharARB **)(&ShaderAssembly), NULL );
	glCompileShaderARB( GLSLShaderObject);
	glGetObjectParameterivARB( GLSLShaderObject, GL_OBJECT_COMPILE_STATUS_ARB, bCompiled );
	return GLSLShaderObject;
}
bool LinkShader(GLhandleARB GLSL_programObj)
{
	GLint bLinked=0;
	glLinkProgramARB( GLSL_programObj );
	glGetObjectParameterivARB( GLSL_programObj, GL_OBJECT_LINK_STATUS_ARB, &bLinked );
	return bLinked!=0?true:false;
}
bool CGLSL_Light_Link_ProgramObject(GLhandleARB GLSL_PO)
{
	GLint bLinked=0;
	glLinkProgramARB( GLSL_PO );
	glGetObjectParameterivARB( GLSL_PO, GL_OBJECT_LINK_STATUS_ARB, &bLinked );
	CTALogSys TALogSysCS;
	if(!bLinked) TALogSysCS.ADDhtmLog("ERROR: GLSL Link Fail.","#FF0000");
	TALogSysCS.ADDhtmLog("GLSL Link LOG");
	char * logbuffer=GetGLSLInfoLog(GLSL_PO);
	TALogSysCS.ADDhtmLog(logbuffer);
	TALogSysCS.WriteLOGFile(true);
	TALogSysCS.ClearLOG();
	delete[] logbuffer;
	return bLinked!=0?true:false;
}
bool CGLSL_Light_Link(GLhandleARB * GLSL_PO,GLhandleARB Attach_VS,GLhandleARB Attach_TC,GLhandleARB Attach_TE,GLhandleARB Attach_GS,GLhandleARB Attach_PS)
{
	if(!GLSL_PO) return false;
	GLSL_PO[0]=glCreateProgramObjectARB();
	if(Attach_VS) glAttachObjectARB(GLSL_PO[0],Attach_VS);
	if(Attach_TC) glAttachObjectARB(GLSL_PO[0],Attach_TC);
	if(Attach_TE) glAttachObjectARB(GLSL_PO[0],Attach_TE);
	if(Attach_GS) glAttachObjectARB(GLSL_PO[0],Attach_GS);
	if(Attach_PS) glAttachObjectARB(GLSL_PO[0],Attach_PS);
	glBindAttribLocation(GLSL_PO[0],AbLoc_Pos, "Position_in" );
	glBindAttribLocation(GLSL_PO[0],AbLoc_Tex0, "TexCoord0_in" );
	glBindAttribLocation(GLSL_PO[0],AbLoc_Normal, "Normal_in" );
	glBindAttribLocation(GLSL_PO[0],AbLoc_Color, "Color_in" );
	glBindAttribLocation(GLSL_PO[0],AbLoc_Tangent, "Tangent_in" );
	GLint bLinked=0;
	glLinkProgramARB( GLSL_PO[0] );
	glGetObjectParameterivARB( GLSL_PO[0], GL_OBJECT_LINK_STATUS_ARB, &bLinked );
	CTALogSys TALogSysCS;
	if(bLinked) TALogSysCS.ADDhtmLog("GLSL Link LOG");
	else TALogSysCS.ADDhtmLog("ERROR: GLSL Link Fail.","#FF0000");
	char * logbuffer=GetGLSLInfoLog(GLSL_PO[0]);
	TALogSysCS.ADDhtmLog(logbuffer);
	TALogSysCS.WriteLOGFile(true);
	TALogSysCS.ClearLOG();
	delete[] logbuffer;
	return bLinked!=0?true:false;
}
void CGLSL_Light_Attach(GLhandleARB * GLSL_PO,GLhandleARB Attach_VS,GLhandleARB Attach_TC,GLhandleARB Attach_TE,GLhandleARB Attach_GS,GLhandleARB Attach_PS)
{
	if(!GLSL_PO) return;
	GLSL_PO[0]=glCreateProgramObjectARB();
	if(Attach_VS) glAttachObjectARB(GLSL_PO[0],Attach_VS);
	if(Attach_TC) glAttachObjectARB(GLSL_PO[0],Attach_TC);
	if(Attach_TE) glAttachObjectARB(GLSL_PO[0],Attach_TE);
	if(Attach_GS) glAttachObjectARB(GLSL_PO[0],Attach_GS);
	if(Attach_PS) glAttachObjectARB(GLSL_PO[0],Attach_PS);
}
void ClearShaderObject(GLhandleARB GLSL_PO,GLhandleARB Attach_VS,GLhandleARB Attach_TC,GLhandleARB Attach_TE,GLhandleARB Attach_GS,GLhandleARB Attach_PS)
{
	if(glIsProgram(GLSL_PO)!=GL_FALSE)
	{
		if(glIsShader(Attach_VS)!=GL_FALSE){ glDetachObjectARB(GLSL_PO,Attach_VS);}
		if(glIsShader(Attach_TC)!=GL_FALSE){ glDetachObjectARB(GLSL_PO,Attach_TC);}
		if(glIsShader(Attach_TE)!=GL_FALSE){ glDetachObjectARB(GLSL_PO,Attach_TE);}
		if(glIsShader(Attach_GS)!=GL_FALSE){ glDetachObjectARB(GLSL_PO,Attach_GS);}
		if(glIsShader(Attach_PS)!=GL_FALSE){ glDetachObjectARB(GLSL_PO,Attach_PS);}
		glDeleteObjectARB(GLSL_PO);
	}
}
void DelShader(GLhandleARB ShaderOBJ)
{
	if(glIsShader(ShaderOBJ)!=GL_FALSE) glDeleteObjectARB(ShaderOBJ);
}
CGLSLLoader::CGLSLLoader(void)
	:g_VS(0)
	,g_TC(0)
	,g_TE(0)
	,g_GS(0)
	,g_PS(0)
{
}
CGLSLLoader::~CGLSLLoader(void)
{
	ClearShader();
	GLSLLOG.ClearLOG();
}
bool CGLSLLoader::GetGLSLLinkSTATUS(GLhandleARB g_programObj)
{
	GLint bLinked=false;
	glLinkProgramARB( g_programObj );
	glGetObjectParameterivARB( g_programObj, GL_OBJECT_LINK_STATUS_ARB, &bLinked );

	if( bLinked == false )
	{
		char * logbuffer=GetGLSLInfoLog(g_programObj);
		GLSLLOG.ADDhtmLog("ERROR: GLSL Link Fail.","#FF0000");
		GLSLLOG.ADDhtmLog(logbuffer);
		GLSLLOG.WriteLOGFile(true);
		GLSLLOG.ClearLOG();
		delete[] logbuffer;
		return false;
	}
	else
	{
		char * logbuffer=GetGLSLInfoLog(g_programObj);
		GLSLLOG.ADDhtmLog("GLSL Link LOG");
		GLSLLOG.ADDhtmLog(logbuffer);
		GLSLLOG.WriteLOGFile(true);
		GLSLLOG.ClearLOG();
		delete[] logbuffer;
	}
	GLSLLOG.ClearLOG();
	return true;
}

bool CGLSLLoader::LoadShader(const wchar_t* VSfilename,const wchar_t* PSfilename)
{
	if((!VSfilename)&&(!PSfilename))
		return false;
	ClearShader();
	if(VSfilename) g_VS=CompileShader(VSfilename,GL_VERTEX_SHADER_ARB);
	if(PSfilename) g_PS=CompileShader(PSfilename,GL_FRAGMENT_SHADER_ARB);
	if((!g_VS)&&(!g_PS))
		return false;
	g_PO = glCreateProgramObjectARB();
	if(g_VS) glAttachObjectARB( g_PO, g_VS );
	if(g_PS) glAttachObjectARB( g_PO, g_PS );
	if(!GetGLSLLinkSTATUS( g_PO ))
	{
		ClearShader();
		return false;
	}
	return true;
}
void CGLSLLoader::ClearShader(void)
{
	if(!g_PO)
		return;
	if(glIsProgram(g_PO)!=GL_FALSE)
	{
		if(glIsShader(g_VS)!=GL_FALSE){ glDetachObjectARB(g_PO,g_VS); glDeleteObjectARB(g_VS);}
		if(glIsShader(g_TC)!=GL_FALSE){ glDetachObjectARB(g_PO,g_TC); glDeleteObjectARB(g_TC);}
		if(glIsShader(g_TE)!=GL_FALSE){ glDetachObjectARB(g_PO,g_TE); glDeleteObjectARB(g_TE);}
		if(glIsShader(g_GS)!=GL_FALSE){ glDetachObjectARB(g_PO,g_GS); glDeleteObjectARB(g_GS);}
		if(glIsShader(g_PS)!=GL_FALSE){ glDetachObjectARB(g_PO,g_PS); glDeleteObjectARB(g_PS);}
		glDeleteObjectARB(g_PS);
	}
	g_VS=0;
	g_TC=0;
	g_TE=0;
	g_GS=0;
	g_PS=0;
	g_PO=0;
}
bool CGLSLLoader::LoadShader(const wchar_t* ShaderName,int ShaderLevel,bool ClearOldShader)
{
	if(ClearOldShader) ClearShader();
	if((!ShaderName)||(ShaderLevel<2)) return false;
	wchar_t* ShaderFullName=NULL;
	wchar_t* ShaderFullNameTMP=NULL;
	if(ShaderLevel>=4)
	{
		ShaderFullNameTMP=ADDTwoChar(ShaderPath,L"SM5/");
		ShaderFullName=ADDTwoChar(ShaderFullNameTMP,ShaderName);
		if(LoadShader2(ShaderFullName,ShaderLevel))
		{
			delete[] ShaderFullNameTMP;
			delete[] ShaderFullName;
			return true;
		}
		delete[] ShaderFullNameTMP;
		delete[] ShaderFullName;
	}
	if(ShaderLevel>=3)
	{
		ShaderFullNameTMP=ADDTwoChar(ShaderPath,L"SM4/");
		ShaderFullName=ADDTwoChar(ShaderFullNameTMP,ShaderName);
		if(LoadShader2(ShaderFullName,min(3,ShaderLevel)))
		{
			delete[] ShaderFullNameTMP;
			delete[] ShaderFullName;
			return true;
		}
		delete[] ShaderFullNameTMP;
		delete[] ShaderFullName;
	}
	ShaderFullNameTMP=ADDTwoChar(ShaderPath,L"SM2/");
	ShaderFullName=ADDTwoChar(ShaderFullNameTMP,ShaderName);
	if(LoadShader2(ShaderFullName,min(2,ShaderLevel)))
	{
		delete[] ShaderFullNameTMP;
		delete[] ShaderFullName;
		return true;
	}
	delete[] ShaderFullNameTMP;
	delete[] ShaderFullName;
	return false;
}
bool CGLSLLoader::LoadShader2(const wchar_t* ShaderFullName,int ShaderLevel)
{
	if(!ShaderFullName) return false;
	if(ShaderLevel>=2)
	if(!g_VS)
	{
		wchar_t* VSfilename=ADDTwoChar(ShaderFullName,L".vs");	
		g_VS=CompileShader(VSfilename,GL_VERTEX_SHADER_ARB);	
		delete[] VSfilename;
	}
	if(ShaderLevel>=4)
	if(!g_TC)
	{
		wchar_t* TCfilename=ADDTwoChar(ShaderFullName,L".tc");	
		g_TC=CompileShader(TCfilename,GL_TESS_CONTROL_SHADER);	
		delete[] TCfilename;
	}
	if(ShaderLevel>=4)
	if(!g_TE)
	{
		wchar_t* TEfilename=ADDTwoChar(ShaderFullName,L".te");	
		g_TE=CompileShader(TEfilename,GL_TESS_EVALUATION_SHADER);	
		delete[] TEfilename;
	}
	if(ShaderLevel>=3)
	if(!g_GS)
	{
		wchar_t* GSfilename=ADDTwoChar(ShaderFullName,L".gs");	
		g_GS=CompileShader(GSfilename,GL_GEOMETRY_SHADER);	
		delete[] GSfilename;
	}
	if(ShaderLevel>=2)
	if(!g_PS)
	{
		wchar_t* PSfilename=ADDTwoChar(ShaderFullName,L".ps");	
		g_PS=CompileShader(PSfilename,GL_FRAGMENT_SHADER_ARB);	
		delete[] PSfilename;
	}
	g_PO = glCreateProgramObjectARB();
	if(ShaderLevel>=2) if(g_VS) glAttachObjectARB( g_PO, g_VS );
	if(ShaderLevel>=4) if(g_TC) glAttachObjectARB( g_PO, g_TC );
	if(ShaderLevel>=4) if(g_TE) glAttachObjectARB( g_PO, g_TE );
	if(ShaderLevel>=3) if(g_GS) glAttachObjectARB( g_PO, g_GS );
	if(ShaderLevel>=2) if(g_PS) glAttachObjectARB( g_PO, g_PS );
	if(!GetGLSLLinkSTATUS( g_PO ))
	{
		ClearShader();
		return false;
	}
	return true;
}
