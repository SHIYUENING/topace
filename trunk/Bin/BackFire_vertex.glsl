uniform vec3 BackFireEyeDir;
uniform vec4 BackFireColor;
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	vec3 EyeNormal=normalize(cross(vec3(0.0,0.0,1.0),normalize(BackFireEyeDir)));
	float outColorA=1.0-abs(dot(normalize(gl_Normal),EyeNormal));
    //gl_FrontColor = vec4(BackFireColor.xyz,BackFireColor.z*outColorA*outColorA*5.0);
    gl_FrontColor = vec4(outColorA*0.7,outColorA*0.7,1.0,outColorA);
    //gl_FrontColor = vec4(gl_Normal.xyz,1.0);
    return;
}
