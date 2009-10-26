//#pragma once
#ifndef _FONT3D_H
#define _FONT3D_H
#include <windows.h> 
#include <GL/glew.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#define MAX_FONT_LIST 64
class CFont2D
{
public:
	CFont2D(void);
	~CFont2D(void);
	bool LoadFont(const char * FontName,int FontSizeW,int FontSizeH,int CHARSET=GB2312_CHARSET);
	void inputTxt(const char * Chars);
	void DrawTXT(int WinW, int WinH, int PosX, int PosY, int SizeW, int SizeH,int WordRightLimit);
	unsigned int WordNum;
	int GetCharHex(char H,char L);
	int next_p2 ( int a );
	FT_Face face;
	FT_Library library;
	GLuint TexID;
	int FontCharSet;
};
#endif