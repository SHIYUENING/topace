#version 150

out  vec4 VertexEyeDir; 
out  vec3 Normal; 
void main()
{
	//VertexEyeDir = gl_ModelViewMatrix * gl_Vertex;
	//gl_Position = ftransform();
	VertexEyeDir = MMatrix * gl_Vertex;
	gl_Position = MVPMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    Normal =( MMatrix * vec4(gl_Normal,0.0)).xyz;
    return;
}
