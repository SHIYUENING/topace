//#pragma once
#ifndef _LOAD3DS_H
#define _LOAD3DS_H
#include <gl\glew.h>
#include <lib3ds.h>
class CLoad3DS
{
public:
	CLoad3DS(void);
	~CLoad3DS(void);
	bool Loadfile(char * filename);
	unsigned int LoadToVRAM(void);
	void Del_RAM(void);
	void Del_VRAM(void);
	bool isRAM;
	bool isVRAM;
	Lib3dsFile *Model3ds
		unsigned int VBONormalID;
	unsigned int VBOTangentID;
	unsigned int VBOTexCoordID;
	unsigned int VBOVerticeID;
	unsigned int VBOColorID;
};

#endif