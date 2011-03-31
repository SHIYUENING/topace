//#pragma once
#ifndef _TAMFT3D_H
#define _TAMFT3D_H
#define TAMFT3D_FILE_PATH L ## "data/Font/test.fnt"
#define TAMFT3D_Ver 2
#define VBOID_NUM 0x1000
#include <GL/glew.h>
#include <math.h>
#include <stdio.h>	
#include <windows.h>

struct _CharSet
{
	unsigned char * VecData;
	unsigned int VecNum;
	unsigned int FaceNum;
};

struct _TAMFT3D_FileHead
{
	char HeadName[8];
	unsigned int FontVer;
	unsigned int FontFileSize;

	unsigned int CodePage;
	unsigned int CharNum;
	unsigned char Unuse[8];

	_CharSet CharSet[0x10000];
};

class CTAMFT3D
{
public:
	CTAMFT3D(void);
	~CTAMFT3D(void);
	bool LoadFontFile(void);
	unsigned char *Font3DFile;
	_TAMFT3D_FileHead * pTAMFT3D_FileHead;
	bool isRAM;
	GLuint VBOID;
	unsigned int MaxVecNum;
	unsigned int MaxFaceNum;
	void DrawText(wchar_t * DrawChar);
	GLuint CharVBOID_indexs[0x10000];
	GLuint CharVBOIDs[VBOID_NUM*2];
};


#endif