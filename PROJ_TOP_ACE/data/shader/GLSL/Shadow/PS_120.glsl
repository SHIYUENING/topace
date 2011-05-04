#version 110

uniform vec4 TexTurnY;

uniform sampler2D DiffuseTex;
varying vec2 TexCoord0;
void main()
{
	gl_FragColor=vec4(1.0,1.0,1.0,texture2DLod(DiffuseTex,TexCoord0,0).a);
    return;
} 
