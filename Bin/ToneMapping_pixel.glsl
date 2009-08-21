uniform sampler2D _texSrc1;
void main()
{
    vec4 _color;
    _color.x = 1.0;
    _color.y = 1.0;
    _color.z = 1.0;
    _color.w = texture2D(_texSrc1, gl_TexCoord[0].xy).x*1.2;
    //_color.w = 0.5;
    gl_FragColor = _color;
    return;
}
