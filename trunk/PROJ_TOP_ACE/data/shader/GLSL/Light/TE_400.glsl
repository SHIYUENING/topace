#version 400
layout(triangles, equal_spacing, ccw) in;
in vec3 tcPosition[];
in vec3 tcNormal[];
in vec2 tcTexCoord0[];
in vec4 tcColor[];

out vec4 teVertexEyeDir;
out vec3 teNormal;
out vec2 teTexCoord0;
out vec4 teColor;
in vec3 b210[];
in vec3 b120[];
in vec3 b021[];
in vec3 b012[];
in vec3 b102[];
in vec3 b201[];
in vec3 b111[];
in vec3 n110[];
in vec3 n011[];
in vec3 n101[];
uniform mat4x4 PMatrix;
//uniform mat4x4 MVPMatrix;

void main()
{
	// The barycentric coordinates
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;
	float w = gl_TessCoord.z;

	// Precompute squares and squares * 3 
	float uu = u * u;
	float vv = v * v;
	float ww = w * w;
	float uu3 = uu * 3;
	float vv3 = vv * 3;
	float ww3 = ww * 3;
		vec3 world_pos = tcPosition[0] * ww * w
					+ tcPosition[1] * uu * u
					+ tcPosition[2] * vv * v
					+ b210[0] * ww3 * u
					+ b120[0] * w * uu3
					+ b201[0] * ww3 * v
					+ b021[0] * uu3 * v
					+ b102[0] * w * vv3
					+ b012[0] * u * vv3
					+ b111[0] * 6 * w * u * v;
	/*vec3 world_pos = gl_TessCoord.x*tcPosition[0]
			 +gl_TessCoord.y*tcPosition[1]
			 +gl_TessCoord.z*tcPosition[2];*/

    gl_Position = PMatrix* vec4(world_pos, 1.0);
	teVertexEyeDir = vec4(world_pos, 1.0);
	/*vec3 Normal = tcNormal[0] * ww
					+ tcNormal[1] * uu
					+ tcNormal[2] * vv
					+ n110[0] * w * u
					+ n011[0] * u * v
					+ n101[0] * w * v;*/
	vec3 Normal=gl_TessCoord.x*tcNormal[1]
			 +gl_TessCoord.y*tcNormal[2]
			 +gl_TessCoord.z*tcNormal[0];
	teNormal=Normal;

	teTexCoord0=gl_TessCoord.z*tcTexCoord0[0]
			 +gl_TessCoord.x*tcTexCoord0[1]
			 +gl_TessCoord.y*tcTexCoord0[2];
			 
	teColor=gl_TessCoord.x*tcColor[1]
			 +gl_TessCoord.y*tcColor[2]
			 +gl_TessCoord.z*tcColor[0];
}