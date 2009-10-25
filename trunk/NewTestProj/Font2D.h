//#pragma once
#ifndef _FONT3D_H
#define _FONT3D_H
#include <windows.h> 
#include <GL/glew.h>
#define MAX_FONT_LIST 64
class CFont2D
{
public:
	CFont2D(void);
	~CFont2D(void);
	bool LoadFont(const char * FontName,int CHARSET=GB2312_CHARSET);
	void inputTxt(const char * Chars);
	void DrawTXT(int WinW, int WinH, int PosX, int PosY, int SizeW, int SizeH,int WordRightLimit);
	unsigned int WordNum;
	int GetCharHex(char H,char L);
};
#endif