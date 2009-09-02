uniform vec4 BackFireEyeDir;
uniform vec4 BackFireColor;
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	//vec3 EyeNormal=normalize(cross(vec3(0.0,0.0,1.0),normalize(BackFireEyeDir)));
	float long=1.0-min((gl_Vertex.z-20.0)/55.0,1.0);
	float outColorA=1.0-abs(dot(normalize(gl_Normal),BackFireEyeDir.xyz));
	
    //gl_FrontColor = vec4(BackFireColor.xyz,BackFireColor.z*outColorA*outColorA*5.0);
    gl_FrontColor = vec4(outColorA*0.7,outColorA*0.7,1.0,outColorA*long*(1.0+BackFireEyeDir.a*0.5));
    //gl_FrontColor = vec4(gl_Normal.xyz,1.0);
    return;
}
