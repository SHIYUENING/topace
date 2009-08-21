// glslv output by Cg compiler
// cgc version 2.2.0006, build date Mar 31 2009
// command line args: -profile glslv -oglsl
// source file: Sea_vertex.cg
//vendor NVIDIA Corporation
//version 2.2.0.6
//profile glslv
//program main
//semantic main.time
//semantic modelViewProj : state.matrix.mvp
//var float time :  : _time1 : 1 : 1
//var float4x4 modelViewProj : state.matrix.mvp : _modelViewProj[0], 4 : -1 : 1
//var float4 IN.position : $vin.POSITION : POSITION : 0 : 1
//var float3 IN.normal : $vin.NORMAL :  : 0 : 0
//var float4 IN.color0 : $vin.COLOR0 : COLOR0 : 0 : 1
//var float2 IN.texcoord0 : $vin.TEXCOORD0 : TEXCOORD0 : 0 : 1
//var float4 main.position : $vout.POSITION : POSITION : -1 : 1
//var float4 main.color0 : $vout.COLOR0 : COLOR0 : -1 : 1
//var float4 main.objectPos2 : $vout.TEXCOORD0 : TEXCOORD0 : -1 : 1
//var float2 main.TexCoord1 : $vout.TEXCOORD1 : TEXCOORD1 : -1 : 1
//var float2 main.TexCoord2 : $vout.TEXCOORD2 : TEXCOORD2 : -1 : 1
//var float2 main.TexCoord3 : $vout.TEXCOORD3 : TEXCOORD3 : -1 : 1
//var float2 main.TexCoord4 : $vout.TEXCOORD4 : TEXCOORD4 : -1 : 1
//var float4 main.objectPos : $vout.TEXCOORD5 : TEXCOORD5 : -1 : 1

struct vertex {
    vec4 _position1;
    vec3 _normal;
    vec4 _color01;
    vec2 _texcoord0;
};

struct fragment {
    vec4 _position;
    vec4 _color0;
    vec4 _objectPos2;
    vec2 _TexCoord1;
    vec2 _TexCoord2;
    vec2 _TexCoord3;
    vec2 _TexCoord4;
    vec4 _objectPos;
};

fragment _ret_0;
uniform float _time1;
vec4 _r0004;
uniform vec4 _modelViewProj[4];

 // main procedure, the original name was main
void main()
{

    vec2 _fTranslation;
    fragment _OUT;

    _fTranslation = vec2(_time1, 0.00000000E+000);
    _r0004 = gl_Vertex.x*_modelViewProj[0];
    _r0004 = _r0004 + gl_Vertex.y*_modelViewProj[1];
    _r0004 = _r0004 + gl_Vertex.z*_modelViewProj[2];
    _r0004 = _r0004 + gl_Vertex.w*_modelViewProj[3];
    _OUT._TexCoord1 = gl_MultiTexCoord0.xy + _fTranslation*2.00000000E+000;
    _OUT._TexCoord2 = gl_MultiTexCoord0.xy*2.00000000E+000 + _fTranslation*4.00000000E+000;
    _OUT._TexCoord3 = gl_MultiTexCoord0.xy*4.00000000E+000 + _fTranslation*2.00000000E+000;
    _OUT._TexCoord4 = gl_MultiTexCoord0.xy*8.00000000E+000 + _fTranslation;
    _ret_0._position = _r0004;
    _ret_0._color0 = gl_Color;
    _ret_0._objectPos2 = gl_Vertex;
    _ret_0._TexCoord1 = _OUT._TexCoord1;
    _ret_0._TexCoord2 = _OUT._TexCoord2;
    _ret_0._TexCoord3 = _OUT._TexCoord3;
    _ret_0._TexCoord4 = _OUT._TexCoord4;
    _ret_0._objectPos = _r0004;
    gl_FrontColor = gl_Color;
    gl_TexCoord[1].xy = _OUT._TexCoord1;
    gl_TexCoord[3].xy = _OUT._TexCoord3;
    gl_TexCoord[4].xy = _OUT._TexCoord4;
    gl_Position = _r0004;
    gl_TexCoord[2].xy = _OUT._TexCoord2;
    gl_TexCoord[5] = _r0004;
    gl_TexCoord[0] = gl_Vertex;
    return;
} // main end
