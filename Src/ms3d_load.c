#include "ms3d_impl.h"

#include "matrix.h"
#include "image.h"

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

//+============================================================================
//|
//| ��ȡMS3D����
//|
//+============================================================================

ms3d_t ms3d_loadFromFile(const char* filename,int UserTexID) {
    void*  data   = 0;
    int    length = 0;
    FILE*  pFile  = 0;
    ms3d_t ret    = 0;

    // ���ļ�
    pFile = fopen(filename, "rb");
    if( pFile == 0 )
        goto err;

    // �����ļ���С
    fseek(pFile, 0, SEEK_END);
    length = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    // �����ļ���С�������ڴ沢��ȡ�ļ��е���������
    data = malloc(length);
    if( data == 0 )
        goto err;
    fread(data, 1, length, pFile);

    // תΪ����ms3d_loadFromMemory
    ret = ms3d_loadFromMemory(data, length,UserTexID);

err:
    free(data);
    if( pFile )
        fclose(pFile);
    return ret;
}

ms3d_t ms3d_loadFromMemory(const void* pData, unsigned int size,int UserTexID) {
    // �ֲ�����
    const char*     ptr = pData;
    const char*     end = ptr + size;
    ms3d_data_t*    pRet = 0;
    word            i;

    // ����꣬������ж�ȡ
    #define read(data, size)            \
    do {                                \
        if( ptr + (size) > end )        \
            goto err;                   \
        memcpy((data), ptr, (size));    \
        ptr += (size);                  \
    } while(0)

    #define read_data(data)             read(&(data), sizeof(data))
    #define read_array(arr, count)      read(arr, sizeof(arr[0]) * (count))

    // �����ڴ�ĺ�
    #define my_alloc(ptr, count)                \
    do {                                        \
        ptr = malloc(sizeof(*ptr) * (count));   \
        if( ptr == 0 )                          \
            goto err;                           \
    } while(0)

    // ��ȡheader
    // �ж��Ƿ�ȷʵΪms3d��ʽ
    {
        ms3d_header_t header;
        read_data(header);
        if( strncmp(header.id, "MS3D000000", 10) != 0 )
            goto err;
        if( header.version > 4 )
            goto err;
    }

    // �����ڴ�
    my_alloc(pRet, 1);
    memset(pRet, 0, sizeof(*pRet));

    // ��ȡ����
    read_data(pRet->vertices_count);
    my_alloc(pRet->vertices, pRet->vertices_count);
    read_array(pRet->vertices, pRet->vertices_count);

    // ��ȡ������
    read_data(pRet->triangles_count);
    my_alloc(pRet->triangles, pRet->triangles_count);
    read_array(pRet->triangles, pRet->triangles_count);

    // ��ȡ��
    read_data(pRet->groups_count);
    my_alloc(pRet->groups, pRet->groups_count);
    memset(pRet->groups, 0, sizeof(pRet->groups[0]) * pRet->groups_count);
    for(i=0; i<pRet->groups_count; ++i) {
        read_data(pRet->groups[i].flags);
        read_data(pRet->groups[i].name);
        read_data(pRet->groups[i].triangles);
        my_alloc(pRet->groups[i].triangleIndices, pRet->groups[i].triangles);
        read_array(pRet->groups[i].triangleIndices, pRet->groups[i].triangles);
        read_data(pRet->groups[i].materialIndex);
    }

    // ��ȡ����
    read_data(pRet->materials_count);
    my_alloc(pRet->materials, pRet->materials_count);
    read_array(pRet->materials, pRet->materials_count);

    // ��ȡFPS��֡��
    read_data(pRet->FPS);
    read_data(pRet->currentTime);
    read_data(pRet->totalFrames);

    // ��ȡ�ؽ�
    read_data(pRet->joints_count);
    my_alloc(pRet->joints, pRet->joints_count);
    memset(pRet->joints, 0, sizeof(pRet->joints[0]) * pRet->joints_count);
    for(i=0; i<pRet->joints_count; ++i) {
        read_data(pRet->joints[i].flags);
        read_data(pRet->joints[i].name);
        read_data(pRet->joints[i].parentName);
        read_data(pRet->joints[i].rotation);
        read_data(pRet->joints[i].position);
        read_data(pRet->joints[i].numRotationFrames);
        read_data(pRet->joints[i].numPositionFrames);
        my_alloc(
            pRet->joints[i].RotationFrames, pRet->joints[i].numRotationFrames);
        read_array(
            pRet->joints[i].RotationFrames, pRet->joints[i].numRotationFrames);
        my_alloc(
            pRet->joints[i].PositionFrames, pRet->joints[i].numPositionFrames);
        read_array(
            pRet->joints[i].PositionFrames, pRet->joints[i].numPositionFrames);
    }

    // ����ؽڵľ���
    my_alloc(pRet->joint_matrix, pRet->joints_count);
    my_alloc(pRet->joint_matrix_inverse, pRet->joints_count);
    for(i=0; i<pRet->joints_count; ++i) {
        ms3d_joint_t *p;

        mat4_identity(pRet->joint_matrix[i]);
        p = &pRet->joints[i];
        for(;;) {
            mat4 tmp1, tmp2;
            word j;

            // �ؽ�p�ľ��󣬱��浽tmp1
            mat4_identity(tmp1);
            mat4_translate(tmp1,
                p->position[0], p->position[1], p->position[2]);
            mat4_rotateZ(tmp1, p->rotation[2]);
            mat4_rotateY(tmp1, p->rotation[1]);
            mat4_rotateX(tmp1, p->rotation[0]);

            // �ؽ�p�ľ������ԭ���ľ��󣬱��浽tmp2��Ȼ���Ƶ���ǰ�ؽھ���
            mat4_multiply(tmp1, pRet->joint_matrix[i], tmp2);
            mat4_copy(pRet->joint_matrix[i], tmp2);

            // ��������ϼ��ؽڣ�ѭ������֮
            for(j=0; j<pRet->joints_count; ++j) {
                if( strcmp(p->parentName, pRet->joints[j].name) == 0 )
                    break;
            }
            if( j < pRet->joints_count )
                p = &pRet->joints[j];
            else
                break;
        }

        mat4_inverse(pRet->joint_matrix[i], pRet->joint_matrix_inverse[i]);
    }

    // ��ȡ����
    {
        GLuint* textures = malloc(sizeof(textures[0]) * pRet->materials_count);
        for(i=0; i<pRet->materials_count; ++i) {
            word j;
            image_t* pImg = 0;

            // �жϵ�ǰ���ʵ������Ƿ�����ǰ��ȡ����ͬ
            // ���ǣ���ֱ��ʹ��֮���������¶�ȡ
            for(j=0; j<i; ++j)
                if( strcmp(pRet->materials[i].texture,
                           pRet->materials[j].texture) == 0 &&
                    strcmp(pRet->materials[i].alphamap,
                           pRet->materials[j].alphamap) == 0)
                    break;
            if( j < i ) {
                textures[i] = textures[j];
                continue;
            }

            // ��ȡ��������
			if(UserTexID==0)
            image_loadAsTexture(
                pRet->materials[i].texture,
                pRet->materials[i].alphamap,
                &textures[i]);
			else
			{
				if(UserTexID>0)
					textures[i]=UserTexID;
				if(UserTexID<0)
					textures[i]=0;
			}
        }

        pRet->textures = textures;
    }

    // ȡ�����ڸ�����Ķ���
    #undef read
    #undef read_data
    #undef read_array
    #undef my_alloc

    // �ɹ�����
    return pRet;

err:
    ms3d_destroy(pRet);
    return 0;
}

void ms3d_destroy(ms3d_t ms3d) {
    ms3d_data_t* p = ms3d;
    if( p ) {
        word i;

        if( p->groups ) {
            for(i=0; i<p->groups_count; ++i)
                free(p->groups[i].triangleIndices);
        }
        if( p->joints ) {
            for(i=0; i<p->joints_count; ++i) {
                free(p->joints[i].PositionFrames);
                free(p->joints[i].RotationFrames);
            }
        }
        free(p->vertices);
        free(p->triangles);
        free(p->groups);
        free(p->materials);
        free(p->joints);
        free(p->joint_matrix);
        free(p->joint_matrix_inverse);
        free(p);
    }
}

float ms3d_totalTime(ms3d_t ms3d) {
    ms3d_data_t* p = ms3d;
    return p->totalFrames / p->FPS;
}

void ms3d_range(ms3d_t ms3d, float minXYZ[3], float maxXYZ[3]) {
    word i;
    ms3d_data_t* p = ms3d;

    minXYZ[0] = minXYZ[1] = minXYZ[2] = FLT_MAX;
    maxXYZ[0] = maxXYZ[1] = maxXYZ[2] = FLT_MIN;
    for(i=0; i<p->vertices_count; ++i) {
        minXYZ[0] = min(p->vertices[i].vertex[0], minXYZ[0]);
        maxXYZ[0] = max(p->vertices[i].vertex[0], maxXYZ[0]);
        minXYZ[1] = min(p->vertices[i].vertex[1], minXYZ[1]);
        maxXYZ[1] = max(p->vertices[i].vertex[1], maxXYZ[1]);
        minXYZ[2] = min(p->vertices[i].vertex[2], minXYZ[2]);
        maxXYZ[2] = max(p->vertices[i].vertex[2], maxXYZ[2]);
    }
}
