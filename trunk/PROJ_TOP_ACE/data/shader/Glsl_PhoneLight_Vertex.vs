varying  vec4 VertexEyeDir; 
varying  vec3 Normal; 
void main()
{
	int ix=0;
	VertexEyeDir = gl_ModelViewMatrix * gl_Vertex;
	gl_Position = ftransform();
    gl_FrontColor = gl_Color;
    gl_TexCoord[0] = gl_TextureMatrix[ix] * gl_MultiTexCoord0;
    Normal = gl_NormalMatrix * gl_Normal;
    return;
}
