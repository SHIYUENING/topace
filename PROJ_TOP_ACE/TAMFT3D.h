//#pragma once
#ifndef _TAMFT3D_H
#define _TAMFT3D_H
#define TAMFT3D_FILE_PATH L ## "data/Font/test.fnt"
#define TAMFT3D_Ver 2
#include <GL/glew.h>
#include <math.h>
#include <stdio.h>	
#include <windows.h>
struct _VecData
{
	float * Vecs;
	int * Faces;
};
struct _CharSet
{
	_VecData * VecData;
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
	bool isVRAM;
	bool ToVRAM(void);
	GLuint VBOID;
	unsigned int TotelVecNum;
	unsigned int TotelFaceNum;
};


#endif