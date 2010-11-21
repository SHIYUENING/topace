#version 150
uniform mat4x4 MMatrix;
uniform mat4x4 MVPMatrix;
out vec4 VertexEyeDir; 
out vec3 Normal; 
out vec2 TexCoord0;
void main()
{
	//VertexEyeDir = gl_ModelViewMatrix * gl_Vertex;
	//gl_Position = ftransform();
	VertexEyeDir = MMatrix * gl_Vertex;
	gl_Position = MVPMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;
    //gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    Normal =( MMatrix * vec4(gl_Normal,0.0)).xyz;
	TexCoord0=gl_MultiTexCoord0.xy;
    return;
}
