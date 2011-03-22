#version 150
uniform mat4x4 WMatrix;
uniform ivec2 LightNums;
uniform float DiffuseTexTurnY;

uniform sampler2D DiffuseTex;
uniform samplerCube RefCubeTex;
uniform sampler2D ShadowTex;

uniform vec4 OmniLight_Pos[8];
uniform vec4 OmniLight_Color[8];
uniform vec4 Material[3];
uniform vec4 Global_Ambient;
#define Material_diffuse Material[0]
#define Material_specular Material[1]
#define Material_emission Material[2]
#define Material_shininess Material[2].w

in vec4 VertexEyeDir; 
in vec3 Normal; 
in vec2 TexCoord0;
in vec4 Color;
in vec4 ShadowDir;
out vec4 FragColor;
float ChebyshevUpperBound( vec2 moments, float t, float minVariance)
{
 // Standard shadow map comparison
 float p = t<=moments.x?1.0:0.0;

 // compute probabilistic upper bound
 float variance = moments.y - ( moments.x*moments.x);
 variance = max( variance, minVariance);

 // compute probabilistic upper bound
 float d = t - moments.x;
 float p_max = variance / ( variance + d*d);

 return max( p, p_max);
}

//--------------------------------------------------------
// variance shadow map
//
#define g_lbrAmount  0.18f;

float tex2DSM(vec4 posInLightSpace)
{
 vec4 projPos = posInLightSpace / posInLightSpace.w;

 // soft shadow
 vec2 moments = texture2D( ShadowTex, projPos.xy).xw;

 float shadowContrib = ChebyshevUpperBound( moments, projPos.z, 0.00001f);


 return clamp( smoothstep( 0.18f, 1.0, shadowContrib) + 0.4f, 0.0, 1.0);
}

vec2 OmniLight(vec4 LightPosEyeIn,float LightShininess)
{
	vec3 Nor=normalize(Normal);
	vec3 LightDir = normalize( LightPosEyeIn.xyz - VertexEyeDir.xyz );
	float NdotL = dot(Nor,LightDir);
	float specular = 0.0;

	vec3 HightLight =normalize( LightDir - normalize(VertexEyeDir.xyz));
	specular = pow(max(dot(Nor, HightLight), 0.0), LightShininess);

	NdotL = max(0.0,NdotL);
	return vec2(NdotL,specular);
}
/*
vec2 SpotLight(vec4 LightPosEyeIn,vec3 LightTGTPosEyeIn,float spotCosCutoff,float spotExponent,float LightShininess)
{
	vec3 Nor=normalize(Normal);
	vec3 LightDir = normalize( LightPosEyeIn.xyz - VertexEyeDir.xyz );
	float NdotL = dot(Nor,LightDir);
	float specular = 0.0;
	float spotEffect = dot(normalize(LightTGTPosEyeIn),-LightDir);
	
	if(spotEffect > spotCosCutoff)
	{
		//spotEffect = pow((spotEffect-spotCosCutoff*2.0),spotExponent);
		//float spotCosFalloff = pow(spotCosCutoff,spotExponent);
		//spotEffect = (spotCosFalloff- spotEffect)/(spotCosFalloff-spotCosCutoff);
		spotEffect = pow(spotEffect,spotExponent);
		vec3 HightLight =normalize( LightDir - normalize(VertexEyeDir.xyz));
		specular = pow(max(dot(Nor, HightLight), 0.0), LightShininess);

		NdotL = max(0.0,NdotL);
		NdotL = NdotL*spotEffect;
		specular = specular*spotEffect;
	}
	else
	{
		NdotL = 0.0;
	}
	return vec2(NdotL,specular);
}
*/
void main()
{
	vec2 TexCoordDiffuse;
	TexCoordDiffuse.x=TexCoord0.x;
	TexCoordDiffuse.y=DiffuseTexTurnY*TexCoord0.y;

	vec4 MX=vec4 (0.001,0.0,0.0,0.0);
	vec4 MU=vec4 (0.0,0.001,0.0,0.0);
	vec4 shadowPos=ShadowDir-vec4(0.0,0.0,0.0025,0.0);
	/*float Shadow=shadow2DProj( ShadowTex, shadowPos ).x;
	Shadow=Shadow+shadow2DProj( ShadowTex, shadowPos+MX ).x;
	Shadow=Shadow+shadow2DProj( ShadowTex, shadowPos-MX ).x;
	Shadow=Shadow+shadow2DProj( ShadowTex, shadowPos+MU ).x;
	Shadow=Shadow+shadow2DProj( ShadowTex, shadowPos-MU ).x;
	Shadow=Shadow+shadow2DProj( ShadowTex, shadowPos+MX+MU ).x;
	Shadow=Shadow+shadow2DProj( ShadowTex, shadowPos-MX+MU ).x;
	Shadow=Shadow+shadow2DProj( ShadowTex, shadowPos+MX-MU ).x;
	Shadow=Shadow+shadow2DProj( ShadowTex, shadowPos-MX-MU ).x;
	Shadow=Shadow/9.0;*/
	float Shadow=tex2DSM(shadowPos);
	vec4 DiffuseTexColor = texture2D(DiffuseTex, TexCoordDiffuse.xy);
	vec2 LightVal=OmniLight (OmniLight_Pos[0],Material_shininess);
	vec4 DiffuseColor=LightVal.x * OmniLight_Color[0]*Shadow;
	vec4 SpecularColor=LightVal.y * OmniLight_Color[0]*Shadow;

	for(int i=1;i<8;i++)
	{
		if(i<LightNums.x)
		{
			LightVal=OmniLight (OmniLight_Pos[i],Material_shininess);
		}
		//else
		//{
		//	if(i<(LightNums.x+LightNums.y))
		//	{
		//		LightVal = SpotLight(gl_LightSource[i].position,gl_LightSource[i].spotDirection,gl_LightSource[i].spotCosCutoff,gl_LightSource[i].spotExponent,Material_shininess);
		//	}
		//}
		DiffuseColor += LightVal.x * OmniLight_Color[i] ;
		SpecularColor += LightVal.y * OmniLight_Color[i] ;
	}

	DiffuseColor=DiffuseColor*Material_diffuse;
	SpecularColor=SpecularColor*Material_specular;

	float NOF=1.0-abs(dot(Normal,vec3(0.0,0.0,1.0)));
	FragColor=DiffuseTexColor *(Global_Ambient+DiffuseColor+Material_emission)+SpecularColor;
	FragColor.w=DiffuseTexColor.w*Material_diffuse.w+SpecularColor.w+max(0.0f,NOF)*0.25;
    return;
} 

