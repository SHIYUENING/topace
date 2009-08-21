vec4 _r0003;
void main()
{
    _r0003 = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[1] = _r0003;
    gl_Position = _r0003;
    return;
}
