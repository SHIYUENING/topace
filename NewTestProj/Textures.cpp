#include"Textures.h"
Textures::Textures(void)
:TexType(0)
,TexID(0)
,DDSfile(NULL)
,TGAfile(NULL)
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
bool Textures::loadfile(char * filename)
{
	char LoadFileName[256]={0};
	
	DDSfile = new CDDS;
	sprintf(LoadFileName,"%s.%s",filename,"dds");
	DDSfile->loadDDSTextureFile(LoadFileName);
	if(DDSfile->pDDSImageData==NULL)
	{
		delete DDSfile;
		DDSfile = NULL;
		sprintf(LoadFileName,"%s.%s",filename,"tga");
		TGAfile = new TGA;
		TGAfile->LoadTGA(LoadFileName);
		if(TGAfile->imageData==NULL)
		{
			delete TGAfile;
			TGAfile=NULL;
			return false;
		}
		else
			TexType=IS_TGA;
	}
	else
		TexType=IS_DDS;
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
}