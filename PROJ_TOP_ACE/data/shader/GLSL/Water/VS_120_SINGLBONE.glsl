#version 110
uniform mat4 ShadowMatrix;
uniform mat4 MMatrix;
uniform mat4 MVPMatrix;
uniform vec4 WaterSet;
attribute vec3 Position_in;
attribute vec2 TexCoord0_in;
varying vec4 VertexEyeDir;
varying vec4 ShadowDir;
varying vec2 WaterTexCoords[4]; 
varying vec2 TexCoord0OUT;
varying mat4 MMatrixPS;
void main()
{
	MMatrixPS=MMatrix;
	VertexEyeDir = MMatrix * vec4(Position_in,1.0);
	gl_Position = MVPMatrix * vec4(Position_in,1.0);
	ShadowDir = ShadowMatrix * vec4(Position_in,1.0);
	TexCoord0OUT=TexCoord0_in;
	vec2 TexCoord0=TexCoord0_in;
	WaterTexCoords[0]=TexCoord0+WaterSet.xy;
	WaterTexCoords[1]=TexCoord0*2.0+WaterSet.zw*2.0;
	WaterTexCoords[2]=TexCoord0*3.0+WaterSet.xy*3.0;
	WaterTexCoords[3]=TexCoord0*4.0+WaterSet.zw*4.0;
    return;
}
