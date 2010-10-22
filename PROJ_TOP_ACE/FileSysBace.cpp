#include "FileSysBace.h"
#include "CharSysBace.h"


unsigned char * ReadLocFile(const char * FileName,unsigned int ReadSize,unsigned int ReadAddress)
{
	unsigned char * FileData;
	if(!FileName)
		return NULL;
	int dwNum=MultiByteToWideChar(CP_ACP,0,FileName,-1,NULL,0);
	wchar_t * FileNameWTmp=new wchar_t[dwNum];
	MultiByteToWideChar(CP_ACP,0,FileName,-1,FileNameWTmp,dwNum);
	FileData = ReadLocFile(FileNameWTmp,ReadSize,ReadAddress);
	delete[] FileNameWTmp;
	return FileData;
}

unsigned char * ReadLocFile(const wchar_t * FileName,unsigned int ReadSize,unsigned int ReadAddress)
{
	if(!FileName)
		return NULL;
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
	if((ReadSize!=0)&&(ReadSize<=FileSize))
		FileSize=ReadSize;
	FileData=new unsigned char[FileSize];
	DWORD Readedsize=0;
	SetFilePointer(hFile,ReadAddress,NULL,FILE_BEGIN);
	BOOL ReadStates=ReadFile(hFile,FileData,FileSize,&Readedsize,NULL);
	CloseHandle(hFile);
	if(!ReadStates)
		return NULL;
	return FileData;
}


bool WriteLocFile(const char * FileName,const char * FilePath,unsigned char * FileData,unsigned int WriteSize)
{
	if((!FileName)||(!FileData)||(WriteSize==0))
		return NULL;
	wchar_t * FileNameWTmp=NULL;
	wchar_t * FilePathWTmp=NULL;
	int dwNum=0;
	dwNum=MultiByteToWideChar(CP_ACP,0,FileName,-1,NULL,0);
	FileNameWTmp=new wchar_t[dwNum];
	MultiByteToWideChar(CP_ACP,0,FileName,-1,FileNameWTmp,dwNum);
	if(FilePath)
	{
		dwNum=MultiByteToWideChar(CP_ACP,0,FilePath,-1,NULL,0);
		FilePathWTmp=new wchar_t[dwNum];
		MultiByteToWideChar(CP_ACP,0,FileName,-1,FilePathWTmp,dwNum);
	}
	bool WriteStates=WriteLocFile(FileNameWTmp,FilePathWTmp,FileData,WriteSize);
	if(FileNameWTmp) delete[] FileNameWTmp;
	if(FilePathWTmp) delete[] FilePathWTmp;
	return WriteStates;
}

bool WriteLocFile(const wchar_t * FileName,const wchar_t * FilePath,unsigned char * FileData,unsigned int WriteSize)
{
	if((!FileName)||(!FileData)||(WriteSize==0))
		return false;
	wchar_t * FileFullPath=NULL;
	if(FilePath)
	{
		FileFullPath=ADDTwoWchar(FilePath,FileName);
	}
	else
	{
		FileFullPath=ADDTwoWchar(L".\\",FileName);
	}
	bool WriteStatus=WriteLocFile(FileFullPath,FileData,WriteSize);
	if(FileFullPath!=NULL) delete[] FileFullPath;
	return WriteStatus;
}
bool WriteLocFile(const char * FileFullPath,unsigned char * FileData,unsigned int WriteSize)
{
	if((!FileFullPath)||(!FileData)||(WriteSize==0))
		return false;
	HANDLE   hFile;
	hFile   =   CreateFileA(FileFullPath,                       //   open   MYFILE.TXT     
                            GENERIC_WRITE,                             //   open   for   reading     
                            FILE_SHARE_READ,                       //   share   for   reading     
                            NULL,                                             //   no   security     
                            CREATE_ALWAYS,                           //   existing   file   only     
                            FILE_ATTRIBUTE_NORMAL,           //   normal   file     
                            NULL);
	DWORD savesize=0;
	bool WriteStatus=WriteFile(hFile,FileData,WriteSize,&savesize,NULL);
	CloseHandle(hFile);
	return WriteStatus;
}
bool WriteLocFile(const wchar_t * FileFullPath,unsigned char * FileData,unsigned int WriteSize)
{
	if((!FileFullPath)||(!FileData)||(WriteSize==0))
		return false;
	HANDLE   hFile;
	hFile   =   CreateFileW(FileFullPath,                       //   open   MYFILE.TXT     
                            GENERIC_WRITE,                             //   open   for   reading     
                            FILE_SHARE_READ,                       //   share   for   reading     
                            NULL,                                             //   no   security     
                            CREATE_ALWAYS,                           //   existing   file   only     
                            FILE_ATTRIBUTE_NORMAL,           //   normal   file     
                            NULL);
	DWORD savesize=0;
	bool WriteStatus=WriteFile(hFile,FileData,WriteSize,&savesize,NULL);
	CloseHandle(hFile);
	return WriteStatus;
}