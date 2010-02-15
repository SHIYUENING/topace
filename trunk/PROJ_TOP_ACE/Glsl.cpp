#include "Glsl.h"
#include <stdio.h>	
#include <windows.h>
int GlslVer = 0;
//GLhandleARB	g_GLSL_ATC_Pixel;
//GLhandleARB	g_GLSL_ATC_Vertex;
//GLhandleARB GLSL_ATC;
GLhandleARB g_PhoneLight;
GLhandleARB g_PhoneLight_Vertex;
GLhandleARB g_PhoneLight_Pixel;
unsigned char *readShaderFile( const char *fileName )
{
	FILE *file = fopen( fileName, "r" );

	if( file == NULL )
	{
		MessageBox( NULL, "Cannot open shader file!", "ERROR",MB_OK | MB_ICONEXCLAMATION );
		return 0;
	}

	unsigned int filesize = 0;
	while (!feof(file))
	{
		fgetc(file);
		filesize++;
	}
	filesize--;
	rewind(file);

	if( filesize== 0 )
	{
		MessageBox( NULL, "Cannot get file stats for shader file!", "ERROR",MB_OK | MB_ICONEXCLAMATION );
		return 0;
	}

	unsigned char *buffer = new unsigned char[filesize+1];

	int bytes = fread( buffer, 1, filesize, file );

	buffer[bytes] = 0;

	fclose( file );

	return buffer;
}

GLhandleARB GLSL_CompileShader(const char* shaderfilename,unsigned int ShaderObject)
{
	GLhandleARB GLSLShaderObject=0;
	GLSLShaderObject=glCreateShaderObjectARB(ShaderObject);
	unsigned char *ShaderAssembly = readShaderFile( shaderfilename );
	const char *ShaderStrings[1];
	ShaderStrings[0] = (char*)ShaderAssembly;
	glShaderSourceARB( GLSLShaderObject, 1, ShaderStrings, NULL );
	glCompileShaderARB( GLSLShaderObject);
	//delete [] ShaderAssembly;
	GLint bCompiled=0;
	glGetObjectParameterivARB( GLSLShaderObject, GL_OBJECT_COMPILE_STATUS_ARB, &bCompiled );
	if( bCompiled == false )
	{
		char str[4096];
		glGetInfoLogARB(GLSLShaderObject, sizeof(str), NULL, str);
		MessageBox( NULL, str, "Shader Compile Error", MB_OK|MB_ICONEXCLAMATION );
	}
	return GLSLShaderObject;
}
bool GetGLSLLinkSTATUS(GLhandleARB g_programObj)
{
//
// Link the program object and print out the info log...
//
	GLint bLinked=false;
	char str[4096];
	glLinkProgramARB( g_programObj );
	glGetObjectParameterivARB( g_programObj, GL_OBJECT_LINK_STATUS_ARB, &bLinked );

	if( bLinked == false )
	{
		glGetInfoLogARB( g_programObj, sizeof(str), NULL, str );
		MessageBox( NULL, str, "Linking Error", MB_OK|MB_ICONEXCLAMATION );
		return false;
	}
	return true;
}

void InitGLSL()
{
/*	GLint glMaxVERTEX_UNIFORM_COMPONENTS=0;
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,&glMaxVERTEX_UNIFORM_COMPONENTS);

	if(glMaxVERTEX_UNIFORM_COMPONENTS==0)
		ShadowLevel=2;
*/
	//char MaxVERTEX_UNIFORM_COMPONENTS[32]={0};
	//itoa(glMaxVERTEX_UNIFORM_COMPONENTS,MaxVERTEX_UNIFORM_COMPONENTS,10);
	//MessageBox( NULL, MaxVERTEX_UNIFORM_COMPONENTS, "!", MB_OK|MB_ICONEXCLAMATION );

	if(glewIsSupported("GL_ARB_shading_language_100"))
		GlslVer=100;
	else
		return;

	//g_GLSL_ATC_Vertex = GLSL_CompileShader("shaders/glsl/Alpha_TO_Coverage.vs",GL_VERTEX_SHADER_ARB);
	//g_GLSL_ATC_Pixel = GLSL_CompileShader("shaders/glsl/Alpha_TO_Coverage.ps",GL_FRAGMENT_SHADER_ARB);
	//GLSL_ATC = glCreateProgramObjectARB();
	//glAttachObjectARB( GLSL_ATC, g_GLSL_ATC_Vertex );
	//glAttachObjectARB( GLSL_ATC, g_GLSL_ATC_Pixel );
	//GetGLSLLinkSTATUS( GLSL_ATC );

	g_PhoneLight_Vertex = GLSL_CompileShader("data/shader/Glsl_PhoneLight_Vertex.vs",GL_VERTEX_SHADER_ARB);
	g_PhoneLight_Pixel = GLSL_CompileShader("data/shader/Glsl_PhoneLight_Pixel.ps",GL_FRAGMENT_SHADER_ARB);
	g_PhoneLight = glCreateProgramObjectARB();
	glAttachObjectARB( g_PhoneLight, g_PhoneLight_Vertex );
	glAttachObjectARB( g_PhoneLight, g_PhoneLight_Pixel );
	GetGLSLLinkSTATUS( g_PhoneLight );

}
void GLSL_Enable_PhoneLight(float* LightColor,float* LightPosEye)
{
	if(GlslVer<=0)
		return;
	glUseProgramObjectARB( g_PhoneLight );
	glUniform1i(glGetUniformLocation(g_PhoneLight,"DiffuseTex"),0);
	glUniform4fv(glGetUniformLocation(g_PhoneLight,"LightColor"),1,LightColor);
	glUniform4fv(glGetUniformLocation(g_PhoneLight,"LightPosEye"),1,LightPosEye);
	//glUniform1i(glGetUniformLocation(GLSL_ATC,"Tex_ATC"),0); 
}
void GLSL_Disable()
{
	if(GlslVer<=0)
		return;
	glUseProgramObjectARB( NULL );
}
/*
void GLSL_Enable_ATC()
{
	if(GlslVer<=0)
		return;
	glUseProgramObjectARB( GLSL_ATC );
	glUniform1i(glGetUniformLocation(GLSL_ATC,"Tex_ATC"),0); 
}
void GLSL_Disable_ATC()
{
	if(GlslVer<=0)
		return;
	glUseProgramObjectARB( NULL );
}
*/