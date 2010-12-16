#version 400

in vec3 Position_in;
in vec4 Normal_in;
in vec2 TexCoord0_in;
in vec4 Color_in;

out vec3 vPosition;
out vec4 vNormal; 
out vec2 vTexCoord0;
out vec4 vColor;
uniform mat4x4 MMatrix;
void main()
{
	vPosition	=	(MMatrix* vec4(Position_in, 1.0)).xyz;
	//vPosition	=	Position_in;
	vNormal		=	MMatrix* vec4(normalize(Normal_in.xyz),0.0);
	vNormal.w	=	Normal_in.w;
	vTexCoord0	=	TexCoord0_in;
	vColor		=	Color_in;
}
