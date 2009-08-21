// glslf output by Cg compiler
// cgc version 2.2.0006, build date Mar 31 2009
// command line args: -profile glslf -oglsl
// source file: Sea_pixel.cg
//vendor NVIDIA Corporation
//version 2.2.0.6
//profile glslf
//program main
//semantic main.globalAmbient
//semantic main.paraLightColor
//semantic main.paraLightDirection
//semantic main.eyePosition
//semantic main.FogColor
//semantic main.testTexture
//semantic main.AmbientReflectiveTexturSea
//var float3 globalAmbient :  : _globalAmbient1 : 1 : 1
//var float3 paraLightColor :  : _paraLightColor1 : 2 : 1
//var float3 paraLightDirection :  : _paraLightDirection1 : 3 : 1
//var float3 eyePosition :  : _eyePosition1 : 4 : 1
//var float3 FogColor :  : _FogColor1 : 5 : 1
//var sampler2D testTexture :  : _testTexture1 : 6 : 1
//var samplerCUBE AmbientReflectiveTexturSea :  : _AmbientReflectiveTexturSea1 : 7 : 1
//var float4 IN.color0 : $vin.COLOR0 :  : 0 : 0
//var float4 IN.objectPos2 : $vin.TEXCOORD0 : TEXCOORD0 : 0 : 1
//var float2 IN.TexCoord1 : $vin.TEXCOORD1 : TEXCOORD1 : 0 : 1
//var float2 IN.TexCoord2 : $vin.TEXCOORD2 : TEXCOORD2 : 0 : 1
//var float2 IN.TexCoord3 : $vin.TEXCOORD3 : TEXCOORD3 : 0 : 1
//var float2 IN.TexCoord4 : $vin.TEXCOORD4 : TEXCOORD4 : 0 : 1
//var float4 IN.objectPos : $vin.TEXCOORD5 : TEXCOORD5 : 0 : 1
//var float4 main.color : $vout.COLOR : COLOR : -1 : 1

struct fragment {
    vec4 _color0;
    vec4 _objectPos2;
    vec2 _TexCoord1;
    vec2 _TexCoord2;
    vec2 _TexCoord3;
    vec2 _TexCoord4;
    vec4 _objectPos;
};

struct pixel {
    vec4 _color;
};

pixel _ret_0;
uniform vec3 _globalAmbient1;
uniform vec3 _paraLightColor1;
uniform vec3 _paraLightDirection1;
uniform vec3 _eyePosition1;
uniform vec3 _FogColor1;
uniform sampler2D _testTexture1;
uniform samplerCube _AmbientReflectiveTexturSea1;
vec3 _TMP16;
vec3 _v0017;
float _x0021;
vec3 _TMP22;
float _a0031;
vec3 _TMP32;
float _x0037;
float _a0041;
vec3 _TMP42;
vec3 _v0043;
float _x0047;
vec3 _TMP48;
float _x0053;
float _a0061;

 // main procedure, the original name was main
void main()
{

    vec3 _vBumpTexA;
    vec3 _vBumpTexB;
    vec3 _vBumpTexC;
    vec3 _vBumpTexD;
    vec3 _N;
    vec3 _vReflBump;
    vec3 _V;
    vec4 _reflection;
    float _NdotL;
    float _Fresnel;
    float _light;
    float _DotMaH;
    float _MaxDotMaH0;
    float _specularLight;
    pixel _OUT;
    float _fogb;

    _vBumpTexA = texture2D(_testTexture1, gl_TexCoord[1].xy).xyz;
    _vBumpTexB = texture2D(_testTexture1, gl_TexCoord[2].xy).xyz;
    _vBumpTexC = texture2D(_testTexture1, gl_TexCoord[3].xy).xyz;
    _vBumpTexD = texture2D(_testTexture1, gl_TexCoord[4].xy).xyz;
    _N = (_vBumpTexA.xyz + _vBumpTexB.xyz + _vBumpTexC.xyz + _vBumpTexD.xyz)/4.00000000E+000;
    _vReflBump = vec3((_N.x - 5.00000000E-001)*2.00000000E+000, (_N.z - 5.00000000E-001)*2.00000000E+000, (_N.y - 5.00000000E-001)*2.00000000E+000);
    _v0017 = gl_TexCoord[0].xyz*1.00000000E+003 - _eyePosition1;
    _x0021 = dot(_v0017, _v0017);
    _TMP16 = inversesqrt(_x0021)*_v0017;
    _V = -_TMP16;
    _TMP22 = _V - (2.00000000E+000*_vReflBump)*dot(_vReflBump, _V);
    _reflection = textureCube(_AmbientReflectiveTexturSea1, _TMP22);
    _a0031 = dot(_V, _vReflBump);
    _NdotL = max(_a0031, 0.00000000E+000);
    _Fresnel = (1.00000000E+000 - _NdotL)*5.00000000E-001;
    _x0037 = dot(_paraLightDirection1, _paraLightDirection1);
    _TMP32 = inversesqrt(_x0037)*_paraLightDirection1;
    _a0041 = dot(_TMP32, _vReflBump);
    _light = max(_a0041, 0.00000000E+000);
    _v0043 = _TMP32 + _V;
    _x0047 = dot(_v0043, _v0043);
    _TMP42 = inversesqrt(_x0047)*_v0043;
    _x0053 = dot(_vReflBump, _vReflBump);
    _TMP48 = inversesqrt(_x0053)*_vReflBump;
    _DotMaH = dot(_TMP48, _TMP42);
    _MaxDotMaH0 = max(_DotMaH, 0.00000000E+000);
    _specularLight = pow(_MaxDotMaH0, 1.00000000E+003);
    _OUT._color.xyz = (_Fresnel*_reflection.xyz + (1.00000000E+000 - _Fresnel)*vec3( 1.00000001E-001, 5.00000000E-001, 1.00000000E+000))*(_light*_paraLightColor1 + _globalAmbient1) + _specularLight*_paraLightColor1;
    _a0061 = (1.00000000E+005 - gl_TexCoord[5].z)/7.00000000E+004;
    _fogb = min(_a0061, 1.00000000E+000);
    _OUT._color.xyz = _OUT._color.xyz*_fogb + (1.00000000E+000 - _fogb)*_FogColor1;
    _OUT._color.w = 1.00000000E+000;
    _ret_0._color = _OUT._color;
    gl_FragColor = _OUT._color;
    return;
} // main end
