#include <GL/glew.h>
#include <Cg/Cg.h>
#include <Cg/cgGL.h>
#include "shaders.h"
#include <stdio.h>	
#include <windows.h>
GLuint AmbientReflectiveTexture;
bool isGLSL=false;
bool ShaderLight=true;//是否使用shader
bool ShaderWater=true;//是否使用shader
bool ShaderBloom=true;//是否使用Bloom
bool UseHighShadow=true;
bool UseShadow=true;
unsigned int ShadowLevel=4;
CGprofile   g_CGprofile_vertex;
CGprofile   g_CGprofile_pixel;
//CGprofile   g_CGprofile_pixel_GlSL;
CGcontext   g_CGcontext;
//CGprogram   g_CGbasicLight_vertex;
//CGprogram   g_CGHighLight_vertex;
//CGprogram   g_CGHighLight_pixel;
CGprogram   g_CGvertex_t;
//CGprogram   g_CGpixel_t;
CGprogram   g_CGpixel_NOBloom;
CGprogram   g_CGpixel_NOBloom_Low_shadow;
CGprogram   g_CGpixel_NONormalMap;
//CGprogram   g_CGpixel_NOBloom_HighShadow;
CGprogram   g_CGRenderShadowMap_vertex;
CGprogram   g_CGRenderShadowMap_pixel;
//CGprogram	g_BloomL1_pixel;
//CGprogram	g_BloomL2_pixel;
//CGprogram	g_BloomL3_pixel;
CGprogram	g_Sea_vertex;
CGprogram	g_Sea_pixel;
CGprogram	g_BloomW_pixel;
CGprogram	g_BloomH_pixel;
CGprogram	g_BloomMap_pixel;
CGprogram	g_ToneMapping_pixel;

CGparameter   g_CGparam_ShadowMapTexture;
CGparameter   g_CGparam_AmbientReflective;
CGparameter   g_CGparam_NormalMapTexture;
CGparameter   g_CGparam_SpecularMapTexture;
CGparameter   g_CGparam_AmbientReflectiveSea;

//CGparameter g_CGparam_testTexture;
CGparameter cg_globalAmbient;
CGparameter cg_lightColor;
CGparameter cg_lightPosition;
CGparameter cg_eyePosition;

CGparameter cg_ShadowMapmvmatrix;
CGparameter cg_ShadowMapprojmatrix;

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

extern float LightSunPos[3];
float BackFireEyeDir[3]={0.0f,1.0f,1.0f};
float BackFireColor[4]={1.0f,0.2f,0.2f,1.0f};
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
float pixelfogColor[3];
float seatime=0.0f;
GLfloat ShadowMapmvmatrix[16],ShadowMapprojmatrix[16];
GLfloat ShadowMapMVPmatrix[16],Worldmatrix[16];
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
	if((ShadowLevel==2)||(ShadowLevel==3))
		isGLSL=true;
	else
		isGLSL=false;

	if((!glewIsSupported("GL_NV_fragment_program"))&&(ShadowLevel==4))
		isGLSL=true;
	ShaderBloom=true;
	if(!isGLSL)
	{
		isGLSL=false;
		InitCG();
	}
	else
	{
		if(ShadowLevel==4)
			ShadowLevel=3;
		UseHighShadow=false;
		isGLSL=true;
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
}
void InitCG()
{
	
    //
    // Search for a valid vertex shader profile in this order:
    //
    // CG_PROFILE_ARBVP1 - GL_ARB_vertex_program
    // CG_PROFILE_VP40   - GL_ARB_vertex_program + GL_NV_vertex_program3
    //

    
    if( cgGLIsProfileSupported(CG_PROFILE_VP40) )
        g_CGprofile_vertex = CG_PROFILE_VP40;
	else if( cgGLIsProfileSupported(CG_PROFILE_ARBVP1) )
        g_CGprofile_vertex = CG_PROFILE_ARBVP1;
	else if( cgGLIsProfileSupported(CG_PROFILE_VP30) )
        g_CGprofile_vertex = CG_PROFILE_VP30;
	else if( cgGLIsProfileSupported(CG_PROFILE_VP20) )
        g_CGprofile_vertex = CG_PROFILE_VP20;
    else
    {
		ShaderWater=false;
        ShaderLight=false;
		ShaderBloom=false;
        return;
    }

	//
	// Search for a valid pixel shader profile in this order:
	//
	// CG_PROFILE_ARBFP1 - GL_ARB_fragment_program
	// CG_PROFILE_FP30   - GL_NV_fragment_program
	// CG_PROFILE_FP20   - NV_texture_shader & NV_register_combiners
	//
	

	if( cgGLIsProfileSupported(CG_PROFILE_FP40) )
        g_CGprofile_pixel = CG_PROFILE_FP40;
	else if( cgGLIsProfileSupported(CG_PROFILE_ARBFP1) )
		g_CGprofile_pixel = CG_PROFILE_ARBFP1;
    else if( cgGLIsProfileSupported(CG_PROFILE_FP30) )
        g_CGprofile_pixel = CG_PROFILE_FP30;
	else if( cgGLIsProfileSupported(CG_PROFILE_FP20) )
        g_CGprofile_pixel = CG_PROFILE_FP20;
    else
    {
		ShaderWater=false;
        ShaderLight=false;
		ShaderBloom=false;
		return;
    }

	//if(( !cgGLIsProfileSupported(CG_PROFILE_FP40) )&&(cgGLIsProfileSupported(CG_PROFILE_GLSLF)))
	//	g_CGprofile_pixel_GlSL=CG_PROFILE_GLSLF;
	//else
	//	g_CGprofile_pixel_GlSL=g_CGprofile_pixel;
	// Create the context...
	g_CGcontext = cgCreateContext();

	//
	// Create the vertex and pixel shader...
	//
	/*
	g_CGbasicLight_vertex = cgCreateProgramFromFile( g_CGcontext,
										          CG_SOURCE,
										         "vertex_basicLight.cg",
										         g_CGprofile_pixel,
										         NULL, 
										         NULL );
	g_CGHighLight_vertex = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"vertex_HighLight.cg",
												g_CGprofile_vertex,
												NULL,
												NULL );
	
	g_CGHighLight_pixel = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"pixel_HighLight.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );*/
	g_CGvertex_t = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"vertex_t.cg",
												g_CGprofile_vertex,
												NULL,
												NULL );
	/*
	g_CGpixel_t = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"pixel_t.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );
	*/

	g_CGpixel_NOBloom = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"pixel_NOBloom_HighShadow.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );


	g_CGpixel_NOBloom_Low_shadow = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"pixel_NOBloom.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );

	g_CGpixel_NONormalMap = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"pixel_NONormalMap.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );

	g_CGRenderShadowMap_vertex = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"RenderShadowMap_vertex.cg",
												g_CGprofile_vertex,
												NULL,
												NULL );
	g_CGRenderShadowMap_pixel = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"RenderShadowMap_pixel.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );
/*
	g_BloomL1_pixel = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"g_BloomL1_pixel.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );

	g_BloomL2_pixel = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"g_BloomL2_pixel.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );

	g_BloomL3_pixel = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"g_BloomL3_pixel.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );*/
	g_Sea_vertex = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"Sea_vertex.cg",
												g_CGprofile_vertex,
												NULL,
												NULL );
	g_Sea_pixel = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"Sea_pixel.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );

	g_BloomW_pixel = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"BloomW_pixel.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );
	g_BloomH_pixel = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"BloomH_pixel.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );

	g_BloomMap_pixel = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"BloomMap_pixel.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );
	g_ToneMapping_pixel = cgCreateProgramFromFile( g_CGcontext,
												CG_SOURCE,
												"ToneMapping_pixel.cg",
												g_CGprofile_pixel,
												NULL,
												NULL );
	//
	// Load the programs using Cg's expanded interface...
	//

	//cgGLLoadProgram(g_BloomL1_pixel);
	//cgGLLoadProgram(g_BloomL2_pixel);
	//cgGLLoadProgram(g_BloomL3_pixel);
	//cgGLLoadProgram( g_CGbasicLight_vertex );
	//cgGLLoadProgram( g_CGHighLight_vertex );
	//cgGLLoadProgram( g_CGHighLight_pixel  );
	
	//cgGLLoadProgram( g_CGpixel_t  );
	//if(!UseHighShadow)
	//	g_CGpixel_NOBloom=g_CGpixel_NOBloom_Low_shadow;
	//cgGLLoadProgram( g_CGpixel_NOBloom  );
	//CGerror GetCGerror=cgGetError();
	if((g_CGprofile_pixel != CG_PROFILE_FP40)||(ShadowLevel==1))
	{
		if(ShadowLevel>1)
			ShadowLevel=1;
		UseHighShadow=false;
		g_CGpixel_NOBloom=g_CGpixel_NOBloom_Low_shadow;
	}
	cgGLLoadProgram( g_CGvertex_t );
	cgGLLoadProgram( g_CGpixel_NOBloom  );
	cgGLLoadProgram( g_CGpixel_NONormalMap  );
	cgGLLoadProgram( g_CGRenderShadowMap_vertex  );
	cgGLLoadProgram( g_CGRenderShadowMap_pixel  );
	cgGLLoadProgram(g_Sea_vertex);
	cgGLLoadProgram(g_Sea_pixel);
	cgGLLoadProgram(g_BloomW_pixel);
	cgGLLoadProgram(g_BloomH_pixel);
	cgGLLoadProgram(g_BloomMap_pixel);
	cgGLLoadProgram(g_ToneMapping_pixel);


	//
	// Bind some parameters by name so we can set them later...
	//

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
	return bLinked;
}
void InitGLSL()
{
	GLint glMaxVERTEX_UNIFORM_COMPONENTS=0;
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,&glMaxVERTEX_UNIFORM_COMPONENTS);

	if(glMaxVERTEX_UNIFORM_COMPONENTS==0)
		ShadowLevel=2;

	//char MaxVERTEX_UNIFORM_COMPONENTS[32]={0};
	//itoa(glMaxVERTEX_UNIFORM_COMPONENTS,MaxVERTEX_UNIFORM_COMPONENTS,10);
	//MessageBox( NULL, MaxVERTEX_UNIFORM_COMPONENTS, "!", MB_OK|MB_ICONEXCLAMATION );

	g_GLSLvertex = GLSL_CompileShader("vertex_t.glsl",GL_VERTEX_SHADER_ARB);
	if(ShadowLevel>=3)
		g_GLSLpixel = GLSL_CompileShader("pixel_NOBloom_HighShadow.glsl",GL_FRAGMENT_SHADER_ARB);
		//g_GLSLpixel = GLSL_CompileShader("pixel_NONormalMap.glsl",GL_FRAGMENT_SHADER_ARB);
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
	if(isGLSL)
		RenderShadowMapGLSL();
	else
		RenderShadowMapCG();

}
void RenderShadowMapCG()
{
		//cgSetParameter3fv(cgGetNamedParameter( g_CGRenderShadowMap_pixel, "UIalpha" ), UIalpha);

	//cgSetMatrixParameterfc(cgGetNamedParameter( g_CGRenderShadowMap_vertex, "ShadowMapmvmatrix" ),ShadowMapmvmatrix);
	//cgSetMatrixParameterfc(cgGetNamedParameter( g_CGRenderShadowMap_vertex, "ShadowMapprojmatrix" ),ShadowMapprojmatrix);
	//cgSetStateMatrixParameter ("modelViewProj2", CG_GL_MODELVIEW_PROJECTION_MATRIX);
	//cgGLSetStateMatrixParameter
	//bind the cg program
	cgGLBindProgram( g_CGRenderShadowMap_vertex );
	cgGLEnableProfile( g_CGprofile_vertex );
	cgGLBindProgram( g_CGRenderShadowMap_pixel );
	cgGLEnableProfile( g_CGprofile_pixel );
}
void RenderShadowMapGLSL()
{
	glUseProgramObjectARB( GLSL_RenderShadowMap );
}
void shaderT(int MainTex,int NormalTex,int SpecularTex,int ShadowMapTexID,float HDlight)
{
	if(isGLSL)
		shaderTGLSL(MainTex,NormalTex,SpecularTex,ShadowMapTexID,HDlight);
	else
		shaderTCG(MainTex,NormalTex,SpecularTex,ShadowMapTexID,HDlight);
}
void shaderTCG(int MainTex,int NormalTex,int SpecularTex,int ShadowMapTexID,float HDlight)//bool UseBloom=false
{/*
	if(Keb[0])
	Ke[0]=Ke[0]+0.02f;
	else
		Ke[0]=Ke[0]-0.02f;
	if((Ke[0]<0.0)||(Ke[0]>1.0))
		Keb[0]=!Keb[0];
	if(Keb[1])
	Ke[1]=Ke[1]+0.02f;
	else
		Ke[1]=Ke[1]-0.02f;
	if((Ke[1]<0.0)||(Ke[1]>1.0))
		Keb[1]=!Keb[1];
	if(Keb[2])
	Ke[2]=Ke[2]+0.02;
	else
		Ke[2]=Ke[2]-0.02;
	if((Ke[2]<0.0)||(Ke[2]>1.0))
		Keb[2]=!Keb[2];
		
	Ke[2]=Ke[2]-0.04f;
	if(Ke[2]<0.0)
		Ke[2]=1.0;
*/
	/*
	if(UseBloom)
	{
		g_CGparam_ShadowMapTexture = cgGetNamedParameter(g_CGpixel_t, "ShadowMapTexture");
		cgGLSetTextureParameter( g_CGparam_ShadowMapTexture, img );
		//g_CGparam_ShadowMapTexture = cgGetNamedParameter(g_CGvertex_t, "ShadowMapTexture");
		cgSetParameter1f(cgGetNamedParameter( g_CGvertex_t, "testnum" ), testNum2);
		cgSetMatrixParameterfc(cgGetNamedParameter( g_CGvertex_t, "ShadowMapmvmatrix" ),ShadowMapmvmatrix);
		cgSetMatrixParameterfc(cgGetNamedParameter( g_CGvertex_t, "ShadowMapprojmatrix" ),ShadowMapprojmatrix);
		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_t, "globalAmbient" ), globalAmbient);
		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_t, "paraLightColor" ), paraLightColor);
		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_t, "paraLightDirection" ), paraLightDirection);
		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_t, "eyePosition"), eyePosition);
//		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_t, "Ke" ), Ke);
//		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_t, "Ka" ), Ka);
//		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_t, "Kd" ), Kd);
//		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_t, "Ks" ), Ks);
//		cgSetParameter1f(cgGetNamedParameter( g_CGpixel_t, "testnum" ), testNum2);
//		cgSetParameter1f(cgGetNamedParameter( g_CGpixel_t, "shininess" ), shininess);
		cgGLBindProgram( g_CGvertex_t );
		cgGLEnableProfile( g_CGprofile_vertex );
		cgGLBindProgram( g_CGpixel_t );
		cgGLEnableProfile( g_CGprofile_pixel );
		cgGLEnableTextureParameter( g_CGparam_ShadowMapTexture );
	}
	else
	{
		
*/
	if((NormalTex==0)||(ShadowLevel<1))
		g_CGpixel_NOBloom=g_CGpixel_NONormalMap;

		g_CGparam_ShadowMapTexture = cgGetNamedParameter(g_CGpixel_NOBloom, "ShadowMapTexture");
		cgGLSetTextureParameter( g_CGparam_ShadowMapTexture, ShadowMapTexID );
		g_CGparam_AmbientReflective = cgGetNamedParameter(g_CGpixel_NOBloom, "AmbientReflectiveTexture");
		cgGLSetTextureParameter( g_CGparam_AmbientReflective, AmbientReflectiveTexture );
		g_CGparam_NormalMapTexture = cgGetNamedParameter(g_CGpixel_NOBloom, "NormalMapTexture");
		cgGLSetTextureParameter( g_CGparam_NormalMapTexture, NormalTex );
		g_CGparam_SpecularMapTexture = cgGetNamedParameter(g_CGpixel_NOBloom, "SpecularMapTexture");
		cgGLSetTextureParameter( g_CGparam_SpecularMapTexture, SpecularTex );


		//g_CGparam_ShadowMapTexture = cgGetNamedParameter(g_CGvertex_t, "ShadowMapTexture");

		//cgSetParameter1f(cgGetNamedParameter( g_CGvertex_t, "testnum" ), testNum2);
		cgSetMatrixParameterfc(cgGetNamedParameter( g_CGvertex_t, "ShadowMapmvmatrix" ),ShadowMapmvmatrix);
		cgSetMatrixParameterfc(cgGetNamedParameter( g_CGvertex_t, "ShadowMapprojmatrix" ),ShadowMapprojmatrix);

		if(HDlight<0.0f)
			HDlight=0.0f;
		if(HDlight>1.0f)
			HDlight=1.0f;
		HDglobalAmbient[0]=globalAmbient[0]*HDlight;
		HDglobalAmbient[1]=globalAmbient[1]*HDlight;
		HDglobalAmbient[2]=globalAmbient[2]*HDlight;
		cgSetMatrixParameterfc(cgGetNamedParameter( g_CGvertex_t, "ShadowMapMVPmatrix" ),ShadowMapMVPmatrix);
		cgSetParameter4fv(cgGetNamedParameter( g_CGvertex_t, "MissleLightDirection" ),MissleLightDirection);
		cgSetParameter3fv(cgGetNamedParameter( g_CGvertex_t, "paraLightColor" ),MissleLightColor);
		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_NOBloom, "globalAmbient" ), HDglobalAmbient);
		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_NOBloom, "paraLightColor" ), paraLightColor);
		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_NOBloom, "paraLightDirection" ), paraLightDirection);
		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_NOBloom, "eyePosition"), eyePosition);
		cgSetMatrixParameterfc(cgGetNamedParameter( g_CGpixel_NOBloom, "Worldmatrix" ),Worldmatrix);
//		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_NOBloom, "Ke" ), Ke);
//		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_NOBloom, "Ka" ), Ka);
//		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_NOBloom, "Kd" ), Kd);
//		cgSetParameter3fv(cgGetNamedParameter( g_CGpixel_NOBloom, "Ks" ), Ks);
//		cgSetParameter1f(cgGetNamedParameter( g_CGpixel_NOBloom, "testnum" ), testNum2);
//		cgSetParameter1f(cgGetNamedParameter( g_CGpixel_NOBloom, "shininess" ), shininess);

		cgGLBindProgram( g_CGvertex_t );
		cgGLEnableProfile( g_CGprofile_vertex );
		cgGLBindProgram( g_CGpixel_NOBloom );
		cgGLEnableProfile( g_CGprofile_pixel );
		cgGLEnableTextureParameter( g_CGparam_ShadowMapTexture );
		cgGLEnableTextureParameter( g_CGparam_AmbientReflective );
		cgGLEnableTextureParameter( g_CGparam_NormalMapTexture );
		cgGLEnableTextureParameter( g_CGparam_SpecularMapTexture );

	
	//}
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
/*
void HighLight()
{


	cgSetMatrixParameterfc(cgGetNamedParameter( g_CGHighLight_vertex, "ShadowMapmvmatrix" ),ShadowMapmvmatrix);
	cgSetMatrixParameterfc(cgGetNamedParameter( g_CGHighLight_vertex, "ShadowMapprojmatrix" ),ShadowMapprojmatrix);
	cgSetMatrixParameterfc(cgGetNamedParameter( g_CGHighLight_vertex, "ShadowMapMVPmatrix" ),ShadowMapMVPmatrix);
	cgSetParameter3fv(cgGetNamedParameter( g_CGHighLight_pixel, "globalAmbient" ), globalAmbient);
	cgSetParameter3fv(cgGetNamedParameter( g_CGHighLight_pixel, "paraLightColor" ), paraLightColor);
	cgSetParameter3fv(cgGetNamedParameter( g_CGHighLight_pixel, "paraLightDirection" ), paraLightDirection);
	cgSetParameter3fv(cgGetNamedParameter( g_CGHighLight_pixel, "eyePosition"), eyePosition);

	cgGLBindProgram( g_CGHighLight_vertex );
	cgGLEnableProfile( g_CGprofile_vertex );
	cgGLBindProgram( g_CGHighLight_pixel );
	cgGLEnableProfile( g_CGprofile_pixel );

}
*/
/*
void BasicLight()
{

	if(BloomLevel==0)
		cgGLBindProgram( g_CGbasicLight_vertex );
	if(BloomLevel==1)
		cgGLBindProgram( g_BloomL1_pixel );
	if(BloomLevel==2)
		cgGLBindProgram( g_BloomL2_pixel );
	if(BloomLevel==3)
		cgGLBindProgram( g_BloomL3_pixel );
	cgGLEnableProfile( g_CGprofile_pixel );
	
	//cgGLDisableProfile( g_CGprofile_vertex );
}
*/
void DrawSea(float seaframe)
{
	if(isGLSL)
		DrawSeaGLSL(seaframe);
	else
		DrawSeaCG(seaframe);
}
void DrawSeaCG(float seaframe)
{
	seatime=seatime+seaframe/200.0f;
	if(seatime>1.0f)
		seatime=seatime-1.0f;
	cgSetParameter1f(cgGetNamedParameter( g_Sea_vertex, "time"), seatime);
		g_CGparam_AmbientReflectiveSea = cgGetNamedParameter(g_Sea_pixel, "AmbientReflectiveTexturSea");
		cgGLSetTextureParameter( g_CGparam_AmbientReflectiveSea, AmbientReflectiveTexture );

		cgSetParameter3fv(cgGetNamedParameter( g_Sea_pixel, "globalAmbient" ), globalAmbient);
		cgSetParameter3fv(cgGetNamedParameter( g_Sea_pixel, "paraLightColor" ), paraLightColor);
		cgSetParameter3fv(cgGetNamedParameter( g_Sea_pixel, "paraLightDirection" ), LightSunPos);
		cgSetParameter3fv(cgGetNamedParameter( g_Sea_pixel, "eyePosition"), eyePositionSea);
		cgSetParameter3fv(cgGetNamedParameter( g_Sea_pixel, "FogColor"), pixelfogColor);
		//cgSetParameter1f(cgGetNamedParameter( g_Sea_pixel, "time"), seatime);
		cgGLBindProgram( g_Sea_vertex );
		cgGLEnableProfile( g_CGprofile_vertex );
		cgGLBindProgram( g_Sea_pixel );
		cgGLEnableProfile( g_CGprofile_pixel );
		cgGLEnableTextureParameter( g_CGparam_AmbientReflectiveSea );
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
}
void DrawBloomMap(int WinW,int WinH)
{
	if(isGLSL)
		DrawBloomMapGLSL(WinW,WinH);
	else
		DrawBloomMapCG(WinW,WinH);
}
void DrawBloomMapCG(int WinW,int WinH)
{
	cgSetParameter1f(cgGetNamedParameter( g_BloomMap_pixel, "AveLum"), 0.23f);
	cgSetParameter1f(cgGetNamedParameter( g_BloomMap_pixel, "imgW"), (float)WinW);
	cgSetParameter1f(cgGetNamedParameter( g_BloomMap_pixel, "imgH"), (float)WinH);
	cgGLBindProgram( g_BloomMap_pixel );
	cgGLEnableProfile( g_CGprofile_pixel );
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
	if(isGLSL)
		DrawBloomWGLSL(WinW);
	else
		DrawBloomWCG(WinW);
}
void DrawBloomWCG(int WinW)
{
	cgSetParameter1f(cgGetNamedParameter( g_BloomW_pixel, "imgW"), (float)WinW);
	cgGLBindProgram( g_BloomW_pixel );
	cgGLEnableProfile( g_CGprofile_pixel );
}
void DrawBloomWGLSL(int WinW)
{
	glUseProgramObjectARB( GLSL_DrawBloomW );
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomW,"_imgW1"),(float)WinW);
	glUniform1i(glGetUniformLocation(GLSL_DrawBloomW,"_texSrc1"),0);
}
void DrawBloomH(int WinH)
{
	if(isGLSL)
		DrawBloomHGLSL(WinH);
	else
		DrawBloomHCG(WinH);
}
void DrawBloomHCG(int WinH)
{
	cgSetParameter1f(cgGetNamedParameter( g_BloomH_pixel, "imgH"), (float)WinH);
	cgGLBindProgram( g_BloomH_pixel );
	cgGLEnableProfile( g_CGprofile_pixel );
}
void DrawBloomHGLSL(int WinH)
{
	glUseProgramObjectARB( GLSL_DrawBloomH );
	glUniform1f(glGetUniformLocation(GLSL_DrawBloomH,"_imgH1"),(float)WinH);
	glUniform1i(glGetUniformLocation(GLSL_DrawBloomH,"_texSrc1"),0);
}
void ToneMapping()
{
	if(isGLSL)
		ToneMappingGLSL();
	else
		ToneMappingCG();
}
void ToneMappingCG()
{
	cgGLBindProgram( g_ToneMapping_pixel );
	cgGLEnableProfile( g_CGprofile_pixel );
}
void ToneMappingGLSL()
{
	glUseProgramObjectARB( GLSL_ToneMapping );
	glUniform1i(glGetUniformLocation(GLSL_ToneMapping,"_texSrc1"),0);
}
void BackFire()
{
	if(isGLSL)
		BackFireGLSL();
	else
		BackFireCG();
}
void BackFireCG()
{
}
void BackFireGLSL()
{
	glUseProgramObjectARB( GLSL_BackFire );
	glUniform3fv(glGetUniformLocation(GLSL_BackFire,"BackFireEyeDir"),1,BackFireEyeDir);
	glUniform4fv(glGetUniformLocation(GLSL_BackFire,"BackFireColor"),1,BackFireColor);
}
void CGDisableProfilePixel()
{
	if(isGLSL)
		glUseProgramObjectARB( NULL );
	else
		cgGLDisableProfile( g_CGprofile_pixel );
}
void CGDisableProfileVertex()
{
	if(isGLSL)
		glUseProgramObjectARB( NULL );
	else
		cgGLDisableProfile( g_CGprofile_vertex );
}
void CGDisableTextureParameterShadowMap()
{
	if(!isGLSL)
	cgGLDisableTextureParameter( g_CGparam_ShadowMapTexture );
	else
		glActiveTexture(GL_TEXTURE0);
}
void CGDisableTextureParameterAmbientReflective()
{
	if(!isGLSL)
	cgGLDisableTextureParameter( g_CGparam_AmbientReflective );
	else
		glActiveTexture(GL_TEXTURE0);
}
void CGDisableTextureParameterNormalMap()
{
	if(!isGLSL)
	cgGLDisableTextureParameter( g_CGparam_NormalMapTexture );
	else
		glActiveTexture(GL_TEXTURE0);
}
void CGDisableTextureParameterSpecularMap()
{
	if(!isGLSL)
	cgGLDisableTextureParameter( g_CGparam_SpecularMapTexture );
	else
		glActiveTexture(GL_TEXTURE0);
}
void CGDisableTextureParameterAmbientReflectiveSea()
{
	if(!isGLSL)
	cgGLDisableTextureParameter( g_CGparam_AmbientReflectiveSea );
	else
		glActiveTexture(GL_TEXTURE0);
}


void CGDisableBackFire()
{
	if(isGLSL)
		glUseProgramObjectARB( NULL );

}