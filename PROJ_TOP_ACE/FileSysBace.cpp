#include "FileSysBace.h"


CFileSysBace::CFileSysBace(void)
{
}


CFileSysBace::~CFileSysBace(void)
{
}


unsigned char * CFileSysBace::ReadLocFile(const char * FileName)
{
	unsigned char * FileData;
	if(!FileName)
		return NULL;
	int dwNum=MultiByteToWideChar(CP_ACP,0,FileName,-1,NULL,0);
	wchar_t * FileNameWTmp=new wchar_t[dwNum];
	MultiByteToWideChar(CP_ACP,0,FileName,-1,FileNameWTmp,dwNum);
	FileData = ReadLocFile(FileNameWTmp);
	delete[] FileNameWTmp;
	return FileData;
}

unsigned char * CFileSysBace::ReadLocFile(const wchar_t * FileName)
{
	HANDLE hFile;
	DWORD FileSize;
	unsigned char * FileData;
	hFile = CreateFileW(FileName,                       //   open   MYFILE.TXT
						GENERIC_READ,                             //   open   for   reading     
						FILE_SHARE_READ,                       //   share   for   reading     
						NULL,                                             //   no   security     
						OPEN_EXISTING,                           //   existing   file   only     
						FILE_ATTRIBUTE_NORMAL,           //   normal   file     
						NULL);     
	if(hFile == INVALID_HANDLE_VALUE)  
	{
		CloseHandle(hFile);
		return NULL;
	}
	GetFileSize(hFile,&FileSize);
	FileData=new unsigned char[FileSize];
	DWORD Readedsize=0;
	BOOL ReadStates=ReadFile(hFile,FileData,FileSize,&Readedsize,NULL);
	CloseHandle(hFile);
	if(!ReadStates)
		return NULL;
	return FileData;
}
