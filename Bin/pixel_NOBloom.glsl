uniform vec3 globalAmbient;
uniform vec3 paraLightColor;
uniform vec3 paraLightDirection;
uniform vec3 eyePosition;
uniform mat4 Worldmatrix;
uniform sampler2D testTexture;
uniform sampler2D ShadowMapTexture;
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
    _x0048 = dot(paraLightDirection, paraLightDirection);
    _TMP43 = inversesqrt(_x0048)*paraLightDirection;
    DotNaL = dot(_r0036, _TMP43);
    diffuseLight = max(DotNaL, 0.00000000E+000);
    diffuse = paraLightColor*diffuseLight;
    _x0058 = dot(eyePosition, eyePosition);
    _TMP53 = inversesqrt(_x0058)*eyePosition;
    _v0060 = _TMP43 + _TMP53;
    _x0064 = dot(_v0060, _v0060);
    _TMP59 = inversesqrt(_x0064)*_v0060;
    DotNaH = dot(_r0036, _TMP59);
    MaxNaH0 = max(DotNaH, 0.00000000E+000);
    specularLight = pow(MaxNaH0, 5.00000000E+001);
    SpecularMapcolor = texture2D(SpecularMapTexture, gl_TexCoord[0].xy);
    if (diffuseLight <= 0.00000000E+000) { // if begin
        specularLight = 0.00000000E+000;
    } // end if
    Ocolor.xyz = globalAmbient + gl_TexCoord[5].xyz + diffuse + (specularLight*8.00000000E+000)*SpecularMapcolor.xyz;
    Ocolor.w = 1.00000000E+000;
    colorposZ = texture2D(ShadowMapTexture, gl_TexCoord[3].xy);
    posz = colorposZ.x*2.55000000E+002 + colorposZ.y + colorposZ.z/2.55000000E+002 + 6.99999988E-001;
    if (gl_TexCoord[4].z > posz) { // if begin
        Ocolor.xyz = globalAmbient + gl_TexCoord[5].xyz;
    } // end if
    _i0076 = eyePosition - gl_TexCoord[2].xyz/gl_TexCoord[2].w;
    _TMP75 = _i0076 - (2.00000000E+000*_r0036)*dot(_r0036, _i0076);
    _r0080 = Worldmatrix*vec4(_TMP75,0.0);
    _OUT_color = MainColor*Ocolor*(textureCube(AmbientReflectiveTexture, _r0080.xyz) + 1.00000000E+000);
    _OUT_color.w = 5.00000000E-001;

    gl_FragColor = _OUT_color;
    return;
} 
