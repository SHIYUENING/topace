#version 120
varying vec2 TexCoord0;
uniform sampler2D _texSrc1;
void main()
{
    gl_FragColor = vec4(1.0,1.0,1.0,texture2D(_texSrc1, TexCoord0.xy).x*1.2);
    return;
}
