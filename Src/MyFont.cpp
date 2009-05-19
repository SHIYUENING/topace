#include "MyFont.h"
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input/Output

CMyFont::CMyFont(void)
{
	OneFontpixels = new unsigned char[0x1000];
		
}

CMyFont::~CMyFont(void)
{
}

bool CMyFont::LoadFont(char *filename)
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

void CMyFont::CreatFont(int FontIndex)
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

}
