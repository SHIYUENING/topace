//#pragma once

#ifndef _TOPACEMODEL_H
#define _TOPACEMODEL_H
#include "Def.h"	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <xmmintrin.h>
typedef enum TAM_Camera_Type {
    TAM_Camera_Type_Target		= 0x01, 
    TAM_Camera_Type_Free		= 0x02
} TAM_Camera_Type;

struct _TAM_Mesh
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int OBJID;
	unsigned int OBJMATID;

	float BoneWeights[4];

	float BoneIDs[4];

	unsigned char UnUse1[16];

	unsigned int OBJChunkNum;//0x40obj����������
	__m128 * vertices;
	__m128 * Normals;
	float * texcos;

	unsigned int * Faces;
	unsigned int FaceNum;
	float * vecBoneWeights;
	unsigned int * vecBoneIDs;

	unsigned char MeshName[32];
};
struct _TAM_Bone_FRAME//֡
{
	unsigned char UnUse1[8];
	_TAM_Bone_FRAME * PreviousFrameAddress;
	unsigned int FrameTime;
	__m128 * FrameData;
};
struct _TAM_Bone_FRAME_Head//����
{
	unsigned int TotalFrameNum;//ʵ��֡��
	unsigned int MAXFrameNum;
	_TAM_Bone_FRAME ** FramesAddress;//TotalFrameNum��MAXFrameNumһ��������ǲ�ͬ�ģ�Ϊ���ڶ�ȡ�ٶȺʹ���ռ�֮�����У����ַ��������MAXFrameNum�������ǰ��û�����ݣ���ô��ǰ��ĵ�ַʵ������ָ����һ�������ݵ�֡
};
struct _TAM_Bone
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int BoneID;
	unsigned int NextBoneID;//0xcͬ��boneID ,Ҳ����ͬһ�����ڵ����һ��bone�������BoneID��Ȼ�Ϊ0���ʾͬһ�����ڵ�û����һ��bone��

	unsigned int ChildBoneID;
	unsigned char UnUse1[12];

	__m128 FirstTranslate;

	__m128 FirstRotate;

	__m128 FirstScale;

	unsigned int FrameChunkNum;
	_TAM_Bone_FRAME_Head * TranslateFramesHeadAddress;
	_TAM_Bone_FRAME_Head * RotateFramesHeadAddress;
	_TAM_Bone_FRAME_Head * ScaleFramesHeadAddress;

	unsigned char BoneName[32];
};

struct _TAM_Mesh_Head
{
	unsigned int OBJNum;
	_TAM_Mesh ** OBJAddress;
};
struct _TAM_Mat
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int MatID;
	unsigned char UnUse1[4];

	unsigned char MatName[32];

	unsigned char ambient[4];
	unsigned char diffuse[4];
	unsigned char specular[4];
	unsigned char self_illum[4];

	float specularLv;
	float Glossiness;
	float opacity;
	unsigned char UnUse2[4];

	unsigned char diffuseMap[32];
	unsigned char specularMap[32];
	unsigned char NormalMap[32];
	unsigned char Refract[32];
};
struct _TAM_Bone_Head
{
	unsigned int BoneNum;
	_TAM_Bone** BoneAddress;
};
struct _TAM_Light_Head
{
	unsigned int LightNum;
	void ** LightAddress;
};
struct _TAM_Camera
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int CameraID;
	unsigned char UnUse1[4];

	unsigned int CameraType;
	float Fov;
	unsigned int SelfBoneID;
	unsigned int TGTBoneID;

	unsigned char CameraName[32];
};
struct _TAM_FileHead
{
	unsigned char HeadName[4];
	unsigned int FileSize;
	unsigned char UnUse1[4];
	unsigned char UnUse2[4];
	unsigned int ChunkNum;//0x10��ַ������
	_TAM_Mesh_Head * MeshHeadAddress;
	_TAM_Mat * MatsAddress;
	_TAM_Bone_Head * BoneHeadAddress;
	_TAM_Light_Head * LightHeadAddress;
	_TAM_Camera * CameraAddress;
};

class CTopAceModel
{
public:
	CTopAceModel(void);
	~CTopAceModel(void);
	bool ReadFile(unsigned char * FileName);
	_TAM_FileHead TAM_FileHead;
};
#endif