//#pragma once
#ifndef _MYFONT_H
#define _MYFONT_H
#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library

class CMyFont
{
public:
	CMyFont(void);
	~CMyFont(void);
	bool LoadFont(const char *filename);
	int GetFontIndex(BYTE InH,BYTE InL);

	unsigned char * MyFontpixels;
	unsigned char * OneFontpixels;
	unsigned int CreatFont(int FontIndex);
	void inputTxt(const char * Chars);
	unsigned int * TXTTexIDs;
	unsigned int WordNum;
	void ClearTXT(void);
	void DrawTXT(int WinW, int WinH, int PosX, int PosY, int SizeW, int SizeH);
	GLuint WordList;
	bool ifloadedFont;
};
#endif