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
void main()
{
	vec4 MainColor	=	texture2D(testTexture, gl_TexCoord[0].xy);
    vec3 Tangent	=	normalize(gl_Color.xyz);
    vec3 NormalIn	=	normalize(gl_TexCoord[1].xyz);
    vec3 Binormal	=	normalize(cross(Tangent,NormalIn));

    vec3 NN2 = texture2D(NormalMapTexture, gl_TexCoord[0].xy).xyz*2.0-vec3(1.0,1.0,1.0);
    mat3 TBN = mat3(Tangent,Binormal,NormalIn);
    vec3 Normal = TBN*NN2;
    vec3 LightDir = normalize(paraLightDirection);
    float diffuseLight = max(dot(Normal, LightDir), 0.0);
    vec3 diffuse = paraLightColor*diffuseLight;
    vec3 ViewDir = normalize(eyePosition-gl_TexCoord[2].xyz);
    vec3 HightLight = normalize(LightDir + ViewDir);
    float specularLight = pow(max(dot(Normal, HightLight), 0.0), 50.0);
    vec4 SpecularMapcolor = texture2D(SpecularMapTexture, gl_TexCoord[0].xy);
    if (diffuseLight <= 0.0) { 
        specularLight = 0.0;
    }
    vec4 shadowPos=gl_TexCoord[4]-vec4(0.0,0.0,0.4,0.0);
	float posz=shadow2DProj( ShadowMapTexture, shadowPos ).x;

	vec4 Ocolor;
    Ocolor.xyz = globalAmbient + gl_TexCoord[5].xyz + (diffuse + (specularLight*8.0)*SpecularMapcolor.xyz)*posz;
    Ocolor.w = 1.0;
    vec3 Reflective=reflect(ViewDir,Normal);
    vec4 ReflectiveWorld = Worldmatrix*vec4(Reflective,0.0);
    gl_FragColor = MainColor*Ocolor*(textureCube(AmbientReflectiveTexture, ReflectiveWorld.xyz) + 1.0);
    gl_FragColor.w = 0.5;
    return;
} 
