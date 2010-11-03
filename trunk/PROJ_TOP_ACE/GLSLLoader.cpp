#include "GLSLLoader.h"

#include <stdio.h>	
#include <windows.h>
#include "FileSysBace.h"

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
	char * logbuffer=new char [logbuffersize];
	glGetInfoLogARB(GLSLShaderObject, logbuffersize,&logreadsize, logbuffer);
	while(logbuffersize<=logreadsize)
	{
		logbuffersize=logbuffersize*2;
		delete[] logbuffer;
		if(logbuffersize>0x10000)
			break;
		logbuffer=new char [logbuffersize];
		glGetInfoLogARB(GLSLShaderObject, logbuffersize,&logreadsize, logbuffer);
	}
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
//
// Link the program object and print out the info log...
//
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


GLhandleARB CGLSLLoader::GetPO(void)
{
	return g_PO;
}
