//#pragma once
#ifndef _GLSLLOADER_H
#define _GLSLLOADER_H
#include <GL/glew.h>
#include "GLSL_Light.h"
#include "GLSL_Bloom.h"
#include "GLSL_Shadow.h"
#include "TALogSys.h"
#define ShaderPath L"data/shader/GLSL/"
GLhandleARB CompileShader(const wchar_t* shaderfilename,GLenum ShaderObject);
GLhandleARB CompileShader(char *ShaderAssembly,GLenum ShaderObject,GLint * bCompiled);
char * GetGLSLInfoLog(GLhandleARB GLSLShaderObject);
bool LinkShader(GLhandleARB GLSL_programObj);
bool CGLSL_Light_Link_ProgramObject(GLhandleARB GLSL_PO);
bool CGLSL_Light_Link(GLhandleARB * GLSL_PO,GLhandleARB Attach_VS,GLhandleARB Attach_TC,GLhandleARB Attach_TE,GLhandleARB Attach_GS,GLhandleARB Attach_PS);
void CGLSL_Light_Attach(GLhandleARB * GLSL_PO,GLhandleARB Attach_VS,GLhandleARB Attach_TC,GLhandleARB Attach_TE,GLhandleARB Attach_GS,GLhandleARB Attach_PS);
void ClearShaderObject(GLhandleARB GLSL_PO,GLhandleARB Attach_VS,GLhandleARB Attach_TC,GLhandleARB Attach_TE,GLhandleARB Attach_GS,GLhandleARB Attach_PS);
void DelShader(GLhandleARB ShaderOBJ);
class CGLSLLoader
{
public:
	CGLSLLoader(void);
	~CGLSLLoader(void);
	bool GetGLSLLinkSTATUS(GLhandleARB g_programObj);
	CTALogSys GLSLLOG;
	bool LoadShader(const wchar_t* VSfilename,const wchar_t* PSfilename);
	void ClearShader(void);
	GLhandleARB g_VS;
	GLhandleARB g_TC;
	GLhandleARB g_TE;
	GLhandleARB g_GS;
	GLhandleARB g_PS;
	GLhandleARB g_PO;//ProgramObject
	bool LoadShader2(const wchar_t* ShaderFullName,int ShaderLevel);
	bool LoadShader(const wchar_t* ShaderName,int ShaderLevel,bool ClearOldShader=false);
};

#endif