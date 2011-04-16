#version 140
uniform mat4x4 WMatrix;
uniform ivec2 LightNums;
uniform vec4 TexTurnY=vec4(1.0,1.0,1.0,1.0);
uniform vec2 ShadowTexSize;

uniform sampler2D DiffuseTex;
uniform sampler2DShadow ShadowTex;
uniform samplerCube RefCubeTex;
uniform sampler2D NormalTex;
uniform sampler2D SpecularTex;

uniform vec4 OmniLight_Pos[8];
uniform vec4 OmniLight_Color[8];
uniform vec4 Material[3];
uniform vec4 Global_Ambient;
#define Material_diffuse Material[0]
#define Material_specular Material[1]
#define Material_emission Material[2]
#define Material_shininess Material[2].w
#define shadow2DProj textureProj
#define TEXTurnYDIF TexTurnY.x
#define TEXTurnYSPE TexTurnY.y
#define TEXTurnYREF TexTurnY.z
#define TEXTurnYNOR TexTurnY.w
in vec4 VertexEyeDir; 
in vec3 Normal; 
in vec2 TexCoord0;
in vec4 Color;
in vec4 ShadowDir;
in mat3x3 TBN;
out vec4 FragColor;
vec2 OmniLight(vec4 LightPosEyeIn,float LightShininess,vec3 LightNormal)
{
	vec3 Nor=normalize(LightNormal);
	vec3 LightDir = normalize( LightPosEyeIn.xyz - VertexEyeDir.xyz );
	float NdotL = dot(Nor,LightDir);
	float specular = 0.0;

	vec3 HightLight =normalize( LightDir - normalize(VertexEyeDir.xyz));
	specular = pow(max(dot(Nor, HightLight), 0.0), LightShininess);
	//specular = NdotL>0.0?specular:0.0;
	if(NdotL<=0.0) specular=0.0;
	NdotL = max(0.0,NdotL);
	return vec2(NdotL,specular);
}
void main()
{
	vec4 MX=vec4 (1.0/ShadowTexSize.x,0.0,0.0,0.0);
	vec4 MU=vec4 (0.0,1.0/ShadowTexSize.y,0.0,0.0);
	vec4 shadowPos=ShadowDir-vec4(0.0,0.0,0.0025,0.0);
	float Shadow=textureProj( ShadowTex, shadowPos );
	Shadow=Shadow+textureProj( ShadowTex, shadowPos+MX );
	Shadow=Shadow+textureProj( ShadowTex, shadowPos-MX );
	Shadow=Shadow+textureProj( ShadowTex, shadowPos+MU );
	Shadow=Shadow+textureProj( ShadowTex, shadowPos-MU );
	Shadow=Shadow+textureProj( ShadowTex, shadowPos+MX+MU );
	Shadow=Shadow+textureProj( ShadowTex, shadowPos-MX+MU );
	Shadow=Shadow+textureProj( ShadowTex, shadowPos+MX-MU );
	Shadow=Shadow+textureProj( ShadowTex, shadowPos-MX-MU );
	Shadow=Shadow+textureProj( ShadowTex, shadowPos+MX*2 );
	Shadow=Shadow+textureProj( ShadowTex, shadowPos-MX*2 );
	Shadow=Shadow+textureProj( ShadowTex, shadowPos+MU*2 );
	Shadow=Shadow+textureProj( ShadowTex, shadowPos-MU*2 );
	Shadow=Shadow/13.0;
	vec2 TexCoordTMP=TexCoord0.xy;
	TexCoordTMP.y=TexCoordTMP.y*TEXTurnYDIF;
	vec4 DiffuseTexColor = texture2D(DiffuseTex, TexCoordTMP);
	TexCoordTMP=TexCoord0.xy;
	TexCoordTMP.y=TexCoordTMP.y*TEXTurnYNOR;
	vec4 NormalTexColor = texture2D(NormalTex, TexCoordTMP);
	TexCoordTMP=TexCoord0.xy;
	TexCoordTMP.y=TexCoordTMP.y*TEXTurnYSPE;
	vec4 SpecularTexColor = texture2D(SpecularTex, TexCoordTMP);
	NormalTexColor=NormalTexColor*2.0-1.0;
//	NormalTexColor.z=NormalTexColor.z*2;
	NormalTexColor.y=-NormalTexColor.y;
	vec3 NormalTBN=TBN*normalize(NormalTexColor.xyz);
	vec2 LightVal=OmniLight (OmniLight_Pos[0],Material_shininess*SpecularTexColor.z,NormalTBN);
	vec4 DiffuseColor=LightVal.x * OmniLight_Color[0]*Shadow;
	vec4 SpecularColor=LightVal.y * OmniLight_Color[0]*Shadow;
	
	for(int i=1;i<LightNums.x;i++)
	{
		LightVal=OmniLight (OmniLight_Pos[i],Material_shininess*SpecularTexColor.z,NormalTBN);
		DiffuseColor += LightVal.x * OmniLight_Color[i] ;
		SpecularColor += LightVal.y * OmniLight_Color[i] ;
	}

	DiffuseColor=DiffuseColor*Material_diffuse;
	SpecularColor=SpecularColor*Material_specular;

	float NOF=1.0-abs(dot(Normal,vec3(0.0,0.0,1.0)));
	FragColor=DiffuseTexColor *(Global_Ambient+DiffuseColor+Material_emission+SpecularTexColor.a)+SpecularColor*(SpecularTexColor.y+SpecularTexColor.x*5.0);
	FragColor.w=DiffuseTexColor.w*Material_diffuse.w+SpecularColor.w+max(0.0f,NOF)*0.25;
	//FragColor.xyz=NormalTBN.xyz;
    return;
} 

