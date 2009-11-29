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
    //float diffuseLight = max(dot(Normal, LightDir), 0.0);
    //vec3 diffuse = paraLightColor*diffuseLight;
    vec3 diffuse = (dot(Normal, LightDir) * 0.5 + 0.5) * paraLightColor;
	diffuse = diffuse*diffuse;
    vec3 ViewDir = normalize(eyePosition-gl_TexCoord[2].xyz);
    vec3 HightLight = normalize(LightDir + ViewDir);
    float specularLight = pow(max(dot(Normal, HightLight), 0.0), 50.0);
    vec4 SpecularMapcolor = texture2D(SpecularMapTexture, gl_TexCoord[0].xy);
  //  if (diffuseLight <= 0.0) { 
  //      specularLight = 0.0;
  //  }
    vec4 shadowPos=gl_TexCoord[4]-vec4(0.0,0.0,0.4,0.0);
    vec4 MX=vec4 (0.15,0.0,0.0,0.0);
	vec4 MU=vec4 (0.0,0.15,0.0,0.0);
	float posz=0.0;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos ).x;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos+MX ).x;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos-MX ).x;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos+MU ).x;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos-MU ).x;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos+MX+MU ).x;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos-MX+MU ).x;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos+MX-MU ).x;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos-MX-MU ).x;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos+MX*2.0 ).x;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos-MX*2.0 ).x;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos+MU*2.0 ).x;
	posz=posz+shadow2DProj( ShadowMapTexture, shadowPos-MU*2.0 ).x;
	//posz=posz+shadow2DProj( ShadowMapTexture, shadowPos+MX*2.0+MU*2.0 ).x;
	//posz=posz+shadow2DProj( ShadowMapTexture, shadowPos-MX*2.0+MU*2.0 ).x;
	//posz=posz+shadow2DProj( ShadowMapTexture, shadowPos+MX*2.0-MU*2.0 ).x;
	//posz=posz+shadow2DProj( ShadowMapTexture, shadowPos-MX*2.0-MU*2.0 ).x;
	//posz=posz+shadow2DProj( ShadowMapTexture, shadowPos+MX*3.0 ).x;
	//posz=posz+shadow2DProj( ShadowMapTexture, shadowPos-MX*3.0 ).x;
	//posz=posz+shadow2DProj( ShadowMapTexture, shadowPos+MU*3.0 ).x;
	//posz=posz+shadow2DProj( ShadowMapTexture, shadowPos-MU*3.0 ).x;
	posz=posz/13.0;
	
	vec4 Ocolor;
		float lerpF = clamp(Normal.y*0.5+0.5f,0.0,1.0);
		Ocolor.xyz = globalAmbient*0.5f*(1.0-lerpF*lerpF)+globalAmbient*lerpF*lerpF + gl_TexCoord[5].xyz + (diffuse + (specularLight*8.0)*SpecularMapcolor.x)*posz;
    //Ocolor.xyz = lerp(globalAmbient*0.5f, globalAmbient, clamp(Normal.y*0.5+0.5f,0.0,1.0)) + gl_TexCoord[5].xyz + (diffuse + (specularLight*8.0)*SpecularMapcolor.x)*posz;
    Ocolor.w = 1.0;
    vec3 Reflective=reflect(ViewDir,Normal);
    vec4 ReflectiveWorld = Worldmatrix*vec4(Reflective,0.0);
    gl_FragColor = MainColor*Ocolor*(textureCube(AmbientReflectiveTexture, ReflectiveWorld.xyz) + 1.0);
    gl_FragColor.w = 0.5;
    return;
} 
