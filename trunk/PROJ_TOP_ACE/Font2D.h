//#pragma once
#ifndef _FONT2D_H
#define _FONT2D_H
#include <windows.h> 
#include <GL/glew.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#define MAX_FONT_LIST 64
#define DEFINE_FONT_W 256
#define DEFINE_FONT_H 256
struct tFont2Dset
{
	int FontSizeW;
	int FontSizeH;
	int FontW;
	int FontH;
	int CHARSET;
};
class CFont2D
{
public:
	CFont2D(void);
	~CFont2D(void);
	bool LoadFont(const char * FontName,int FontSizeW,int FontSizeH,int FontW=DEFINE_FONT_W,int FontH=DEFINE_FONT_H,int CHARSET=GB2312_CHARSET);
	void inputTxt(const char * Chars);
	void DrawTXT(int WinW, int WinH, int PosX, int PosY, int SizeW, int SizeH,int WordRightLimit);
	unsigned int WordNum;
	int GetCharHex(char H,char L);
	int next_p2 ( int a );
	FT_Face face;
	FT_Library library;
	GLuint TexID;
	int FontCharSet;
	void CharToImage(const char * Chars,int byteNum);
	int FontPosX;
	int FontPosY;
	int FontTexW;
	int FontTexH;
	int OnefontW;
	int OnefontH;
	float OneCharWidth[MAX_FONT_LIST];
	unsigned char* OnefontData;
private:
	int CharNum;
};
#endif