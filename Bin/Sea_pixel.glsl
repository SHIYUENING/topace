uniform vec3 globalAmbient;
uniform vec3 paraLightColor;
uniform vec3 paraLightDirection;
uniform vec3 eyePosition;
uniform vec3 FogColor;
uniform sampler2D testTexture;
uniform samplerCube AmbientReflectiveTexturSea;
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
    vec4 OUTcolor;
    float _NdotL;
    float _Fresnel;
    float _light;
    float _DotMaH;
    float _MaxDotMaH0;
    float _specularLight;
    float _fogb;

    _vBumpTexA = texture2D(testTexture, gl_TexCoord[1].xy).xyz;
    _vBumpTexB = texture2D(testTexture, gl_TexCoord[2].xy).xyz;
    _vBumpTexC = texture2D(testTexture, gl_TexCoord[3].xy).xyz;
    _vBumpTexD = texture2D(testTexture, gl_TexCoord[4].xy).xyz;
    _N = (_vBumpTexA.xyz + _vBumpTexB.xyz + _vBumpTexC.xyz + _vBumpTexD.xyz)/4.0;
    _vReflBump = vec3((_N.x - 0.5)*2.0, (_N.z - 0.5)*2.0, (_N.y - 0.5)*2.0);
    _V =- normalize(gl_TexCoord[0].xyz*1000.0 - eyePosition);
    _TMP22 = _V - (2.0*_vReflBump)*dot(_vReflBump, _V);
    _reflection = textureCube(AmbientReflectiveTexturSea, _TMP22);
    _a0031 = dot(_V, _vReflBump);
    _NdotL = max(_a0031, 0.0);
    _Fresnel = (1.0 - _NdotL)*0.5;
    _TMP32 = normalize(paraLightDirection);
    _a0041 = dot(_TMP32, _vReflBump);
    _light = max(_a0041, 0.0);
    _v0043 = _TMP32 + _V;
    _x0047 = dot(_v0043, _v0043);
    _TMP42 = inversesqrt(_x0047)*_v0043;
    _x0053 = dot(_vReflBump, _vReflBump);
    _TMP48 = inversesqrt(_x0053)*_vReflBump;
    _DotMaH = dot(_TMP48, _TMP42);
    _MaxDotMaH0 = max(_DotMaH, 0.0);
    _specularLight = pow(_MaxDotMaH0, 1.00000000E+003);
    OUTcolor.xyz = (_Fresnel*_reflection.xyz + (1.0 - _Fresnel)*vec3( 1.00000001E-001, 5.00000000E-001, 1.0))*(_light*paraLightColor + globalAmbient) + _specularLight*paraLightColor;
    _a0061 = (1.00000000E+005 - gl_TexCoord[5].z)/7.00000000E+004;
    _fogb = min(_a0061, 1.0);
    OUTcolor.xyz = OUTcolor.xyz*_fogb + (1.0 - _fogb)*FogColor;
    OUTcolor.w = 1.0;
   // OUTcolor.xyz=_reflection;
    gl_FragColor = OUTcolor;
    return;
} // main end
