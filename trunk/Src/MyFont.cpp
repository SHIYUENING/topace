#include "MyFont.h"
CMyFont::CMyFont(void)
:WordNum(0)
,WordList(0)
,ifloadedFont(false)
{
	OneFontpixels = new unsigned char[0x1000];
	WordList=glGenLists(1);
	glNewList(WordList,GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,1.0f);glVertex2f(0.0f,1.0f);
			glTexCoord2f(0.0f,0.0f);glVertex2f(0.0f,0.0f);
			glTexCoord2f(1.0f,0.0f);glVertex2f(1.0f,0.0f);
			glTexCoord2f(1.0f,1.0f);glVertex2f(1.0f,1.0f);
		glEnd();
	glEndList();
		
}

CMyFont::~CMyFont(void)
{
	delete [] OneFontpixels;
	delete [] MyFontpixels;
	ClearTXT();
	glDeleteLists(WordList,1);
}

bool CMyFont::LoadFont(const char *filename)
{
	FILE	*m_FilePointer;
	m_FilePointer= new FILE;
	if ((m_FilePointer=fopen(filename,"rb"))==NULL)
	{
		return false;	// 打开文件失败
	}

	unsigned int filesize = 0;
	while (!feof(m_FilePointer))
	{
		fgetc(m_FilePointer);
		filesize++;
	}
	filesize--;
	rewind(m_FilePointer);
	if(filesize==0xFF900)
	{
		MyFontpixels = new unsigned char[filesize];
		fread( MyFontpixels, 1, filesize, m_FilePointer );
		fclose(m_FilePointer);
		ifloadedFont=true;
		return true;
	}

	return false;
}

int CMyFont::GetFontIndex(BYTE InH,BYTE InL)
{

	return (InH-0xA1)*(0xFE-0xA1+1)+InL-0xA1;
}

unsigned int CMyFont::CreatFont(int FontIndex)
{
	for(int i=0;i<0x80;i++)
	{
		BYTE pixels8 = MyFontpixels[FontIndex*0x80+i];
		bool bpixels[8];
		/*
		bpixels[0] = bool(pixels8 & 1);
		bpixels[1] = bool(pixels8 & 2);
		bpixels[2] = bool(pixels8 & 4);
		bpixels[3] = bool(pixels8 & 8);
		bpixels[4] = bool(pixels8 & 0x10);
		bpixels[5] = bool(pixels8 & 0x20);
		bpixels[6] = bool(pixels8 & 0x40);
		bpixels[7] = bool(pixels8 & 0x80);
		*/

		bpixels[7] = bool(pixels8 & 1);
		bpixels[6] = bool(pixels8 & 2);
		bpixels[5] = bool(pixels8 & 4);
		bpixels[4] = bool(pixels8 & 8);
		bpixels[3] = bool(pixels8 & 0x10);
		bpixels[2] = bool(pixels8 & 0x20);
		bpixels[1] = bool(pixels8 & 0x40);
		bpixels[0] = bool(pixels8 & 0x80);
		for(int j=0;j<8;j++)
		{

			OneFontpixels[i*0x20+j*4+0]=0xFF;
			OneFontpixels[i*0x20+j*4+1]=0xFF;
			OneFontpixels[i*0x20+j*4+2]=0xFF;
			if(bpixels[j])
				OneFontpixels[i*0x20+j*4+3]=0xFF;
			else
				OneFontpixels[i*0x20+j*4+3]=0x0;
		}
	}
	unsigned int FontTexID;
	glGenTextures(1, &FontTexID);				// 创建一个纹理
	glBindTexture(GL_TEXTURE_2D, FontTexID);			// 构造纹理
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 32, 32, GL_RGBA, GL_UNSIGNED_BYTE, OneFontpixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	return FontTexID;

}

void CMyFont::inputTxt(const char * Chars)
{
	if(!ifloadedFont)
		return;
	ClearTXT();
	WordNum=strlen(Chars)/2;
	if(WordNum<1)
		return;
	TXTTexIDs=new unsigned int[WordNum*sizeof(unsigned int)];
	for(unsigned int i=0;i<WordNum;i++)
	{
		//if(Chars[i*2]*Chars[i*2+1]==0)
			//return;
		TXTTexIDs[i]=CreatFont(GetFontIndex(Chars[i*2],Chars[i*2+1]));
	}
}

void CMyFont::ClearTXT(void)
{
	if(WordNum<1)
		return;
	for(unsigned int i=0;i<WordNum;i++)
	{
		if(TXTTexIDs[i]!=0)
		glDeleteTextures(1,&TXTTexIDs[i]);
	}
	delete [] TXTTexIDs;
}

void CMyFont::DrawTXT(int WinW, int WinH, int PosX, int PosY, int SizeW, int SizeH,int WordRightLimit)
{
	if(WordNum<1)
		return;
	int WinPosX=0;
	int WinPosY=WinH;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
				// Select Our Font Texture
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,WinW,0,WinH,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	for(unsigned int i=0;i<WordNum;i++)
	{
		glBindTexture(GL_TEXTURE_2D, TXTTexIDs[i]);
		glLoadIdentity();
		WinPosX=WinPosX+SizeW;
		if(WinPosX>(WordRightLimit-PosX))
		{
			WinPosX=0;
			WinPosY=WinPosY-SizeH;
		}
		glTranslated(WinPosX+PosX,WinPosY-PosY,0);
		//glScaled(SizeW,SizeH,0.0);
		//glCallList(WordList);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,1.0f);glVertex2i(-SizeW/2,-SizeH/2);
				glTexCoord2f(1.0f,1.0f);glVertex2i( SizeW/2,-SizeH/2);
				glTexCoord2f(1.0f,0.0f);glVertex2i( SizeW/2, SizeH/2);
				glTexCoord2f(0.0f,0.0f);glVertex2i(-SizeW/2, SizeH/2);
			glEnd();
	
	}


	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}
