uniform mat4 ShadowMapMVPmatrix;
uniform vec4 MissleLightDirection;
uniform vec3 MissleLightColor;
vec4 _r0008;
vec4 _r0010;
vec3 _TMP11;
float _x0016;
vec3 _TMP17;
vec3 _v0018;
float _x0022;
void main()
{

    float _DotNaL;
    float _diffuseLight;
    vec3 _diffuse;
    vec2 _OUT_texcoord3;

    _r0008 = ShadowMapMVPmatrix * gl_Vertex;
    _OUT_texcoord3.x = _r0008.x/(_r0008.w*2.0) + 0.5;
    _OUT_texcoord3.y = _r0008.y/(_r0008.w*2.0) + 0.5;
    _r0010 = gl_ModelViewProjectionMatrix * gl_Vertex;
    _TMP11 = normalize(gl_Normal);
    _v0018 = MissleLightDirection.xyz - gl_Vertex.xyz;
    _TMP17 = normalize(_v0018);
    _DotNaL = dot(_TMP11, _TMP17);
    _diffuseLight = max(_DotNaL, 0.0);
    _diffuse = MissleLightColor*_diffuseLight*10.0;

	gl_Position = _r0010;
    gl_FrontColor = gl_Color;
    gl_TexCoord[0].xy = gl_MultiTexCoord0.xy;
    gl_TexCoord[1].xyz = gl_Normal;
    gl_TexCoord[2] = gl_Vertex;
    gl_TexCoord[3].xy = _OUT_texcoord3;
    gl_TexCoord[4] = _r0008;
    gl_TexCoord[5].xyz = _diffuse;
    
    return;
} // main end
