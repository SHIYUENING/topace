#version 400

in vec3 Position_in;
in vec3 Normal_in;
in vec2 TexCoord0_in;
in vec4 Color_in;

out vec3 vPosition;
out vec3 vNormal; 
out vec2 vTexCoord0;
out vec4 vColor;
void main()
{
	vPosition	=	Position_in;
	vNormal		=	normalize(Normal_in);
	vTexCoord0	=	TexCoord0_in;
	vColor		=	Color_in;
}
