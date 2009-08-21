// glslf output by Cg compiler
// cgc version 2.2.0006, build date Mar 31 2009
// command line args: -profile glslf -oglsl
// source file: pixel_NONormalMap.cg
//vendor NVIDIA Corporation
//version 2.2.0.6
//profile glslf
//program main
//semantic main.globalAmbient
//semantic main.paraLightColor
//semantic main.paraLightDirection
//semantic main.eyePosition
//semantic main.Worldmatrix
//semantic main.testTexture
//semantic main.ShadowMapTexture
//semantic main.AmbientReflectiveTexture
//semantic main.NormalMapTexture
//semantic main.SpecularMapTexture
//var float3 globalAmbient :  : _globalAmbient1 : 1 : 1
//var float3 paraLightColor :  : _paraLightColor1 : 2 : 1
//var float3 paraLightDirection :  : _paraLightDirection1 : 3 : 1
//var float3 eyePosition :  : _eyePosition1 : 4 : 1
//var float4x4 Worldmatrix :  : , 4 : 5 : 0
//var sampler2D testTexture :  : _testTexture1 : 6 : 1
//var sampler2D ShadowMapTexture :  :  : 7 : 0
//var samplerCUBE AmbientReflectiveTexture :  :  : 8 : 0
//var sampler2D NormalMapTexture :  :  : 9 : 0
//var sampler2D SpecularMapTexture :  :  : 10 : 0
//var float3 IN.color0 : $vin.COLOR0 :  : 0 : 0
//var float2 IN.texcoord0 : $vin.TEXCOORD0 : TEXCOORD0 : 0 : 1
//var float3 IN.normal : $vin.TEXCOORD1 : TEXCOORD1 : 0 : 1
//var float4 IN.objectPos : $vin.TEXCOORD2 :  : 0 : 0
//var float2 IN.texcoord3 : $vin.TEXCOORD3 :  : 0 : 0
//var float4 IN.objectPos2 : $vin.TEXCOORD4 :  : 0 : 0
//var float3 IN.Light2color : $vin.TEXCOORD5 : TEXCOORD5 : 0 : 1
//var float4 main.color : $vout.COLOR : COLOR : -1 : 1

struct fragment {
    vec3 _color0;
    vec2 _texcoord0;
    vec3 _normal;
    vec4 _objectPos;
    vec2 _texcoord3;
    vec4 _objectPos2;
    vec3 _Light2color;
};

struct pixel {
    vec4 _color;
};

pixel _ret_0;
uniform vec3 _globalAmbient1;
uniform vec3 _paraLightColor1;
uniform vec3 _paraLightDirection1;
uniform vec3 _eyePosition1;
uniform sampler2D _testTexture1;
vec3 _TMP13;
float _x0018;
vec3 _TMP19;
float _x0024;
vec3 _TMP29;
float _x0034;
vec3 _TMP35;
vec3 _v0036;
float _x0040;

 // main procedure, the original name was main
void main()
{

    vec4 _MainColor;
    float _DotNaL;
    float _diffuseLight;
    vec3 _diffuse;
    float _DotNaH;
    float _MaxNaH0;
    float _specularLight;
    vec4 _Ocolor;
    pixel _OUT;

    _MainColor = texture2D(_testTexture1, gl_TexCoord[0].xy);
    _x0018 = dot(gl_TexCoord[1].xyz, gl_TexCoord[1].xyz);
    _TMP13 = inversesqrt(_x0018)*gl_TexCoord[1].xyz;
    _x0024 = dot(_paraLightDirection1, _paraLightDirection1);
    _TMP19 = inversesqrt(_x0024)*_paraLightDirection1;
    _DotNaL = dot(_TMP13, _TMP19);
    _diffuseLight = max(_DotNaL, 0.00000000E+000);
    _diffuse = _paraLightColor1*_diffuseLight;
    _x0034 = dot(_eyePosition1, _eyePosition1);
    _TMP29 = inversesqrt(_x0034)*_eyePosition1;
    _v0036 = _TMP19 + _TMP29;
    _x0040 = dot(_v0036, _v0036);
    _TMP35 = inversesqrt(_x0040)*_v0036;
    _DotNaH = dot(_TMP13, _TMP35);
    _MaxNaH0 = max(_DotNaH, 0.00000000E+000);
    _specularLight = pow(_MaxNaH0, 5.00000000E+001);
    if (_diffuseLight <= 0.00000000E+000) { // if begin
        _specularLight = 0.00000000E+000;
    } // end if
    _Ocolor.xyz = (_globalAmbient1 + gl_TexCoord[5].xyz + _diffuse) + _specularLight*8.00000000E+000;
    _Ocolor.w = 1.00000000E+000;
    _OUT._color = _MainColor*_Ocolor;
    _OUT._color.w = 5.00000000E-001;
    _ret_0._color = _OUT._color;
    gl_FragColor = _OUT._color;
    return;
} // main end
