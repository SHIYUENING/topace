uniform float AveLum;
uniform float imgW;
uniform float imgH;
uniform sampler2D _texColor1;
vec2 _c0007;
vec2 _c0009;
vec2 _c0011;
vec2 _c0013;
vec2 _c0015;
vec2 _c0017;
vec2 _c0019;

void main()
{

    float _dx;
    float _dy;
    vec4 _color;
    vec4 _cout;
    float _lum;
    vec4 _p;
    float _luml;

    _dx = 1.00000000E+000/imgW;
    _dy = 1.00000000E+000/imgH;
    _color = texture2D(_texColor1, gl_TexCoord[0].xy);
    _c0007 = gl_TexCoord[0].xy + vec2(_dx*3.00000000E+000, 0.00000000E+000);
    _color = _color + texture2D(_texColor1, _c0007);
    _c0009 = gl_TexCoord[0].xy + vec2(0.00000000E+000, _dy);
    _color = _color + texture2D(_texColor1, _c0009);
    _c0011 = gl_TexCoord[0].xy + vec2(_dx*3.00000000E+000, _dy);
    _color = _color + texture2D(_texColor1, _c0011);
    _c0013 = gl_TexCoord[0].xy + vec2(0.00000000E+000, _dy*2.00000000E+000);
    _color = _color + texture2D(_texColor1, _c0013);
    _c0015 = gl_TexCoord[0].xy + vec2(_dx*3.00000000E+000, _dy*2.00000000E+000);
    _color = _color + texture2D(_texColor1, _c0015);
    _c0017 = gl_TexCoord[0].xy + vec2(0.00000000E+000, _dy*3.00000000E+000);
    _color = _color + texture2D(_texColor1, _c0017);
    _c0019 = gl_TexCoord[0].xy + vec2(_dx*3.00000000E+000, _dy*3.00000000E+000);
    _color = _color + texture2D(_texColor1, _c0019);
    _color = _color*1.25000000E-001;
    _cout = vec4( 0.00000000E+000, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000);
    _lum = _color.x*3.00000012E-001 + _color.y*5.89999974E-001 + _color.z*1.09999999E-001;
    _p = _color*(_lum/AveLum);
    _p.x = _p.x/(_p.x + 1.00000000E+000);
    _p.y = _p.y/(_p.y + 1.00000000E+000);
    _p.z = _p.z/(_p.z + 1.00000000E+000);
    _luml = (_p.x + _p.y + _p.z)/3.00000000E+000;
    if (_luml > 7.50000000E-001) { // if begin
        _cout = _p;
    }
    gl_FragColor = _cout;
    return;
} 
