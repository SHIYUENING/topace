#include "TopAceModel.h"//文件头

CTopAceModel::CTopAceModel(void)
:TAM_File_States(_TAM_File_States_NoRead)
, TMA_FileData(NULL)
{
}

CTopAceModel::~CTopAceModel(void)
{
	if(TMA_FileData)
		_aligned_free(TMA_FileData);
	TMA_FileData = NULL;
}

bool CTopAceModel::ReadTAMFile(char * FileName)
{
	if(TAM_File_States==_TAM_File_States_ReadOK)
		return false;
	HANDLE   hFile;     
      
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
		TMA_FileData = NULL;
		return false;
	}

	_TAM_FileHead TAM_FileHead;
	DWORD Readedsize=0;
	BOOL ReadStates=ReadFile(hFile,&TAM_FileHead,sizeof(TAM_FileHead),&Readedsize,NULL);
	if(!ReadStates)
	{
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_NoFile;
		TMA_FileData = NULL;
		return false;
	}
	if(TAM_FileHead.FileSize<sizeof(TAM_FileHead))
	{
		TAM_File_States=_TAM_File_States_ReadFail;
		TMA_FileData = NULL;
		CloseHandle(hFile);
		return false;
	}
	TMA_FileData = (unsigned char * ) _aligned_malloc (TAM_FileHead.FileSize,16);

	Readedsize = 0;
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	ReadStates=ReadFile(hFile,TMA_FileData,TAM_FileHead.FileSize,&Readedsize,NULL);
	if(!ReadStates)
	{
		DWORD dwError = GetLastError();
		_aligned_free(TMA_FileData);
		TMA_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}
	if(!ReadTAMFile_After(TMA_FileData))
	{
		_aligned_free(TMA_FileData);
		TMA_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}


	CloseHandle(hFile);
	return true;
}
bool CTopAceModel::ReadTAMFile(wchar_t * FileName)
{
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

	_TAM_FileHead TAM_FileHead;
	DWORD Readedsize=0;
	BOOL ReadStates=ReadFile(hFile,&TAM_FileHead,sizeof(TAM_FileHead),&Readedsize,NULL);
	if(!ReadStates)
	{
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_NoFile;
		TMA_FileData = NULL;
		return false;
	}
	if(TAM_FileHead.FileSize<sizeof(TAM_FileHead))
	{
		TAM_File_States=_TAM_File_States_ReadFail;
		TMA_FileData = NULL;
		CloseHandle(hFile);
		return false;
	}
	TMA_FileData = (unsigned char * ) _aligned_malloc (TAM_FileHead.FileSize,16);

	Readedsize = 0;
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	ReadStates=ReadFile(hFile,TMA_FileData,TAM_FileHead.FileSize,&Readedsize,NULL);
	if(!ReadStates)
	{
		DWORD dwError = GetLastError();
		_aligned_free(TMA_FileData);
		TMA_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}
	if(!ReadTAMFile_After(TMA_FileData))
	{
		_aligned_free(TMA_FileData);
		TMA_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}


	CloseHandle(hFile);
	return true;
}
bool CTopAceModel::ReadTAMFile_After(unsigned char * TAM_FileData_IN)
{
	_TAM_FileHead  * TAM_FileHead_IN=(_TAM_FileHead*)TAM_FileData_IN;
	TAM_FileHead_IN->MeshHeadAddress=(_TAM_Mesh_Head  * )&TAM_FileData_IN[(int)TAM_FileHead_IN->MeshHeadAddress];
	TAM_FileHead_IN->MatsAddress=(_TAM_Mat  * )&TAM_FileData_IN[(int)TAM_FileHead_IN->MatsAddress];
	TAM_FileHead_IN->BoneHeadAddress=(_TAM_Bone_Head  * )&TAM_FileData_IN[(int)TAM_FileHead_IN->BoneHeadAddress];
	TAM_FileHead_IN->LightHeadAddress=(_TAM_Light_Head * )&TAM_FileData_IN[(int)TAM_FileHead_IN->LightHeadAddress];
	TAM_FileHead_IN->CameraAddress=(_TAM_Camera * )&TAM_FileData_IN[(int)TAM_FileHead_IN->CameraAddress];
/*
	_TAM_Mesh ** OBJAddressTMP=NULL;
	OBJAddressTMP=(_TAM_Mesh **)TAM_FileHead_IN->MeshHeadAddress;
	for (int i=0;i<TAM_FileHead_IN->MeshNum;i++)
	{
		OBJAddressTMP[i]=(_TAM_Mesh *)(int(OBJAddressTMP[i])+int(TAM_FileHead_IN->MeshHeadAddress));
		//&TAM_FileHead_IN->MeshHeadAddress->OBJAddress[i]=(_TAM_Mesh  ** )&TAM_FileData_IN[(int)&TAM_FileHead_IN->MeshHeadAddress->OBJAddress[i]];
		int sererwer=12132;
	}
	_TAM_Mesh * TTT_TAM_Mesh=TAM_FileHead_IN->MeshHeadAddress->OBJAddress[0];
	*/
	return true;
}


_TAM_Mesh * CTopAceModel::TAM_Get_Mesh(unsigned int MeshID)
{
	return NULL;
}

_TAM_Bone * CTopAceModel::TAM_Get_Bone(unsigned int BoneID)
{
	return NULL;
}

_TAM_Light * CTopAceModel::TAM_Get_Light(unsigned int LightID)
{
	return NULL;
}

_TAM_Bone_Frame * CTopAceModel::TAM_Get_Bone_Frame(unsigned int BoneFrameID,unsigned int BoneID,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type)
{
	return NULL;
}
_TAM_Bone_Frame * CTopAceModel::TAM_Get_Bone_Frame(unsigned int BoneFrameID,_TAM_Bone * TAM_Bone,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type)
{
	return NULL;
}
_TAM_Bone_Frame * CTopAceModel::TAM_Get_Bone_PreviousFrame(unsigned int BoneFrameID,unsigned int BoneID,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type)
{
	return NULL;
}
_TAM_Bone_Frame * CTopAceModel::TAM_Get_Bone_PreviousFrame(unsigned int BoneFrameID,_TAM_Bone * TAM_Bone,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type)
{
	return NULL;
}

_TAM_Light_Frame * CTopAceModel::TAM_Get_Light_Frame(unsigned int LightFrameID,unsigned int LightID,_TAM_Light_Frame_Type TAM_Light_Frame_Type)
{
	return NULL;
}
_TAM_Light_Frame * CTopAceModel::TAM_Get_Light_Frame(unsigned int LightFrameID,_TAM_Light * TAM_Light,_TAM_Light_Frame_Type TAM_Light_Frame_Type)
{
	return NULL;
}
_TAM_Light_Frame * CTopAceModel::TAM_Get_Light_PreviousFrame(unsigned int LightFrameID,unsigned int LightID,_TAM_Light_Frame_Type TAM_Light_Frame_Type)
{
	return NULL;
}
_TAM_Light_Frame * CTopAceModel::TAM_Get_Light_PreviousFrame(unsigned int LightFrameID,_TAM_Light * TAM_Light,_TAM_Light_Frame_Type TAM_Light_Frame_Type)
{
	return NULL;
}

_TAM_Bone * CTopAceModel::TAM_Get_NextBone(unsigned int BoneID)
{
	return NULL;
}
_TAM_Bone * CTopAceModel::TAM_Get_NextBone(_TAM_Bone * TAM_Bone)
{
	return NULL;
}

_TAM_Bone * CTopAceModel::TAM_Get_ChildBone(unsigned int BoneID)
{
	return NULL;
}
_TAM_Bone * CTopAceModel::TAM_Get_ChildBone(_TAM_Bone * TAM_Bone)
{
	return NULL;
}

