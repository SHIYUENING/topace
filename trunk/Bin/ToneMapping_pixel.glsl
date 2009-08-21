// glslf output by Cg compiler
// cgc version 2.2.0006, build date Mar 31 2009
// command line args: -profile glslf -oglsl
// source file: ToneMapping_pixel.cg
//vendor NVIDIA Corporation
//version 2.2.0.6
//profile glslf
//program main
//semantic main.texSrc
//var sampler2D texSrc :  : _texSrc1 : 1 : 1
//var float2 oPosition : $vin.TEXCOORD0 : TEXCOORD0 : 0 : 1
//var float4 main.colorout : $vout.COLOR : COLOR : -1 : 1

struct pixel {
    vec4 _colorout;
};

pixel _ret_0;
uniform sampler2D _texSrc1;

 // main procedure, the original name was main
void main()
{

    vec4 _color;

    _color.x = 1.00000000E+000;
    _color.y = 1.00000000E+000;
    _color.z = 1.00000000E+000;
    _color.w = texture2D(_texSrc1, gl_TexCoord[0].xy).x*1.20000005E+000;
    _ret_0._colorout = _color;
    gl_FragColor = _color;
    return;
} // main end
