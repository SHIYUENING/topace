#version 120
uniform mat4x4 MVPMatrix;
attribute vec3 Position_in;
void main()
{
	gl_Position = MVPMatrix * vec4(Position_in,1.0);
    return;
}
