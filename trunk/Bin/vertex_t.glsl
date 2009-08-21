// glslv output by Cg compiler
// cgc version 2.2.0006, build date Mar 31 2009
// command line args: -profile glslv -oglsl
// source file: vertex_t.cg
//vendor NVIDIA Corporation
//version 2.2.0.6
//profile glslv
//program main
//semantic main.ShadowMapmvmatrix
//semantic main.ShadowMapprojmatrix
//semantic main.ShadowMapMVPmatrix
//semantic main.MissleLightDirection
//semantic main.paraLightColor
//semantic modelViewProj : state.matrix.mvp
//var float4x4 ShadowMapmvmatrix :  : , 4 : 1 : 0
//var float4x4 ShadowMapprojmatrix :  : , 4 : 2 : 0
//var float4x4 ShadowMapMVPmatrix :  : _ShadowMapMVPmatrix1[0], 4 : 3 : 1
//var float4 MissleLightDirection :  : _MissleLightDirection1 : 4 : 1
//var float3 paraLightColor :  : _paraLightColor1 : 5 : 1
//var float4x4 modelViewProj : state.matrix.mvp : _modelViewProj[0], 4 : -1 : 1
//var float4 IN.position : $vin.POSITION : POSITION : 0 : 1
//var float3 IN.normal : $vin.NORMAL : NORMAL : 0 : 1
//var float4 IN.color0 : $vin.COLOR0 : COLOR0 : 0 : 1
//var float2 IN.texcoord0 : $vin.TEXCOORD0 : TEXCOORD0 : 0 : 1
//var float4 main.position : $vout.POSITION : POSITION : -1 : 1
//var float3 main.oNormal : $vout.TEXCOORD1 : TEXCOORD1 : -1 : 1
//var float4 main.color0 : $vout.COLOR0 : COLOR0 : -1 : 1
//var float2 main.texcoord0 : $vout.TEXCOORD0 : TEXCOORD0 : -1 : 1
//var float3 main.objectPos : $vout.TEXCOORD2 : TEXCOORD2 : -1 : 1
//var float2 main.texcoord3 : $vout.TEXCOORD3 : TEXCOORD3 : -1 : 1
//var float4 main.objectPos2 : $vout.TEXCOORD4 : TEXCOORD4 : -1 : 1
//var float3 main.Light2color : $vout.TEXCOORD5 : TEXCOORD5 : -1 : 1

struct vertex {
    vec4 _position1;
    vec3 _normal;
    vec4 _color01;
    vec2 _texcoord01;
};

struct fragment {
    vec4 _position;
    vec3 _oNormal;
    vec4 _color0;
    vec2 _texcoord0;
    vec3 _objectPos;
    vec2 _texcoord3;
    vec4 _objectPos2;
    vec3 _Light2color;
};

fragment _ret_0;
uniform vec4 _ShadowMapMVPmatrix1[4];
uniform vec4 _MissleLightDirection1;
uniform vec3 _paraLightColor1;
vec4 _r0008;
vec4 _r0010;
vec3 _TMP11;
float _x0016;
vec3 _TMP17;
vec3 _v0018;
float _x0022;
uniform vec4 _modelViewProj[4];

 // main procedure, the original name was main
void main()
{

    fragment _OUT;
    float _DotNaL;
    float _diffuseLight;
    vec3 _diffuse;

    _r0008 = gl_Vertex.x*_ShadowMapMVPmatrix1[0];
    _r0008 = _r0008 + gl_Vertex.y*_ShadowMapMVPmatrix1[1];
    _r0008 = _r0008 + gl_Vertex.z*_ShadowMapMVPmatrix1[2];
    _r0008 = _r0008 + gl_Vertex.w*_ShadowMapMVPmatrix1[3];
    _OUT._texcoord3.x = _r0008.x/(_r0008.w*2.00000000E+000) + 5.00000000E-001;
    _OUT._texcoord3.y = _r0008.y/(_r0008.w*2.00000000E+000) + 5.00000000E-001;
    _r0010 = gl_Vertex.x*_modelViewProj[0];
    _r0010 = _r0010 + gl_Vertex.y*_modelViewProj[1];
    _r0010 = _r0010 + gl_Vertex.z*_modelViewProj[2];
    _r0010 = _r0010 + gl_Vertex.w*_modelViewProj[3];
    _x0016 = dot(gl_Normal, gl_Normal);
    _TMP11 = inversesqrt(_x0016)*gl_Normal;
    _v0018 = _MissleLightDirection1.xyz - gl_Vertex.xyz;
    _x0022 = dot(_v0018, _v0018);
    _TMP17 = inversesqrt(_x0022)*_v0018;
    _DotNaL = dot(_TMP11, _TMP17);
    _diffuseLight = max(_DotNaL, 0.00000000E+000);
    _diffuse = _paraLightColor1*_diffuseLight*1.00000000E+001;
    _ret_0._position = _r0010;
    _ret_0._oNormal = gl_Normal;
    _ret_0._color0 = gl_Color;
    _ret_0._texcoord0 = gl_MultiTexCoord0.xy;
    _ret_0._objectPos = gl_Vertex.xyz;
    _ret_0._texcoord3 = _OUT._texcoord3;
    _ret_0._objectPos2 = _r0008;
    _ret_0._Light2color = _diffuse;
    gl_FrontColor = gl_Color;
    gl_TexCoord[1].xyz = gl_Normal;
    gl_TexCoord[3].xy = _OUT._texcoord3;
    gl_TexCoord[4] = _r0008;
    gl_Position = _r0010;
    gl_TexCoord[2].xyz = gl_Vertex.xyz;
    gl_TexCoord[5].xyz = _diffuse;
    gl_TexCoord[0].xy = gl_MultiTexCoord0.xy;
    return;
} // main end
