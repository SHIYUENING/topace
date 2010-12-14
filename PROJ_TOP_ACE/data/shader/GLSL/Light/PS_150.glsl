#version 150
uniform ivec2 LightNums;
uniform sampler2D DiffuseTex;
uniform float DiffuseTexTurnY;

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
out vec4 FragColor;
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
	vec4 DiffuseTexColor = texture2D(DiffuseTex, TexCoordDiffuse.xy);
	vec2 LightVal=vec2(0.0,0.0);
	vec4 DiffuseColor=vec4(0.0,0.0,0.0,0.0);
	vec4 SpecularColor=vec4(0.0,0.0,0.0,0.0);
	for(int i=0;i<8;i++)
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
		DiffuseColor += LightVal.x * OmniLight_Color[i] * Material_diffuse ;
		SpecularColor += LightVal.y * OmniLight_Color[i] * Material_specular ;
	}

	FragColor=DiffuseTexColor *(Global_Ambient+DiffuseColor+Material_emission)+SpecularColor;
	FragColor.w=DiffuseTexColor.w;
    return;
} 

