#include "GLSLLoader.h"

#include <stdio.h>	
#include <windows.h>
#include "FileSysBace.h"
#include "CharSysBace.h"
#define ShaderPath L"data/shader/GLSL/"
CGLSLLoader::CGLSLLoader(void)
{
	g_VS=0;
	g_PS=0;
	g_PO=0;
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
		GLSLLOG.AddLOG("****** GLSL ERROR ******");
		GLSLLOG.AddLOG("Cannot open shader file");
		GLSLLOG.AddLOG(shaderfilenameANSI);
		GLSLLOG.WriteLOGFile(true);
		GLSLLOG.ClearLOG();
		delete [] shaderfilenameANSI;
		return 0;
	}
	GLSLLOG.AddLOG("****** GLSL Loading File ******");
	GLSLLOG.AddLOG(shaderfilenameANSI);
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
	{
		char * logbuffer=GetGLSLInfoLog(GLSLShaderObject);
		GLSLLOG.AddLOG("****** GLSL ERROR ******");
		GLSLLOG.AddLOG(logbuffer);
		GLSLLOG.WriteLOGFile(true);
		GLSLLOG.ClearLOG();
		delete[] logbuffer;
	}
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
		GLSLLOG.AddLOG("****** GLSL ERROR ******");
		GLSLLOG.AddLOG(logbuffer);
		GLSLLOG.WriteLOGFile(true);
		GLSLLOG.ClearLOG();
		delete[] logbuffer;
		/*char str[40960];
		glGetInfoLogARB( g_programObj, sizeof(str), NULL, str );
		MessageBox( NULL, "Error Message saving to Error.log", "Linking Error", MB_OK|MB_ICONEXCLAMATION );
		//WritePrivateProfileString("Glsl","Linking_Error",str,".\\Error_log.ini");
		HANDLE   hFile;     
      
		hFile   =   CreateFileW(L".\\Error.log",                       //   open   MYFILE.TXT     
                                  GENERIC_WRITE,                             //   open   for   reading     
                                  FILE_SHARE_READ,                       //   share   for   reading     
                                  NULL,                                             //   no   security     
                                  CREATE_ALWAYS,                           //   existing   file   only     
                                  FILE_ATTRIBUTE_NORMAL,           //   normal   file     
                                  NULL);
		str[40959]=0;
		DWORD savesize=0;
		WriteFile(hFile,str,min(40959,strlen(str)),&savesize,NULL);
		CloseHandle(hFile);*/
		return false;
	}
	else
	{
		char * logbuffer=GetGLSLInfoLog(g_programObj);
		GLSLLOG.AddLOG("****** GLSL Log ******");
		GLSLLOG.AddLOG(logbuffer);
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
	if((g_PO>0)&&(g_VS>0)) glDetachObjectARB(g_PO,g_VS);
	if((g_PO>0)&&(g_PS>0)) glDetachObjectARB(g_PO,g_PS);
	if(g_PO>0) glDeleteObjectARB(g_PO);
	if(g_VS>0) glDeleteObjectARB(g_VS);
	if(g_PS>0) glDeleteObjectARB(g_PS);
	g_VS=0;
	g_PS=0;
	g_PO=0;
}

bool CGLSLLoader::LoadShader(const wchar_t* ShaderName,int LightSet)
{
	if(!ShaderName)
		return false;
	if(LightSet<2)
		return false;
	wchar_t* ShaderFullName=NULL;
	wchar_t* ShaderFullNameTMP=NULL;
	if(LightSet>=3)
	{
		ShaderFullNameTMP=ADDTwoChar(ShaderPath,L"SM4/");
		ShaderFullName=ADDTwoChar(ShaderFullNameTMP,ShaderName);
		if(LoadShader2(ShaderFullName))
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
	if(LoadShader2(ShaderFullName))
	{
		delete[] ShaderFullNameTMP;
		delete[] ShaderFullName;
		return true;
	}
	delete[] ShaderFullNameTMP;
	delete[] ShaderFullName;
	return false;
}

bool CGLSLLoader::LoadShader2(const wchar_t* ShaderName)
{
	if(!ShaderName)
		return false;
	ClearShader();
	wchar_t* VSfilename=ADDTwoChar(ShaderName,L".vs");g_VS=CompileShader(VSfilename,GL_VERTEX_SHADER_ARB);
	wchar_t* PSfilename=ADDTwoChar(ShaderName,L".ps");g_PS=CompileShader(PSfilename,GL_FRAGMENT_SHADER_ARB);
	delete[] VSfilename;
	delete[] PSfilename;
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
