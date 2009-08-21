// glslf output by Cg compiler
// cgc version 2.2.0006, build date Mar 31 2009
// command line args: -profile glslf -oglsl
// source file: pixel_NOBloom_HighShadow.cg
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
//var float4x4 Worldmatrix :  : _Worldmatrix1[0], 4 : 5 : 1
//var sampler2D testTexture :  : _testTexture1 : 6 : 1
//var sampler2D ShadowMapTexture :  : _ShadowMapTexture1 : 7 : 1
//var samplerCUBE AmbientReflectiveTexture :  : _AmbientReflectiveTexture1 : 8 : 1
//var sampler2D NormalMapTexture :  : _NormalMapTexture1 : 9 : 1
//var sampler2D SpecularMapTexture :  : _SpecularMapTexture1 : 10 : 1
//var float4 IN.color0 : $vin.COLOR0 : COLOR0 : 0 : 1
//var float2 IN.texcoord0 : $vin.TEXCOORD0 : TEXCOORD0 : 0 : 1
//var float3 IN.normal : $vin.TEXCOORD1 : TEXCOORD1 : 0 : 1
//var float4 IN.objectPos : $vin.TEXCOORD2 : TEXCOORD2 : 0 : 1
//var float2 IN.texcoord3 : $vin.TEXCOORD3 :  : 0 : 0
//var float4 IN.objectPos2 : $vin.TEXCOORD4 : TEXCOORD4 : 0 : 1
//var float3 IN.Light2color : $vin.TEXCOORD5 : TEXCOORD5 : 0 : 1
//var float4 main.color : $vout.COLOR : COLOR : -1 : 1

struct fragment {
    vec4 _color0;
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

fragment _TMP0;
pixel _ret_0;
uniform vec3 _globalAmbient1;
uniform vec3 _paraLightColor1;
uniform vec3 _paraLightDirection1;
uniform vec3 _eyePosition1;
uniform vec4 _Worldmatrix1[4];
uniform sampler2D _testTexture1;
uniform sampler2DShadow _ShadowMapTexture1;
uniform samplerCube _AmbientReflectiveTexture1;
uniform sampler2D _NormalMapTexture1;
uniform sampler2D _SpecularMapTexture1;
vec3 _TMP13;
float _x0018;
vec3 _TMP19;
float _x0024;
vec3 _TMP27;
vec3 _v0028;
float _x0032;
vec3 _r0036;
vec3 _TMP43;
float _x0048;
vec3 _TMP53;
float _x0058;
vec3 _TMP59;
vec3 _v0060;
float _x0064;
vec4 _c0076;
vec4 _c0078;
vec4 _c0080;
vec4 _c0082;
vec4 _c0084;
vec4 _c0086;
vec4 _c0088;
vec4 _c0090;
vec4 _c0092;
vec4 _c0094;
vec4 _c0096;
vec4 _c0098;
vec4 _c0100;
vec4 _c0102;
vec4 _c0104;
vec4 _c0106;
vec4 _c0108;
vec4 _c0110;
vec4 _c0112;
vec4 _c0114;
vec3 _TMP115;
vec3 _i0116;
vec4 _r0120;

 // main procedure, the original name was main
void main()
{

    vec4 _MainColor;
    vec3 _NN;
    vec3 _NN2;
    float _DotNaL;
    float _diffuseLight;
    vec3 _diffuse;
    float _DotNaH;
    float _MaxNaH0;
    float _specularLight;
    vec4 _SpecularMapcolor;
    vec4 _Ocolor;
    pixel _OUT;
    float _colorposZ;

    _TMP0._objectPos2 = gl_TexCoord[4];
    _MainColor = texture2D(_testTexture1, gl_TexCoord[0].xy);
    _x0018 = dot(gl_Color.xyz, gl_Color.xyz);
    _TMP13 = inversesqrt(_x0018)*gl_Color.xyz;
    _x0024 = dot(gl_TexCoord[1].xyz, gl_TexCoord[1].xyz);
    _TMP19 = inversesqrt(_x0024)*gl_TexCoord[1].xyz;
    _v0028 = _TMP13.yzx*_TMP19.zxy - _TMP13.zxy*_TMP19.yzx;
    _x0032 = dot(_v0028, _v0028);
    _TMP27 = inversesqrt(_x0032)*_v0028;
    _NN = texture2D(_NormalMapTexture1, gl_TexCoord[0].xy).xyz;
    _NN2.x = (_NN.x - 5.00000000E-001)*2.00000000E+000;
    _NN2.y = (_NN.y - 5.00000000E-001)*2.00000000E+000;
    _NN2.z = (_NN.z - 5.00000000E-001)*2.00000000E+000;
    _r0036.x = dot(_TMP13, _NN2);
    _r0036.y = dot(_TMP27, _NN2);
    _r0036.z = dot(_TMP19, _NN2);
    _x0048 = dot(_paraLightDirection1, _paraLightDirection1);
    _TMP43 = inversesqrt(_x0048)*_paraLightDirection1;
    _DotNaL = dot(_r0036, _TMP43);
    _diffuseLight = max(_DotNaL, 0.00000000E+000);
    _diffuse = _paraLightColor1*_diffuseLight;
    _x0058 = dot(_eyePosition1, _eyePosition1);
    _TMP53 = inversesqrt(_x0058)*_eyePosition1;
    _v0060 = _TMP43 + _TMP53;
    _x0064 = dot(_v0060, _v0060);
    _TMP59 = inversesqrt(_x0064)*_v0060;
    _DotNaH = dot(_r0036, _TMP59);
    _MaxNaH0 = max(_DotNaH, 0.00000000E+000);
    _specularLight = pow(_MaxNaH0, 5.00000000E+001);
    _SpecularMapcolor = texture2D(_SpecularMapTexture1, gl_TexCoord[0].xy);
    if (_diffuseLight <= 0.00000000E+000) { // if begin
        _specularLight = 0.00000000E+000;
    } // end if
    _Ocolor.w = 1.00000000E+000;
    _TMP0._objectPos2.z = gl_TexCoord[4].z - 4.00000006E-001;
    _colorposZ = shadow2DProj(_ShadowMapTexture1, _TMP0._objectPos2).x;
    _c0076 = _TMP0._objectPos2 + vec4( 1.50000006E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0076).x;
    _c0078 = _TMP0._objectPos2 - vec4( 1.50000006E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0078).x;
    _c0080 = _TMP0._objectPos2 + vec4( 0.00000000E+000, 1.50000006E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0080).x;
    _c0082 = _TMP0._objectPos2 - vec4( 0.00000000E+000, 1.50000006E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0082).x;
    _c0084 = _TMP0._objectPos2 + vec4( 1.50000006E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000) + vec4( 0.00000000E+000, 1.50000006E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0084).x;
    _c0086 = (_TMP0._objectPos2 - vec4( 1.50000006E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000)) + vec4( 0.00000000E+000, 1.50000006E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0086).x;
    _c0088 = (_TMP0._objectPos2 + vec4( 1.50000006E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000)) - vec4( 0.00000000E+000, 1.50000006E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0088).x;
    _c0090 = (_TMP0._objectPos2 - vec4( 1.50000006E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000)) - vec4( 0.00000000E+000, 1.50000006E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0090).x;
    _c0092 = _TMP0._objectPos2 + vec4( 3.00000012E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0092).x;
    _c0094 = _TMP0._objectPos2 - vec4( 3.00000012E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0094).x;
    _c0096 = _TMP0._objectPos2 + vec4( 0.00000000E+000, 3.00000012E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0096).x;
    _c0098 = _TMP0._objectPos2 - vec4( 0.00000000E+000, 3.00000012E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0098).x;
    _c0100 = _TMP0._objectPos2 + vec4( 3.00000012E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000) + vec4( 0.00000000E+000, 3.00000012E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0100).x;
    _c0102 = (_TMP0._objectPos2 - vec4( 3.00000012E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000)) + vec4( 0.00000000E+000, 3.00000012E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0102).x;
    _c0104 = (_TMP0._objectPos2 + vec4( 3.00000012E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000)) - vec4( 0.00000000E+000, 3.00000012E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0104).x;
    _c0106 = (_TMP0._objectPos2 - vec4( 3.00000012E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000)) - vec4( 0.00000000E+000, 3.00000012E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0106).x;
    _c0108 = _TMP0._objectPos2 + vec4( 4.50000018E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0108).x;
    _c0110 = _TMP0._objectPos2 - vec4( 4.50000018E-001, 0.00000000E+000, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0110).x;
    _c0112 = _TMP0._objectPos2 + vec4( 0.00000000E+000, 4.50000018E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0112).x;
    _c0114 = _TMP0._objectPos2 - vec4( 0.00000000E+000, 4.50000018E-001, 0.00000000E+000, 0.00000000E+000);
    _colorposZ = _colorposZ + shadow2DProj(_ShadowMapTexture1, _c0114).x;
    _i0116 = _eyePosition1 - gl_TexCoord[2].xyz/gl_TexCoord[2].w;
    _TMP115 = _i0116 - (2.00000000E+000*_r0036)*dot(_r0036, _i0116);
    _r0120 = _TMP115.x*_Worldmatrix1[0];
    _r0120 = _r0120 + _TMP115.y*_Worldmatrix1[1];
    _r0120 = _r0120 + _TMP115.z*_Worldmatrix1[2];
    _Ocolor.xyz = _globalAmbient1 + gl_TexCoord[5].xyz + ((_diffuse + _specularLight*1.00000000E+001*_SpecularMapcolor.x)*_colorposZ)/2.10000000E+001;
    _OUT._color = _MainColor*_Ocolor*(textureCube(_AmbientReflectiveTexture1, _r0120.xyz) + 1.00000000E+000);
    _OUT._color.w = 5.00000000E-001;
    _ret_0._color = _OUT._color;
    gl_FragColor = _OUT._color;
    return;
} // main end
