#include "BomsSet.h"
bool LoadTGA(Texture *, char *);
CBomsSet::CBomsSet(void)
: Pnum(0)
, SizeStart(0)
, SizeEnd(0)
, ShowTimeStart(0)
, ShowTimeEnd(0)
, ColorAlphaStart(0)
, ColorAlphaEnd(0)
, m_IsSupportFBO(false)
{
}

CBomsSet::~CBomsSet(void)
{
}

bool CBomsSet::LoadBoms(int BomsNum)
{
	Texture LoadBomTexture;
	char BomsFileName[64]={0};
	sprintf(BomsFileName,"Data/Boms/Bom%d.tga",BomsNum);
	FILE	*m_Filefighter;
	if ((m_Filefighter=fopen(BomsFileName,"rb"))==NULL)
		return false;
	if (LoadTGA(&LoadBomTexture, BomsFileName))
	{
		glGenTextures(1, &LoadBomTexture.texID);
		glBindTexture(GL_TEXTURE_2D, LoadBomTexture.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, LoadBomTexture.bpp / 8, LoadBomTexture.width, LoadBomTexture.height, 0, LoadBomTexture.type, GL_UNSIGNED_BYTE, LoadBomTexture.imageData);
		Pnum=LoadBomTexture.texID;
		if(m_IsSupportFBO)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}
		if (LoadBomTexture.imageData)						// If Texture Image Exists ( CHANGE )
		{
			free(LoadBomTexture.imageData);					// Free The Texture Image Memory ( CHANGE )
		}
		return true;

	}
	return false;
}
