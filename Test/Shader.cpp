#include <Cg/Cg.h>
#include <Cg/cgGL.h>
#include "Shader.h"
#include <stdio.h>	
GLuint AmbientReflectiveTexture;
bool ShaderWater=true;
CGprofile   g_CGprofile_vertex;
CGprofile   g_CGprofile_pixel;
CGcontext   g_CGcontext;
CGprogram	g_Sea_vertex;
CGprogram	g_Sea_pixel;

CGparameter   g_CGparam_AmbientReflectiveSea;

CGparameter cg_globalAmbient;
CGparameter cg_lightColor;
CGparameter cg_lightPosition;
CGparameter cg_eyePosition;


float LightSunPos[3];
float globalAmbient[4]={0.5f,0.5f,0.5f,1.0f};
float paraLightColor[4]={0.5f,0.5f,0.5f,1.0f};
float paraLightDirection[3]={0.5f,1000000.0f,0.5f};
float eyePositionSea[3]={0.0f, 150.0f, 30.0f};
float pixelfogColor[3]={0.5f,0.5f,0.5f};
void InitCG()
{

    if( cgGLIsProfileSupported(CG_PROFILE_ARBVP1) )
        g_CGprofile_vertex = CG_PROFILE_ARBVP1;
    else if( cgGLIsProfileSupported(CG_PROFILE_VP40) )
        g_CGprofile_vertex = CG_PROFILE_VP40;
    else
    {
		ShaderWater=false;
        return;
    }

	
	if( cgGLIsProfileSupported(CG_PROFILE_ARBFP1) )
        g_CGprofile_pixel = CG_PROFILE_ARBFP1;
    else if( cgGLIsProfileSupported(CG_PROFILE_FP30) )
        g_CGprofile_pixel = CG_PROFILE_FP30;
	else if( cgGLIsProfileSupported(CG_PROFILE_FP20) )
        g_CGprofile_pixel = CG_PROFILE_FP20;
    else
    {
		ShaderWater=false;
		return;
    }
	g_CGcontext = cgCreateContext();
	
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
	cgGLLoadProgram(g_Sea_vertex);
	cgGLLoadProgram(g_Sea_pixel);
} 

void DrawSea()
{
	
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
void CGDisableTextureParameterAmbientReflectiveSea()
{
	cgGLDisableTextureParameter( g_CGparam_AmbientReflectiveSea );
}
void CGDisableProfilePixel()
{
	cgGLDisableProfile( g_CGprofile_pixel );
}
void CGDisableProfileVertex()
{
	cgGLDisableProfile( g_CGprofile_vertex );
}