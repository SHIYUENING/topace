#include "ms3d_impl.h"

#include "matrix.h"

#include <stdlib.h>
#include <string.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/gl.h>
// ����ʱ������ֵ
static void getTimeValue(ms3d_timevec_t* p, word count,
                         float time, float start[3], float result[3]) {
    word i;
    float weight, *p1=0, *p2=0;
    if( count > 0 ) {
        for(i=0; i<count; ++i) {
            if( p[i].time > time ) {
                if( i == 0 ) {
                    p1 = start;
                    p2 = p[0].value;
                    weight = time / p[i].time;
                } else {
                    p1 = p[i-1].value;
                    p2 = p[i].value;
                    weight = (time - p[i-1].time) / (p[i].time - p[i-1].time);
                }
                break;
            }
            if( p1 == 0 ) {
                p1 = p2 = p[count-1].value;
                weight = 1.0f;
            }
        }
    } else {
        p1 = p2 = start;
        weight = 1.0f;
    }
    result[0] = p1[0]*(1.0f-weight) + p2[0]*weight;
    result[1] = p1[1]*(1.0f-weight) + p2[1]*weight;
    result[2] = p1[2]*(1.0f-weight) + p2[2]*weight;
}
float time2=0.0f;
float Nortmp[3];
void ms3d_drawStatic(ms3d_t ms3d) {
    ms3d_data_t* p = ms3d;

    // ����ѭ��
    // ��άģ���ɶ����(group)����
    // ÿ����(group)�ɶ��������(triangle)����
    // ÿ��������(triangle)����������(vertex)����
    word i, j, k;
    for(i=0; i<p->groups_count; ++i) {
        // Ӧ�ò���
        ms3d_material_t* pMaterial = &p->materials[p->groups[i].materialIndex];
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pMaterial->ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pMaterial->diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pMaterial->specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, pMaterial->emissive);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->shininess);
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f - pMaterial->transparency);
        glBindTexture(GL_TEXTURE_2D,
            ((GLuint*)p->textures)[p->groups[i].materialIndex]);

        // ����������
        glBegin(GL_TRIANGLES);
        for(j=0; j<p->groups[i].triangles; ++j) 
		{
            ms3d_triangle_t* pTriangle = &p->triangles[p->groups[i].triangleIndices[j]];
            for(k=0; k<3; ++k) 
			{
				ms3d_vertex_t* pVertex =  &p->vertices[pTriangle->vertexIndices[k]];

				vec4 v1, v2;
				mat4 m;

				vec4_fromXYZW(v1, pTriangle->vertexNormals[k][0], pTriangle->vertexNormals[k][1], pTriangle->vertexNormals[k][2],0.0f);

				// ��һ�������Ϲؽڵ������
				mat4_transform(p->joint_matrix_inverse[pVertex->boneID], v1, v2);
				// �ڶ���������ʱ�����һ������
				mat4_identity(m);
				{
					ms3d_joint_t* pJoint = &p->joints[pVertex->boneID];

					getTimeValue(pJoint->PositionFrames, pJoint->numPositionFrames, time2, pJoint->position, v1);
					mat4_translate(m, v1[0], v1[1], v1[2]);

					getTimeValue(pJoint->RotationFrames, pJoint->numRotationFrames, time2, pJoint->rotation, v1);
					mat4_rotateZ(m, v1[2]);
					mat4_rotateY(m, v1[1]);
					mat4_rotateX(m, v1[0]);
				}
				mat4_transform(m, v2, v1);
				// �����������Ϲؽھ���
				mat4_transform(p->joint_matrix[pVertex->boneID], v1, v2);
				
				Nortmp[0] = v2[0];
				Nortmp[1] = v2[1];
				Nortmp[2] = v2[2];
                
                glTexCoord2f(pTriangle->s[k], 1.0f - pTriangle->t[k]);
                glNormal3fv(Nortmp);
                glVertex3fv(pVertex->vertex);
            }
        }
        glEnd();
    }
}


void ms3d_drawAnimation(ms3d_t ms3d, float time) {
    ms3d_data_t* p = ms3d;
    word i, j, k,i2;
    ms3d_vertex_t* pOriginalVertices = p->vertices;

	time2=time;
    // ��ԭ���Ķ������ݱ��浽pOriginalVertices
    // Ȼ�����¸���һ��
    p->vertices = malloc(sizeof(ms3d_vertex_t) * p->vertices_count);
    if( p->vertices == 0 )
        goto err;
    memcpy(p->vertices, pOriginalVertices, sizeof(ms3d_vertex_t) * p->vertices_count);

    // ���ݹؽڡ�ʱ������أ��޸Ķ����λ��
    // ע���޸���ʵ���ڸ��Ƶ������Ͻ����޸�
    for(i2=0; i2<p->vertices_count; ++i2) 
	{
		ms3d_vertex_t* pVertex = &p->vertices[i2];
		pVertex->referenceCount=0;
	
	}

	for(i=0; i<p->groups_count; ++i)
	for(j=0; j<p->groups[i].triangles; ++j) 
	{
		ms3d_triangle_t* pTriangle = &p->triangles[p->groups[i].triangleIndices[j]];
		for(k=0; k<3; ++k) 
		{
			ms3d_vertex_t* pVertex = &p->vertices[pTriangle->vertexIndices[k]];
			
			if(pVertex->referenceCount==0)
			{
				vec4 v1, v2;
				mat4 m;

				
				vec4_fromXYZ(v1, pVertex->vertex[0], pVertex->vertex[1], pVertex->vertex[2]);

				// ��һ�������Ϲؽڵ������
				mat4_transform(p->joint_matrix_inverse[pVertex->boneID], v1, v2);
				// �ڶ���������ʱ�����һ������
				mat4_identity(m);
				{
					ms3d_joint_t* pJoint = &p->joints[pVertex->boneID];

					getTimeValue(pJoint->PositionFrames, pJoint->numPositionFrames, time, pJoint->position, v1);
					mat4_translate(m, v1[0], v1[1], v1[2]);

					getTimeValue(pJoint->RotationFrames, pJoint->numRotationFrames, time, pJoint->rotation, v1);
					mat4_rotateZ(m, v1[2]);
					mat4_rotateY(m, v1[1]);
					mat4_rotateX(m, v1[0]);
				}
				mat4_transform(m, v2, v1);
				// �����������Ϲؽھ���
				mat4_transform(p->joint_matrix[pVertex->boneID], v1, v2);
			
				pVertex->referenceCount=1;
				pVertex->vertex[0] = v2[0];
				pVertex->vertex[1] = v2[1];
				pVertex->vertex[2] = v2[2];
			}
		}
	}

    ms3d_drawStatic(p);

err:
    // �ָ���ԭ������Ķ�������
    free(p->vertices);
    p->vertices = pOriginalVertices;
}
