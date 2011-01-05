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
	,FontSizeFX(0)
	,FontSizeFY(0)
	,FontSizeHX(0)
	,FontSizeHY(0)
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
	for(int i=0;i<0xFFFF;i++)
	{
		if(FontSets[i].TexID!=0)
			glDeleteTextures(1, &FontSets[i].TexID);
	}
}
int CFONTS2D::next_p2 ( int a )
{
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}
bool CFONTS2D::LoadFullWidthFont(const char * FontPath,int FontW,int FontH,int CHARSET)
{
	FT_Face FaceTMP=NULL;
	if(!library)if (FT_Init_FreeType( &library )) return false;
	if (FT_New_Face( library, FontPath, 0, &FaceTMP ))  return false;
	if(Face_FullWidth) FT_Done_Face(Face_FullWidth);
	Face_FullWidth=FaceTMP;
	FT_Set_Char_Size( Face_FullWidth, FontW << 6, FontH << 6, 66, 64);
	//FT_Set_Pixel_Sizes(Face_FullWidth,FontW,FontH);
	FontSizeFX=next_p2(FontW);
	FontSizeFY=next_p2(FontH);
	if(FontDataTMP_FullWidth) delete [] FontDataTMP_FullWidth;
	FontDataTMP_FullWidth = new unsigned char[FontSizeFX*FontSizeFY*2];
	ZeroMemory(FontDataTMP_FullWidth,FontSizeFX*FontSizeFY*2);
	return true;
}
bool CFONTS2D::LoadHalfWidthFont(const char * FontPath,int FontW,int FontH,int CHARSET)
{
	FT_Face FaceTMP=NULL;
	if(!library)if (FT_Init_FreeType( &library )) return false;
	if (FT_New_Face( library, FontPath, 0, &FaceTMP ))  return false;
	if(Face_HalfWidth) FT_Done_Face(Face_HalfWidth);
	Face_HalfWidth=FaceTMP;
	FT_Set_Char_Size( Face_HalfWidth, FontW << 6, FontH << 6, 64, 64);
	FontSizeHX=next_p2(FontW);
	FontSizeHY=next_p2(FontH);
	if(FontDataTMP_HalfWidth) delete [] FontDataTMP_HalfWidth;
	FontDataTMP_HalfWidth = new unsigned char[FontSizeHX*FontSizeHY*2];
	ZeroMemory(FontDataTMP_HalfWidth,FontSizeFX*FontSizeFY*2);
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
	FontSets[CharIn].TexSizeX=face==Face_FullWidth?FontSizeFX:FontSizeHX;
	FontSets[CharIn].TexSizeY=face==Face_FullWidth?FontSizeFY:FontSizeHY;
	unsigned char* FontDataTMP=face==Face_FullWidth?FontDataTMP_FullWidth:FontDataTMP_HalfWidth;
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, CharIn ), FT_LOAD_DEFAULT )) return;
	FT_Outline_Embolden( &(face->glyph->outline), 30 );
    if(FT_Get_Glyph( face->glyph, &glyph )) return;
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    bitmap_glyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;
	FontSets[CharIn].SizeW=bitmap.width;
	FontSets[CharIn].SizeH=bitmap.rows;

	int Ymove=0;
	//if(CharIn<0xFF)
	//	Ymove=FontSets[CharIn].TexSizeY/20;
	//if(CharIn==L'-')
	//	Ymove=FontSets[CharIn].TexSizeY/2-bitmap.rows*2;
	//if(CharIn==L'.')
	//	Ymove=bitmap.rows/2;
	if(CharIn<0xFF) FontSets[CharIn].MoveY=bitmap.rows/6;
	if(CharIn==L'-') FontSets[CharIn].MoveY=FontSets[CharIn].TexSizeY/2-bitmap.rows*2;
	for(int j=Ymove; j <FontSets[CharIn].TexSizeY;j++) {
		for(int i=0; i < FontSets[CharIn].TexSizeX; i++){
			FontDataTMP[i+(j-Ymove)*FontSets[CharIn].TexSizeX] = (i>=bitmap.width || j<(FontSets[CharIn].TexSizeY-bitmap.rows)) ? 0 : bitmap.buffer[i + bitmap.width*(j-FontSets[CharIn].TexSizeY+bitmap.rows)];
		}
	}
	/*for(int j=FontSets[CharIn].TexSizeY-Ymove; j <FontSets[CharIn].TexSizeY;j++) {
		for(int i=0; i < FontSets[CharIn].TexSizeX; i++){
			FontDataTMP[i+(j)*FontSets[CharIn].TexSizeX] = 0;
		}
	}*/

	//glDisable(GL_TEXTURE_2D);
	//glEnable(GL_TEXTURE_RECTANGLE);
	glGenTextures( 1, &FontSets[CharIn].TexID );
	glBindTexture(GL_TEXTURE_2D, FontSets[CharIn].TexID);
	glTexImage2D(GL_TEXTURE_2D,0, GL_ALPHA, FontSets[CharIn].TexSizeX, FontSets[CharIn].TexSizeY, 0,GL_ALPHA, GL_UNSIGNED_BYTE, FontDataTMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


	//glDisable(GL_TEXTURE_RECTANGLE);
}


void CFONTS2D::DrawTexts(const wchar_t * CharIn,int PosX,int PosY,int WinW,int WinH,int LineW,int lineH)
{
	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_TEXTURE_2D); glEnable(GL_TEXTURE_RECTANGLE);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   ); glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);glPushMatrix();GLfloat DrawTextMatrix[16]; CO_MatrixOrthogonalProjection(0.0f,(float)WinW,0.0f,(float)WinH,-1.0f,1.0f,DrawTextMatrix); glLoadMatrixf(DrawTextMatrix);
	glMatrixMode(GL_MODELVIEW); glPushMatrix();glLoadIdentity(); //glTranslatef((float)PosX,(float)PosY,0.0f);
	//DrawQUAD(0.0f,100.0f,100.0f,0.0f,10,10);
	if(!CharIn) return;
	int CharInCount=GetCharLenth(CharIn);
	float DrawX=float(PosX);float DrawY=float(PosY);
	float MaxLineY=0.0f;
	for (int i=0;i<CharInCount;i++)
	{
		SetCharTex(CharIn[i]);
		glBindTexture(GL_TEXTURE_2D, FontSets[CharIn[i]].TexID);
		MaxLineY=max(MaxLineY,float(FontSets[CharIn[i]].SizeH));
		if(LineW<=(DrawX+float(FontSets[CharIn[i]].SizeW)))
		{
			DrawY=DrawY-MaxLineY;
			DrawX=float(PosX);
		}
		DrawQUAD(
			DrawX,
			DrawX+float(FontSets[CharIn[i]].SizeW),
			DrawY+float(FontSets[CharIn[i]].SizeH+FontSets[CharIn[i]].MoveY),
			DrawY+(float)FontSets[CharIn[i]].MoveY,
			float(FontSets[CharIn[i]].SizeW)/(float)FontSets[CharIn[i]].TexSizeX,
			float(FontSets[CharIn[i]].SizeH)/(float)FontSets[CharIn[i]].TexSizeY
			);
		
		//DrawQUAD(DrawX,DrawX+float(FontSets[CharIn[i]].SizeW),DrawY+float(FontSets[CharIn[i]].SizeH),DrawY,(float)FontSets[CharIn[i]].TexSizeX,(float)FontSets[CharIn[i]].TexSizeY);
		DrawX=DrawX+float(FontSets[CharIn[i]].SizeW)+2.0f;
	}
	glMatrixMode(GL_MODELVIEW);glPopMatrix();
	glMatrixMode(GL_PROJECTION);glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//glDisable(GL_TEXTURE_RECTANGLE);
	glEnable(GL_DEPTH_TEST);
}
