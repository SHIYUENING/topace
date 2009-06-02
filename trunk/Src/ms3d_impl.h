#ifndef _ms3d_impl_H_
#define _ms3d_impl_H_

#include "ms3d.h"

typedef unsigned char  byte;
typedef unsigned short word;

// ���µĸ���struct���Ե��ֽڶ��루Ҳ���ǲ����룩��������VCĬ�ϵ����ֽڶ���
// ͨ������ʹ��#include <pshpack1.h>
// VC����ʵ����pragma pack(push, 1)
// �������������ܻ�������ͬ
#pragma pack(push,1)

typedef struct __ms3d_header {
    char        id[10];             // "MS3D000000"
    int         version;            // 4
} ms3d_header_t;

typedef struct __ms3d_vertex {
    byte        flags;              // SELECTED | SELECTED2 | HIDDEN����ʾʱ���ã����ڱ༭ʱʹ��
    float       vertex[3];          // ��������
    char        boneID;             // �����ؽڵ�������-1��ʾ����û�б�ָ�����ؽ�
    byte        referenceCount;     // ��ʾʱ���ã����ڱ༭ʱʹ��
} ms3d_vertex_t;

typedef struct __ms3d_triangle {
    word        flags;              // SELECTED | SELECTED2 | HIDDEN����ʾʱ���ã����ڱ༭ʱʹ��
    word        vertexIndices[3];   // �������������������
    float       vertexNormals[3][3];// ��������������ķ�������
    float       s[3];               // �����������������������s�������꣬���Ϊ0.0���ұ�Ϊ1.0��
    float       t[3];               // �����������������������t�������꣬�ϱ�Ϊ0.0���±�Ϊ1.0��
    byte        smoothingGroup;     // ƽ���飬��Χ1-32
    byte        groupIndex;         // ������������
} ms3d_triangle_t;

typedef struct __ms3d_group {
    byte        flags;              // SELECTED | HIDDEN����ʾʱ���ã����ڱ༭ʱʹ��
    char        name[32];           // 
    word        triangles;          // �����ε���Ŀ
    word*       triangleIndices;    // �������������ε�����
    char        materialIndex;      // ���ʵ�������-1��ʾû�в���
} ms3d_group_t;

typedef struct __ms3d_material {
    char        name[32];           // 
    float       ambient[4];         // ������ɫ
    float       diffuse[4];         // ��������ɫ
    float       specular[4];        // ���淴����ɫ
    float       emissive[4];        // ��������ɫ
    float       shininess;          // �⻬�̶ȣ�0~128��ֵԽ��Խ�⻬����Դ���������γɵ�����ԽС
    float       transparency;       // ͸����
    char        mode;               // 0, 1 ������
    char        texture[128];       // ����ͼ���ļ�·��
    char        alphamap[128];      // ����alphaֵͼ���ļ�·��
} ms3d_material_t;

typedef struct __ms3d_timevec {
    float       time;
    float       value[3];
} ms3d_timevec_t;

typedef struct __ms3d_joint {
    byte        flags;              // SELECTED | DIRTY
    char        name[32];           // 
    char        parentName[32];     // ��һ���ؽڵ����֣����еĹؽڶ����������γɹǼ�
    float       rotation[3];        // ��ת��������ǻ��ȶ����ǽǶȡ���תʱ����x����תrotation[0]������y��תrotation[1]�������z��תrotation[2]
    float       position[3];        // �ƶ�
    word        numRotationFrames;  // �ؼ�֡����ת���ƶ�ʹ�ò�ͬ�Ĺؼ�֡���ؼ�֡�����ݰ�����֡��ʱ�̡�֡��ֵ��
    word        numPositionFrames;  // 
    ms3d_timevec_t* RotationFrames; // 
    ms3d_timevec_t* PositionFrames; // 
} ms3d_joint_t;

typedef struct __ms3d_data {
    short               vertices_count;
    ms3d_vertex_t*      vertices;
    short               triangles_count;
    ms3d_triangle_t*    triangles;
    short               groups_count;
    ms3d_group_t*       groups;
    short               materials_count;
    ms3d_material_t*    materials;
    short               joints_count;
    ms3d_joint_t*       joints;
    float               FPS;
    float               currentTime;            // ��ʾʱ���ã����ڱ༭ʱʹ��
    float               totalFrames;

    // ��������ݲ���ms3d�ļ��б����
    // ��������ʾʱ����ʹ�ã����Ҳ�����ڴ�
    float               (*joint_matrix)[16];    // ����ÿ���ؽڵı任���󣨰��������ȹؽڣ�
    float               (*joint_matrix_inverse)[16];    // ��������������
    void*               textures;               // ÿ�ֲ����е�����
                                                // ������ʹ��OpenGL����ʾ����������ֻ�������ţ�����ΪGLuint��32λ�޷�������
                                                // ���ʹ��DirectX����Ӧ��ʹ������ķ�ʽ����
                                                // ��������α��棬�����ָ������Ϊvoid*
} ms3d_data_t;

// �ָ���ԭ���Ķ��뷽ʽ
// ͨ������ʹ��#include <poppack.h>
// VC����ʵ����pragma pack(pop)
// �������������ܻ�������ͬ
#pragma pack(pop)

#endif
