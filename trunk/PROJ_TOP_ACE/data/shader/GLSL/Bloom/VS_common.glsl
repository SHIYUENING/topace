#version 110
varying vec2 TexCoord0;
uniform mat4 MVPMatrix;
attribute vec2 Position_in;
attribute vec2 TexCoord0_in;
void main()
{
	TexCoord0 = TexCoord0_in.xy;
	gl_Position = MVPMatrix * vec4(Position_in,0.0,1.0);
    return;
}
