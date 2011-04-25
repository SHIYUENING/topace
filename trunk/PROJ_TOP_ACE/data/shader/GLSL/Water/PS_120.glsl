#version 110
uniform mat4 WMatrix;

uniform sampler2D DiffuseTex;
uniform sampler2D NormalTex;
uniform sampler2DShadow ShadowTex;
uniform samplerCube RefCubeTex;

uniform vec4 OmniLight_Pos[8];
uniform vec4 OmniLight_Color[8];
uniform vec4 Material[3];
uniform vec4 Global_Ambient;
#define Material_diffuse Material[0]
#define Material_specular Material[1]
#define Material_emission Material[2]
#define Material_shininess Material[2].w
#define Material_specularlevel Material[1].w

varying vec4 VertexEyeDir; 
varying vec4 ShadowDir;
varying vec2 WaterTexCoords[4]; 
varying vec2 TexCoord0OUT;
varying mat4 MMatrixPS;
vec2 OmniLight(vec4 LightPosEyeIn,float LightShininess,vec3 texNormals)
{
	vec3 LightDir = normalize( LightPosEyeIn.xyz - VertexEyeDir.xyz );
	float NdotL = dot(texNormals,LightDir);
	float specular = 0.0;

	vec3 HightLight =normalize( LightDir - normalize(VertexEyeDir.xyz));
	specular = pow(max(dot(texNormals, HightLight), 0.0), LightShininess);

	NdotL = max(0.0,NdotL);
	return vec2(NdotL,specular);
}
void main()
{
	vec3 texNormals; 
	texNormals= texture2D(NormalTex, WaterTexCoords[0]).xyz;
	texNormals= texture2D(NormalTex, WaterTexCoords[1]).xyz+texNormals;
	texNormals= texture2D(NormalTex, WaterTexCoords[2]).xyz+texNormals;
	texNormals= texture2D(NormalTex, WaterTexCoords[3]).xyz+texNormals;
	
	texNormals=normalize(texNormals);
	texNormals=texNormals*2.0-1.0;
	texNormals.xy=texNormals.xy*1.5;
	texNormals=(MMatrixPS*vec4(texNormals,0.0)).xyz;
	texNormals=normalize(texNormals);
	vec4 shadowPos=ShadowDir;
	float Shadow=shadow2DProj( ShadowTex, shadowPos ).x;

	vec2 LightVal = OmniLight (OmniLight_Pos[0],Material_shininess,texNormals)*Shadow;
	vec4 DiffuseColor=LightVal.x * OmniLight_Color[0] * Material_diffuse;
	vec4 SpecularColor=LightVal.y * OmniLight_Color[0] * Material_specular;

	float NOF=1.0-dot(texNormals,- normalize(VertexEyeDir.xyz))*0.5;
	NOF=pow(NOF,2.0);
	//NOF=max(0.0,NOF)*0.25;
	vec3 Reflective=reflect( - normalize(VertexEyeDir.xyz),texNormals);
    vec4 ReflectiveWorld = WMatrix*vec4(Reflective,0.0);
	//float REFC=Material_shininess*0.015;

	gl_FragColor=vec4(0.1,1.0,0.9,1.0)*(Global_Ambient+DiffuseColor+Material_emission)*(1.0-NOF)+SpecularColor+textureCube(RefCubeTex, ReflectiveWorld.xyz)*NOF;
	gl_FragColor.w=Material_diffuse.w+SpecularColor.w+NOF;
	//gl_FragColor.xyz=texNormals.xyz;
	//gl_FragColor=textureCube(RefCubeTex, ReflectiveWorld.xyz);
	gl_FragColor.w=1.0;
    return;
} 
