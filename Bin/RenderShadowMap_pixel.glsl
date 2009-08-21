
float _x0006;

void main()
{
    gl_FragColor.x = floor(gl_TexCoord[1].z)/2.55000000E+002;
    gl_FragColor.y = fract(gl_TexCoord[1].z);
    _x0006 = gl_TexCoord[1].z*2.55000000E+002;
    gl_FragColor.z = fract(_x0006);
    gl_FragColor.w = 1.00000000E+000;
    return;
} 
