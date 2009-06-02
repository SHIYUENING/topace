#ifndef _ms3d_impl_H_
#define _ms3d_impl_H_

#include "ms3d.h"

typedef unsigned char  byte;
typedef unsigned short word;

// 以下的各种struct，以单字节对齐（也就是不对齐），而不是VC默认的四字节对齐
// 通常可以使用#include <pshpack1.h>
// VC下其实就是pragma pack(push, 1)
// 其它编译器可能会有所不同
#pragma pack(push,1)

typedef struct __ms3d_header {
    char        id[10];             // "MS3D000000"
    int         version;            // 4
} ms3d_header_t;

typedef struct __ms3d_vertex {
    byte        flags;              // SELECTED | SELECTED2 | HIDDEN。显示时无用，仅在编辑时使用
    float       vertex[3];          // 顶点坐标
    char        boneID;             // 所属关节的索引，-1表示顶点没有被指定到关节
    byte        referenceCount;     // 显示时无用，仅在编辑时使用
} ms3d_vertex_t;

typedef struct __ms3d_triangle {
    word        flags;              // SELECTED | SELECTED2 | HIDDEN。显示时无用，仅在编辑时使用
    word        vertexIndices[3];   // 三角形三个顶点的索引
    float       vertexNormals[3][3];// 三角形三个顶点的法线向量
    float       s[3];               // 三角形三个顶点的纹理坐标s（横坐标，左边为0.0，右边为1.0）
    float       t[3];               // 三角形三个顶点的纹理坐标t（纵坐标，上边为0.0，下边为1.0）
    byte        smoothingGroup;     // 平滑组，范围1-32
    byte        groupIndex;         // 所属的组索引
} ms3d_triangle_t;

typedef struct __ms3d_group {
    byte        flags;              // SELECTED | HIDDEN。显示时无用，仅在编辑时使用
    char        name[32];           // 
    word        triangles;          // 三角形的数目
    word*       triangleIndices;    // 组中所有三角形的索引
    char        materialIndex;      // 材质的索引，-1表示没有材质
} ms3d_group_t;

typedef struct __ms3d_material {
    char        name[32];           // 
    float       ambient[4];         // 环境颜色
    float       diffuse[4];         // 漫反射颜色
    float       specular[4];        // 镜面反射颜色
    float       emissive[4];        // 自身发光颜色
    float       shininess;          // 光滑程度，0~128，值越大越光滑，光源照在其上形成的亮点越小
    float       transparency;       // 透明度
    char        mode;               // 0, 1 ？？？
    char        texture[128];       // 纹理图象文件路径
    char        alphamap[128];      // 纹理alpha值图象文件路径
} ms3d_material_t;

typedef struct __ms3d_timevec {
    float       time;
    float       value[3];
} ms3d_timevec_t;

typedef struct __ms3d_joint {
    byte        flags;              // SELECTED | DIRTY
    char        name[32];           // 
    char        parentName[32];     // 上一级关节的名字，所有的关节都连接起来形成骨架
    float       rotation[3];        // 旋转，保存的是弧度而不是角度。旋转时先绕x轴旋转rotation[0]，再绕y旋转rotation[1]，最后绕z旋转rotation[2]
    float       position[3];        // 移动
    word        numRotationFrames;  // 关键帧。旋转和移动使用不同的关键帧。关键帧的数据包括了帧的时刻、帧的值。
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
    float               currentTime;            // 显示时无用，仅在编辑时使用
    float               totalFrames;

    // 下面的内容不是ms3d文件中保存的
    // 但是在显示时经常使用，因此也保存在此
    float               (*joint_matrix)[16];    // 保存每个关节的变换矩阵（包含了祖先关节）
    float               (*joint_matrix_inverse)[16];    // 上述矩阵的逆矩阵
    void*               textures;               // 每种材质中的纹理
                                                // 程序中使用OpenGL来显示，所以纹理只保存其编号，类型为GLuint即32位无符号整数
                                                // 如果使用DirectX，则应该使用另外的方式保存
                                                // 但无论如何保存，这里的指针类型为void*
} ms3d_data_t;

// 恢复到原来的对齐方式
// 通常可以使用#include <poppack.h>
// VC下其实就是pragma pack(pop)
// 其它编译器可能会有所不同
#pragma pack(pop)

#endif
