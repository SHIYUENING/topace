#ifndef _FONTS2D_H
#define _FONTS2D_H
//#pragma once
#include <windows.h> 
#include <GL/glew.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
struct tFonts2Dset
{
	int SizeW;
	int SizeH;
	int TexSizeX;
	int TexSizeY;
	int MoveY;
	GLuint TexID;
};
class CFONTS2D
{
public:
	CFONTS2D(void);
	~CFONTS2D(void);
	bool LoadFullWidthFont(const char * FontPath,int FontW,int FontH,int CHARSET=GB2312_CHARSET);
	bool LoadHalfWidthFont(const char * FontPath,int FontW,int FontH,int CHARSET=GB2312_CHARSET);
	FT_Face Face_FullWidth;
	FT_Face Face_HalfWidth;
	FT_Face face;
	FT_Library library;
	tFonts2Dset FontSets[0xFFFF];
	unsigned char* FontDataTMP_FullWidth;
	unsigned char* FontDataTMP_HalfWidth;
	void SetCharTex(const wchar_t CharIn);
	void DrawTexts(const wchar_t * CharIn,int PosX,int PosY,int WinW,int WinH,int LineW,int lineH,float IntervalW=2.0f);
	int next_p2 ( int a );
	int FontSizeFX;
	int FontSizeFY;
	int FontSizeHX;
	int FontSizeHY;
};
#endif
