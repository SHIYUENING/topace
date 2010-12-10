#include "GLSLLoader.h"

#include <stdio.h>	
#include <windows.h>
#include "FileSysBace.h"
#include "CharSysBace.h"
#define ShaderPath L"data/shader/GLSL/"
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

char * CGLSLLoader::GetGLSLInfoLog(GLhandleARB GLSLShaderObject)
{
	int logreadsize=0;
	int logbuffersize=0x800;
	glGetObjectParameterivARB(GLSLShaderObject, GL_OBJECT_INFO_LOG_LENGTH_ARB,&logbuffersize);
	char * logbuffer=new char [logbuffersize+1];
	glGetInfoLogARB(GLSLShaderObject, logbuffersize,&logreadsize, logbuffer);
	logbuffer[logbuffersize]=0;
	return logbuffer;
}
GLhandleARB CGLSLLoader::CompileShader(const wchar_t* shaderfilename,GLenum ShaderObject)
{
	GLhandleARB GLhandleARBTMP=0;
	char * GLSLFileBuffer=ReadLocFullFile_ANSI_TXT(shaderfilename);
	int dwNum=WideCharToMultiByte(CP_ACP,0,shaderfilename,-1,NULL,0,NULL,NULL);
	char * shaderfilenameANSI=new char[dwNum];
	WideCharToMultiByte(CP_ACP,0,shaderfilename,-1,shaderfilenameANSI,dwNum,NULL,NULL);
	if(!GLSLFileBuffer)
	{
		GLSLLOG.AddLOG("\n  ****** GLSL ERROR ******\n    ");
		GLSLLOG.AddLOG("Cannot open shader file");
		GLSLLOG.AddLOG(shaderfilenameANSI);
		GLSLLOG.WriteLOGFile(true);
		GLSLLOG.ClearLOG();
		delete [] shaderfilenameANSI;
		return 0;
	}
	GLSLLOG.AddLOG("\n  ****** GLSL Loading File ******\n    ");
	GLSLLOG.AddLOG(shaderfilenameANSI,true);
	GLhandleARBTMP = CompileShader(GLSLFileBuffer,ShaderObject);
	
	delete [] shaderfilenameANSI;
	delete [] GLSLFileBuffer;
	return GLhandleARBTMP;
}
GLhandleARB CGLSLLoader::CompileShader(char *ShaderAssembly,GLenum ShaderObject)
{
	GLhandleARB GLSLShaderObject=glCreateShaderObjectARB(ShaderObject);
	glShaderSourceARB( GLSLShaderObject, 1, (const GLcharARB **)(&ShaderAssembly), NULL );
	glCompileShaderARB( GLSLShaderObject);
	GLint bCompiled=0;
	glGetObjectParameterivARB( GLSLShaderObject, GL_OBJECT_COMPILE_STATUS_ARB, &bCompiled );
	if(!bCompiled)
		GLSLLOG.AddLOG("\n  ****** GLSL ERROR ******\n    ");
	else
		GLSLLOG.AddLOG("\n  ****** GLSL Log ******\n    ");
	char * logbuffer=GetGLSLInfoLog(GLSLShaderObject);
	GLSLLOG.AddLOG(logbuffer,true);
	GLSLLOG.WriteLOGFile(true);
	GLSLLOG.ClearLOG();
	delete[] logbuffer;
	return GLSLShaderObject;
}
bool CGLSLLoader::GetGLSLLinkSTATUS(GLhandleARB g_programObj)
{
	GLint bLinked=false;
	glLinkProgramARB( g_programObj );
	glGetObjectParameterivARB( g_programObj, GL_OBJECT_LINK_STATUS_ARB, &bLinked );

	if( bLinked == false )
	{
		char * logbuffer=GetGLSLInfoLog(g_programObj);
		GLSLLOG.AddLOG("\n  ****** GLSL ERROR ******\n    ");
		GLSLLOG.AddLOG(logbuffer,true);
		GLSLLOG.WriteLOGFile(true);
		GLSLLOG.ClearLOG();
		delete[] logbuffer;
		return false;
	}
	else
	{
		char * logbuffer=GetGLSLInfoLog(g_programObj);
		GLSLLOG.AddLOG("\n  ****** GLSL Log ******\n    ");
		GLSLLOG.AddLOG(logbuffer,true);
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
