//#pragma once

#ifndef _TOPACEMODEL_H
#define _TOPACEMODEL_H
#include "Def.h"	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <xmmintrin.h>
#include "Glsl.h"
#include "GLSLLoader.h"
#include "FileSysBace.h"
#include "TALogSys.h"
#include "CharSysBace.h"
#include "Common.h"
#include "EasyMatrix.h"
#include "TexManager.h"
#define _TAM_VERSION 1 
typedef enum _TAM_File_States {
	_TAM_File_States_NoRead =0x01,
	_TAM_File_States_ReadOK =0x02,
	_TAM_File_States_NoFile =0x03,
	_TAM_File_States_ReadFail = 0x04,
	_TAM_File_States_ErrorVer = 0x05
}_TAM_File_States;
typedef enum _TAM_Camera_Type {
    TAM_Camera_Type_Target		= 0x01, 
    TAM_Camera_Type_Free		= 0x02
} _TAM_Camera_Type;
typedef enum _TAM_Light_Type {//****灯光种类：01_omni,02_freeSpot,03_targetSpot,04_freeDirect,05_targetDirect*********
	TAM_Light_Type_Omni = 0x01,
	TAM_Light_Type_Free_Spot = 0x02,
	TAM_Light_Type_Target_Spot = 0x03,
	TAM_Light_Type_Free_Direct = 0x04,
	TAM_Light_Type_Target_Direct = 0x05
} _TAM_Light_Type;
typedef enum _TAM_Bone_Frame_Type{
	_TAM_Bone_Frame_Type_Translate = 0x00,
	_TAM_Bone_Frame_Type_Rotate = 0x01,
	_TAM_Bone_Frame_Type_Scale = 0x02
} _TAM_Bone_Frame_Type;
typedef enum _TAM_Light_Frame_Type{
	_TAM_Light_Frame_Type_Color = 0x00,
	_TAM_Light_Frame_Type_Constant = 0x01,
	_TAM_Light_Frame_Type_CutOff = 0x02
} _TAM_Light_Frame_Type;
struct _TAM_vecBoneWeightsAndBoneIDs
{
	float vecBoneWeights[4];
	unsigned int vecBoneIDs[4];
};
struct _TAM_Mesh_Fiexible
{
	__m128 * vertices;
	__m128 * Normals;
	unsigned int vecNum;
};
struct _TAM_Mesh
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int OBJID;
	unsigned int OBJMATID;

	//float BoneWeights[4];

	//unsigned int BoneIDs[4];

	unsigned char BoneWeightNum;
	unsigned char IsFiexible;
	unsigned char UnUse1[14];

	unsigned int OBJChunkNum;//0x40obj内数据数量
	__m128 * vertices;
	__m128 * Normals;
	float * texcos;

	unsigned int * Faces;
	unsigned int FaceNum;
	unsigned int vecNum;
	_TAM_vecBoneWeightsAndBoneIDs * vecBoneWeightsAndBoneIDs;
	//unsigned int * vecBoneIDs;

	unsigned char MeshName[32];
	unsigned char MakeShadow;
	unsigned char UseLight;
	unsigned char Render;
	unsigned char RenderCartoon;
	unsigned char Frame;
	unsigned char OneFace;
	unsigned char UseAlpha;
	unsigned char UnUse2[9];

	float BoxMin[4];

	float BoxMax[4];
};
struct _TAM_Mesh_Head
{
	//unsigned int OBJNum;
	_TAM_Mesh ** OBJAddress;
};
struct _TAM_Mat_Texture
{
	unsigned int TexID;
	unsigned int TexManagerID;
	int TexType;
	//Textures Mat_Texture;
	bool UseAlpha;
};
struct _TAM_Mat
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int MatID;
	unsigned char UnUse1[4];

	unsigned char MatName[32];

	float ambient[4];
	float diffuse[4];
	float specular[4];
	float self_illum[4];

	float specularLv;
	float Glossiness;
	float opacity;
	unsigned char UnUse2[4];

	unsigned char Name_diffuseMap[60];
	_TAM_Mat_Texture * Tex_diffuse;
	unsigned char Name_specularMap[60];
	_TAM_Mat_Texture * Tex_specular;
	unsigned char Name_NormalMap[60];
	_TAM_Mat_Texture * Tex_Normal;
	unsigned char Name_Refract[60];
	_TAM_Mat_Texture * Tex_Refract;
	unsigned char Name_BumpMAP[60];
	_TAM_Mat_Texture * Tex_BumpMAP;
};
struct _TAM_Bone_Frame//帧
{
	unsigned char UnUse1[8];
	_TAM_Bone_Frame * PreviousFrameAddress;
	unsigned int FrameTime;
	__m128 FrameData;
};
struct _TAM_Bone_Frame_Head//动画
{
	unsigned int TotalFrameNum;//实际帧数
	unsigned int MAXFrameNum;
	_TAM_Bone_Frame ** FramesAddress;//TotalFrameNum和MAXFrameNum一般情况下是不同的，为了在读取速度和储存空间之间折中，桢地址数量等于MAXFrameNum。如果当前桢没有数据，那么当前桢的地址实际上是指向下一个有数据的帧
};
struct _TAM_Bone
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int BoneID;
	unsigned int NextBoneID;//0xc同级boneID ,也就是同一个父节点的下一个bone，如果与BoneID相等或为0则表示同一个父节点没有下一个bone了

	unsigned int ChildBoneID;
	unsigned int ParentBoneID;
	unsigned char UnUse1[8];

	__m128 FirstTranslate;

	__m128 FirstRotate;

	__m128 FirstScale;

	unsigned int FrameChunkNum;
	_TAM_Bone_Frame_Head * FramesHeadAddress[3];//_TAM_Bone_Frame_Type
	//_TAM_Bone_Frame_Head * TranslateFramesHeadAddress;
	//_TAM_Bone_Frame_Head * RotateFramesHeadAddress;
	//_TAM_Bone_Frame_Head * ScaleFramesHeadAddress;

	unsigned char BoneName[32];

	unsigned char BoneSet[16];

	__m128 LocMat[4];
};
struct _TAM_Bone_Head
{
	//unsigned int BoneNum;
	_TAM_Bone** BoneAddress;
};
struct _TAM_Light_Frame
{
	_TAM_Light_Frame * PreviousFrameAddress;
	unsigned int FrameTime;
	unsigned int FrameData;
};
struct _TAM_Light_Frame_Head
{
	unsigned int TotalFrameNum;//实际帧数
	unsigned int MAXFrameNum;
	_TAM_Light_Frame ** FramesAddress;
};
struct _TAM_Light
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int LightID;
	unsigned char UnUse1[4];

	unsigned int LightType;
	unsigned char LightColor[4];
	int LightConstant;
	float LightCutOff;

	unsigned int BoneID;
	unsigned int TGTBoneID;
	unsigned char UnUse2[4];
	unsigned char UnUse3[4];

	unsigned char LightName[32];
	_TAM_Light_Frame_Head * FramesHeadAddress[3];//_TAM_Light_Frame_Type
	//_TAM_Light_Frame_Head * LightColorFramesHeadAddress;
	//_TAM_Light_Frame_Head * LightConstantFramesHeadAddress;
	//_TAM_Light_Frame_Head * LightCutOffFramesHeadAddress;
	unsigned char UnUse4[4];

	__m128 FirstTranslate;

	__m128 FirstRotate;
};
struct _TAM_Light_Head
{
	//unsigned int LightNum;
	_TAM_Light ** LightAddress;
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

	__m128 FirstTranslate;

	__m128 FirstRotate;
};
struct _TAM_FileHead
{
	unsigned char HeadName[4];
	unsigned int FileSize;
	unsigned int TAMVer;
	unsigned char UnUse2[4];

	unsigned int ChunkNum;//0x10地址表数量
	_TAM_Mesh ** MeshHeadAddress;
	_TAM_Mat * MatsAddress;
	_TAM_Bone ** BoneHeadAddress;

	_TAM_Light ** LightHeadAddress;
	_TAM_Camera * CameraAddress;
	unsigned int MeshNum;
	unsigned int MatNum;

	unsigned int BoneNum;
	unsigned int LightNum;
	unsigned int CameraNum;
	unsigned int RootBoneID;

	float BoxMin[4];

	float BoxMax[4];
};
struct tMeshVBOID
{
	unsigned int VerticeID;
	unsigned int NormalID;
	unsigned int TexCoordID;
	unsigned int FaceID;
	unsigned int VAOID;
	unsigned int BoneIDsID;
	unsigned int BoneWGsID;

};
class CTopAceModel
{
public:
	CTopAceModel(void);
	~CTopAceModel(void);
	bool ReadTAMFile(char * FileName);
	bool ReadTAMFile(wchar_t * FileName);
	_TAM_FileHead * pTAM_FileHead;
	_TAM_Mesh * TAM_Get_Mesh(unsigned int MeshID);
	_TAM_Bone * TAM_Get_Bone(unsigned int BoneID);
	_TAM_Bone * TAM_Get_Bone_Fast1(unsigned int BoneID);
	_TAM_Light * TAM_Get_Light(unsigned int LightID);

	_TAM_Bone_Frame * TAM_Get_Bone_Frame(unsigned int BoneFrameID,unsigned int BoneID,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type);
	_TAM_Bone_Frame * TAM_Get_Bone_Frame(unsigned int BoneFrameID,_TAM_Bone * TAM_Bone,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type);

	_TAM_Light_Frame * TAM_Get_Light_Frame(unsigned int LightFrameID,unsigned int LightID,_TAM_Light_Frame_Type TAM_Light_Frame_Type);
	_TAM_Light_Frame * TAM_Get_Light_Frame(unsigned int LightFrameID,_TAM_Light * TAM_Light,_TAM_Light_Frame_Type TAM_Light_Frame_Type);

	_TAM_Bone * TAM_Get_NextBone(unsigned int BoneID);
	_TAM_Bone * TAM_Get_NextBone(_TAM_Bone * TAM_Bone);

	_TAM_Bone * TAM_Get_ChildBone(unsigned int BoneID);
	_TAM_Bone * TAM_Get_ChildBone(_TAM_Bone * TAM_Bone);

	_TAM_File_States TAM_File_States;
	
	_MaterialData MaterialDataTAMTMP;
	unsigned char * TAM_FileData;
	bool InitTAMFile(unsigned char * TAM_FileData_IN);
	bool InitTAMMesh(_TAM_Mesh * TAM_MeshData_IN);
	bool InitTAMMat(_TAM_Mat * TAM_MatData_IN);
	bool InitTAMBone(_TAM_Bone * TAM_BoneData_IN);
	bool InitTAMLight(_TAM_Light * TAM_LightData_IN);
	bool InitTAMCamera(_TAM_Camera * TAM_CameraData_IN);
	bool LoadToVRAM(void);
	bool LoadMeshToVRAM(_TAM_Mesh * TAM_Mesh);
	void DeleteVRAM(void);
	void DeleteMeshVRAM(_TAM_Mesh * TAM_Mesh);
	void Draw(void);
	void DrawRAM(void);
	bool DrawMeshRigid(_TAM_Mesh * TAM_Mesh);
	bool DrawRAMMeshRigid(_TAM_Mesh * TAM_Mesh);
	bool DrawRAMMeshFiexible(_TAM_Mesh * TAM_Mesh);
	bool SuppotVBO;
	tMeshVBOID * MeshVBOIDs;
	bool isVRAM;
	void GetBoneMatrix(float Frame,unsigned int BoneID);
	void InitTAMBoneMatrixs(void);
	void DeinitTAMBoneMatrixs(void);
	void DeinitTAMMesh();
	__m128 * BoneMatrixs;

	_TAM_Bone_Frame ** TAM_Bone_FramesTMP;
	_TAM_Light_Frame ** TAM_Light_FramesTMP;
	bool GetlinearBoneFrameData(_TAM_Bone_Frame * TAM_Bone_FrameFront,__m128 * linearFrameData,float Frame);
	bool GetSlerpBoneFrameData(_TAM_Bone_Frame * TAM_Bone_FrameFront,__m128 * SlerpFrameData,float Frame);
	__m128 GetBoneMatrix_BonePos;
	__m128 GetBoneMatrix_BoneRot;
	__m128 GetBoneMatrix_BoneSca;
	__m128 NodeBoneMatrixTMP[4];
	__m128 NodeBoneMatrixTMPFirst[4];
	double NodeBoneMatrixTMPD[16];
	_TAM_Bone * TAM_Bone_Tmp;
	void GetNodeMatrixs(__m128 * NodeMatrix,__m128 * NodeFirstMatrix,_TAM_Bone * TAM_Bone);
	__m128 TAM_IdentityMatrix[4];
	__m128 DrawRAMMeshFiexibleTMPvec;
	__m128 DrawRAMMeshFiexibleTMPvec2;
	__m128 DrawRAMMeshFiexibleTMPnol;
	__m128 DrawRAMMeshFiexibleTMPnol2;
	_TAM_vecBoneWeightsAndBoneIDs TAM_vecBoneWeightsAndBoneIDsTMP;
	__m128 * pDrawRAMMeshFiexibleDSTTMP;
	
	void FrameTAMBoneMatrixs(float Frame);
	wchar_t * FilePath;
	float MatTmp[4];

	float * MatInt8toFloat(unsigned char * Input)
	{
		MatTmp[0]=Input[0];
		MatTmp[1]=Input[1];
		MatTmp[2]=Input[2];
		MatTmp[3]=Input[3];
		return &MatTmp[0];
	}
	void SetDrawMeshMat(_TAM_Mat * TAM_Mat);
	void DeinitTAMMatAll();
	void DeinitTAMMat(_TAM_Mat * TAM_MatData_IN);
	void LoadMatTexsToVRAM(void);
	CTexManager TexManager;
	bool DrawTranslucent;
	bool GetCamMatrix(unsigned int CamID, __m128 * CamMatrix);
	void SetLight(unsigned int LightID,unsigned int LightBase=0);
	void Draw(bool Translucent,bool Fiexible);
	void CreatVAO(tMeshVBOID * MeshVBOID);
	bool MeshUseAlphaTMP;
	bool IsDrawWithAlpha(_TAM_Mesh * TAM_Mesh);
	unsigned int TAMDrawMode;
	unsigned int testMAXFrame;
};
#endif