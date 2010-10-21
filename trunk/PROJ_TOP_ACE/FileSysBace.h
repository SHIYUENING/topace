//#pragma once
#ifndef FILESYSBACE
#define FILESYSBACE
#ifdef WIN32
#include <stdio.h>	
#include <windows.h>
#endif
class CFileSysBace
{
public:
	CFileSysBace(void);
	~CFileSysBace(void);
	unsigned char * ReadLocFile(const char * FileName);
	unsigned char * ReadLocFile(const wchar_t * FileName);
};

#endif