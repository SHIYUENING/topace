#version 110
uniform mat4 WMatrix;
uniform ivec2 LightNums;
uniform vec4 TexTurnY;

uniform sampler2D DiffuseTex;
uniform sampler2DShadow ShadowTex;
uniform samplerCube RefCubeTex;
uniform sampler2D SpecularTex;

uniform vec4 OmniLight_Pos[8];
uniform vec4 OmniLight_Color[8];
uniform vec4 Material[3];
uniform vec4 Global_Ambient;
#define Material_diffuse Material[0]
#define Material_specular Material[1]
#define Material_emission Material[2]
#define Material_shininess Material[2].w
#define Material_specularlevel Material[1].w
#define TEXTurnYDIF TexTurnY.x
#define TEXTurnYSPE TexTurnY.y
#define TEXTurnYREF TexTurnY.z
#define TEXTurnYNOR TexTurnY.w
varying vec4 VertexEyeDir; 
varying vec3 Normal; 
varying vec2 TexCoord0;
varying vec4 Color;
varying vec4 ShadowDir;
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
void main()
{
	vec2 TexCoordDiffuse;
	TexCoordDiffuse.x=TexCoord0.x;
	TexCoordDiffuse.y=TexTurnY.x*TexCoord0.y;
	vec2 TexCoordTMP=TexCoord0.xy;
	TexCoordTMP.y=TexCoordTMP.y*TEXTurnYSPE;
	vec4 SpecularTexColor = texture2D(SpecularTex, TexCoordTMP);

	vec4 shadowPos=ShadowDir-vec4(0.0,0.0,0.0025,0.0);
	float Shadow=shadow2DProj( ShadowTex, shadowPos ).x;

	vec4 DiffuseTexColor = texture2D(DiffuseTex, TexCoordDiffuse.xy)*abs(TEXTurnYDIF)+(1.0-abs(TEXTurnYDIF))*Material_diffuse;
	vec2 LightVal = OmniLight (OmniLight_Pos[0],Material_shininess)*Shadow;
	vec4 DiffuseColor=LightVal.x * OmniLight_Color[0];
	vec4 SpecularColor=LightVal.y * OmniLight_Color[0] * Material_specular;

	float NOF=1.0-abs(dot(Normal,- normalize(VertexEyeDir.xyz)));
	NOF=max(0.0,NOF)*0.25;
	vec3 Reflective=reflect( - normalize(VertexEyeDir.xyz),Normal);
    vec4 ReflectiveWorld = WMatrix*vec4(Reflective,0.0);
	float REFC=Material_shininess*0.002;

	//gl_FragColor=DiffuseTexColor *(Global_Ambient+DiffuseColor+Material_emission)+SpecularColor+textureCube(RefCubeTex, ReflectiveWorld.xyz)*REFC;
	gl_FragColor=DiffuseTexColor *(Global_Ambient+DiffuseColor+Material_emission+SpecularTexColor.a)+SpecularColor*(SpecularTexColor.y+SpecularTexColor.x*Material_specularlevel);
	gl_FragColor.w=DiffuseTexColor.w*Material_diffuse.w+SpecularColor.w+NOF;
	//gl_FragColor.xyz=textureCube(RefCubeTex, ReflectiveWorld.xyz).xyz;
	//gl_FragColor.xyz=DiffuseTexColor.xyz;
    return;
} 
