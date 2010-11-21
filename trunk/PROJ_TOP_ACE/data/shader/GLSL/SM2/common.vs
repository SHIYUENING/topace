#version 120
varying vec2 TexCoord0;
uniform mat4x4 MVPMatrix;
attribute vec2 TexCoord0_in;
void main()
{
	TexCoord0=TexCoord0_in.xy;
	gl_Position = MVPMatrix * gl_Vertex;
    //gl_FrontColor = gl_Color;
    //gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    return;
}
