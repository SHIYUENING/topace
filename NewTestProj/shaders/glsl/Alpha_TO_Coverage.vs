
void main()
{

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;
    gl_TexCoord[0].xy = gl_MultiTexCoord0.xy;
    return;
}