//#pragma once
#ifndef FILESYSBACE
#define FILESYSBACE
#ifdef WIN32
#include <stdio.h>	
#include <windows.h>
#endif

unsigned char * ReadLocFile(const char * FileName,unsigned int ReadSize=0,unsigned int ReadAddress=0);
unsigned char * ReadLocFile(const wchar_t * FileName,unsigned int ReadSize=0,unsigned int ReadAddress=0);
bool WriteLocFile(const char * FileName,const char * FilePath,unsigned char * FileData,unsigned int WriteSize);
bool WriteLocFile(const wchar_t * FileName,const wchar_t * FilePath,unsigned char * FileData,unsigned int WriteSize);
bool WriteLocFile(const char * FileFullPath,unsigned char * FileData,unsigned int WriteSize);
bool WriteLocFile(const wchar_t * FileFullPath,unsigned char * FileData,unsigned int WriteSize);

#endif