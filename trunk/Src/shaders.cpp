#include <GL/glew.h>
#include "shaders.h"
#include <stdio.h>	
#include <windows.h>
GLuint AmbientReflectiveTexture;
bool ShaderLight=true;//是否使用shader
bool ShaderWater=true;//是否使用shader
bool ShaderBloom=true;//是否使用Bloom
bool UseShadow=true;
unsigned int ShadowLevel=4;

GLhandleARB	g_GLSLpixel;
GLhandleARB	g_GLSLvertex;
GLhandleARB	g_GLSLRenderShadowMap_vertex;
GLhandleARB	g_GLSLRenderShadowMap_pixel;
GLhandleARB	g_GLSLSea_vertex;
GLhandleARB	g_GLSLSea_pixel;
GLhandleARB g_GLSLBackFire_vertex;
GLhandleARB g_GLSLBackFire_pixel;
//GLhandleARB	g_GLSLBloom_vertex;
GLhandleARB	g_GLSLBloomW_pixel;
GLhandleARB	g_GLSLBloomH_pixel;
GLhandleARB	g_GLSLBloomMap_pixel;
GLhandleARB	g_GLSLToneMapping_pixel;
GLhandleARB GLSL_RenderShadowMap;
GLhandleARB GLSL_shaderT;
GLhandleARB GLSL_DrawSea;
GLhandleARB GLSL_DrawBloomMap;
GLhandleARB GLSL_DrawBloomW;
GLhandleARB GLSL_DrawBloomH;
GLhandleARB GLSL_ToneMapping;
GLhandleARB GLSL_BackFire;
extern float EnginePower;
extern float LightSunPos[3];
float BackFireEyeDir[4]={0.0f,1.0f,1.0f,0.0f};
float BackFireColor[4]={0.8f,0.8f,2.0f,1.0f};
float globalAmbient[4];
float paraLightColor[4];
float paraLightDirection[3];
float MissleLightDirection[4];
float MissleLightColor[3];
float lightColor[4];
float eyePosition[3]={0.0f, 150.0f, 30.0f};
float eyePositionSea[3]={0.0f, 150.0f, 30.0f};
float lightPosition[]= { 0.0f, 0.0f, 2.0f };
float lightPositionSea[]= { 0.0f, 0.0f, 2.0f };
float HDglobalAmbient[3]={1.0f,1.0f,1.0f};
float Ppos1=30.0f;
float Ppos2=150.0f;
float pixelfogColor[3]={201,207,210};
float seatime=0.0f;
GLfloat ShadowMapmvmatrix[16],ShadowMapprojmatrix[16];
GLfloat ShadowMapMVPmatrix[16]={0};
GLfloat Worldmatrix[16]={0};
unsigned char *readShaderFile( const char *fileName )
{
 FILE *file = fopen( fileName, "r" );

 if( file == NULL )
 {
 MessageBox( NULL, "Cannot open shader file!", "ERROR",
 MB_OK | MB_ICONEXCLAMATION );
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
 MessageBox( NULL, "Cannot get file stats for shader file!", "ERROR",
 MB_OK | MB_ICONEXCLAMATION );
 return 0;
 }

 unsigned char *buffer = new unsigned char[filesize+1];

  int bytes = fread( buffer, 1, filesize, file );

 buffer[bytes] = 0;

  fclose( file );

  return buffer;
}
//初始化shader
void InitShader()
{
	ShadowLevel=3;
		if(glewIsSupported("GL_ARB_shading_language_100"))
			InitGLSL();
		else
		{
			ShadowLevel=0;
			UseShadow=false;
			ShaderLight=false;
			ShaderBloom=false;
		}
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
		//MessageBox( NULL, "请尝试降低阴影设置，否则程序无法正常运行", "注意", MB_OK|MB_ICONEXCLAMATION );
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
	}
	return (bool)bLinked;
}
void InitGLSL()
{
	GLint glMaxVERTEX_UNIFORM_COMPONENTS=0;
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,&glMaxVERTEX_UNIFORM_COMPONENTS);

	if(glMaxVERTEX_UNIFORM_COMPONENTS==0)
		ShadowLevel=2;


	g_GLSLvertex = GLSL_CompileShader("vertex_t.glsl",GL_VERTEX_SHADER_ARB);
	if(ShadowLevel>=3)
		g_GLSLpixel = GLSL_CompileShader("pixel_NOBloom_HighShadow.glsl",GL_FRAGMENT_SHADER_ARB);
	else
		g_GLSLpixel = GLSL_CompileShader("pixel_NOBloom.glsl",GL_FRAGMENT_SHADER_ARB);
	g_GLSLRenderShadowMap_vertex = GLSL_CompileShader("RenderShadowMap_vertex.glsl",GL_VERTEX_SHADER_ARB);
	g_GLSLRenderShadowMap_pixel = GLSL_CompileShader("RenderShadowMap_pixel.glsl",GL_FRAGMENT_SHADER_ARB);
	g_GLSLSea_vertex = GLSL_CompileShader("Sea_vertex.glsl",GL_VERTEX_SHADER_ARB);
	g_GLSLSea_pixel = GLSL_CompileShader("Sea_pixel.glsl",GL_FRAGMENT_SHADER_ARB);
	g_GLSLBackFire_vertex = GLSL_CompileShader("BackFire_vertex.glsl",GL_VERTEX_SHADER_ARB);
	g_GLSLBackFire_pixel = GLSL_CompileShader("BackFire_pixel.glsl",GL_FRAGMENT_SHADER_ARB);
//	g_GLSLBloom_vertex = GLSL_CompileShader("Bloom_vertex.glsl",GL_VERTEX_SHADER_ARB);
	g_GLSLBloomW_pixel = GLSL_CompileShader("BloomW_pixel.glsl",GL_FRAGMENT_SHADER_ARB);
	g_GLSLBloomH_pixel = GLSL_CompileShader("BloomH_pixel.glsl",GL_FRAGMENT_SHADER_ARB);
	g_GLSLBloomMap_pixel = GLSL_CompileShader("BloomMap_pixel.glsl",GL_FRAGMENT_SHADER_ARB);
	g_GLSLToneMapping_pixel = GLSL_CompileShader("ToneMapping_pixel.glsl",GL_FRAGMENT_SHADER_ARB);

	GLSL_RenderShadowMap = glCreateProgramObjectARB();
	GLSL_shaderT = glCreateProgramObjectARB();
	GLSL_DrawSea = glCreateProgramObjectARB();
	GLSL_BackFire = glCreateProgramObjectARB();
	GLSL_DrawBloomW = glCreateProgramObjectARB();
	GLSL_DrawBloomH = glCreateProgramObjectARB();
	GLSL_DrawBloomMap = glCreateProgramObjectARB();
	GLSL_ToneMapping = glCreateProgramObjectARB();
	glAttachObjectARB( GLSL_RenderShadowMap, g_GLSLRenderShadowMap_vertex );
	glAttachObjectARB( GLSL_RenderShadowMap, g_GLSLRenderShadowMap_pixel );
	glAttachObjectARB( GLSL_shaderT, g_GLSLvertex );
	glAttachObjectARB( GLSL_shaderT, g_GLSLpixel );
	glAttachObjectARB( GLSL_DrawSea, g_GLSLSea_vertex );
	glAttachObjectARB( GLSL_DrawSea, g_GLSLSea_pixel );
	glAttachObjectARB( GLSL_BackFire, g_GLSLBackFire_vertex );
	glAttachObjectARB( GLSL_BackFire, g_GLSLBackFire_pixel );
	//glAttachObjectARB( GLSL_DrawBloomW, g_GLSLBloom_vertex );
	glAttachObjectARB( GLSL_DrawBloomW, g_GLSLBloomW_pixel );
	//glAttachObjectARB( GLSL_DrawBloomH, g_GLSLBloom_vertex );
	glAttachObjectARB( GLSL_DrawBloomH, g_GLSLBloomH_pixel );
	//glAttachObjectARB( GLSL_DrawBloomMap, g_GLSLBloom_vertex );
	glAttachObjectARB( GLSL_DrawBloomMap, g_GLSLBloomMap_pixel );
	//glAttachObjectARB( GLSL_ToneMapping, g_GLSLBloom_vertex );
	glAttachObjectARB( GLSL_ToneMapping, g_GLSLToneMapping_pixel );
	GetGLSLLinkSTATUS( GLSL_RenderShadowMap);
	GetGLSLLinkSTATUS( GLSL_shaderT);
	GetGLSLLinkSTATUS( GLSL_DrawSea);
	GetGLSLLinkSTATUS( GLSL_BackFire);
	GetGLSLLinkSTATUS( GLSL_DrawBloomW);
	GetGLSLLinkSTATUS( GLSL_DrawBloomH);
	GetGLSLLinkSTATUS( GLSL_DrawBloomMap);
	GetGLSLLinkSTATUS( GLSL_ToneMapping);
}
//使用shader
void RenderShadowMap()
{
		RenderShadowMapGLSL();

}
void RenderShadowMapGLSL()
{
	glUseProgramObjectARB( GLSL_RenderShadowMap );
}
void shaderT(int MainTex,int NormalTex,int SpecularTex,int ShadowMapTexID,float HDlight)
{
		shaderTGLSL(MainTex,NormalTex,SpecularTex,ShadowMapTexID,1.0f);
}
void shaderTGLSL(int MainTex,int NormalTex,int SpecularTex,int ShadowMapTexID,float HDlight)
{
	if(HDlight<0.0f)
		HDlight=0.0f;
	if(HDlight>1.0f)
		HDlight=1.0f;
	HDglobalAmbient[0]=globalAmbient[0]*HDlight;
	HDglobalAmbient[1]=globalAmbient[1]*HDlight;
	HDglobalAmbient[2]=globalAmbient[2]*HDlight;
	glUseProgramObjectARB( GLSL_shaderT );
	glActiveTexture(GL_TEXTURE0);	glBindTexture(GL_TEXTURE_2D,MainTex);			glUniform1i(glGetUniformLocation(GLSL_shaderT,"testTexture"),0);
	glActiveTexture(GL_TEXTURE1);	glBindTexture(GL_TEXTURE_2D,ShadowMapTexID);	glUniform1i(glGetUniformLocation(GLSL_shaderT,"ShadowMapTexture"),1);
	glActiveTexture(GL_TEXTURE2);	glBindTexture(GL_TEXTURE_CUBE_MAP_EXT,AmbientReflectiveTexture);	glUniform1i(glGetUniformLocation(GLSL_shaderT,"AmbientReflectiveTexture"),2);
	glActiveTexture(GL_TEXTURE3);	glBindTexture(GL_TEXTURE_2D,NormalTex);	glUniform1i(glGetUniformLocation(GLSL_shaderT,"NormalMapTexture"),3);
	glActiveTexture(GL_TEXTURE4);	glBindTexture(GL_TEXTURE_2D,SpecularTex);	glUniform1i(glGetUniformLocation(GLSL_shaderT,"SpecularMapTexture"),4);
	glActiveTexture(GL_TEXTURE0);
	glUniformMatrix4fv(glGetUniformLocation(GLSL_shaderT,"ShadowMapMVPmatrix"),1,GL_FALSE,ShadowMapMVPmatrix);
	glUniformMatrix4fv(glGetUniformLocation(GLSL_shaderT,"Worldmatrix"),1,GL_FALSE,Worldmatrix);
	glUniform4fv(glGetUniformLocation(GLSL_shaderT,"MissleLightDirection"),1,MissleLightDirection);
	glUniform3fv(glGetUniformLocation(GLSL_shaderT,"MissleLightColor"),1,MissleLightColor);
	glUniform3fv(glGetUniformLocation(GLSL_shaderT,"globalAmbient"),1,HDglobalAmbient);
	glUniform3fv(glGetUniformLocation(GLSL_shaderT,"paraLightColor"),1,paraLightColor);
	glUniform3fv(glGetUniformLocation(GLSL_shaderT,"paraLightDirection"),1,paraLightDirection);
	glUniform3fv(glGetUniformLocation(GLSL_shaderT,"eyePosition"),1,eyePosition);
}
void DrawSea(float seaframe)
{
		DrawSeaGLSL(seaframe);
}
void DrawSeaGLSL(float seaframe)
{
	seatime=seatime+seaframe/200.0f;
	if(seatime>1.0f)
		seatime=seatime-1.0f;
	glUseProgramObjectARB( GLSL_DrawSea );
	glUniform1f(glGetUniformLocation(GLSL_DrawSea,"time"),seatime);
	glUniform1i(glGetUniformLocation(GLSL_DrawSea,"testTexture"),0);
	glActiveTexture(GL_TEXTURE2);              
    glBindTexture(GL_TEXTURE_CUBE_MAP_EXT,AmbientReflectiveTexture);  
	glUniform1i(glGetUniformLocation(GLSL_DrawSea,"AmbientReflectiveTexturSea"),2); 
	glUniform3fv(glGetUniformLocation(GLSL_DrawSea,"globalAmbient"),1,globalAmbient);
	glUniform3fv(glGetUniformLocation(GLSL_DrawSea,"paraLightColor"),1,paraLightColor);
	glUniform3fv(glGetUniformLocation(GLSL_DrawSea,"paraLightDirection"),1,LightSunPos);
	glUniform3fv(glGetUniformLocation(GLSL_DrawSea,"eyePosition"),1,eyePositionSea);
	glUniform3fv(glGetUniformLocation(GLSL_DrawSea,"FogColor"),1,pixelfogColor);
	glActiveTexture(GL_TEXTURE0);              
}
void DrawBloomMap(int WinW,int WinH)
{
		DrawBloomMapGLSL(WinW,WinH);
}
void DrawBloomMapGLSL(int WinW,int WinH)
{
	glUseProgramObjectARB( GLSL_DrawBloomMap );
	glUniform1i(glGetUniformLocation(GLSL_DrawBloomMap,"texColor"),0);
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomMap,"AveLum"),0.23f);
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomMap,"imgW"),(float)WinW);
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomMap,"imgH"),(float)WinH);
}
void DrawBloomW(int WinW)
{
		DrawBloomWGLSL(WinW);
}
void DrawBloomWGLSL(int WinW)
{
	glUseProgramObjectARB( GLSL_DrawBloomW );
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomW,"_imgW1"),(float)WinW);
	glUniform1i(glGetUniformLocation(GLSL_DrawBloomW,"_texSrc1"),0);
}
void DrawBloomH(int WinH)
{
		DrawBloomHGLSL(WinH);
}
void DrawBloomHGLSL(int WinH)
{
	glUseProgramObjectARB( GLSL_DrawBloomH );
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomH,"_imgH1"),(float)WinH);
	glUniform1i(glGetUniformLocation(GLSL_DrawBloomH,"_texSrc1"),0);
}
void ToneMapping()
{
		ToneMappingGLSL();
}
void ToneMappingGLSL()
{
	glUseProgramObjectARB( GLSL_ToneMapping );
	glUniform1i(glGetUniformLocation(GLSL_ToneMapping,"_texSrc1"),0);
}
void BackFire()
{
		BackFireGLSL();
}
void BackFireGLSL()
{
	glUseProgramObjectARB( GLSL_BackFire );
	glUniform4fv(glGetUniformLocation(GLSL_BackFire,"BackFireEyeDir"),1,BackFireEyeDir);
	glUniform4fv(glGetUniformLocation(GLSL_BackFire,"BackFireColor"),1,BackFireColor);
	glUniform1f(glGetUniformLocation(GLSL_BackFire,"EnginePower"),EnginePower);
}
void CGDisableProfilePixel()
{
		glUseProgramObjectARB( NULL );
}
void CGDisableProfileVertex()
{
		glUseProgramObjectARB( NULL );
}
void CGDisableTextureParameterShadowMap()
{
		glActiveTexture(GL_TEXTURE0);
}
void CGDisableTextureParameterAmbientReflective()
{
		glActiveTexture(GL_TEXTURE0);
}
void CGDisableTextureParameterNormalMap()
{
		glActiveTexture(GL_TEXTURE0);
}
void CGDisableTextureParameterSpecularMap()
{
		glActiveTexture(GL_TEXTURE0);
}
void CGDisableTextureParameterAmbientReflectiveSea()
{
		glActiveTexture(GL_TEXTURE0);
}
