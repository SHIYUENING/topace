#version 120
uniform mat4x4 ShadowMatrix;
uniform mat4x4 MMatrix;
uniform mat4x4 MVPMatrix;
attribute vec3 Position_in;
attribute vec2 TexCoord0_in;
attribute vec4 Normal_in;
attribute vec4 Color_in;
varying vec4 VertexEyeDir; 
varying vec3 Normal; 
varying vec2 TexCoord0;
varying vec4 Color;
varying vec4 ShadowDir;
void main()
{
	VertexEyeDir = MMatrix * vec4(Position_in,1.0);
	gl_Position = MVPMatrix * vec4(Position_in,1.0);
	ShadowDir = ShadowMatrix * vec4(Position_in,1.0);
    Color = Color_in;
    Normal =( MMatrix * vec4(Normal_in.xyz,0.0)).xyz;
	TexCoord0=TexCoord0_in .xy;
    return;
}
