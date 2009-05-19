//#pragma once
#ifndef _MYFONT_H
#define _MYFONT_H
class CMyFont
{
public:
	CMyFont(void);
	~CMyFont(void);
	bool LoadFont(char *filename);
	int GetFontIndex(int InH,int InL);

	unsigned char * MyFontpixels;
	unsigned char * OneFontpixels;
	void CreatFont(int FontIndex);
};
#endif