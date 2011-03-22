#version 120
uniform mat4x4 MVPMatrix;
attribute vec3 Position_in;
varying vec2 ShadowDepth;
void main()
{
	vec4 MVP_Position = MVPMatrix * vec4(Position_in,1.0);
	ShadowDepth.x=MVP_Position.z/MVP_Position.w;
	ShadowDepth.y=ShadowDepth.x*ShadowDepth.x;
	gl_Position = MVP_Position;
    return;
}
