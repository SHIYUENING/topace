#version 140
uniform mat4x4 ShadowMatrix;
uniform mat4x4 MMatrix;
uniform mat4x4 MVPMatrix;
in vec3 Position_in;
in vec2 TexCoord0_in;
in vec4 Normal_in;
in vec4 Color_in;
in vec3 Tangent_in;
out vec4 VertexEyeDir; 
out vec3 Normal; 
out vec2 TexCoord0;
out vec4 Color;
out vec4 ShadowDir;
out mat3x3 TBN;
void main()
{
	VertexEyeDir = MMatrix * vec4(Position_in,1.0);
	gl_Position = MVPMatrix * vec4(Position_in,1.0);
	ShadowDir = ShadowMatrix * vec4(Position_in,1.0);
   // Color = Color_in;
    vec3 Normal_tmp =( MMatrix * vec4(Normal_in.xyz,0.0)).xyz;
	Normal=Normal_tmp;
	TexCoord0=TexCoord0_in .xy;
	vec3 Tangent=( MMatrix * vec4(Tangent_in.xyz,0.0)).xyz;
	vec3 Bionormal=cross(Tangent,Normal_tmp);
	TBN=mat3(Tangent,Bionormal,Normal_tmp);
    return;
}
