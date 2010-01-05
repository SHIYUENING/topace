#include "Font2D.h"

#pragma comment( lib, "freetype2311MT.lib" )
CFont2D::CFont2D(void)
: WordNum(0)
,face(NULL)
,library(NULL)
, TexID(0)
, FontCharSet(GB2312_CHARSET)
,FontPosX(0)
,FontPosY(0)
,FontTexW(DEFINE_FONT_W)
,FontTexH(DEFINE_FONT_H)
,OnefontData(NULL)
,OnefontW(DEFINE_FONT_W/8)
,OnefontH(DEFINE_FONT_W/8)
, CharNum(0)
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
	delete [] OnefontData;
	OnefontData=NULL;
}

bool CFont2D::LoadFont(const char * FontName,int FontSizeW,int FontSizeH,int FontW,int FontH,int CHARSET)
{
	glEnable( GL_TEXTURE_2D );
	FontTexW=next_p2(FontW);
	FontTexH=next_p2(FontH);
	OnefontW=FontTexW/8;
	OnefontH=FontTexH/8;

	FontCharSet=CHARSET;
	if (FT_Init_FreeType( &library ))
		return false;
	if (FT_New_Face( library, FontName, 0, &face )) 
		return false;
	if(FontSizeW<32)
		FT_Set_Char_Size( face, FontSizeW << 6, FontSizeH << 6, 66, 64);
	else
		FT_Set_Pixel_Sizes(face, min(FontSizeW,FontTexW/8), min(FontSizeH,FontTexH/8));
	unsigned char* data;
	data =new unsigned char[FontTexW*FontTexH*2];
	ZeroMemory(data,FontTexW*FontTexH*2);

	glGenTextures( 1, &TexID );
	glBindTexture(GL_TEXTURE_2D, TexID);			//
	glTexImage2D(GL_TEXTURE_2D,0, GL_ALPHA, FontTexW, FontTexH, 0,GL_ALPHA, GL_UNSIGNED_BYTE, data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	delete [] data;

	OnefontData = new unsigned char[OnefontW*OnefontH];
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
	CharNum=0;
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
void CFont2D::inputTxt(const wchar_t * Chars)
{
	CharNum=0;
	if(!face)
		return;
	if(!library)
		return;

	WordNum=0;
	WordNum=wcslen(Chars);
	if(WordNum<1)
		return;
	if(WordNum>MAX_FONT_LIST)
		WordNum=MAX_FONT_LIST;
	FontPosX=0;
	FontPosY=0;
	for(unsigned int i=0;i<WordNum;i++)
	{
//		if(Chars[i]>0)
//		{
			CharToImage(&Chars[i]);
//		}
//		else
//		{
//			i++;
//			if(i<WordNum)
//			{
//				CharToImage(&Chars[i-1],2);
//			}
//		}
	}


}
void CFont2D::DrawTXT(int WinW, int WinH, int PosX, int PosY, int SizeW, int SizeH,int WordRightLimit,int Pitch)
{
	if(WordNum<1)
		return;
	int WinPosX=0;
	int WinPosY=WinH;
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );

	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,WinW,0,WinH,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glBindTexture(GL_TEXTURE_2D, TexID);
	for(unsigned int i=0;i<WordNum;i++)
	{
		int thisFontW=int(float(SizeW)*OneCharWidth[i]);
		glLoadIdentity();
		if(WordRightLimit>0)
		{
			if(WinPosX>=(WordRightLimit-PosX-thisFontW))
			{
				WinPosX=0;
				WinPosY=WinPosY-SizeH;
			}
		}
		else
		{
			if(WinPosX>=WinW)
			{
				WinPosX=0;
				WinPosY=WinPosY-SizeH;
			}
		}
		WinPosX=WinPosX+thisFontW+Pitch;

		if(WordRightLimit>0)
			glTranslated(WinPosX+PosX,WinPosY-PosY,0);
		else
			glTranslated(WinPosX+(WinW-WordNum*SizeW)/2+SizeW/2,WinPosY-PosY,0);
		float FontTexPosX=(float(i%8))/8.0f;
		float FontTexPosY=(float(i/8))/8.0f;
			glBegin(GL_QUADS);
				glTexCoord2f(FontTexPosX+0.0f,		FontTexPosY+1.0f/8.0f);	glVertex2i(-thisFontW,-SizeH);
				glTexCoord2f(FontTexPosX+OneCharWidth[i]/8.0f,	FontTexPosY+1.0f/8.0f);	glVertex2i( 0,-SizeH);
				glTexCoord2f(FontTexPosX+OneCharWidth[i]/8.0f,	FontTexPosY+0.0f);		glVertex2i( 0, 0);
				glTexCoord2f(FontTexPosX+0.0f,		FontTexPosY+0.0f);		glVertex2i(-thisFontW, 0);
			glEnd();
		

	}
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);	
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
	FT_Outline_Embolden( &(face->glyph->outline), 30 );
	FT_Glyph glyph;
    if(FT_Get_Glyph( face->glyph, &glyph ))
		return;
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;

	if(bitmap.width>=OnefontW)
		OneCharWidth[CharNum]=1.0f;
	else
		OneCharWidth[CharNum]=float(bitmap.width)/float(OnefontW);
	if(Chars[0]==0x20)
		OneCharWidth[CharNum]=0.5f;

	CharNum=CharNum+1;
	int Ymove=0;
	if(Chars[0]>0)
		Ymove=bitmap.rows/6;
	if(Chars[0]=='-')
		Ymove=OnefontH/2-bitmap.rows*2;
	if(Chars[0]=='.')
		Ymove=bitmap.rows/2;
	for(int j=Ymove; j <OnefontH;j++) {
		for(int i=0; i < OnefontW; i++){
			OnefontData[i+(j-Ymove)*OnefontW] = (i>=bitmap.width || j<(OnefontH-bitmap.rows)) ? 0 : bitmap.buffer[i + bitmap.width*(j-OnefontH+bitmap.rows)];
		}
	}
	for(int j=OnefontH-Ymove; j <OnefontH;j++) {
		for(int i=0; i < OnefontW; i++){
			OnefontData[i+(j)*OnefontW] = 0;
		}
	}
	glBindTexture(GL_TEXTURE_2D, TexID);
	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,
		FontPosX,
		FontPosY,
		OnefontW,
		OnefontH,
		GL_ALPHA,
		GL_UNSIGNED_BYTE,
		OnefontData);

	FontPosX=FontPosX+OnefontW;
	if(FontPosX>=FontTexW)
	{
		FontPosX=0;
		FontPosY=FontPosY+OnefontH;
		if(FontPosY>=FontTexH)
			FontPosY=FontTexH;
	}
	FT_Done_Glyph(glyph);

}

void CFont2D::CharToImage(const wchar_t * Chars)
{
	//	wchar_t InputChar;
//	MultiByteToWideChar(CP_ACP,0,Chars,byteNum,&InputChar,1);
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, Chars[0] ), FT_LOAD_DEFAULT ))
		return;
	FT_Outline_Embolden( &(face->glyph->outline), 30 );
	FT_Glyph glyph;
    if(FT_Get_Glyph( face->glyph, &glyph ))
		return;
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;

	if(bitmap.width>=OnefontW)
		OneCharWidth[CharNum]=1.0f;
	else
		OneCharWidth[CharNum]=float(bitmap.width)/float(OnefontW);
	if(Chars[0]==L' ')
		OneCharWidth[CharNum]=0.5f;

	CharNum=CharNum+1;

	int Ymove=0;
	if(Chars[0]<0x80)
		Ymove=bitmap.rows/6;
	if(Chars[0]==L'-')
		Ymove=OnefontH/2-bitmap.rows*2;
	if(Chars[0]==L'.')
		Ymove=bitmap.rows/2;

	for(int j=Ymove; j <OnefontH;j++) {
		for(int i=0; i < OnefontW; i++){
			OnefontData[i+(j-Ymove)*OnefontW] = (i>=bitmap.width || j<(OnefontH-bitmap.rows)) ? 0 : bitmap.buffer[i + bitmap.width*(j-OnefontH+bitmap.rows)];
		}
	}
	for(int j=OnefontH-Ymove; j <OnefontH;j++) {
		for(int i=0; i < OnefontW; i++){
			OnefontData[i+(j)*OnefontW] = 0;
		}
	}
	glBindTexture(GL_TEXTURE_2D, TexID);
	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,
		FontPosX,
		FontPosY,
		OnefontW,
		OnefontH,
		GL_ALPHA,
		GL_UNSIGNED_BYTE,
		OnefontData);

	FontPosX=FontPosX+OnefontW;
	if(FontPosX>=FontTexW)
	{
		FontPosX=0;
		FontPosY=FontPosY+OnefontH;
		if(FontPosY>=FontTexH)
			FontPosY=FontTexH;
	}
	FT_Done_Glyph(glyph);
}