#version 110
#extension GL_ARB_texture_rectangle : enable
varying vec2 TexCoord0;
uniform sampler2DRect texColor;
uniform float AveLum;
//uniform float imgW;
//uniform float imgH;
void main()
{
	//float dx = 1.0/imgW;
	//float dy = 1.0/imgH;

	vec4 color = texture2DRect(texColor,TexCoord0.xy);
	color += texture2DRect(texColor,TexCoord0.xy+vec2(3.0,0.0));

	color += texture2DRect(texColor,TexCoord0.xy+vec2(0.0,1.0));
	color += texture2DRect(texColor,TexCoord0.xy+vec2(3.0,1.0));

	color += texture2DRect(texColor,TexCoord0.xy+vec2(0.0,2.0));
	color += texture2DRect(texColor,TexCoord0.xy+vec2(3.0,2.0));

	color += texture2DRect(texColor,TexCoord0.xy+vec2(0.0,3.0));
	color += texture2DRect(texColor,TexCoord0.xy+vec2(3.0,3.0));
	color /= 8.0;

	vec4 cout = vec4(0.0,0.0,0.0,0.0);
	float lum = color.x * 0.3 + color.y *0.59 + color.z * 0.11;
	vec4 p = color*(lum/0.23);
	p= p/(p+1.0);
	float luml = (p.x+p.y+p.z)/3.0;
	if (luml > 0.75)
	{
		cout = p;
	}
	gl_FragColor = cout;	
	return;
}