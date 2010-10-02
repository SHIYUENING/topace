#include "Glsl.h"
#include <stdio.h>	
#include <windows.h>
#include"IniFile.h"
int GlslVer = 0;
//GLhandleARB	g_GLSL_ATC_Pixel;
//GLhandleARB	g_GLSL_ATC_Vertex;
//GLhandleARB GLSL_ATC;
int GLSLLightSet=0;
GLhandleARB g_PhoneLight=0;
GLhandleARB g_PhoneLight_Vertex=0;
GLhandleARB g_PhoneLight_Pixel=0;
GLhandleARB g_StarPass1=0;
GLhandleARB g_StarPass1_Pixel=0;
GLhandleARB g_StarPass0=0;
GLhandleARB g_StarPass0_Pixel=0;

GLhandleARB	g_GLSLBloomW_pixel=0;
GLhandleARB	g_GLSLBloomH_pixel=0;
GLhandleARB	g_GLSLBloomMap_pixel=0;
GLhandleARB	g_GLSLToneMapping_pixel=0;

GLhandleARB GLSL_DrawBloomW=0;
GLhandleARB GLSL_DrawBloomH=0;
GLhandleARB GLSL_ToneMapping=0;
GLhandleARB GLSL_DrawBloomMap=0;

GLhandleARB g_GLSLSSAOPass0_pixel=0;
GLhandleARB GLSL_SSAOPass0=0;
GLhandleARB g_GLSLSSAOPass1_pixel=0;
GLhandleARB GLSL_SSAOPass1=0;

GLhandleARB g_BlurTex_pixel=0;
GLhandleARB GLSL_BlurTex=0;

_ShaderGLSL GLSL_DrawSea;
extern tGameSet GameSet;
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
		char str[40960];
		glGetInfoLogARB(GLSLShaderObject, sizeof(str), NULL, str);
		MessageBox( NULL, "Error Message saving to Error.log", "Shader Compile Error", MB_OK|MB_ICONEXCLAMATION );
		//WritePrivateProfileString("Glsl","Compile_Error",str,".\\Error_log.ini");
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
		CloseHandle(hFile);
	}
	return GLSLShaderObject;
}
bool GetGLSLLinkSTATUS(GLhandleARB g_programObj)
{
//
// Link the program object and print out the info log...
//
	GLint bLinked=false;
	glLinkProgramARB( g_programObj );
	glGetObjectParameterivARB( g_programObj, GL_OBJECT_LINK_STATUS_ARB, &bLinked );

	if( bLinked == false )
	{
		char str[40960];
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
		CloseHandle(hFile);
		return false;
	}
	return true;
}

bool Init_ShaderGLSL(_ShaderGLSL * ShaderGLSL,const char* VSfilename,const char* PSfilename)
{
	if(!ShaderGLSL) return false;
	ShaderGLSL->g_VS = GLSL_CompileShader(VSfilename,GL_VERTEX_SHADER_ARB);
	ShaderGLSL->g_PS = GLSL_CompileShader(PSfilename,GL_FRAGMENT_SHADER_ARB);
	ShaderGLSL->g_PO = glCreateProgramObjectARB();
	glAttachObjectARB( ShaderGLSL->g_PO, ShaderGLSL->g_VS );
	glAttachObjectARB( ShaderGLSL->g_PO, ShaderGLSL->g_PS );
	return GetGLSLLinkSTATUS( ShaderGLSL->g_PO );
}
void Deinit_ShaderGLSL(_ShaderGLSL * ShaderGLSL)
{
	if(!ShaderGLSL) return;
	glDetachObjectARB( ShaderGLSL->g_PO, ShaderGLSL->g_VS );
	glDetachObjectARB( ShaderGLSL->g_PO, ShaderGLSL->g_PS );
	glDeleteObjectARB( ShaderGLSL->g_VS );
	glDeleteObjectARB( ShaderGLSL->g_PS );
	glDeleteObjectARB( ShaderGLSL->g_PO );
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


	Init_ShaderGLSL(&GLSL_DrawSea,"data/shader/GLSL_Sea.vs","data/shader/GLSL_Sea.ps");

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

	if(GameSet.SSAO>0)
	{
		GLSL_SSAOPass0 = glCreateProgramObjectARB();
		g_GLSLSSAOPass0_pixel = GLSL_CompileShader("data/shader/Glsl_SSAO_Pass0.ps",GL_FRAGMENT_SHADER_ARB);
		glAttachObjectARB( GLSL_SSAOPass0, g_GLSLSSAOPass0_pixel);
		GetGLSLLinkSTATUS( GLSL_SSAOPass0);
		
		GLSL_SSAOPass1 = glCreateProgramObjectARB();
		g_GLSLSSAOPass1_pixel = GLSL_CompileShader("data/shader/Glsl_SSAO_Pass1.ps",GL_FRAGMENT_SHADER_ARB);
		glAttachObjectARB( GLSL_SSAOPass1, g_GLSLSSAOPass1_pixel);
		GetGLSLLinkSTATUS( GLSL_SSAOPass1);
	}

	InitBlurTex();
}
void DeinitGLSL()
{
	if(GlslVer<100)
		return;
	glDetachObjectARB( g_PhoneLight, g_PhoneLight_Vertex );
	glDetachObjectARB( g_PhoneLight, g_PhoneLight_Pixel );
	glDeleteObjectARB(g_PhoneLight_Vertex);
	glDeleteObjectARB(g_PhoneLight_Pixel);
	glDeleteObjectARB(g_PhoneLight);

	glDetachObjectARB( g_StarPass1, g_StarPass1_Pixel );
	glDeleteObjectARB(g_StarPass1_Pixel);
	glDeleteObjectARB(g_StarPass1);

	glDetachObjectARB( g_StarPass0, g_StarPass0_Pixel );
	glDeleteObjectARB(g_StarPass0_Pixel);
	glDeleteObjectARB(g_StarPass0);

	glDetachObjectARB( GLSL_DrawBloomW, g_GLSLBloomW_pixel );
	glDetachObjectARB( GLSL_DrawBloomH, g_GLSLBloomH_pixel );
	glDetachObjectARB( GLSL_DrawBloomMap, g_GLSLBloomMap_pixel );
	glDetachObjectARB( GLSL_ToneMapping, g_GLSLToneMapping_pixel );

	glDeleteObjectARB( g_GLSLBloomW_pixel );
	glDeleteObjectARB( g_GLSLBloomH_pixel );
	glDeleteObjectARB( g_GLSLBloomMap_pixel );
	glDeleteObjectARB( g_GLSLToneMapping_pixel );
	glDeleteObjectARB( GLSL_DrawBloomW );
	glDeleteObjectARB( GLSL_DrawBloomH );
	glDeleteObjectARB( GLSL_DrawBloomMap );
	glDeleteObjectARB( GLSL_ToneMapping );

	glDetachObjectARB( GLSL_SSAOPass0, g_GLSLSSAOPass0_pixel);
	glDeleteObjectARB( g_GLSLSSAOPass0_pixel);
	glDeleteObjectARB( GLSL_SSAOPass0);
	glDetachObjectARB( GLSL_SSAOPass1, g_GLSLSSAOPass1_pixel);
	glDeleteObjectARB( g_GLSLSSAOPass1_pixel);
	glDeleteObjectARB( GLSL_SSAOPass1);

	Deinit_ShaderGLSL(&GLSL_DrawSea);
	DeinitBlurTex();
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
void SSAOPass0()
{
	glUseProgramObjectARB(GLSL_SSAOPass0);
	glUniform1i(glGetUniformLocation(GLSL_SSAOPass0,"DepthTex"),0);
	
}
void SSAOPass1(float SSAOset[4])
{
	glUseProgramObjectARB(GLSL_SSAOPass1);
	glUniform1i(glGetUniformLocation(GLSL_SSAOPass1,"DepthTex"),0);
	glUniform4fv(glGetUniformLocation(GLSL_SSAOPass1,"SSAOset"),1,SSAOset);
	
}
void InitBlurTex()
{
	GLSL_BlurTex = glCreateProgramObjectARB();
	g_BlurTex_pixel = GLSL_CompileShader("data/shader/BlurTex.ps",GL_FRAGMENT_SHADER_ARB);
	glAttachObjectARB( GLSL_BlurTex, g_BlurTex_pixel);
	GetGLSLLinkSTATUS( GLSL_BlurTex);
}
void DeinitBlurTex()
{
	glDetachObjectARB( GLSL_BlurTex, g_BlurTex_pixel);
	glDeleteObjectARB( g_BlurTex_pixel);
	glDeleteObjectARB( GLSL_BlurTex );
}
void BlurTex(int Size,bool WorH)
{
	float BlurTexSet[2]={0.0f,0.0f};
	if(WorH)
		BlurTexSet[0]=1.0f/float(Size);
	else
		BlurTexSet[1]=1.0f/float(Size);
	glUseProgramObjectARB(GLSL_BlurTex);
	glUniform1i(glGetUniformLocation(GLSL_BlurTex,"BlurTex"),0);
	glUniform2fv(glGetUniformLocation(GLSL_BlurTex,"BlurTexSet"),1,BlurTexSet);

}
