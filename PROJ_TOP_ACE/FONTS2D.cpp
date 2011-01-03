#include "FONTS2D.h"

#pragma comment( lib, "freetype2311MT.lib" )
CFONTS2D::CFONTS2D(void)
	:FontDataTMP_FullWidth(0)
	,FontDataTMP_HalfWidth(0)
{
	ZeroMemory(FontSets,sizeof(FontSets));
}

CFONTS2D::~CFONTS2D(void)
{	
	if(Face_FullWidth) FT_Done_Face(Face_FullWidth);
	if(Face_HalfWidth) FT_Done_Face(Face_HalfWidth);
	if(library) FT_Done_FreeType(library);
	if(FontDataTMP_FullWidth) delete [] FontDataTMP_FullWidth;
	if(FontDataTMP_HalfWidth) delete [] FontDataTMP_HalfWidth;
}

bool CFONTS2D::LoadFullWidthFont(const char * FontPath,int FontW,int FontH,int CHARSET=GB2312_CHARSET)
{
	if (FT_Init_FreeType( &library )) return false;
	if (FT_New_Face( library, FontPath, 0, &Face_FullWidth ))  return false;
	FT_Set_Char_Size( Face_FullWidth, FontW << 6, FontH << 6, 66, 64);
	FontDataTMP_FullWidth = new unsigned char[FontW*FontH*2];
	return true;
}
bool CFONTS2D::LoadHalfWidthFont(const char * FontPath,int FontW,int FontH,int CHARSET=GB2312_CHARSET)
{
	if (FT_Init_FreeType( &library )) return false;
	if (FT_New_Face( library, FontPath, 0, &Face_HalfWidth ))  return false;
	FT_Set_Char_Size( Face_HalfWidth, FontW << 6, FontH << 6, 66, 64);
	FontDataTMP_HalfWidth = new unsigned char[FontW*FontH*2];
	return true;
}

void CFONTS2D::SetCharTex(const wchar_t CharIn)
{
	if(FontSets[CharIn].TexID) return;
	face=CharIn>=0xff?Face_FullWidth:Face_HalfWidth;
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, CharIn ), FT_LOAD_DEFAULT )) return;
	FT_Outline_Embolden( &(face->glyph->outline), 30 );
    if(FT_Get_Glyph( face->glyph, &glyph )) return;
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    bitmap_glyph = (FT_BitmapGlyph)glyph;
	bitmap=bitmap_glyph->bitmap;
	FontSets[CharIn].SizeW=bitmap.width;
	FontSets[CharIn].SizeH=bitmap.rows;

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_RECTANGLE);
	glGenTextures( 1, &FontSets[CharIn].TexID );
	glBindTexture(GL_TEXTURE_RECTANGLE, FontSets[CharIn].TexID);
	glTexImage2D(GL_TEXTURE_RECTANGLE,0, GL_ALPHA, bitmap.width, bitmap.rows, 0,GL_ALPHA, GL_UNSIGNED_BYTE, bitmap.buffer);
	glTexParameterf(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_RECTANGLE,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_RECTANGLE,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


	glDisable(GL_TEXTURE_RECTANGLE);
}
