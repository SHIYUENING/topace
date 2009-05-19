#include "MyFont.h"
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input/Output

CMyFont::CMyFont(void)
{
		
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
