//#pragma once

#ifndef _TOPACEMODEL_H
#define _TOPACEMODEL_H

typedef enum TAM_Camera_Type {
    TAM_Camera_Type_Target		= 0x01, 
    TAM_Camera_Type_Free		= 0x02
} TAM_Camera_Type;


struct _TAM_Mesh_Head
{
	unsigned int OBJNum;
	void ** OBJAddress;
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
	void ** BoneAddress;
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
	unsigned int ChunkNum;//0x10地址表数量
	_TAM_Mesh_Head * MeshAddress;
	_TAM_Mat * MatsAddress;
	_TAM_Bone_Head * BoneAddress;
	_TAM_Light_Head * LightAddress;
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