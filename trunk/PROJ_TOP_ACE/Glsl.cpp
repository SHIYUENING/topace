#include "Glsl.h"
#include <stdio.h>	
#include <windows.h>
int GlslVer = 0;
//GLhandleARB	g_GLSL_ATC_Pixel;
//GLhandleARB	g_GLSL_ATC_Vertex;
//GLhandleARB GLSL_ATC;
int GLSLLightSet=0;
GLhandleARB g_PhoneLight;
GLhandleARB g_PhoneLight_Vertex;
GLhandleARB g_PhoneLight_Pixel;
GLhandleARB g_StarPass1;
GLhandleARB g_StarPass1_Pixel;
GLhandleARB g_StarPass0;
GLhandleARB g_StarPass0_Pixel;

GLhandleARB	g_GLSLBloomW_pixel;
GLhandleARB	g_GLSLBloomH_pixel;
GLhandleARB	g_GLSLBloomMap_pixel;
GLhandleARB	g_GLSLToneMapping_pixel;

GLhandleARB GLSL_DrawBloomW;
GLhandleARB GLSL_DrawBloomH;
GLhandleARB GLSL_ToneMapping;
GLhandleARB GLSL_DrawBloomMap;
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

void InitGLSL(int LightSet)
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

	GLSLLightSet = LightSet;
	if(LightSet<2)
	{
		GlslVer=0;
		return;
	}

	//g_GLSL_ATC_Vertex = GLSL_CompileShader("shaders/glsl/Alpha_TO_Coverage.vs",GL_VERTEX_SHADER_ARB);
	//g_GLSL_ATC_Pixel = GLSL_CompileShader("shaders/glsl/Alpha_TO_Coverage.ps",GL_FRAGMENT_SHADER_ARB);
	//GLSL_ATC = glCreateProgramObjectARB();
	//glAttachObjectARB( GLSL_ATC, g_GLSL_ATC_Vertex );
	//glAttachObjectARB( GLSL_ATC, g_GLSL_ATC_Pixel );
	//GetGLSLLinkSTATUS( GLSL_ATC );

	g_PhoneLight_Vertex = GLSL_CompileShader("data/shader/Glsl_PhoneLight_Vertex.vs",GL_VERTEX_SHADER_ARB);

	switch (LightSet)
	{
		case 2: g_PhoneLight_Pixel = GLSL_CompileShader("data/shader/Glsl_PhoneLight_Pixel_Singe.ps",GL_FRAGMENT_SHADER_ARB);break;
		case 3: g_PhoneLight_Pixel = GLSL_CompileShader("data/shader/Glsl_PhoneLight_Pixel_Multi.ps",GL_FRAGMENT_SHADER_ARB);break;
		default : g_PhoneLight_Pixel = GLSL_CompileShader("data/shader/Glsl_PhoneLight_Pixel_Singe.ps",GL_FRAGMENT_SHADER_ARB);break;
	}
	g_PhoneLight = glCreateProgramObjectARB();
	glAttachObjectARB( g_PhoneLight, g_PhoneLight_Vertex );
	glAttachObjectARB( g_PhoneLight, g_PhoneLight_Pixel );
	GetGLSLLinkSTATUS( g_PhoneLight );

	g_StarPass1_Pixel = GLSL_CompileShader("data/shader/Glsl_StarPass1_Pixel.ps",GL_FRAGMENT_SHADER_ARB);
	g_StarPass1 = glCreateProgramObjectARB();

	glAttachObjectARB( g_StarPass1, g_StarPass1_Pixel );
	GetGLSLLinkSTATUS( g_StarPass1 );

	g_StarPass0_Pixel = GLSL_CompileShader("data/shader/Glsl_StarPass0_Pixel.ps",GL_FRAGMENT_SHADER_ARB);
	g_StarPass0 = glCreateProgramObjectARB();

	glAttachObjectARB( g_StarPass0, g_StarPass0_Pixel );
	GetGLSLLinkSTATUS( g_StarPass0 );

	GLSL_DrawBloomW = glCreateProgramObjectARB();
	GLSL_DrawBloomH = glCreateProgramObjectARB();
	GLSL_DrawBloomMap = glCreateProgramObjectARB();
	GLSL_ToneMapping = glCreateProgramObjectARB();

	g_GLSLBloomW_pixel = GLSL_CompileShader("data/shader/BloomW_pixel.glsl",GL_FRAGMENT_SHADER_ARB);
	g_GLSLBloomH_pixel = GLSL_CompileShader("data/shader/BloomH_pixel.glsl",GL_FRAGMENT_SHADER_ARB);
	g_GLSLBloomMap_pixel = GLSL_CompileShader("data/shader/BloomMap_pixel.glsl",GL_FRAGMENT_SHADER_ARB);
	g_GLSLToneMapping_pixel = GLSL_CompileShader("data/shader/ToneMapping_pixel.glsl",GL_FRAGMENT_SHADER_ARB);

	glAttachObjectARB( GLSL_DrawBloomW, g_GLSLBloomW_pixel );
	glAttachObjectARB( GLSL_DrawBloomH, g_GLSLBloomH_pixel );
	glAttachObjectARB( GLSL_DrawBloomMap, g_GLSLBloomMap_pixel );
	glAttachObjectARB( GLSL_ToneMapping, g_GLSLToneMapping_pixel );

	GetGLSLLinkSTATUS( GLSL_DrawBloomW);
	GetGLSLLinkSTATUS( GLSL_DrawBloomH);
	GetGLSLLinkSTATUS( GLSL_DrawBloomMap);
	GetGLSLLinkSTATUS( GLSL_ToneMapping);

	

}
void DeinitGLSL()
{
	if(GlslVer<100)
		return;
	glDetachObjectARB( g_PhoneLight, g_PhoneLight_Vertex );
	glDetachObjectARB( g_PhoneLight, g_PhoneLight_Pixel );
	glDeleteObjectARB(g_PhoneLight_Vertex);
	glDeleteObjectARB(g_PhoneLight_Pixel);

	glDetachObjectARB( g_StarPass1, g_StarPass1_Pixel );
	glDeleteObjectARB(g_StarPass1_Pixel);

	glDetachObjectARB( g_StarPass0, g_StarPass0_Pixel );
	glDeleteObjectARB(g_StarPass0_Pixel);

	glDetachObjectARB( GLSL_DrawBloomW, g_GLSLBloomW_pixel );
	glDetachObjectARB( GLSL_DrawBloomH, g_GLSLBloomH_pixel );
	glDetachObjectARB( GLSL_DrawBloomMap, g_GLSLBloomMap_pixel );
	glDetachObjectARB( GLSL_ToneMapping, g_GLSLToneMapping_pixel );

	glDeleteObjectARB( g_GLSLBloomW_pixel );
	glDeleteObjectARB( g_GLSLBloomH_pixel );
	glDeleteObjectARB( g_GLSLBloomMap_pixel );
	glDeleteObjectARB( g_GLSLToneMapping_pixel );
}
void GLSL_Enable_PhoneLight(int OmniLightNum,int SpotLightNum)
{
	int LightNums[2]={OmniLightNum,SpotLightNum};
	if(GlslVer<100)
		return;
	glUseProgramObjectARB( g_PhoneLight );
	glUniform1i(glGetUniformLocation(g_PhoneLight,"DiffuseTex"),0);
	glUniform2iv(glGetUniformLocation(g_PhoneLight,"LightNums"),1,LightNums); 
	//glUniform4fv(glGetUniformLocation(g_PhoneLight,"LightColor"),1,LightColor);
	//glUniform4fv(glGetUniformLocation(g_PhoneLight,"LightPosEye"),1,LightPosEye);
	//glUniform1i(glGetUniformLocation(GLSL_ATC,"Tex_ATC"),0); 
}
void GLSL_Disable()
{
	if(GlslVer<100)
		return;
	glUseProgramObjectARB( NULL );
}
void GLSL_Enable_StarPass1()
{
	if(GlslVer<100)
		return;
	glUseProgramObjectARB( g_StarPass1 );
	glUniform1i(glGetUniformLocation(g_StarPass1,"StarTex1"),0);
}
void GLSL_Enable_StarPass0()
{
	if(GlslVer<100)
		return;
	glUseProgramObjectARB( g_StarPass0 );
	glUniform1i(glGetUniformLocation(g_StarPass0,"StarTex1"),0);
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
void DrawBloomMapGLSL(int WinW,int WinH)
{
	glUseProgramObjectARB( GLSL_DrawBloomMap );
	glUniform1i(glGetUniformLocation(GLSL_DrawBloomMap,"texColor"),0);
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomMap,"AveLum"),0.23f);
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomMap,"imgW"),(float)WinW);
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomMap,"imgH"),(float)WinH);
}
void DrawBloomWGLSL(int WinW)
{
	glUseProgramObjectARB( GLSL_DrawBloomW );
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomW,"_imgW1"),(float)WinW);
	glUniform1i(glGetUniformLocation(GLSL_DrawBloomW,"_texSrc1"),0);
}
void DrawBloomHGLSL(int WinH)
{
	glUseProgramObjectARB( GLSL_DrawBloomH );
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomH,"_imgH1"),(float)WinH);
	glUniform1i(glGetUniformLocation(GLSL_DrawBloomH,"_texSrc1"),0);
}
void ToneMappingGLSL()
{
	glUseProgramObjectARB( GLSL_ToneMapping );
	glUniform1i(glGetUniformLocation(GLSL_ToneMapping,"_texSrc1"),0);
}