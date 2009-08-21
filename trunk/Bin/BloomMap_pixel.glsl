// glslf output by Cg compiler
// cgc version 2.2.0006, build date Mar 31 2009
// command line args: -profile glslf -oglsl
// source file: BloomMap_pixel.cg
//vendor NVIDIA Corporation
//version 2.2.0.6
//profile glslf
//program main
//semantic main.AveLum
//semantic main.imgW
//semantic main.imgH
//semantic main.texColor
//var float AveLum :  : _AveLum1 : 1 : 1
//var float imgW :  : _imgW1 : 2 : 1
//var float imgH :  : _imgH1 : 3 : 1
//var sampler2D texColor :  : _texColor1 : 4 : 1
//var float2 oPosition : $vin.TEXCOORD0 : TEXCOORD0 : 0 : 1
//var float4 main.colorout : $vout.COLOR : COLOR : -1 : 1

struct pixel {
    vec4 _colorout;
};

pixel _ret_0;
uniform float _AveLum1;
uniform float _imgW1;
uniform float _imgH1;
uniform sampler2D _texColor1;
vec2 _c0007;
vec2 _c0009;
vec2 _c0011;
vec2 _c0013;
vec2 _c0015;
vec2 _c0017;
vec2 _c0019;

 // main procedure, the original name was main
void main()
{

    float _dx;
    float _dy;
    vec4 _color;
    vec4 _cout;
    float _lum;
    vec4 _p;
    float _luml;

    _dx = 1.00000000E+000/_imgW1;
    _dy = 1.00000000E+000/_imgH1;
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
    _p = _color*(_lum/_AveLum1);
    _p.x = _p.x/(_p.x + 1.00000000E+000);
    _p.y = _p.y/(_p.y + 1.00000000E+000);
    _p.z = _p.z/(_p.z + 1.00000000E+000);
    _luml = (_p.x + _p.y + _p.z)/3.00000000E+000;
    if (_luml > 7.50000000E-001) { // if begin
        _cout = _p;
    } // end if
    _ret_0._colorout = _cout;
    gl_FragColor = _cout;
    return;
} // main end
