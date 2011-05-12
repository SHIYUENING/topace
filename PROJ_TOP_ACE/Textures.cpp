#include"Textures.h"

GLuint Textures::DefineTexID=0;
GLuint Textures::DefNorTexID=0;
GLuint Textures::DefSpeTexID=0;
Textures::Textures(void)
:TexType(0)
,TexID(0)
,DDSfile(NULL)
,TGAfile(NULL)
,UseAlpha(false)
, TexW(0)
, TexH(0)
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
	if(!Textures::DefineTexID)
	{
		unsigned char DefTexData[64*64*4];
		for(int i=0;i<64*64*4;i++)
			DefTexData[i]=255;

		glGenTextures(1, &(Textures::DefineTexID));
		glBindTexture(GL_TEXTURE_2D, (Textures::DefineTexID));
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, 64, 64, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, DefTexData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	}

	if(!Textures::DefNorTexID)
	{
		unsigned char DefTexData[64*64*4];
		for(int i=0;i<64*64*4;i=i+4)
		{
			DefTexData[i+0]=127;
			DefTexData[i+1]=127;
			DefTexData[i+2]=255;
			DefTexData[i+3]=255;
		}

		glGenTextures(1, &(Textures::DefNorTexID));
		glBindTexture(GL_TEXTURE_2D, (Textures::DefNorTexID));
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, DefTexData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	}
	if(!Textures::DefSpeTexID)
	{
		unsigned char DefTexData[64*64*4];
		for(int i=0;i<64*64*4;i=i+4)
		{
			DefTexData[i+0]=255;
			DefTexData[i+1]=0;
			DefTexData[i+2]=255;
			DefTexData[i+3]=0;
		}

		glGenTextures(1, &(Textures::DefSpeTexID));
		glBindTexture(GL_TEXTURE_2D, (Textures::DefSpeTexID));
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, DefTexData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	}
}

bool Textures::loadfile(char * filename)
{
	char LoadFileName[256]={0};
	
	DDSfile = new CDDS;
	sprintf(LoadFileName,"%s.%s",filename,"dds");
	DDSfile->LoadFile(LoadFileName);
	if((DDSfile->pDDSImageData==NULL)||(DDSfile->DDSerror!=DDS_NO_ERROR))
	{
		delete DDSfile;
		DDSfile = NULL;
		sprintf(LoadFileName,"%s.%s",filename,"tga");
		TGAfile = new TGA;
		TGAfile->LoadFile(LoadFileName);
		if((TGAfile->imageData==NULL)||(TGAfile->TGAerror!=TGA_NO_ERROR))
		{
			delete TGAfile;
			TGAfile=NULL;
			TexType = NO_TEX;
			return false;
		}
		else
		{
			TexW=TGAfile->width;
			TexH=TGAfile->height;
			UseAlpha=TGAfile->UseAlpha;
			TexType=IS_TGA;
		}
	}
	else
	{
		TexW=DDSfile->TexW;
		TexH=DDSfile->TexH;
		TexType=IS_DDS;
		UseAlpha=DDSfile->UseAlpha;
	}
	
	return true;
}
bool Textures::loadfile(wchar_t * filename)
{
	ADD_LOG_Q("Read Texture");
	TexID=DefineTexID;
	wchar_t LoadFileName[256]={0};
	
	DDSfile = new CDDS;
	swprintf_s(LoadFileName,256,L"%s.%s",filename,L"dds");
	//sprintf(LoadFileName,L"%s.%s",filename,L"dds");
	ADD_LOG_Q(LoadFileName);
	DDSfile->LoadFileT(LoadFileName);
	if((DDSfile->pDDSImageData==NULL)||(DDSfile->DDSerror!=DDS_NO_ERROR))
	{
		ADD_LOG_Q("Read DDS fail,change TGA.","#0000FF");
		delete DDSfile;
		DDSfile = NULL;
		swprintf_s(LoadFileName,256,L"%s.%s",filename,L"tga");
		//sprintf(LoadFileName,"%s.%s",filename,"tga");
		TGAfile = new TGA;
		ADD_LOG_Q(LoadFileName);
		TGAfile->LoadFile(LoadFileName);
		if((TGAfile->imageData==NULL)||(TGAfile->TGAerror!=TGA_NO_ERROR))
		{
			ADD_LOG_Q("Read TGA fail.","#0000FF");
			delete TGAfile;
			TGAfile=NULL;
			TexType = NO_TEX;
			return false;
		}
		else
		{
			TexW=TGAfile->width;
			TexH=TGAfile->height;
			ADD_LOG_Q("Read TGA OK.");
			UseAlpha=TGAfile->UseAlpha;
			TexType=IS_TGA;
		}
	}
	else
	{
		TexW=DDSfile->TexW;
		TexH=DDSfile->TexH;
		ADD_LOG_Q("Read DDS OK.");
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
	if(Textures::DefineTexID)
	{
		glDeleteTextures(1, &(Textures::DefineTexID));
		Textures::DefineTexID=0;
	}
	if(Textures::DefNorTexID)
	{
		glDeleteTextures(1, &(Textures::DefNorTexID));
		Textures::DefNorTexID=0;
	}
	if(Textures::DefSpeTexID)
	{
		glDeleteTextures(1, &(Textures::DefSpeTexID));
		Textures::DefSpeTexID=0;
	}
}

