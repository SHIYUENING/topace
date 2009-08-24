uniform mat4 ShadowMapMVPmatrix;
uniform vec4 MissleLightDirection;
uniform vec3 MissleLightColor;
void main()
{
    //vec2 _OUT_texcoord3;
    vec4 ShadowPos = ShadowMapMVPmatrix * gl_Vertex;
    vec3 MissleLightDir = normalize(MissleLightDirection.xyz - gl_Vertex.xyz);
    float diffuseLight = max( dot( normalize(gl_Normal),MissleLightDir ), 0.0);
    vec3 diffuse = MissleLightColor*diffuseLight*10.0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;
    gl_TexCoord[0].xy = gl_MultiTexCoord0.xy;
    gl_TexCoord[1].xyz = gl_Normal;
    gl_TexCoord[2] = gl_Vertex;
    //gl_TexCoord[3].xy = _OUT_texcoord3;
    gl_TexCoord[4] = ShadowPos;
    gl_TexCoord[5].xyz = diffuse;
    return;
}
