#include "TAMTEX.h"
_TAM_TEX *CTAMTEX::pTAM_TEXs=NULL;
GLfloat CTAMTEX::AFSet=1.0f;
GLuint CTAMTEX::DefineTexID=0;
GLuint CTAMTEX::DefNorTexID=0;
GLuint CTAMTEX::DefSpeTexID=0;
CTAMTEX::CTAMTEX(void)
{
}


CTAMTEX::~CTAMTEX(void)
{
}




void CTAMTEX::Init(void)
{
	Init_One_TAM_TEX(CTAMTEX::pTAM_TEXs);
}


void CTAMTEX::Deinit(void)
{
	_TAM_TEX * TAM_TEX_TMP=NULL;
	while(CTAMTEX::pTAM_TEXs->pNext)
	{
		Clear_One_TAM_TEX(CTAMTEX::pTAM_TEXs);
		TAM_TEX_TMP=CTAMTEX::pTAM_TEXs->pNext;
		CTAMTEX::pTAM_TEXs=CTAMTEX::pTAM_TEXs->pNext;
		delete TAM_TEX_TMP;
	}
}
void CTAMTEX::LoadDefineTex()
{
	unsigned char DefTexData[4];

	if(CTAMTEX::DefineTexID)
		glDeleteTextures(1,&CTAMTEX::DefineTexID);
	for(int i=0;i<4;i++)
		DefTexData[i]=255;

	glGenTextures(1, &(CTAMTEX::DefineTexID));
	glBindTexture(GL_TEXTURE_2D, (CTAMTEX::DefineTexID));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, 1, 1, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, DefTexData);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	if(CTAMTEX::DefNorTexID)
		glDeleteTextures(1,&CTAMTEX::DefNorTexID);
	DefTexData[0]=127;
	DefTexData[1]=127;
	DefTexData[2]=255;
	DefTexData[3]=255;

	glGenTextures(1, &(CTAMTEX::DefNorTexID));
	glBindTexture(GL_TEXTURE_2D, (CTAMTEX::DefNorTexID));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, DefTexData);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);


	if(CTAMTEX::DefSpeTexID)
		glDeleteTextures(1,&CTAMTEX::DefSpeTexID);
	DefTexData[0]=225;
	DefTexData[1]=0;
	DefTexData[2]=0;
	DefTexData[3]=0;

	glGenTextures(1, &(CTAMTEX::DefSpeTexID));
	glBindTexture(GL_TEXTURE_2D, (CTAMTEX::DefSpeTexID));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, DefTexData);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
}
