uniform float _imgW1;
uniform sampler2D _texSrc1;
void main()
{
	float dw=4.0/_imgW1;
    vec2 Tpos;
    vec4 color;
    Tpos=vec2(-dw,0.0);
    color += texture2D(_texSrc1,gl_TexCoord[0].xy+Tpos*5.0) * 0.1;
    color += texture2D(_texSrc1,gl_TexCoord[0].xy+Tpos*4.0) * 0.22;
    color += texture2D(_texSrc1,gl_TexCoord[0].xy+Tpos*3.0) * 0.358;
    color += texture2D(_texSrc1,gl_TexCoord[0].xy+Tpos*2.0) * 0.523;
    color += texture2D(_texSrc1,gl_TexCoord[0].xy+Tpos) * 0.843;
    color += texture2D(_texSrc1,gl_TexCoord[0].xy ) * 1.0;
    Tpos.x = dw;
    color += texture2D(_texSrc1,gl_TexCoord[0].xy+Tpos) * 0.843;
    color += texture2D(_texSrc1,gl_TexCoord[0].xy+Tpos*2.0) * 0.523;
    color += texture2D(_texSrc1,gl_TexCoord[0].xy+Tpos*3.0) * 0.358;
    color += texture2D(_texSrc1,gl_TexCoord[0].xy+Tpos*4.0) * 0.22;
    color += texture2D(_texSrc1,gl_TexCoord[0].xy+Tpos*5.0) * 0.1;
    color = color/5.0;
    color.w = 1.0;
    gl_FragColor = color;
    return;
}
