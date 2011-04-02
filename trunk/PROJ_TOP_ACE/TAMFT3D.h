//#pragma once
#ifndef _TAMFT3D_H
#define _TAMFT3D_H
#define TAMFT3D_FILE_PATH L ## "data/Font/test.fnt"
#define TAMFT3D_Ver 2
#define VBOID_NUM 0x400
//#define CharSetTMP pTAMFT3D_FileHead->CharSet[DrawChar]
#include <GL/glew.h>
#include <math.h>
#include <stdio.h>	
#include <windows.h>
struct _TestTTTTTT
{
	float xx[67*3];
	int yy[53*3];
};
struct _CharVBO
{
	GLuint Vec;
	GLuint Face;
	GLuint NoDrawTimes;
};
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
	void Draw3DText(wchar_t * DrawChar,float FontW,float FontH,float LineW,float lineH=0.0f,float IntervalW=0.0f);
	GLuint CharVBOID_indexs[0x10000];
	_CharVBO CharVBO[VBOID_NUM];
	unsigned int CharToVRAM(wchar_t DrawChar);
	void ClearOneCharVBO(unsigned int VBOIndex);
	void DrawOneChar(wchar_t DrawChar);
	void ClearAllVBO(void);
	int RenderFaceNum;
};


#endif