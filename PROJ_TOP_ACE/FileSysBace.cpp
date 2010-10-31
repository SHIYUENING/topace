#include "FileSysBace.h"
#include "CharSysBace.h"

bool ReadLocFile(HANDLE hFile,unsigned char * FileData,unsigned int ReadSize,DWORD * ReadInSize,unsigned int ReadAddress)
{
	BOOL ReadStates;
	DWORD FileSize=0;
	if((!hFile)||(hFile == INVALID_HANDLE_VALUE))
		return false;
	FileSize=GetFileSize(hFile,NULL);
	if((ReadSize!=0)&&(ReadSize<=FileSize))
		FileSize=ReadSize;
	if(FileSize<=0)
		return false;
	if(!FileData)
		FileData=new unsigned char[FileSize];
	SetFilePointer(hFile,ReadAddress,NULL,FILE_BEGIN);
	ReadStates=ReadFile(hFile,FileData,FileSize,ReadInSize,NULL);
	CloseHandle(hFile);
	return ReadStates>0?true:false;
}
bool ReadLocFile(const char * FileName,unsigned char * FileData,unsigned int ReadSize,DWORD * ReadInSize,unsigned int ReadAddress)
{
	if(!FileName)
		return false;
	HANDLE hFile=CreateFileA(FileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	return ReadLocFile(hFile,FileData,ReadSize,ReadInSize,ReadAddress);
}
bool ReadLocFile(const wchar_t * FileName,unsigned char * FileData,unsigned int ReadSize,DWORD * ReadInSize,unsigned int ReadAddress)
{
	if(!FileName)
		return false;
	HANDLE hFile=CreateFileW(FileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	return ReadLocFile(hFile,FileData,ReadSize,ReadInSize,ReadAddress);
}
char * ReadLocFullFile_ANSI_TXT(const wchar_t * FileName)
{
	BOOL ReadStates;
	DWORD FileSize=0;
	if(!FileName)
		return false;
	HANDLE hFile=CreateFileW(FileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if((!hFile)||(hFile == INVALID_HANDLE_VALUE))
		return NULL;
	FileSize=GetFileSize(hFile,NULL);
	if(FileSize<=0)
		return NULL;
	char * FileData=new char[FileSize+1];
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	DWORD Readedsize=0;
	ReadStates=ReadFile(hFile,FileData,FileSize,&Readedsize,NULL);
	CloseHandle(hFile);
	FileData[FileSize]=0;
	return ReadStates>0?FileData:NULL;
}
/*
unsigned char * ReadLocFile(const char * FileName,unsigned int ReadSize,int * ReadInSize,unsigned int ReadAddress)
{
	unsigned char * FileData;
	if(!FileName)
		return NULL;
	int dwNum=MultiByteToWideChar(CP_ACP,0,FileName,-1,NULL,0);
	wchar_t * FileNameWTmp=new wchar_t[dwNum];
	MultiByteToWideChar(CP_ACP,0,FileName,-1,FileNameWTmp,dwNum);
	FileData = ReadLocFile(FileNameWTmp,ReadSize,ReadInSize,ReadAddress);
	delete[] FileNameWTmp;
	return FileData;
}
unsigned char * ReadLocFile(const wchar_t * FileName,unsigned int ReadSize,int * ReadInSize,unsigned int ReadAddress)
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
	FileSize=GetFileSize(hFile,NULL);
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
*/
bool WriteLocFile(const char * FileName,const char * FilePath,unsigned char * FileData,unsigned int WriteSize,bool Add)
{
	if((!FileName)||(!FileData)||(WriteSize==0))
		return false;
	char * FileFullPath=NULL;
	if(FilePath)
		FileFullPath=ADDTwoChar(FilePath,FileName);
	else
		FileFullPath=ADDTwoChar(".\\",FileName);
	bool WriteStatus=WriteLocFile(FileFullPath,FileData,WriteSize,Add);
	if(FileFullPath!=NULL) delete[] FileFullPath;
	return WriteStatus;
}
bool WriteLocFile(const wchar_t * FileName,const wchar_t * FilePath,unsigned char * FileData,unsigned int WriteSize,bool Add)
{
	if((!FileName)||(!FileData)||(WriteSize==0))
		return false;
	wchar_t * FileFullPath=NULL;
	if(FilePath)
		FileFullPath=ADDTwoChar(FilePath,FileName);
	else
		FileFullPath=ADDTwoChar(L".\\",FileName);
	bool WriteStatus=WriteLocFile(FileFullPath,FileData,WriteSize,Add);
	if(FileFullPath!=NULL) delete[] FileFullPath;
	return WriteStatus;
}
bool WriteLocFile(const char * FileFullPath,unsigned char * FileData,unsigned int WriteSize,bool Add)
{
	if((!FileFullPath)||(!FileData)||(WriteSize==0))
		return false;
	FILE * fWrite;
	if(Add)
		fopen_s(&fWrite,FileFullPath,"a");
	else
		fopen_s(&fWrite,FileFullPath,"w");
	fwrite(FileData,1,WriteSize,fWrite);
	fclose(fWrite);
	/*HANDLE   hFile;
	hFile   =   CreateFileA(FileFullPath,                      
                            GENERIC_WRITE,                         
                            FILE_SHARE_READ,                  
                            NULL,                                         
                            Add?OPEN_EXISTING:CREATE_ALWAYS,                        
                            FILE_ATTRIBUTE_NORMAL,          
                            NULL);
	DWORD savesize=0;
	if(Add)
		SetFilePointer(hFile,0,NULL,FILE_END);
	bool WriteStatus=WriteFile(hFile,FileData,WriteSize,&savesize,NULL)!=0?true:false;
	CloseHandle(hFile);
	return WriteStatus;*/
	return false;
}
bool WriteLocFile(const wchar_t * FileFullPath,unsigned char * FileData,unsigned int WriteSize,bool Add)
{
	if((!FileFullPath)||(!FileData)||(WriteSize==0))
		return false;
	FILE * fWrite;
	if(Add)
		_wfopen_s(&fWrite,FileFullPath,L"a");
	else
		_wfopen_s(&fWrite,FileFullPath,L"w");
	fwrite(FileData,1,WriteSize,fWrite);
	fclose(fWrite);
	/*HANDLE   hFile;
	hFile   =   CreateFileW(FileFullPath,                 
                            GENERIC_WRITE,                        
                            FILE_SHARE_READ,                     
                            NULL,                                         
                            Add?OPEN_EXISTING:CREATE_ALWAYS,                     
                            FILE_ATTRIBUTE_NORMAL,           
                            NULL);
	DWORD savesize=0;
	if(Add)
		SetFilePointer(hFile,0,NULL,FILE_END);
	bool WriteStatus=WriteFile(hFile,FileData,WriteSize,&savesize,NULL)!=0?true:false;
	CloseHandle(hFile);
	return WriteStatus;*/
	return false;
}
