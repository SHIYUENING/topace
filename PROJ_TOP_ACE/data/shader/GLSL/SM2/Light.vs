#version 120
uniform mat4x4 MMatrix;
uniform mat4x4 MVPMatrix;
attribute vec3 Position_in;
attribute vec2 TexCoord0_in;
attribute vec3 Normal_in;
attribute vec4 Color_in;
varying vec4 VertexEyeDir; 
varying vec3 Normal; 
varying vec2 TexCoord0;
varying vec4 Color;
void main()
{
	/*
	//VertexEyeDir = gl_ModelViewMatrix * gl_Vertex;
	//gl_Position = ftransform();
	VertexEyeDir = MMatrix * gl_Vertex;
	gl_Position = MVPMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;
    //gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    Normal =( MMatrix * vec4(gl_Normal,0.0)).xyz;
	TexCoord0=gl_MultiTexCoord0.xy;*/

	VertexEyeDir = MMatrix * vec4(Position_in,1.0);
	gl_Position = MVPMatrix * vec4(Position_in,1.0);
    Color = Color_in;
    Normal =( MMatrix * vec4(Normal_in,0.0)).xyz;
	TexCoord0=TexCoord0_in .xy;
    return;
}
