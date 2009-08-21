// glslf output by Cg compiler
// cgc version 2.2.0006, build date Mar 31 2009
// command line args: -profile glslf -oglsl
// source file: BloomW_pixel.cg
//vendor NVIDIA Corporation
//version 2.2.0.6
//profile glslf
//program main
//semantic main.imgW
//semantic main.texSrc
//var float imgW :  : _imgW1 : 1 : 1
//var sampler2D texSrc :  : _texSrc1 : 2 : 1
//var float2 oPosition : $vin.TEXCOORD0 : TEXCOORD0 : 0 : 1
//var float4 main.colorout : $vout.COLOR : COLOR : -1 : 1

struct pixel {
    vec4 _colorout;
};

pixel _ret_0;
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

 // main procedure, the original name was main
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
    _ret_0._colorout = _color;
    gl_FragColor = _color;
    return;
} // main end
