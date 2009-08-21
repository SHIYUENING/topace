uniform float _imgW1;
uniform sampler2D _texSrc1;
vec2 _c0003;
vec2 _c0005;
vec2 _c0007;
vec2 _c0009;
vec2 _c0011;
vec2 _c0015;
vec2 _c0017;
vec2 _c0019;
vec2 _c0021;
vec2 _c0023;

void main()
{

    float _d;
    vec2 _Tpos;
    vec4 _color;

    _d = 4.00000000E+000/_imgW1;
    _Tpos.x = -_d;
    _Tpos.y = 0.00000000E+000;
    _c0003 = gl_TexCoord[0].xy + _Tpos*5.00000000E+000;
    _color = texture2D(_texSrc1, _c0003)*1.00000001E-001;
    _c0005 = gl_TexCoord[0].xy + _Tpos*4.00000000E+000;
    _color = _color + texture2D(_texSrc1, _c0005)*2.19999999E-001;
    _c0007 = gl_TexCoord[0].xy + _Tpos*3.00000000E+000;
    _color = _color + texture2D(_texSrc1, _c0007)*3.58000010E-001;
    _c0009 = gl_TexCoord[0].xy + _Tpos*2.00000000E+000;
    _color = _color + texture2D(_texSrc1, _c0009)*5.23000002E-001;
    _c0011 = gl_TexCoord[0].xy + _Tpos;
    _color = _color + texture2D(_texSrc1, _c0011)*8.42999995E-001;
    _color = _color + texture2D(_texSrc1, gl_TexCoord[0].xy);
    _Tpos.x = _d;
    _c0015 = gl_TexCoord[0].xy + _Tpos;
    _color = _color + texture2D(_texSrc1, _c0015)*8.42999995E-001;
    _c0017 = gl_TexCoord[0].xy + _Tpos*2.00000000E+000;
    _color = _color + texture2D(_texSrc1, _c0017)*5.23000002E-001;
    _c0019 = gl_TexCoord[0].xy + _Tpos*3.00000000E+000;
    _color = _color + texture2D(_texSrc1, _c0019)*3.58000010E-001;
    _c0021 = gl_TexCoord[0].xy + _Tpos*4.00000000E+000;
    _color = _color + texture2D(_texSrc1, _c0021)*2.19999999E-001;
    _c0023 = gl_TexCoord[0].xy + _Tpos*5.00000000E+000;
    _color = _color + texture2D(_texSrc1, _c0023)*1.00000001E-001;
    _color = _color/5.00000000E+000;
    _color.w = 1.00000000E+000;
    gl_FragColor = _color;
    return;
}
