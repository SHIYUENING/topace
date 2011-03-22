#version 120
varying vec2 ShadowDepth;
void main()
{
	gl_FragColor=vec4(ShadowDepth.x,1.0,1.0,ShadowDepth.y);
    return;
} 
