#version 150
uniform mat4x4 MMatrix;
uniform mat4x4 MVPMatrix;
in vec3 Position_in;
in vec2 TexCoord0_in;
in vec3 Normal_in;
in vec4 Color_in;
out vec4 VertexEyeDir; 
out vec3 Normal; 
out vec2 TexCoord0;
out vec4 Color;
void main()
{
	VertexEyeDir = MMatrix * vec4(Position_in,1.0);
	gl_Position = MVPMatrix * vec4(Position_in,1.0);
    Color = Color_in;
    Normal =( MMatrix * vec4(Normal_in,0.0)).xyz;
	TexCoord0=TexCoord0_in .xy;
    return;
}
