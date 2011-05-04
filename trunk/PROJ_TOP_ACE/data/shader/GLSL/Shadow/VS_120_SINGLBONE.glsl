#version 110
uniform mat4 MVPMatrix;
attribute vec3 Position_in;
attribute vec2 TexCoord0_in;
varying vec2 TexCoord0;
void main()
{
	TexCoord0=TexCoord0_in;
	gl_Position = MVPMatrix * vec4(Position_in,1.0);
    return;
}
