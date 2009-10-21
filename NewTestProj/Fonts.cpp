#include "Fonts.h"

CFonts::CFonts(void)
: hDC(NULL)
, WordNum(0)
{
	for(unsigned int i=0;i<MAX_FONT_LIST;i++)
		FontList[i]=0;
}

CFonts::~CFonts(void)
{
}

bool CFonts::LoadFont(const char * FontName,int CHARSET)
{
	HFONT	font;										// Windows Font ID
	font = CreateFont(	-MulDiv(16,GetDeviceCaps(hDC,LOGPIXELSY),72),							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						FontName);				// Font Name

	SelectObject(hDC, font);
	if(hDC)
		return true;
	else
		return false;
}

void CFonts::inputTxt(const char * Chars)
{
	if(!hDC)
		return;
	WordNum=0;
	WordNum=strlen(Chars)/2;
	if(WordNum<1)
		return;
	if(WordNum>MAX_FONT_LIST)
		WordNum=MAX_FONT_LIST;
	for(unsigned int i=0;i<WordNum;i++)
	{
		if(FontList[i]>0)
			glDeleteLists(FontList[i], 1);
		FontList[i]=glGenLists(1);
		if(Chars[i]<0x80)
		wglUseFontOutlines(	hDC,							// Select The Current DC
						0xb1a1,								// Starting Character
						1,							// Number Of Display Lists To Build
						FontList[i],							// Starting Display Lists
						0.0f,							// Deviation From The True Outlines
						0.2f,							// Font Thickness In The Z Direction
						WGL_FONT_LINES,				// Use Polygons, Not Lines
						gmf[i]);
	}
}

void CFonts::DrawTXT(int WinW, int WinH, int PosX, int PosY, int SizeW, int SizeH,int WordRightLimit)
{
	if(!hDC)
		return;
}
