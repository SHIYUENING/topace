#include "FONTS2D.h"
#include "CharSysBace.h"
#include "Common.h"
#include "DrawQUAD.h"
#pragma comment( lib, "freetype2311MT.lib" )
CFONTS2D::CFONTS2D(void)
	:FontDataTMP_FullWidth(0)
	,FontDataTMP_HalfWidth(0)
	,Face_FullWidth(0)
	,Face_HalfWidth(0)
	,library(0)
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

bool CFONTS2D::LoadFullWidthFont(const char * FontPath,int FontW,int FontH,int CHARSET)
{
	if(Face_FullWidth) FT_Done_Face(Face_FullWidth);
	if(!library)if (FT_Init_FreeType( &library )) return false;
	if (FT_New_Face( library, FontPath, 0, &Face_FullWidth ))  return false;
	FT_Set_Char_Size( Face_FullWidth, FontW << 6, FontH << 6, 66, 64);
	FontDataTMP_FullWidth = new unsigned char[FontW*FontH*2];
	return true;
}
bool CFONTS2D::LoadHalfWidthFont(const char * FontPath,int FontW,int FontH,int CHARSET)
{
	if(Face_HalfWidth) FT_Done_Face(Face_HalfWidth);
	if(!library)if (FT_Init_FreeType( &library )) return false;
	if (FT_New_Face( library, FontPath, 0, &Face_HalfWidth ))  return false;
	FT_Set_Char_Size( Face_HalfWidth, FontW << 6, FontH << 6, 66, 64);
	FontDataTMP_HalfWidth = new unsigned char[FontW*FontH*2];
	return true;
}

void CFONTS2D::SetCharTex(const wchar_t CharIn)
{
	if((!Face_FullWidth)&&(!Face_HalfWidth)) return;
	FT_Glyph glyph;
	FT_BitmapGlyph bitmap_glyph;
	if(FontSets[CharIn].TexID) return;
	face=CharIn>=0xff?Face_FullWidth:Face_HalfWidth;
	if(!Face_FullWidth) face=Face_HalfWidth;
	if(!Face_HalfWidth) face=Face_FullWidth;
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, CharIn ), FT_LOAD_DEFAULT )) return;
	FT_Outline_Embolden( &(face->glyph->outline), 30 );
    if(FT_Get_Glyph( face->glyph, &glyph )) return;
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    bitmap_glyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;
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


void CFONTS2D::DrawTexts(const wchar_t * CharIn,int PosX,int PosY,int WinW,int WinH,int LineW,int lineH)
{
	glDisable(GL_TEXTURE_2D); glEnable(GL_TEXTURE_RECTANGLE);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   ); glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);glPushMatrix();GLfloat DrawTextMatrix[16]; CO_MatrixOrthogonalProjection(0.0f,(float)WinW,0.0f,(float)WinH,-1.0f,2.0f,DrawTextMatrix); glLoadMatrixf(DrawTextMatrix);
	glMatrixMode(GL_MODELVIEW); glPushMatrix();glLoadIdentity(); //glTranslatef((float)PosX,(float)PosY,0.0f);
	//DrawQUAD(0.0f,100.0f,100.0f,0.0f,10,10);
	if(!CharIn) return;
	int CharInCount=GetCharLenth(CharIn);
	float DrawX=float(PosX);float DrawY=float(PosY);
	float MaxLineY=0.0f;
	for (int i=0;i<CharInCount;i++)
	{
		SetCharTex(CharIn[i]);
		glBindTexture(GL_TEXTURE_RECTANGLE, FontSets[CharIn[i]].TexID);
		MaxLineY=max(MaxLineY,float(FontSets[CharIn[i]].SizeH));
		if(LineW<=(DrawX+float(FontSets[CharIn[i]].SizeW)))
		{
			DrawY=DrawY+MaxLineY;
			DrawX=float(PosX);
		}
		DrawQUAD(DrawX,DrawX+float(FontSets[CharIn[i]].SizeW),DrawY+float(FontSets[CharIn[i]].SizeH),DrawY,FontSets[CharIn[i]].SizeW,FontSets[CharIn[i]].SizeH);
		DrawX=DrawX+float(FontSets[CharIn[i]].SizeW);
	}
	glMatrixMode(GL_MODELVIEW);glPopMatrix();
	glMatrixMode(GL_PROJECTION);glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_TEXTURE_RECTANGLE);glEnable(GL_DEPTH_TEST);
}
