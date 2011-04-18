#include "TexManager.h"

CTexManager::CTexManager(void)
: TexArray(NULL)
, TexNum(0)
, FilePath(NULL)
, TexNameArray(NULL)
, TexArrayMax(0)
{
}

CTexManager::~CTexManager(void)
{
	DeinitTexArray();
}

void CTexManager::InitTexArray(int MaxTexNum,wchar_t * FilePathIn)
{
	DeinitTexArray();
	TexArrayMax=MaxTexNum;
	TexArray=new Textures*[MaxTexNum];
	for(int i=0;i<TexArrayMax;i++)
		TexArray[i]=NULL;

	FilePath=new wchar_t[wcslen(FilePathIn)+1];
	wcscpy(FilePath,FilePathIn);
	for(int i=wcslen(FilePath)-1;i>0;i--)
	{
		if((FilePath[i]==L'/')||(FilePath[i]==L'\\'))
		{
			FilePath[i+1]=0;
			break;
		}
	}

	TexNameArray=new char *[MaxTexNum];
	for(int i=0;i<TexArrayMax;i++)
		TexNameArray[i]=NULL;

}

void CTexManager::DeinitTexArray(void)
{
	if(TexArray)
	{
		for(int i=0;i<TexArrayMax;i++)
		{
			if(TexArray[i])
				delete TexArray[i];
		}
		delete [] TexArray;
	}
	TexArray=NULL;
	TexArrayMax=0;
	TexNum=0;

	if(FilePath)
		delete [] FilePath;
	FilePath=NULL;

	if(TexNameArray)
	{
		for(int i=0;i<TexArrayMax;i++)
		{
			if(TexNameArray[i])
				delete [] TexNameArray[i];
		}
		delete [] TexNameArray;
	}
	TexNameArray=NULL;
}

int CTexManager::AddTex(char * TexName)
{
	if(TexNum==TexArrayMax)
		return 0;
	if(!TexNameArray)
		return 0;
	for(int i=0;i<TexNum;i++)
	{
		if(TexNameArray[i])
		{
			if(stricmp(TexNameArray[i],TexName)==0)
			{
				return i;
			}
		}
	}
	TexNameArray[TexNum]=new char[strlen(TexName)+1];
	strcpy(TexNameArray[TexNum],TexName);
	TexArray[TexNum]=new Textures;

	int dwNum=MultiByteToWideChar(CP_ACP,0,TexName,-1,NULL,0);
	wchar_t * FileNameWTmp=new wchar_t[dwNum+1];
	MultiByteToWideChar(CP_ACP,0,TexName,-1,FileNameWTmp,dwNum);
	for(int i=0;i<dwNum;i++)
	{
		if(FileNameWTmp[i]==L'.')
			FileNameWTmp[i]=0;
	}
	wchar_t * FilePathTmp=new wchar_t[wcslen(FilePath)+1];
	wchar_t * FullFilePath=new wchar_t[wcslen(FilePath)+dwNum+1];
	wcscpy(FilePathTmp,FilePath);
	for(int i=wcslen(FilePath)-1;i>0;i--)
	{
		if(FilePathTmp[i]==L'/')
		{
			FilePathTmp[i+1]=0;
			break;
		}
	}
	swprintf_s(FullFilePath,wcslen(FilePathTmp)+wcslen(FileNameWTmp)+1,L"%s%s",FilePathTmp,FileNameWTmp);
	if(TexArray[TexNum]->loadfile(FullFilePath))
	{

		delete[] FileNameWTmp;
		delete[] FullFilePath;
		delete[] FilePathTmp;
		TexNum++;
		return TexNum-1;
	}
	else
	{
		delete[] FileNameWTmp;
		delete[] FullFilePath;
		delete[] FilePathTmp;
		return -1;
	}
}

void CTexManager::LoadToVRAM(void)
{
	if(!TexArray)
		return;
	for(int i=0;i<TexNum;i++)
	{
		if(TexArray[i])
			TexArray[i]->LoadToVRAM();
	}
}

void CTexManager::Del_VRAM(void)
{
	if(!TexArray)
		return;
	for(int i=0;i<TexNum;i++)
	{
		if(TexArray[i])
			TexArray[i]->Del_VRAM();
	}
}

void CTexManager::GetTexSet(int TexManagerID,unsigned int * TexID,int * TexType,bool * UseAlpha)
{
	if((TexManagerID>=TexNum)||(TexManagerID<0))
	{
		TexID[0]=Textures::DefineTexID;//
		TexType[0]=NO_TEX;
		UseAlpha[0]=false;
		return;
	}
	TexID[0]=TexArray[TexManagerID]->TexID;
	TexType[0]=TexArray[TexManagerID]->TexType;
	UseAlpha[0]=TexArray[TexManagerID]->UseAlpha;
}
