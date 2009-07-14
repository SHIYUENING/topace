#include "MyFont.h"
unsigned char * MyFontpixels;
unsigned char * OneFontpixels;
bool ifloadedFont=false;
void DeleteFont(void)
{
	delete [] OneFontpixels;
	delete [] MyFontpixels;
}
CMyFont::CMyFont(void)
:WordNum(0)
,TXTTexID(0)
{	
}

CMyFont::~CMyFont(void)
{

	glDeleteTextures(1,&TXTTexID);
}

bool CMyFont::LoadFont(const char *filename)
{

	if(TXTTexID!=0)
		glDeleteTextures(1,&TXTTexID);
	unsigned char* data;	
	data = new unsigned char[256*256*4];
	ZeroMemory(data,256*256*4);	// 清除存储区
	glGenTextures(1, &TXTTexID);				// 创建一个纹理
	glBindTexture(GL_TEXTURE_2D, TXTTexID);			// 构造纹理
	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, 256, 256,0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	delete [] data;

	if(!ifloadedFont)
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
			OneFontpixels=new unsigned char[0x1000];
			MyFontpixels = new unsigned char[filesize];
			fread( MyFontpixels, 1, filesize, m_FilePointer );
			fclose(m_FilePointer);
			ifloadedFont=true;
			return true;
		}
		return false;
	}
	return true;
}

int CMyFont::GetFontIndex(BYTE InH,BYTE InL)
{

	return (InH-0xA1)*(0xFE-0xA1+1)+InL-0xA1;
}

void CMyFont::CreatFont(int FontIndex,int FontInTexNum)
{
	if(FontInTexNum>=64)
		return;
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
	glBindTexture(GL_TEXTURE_2D, TXTTexID);
	glTexSubImage2D(GL_TEXTURE_2D,0,(FontInTexNum%8)*32,(FontInTexNum/8)*32,32,32,GL_RGBA,GL_UNSIGNED_BYTE,OneFontpixels);


}

void CMyFont::inputTxt(const char * Chars)
{
	if(!ifloadedFont)
		return;

	WordNum=0;
	WordNum=strlen(Chars)/2;
	if(WordNum<1)
		return;
	if(WordNum>64)
		WordNum=64;

	for(unsigned int i=0;i<WordNum;i++)
	{
		CreatFont(GetFontIndex(Chars[i*2],Chars[i*2+1]),i);
	}
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
	glBindTexture(GL_TEXTURE_2D, TXTTexID);
	for(unsigned int i=0;i<WordNum;i++)
	{
		glLoadIdentity();
		if(WordRightLimit>0)
		{
			if(WinPosX>(WordRightLimit-PosX-SizeW))
			{
				WinPosX=0;
				WinPosY=WinPosY-SizeH;
			}
		}

		if(WordRightLimit>0)
			glTranslated(WinPosX+PosX,WinPosY-PosY,0);
		else
			glTranslated(WinPosX+(WinW-WordNum*SizeW)/2+SizeW/2,WinPosY-PosY,0);
		float FontTexPosX=(float(i%8))/8.0f;
		float FontTexPosY=(float(i/8))/8.0f;
			glBegin(GL_QUADS);
				glTexCoord2f(FontTexPosX+0.0f,FontTexPosY+1.0f/8.0f);glVertex2i(-SizeW/2,-SizeH/2);
				glTexCoord2f(FontTexPosX+1.0f/8.0f,FontTexPosY+1.0f/8.0f);glVertex2i( SizeW/2,-SizeH/2);
				glTexCoord2f(FontTexPosX+1.0f/8.0f,FontTexPosY+0.0f);glVertex2i( SizeW/2, SizeH/2);
				glTexCoord2f(FontTexPosX+0.0f,FontTexPosY+0.0f);glVertex2i(-SizeW/2, SizeH/2);
			glEnd();
		WinPosX=WinPosX+SizeW;
	
	}


	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}
