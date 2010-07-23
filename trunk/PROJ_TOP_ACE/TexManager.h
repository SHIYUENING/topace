#ifndef _TEXMANAGER_H
#define _TEXMANAGER_H
#include"Textures.h"
class CTexManager
{
public:
	CTexManager(void);
	~CTexManager(void);
	Textures **TexArray;
	char **TexNameArray;
	void InitTexArray(int MaxTexNum,wchar_t * FilePathIn);
	void DeinitTexArray(void);
	int TexNum;
	int TexArrayMax;
	wchar_t *FilePath;
	
	int AddTex(char * TexName);
	void LoadToVRAM(void);
	void Del_VRAM(void);
	void GetTexSet(int TexManagerID,unsigned int * TexID,int * TexType,bool * UseAlpha);
};

#endif