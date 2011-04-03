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
	,DrawCount(0)
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
	FontSizeFX=FontW;
	FontSizeFY=FontH;
	if(FontDataTMP_FullWidth) delete [] FontDataTMP_FullWidth;
	FontDataTMP_FullWidth = new unsigned char[next_p2(FontW)*next_p2(FontH)*2];
	ZeroMemory(FontDataTMP_FullWidth,next_p2(FontW)*next_p2(FontH)*2);
	for(int i=0x100;i<0xFFFF;i++)
	{
		if(FontSets[i].TexID!=0)
			glDeleteTextures(1, &FontSets[i].TexID);
		FontSets[i].TexID=0;
	}
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
	FontSizeHX=FontW;
	FontSizeHY=FontH;
	if(FontDataTMP_HalfWidth) delete [] FontDataTMP_HalfWidth;
	FontDataTMP_HalfWidth = new unsigned char[next_p2(FontW)*next_p2(FontH)*2];
	ZeroMemory(FontDataTMP_HalfWidth,next_p2(FontW)*next_p2(FontH)*2);
	for(int i=0;i<0x100;i++)
	{
		if(FontSets[i].TexID!=0)
			glDeleteTextures(1, &FontSets[i].TexID);
		FontSets[i].TexID=0;
	}
	return true;
}
FT_Error Old_FT_Outline_Embolden( FT_Outline*  outline, FT_Pos strength )
{
    FT_Vector*    points;
    FT_Vector    v_prev, v_first, v_next, v_cur;
    FT_Angle    rotate, angle_in, angle_out;
    FT_Int        c, n, first;
    FT_Int        orientation;

    if ( !outline )
        return FT_Err_Invalid_Argument;

    strength /= 2;
    if ( strength == 0 )
        return FT_Err_Ok;

    orientation = FT_Outline_Get_Orientation( outline );
    if ( orientation == FT_ORIENTATION_NONE )
    {
        if ( outline->n_contours )
            return FT_Err_Invalid_Argument;
        else
            return FT_Err_Ok;
    }

    if ( orientation == FT_ORIENTATION_TRUETYPE )
        rotate = -FT_ANGLE_PI2;
    else
        rotate = FT_ANGLE_PI2;

    points = outline->points;

    first = 0;
    for ( c = 0; c < outline->n_contours; c++ )
    {
        int  last = outline->contours[c];

        v_first = points[first];
        v_prev  = points[last];
        v_cur   = v_first;

        for ( n = first; n <= last; n++ )
        {
            FT_Vector    in, out;
            FT_Angle    angle_diff;
            FT_Pos        d;
            FT_Fixed    scale;

            if ( n < last )
                v_next = points[n + 1];
            else
                v_next = v_first;

            /* compute the in and out vectors */
            in.x = v_cur.x - v_prev.x;
            in.y = v_cur.y - v_prev.y;

            out.x = v_next.x - v_cur.x;
            out.y = v_next.y - v_cur.y;

            angle_in   = FT_Atan2( in.x, in.y );
            angle_out  = FT_Atan2( out.x, out.y );
            angle_diff = FT_Angle_Diff( angle_in, angle_out );
            scale      = FT_Cos( angle_diff / 2 );

            if ( scale < 0x4000L && scale > -0x4000L )
                in.x = in.y = 0;
            else
            {
                d = FT_DivFix( strength, scale );

                FT_Vector_From_Polar( &in, d, angle_in + angle_diff / 2 - rotate );
            }

            outline->points[n].x = v_cur.x + strength + in.x;
            //伀偙傟傪僐儊儞僩傾僂僩偟偨偩偗
            //outline->points[n].y = v_cur.y + strength + in.y;

            v_prev = v_cur;
            v_cur  = v_next;
        }

        first = last + 1;
    }

    return FT_Err_Ok;
}
void CFONTS2D::SetCharTex(const wchar_t CharIn)
{
	if(CharIn==0x0D) return;
	if(CharIn==0x0A) return;
	if((!Face_FullWidth)&&(!Face_HalfWidth)) return;
	FT_Glyph glyph;
	FT_BitmapGlyph bitmap_glyph;
	if(FontSets[CharIn].TexID) return;
	face=CharIn>=0xff?Face_FullWidth:Face_HalfWidth;
	if(!Face_FullWidth) face=Face_HalfWidth;
	if(!Face_HalfWidth) face=Face_FullWidth;
	FontSets[CharIn].TexSizeX=face==Face_FullWidth?FontSizeFX:FontSizeHX;FontSets[CharIn].TexSizeX=next_p2(FontSets[CharIn].TexSizeX);
	FontSets[CharIn].TexSizeY=face==Face_FullWidth?FontSizeFY:FontSizeHY;FontSets[CharIn].TexSizeY=next_p2(FontSets[CharIn].TexSizeY);
	unsigned char* FontDataTMP=face==Face_FullWidth?FontDataTMP_FullWidth:FontDataTMP_HalfWidth;
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, CharIn ), FT_LOAD_DEFAULT )) return;
	Old_FT_Outline_Embolden( &(face->glyph->outline), 30 );
    if(FT_Get_Glyph( face->glyph, &glyph )) return;
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    bitmap_glyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;
	FontSets[CharIn].SizeW=bitmap.width;
	FontSets[CharIn].SizeH=bitmap.rows;
	if(CharIn==L' ') 
		FontSets[CharIn].SizeW=(face==Face_FullWidth?FontSizeFX:FontSizeHX)/2;
	if(CharIn==L'　') 
		FontSets[CharIn].SizeW=(face==Face_FullWidth?FontSizeFX:FontSizeHX);
	int Ymove=0;
	//if(CharIn<0xFF)
	//	Ymove=FontSets[CharIn].TexSizeY/20;
	//if(CharIn==L'-')
	//	Ymove=FontSets[CharIn].TexSizeY/2-bitmap.rows*2;
	//if(CharIn==L'.')
	//	Ymove=bitmap.rows/2;
	if(CharIn<0xFF) FontSets[CharIn].MoveY=bitmap.rows/6;
	if(CharIn==L'-') FontSets[CharIn].MoveY=FontSets[CharIn].TexSizeY/2-bitmap.rows*2;
	if(CharIn==L'.') FontSets[CharIn].MoveY=bitmap.rows/2;
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


void CFONTS2D::DrawTexts(const wchar_t * CharIn,int PosX,int PosY,int WinW,int WinH,int LineW,int lineH,float IntervalW)
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
		FontSets[CharIn[i]].UseCount++;
		glBindTexture(GL_TEXTURE_2D, FontSets[CharIn[i]].TexID);
		MaxLineY=max(MaxLineY,float(FontSets[CharIn[i]].SizeH));
		if((LineW<=(DrawX+float(FontSets[CharIn[i]].SizeW)))||(CharIn[i]==0x0A))
		{
			DrawY=DrawY-(lineH==0?MaxLineY:(float)lineH);
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
		DrawX=DrawX+float(FontSets[CharIn[i]].SizeW)-IntervalW;
		if((CharIn[i]!=L' ')&&(CharIn[i]!=L'　')) DrawX=DrawX+IntervalW*2.0f;
	}
	glMatrixMode(GL_MODELVIEW);glPopMatrix();
	glMatrixMode(GL_PROJECTION);glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//glDisable(GL_TEXTURE_RECTANGLE);
	glEnable(GL_DEPTH_TEST);
}
