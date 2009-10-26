#include "Font2D.h"

#pragma comment( lib, "libfreetype.lib" )
CFont2D::CFont2D(void)
: WordNum(0)
,face(NULL)
,library(NULL)
, TexID(0)
, FontCharSet(0)
{
}

CFont2D::~CFont2D(void)
{
	if(face)
		FT_Done_Face(face);
	if(library)
		FT_Done_FreeType(library);
	if(TexID!=0)
		glDeleteTextures(1, &TexID);
	TexID=0;
	face=NULL;
	library=NULL;
}

bool CFont2D::LoadFont(const char * FontName,int FontSizeW,int FontSizeH,int CHARSET)
{
	FontCharSet=CHARSET;
	if (FT_Init_FreeType( &library ))
		return false;
	
	if (FT_New_Face( library, FontName, 0, &face )) 
		return false;
	FT_Set_Char_Size( face, FontSizeW << 6, FontSizeH << 6, 96, 96);

	glGenTextures( 1, &FontCharSet );
	return true;
}
int CFont2D::GetCharHex(char H,char L)
{

	return 0;
}
void CFont2D::inputTxt(const char * Chars)
{

}

void CFont2D::DrawTXT(int WinW, int WinH, int PosX, int PosY, int SizeW, int SizeH,int WordRightLimit)
{

}
int CFont2D::next_p2 ( int a )
{
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}