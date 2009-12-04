#ifndef _TEXTURES_H
#define _TEXTURES_H
#include "DDS.h"
#include "tga.h"
#define NO_TEX 0
#define IS_DDS 1
#define IS_TGA 2

class Textures
{
public:
	Textures(void);
	~Textures(void);
	bool loadfile(char * filename);
	unsigned int LoadToVRAM(int TexParameter = GL_LINEAR);
	bool isRAM();
	bool isVRAM();
	int GetTexError();
	void Del_RAM();
	void Del_VRAM();
	int TexType;
	GLuint TexID;
	CDDS *DDSfile;
	TGA *TGAfile;
};
#endif