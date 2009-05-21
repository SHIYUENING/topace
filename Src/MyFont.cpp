#include "MyFont.h"
CMyFont::CMyFont(void)
:WordNum(0)
{
	OneFontpixels = new unsigned char[0x1000];
		
}

CMyFont::~CMyFont(void)
{
	delete [] OneFontpixels;
}

bool CMyFont::LoadFont(const char *filename)
{
	FILE	*m_FilePointer;
	m_FilePointer= new FILE;
	if ((m_FilePointer=fopen(filename,"rb"))==NULL)
	{
		return false;	// 打开文件失败
	}

	unsigned int filesize = 0;
	while (!feof(m_FilePointer))
	{
		fgetc(m_FilePointer);
		filesize++;
	}
	filesize--;
	rewind(m_FilePointer);
	if(filesize==0xFF900)
	{
		MyFontpixels = new unsigned char[filesize];
		fread( MyFontpixels, 1, filesize, m_FilePointer );
		fclose(m_FilePointer);
		return true;
	}

	return false;
}

int CMyFont::GetFontIndex(int InH,int InL)
{

	return (InH-0xA1)*(0xFE-0xA1+1)+InL-0xA1;
}

unsigned int CMyFont::CreatFont(int FontIndex)
{
	for(int i=0;i<0x80;i++)
	{
		BYTE pixels8 = MyFontpixels[FontIndex*0x80+i];
		bool bpixels[8];
		bpixels[0] = bool(pixels8 & 1);
		bpixels[1] = bool(pixels8 & 2);
		bpixels[2] = bool(pixels8 & 4);
		bpixels[3] = bool(pixels8 & 8);
		bpixels[4] = bool(pixels8 & 0x10);
		bpixels[5] = bool(pixels8 & 0x20);
		bpixels[6] = bool(pixels8 & 0x40);
		bpixels[7] = bool(pixels8 & 0x80);
		for(int j=0;j<8;j++)
		{

			OneFontpixels[i*0x20+j*4+0]=0xFF;
			OneFontpixels[i*0x20+j*4+1]=0xFF;
			OneFontpixels[i*0x20+j*4+2]=0xFF;
			if(bpixels[j])
				OneFontpixels[i*0x20+j*4+3]=0xFF;
			else
				OneFontpixels[i*0x20+j*4+3]=0;

		
		}

	
	}

	unsigned int FontTexID;


	glGenTextures(1, &FontTexID);				// 创建一个纹理
	glBindTexture(GL_TEXTURE_2D, FontTexID);			// 构造纹理
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 32, 32, GL_RGBA, GL_UNSIGNED_BYTE, OneFontpixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	return FontTexID;

}

void CMyFont::inputTxt(const char * Chars)
{
	WordNum=strlen(Chars)/2;
	DrawTXT=new unsigned int[WordNum*sizeof(unsigned int)];
	for(int i=0;i<WordNum;i++)
	{
		//if(Chars[i*2]*Chars[i*2+1]==0)
			//return;
		DrawTXT[i]=CreatFont(GetFontIndex(Chars[i*2],Chars[i*2+1]));
	
	}
}

void CMyFont::ClearTXT(void)
{
	if(WordNum==0)
		return;
}
