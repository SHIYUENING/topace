uniform vec3 globalAmbient;
uniform vec3 paraLightColor;
uniform vec3 paraLightDirection;
uniform vec3 eyePosition;
uniform mat4 Worldmatrix;
uniform sampler2D testTexture;
uniform sampler2DShadow ShadowMapTexture;
uniform samplerCube AmbientReflectiveTexture;
uniform sampler2D NormalMapTexture;
uniform sampler2D SpecularMapTexture;
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
vec3 _TMP75;
vec3 _i0076;
vec4 _r0080;

void main()
{


    float DotNaL;
    float diffuseLight;
    vec3 diffuse;
    float DotNaH;
    float MaxNaH0;
    float specularLight;
    vec4 SpecularMapcolor;
    vec4 Ocolor;
    vec4 colorposZ;
    vec4 _OUT_color;
    float posz;

    vec4 MainColor	=	texture2D(testTexture, gl_TexCoord[0].xy);
    vec3 Tangent	=	normalize(gl_Color.xyz);
    vec3 NormalIn	=	normalize(gl_TexCoord[1].xyz);
    vec3 Binormal	=	normalize(cross(Tangent,NormalIn));

    vec3 NN2 = texture2D(NormalMapTexture, gl_TexCoord[0].xy).xyz*2.0-vec3(1.0,1.0,1.0);
    mat3 TBN = mat3(Tangent,Binormal,NormalIn);
    vec3 Normal = TBN*NN2;
    _r0036=Normal;
    _TMP43 = normalize(paraLightDirection);
    DotNaL = dot(Normal, _TMP43);
    diffuseLight = max(DotNaL, 0.0);
    diffuse = paraLightColor*diffuseLight;
    _TMP53 = normalize(eyePosition);
    _TMP59 = normalize(_TMP43 + _TMP53);
    DotNaH = dot(_r0036, _TMP59);
    MaxNaH0 = max(DotNaH, 0.0);
    specularLight = pow(MaxNaH0, 50.0);
    SpecularMapcolor = texture2D(SpecularMapTexture, gl_TexCoord[0].xy);
    if (diffuseLight <= 0.0) { 
        specularLight = 0.0;
    }
    posz=shadow2DProj(ShadowMapTexture, gl_TexCoord[4]-vec4(0.0,0.0,0.4,0.0)).x;
    Ocolor.xyz = globalAmbient + gl_TexCoord[5].xyz + (diffuse + (specularLight*8.0)*SpecularMapcolor.xyz)*posz;
    Ocolor.w = 1.0;
    _i0076 = eyePosition - gl_TexCoord[2].xyz/gl_TexCoord[2].w;
    _TMP75 = _i0076 - (2.0*_r0036)*dot(_r0036, _i0076);
    _r0080 = Worldmatrix*vec4(_TMP75,0.0);
    _OUT_color = MainColor*Ocolor*(textureCube(AmbientReflectiveTexture, _r0080.xyz) + 1.0);
    _OUT_color.w = 0.5;
    gl_FragColor = _OUT_color;
    return;
} 
