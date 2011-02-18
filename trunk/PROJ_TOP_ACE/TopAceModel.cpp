#include "TopAceModel.h"//文件头

CTopAceModel::CTopAceModel(void)
:TAM_File_States(_TAM_File_States_NoRead)
, TAM_FileData(NULL)
, pTAM_FileHead(NULL)
, SuppotVBO(false)
, MeshVBOIDs(NULL)
, isVRAM(false)
, BoneMatrixs(NULL)
, TAM_Bone_FramesTMP(NULL)
, TAM_Light_FramesTMP(NULL)
, TAM_Bone_Tmp(NULL)
, FilePath(NULL)
, TAMDrawMode(GL_TRIANGLES)
, testMAXFrame(0)
{
	
}

CTopAceModel::~CTopAceModel(void)
{
	DeleteVRAM();
	DeinitTAMMatAll();
	DeinitTAMBoneMatrixs();
	DeinitTAMMesh();
	if(TAM_FileData)
		_aligned_free(TAM_FileData);
	TAM_FileData = NULL;
	pTAM_FileHead = NULL;

	if(FilePath)
		delete[] FilePath;
	FilePath=NULL;
}

bool CTopAceModel::ReadTAMFile(char * FileName)
{
	if(TAM_File_States==_TAM_File_States_ReadOK)
		return false;
	if(!FileName)
		return false;
	int dwNum=MultiByteToWideChar(CP_ACP,0,FileName,-1,NULL,0);
	wchar_t * FileNameWTmp=new wchar_t[dwNum];
	MultiByteToWideChar(CP_ACP,0,FileName,-1,FileNameWTmp,dwNum);
	ReadTAMFile(FileNameWTmp);
	delete[] FileNameWTmp;
	/*HANDLE   hFile;     
      
	hFile   =   CreateFileA(FileName,                 
                                  GENERIC_READ,                 
                                  FILE_SHARE_READ,                     
                                  NULL,                                  
                                  OPEN_EXISTING,                        
                                  FILE_ATTRIBUTE_NORMAL,       
                                  NULL); 
	if   (hFile   ==   INVALID_HANDLE_VALUE)  
	{
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_NoFile;
		TAM_FileData = NULL;
		return false;
	}

	_TAM_FileHead TAM_FileHeadTMP;
	DWORD Readedsize=0;
	BOOL ReadStates=ReadFile(hFile,&TAM_FileHeadTMP,sizeof(TAM_FileHeadTMP),&Readedsize,NULL);
	if(!ReadStates)
	{
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_NoFile;
		TAM_FileData = NULL;
		return false;
	}
	if(TAM_FileHeadTMP.FileSize<sizeof(TAM_FileHeadTMP))
	{
		TAM_File_States=_TAM_File_States_ReadFail;
		TAM_FileData = NULL;
		CloseHandle(hFile);
		return false;
	}
	TAM_FileData = (unsigned char * ) _aligned_malloc (TAM_FileHeadTMP.FileSize,16);

	Readedsize = 0;
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	ReadStates=ReadFile(hFile,TAM_FileData,TAM_FileHeadTMP.FileSize,&Readedsize,NULL);
	if(!ReadStates)
	{
		DWORD dwError = GetLastError();
		_aligned_free(TAM_FileData);
		TAM_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}
	if(!InitTAMFile(TAM_FileData))
	{
		_aligned_free(TAM_FileData);
		TAM_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}


	CloseHandle(hFile);*/
	return true;
}
bool CTopAceModel::ReadTAMFile(wchar_t * FileName)
{
	FilePath=new wchar_t[wcslen(FileName)+1];
	wcscpy(FilePath,FileName);
	HANDLE   hFile;     
      
	hFile   =   CreateFileW(FileName,                       //   open   MYFILE.TXT     
                                  GENERIC_READ,                             //   open   for   reading     
                                  FILE_SHARE_READ,                       //   share   for   reading     
                                  NULL,                                             //   no   security     
                                  OPEN_EXISTING,                           //   existing   file   only     
                                  FILE_ATTRIBUTE_NORMAL,           //   normal   file     
                                  NULL);     
	if   (hFile   ==   INVALID_HANDLE_VALUE)  
	{
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_NoFile;
		return false;
	}

	_TAM_FileHead TAM_FileHeadTMP;
	DWORD Readedsize=0;
	BOOL ReadStates=ReadFile(hFile,&TAM_FileHeadTMP,sizeof(TAM_FileHeadTMP),&Readedsize,NULL);
	if(!ReadStates)
	{
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_NoFile;
		TAM_FileData = NULL;
		return false;
	}
	if(TAM_FileHeadTMP.FileSize<sizeof(TAM_FileHeadTMP))
	{
		TAM_File_States=_TAM_File_States_ReadFail;
		TAM_FileData = NULL;
		CloseHandle(hFile);
		return false;
	}
	/*if(TAM_FileHeadTMP.TAMVer!=_TAM_VERSION)
	{
		::MessageBoxA(HWND_DESKTOP,"Load TAM File Error","TAM File Ver Error",MB_OK | MB_ICONEXCLAMATION);
		TAM_File_States=_TAM_File_States_ErrorVer;
		TAM_FileData = NULL;
		CloseHandle(hFile);
		return false;
	}*/
	TAM_FileData = (unsigned char * ) _aligned_malloc (TAM_FileHeadTMP.FileSize,16);

	Readedsize = 0;
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	ReadStates=ReadFile(hFile,TAM_FileData,TAM_FileHeadTMP.FileSize,&Readedsize,NULL);
	if(!ReadStates)
	{
		DWORD dwError = GetLastError();
		_aligned_free(TAM_FileData);
		TAM_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}
	if(!InitTAMFile(TAM_FileData))
	{
		_aligned_free(TAM_FileData);
		TAM_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}


	CloseHandle(hFile);
	return true;
}
bool CTopAceModel::InitTAMFile(unsigned char * TAM_FileData_IN)
{
	if(!TAM_FileData_IN)
		return false;

	_TAM_FileHead  * TAM_FileHead_IN=(_TAM_FileHead*)TAM_FileData_IN;
	pTAM_FileHead=TAM_FileHead_IN;

	if((unsigned int(TAM_FileHead_IN->MeshHeadAddress)!=0xFFFFFFFF)&&(TAM_FileHead_IN->MeshNum)>0)
	{
		TAM_FileHead_IN->MeshHeadAddress=(_TAM_Mesh ** )&TAM_FileData_IN[(int)TAM_FileHead_IN->MeshHeadAddress];
		for (unsigned int i=0;i<TAM_FileHead_IN->MeshNum;i++)
		{
			TAM_FileHead_IN->MeshHeadAddress[i]=(_TAM_Mesh *)(int(TAM_FileHead_IN->MeshHeadAddress[i])+int(TAM_FileData_IN));
			InitTAMMesh(TAM_FileHead_IN->MeshHeadAddress[i]);
		}
	}

	if((unsigned int(TAM_FileHead_IN->MatsAddress)!=0xFFFFFFFF)&&(TAM_FileHead_IN->MatNum>0))
	{
		TexManager.InitTexArray(TAM_FileHead_IN->MatNum*4,FilePath);
		TAM_FileHead_IN->MatsAddress=(_TAM_Mat * )&TAM_FileData_IN[(int)TAM_FileHead_IN->MatsAddress];
		for (unsigned int i=0;i<TAM_FileHead_IN->MatNum;i++)
		{
			InitTAMMat(&(TAM_FileHead_IN->MatsAddress[i]));
		}
	}

	if((unsigned int(TAM_FileHead_IN->BoneHeadAddress)!=0xFFFFFFFF)&&(TAM_FileHead_IN->BoneNum>0))
	{
		TAM_FileHead_IN->BoneHeadAddress=(_TAM_Bone ** )&TAM_FileData_IN[(int)TAM_FileHead_IN->BoneHeadAddress];
		for (unsigned int i=0;i<TAM_FileHead_IN->BoneNum;i++)
		{
			TAM_FileHead_IN->BoneHeadAddress[i]=(_TAM_Bone *)(int(TAM_FileHead_IN->BoneHeadAddress[i])+int(TAM_FileData_IN));
			InitTAMBone(TAM_FileHead_IN->BoneHeadAddress[i]);
		}
	}

	if((unsigned int(TAM_FileHead_IN->LightHeadAddress)!=0xFFFFFFFF)&&(TAM_FileHead_IN->LightNum>0))
	{
		TAM_FileHead_IN->LightHeadAddress=(_TAM_Light ** )&TAM_FileData_IN[(int)TAM_FileHead_IN->LightHeadAddress];
		for (unsigned int i=0;i<TAM_FileHead_IN->LightNum;i++)
		{
			TAM_FileHead_IN->LightHeadAddress[i]=(_TAM_Light *)(int(TAM_FileHead_IN->LightHeadAddress[i])+int(TAM_FileData_IN));
			InitTAMLight(TAM_FileHead_IN->LightHeadAddress[i]);
		}
	}

	if((unsigned int(TAM_FileHead_IN->CameraAddress)!=0xFFFFFFFF)&&(TAM_FileHead_IN->CameraNum>0))
	{
		TAM_FileHead_IN->CameraAddress=(_TAM_Camera * )&TAM_FileData_IN[(int)TAM_FileHead_IN->CameraAddress];
		for (unsigned int i=0;i<TAM_FileHead_IN->CameraNum;i++)
		{
			InitTAMCamera(&(TAM_FileHead_IN->CameraAddress[i]));
		}
	}
	
	InitTAMBoneMatrixs();
	TAM_File_States = _TAM_File_States_ReadOK;
	return true;
}
bool CTopAceModel::InitTAMMesh(_TAM_Mesh * TAM_MeshData_IN)
{
	if(!((TAM_MeshData_IN->FaceNum>0)&&(TAM_MeshData_IN->vecNum>0)))
		return false;
	TAM_MeshData_IN->vertices=(__m128 *)&TAM_FileData[(int)TAM_MeshData_IN->vertices];
	TAM_MeshData_IN->Normals=(__m128 *)&TAM_FileData[(int)TAM_MeshData_IN->Normals];
	TAM_MeshData_IN->texcos=(float *)&TAM_FileData[(int)TAM_MeshData_IN->texcos];
	TAM_MeshData_IN->Faces=(unsigned int *)&TAM_FileData[(int)TAM_MeshData_IN->Faces];
	TAM_MeshData_IN->vecBoneWeightsAndBoneIDs=(_TAM_vecBoneWeightsAndBoneIDs *)&TAM_FileData[(int)TAM_MeshData_IN->vecBoneWeightsAndBoneIDs];

	if(TAM_MeshData_IN->IsFiexible)
		TAM_MeshData_IN->UserPTR=_aligned_malloc(sizeof(__m128)*TAM_MeshData_IN->vecNum*2,16);
	else
		TAM_MeshData_IN->UserPTR=NULL;
	return true;
}
void CTopAceModel::DeinitTAMMesh()
{
	_TAM_Mesh * pTAM_Mesh_TMP=NULL;
	if(!pTAM_FileHead)
		return;
	for(unsigned int i=0;i<pTAM_FileHead->MeshNum;i++)
	{
		pTAM_Mesh_TMP=pTAM_FileHead->MeshHeadAddress[i];
		if(pTAM_Mesh_TMP->UserPTR)
			_aligned_free(pTAM_Mesh_TMP->UserPTR);
		pTAM_Mesh_TMP->UserPTR=NULL;
	}
}

void CTopAceModel::LoadMatTexsToVRAM(void)
{
	if((unsigned int(pTAM_FileHead->MatsAddress)==0xFFFFFFFF)||(pTAM_FileHead->MatNum==0))
		return;
	TexManager.LoadToVRAM();
	for(unsigned int i=0;i<pTAM_FileHead->MatNum;i++)
	{
		if(!pTAM_FileHead->MatsAddress[i].Tex_diffuse)
			continue;
		
		_TAM_Mat_Texture * TAM_Mat_Texture_Tmp=pTAM_FileHead->MatsAddress[i].Tex_diffuse;
		TexManager.GetTexSet(
			TAM_Mat_Texture_Tmp->TexManagerID,
			&(TAM_Mat_Texture_Tmp->TexID),
			&(TAM_Mat_Texture_Tmp->TexType),
			&(TAM_Mat_Texture_Tmp->UseAlpha)
			);
	}
}
bool CTopAceModel::InitTAMMat(_TAM_Mat * TAM_MatData_IN)
{
	if(!TAM_MatData_IN)
		return false;
	TAM_MatData_IN->ambient[3]=1.0f;
	TAM_MatData_IN->diffuse[3]=1.0f;
	TAM_MatData_IN->self_illum[3]=1.0f;
	TAM_MatData_IN->specular[3]=1.0f;
	TAM_MatData_IN->specularLv=max(5.0,min(TAM_MatData_IN->specularLv,128));
	if(TAM_MatData_IN->Name_diffuseMap[0]!=0)
	{
		TAM_MatData_IN->Tex_diffuse=new _TAM_Mat_Texture;
		TAM_MatData_IN->Tex_diffuse->TexManagerID=TexManager.AddTex((char*)&(TAM_MatData_IN->Name_diffuseMap[0]));
	}
	else
		TAM_MatData_IN->Tex_diffuse=NULL;
	if(TAM_MatData_IN->Name_specularMap[0]!=0)
	{
		TAM_MatData_IN->Tex_specular=new _TAM_Mat_Texture;
	}
	else
		TAM_MatData_IN->Tex_specular=NULL;
	if(TAM_MatData_IN->Name_NormalMap[0]!=0)
	{
		TAM_MatData_IN->Tex_Normal=new _TAM_Mat_Texture;
	}
	else
		TAM_MatData_IN->Tex_Normal=NULL;
	if(TAM_MatData_IN->Name_Refract[0]!=0)
	{
		TAM_MatData_IN->Tex_Refract=new _TAM_Mat_Texture;
	}
	else
		TAM_MatData_IN->Tex_Refract=NULL;

	return true;
}
void CTopAceModel::DeinitTAMMat(_TAM_Mat * TAM_MatData_IN)
{
	if(!TAM_MatData_IN)
		return;
	if(TAM_MatData_IN->Tex_diffuse)
		delete TAM_MatData_IN->Tex_diffuse;
	if(TAM_MatData_IN->Tex_specular)
		delete TAM_MatData_IN->Tex_specular;
	if(TAM_MatData_IN->Tex_Normal)
		delete TAM_MatData_IN->Tex_Normal;
	if(TAM_MatData_IN->Tex_Refract)
		delete TAM_MatData_IN->Tex_Refract;

	TAM_MatData_IN->Tex_diffuse=NULL;
	TAM_MatData_IN->Tex_specular=NULL;
	TAM_MatData_IN->Tex_Normal=NULL;
	TAM_MatData_IN->Tex_Refract=NULL;
}
void CTopAceModel::DeinitTAMMatAll()
{
	if(!pTAM_FileHead)
		return ;
	if((unsigned int(pTAM_FileHead->MatsAddress)!=0xFFFFFFFF)&&(pTAM_FileHead->MatNum>0))
	{
		for (unsigned int i=0;i<pTAM_FileHead->MatNum;i++)
		{
			DeinitTAMMat(&(pTAM_FileHead->MatsAddress[i]));
		}
	}

}
bool CTopAceModel::InitTAMBone(_TAM_Bone * TAM_BoneData_IN)
{
	if(!TAM_BoneData_IN)
		return false;
	for(unsigned int i=0;i<TAM_BoneData_IN->FrameChunkNum;i++)
	{
		if(unsigned int(TAM_BoneData_IN->FramesHeadAddress[i])==0xFFFFFFFF)
			continue;

		TAM_BoneData_IN->FramesHeadAddress[i]=(_TAM_Bone_Frame_Head *)&TAM_FileData[int(TAM_BoneData_IN->FramesHeadAddress[i])];
		if(TAM_BoneData_IN->FramesHeadAddress[i]->TotalFrameNum>0)
		{
			testMAXFrame=max(TAM_BoneData_IN->FramesHeadAddress[i]->MAXFrameNum,testMAXFrame);
			_TAM_Bone_Frame ** TAM_Bone_Frames=(_TAM_Bone_Frame **) &(TAM_BoneData_IN->FramesHeadAddress[i]->FramesAddress);
			for(unsigned int j=0;j<=TAM_BoneData_IN->FramesHeadAddress[i]->MAXFrameNum;j++)
			{
				TAM_Bone_Frames[j]=(_TAM_Bone_Frame *)&TAM_FileData[int(TAM_Bone_Frames[j])];
			}
			_TAM_Bone_Frame * pTAM_Bone_FrameTMP=TAM_Bone_Frames[TAM_BoneData_IN->FramesHeadAddress[i]->MAXFrameNum];
			while(unsigned int(pTAM_Bone_FrameTMP->PreviousFrameAddress)!=0xFFFFFFFF)
			{
				pTAM_Bone_FrameTMP->PreviousFrameAddress=(_TAM_Bone_Frame *)&TAM_FileData[int(pTAM_Bone_FrameTMP->PreviousFrameAddress)];
				pTAM_Bone_FrameTMP=pTAM_Bone_FrameTMP->PreviousFrameAddress;
			}
			if(unsigned int(pTAM_Bone_FrameTMP->PreviousFrameAddress)==0xFFFFFFFF)
			{
				pTAM_Bone_FrameTMP->PreviousFrameAddress=pTAM_Bone_FrameTMP;
			}
		}
	}
	
	return true;
}
void CTopAceModel::InitTAMBoneMatrixs()
{
	if(BoneMatrixs)
		return;
	if(pTAM_FileHead->BoneNum<=0)
		return;
	BoneMatrixs=(__m128 *) _aligned_malloc(4*(pTAM_FileHead->BoneNum+1)*sizeof(__m128),16);

	Easy_matrix_identity(NodeBoneMatrixTMP);
	Easy_matrix_identity(TAM_IdentityMatrix);
	Easy_matrix_identity(BoneMatrixs,pTAM_FileHead->BoneNum+1);
	for(unsigned int i=0;i<pTAM_FileHead->BoneNum;i++)
	{
		TAM_Bone_Tmp=pTAM_FileHead->BoneHeadAddress[i];
		Easy_matrix_transpose(TAM_Bone_Tmp->LocMat);
	}

}
void CTopAceModel::FrameTAMBoneMatrixs(float Frame)
{
	if(!BoneMatrixs)
		return;
	if(pTAM_FileHead->BoneNum<=0)
		return;
	for(unsigned int i=0;i<pTAM_FileHead->BoneNum;i++)
	{
		TAM_Bone_Tmp=pTAM_FileHead->BoneHeadAddress[i];
		GetBoneMatrix(Frame,TAM_Bone_Tmp->BoneID);
	}
	for(TAM_Bone_Tmp=TAM_Get_Bone_Fast1(pTAM_FileHead->RootBoneID);TAM_Bone_Tmp!=NULL;TAM_Bone_Tmp=TAM_Get_Bone_Fast1(TAM_Bone_Tmp->NextBoneID))
	{
		GetNodeMatrixs(TAM_IdentityMatrix,TAM_IdentityMatrix,TAM_Bone_Tmp);
	}
}
void CTopAceModel::GetNodeMatrixs(__m128 * NodeMatrix,__m128 * NodeFirstMatrix,_TAM_Bone * TAM_Bone)
{
	Easy_matrix_mult(NodeBoneMatrixTMPFirst,TAM_Bone->LocMat,NodeFirstMatrix);
	Easy_matrix_mult(NodeBoneMatrixTMP,NodeMatrix,&BoneMatrixs[TAM_Bone->BoneID*4]);
	Easy_matrix_mult(&BoneMatrixs[TAM_Bone->BoneID*4],NodeBoneMatrixTMP,NodeBoneMatrixTMPFirst);
	__m128 NodeBoneMatrixRec[4];
	__m128 NodeBoneMatrixRecFirst[4];
	Easy_matrix_copy(NodeBoneMatrixRec,NodeBoneMatrixTMP);
	Easy_matrix_copy(NodeBoneMatrixRecFirst,NodeBoneMatrixTMPFirst);
	for(_TAM_Bone * TAM_Bone_Child=TAM_Get_Bone_Fast1(TAM_Bone->ChildBoneID);TAM_Bone_Child!=NULL;TAM_Bone_Child=TAM_Get_Bone_Fast1(TAM_Bone_Child->NextBoneID))
		GetNodeMatrixs(NodeBoneMatrixRec,NodeBoneMatrixRecFirst,TAM_Bone_Child);
	float testmat[4][4];
	Easy_matrix_copy(testmat,&BoneMatrixs[TAM_Bone->BoneID*4]);
	Easy_matrix_copy(testmat,&BoneMatrixs[TAM_Bone->BoneID*4]);
}

void CTopAceModel::DeinitTAMBoneMatrixs()
{
	if(BoneMatrixs)
	{
		_aligned_free(BoneMatrixs);
		BoneMatrixs=NULL;
	}
}
bool CTopAceModel::InitTAMLight(_TAM_Light * TAM_LightData_IN)
{
	for(unsigned int i=0;i<3;i++)
	{
		if(unsigned int(TAM_LightData_IN->FramesHeadAddress[i])==0xFFFFFFFF)
			continue;
		TAM_LightData_IN->FramesHeadAddress[i]=(_TAM_Light_Frame_Head *)&TAM_FileData[int(TAM_LightData_IN->FramesHeadAddress[i])];
		if(TAM_LightData_IN->FramesHeadAddress[i]->MAXFrameNum>1)
		{
			_TAM_Light_Frame ** TAM_Light_Frames=(_TAM_Light_Frame **)&(TAM_LightData_IN->FramesHeadAddress[i]->FramesAddress);
			for(unsigned int j=0;j<=TAM_LightData_IN->FramesHeadAddress[i]->MAXFrameNum;j++)
				TAM_Light_Frames[j]=(_TAM_Light_Frame *)&TAM_FileData[int(TAM_Light_Frames[j])];
			_TAM_Light_Frame * pTAM_Light_FrameTMP=TAM_Light_Frames[TAM_LightData_IN->FramesHeadAddress[i]->MAXFrameNum];
			while(pTAM_Light_FrameTMP->FrameTime!=0)
			{
				pTAM_Light_FrameTMP->PreviousFrameAddress=(_TAM_Light_Frame *)&TAM_FileData[int(pTAM_Light_FrameTMP->PreviousFrameAddress)];
				pTAM_Light_FrameTMP=pTAM_Light_FrameTMP->PreviousFrameAddress;
			}
			if(pTAM_Light_FrameTMP->FrameTime==0)
			{
				pTAM_Light_FrameTMP->PreviousFrameAddress=pTAM_Light_FrameTMP;
			}
		}
	}
	return true;
}
bool CTopAceModel::InitTAMCamera(_TAM_Camera * TAM_CameraData_IN)
{
	return true;
}
_TAM_Mesh * CTopAceModel::TAM_Get_Mesh(unsigned int MeshID)
{
	if(!MeshID)
		return NULL;
	if(!pTAM_FileHead)
		return NULL;
	if(unsigned int(pTAM_FileHead->MeshHeadAddress)==0xFFFFFFFF)
		return NULL;
	if(pTAM_FileHead->MeshNum<=0)
		return NULL;
	if(pTAM_FileHead->MeshNum<=(MeshID-1))
		return NULL;

	return pTAM_FileHead->MeshHeadAddress[(MeshID-1)];
}

_TAM_Bone * CTopAceModel::TAM_Get_Bone(unsigned int BoneID)
{
	if(!BoneID)
		return NULL;
	if(!pTAM_FileHead)
		return NULL;
	if(unsigned int(pTAM_FileHead->BoneHeadAddress)==0xFFFFFFFF)
		return NULL;
	if(pTAM_FileHead->BoneNum<=0)
		return NULL;
	if(pTAM_FileHead->BoneNum<=(BoneID-1))
		return NULL;

	return pTAM_FileHead->BoneHeadAddress[(BoneID-1)];
}
_TAM_Bone * CTopAceModel::TAM_Get_Bone_Fast1(unsigned int BoneID)
{
	if(!BoneID)
		return NULL;
	return pTAM_FileHead->BoneHeadAddress[(BoneID-1)];
}
_TAM_Light * CTopAceModel::TAM_Get_Light(unsigned int LightID)
{
	if(!LightID)
		return NULL;
	if(!pTAM_FileHead)
		return NULL;
	if(unsigned int(pTAM_FileHead->LightHeadAddress)==0xFFFFFFFF)
		return NULL;
	if(pTAM_FileHead->LightNum<=0)
		return NULL;
	if(pTAM_FileHead->LightNum<=(LightID-1))
		return NULL;

	return pTAM_FileHead->LightHeadAddress[(LightID-1)];
}

_TAM_Bone_Frame * CTopAceModel::TAM_Get_Bone_Frame(unsigned int BoneFrameID,unsigned int BoneID,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type)
{
	return TAM_Get_Bone_Frame(BoneFrameID,TAM_Get_Bone(BoneID),TAM_Bone_Frame_Type);
}
_TAM_Bone_Frame * CTopAceModel::TAM_Get_Bone_Frame(unsigned int BoneFrameID,_TAM_Bone * TAM_Bone,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type)
{
	if(!pTAM_FileHead)
		return NULL;
	if(unsigned int(pTAM_FileHead->BoneHeadAddress)==0xFFFFFFFF)
		return NULL;
	if(pTAM_FileHead->BoneNum<=0)
		return NULL;
	if(!TAM_Bone)
		return NULL;

	if(!TAM_Bone->FramesHeadAddress[TAM_Bone_Frame_Type])
		return NULL;
	if(unsigned int(TAM_Bone->FramesHeadAddress[TAM_Bone_Frame_Type])==0xFFFFFFFF)
		return NULL;
	TAM_Bone_FramesTMP=(_TAM_Bone_Frame **) &(TAM_Bone->FramesHeadAddress[TAM_Bone_Frame_Type]->FramesAddress);
	if(!TAM_Bone_FramesTMP)
		return NULL;
	return TAM_Bone_FramesTMP[min(TAM_Bone->FramesHeadAddress[TAM_Bone_Frame_Type]->MAXFrameNum,BoneFrameID)];
}

_TAM_Light_Frame * CTopAceModel::TAM_Get_Light_Frame(unsigned int LightFrameID,unsigned int LightID,_TAM_Light_Frame_Type TAM_Light_Frame_Type)
{
	return TAM_Get_Light_Frame(LightFrameID,TAM_Get_Light(LightID),TAM_Light_Frame_Type);
}
_TAM_Light_Frame * CTopAceModel::TAM_Get_Light_Frame(unsigned int LightFrameID,_TAM_Light * TAM_Light,_TAM_Light_Frame_Type TAM_Light_Frame_Type)
{
	if(!pTAM_FileHead)
		return NULL;
	if(unsigned int(pTAM_FileHead->LightHeadAddress)==0xFFFFFFFF)
		return NULL;
	if(pTAM_FileHead->LightNum<=0)
		return NULL;
	if(!TAM_Light)
		return NULL;

	TAM_Light_FramesTMP=(_TAM_Light_Frame **) &(TAM_Light->FramesHeadAddress[TAM_Light_Frame_Type]->FramesAddress);
	return TAM_Light_FramesTMP[min(TAM_Light->FramesHeadAddress[TAM_Light_Frame_Type]->MAXFrameNum,LightFrameID)];
}
_TAM_Bone * CTopAceModel::TAM_Get_NextBone(unsigned int BoneID)
{
	return TAM_Get_NextBone(TAM_Get_Bone(BoneID));
}
_TAM_Bone * CTopAceModel::TAM_Get_NextBone(_TAM_Bone * TAM_Bone)
{
	if(TAM_Bone)
		return TAM_Get_Bone(TAM_Bone->NextBoneID);
	else
		return NULL;
}

_TAM_Bone * CTopAceModel::TAM_Get_ChildBone(unsigned int BoneID)
{
	return TAM_Get_ChildBone(TAM_Get_Bone(BoneID));
}
_TAM_Bone * CTopAceModel::TAM_Get_ChildBone(_TAM_Bone * TAM_Bone)
{
	if(TAM_Bone)
		return TAM_Get_Bone(TAM_Bone->ChildBoneID);
	else
		return NULL;
}
bool CTopAceModel::LoadToVRAM(void)
{
	if(!pTAM_FileHead)
		return false;
	if(unsigned int(pTAM_FileHead->MeshHeadAddress)==0xFFFFFFFF)
		return false;
	if(pTAM_FileHead->MeshNum<=0)
		return false;
	if (glewIsSupported("GL_ARB_vertex_buffer_object"))
		SuppotVBO=true;
	else
		SuppotVBO=false;
	if(!SuppotVBO)
		return false;

	MeshVBOIDs= new tMeshVBOID[pTAM_FileHead->MeshNum+2];
	for (unsigned int i=0;i<pTAM_FileHead->MeshNum+2;i++)
	{
		MeshVBOIDs[i].FaceID=0;
		MeshVBOIDs[i].NormalID=0;
		MeshVBOIDs[i].TexCoordID=0;
		MeshVBOIDs[i].ColorID=0;
		MeshVBOIDs[i].VerticeID=0;
		MeshVBOIDs[i].VAOID=0;
	}
	for (unsigned int i=0;i<pTAM_FileHead->MeshNum;i++)
		LoadMeshToVRAM(pTAM_FileHead->MeshHeadAddress[i]);
	glBindVertexArray(0);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
	LoadMatTexsToVRAM();

	isVRAM=true;
	return true;
}
void CTopAceModel::CreatVAO(tMeshVBOID * MeshVBOID)
{
	if(!MeshVBOID)
		return;
	glGenVertexArrays(1,&MeshVBOID->VAOID);
	glBindVertexArray(MeshVBOID->VAOID);

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->VerticeID );
	glEnableVertexAttribArray(AbLoc_Pos);
	glVertexAttribPointer(AbLoc_Pos,3,GL_FLOAT,0,sizeof(__m128),0);
	if(MeshVBOID->NormalID)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->NormalID );
		glEnableVertexAttribArray(AbLoc_Normal);
		glVertexAttribPointer(AbLoc_Normal,4,GL_FLOAT,0,sizeof(__m128),0);
	}
	if(MeshVBOID->TexCoordID)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->TexCoordID );
		glEnableVertexAttribArray(AbLoc_Tex0);
		glVertexAttribPointer(AbLoc_Tex0,2,GL_FLOAT,0,0,0);
	}
	if(MeshVBOID->ColorID)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->ColorID );
		glEnableVertexAttribArray(AbLoc_Color);
		glVertexAttribPointer(AbLoc_Color,4,GL_FLOAT,0,0,0);
	}
	glBindVertexArray(0);
}

bool CTopAceModel::LoadMeshToVRAM(_TAM_Mesh * TAM_Mesh)
{
	if(TAM_Mesh->IsFiexible)
	{
		return false;
	}
	if(unsigned int(TAM_Mesh->vertices)==0xFFFFFFFF)
		return false;
	if(TAM_Mesh->vecNum<=0)
		return false;
	tMeshVBOID * MeshVBOID = &MeshVBOIDs[TAM_Mesh->OBJID];

	glGenBuffersARB( 1,&MeshVBOID->VerticeID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->VerticeID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, TAM_Mesh->vecNum*sizeof(__m128), TAM_Mesh->vertices, GL_STATIC_DRAW_ARB );

	if((TAM_Mesh->Normals)&&(unsigned int(TAM_Mesh->Normals)!=0xFFFFFFFF))
	{
		glGenBuffersARB( 1,&MeshVBOID->NormalID);
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->NormalID );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, TAM_Mesh->vecNum*sizeof(__m128), TAM_Mesh->Normals, GL_STATIC_DRAW_ARB );
	}

	if((TAM_Mesh->texcos)&&(unsigned int(TAM_Mesh->texcos)!=0xFFFFFFFF))
	{
		glGenBuffersARB( 1,&MeshVBOID->TexCoordID);
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->TexCoordID );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, TAM_Mesh->vecNum*2*sizeof(float), TAM_Mesh->texcos, GL_STATIC_DRAW_ARB );
	}

	//glGenBuffersARB( 1,&MeshVBOID->FaceID);
	//glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, MeshVBOID->FaceID );
	//glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, TAM_Mesh->FaceNum*3*sizeof(unsigned int), TAM_Mesh->Faces, GL_STATIC_DRAW_ARB );
	
	CreatVAO(MeshVBOID);
	return true;
}
void CTopAceModel::DeleteVRAM()
{
	if(!pTAM_FileHead)
		return ;
	if(unsigned int(pTAM_FileHead->MeshHeadAddress)==0xFFFFFFFF)
		return ;
	if(pTAM_FileHead->MeshNum<=0)
		return ;
	if(!SuppotVBO)
		return ;
	if(!MeshVBOIDs)
		return ;
	if(!isVRAM)
		return ;
	tMeshVBOID * MeshVBOID = NULL;
	for (unsigned int i=0;i<pTAM_FileHead->MeshNum+2;i++)
	{
		MeshVBOID = &MeshVBOIDs[i];
		if(MeshVBOID->VerticeID)
			glDeleteBuffersARB(1,&MeshVBOID->VerticeID);
		if(MeshVBOID->NormalID)
			glDeleteBuffersARB(1,&MeshVBOID->NormalID);
		if(MeshVBOID->TexCoordID)
			glDeleteBuffersARB(1,&MeshVBOID->TexCoordID);
		if(MeshVBOID->FaceID)
			glDeleteBuffersARB(1,&MeshVBOID->FaceID);
		if(MeshVBOID->VAOID)
			glDeleteVertexArrays(1,&MeshVBOID->VAOID);
	}
	if(MeshVBOIDs)
		delete[] MeshVBOIDs;
	MeshVBOIDs=NULL;
	TexManager.Del_VRAM();
	isVRAM=false;
}
void CTopAceModel::DeleteMeshVRAM(_TAM_Mesh * TAM_Mesh)
{
	tMeshVBOID * MeshVBOID = &MeshVBOIDs[TAM_Mesh->OBJID];
	if(MeshVBOID->VerticeID)
		glDeleteBuffersARB(1,&MeshVBOID->VerticeID);
	if(MeshVBOID->NormalID)
		glDeleteBuffersARB(1,&MeshVBOID->NormalID);
	if(MeshVBOID->TexCoordID)
		glDeleteBuffersARB(1,&MeshVBOID->TexCoordID);
	if(MeshVBOID->FaceID)
		glDeleteBuffersARB(1,&MeshVBOID->FaceID);
	if(glIsVertexArray(MeshVBOID->VAOID))
		glDeleteVertexArrays(1,&MeshVBOID->VAOID);
}
void CTopAceModel::Draw(bool Translucent,bool Fiexible)
{
	if(!pTAM_FileHead) return ;
	if(unsigned int(pTAM_FileHead->MeshHeadAddress)==0xFFFFFFFF) return ;
	_TAM_Mesh * TAM_Mesh_Draw=NULL;
	DrawTranslucent=Translucent;
	for(unsigned int i=0;i<pTAM_FileHead->MeshNum;i++)
	{
		TAM_Mesh_Draw=pTAM_FileHead->MeshHeadAddress[i];
		if(TAM_Mesh_Draw)
		{
			if(TAM_Mesh_Draw->OneFace)
				glEnable(GL_CULL_FACE);
				//glCullFace(GL_BACK);
			else
				glDisable(GL_CULL_FACE);
				//glCullFace(GL_NONE);
			//glDisable(GL_CULL_FACE);
			if(TAM_Mesh_Draw->IsFiexible)
			{
				if(!Fiexible) continue;
				CO_SetMMatrixToGlsl(NULL);
				CO_SetPMatrixToGlsl(NULL);
				CO_SetMVPMatrixToGlsl(NULL);
				DrawRAMMeshFiexible(TAM_Mesh_Draw);
			}
			else
			{
				if(Fiexible) continue;
				if(TAM_Mesh_Draw->BoneWeightNum>0)
				{
					glGetFloatv(GL_MODELVIEW_MATRIX,(float *)&NodeBoneMatrixTMP[0]);
					CO_GetMMatrixD(NodeBoneMatrixTMPD);
					if(TAM_Mesh_Draw->FaceNum>0)
					{
						glMultMatrixf((float *)&BoneMatrixs[(TAM_Mesh_Draw->vecBoneWeightsAndBoneIDs[0].vecBoneIDs[0])*4]);
						CO_MultMMatrix((float *)&BoneMatrixs[(TAM_Mesh_Draw->vecBoneWeightsAndBoneIDs[0].vecBoneIDs[0])*4]);
					}
				}
				CO_SetMMatrixToGlsl(NULL);
				CO_SetPMatrixToGlsl(NULL);
				CO_SetMVPMatrixToGlsl(NULL);
				if(SuppotVBO)
					DrawMeshRigid(TAM_Mesh_Draw);
				else
					DrawRAMMeshRigid(TAM_Mesh_Draw);
				if(TAM_Mesh_Draw->BoneWeightNum>0)
				{
					glLoadMatrixf((float *)&NodeBoneMatrixTMP[0]);
					CO_SetMMatrixD(NodeBoneMatrixTMPD);
				}
			}
		}
	}
}
void CTopAceModel::Draw(void)
{
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	Draw(false,true);
	Draw(false,false);
	//glDepthMask(GL_FALSE);
	Draw(true,false);
	Draw(true,true);
	//glDepthMask(GL_TRUE);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
}
void CTopAceModel::SetDrawMeshMat(_TAM_Mat * TAM_Mat)
{
	if(!TAM_Mat)
		return;
	
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,TAM_Mat->specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,TAM_Mat->ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,TAM_Mat->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,TAM_Mat->self_illum);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,&TAM_Mat->specularLv);
	for(int i=0;i<4;i++)
	{
		MaterialDataTAMTMP.diffuse[i]=TAM_Mat->diffuse[i];
		MaterialDataTAMTMP.emission[i]=TAM_Mat->self_illum[i];
		MaterialDataTAMTMP.specular[i]=TAM_Mat->specular[i];
	}
	MaterialDataTAMTMP.diffuse[3]=TAM_Mat->opacity/100.0f;
	MaterialDataTAMTMP.emission[3]=max(1.0f,TAM_Mat->specularLv);
	CO_SetMaterialToGLSL(&MaterialDataTAMTMP);
	if(TAM_Mat->Tex_diffuse)
	{
		glBindTexture(GL_TEXTURE_2D, TAM_Mat->Tex_diffuse->TexID);
		glMatrixMode(GL_TEXTURE);
		if(TAM_Mat->Tex_diffuse->TexType==IS_DDS)
		{
			glLoadMatrixf(&IdentityDDSTexMatrix[0][0]);
			CO_SetDiffuseTexTurnYToGLSL(-1.0f);
		}
		else
		{
			CO_SetDiffuseTexTurnYToGLSL(1.0f);
			glLoadIdentity();
		}
		glMatrixMode(GL_MODELVIEW);
	}


}
void CTopAceModel::DrawRAM(void)
{
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	if(!pTAM_FileHead)
		return ;
	if(unsigned int(pTAM_FileHead->MeshHeadAddress)==0xFFFFFFFF)
		return ;
	_TAM_Mesh * TAM_Mesh_Draw=NULL;
	for(unsigned int i=0;i<pTAM_FileHead->MeshNum;i++)
	{
		TAM_Mesh_Draw=pTAM_FileHead->MeshHeadAddress[i];
		if(TAM_Mesh_Draw)
		{
			if(TAM_Mesh_Draw->IsFiexible)
				DrawRAMMeshFiexible(TAM_Mesh_Draw);
			else
				DrawRAMMeshRigid(TAM_Mesh_Draw);
		}
	}
	glEnable(GL_CULL_FACE);
}
bool CTopAceModel::IsDrawWithAlpha(_TAM_Mesh * TAM_Mesh)
{

	if(!TAM_Mesh) return false;
	//MeshUseAlphaTMP=TAM_Mesh->UseAlpha>0?true:false;
	if(TAM_Mesh->OBJMATID) if(pTAM_FileHead->MatsAddress[TAM_Mesh->OBJMATID-1].Tex_diffuse)
		MeshUseAlphaTMP=pTAM_FileHead->MatsAddress[TAM_Mesh->OBJMATID-1].Tex_diffuse->UseAlpha;
	MeshUseAlphaTMP=MeshUseAlphaTMP||(pTAM_FileHead->MatsAddress[TAM_Mesh->OBJMATID-1].opacity<99.8?true:false);
	if(MeshUseAlphaTMP!=DrawTranslucent) return false;
	if(MeshUseAlphaTMP) glEnable(GL_BLEND);
	else glDisable(GL_BLEND);
	//glColorMask(1.0f,1.0f,1.0f,pTAM_FileHead->MatsAddress[TAM_Mesh->OBJMATID-1].opacity/100.0f);
	return true;
}
bool CTopAceModel::DrawMeshRigid(_TAM_Mesh * TAM_Mesh)
{
	if(TAM_Mesh->vecNum==0) return false;
	tMeshVBOID * MeshVBOID = MeshVBOIDs+TAM_Mesh->OBJID;
	if(MeshVBOID->VerticeID==0) return false;
	
	if(!IsDrawWithAlpha(TAM_Mesh))return false;

	glBindTexture(GL_TEXTURE_2D, 1);
	if(TAM_Mesh->OBJMATID)
		SetDrawMeshMat(pTAM_FileHead->MatsAddress+TAM_Mesh->OBJMATID-1);
	
	glBindVertexArray(MeshVBOID->VAOID);
	glDrawArrays(TAMDrawMode,0,TAM_Mesh->vecNum);
	glBindVertexArray(0);
	glDisableVertexAttribArray(AbLoc_Color);
	glDisableVertexAttribArray(AbLoc_Normal);
	glDisableVertexAttribArray(AbLoc_Pos);
	glDisableVertexAttribArray(AbLoc_Tex0);
	return true;
}
bool CTopAceModel::DrawRAMMeshRigid(_TAM_Mesh * TAM_Mesh)
{
	if(TAMDrawMode==GL_PATCHES) return false;
	if(TAM_Mesh->vecNum==0) return false;

	if(!IsDrawWithAlpha(TAM_Mesh))return false;

	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBindTexture(GL_TEXTURE_2D, 1);
	if(TAM_Mesh->OBJMATID)
		SetDrawMeshMat(pTAM_FileHead->MatsAddress+TAM_Mesh->OBJMATID-1);
	glEnableClientState( GL_VERTEX_ARRAY );
	if((TAM_Mesh->Normals)&&(unsigned int(TAM_Mesh->Normals)!=0xFFFFFFFF))
	{
		glEnableClientState( GL_NORMAL_ARRAY );
		glNormalPointer( GL_FLOAT, 16, TAM_Mesh->Normals[0].m128_f32 );
	}
	if((TAM_Mesh->texcos)&&(unsigned int(TAM_Mesh->texcos)!=0xFFFFFFFF))
	{
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glTexCoordPointer( 2, GL_FLOAT, 0, TAM_Mesh->texcos );
	}
	glVertexPointer( 3, GL_FLOAT, 16, TAM_Mesh->vertices[0].m128_f32 );
	//glDrawElements(GL_TRIANGLES,TAM_Mesh->FaceNum*3,GL_UNSIGNED_INT,(GLvoid*)&(TAM_Mesh->Faces[0]));
	glDrawArrays(GL_TRIANGLES,0,TAM_Mesh->vecNum);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );

	return true;
}

bool CTopAceModel::DrawRAMMeshFiexible(_TAM_Mesh * TAM_Mesh)
{
	
	if(TAMDrawMode==GL_PATCHES) return false;
	if(TAM_Mesh->vecNum==0) return false;

	if(!IsDrawWithAlpha(TAM_Mesh))return false;

	int j=0;
	pDrawRAMMeshFiexibleDSTTMP=(__m128 *)TAM_Mesh->UserPTR;
	bool testbone=false;
	for(unsigned int i=0;i<TAM_Mesh->vecNum;i++)
	{
		if(!BoneMatrixs)
		{
			pDrawRAMMeshFiexibleDSTTMP[i]=TAM_Mesh->vertices[i];
			pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum]=TAM_Mesh->Normals[i];
			continue;
		}
		DrawRAMMeshFiexibleTMPvec=TAM_Mesh->vertices[i];
		DrawRAMMeshFiexibleTMPnol=TAM_Mesh->Normals[i];

		TAM_vecBoneWeightsAndBoneIDsTMP=TAM_Mesh->vecBoneWeightsAndBoneIDs[i];
		
		pDrawRAMMeshFiexibleDSTTMP[i]=IdentityMatrix3;
		pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum]=_mm_set_ps1(0.0f);

		for(j=0;j<min(TAM_Mesh->BoneWeightNum,4);j++)
		{
			if(TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneWeights[j]<=0.0f) continue;
			if(TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneIDs[j]>pTAM_FileHead->BoneNum) continue;
			Easy_matrix_mult_vector3X3(&DrawRAMMeshFiexibleTMPvec2,&BoneMatrixs[TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneIDs[j]*4],DrawRAMMeshFiexibleTMPvec);
			Easy_matrix_mult_Normal3X3(&DrawRAMMeshFiexibleTMPnol2,&BoneMatrixs[TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneIDs[j]*4],DrawRAMMeshFiexibleTMPnol);
			if(TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneWeights[j]<1.0f)
			{
				Easy_vector_scalar_mul(&DrawRAMMeshFiexibleTMPvec2,DrawRAMMeshFiexibleTMPvec2,TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneWeights[j]);
				Easy_vector_scalar_mul(&DrawRAMMeshFiexibleTMPnol2,DrawRAMMeshFiexibleTMPnol2,TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneWeights[j]);
			}
			Easy_vector_add(&pDrawRAMMeshFiexibleDSTTMP[i],pDrawRAMMeshFiexibleDSTTMP[i],DrawRAMMeshFiexibleTMPvec2);
			Easy_vector_add(&pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum],pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum],DrawRAMMeshFiexibleTMPnol2);
		}
		pDrawRAMMeshFiexibleDSTTMP[i].m128_f32[3]=TAM_Mesh->vertices[i].m128_f32[3];
		pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum].m128_f32[3]=TAM_Mesh->Normals[i].m128_f32[3];
		Easy_vector_normalize(&pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum],pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum]);
	}
	glColor3f(1.0f,1.0f,1.0f);
	glBindTexture(GL_TEXTURE_2D, 1);
	if(TAM_Mesh->OBJMATID)
		SetDrawMeshMat(pTAM_FileHead->MatsAddress+TAM_Mesh->OBJMATID-1);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );

	glEnableVertexAttribArray(AbLoc_Pos);
	glVertexAttribPointer(AbLoc_Pos,3,GL_FLOAT,0,sizeof(__m128),pDrawRAMMeshFiexibleDSTTMP);
	if((TAM_Mesh->Normals)&&(unsigned int(TAM_Mesh->Normals)!=0xFFFFFFFF))
	{
		glEnableVertexAttribArray(AbLoc_Normal);
		glVertexAttribPointer(AbLoc_Normal,4,GL_FLOAT,0,sizeof(__m128),pDrawRAMMeshFiexibleDSTTMP+TAM_Mesh->vecNum);
	}
	if((TAM_Mesh->texcos)&&(unsigned int(TAM_Mesh->texcos)!=0xFFFFFFFF))
	{
		glEnableVertexAttribArray(AbLoc_Tex0);
		glVertexAttribPointer(AbLoc_Tex0,2,GL_FLOAT,0,0,TAM_Mesh->texcos);
	}
	glDrawArrays(GL_TRIANGLES,0,TAM_Mesh->vecNum);
	return true;
}

void CTopAceModel::GetBoneMatrix(float Frame,unsigned int BoneID)
{
	if(!BoneMatrixs)
		return;

	GetBoneMatrix_BonePos=IdentityMatrix3;
	GetlinearBoneFrameData(TAM_Get_Bone_Frame(unsigned int(Frame)+1,BoneID,_TAM_Bone_Frame_Type_Translate),&GetBoneMatrix_BonePos,Frame);
	if(GetSlerpBoneFrameData(TAM_Get_Bone_Frame(unsigned int(Frame)+1,BoneID,_TAM_Bone_Frame_Type_Rotate),&GetBoneMatrix_BoneRot,Frame))
	{
		
		Easy_quat_normalize(&GetBoneMatrix_BoneRot,GetBoneMatrix_BoneRot);
		Easy_quat_to_matrix(&BoneMatrixs[BoneID*4],GetBoneMatrix_BoneRot);
		Easy_matrix_translate_External(&BoneMatrixs[BoneID*4],GetBoneMatrix_BonePos);
	}
	else
	{
		Easy_matrix_identity(&BoneMatrixs[BoneID*4]);
		Easy_matrix_translate_External(&BoneMatrixs[BoneID*4],GetBoneMatrix_BonePos);
	}
	if(GetlinearBoneFrameData(TAM_Get_Bone_Frame(unsigned int(Frame)+1,BoneID,_TAM_Bone_Frame_Type_Scale),&GetBoneMatrix_BoneSca,Frame))
		Easy_matrix_scale(&BoneMatrixs[BoneID*4],GetBoneMatrix_BoneSca);	

}
void QuatSlerp(const __m128 from, const __m128 to, float frac, __m128 * out)
{
	float           cosom, absCosom, sinom, sinSqr, omega, scale0, scale1;
	cosom = from.m128_f32[0] * to.m128_f32[0] + from.m128_f32[1] * to.m128_f32[1] + from.m128_f32[2] * to.m128_f32[2] + from.m128_f32[3] * to.m128_f32[3];
	absCosom = fabs(cosom);

	if((1.0f - absCosom) > 1e-6f)
	{
		sinSqr = 1.0f - absCosom * absCosom;
		sinom = 1.0f / sqrt(sinSqr);
		omega = atan2(sinSqr * sinom, absCosom);

		scale0 = sin((1.0f - frac) * omega) * sinom;
		scale1 = sin(frac * omega) * sinom;
	}
	else
	{
		scale0 = 1.0f - frac;
		scale1 = frac;
	}

	scale1 = (cosom >= 0.0f) ? scale1 : -scale1;

	out->m128_f32[0] = scale0 * from.m128_f32[0] + scale1 * to.m128_f32[0];
	out->m128_f32[1] = scale0 * from.m128_f32[1] + scale1 * to.m128_f32[1];
	out->m128_f32[2] = scale0 * from.m128_f32[2] + scale1 * to.m128_f32[2];
	out->m128_f32[3] = scale0 * from.m128_f32[3] + scale1 * to.m128_f32[3];
}
bool CTopAceModel::GetlinearBoneFrameData(_TAM_Bone_Frame * TAM_Bone_FrameFront,__m128 * linearFrameData,float Frame)
{
	if(!TAM_Bone_FrameFront)
		return false;
	if ((int(TAM_Bone_FrameFront)==int(TAM_Bone_FrameFront->PreviousFrameAddress))||(unsigned int(Frame)>=TAM_Bone_FrameFront->FrameTime))
	{
		Easy_vector_copy(linearFrameData,TAM_Bone_FrameFront->FrameData);
	}
	else
	{

		Easy_quat_Mix(
			linearFrameData,
			TAM_Bone_FrameFront->FrameData,
			TAM_Bone_FrameFront->PreviousFrameAddress->FrameData,
			( Frame - float ( TAM_Bone_FrameFront->PreviousFrameAddress->FrameTime ) ) / float( TAM_Bone_FrameFront->FrameTime - TAM_Bone_FrameFront->PreviousFrameAddress->FrameTime )
			);

	}
	return true;

}

bool CTopAceModel::GetSlerpBoneFrameData(_TAM_Bone_Frame * TAM_Bone_FrameFront,__m128 * SlerpFrameData,float Frame)
{
	if(!TAM_Bone_FrameFront)
		return false;
	if ((int(TAM_Bone_FrameFront)==int(TAM_Bone_FrameFront->PreviousFrameAddress))||(unsigned int(Frame)>=TAM_Bone_FrameFront->FrameTime))
	{
		Easy_vector_copy(SlerpFrameData,TAM_Bone_FrameFront->FrameData);
	}
	else
	{
		QuatSlerp(
			TAM_Bone_FrameFront->PreviousFrameAddress->FrameData,
			TAM_Bone_FrameFront->FrameData,
			( Frame - float ( TAM_Bone_FrameFront->PreviousFrameAddress->FrameTime ) ) / float( TAM_Bone_FrameFront->FrameTime - TAM_Bone_FrameFront->PreviousFrameAddress->FrameTime ),
			SlerpFrameData
			);
	}
	return true;

}

bool CTopAceModel::GetCamMatrix(unsigned int CamID, __m128 * CamMatrix)
{
	if(!CamMatrix)
		return false;
	if(!pTAM_FileHead->CameraNum)
		return false;
	if(CamID>=pTAM_FileHead->CameraNum)
		return false;
	if(!pTAM_FileHead->CameraAddress)
		return false;
	_TAM_Camera * TAM_Camera_Tmp=&(pTAM_FileHead->CameraAddress[CamID]);
	if((!TAM_Camera_Tmp->SelfBoneID)||(!BoneMatrixs))
	{
		Easy_matrix_identity(CamMatrix);
		return true;
	}
	if(!TAM_Camera_Tmp->TGTBoneID)
	{
		Easy_matrix_copy(CamMatrix,&BoneMatrixs[TAM_Camera_Tmp->SelfBoneID*4]);
		return true;
	}
	else
	{
		float CamMatrixTmp[4][4];
		Easy_matrix_camera(
			CamMatrixTmp,
			BoneMatrixs[TAM_Camera_Tmp->SelfBoneID*4+3].m128_f32,
			BoneMatrixs[TAM_Camera_Tmp->TGTBoneID*4+3].m128_f32,
			0.0f);
		Easy_matrix_copy(CamMatrix,CamMatrixTmp);
	}
	return true;
}

void CTopAceModel::SetLight(unsigned int LightID,unsigned int LightBase)
{
}


