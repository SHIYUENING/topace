uniform vec3 globalAmbient;
uniform vec3 paraLightColor;
uniform vec3 paraLightDirection;
uniform vec3 eyePosition;
uniform vec3 FogColor;
uniform sampler2D testTexture;
uniform samplerCube AmbientReflectiveTexturSea;

void main()
{
    vec4 OUTcolor;

    vec3  vBumpTexA = texture2D(testTexture, gl_TexCoord[1].xy).xyz;
    vec3  vBumpTexB = texture2D(testTexture, gl_TexCoord[2].xy).xyz;
    vec3  vBumpTexC = texture2D(testTexture, gl_TexCoord[3].xy).xyz;
    vec3  vBumpTexD = texture2D(testTexture, gl_TexCoord[4].xy).xyz;
    vec3  NormalIN = (vBumpTexA.xyz + vBumpTexB.xyz + vBumpTexC.xyz + vBumpTexD.xyz)/4.0;
    vec3  vReflBump = vec3((NormalIN.x - 0.5)*2.0, (NormalIN.z - 0.5)*2.0, (NormalIN.y - 0.5)*2.0);
    vec3  ViewDir =- normalize(gl_TexCoord[0].xyz*1000.0 - eyePosition);
    vec4  reflection = textureCube(AmbientReflectiveTexturSea, reflect(ViewDir,vReflBump));
    float Fresnel = (1.0 - max(dot(ViewDir, vReflBump), 0.0))*0.5;
    vec3  LightDir = normalize(paraLightDirection);
    float light = max(dot(LightDir, vReflBump), 0.0);
    vec3 HightLight = normalize(LightDir + ViewDir);
    float specularLight = pow(max(dot(normalize(vReflBump), HightLight), 0.0), 1000.0);

    OUTcolor.xyz = (Fresnel*reflection.xyz + (1.0 - Fresnel)*vec3(0.1,0.5,1.0))*(light*paraLightColor + globalAmbient) + specularLight*paraLightColor;
	float seapos=length(gl_TexCoord[0].xyz*1000.0 - eyePosition);
    float fogb = max(0.0,min((100000.0-seapos)/80000.0,1.0));
    OUTcolor.xyz = OUTcolor.xyz*fogb + (1.0 - fogb)*FogColor;
    OUTcolor.w = 1.0;
    gl_FragColor = OUTcolor;
    return;
} 
