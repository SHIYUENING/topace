#pragma once


//初始化shader
void InitCG();
//使用shader
void RenderShadowMap();
void shaderT(int NormalTex=0,int SpecularTex=0,int ShadowMapTexID=0);
void DrawSea();
void DrawBloomMap(int WinW,int WinH);
void DrawBloomW(int WinW);
void DrawBloomH(int WinH);
void ToneMapping();
void CGDisableProfilePixel();
void CGDisableProfileVertex();
void CGDisableTextureParameterShadowMap();
void CGDisableTextureParameterAmbientReflective();
void CGDisableTextureParameterNormalMap();
void CGDisableTextureParameterSpecularMap();
void CGDisableTextureParameterAmbientReflectiveSea();
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
