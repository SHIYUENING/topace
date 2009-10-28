#include "Font2D.h"

#pragma comment( lib, "libfreetype.lib" )
CFont2D::CFont2D(void)
: WordNum(0)
,face(NULL)
,library(NULL)
, TexID(0)
, FontCharSet(0)
,FontPosX(0)
,FontPosY(0)
,FontTexW(DEFINE_FONT_W)
,FontTexH(DEFINE_FONT_H)
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

bool CFont2D::LoadFont(const char * FontName,int FontSizeW,int FontSizeH,int FontW,int FontH,int CHARSET)
{
	FontTexW=next_p2(FontW);
	FontTexH=next_p2(FontH);
	FontCharSet=CHARSET;
	if (FT_Init_FreeType( &library ))
		return false;
	
	if (FT_New_Face( library, FontName, 0, &face )) 
		return false;
//	FT_Set_Char_Size( face, FontSizeW << 6, FontSizeH << 6, 96, 96);
	FT_Set_Pixel_Sizes(face, FontSizeW, FontSizeH);
	unsigned char* data;
	data =new unsigned char[FontTexW*FontTexH*2];
	ZeroMemory(data,FontTexW*FontTexH*2);
	glGenTextures( 1, &TexID );
	glBindTexture(GL_TEXTURE_2D, TexID);			// ¹¹ÔìÎÆÀí
	glTexImage2D(GL_TEXTURE_2D,0, GL_ALPHA, FontTexW, FontTexH, 0,GL_ALPHA, GL_UNSIGNED_BYTE, data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	delete [] data;
	return true;
}
int CFont2D::GetCharHex(char H,char L)
{
	if(L<0)
		return (256+H)*256+256+L;
	else
		return (256+H)*256+L;
}
void CFont2D::inputTxt(const char * Chars)
{
	if(!face)
		return;
	if(!library)
		return;

	WordNum=0;
	WordNum=strlen(Chars);
	if(WordNum<1)
		return;
	if(WordNum>MAX_FONT_LIST)
		WordNum=MAX_FONT_LIST;
	FontPosX=0;
	FontPosY=0;
	for(unsigned int i=0;i<WordNum;i++)
	{
		if(Chars[i]>0)
		{
			CharToImage(&Chars[i],1);
		}
		else
		{
			i++;
			if(i<WordNum)
			{
				CharToImage(&Chars[i-1],2);
			}
		}

	
	}


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
void CFont2D::CharToImage(const char * Chars,int byteNum)
{
	wchar_t InputChar;
	MultiByteToWideChar(CP_ACP,0,Chars,byteNum,&InputChar,1);
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, InputChar ), FT_LOAD_DEFAULT ))
		return;
	FT_Glyph glyph;
    if(FT_Get_Glyph( face->glyph, &glyph ))
		return;
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;
	unsigned char* data;
	data =new unsigned char[32*32];

	for(int j=0; j <32;j++) {
		for(int i=0; i < 32; i++){
			data[i+j*32] = (i>=bitmap.width || j>=bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width*j];
		}
	}

	glBindTexture(GL_TEXTURE_2D, TexID);
	glTexSubImage2D(GL_TEXTURE_2D,0,FontPosX,FontPosY,bitmap.width,bitmap.rows,GL_ALPHA,GL_UNSIGNED_BYTE,bitmap.buffer);
	FontPosX=FontPosX+FontTexW/8;
	FontPosY=FontPosY+FontTexH/8;
	FT_Done_Glyph(glyph);

	delete [] data;
}
