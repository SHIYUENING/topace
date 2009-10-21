//#pragma once
#ifndef _FONTS_H
#define _FONTS_H
#include <windows.h> 
#include <GL/glew.h>
#define MAX_FONT_LIST 64
class CFonts
{
public:
	CFonts(void);
	~CFonts(void);
	bool LoadFont(const char * FontName,int CHARSET=GB2312_CHARSET);
	void inputTxt(const char * Chars);
	void DrawTXT(int WinW, int WinH, int PosX, int PosY, int SizeW, int SizeH,int WordRightLimit);
	HDC hDC;
	GLuint FontList[MAX_FONT_LIST];
	GLYPHMETRICSFLOAT gmf[MAX_FONT_LIST];
	unsigned int WordNum;
};
#endif