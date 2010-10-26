//#pragma once
#ifndef FILESYSBACE
#define FILESYSBACE
#ifdef WIN32
#include <stdio.h>	
#include <windows.h>
#endif
/*
typedef enum _WriteLocFile_Type {
	_WriteLocFile_Type_Rewrite 0x0;
	_WriteLocFile_Type_Add 0x1;
}_WriteLocFile_Type;*/
unsigned char * ReadLocFile(const char * FileName,unsigned int ReadSize=0,unsigned int ReadAddress=0);
unsigned char * ReadLocFile(const wchar_t * FileName,unsigned int ReadSize=0,unsigned int ReadAddress=0);
bool WriteLocFile(const char * FileName,const char * FilePath,unsigned char * FileData,unsigned int WriteSize,bool Add );
bool WriteLocFile(const wchar_t * FileName,const wchar_t * FilePath,unsigned char * FileData,unsigned int WriteSize,bool Add );
bool WriteLocFile(const char * FileFullPath,unsigned char * FileData,unsigned int WriteSize,bool Add );
bool WriteLocFile(const wchar_t * FileFullPath,unsigned char * FileData,unsigned int WriteSize,bool Add );

#endif