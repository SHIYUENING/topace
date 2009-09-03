uniform vec4 BackFireEyeDir;
uniform vec4 BackFireColor;
uniform float EnginePower;
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	float BackPosZ=1.0-min((gl_Vertex.z-20.0)/(55.0*EnginePower),1.0);
	float outColorA=1.0-abs(dot(normalize(gl_Normal),BackFireEyeDir.xyz));
    gl_FrontColor = vec4(BackFireColor.xyz,BackFireColor.z*BackPosZ*(1.0+BackFireEyeDir.a*0.5))*outColorA;
    return;
}
