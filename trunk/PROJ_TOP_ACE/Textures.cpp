#include"Textures.h"

bool DEFTEXLoaded=false;
unsigned int DEFTEXID=0;
GLuint Textures::DefineTexID=0;
Textures::Textures(void)
:TexType(0)
,TexID(0)
,DDSfile(NULL)
,TGAfile(NULL)
,UseAlpha(false)
{
}
Textures::~Textures(void)
{
	Del_RAM();
	Del_VRAM();
	if(DDSfile!=NULL)
		delete DDSfile;
	DDSfile=NULL;
	if(TGAfile!=NULL)
		delete TGAfile;
	TGAfile=NULL;
	TexID=0;
}
void Textures::LoadDefineTex()
{
	if(Textures::DefineTexID)
		return;
	unsigned char DefTexData[64*64*4];
	for(int i=0;i<64*64*4;i++)
		DefTexData[i]=255;

	glGenTextures(1, &(Textures::DefineTexID));
	glBindTexture(GL_TEXTURE_2D, (Textures::DefineTexID));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, 64, 64, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, DefTexData);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
}
bool Textures::LoadDefTex(void)
{
	if(DEFTEXLoaded)
	{
		TexID=DEFTEXID;
		TexType=IS_DEF;
		return true;
	}
	unsigned char DefTexData[64*64*4];
	for(int i=0;i<64*64*4;i++)
		DefTexData[i]=255;

	glGenTextures(1, &DEFTEXID);
	glBindTexture(GL_TEXTURE_2D, DEFTEXID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, 64, 64, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, DefTexData);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	DEFTEXLoaded=true;
	TexID=DEFTEXID;
	TexType=IS_DEF;
	return true;
}
bool Textures::loadfile(char * filename)
{
	char LoadFileName[256]={0};
	
	DDSfile = new CDDS;
	sprintf(LoadFileName,"%s.%s",filename,"dds");
	DDSfile->loadDDSTextureFile(LoadFileName);
	if((DDSfile->pDDSImageData==NULL)||(DDSfile->DDSerror!=DDS_NO_ERROR))
	{
		delete DDSfile;
		DDSfile = NULL;
		sprintf(LoadFileName,"%s.%s",filename,"tga");
		TGAfile = new TGA;
		TGAfile->LoadTGA(LoadFileName);
		if((TGAfile->imageData==NULL)||(TGAfile->TGAerror!=TGA_NO_ERROR))
		{
			delete TGAfile;
			TGAfile=NULL;
			TexType = NO_TEX;
			return false;
		}
		else
		{
			UseAlpha=TGAfile->UseAlpha;
			TexType=IS_TGA;
		}
	}
	else
	{
		TexType=IS_DDS;
		UseAlpha=DDSfile->UseAlpha;
	}
	return true;
}
unsigned int Textures::LoadToVRAM(int TexParameter)
{
	if(DDSfile!=NULL)
	{
		TexID=DDSfile->loadCompressedTexture(TexParameter);
	}
	else
	{
		if(TGAfile!=NULL)
			TexID=TGAfile->LoadTGA_RAMtoVRAM(TexParameter);
		else
			TexID=Textures::DefineTexID;
			//LoadDefTex();
	}
	return TexID;
}
bool Textures::isRAM()
{
	if(DDSfile!=NULL)
	{
		return DDSfile->isRAM;
	}
	else
	{
		if(TGAfile!=NULL)
			return TGAfile->isRAM;
	}
	return false;
}
bool Textures::isVRAM()
{
	if(DDSfile!=NULL)
	{
		return DDSfile->isVRAM;
	}
	else
	{
		if(TGAfile!=NULL)
			return TGAfile->isVRAM;
	}
	return false;
}
int Textures::GetTexError()
{
	if(DDSfile!=NULL)
	{
		return DDSfile->DDSerror;
	}
	else
	{
		if(TGAfile!=NULL)
			return TGAfile->TGAerror;
	}
	return 0;
}
void Textures::Del_RAM()
{
	if(DDSfile!=NULL)
	{
		DDSfile->DelDDS_RAM();
	}
	else
	{
		if(TGAfile!=NULL)
			TGAfile->DelTGA_RAM();
	}
}
void Textures::Del_VRAM()
{
	if(DDSfile!=NULL)
	{
		DDSfile->DelDDS_VRAM();
	}
	else
	{
		if(TGAfile!=NULL)
			TGAfile->DelTGA_VRAM();
	}
	if(DEFTEXLoaded)
	{
		DEFTEXLoaded=false;
		if(DEFTEXID!=0)
			glDeleteTextures(1, &DEFTEXID);
		DEFTEXID=0;
	}
	if(Textures::DefineTexID)
	{
		glDeleteTextures(1, &(Textures::DefineTexID));
		Textures::DefineTexID=0;
	}
}

