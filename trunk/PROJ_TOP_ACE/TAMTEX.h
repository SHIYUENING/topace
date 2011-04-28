//#pragma once
#ifndef _TAMTEX_H
#define _TAMTEX_H
#include <windows.h>		// Header File For Windows
//#endif
#include "TALogSys.h"
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>
#include <gl\glew.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
typedef enum _TAM_TEX_Type {
	_TAM_TEX_Type_NO_Type=0x00,
    _TAM_TEX_Type_DXT		= 0x01,
    _TAM_TEX_Type_TGA		= 0x02,
    _TAM_TEX_Type_DXT_Alpha		= 0x03,
    _TAM_TEX_Type_TGA_Alpha		= 0x04
} _TAM_TEX_Type;

typedef enum _TAM_TEX_Status {
	_TAM_TEX_Status_NO_Status=0x00,
    _TAM_TEX_Status_NO_File		= 0x01,
    _TAM_TEX_Status_Read_Error		= 0x02,
    _TAM_TEX_Status_File_Error		= 0x03,
    _TAM_TEX_Status_LoadOK		= 0x04
} _TAM_TEX_Status;

struct _TAM_TEX
{
	unsigned char * pTEX_Data;
	GLuint TEXID;
	int x;
	int y;

	GLuint Type;
	_TAM_TEX_Type File_Type;
	_TAM_TEX_Status Status;
	GLint TexParameter;

	_TAM_TEX * pNext;
	unsigned TAM_TEX_ID;
	wchar_t * FilePath;
	int UNUSE1;
};

inline void Init_One_TAM_TEX(_TAM_TEX * pTAM_TEX)
{
	if(!pTAM_TEX) return;

	pTAM_TEX->FilePath=NULL;
	pTAM_TEX->pTEX_Data=NULL;
	pTAM_TEX->File_Type=_TAM_TEX_Type_NO_Type;
	pTAM_TEX->Status=_TAM_TEX_Status_NO_Status;

	pTAM_TEX->TAM_TEX_ID=0;
	pTAM_TEX->TEXID=0;
	pTAM_TEX->TexParameter=0;
	pTAM_TEX->Type=0;

	pTAM_TEX->UNUSE1=0;
	pTAM_TEX->x=0;
	pTAM_TEX->y=0;
	pTAM_TEX->pNext=0;
}
inline void Clear_One_TAM_TEX(_TAM_TEX * pTAM_TEX)
{
	if(!pTAM_TEX) return;

	if(pTAM_TEX->FilePath) delete [] pTAM_TEX->FilePath; pTAM_TEX->FilePath=NULL;
	pTAM_TEX->File_Type=_TAM_TEX_Type_NO_Type;
	if(pTAM_TEX->pTEX_Data) delete [] pTAM_TEX->pTEX_Data; pTAM_TEX->pTEX_Data=NULL;
	pTAM_TEX->Status=_TAM_TEX_Status_NO_Status;

	pTAM_TEX->TAM_TEX_ID=0;
	if(pTAM_TEX->TEXID) glDeleteTextures(1,&pTAM_TEX->TEXID); pTAM_TEX->TEXID=0;
	pTAM_TEX->TexParameter=0;

	pTAM_TEX->Type=0;
	pTAM_TEX->UNUSE1=0;
	pTAM_TEX->x=0;
	pTAM_TEX->y=0;
}
class CTAMTEX
{
public:
	CTAMTEX(void);
	~CTAMTEX(void);
	static void Init(void);
	static void Deinit(void);
	static _TAM_TEX *pTAM_TEXs;
};

#endif