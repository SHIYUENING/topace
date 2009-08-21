
uniform sampler2D texColor;
uniform float AveLum;
uniform float imgW;
uniform float imgH;
void main()
{
	float dx = 1.0/imgW;
	float dy = 1.0/imgH;
	//对texColor进行采样
	vec4 color = texture2D(texColor,gl_TexCoord[0].xy);
	color += texture2D(texColor,gl_TexCoord[0].xy+vec2(dx*3.0,0.0));

	color += texture2D(texColor,gl_TexCoord[0].xy+vec2(0.0,dy));
	color += texture2D(texColor,gl_TexCoord[0].xy+vec2(dx*3.0,dy));

	color += texture2D(texColor,gl_TexCoord[0].xy+vec2(0.0,dy*2.0));
	color += texture2D(texColor,gl_TexCoord[0].xy+vec2(dx*3.0,dy*2.0));

	color += texture2D(texColor,gl_TexCoord[0].xy+vec2(0.0,dy*3.0));
	color += texture2D(texColor,gl_TexCoord[0].xy+vec2(dx*3.0,dy*3.0));
	color /= 8.0;
	//计算该像素在Tone Mapping之后的亮度值，如果依然很大，则该像素将产生光晕
	vec4 cout = vec4(0.0,0.0,0.0,0.0);
	float lum = color.x * 0.3 + color.y *0.59 + color.z * 0.11;
	vec4 p = color*(lum/0.23);
	p.x = p.x/(p.x+1.0);
	p.y = p.y/(p.y+1.0);
	p.z = p.z/(p.z+1.0);
	float luml = (p.x+p.y+p.z)/3.0;
	if (luml > 0.75)
	{
		cout = p;
	}
	gl_FragColor = cout;	
}