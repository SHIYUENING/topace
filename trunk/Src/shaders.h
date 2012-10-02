#pragma once


//初始化shader
void InitShader();
void InitCG();
void InitGLSL();
//使用shader
void RenderShadowMap();
//void RenderShadowMapCG();
void RenderShadowMapGLSL();
void shaderT(int MainTex,int NormalTex=0,int SpecularTex=0,int ShadowMapTexID=0,float HDlight=1.0f);
//void shaderTCG(int MainTex,int NormalTex=0,int SpecularTex=0,int ShadowMapTexID=0,float HDlight=1.0f);
void shaderTGLSL(int MainTex,int NormalTex=0,int SpecularTex=0,int ShadowMapTexID=0,float HDlight=1.0f);
void DrawSea(float seaframe=1.0f);
//void DrawSeaCG(float seaframe=1.0f);
void DrawSeaGLSL(float seaframe=1.0f);
void DrawBloomMap(int WinW,int WinH);
//void DrawBloomMapCG(int WinW,int WinH);
void DrawBloomMapGLSL(int WinW,int WinH);
void DrawBloomW(int WinW);
//void DrawBloomWCG(int WinW);
void DrawBloomWGLSL(int WinW);
void DrawBloomH(int WinH);
//void DrawBloomHCG(int WinH);
void DrawBloomHGLSL(int WinH);
void ToneMapping();
//void ToneMappingCG();
void ToneMappingGLSL();
void BackFire();
//void BackFireCG();
void BackFireGLSL();
void CGDisableProfilePixel();
//void CGDisableProfilePixelCG();
//void CGDisableProfilePixelGLSL();
void CGDisableProfileVertex();
//void CGDisableProfileVertexCG();
//void CGDisableProfileVertexGLSL();
void CGDisableTextureParameterShadowMap();
//void CGDisableTextureParameterShadowMapCG();
//void CGDisableTextureParameterShadowMapGLSL();
void CGDisableTextureParameterAmbientReflective();
//void CGDisableTextureParameterAmbientReflectiveCG();
//void CGDisableTextureParameterAmbientReflectiveGLSL();
void CGDisableTextureParameterNormalMap();
//void CGDisableTextureParameterNormalMapCG();
//void CGDisableTextureParameterNormalMapGLSL();
void CGDisableTextureParameterSpecularMap();
//void CGDisableTextureParameterSpecularMapCG();
//void CGDisableTextureParameterSpecularMapGLSL();
void CGDisableTextureParameterAmbientReflectiveSea();
//void CGDisableTextureParameterAmbientReflectiveSeaCG();
//void CGDisableTextureParameterAmbientReflectiveSeaGLSL();
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
