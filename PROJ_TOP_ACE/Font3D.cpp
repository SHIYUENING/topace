#include "Font3D.h"

CFont3D::CFont3D(void)
: hDC(NULL)
, WordNum(0)
{
	for(unsigned int i=0;i<MAX_FONT_LIST;i++)
		FontList[i]=0;
	hDC=CreateDC( "DISPLAY", "", "", NULL );
}

CFont3D::~CFont3D(void)
{
	for(unsigned int i=0;i<MAX_FONT_LIST;i++)
		if(FontList[i]>0)
			glDeleteLists(FontList[i], 1);
}

bool CFont3D::LoadFont(const char * FontName,int CHARSET)
{
	HFONT	font;										// Windows Font ID
	font = CreateFont(	-MulDiv(16,GetDeviceCaps(hDC,LOGPIXELSY),72),//							// Height Of Font
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
int CFont3D::GetCharHex(char H,char L)
{
	if(L<0)
		return (256+H)*256+256+L;
	else
		return (256+H)*256+L;
}
void CFont3D::inputTxt(const char * Chars)
{
	if(!hDC)
		return;
	WordNum=0;
	WordNum=strlen(Chars);
	if(WordNum<1)
		return;
	if(WordNum>MAX_FONT_LIST)
		WordNum=MAX_FONT_LIST;
	for(unsigned int i=0;i<WordNum;i++)
	{
		if(FontList[i]>0)
			glDeleteLists(FontList[i], 1);
		FontList[i]=glGenLists(1);
		if(Chars[i]>0)
		wglUseFontOutlines(	hDC,							// Select The Current DC
							Chars[i],								// Starting Character
							1,							// Number Of Display Lists To Build
							FontList[i],							// Starting Display Lists
							0.0f,							// Deviation From The True Outlines
							0.2f,							// Font Thickness In The Z Direction
							WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
							&gmf[i]);
		else
		{
			i++;
			if(i<WordNum)
			{
				if(FontList[i]>0)
					glDeleteLists(FontList[i], 1);
					wglUseFontOutlines(	hDC,							// Select The Current DC
										GetCharHex(Chars[i-1],Chars[i]),								// Starting Character
										1,							// Number Of Display Lists To Build
										FontList[i-1],							// Starting Display Lists
										0.0f,							// Deviation From The True Outlines
										0.2f,							// Font Thickness In The Z Direction
										WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
										&gmf[i-1]);
			}
		}
	}
}

void CFont3D::DrawTXT(int WinW, int WinH, int PosX, int PosY, int SizeW, int SizeH,int WordRightLimit)
{
	glDisable(GL_BLEND);
	//glLoadIdentity();									// Reset The Current Modelview Matrix
	//glTranslatef(0.0f,0.0f,-15.0f);						// Move One Unit Into The Screen
	if(!hDC)
		return;
	float		length=0;	
	for (unsigned int loop=0;loop<WordNum;loop++)	// Loop To Find Text Length
	//{
		length+=gmf[loop].gmfCellIncX;			// Increase Length By Each Characters Width
	//}
	//glTranslatef(-length/2,0.0f,0.0f);
	glEnable(GL_MULTISAMPLE_ARB);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,WinW,0,WinH,-100,100);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();	
	glTranslatef(float(PosX),float(PosY)*1.004f,0.0f);
	glScaled(SizeW,SizeW,10.0);
	//
	for(unsigned int i=0;i<WordNum;i++)
	{
		if(FontList[i]>0)
			glCallList(FontList[i]);
	}
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDisable(GL_MULTISAMPLE_ARB);
}
