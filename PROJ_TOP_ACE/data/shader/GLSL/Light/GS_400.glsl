#version 400
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
in vec4 teVertexEyeDir[3];
in vec3 teNormal[3];
in vec2 teTexCoord0[3];
in vec4 teColor[3];

out vec4 VertexEyeDir; 
out vec3 Normal; 
out vec2 TexCoord0;
out vec4 Color;
void main()
{
	VertexEyeDir=vec4(1.0,1.0,1.0,1.0);
	Normal=vec3(1.0,1.0,1.0);
	TexCoord0=vec2(1.0,1.0);
	Color=vec4(1.0,1.0,1.0,1.0);
	gl_Position=vec4(1.0,1.0,1.0,1.0);
	for(int i=0;i<3;i++)
	{
		VertexEyeDir = teVertexEyeDir[i];
		Normal = teNormal[i];
		TexCoord0 = teTexCoord0[i];
		Color = teColor[i];
		gl_Position = gl_in[i].gl_Position; EmitVertex();
	}
    EndPrimitive();
}