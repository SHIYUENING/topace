#include "TAMFT3D.h"
#include "TALogSys.h"
#include "CharSysBace.h"
float ASCIICharWides[0x100];
CTAMFT3D::CTAMFT3D(void)
	: Font3DFile(NULL)
	, pTAMFT3D_FileHead(NULL)
	, isRAM(false)
	, VBOID(0)
	, MaxVecNum(0)
	, MaxFaceNum(0)
	, RenderFaceNum(0)
{
	for(int i=0;i<0x10000;i++)
		CharVBOID_indexs[i]=0;
	for(int i=0;i<VBOID_NUM;i++)
	{
		CharVBO[i].Face=0;
		CharVBO[i].Vec=0;
		CharVBO[i].NoDrawTimes=0;
	}
}


CTAMFT3D::~CTAMFT3D(void)
{
	if (Font3DFile) delete [] Font3DFile;
}


bool CTAMFT3D::LoadFontFile(void)
{
	if(Font3DFile) return false;
	HANDLE   hFile; 
	CTALogSys TAMFT3DLOG;
	hFile   =   CreateFileW(TAMFT3D_FILE_PATH,  
                                  GENERIC_READ, 
                                  FILE_SHARE_READ,   
                                  NULL,    
                                  OPEN_EXISTING,
                                  FILE_ATTRIBUTE_NORMAL,  
                                  NULL);
	if   (hFile   ==   INVALID_HANDLE_VALUE)  
	{
		CloseHandle(hFile);
		TAMFT3DLOG.ADDhtmLog("3DFont Read Error.","#FF0000");
		TAMFT3DLOG.WriteLOGFile(true);
		return false;
	}
	int FileSize = GetFileSize(hFile, NULL);
	if(FileSize<=sizeof(_TAMFT3D_FileHead))
	{
		CloseHandle(hFile);
		TAMFT3DLOG.ADDhtmLog("3DFont Size Error.","#FF0000");
		TAMFT3DLOG.WriteLOGFile(true);
		return false;
	}
	
	_TAMFT3D_FileHead TAMFT3D_FileHead;
	DWORD Readedsize=0;
	BOOL ReadStates=ReadFile(hFile,&TAMFT3D_FileHead,sizeof(TAMFT3D_FileHead),&Readedsize,NULL);
	if(!ReadStates)
	{
		CloseHandle(hFile);
		TAMFT3DLOG.ADDhtmLog("3DFont file head read Error.","#FF0000");
		TAMFT3DLOG.WriteLOGFile(true);
		return false;
	}
	if(Readedsize!=sizeof(TAMFT3D_FileHead))
	{
		CloseHandle(hFile);
		TAMFT3DLOG.ADDhtmLog("3DFont file head read size Error.","#FF0000");
		TAMFT3DLOG.WriteLOGFile(true);
		return false;
	}
	if(TAMFT3D_FileHead.FontVer!=TAMFT3D_Ver)
	{
		CloseHandle(hFile);
		ADD_LOG_Q("3DFont file Ver Error","#FF0000");
		return false;
	}
	if(FileSize!=TAMFT3D_FileHead.FontFileSize)
	{
		CloseHandle(hFile);
		TAMFT3DLOG.ADDhtmLog("3DFont file size Error.","#FF0000");
		TAMFT3DLOG.WriteLOGFile(true);
		return false;
	}
	Font3DFile=new unsigned char[FileSize];
	Readedsize=0;
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	ReadStates=ReadFile(hFile,Font3DFile,FileSize,&Readedsize,NULL);
	if(FileSize!=Readedsize)
	{
		delete [] Font3DFile;
		Font3DFile=NULL;
		CloseHandle(hFile);
		TAMFT3DLOG.ADDhtmLog("3DFont file size Error.","#FF0000");
		TAMFT3DLOG.WriteLOGFile(true);
		return false;
	}
	CloseHandle(hFile);
	pTAMFT3D_FileHead=(_TAMFT3D_FileHead *)Font3DFile;
	isRAM=true;
	for(int i=0;i<0x10000;i++)
	{
		MaxVecNum=max(MaxVecNum,pTAMFT3D_FileHead->CharSet[i].VecNum);
		MaxFaceNum=max(MaxFaceNum,pTAMFT3D_FileHead->CharSet[i].FaceNum);
	}
	return true;
}


void CTAMFT3D::DrawOneChar(wchar_t DrawChar)
{
	if((!CharVBOID_indexs[DrawChar])||(CharVBO[CharVBOID_indexs[DrawChar]].Face==0))
	{
		CharVBOID_indexs[DrawChar]=CharToVRAM(DrawChar);
	}
	_CharVBO * CharVBOTMP=CharVBO+CharVBOID_indexs[DrawChar];
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_INDEX_ARRAY );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, CharVBOTMP->Vec );
	glVertexPointer( 3, GL_FLOAT, 0, 0 );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, CharVBOTMP->Face );
	//glIndexPointer(GL_UNSIGNED_INT,0,0);
	glDrawElements(GL_TRIANGLES,(pTAMFT3D_FileHead->CharSet[DrawChar].FaceNum)*3,GL_UNSIGNED_INT,0);
	
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_INDEX_ARRAY );
	
	CharVBO[CharVBOID_indexs[DrawChar]].NoDrawTimes=1;
	RenderFaceNum=RenderFaceNum+pTAMFT3D_FileHead->CharSet[DrawChar].FaceNum;
	
}

void CTAMFT3D::Draw3DText(wchar_t * DrawChar,float FontW,float FontH,float LineW,float lineH,float IntervalW)
{
	RenderFaceNum=0;
	if(!DrawChar) return;
	if(!GetCharLenth(DrawChar)) return;
	if(!isRAM) return;
	if(!pTAMFT3D_FileHead) return;
	
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDisable( GL_CULL_FACE );
	int CharIndex=0;
	for(int i=0;i<VBOID_NUM;i++)
	{
		CharVBO[i].NoDrawTimes++;
	}
	float LinePosX=0.0f;
	float LinePosY=0.0f;
	while(DrawChar[CharIndex])
	{
		glPushMatrix();
		glTranslatef(LinePosX,LinePosY,0.0f);
		glScalef(FontW,FontH,1.0f);
		if(DrawChar[CharIndex]>=0x20)
		LinePosX=LinePosX+IntervalW+(DrawChar[CharIndex]>=0x100?1.0f:0.75f)*FontW;
		if(LinePosX>LineW)
		{
			LinePosX=0;
			LinePosY=LinePosY-max(FontH,lineH);
		}
		DrawOneChar(DrawChar[CharIndex]);
		CharIndex++;
		glPopMatrix();
	}
	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
}


unsigned int CTAMFT3D::CharToVRAM(wchar_t DrawChar)
{
	unsigned int MaxCharNoDrawTime=0;
	unsigned int CharVBOIndexTMP=0;
	_CharSet * CharSetTMP=pTAMFT3D_FileHead->CharSet+DrawChar;
	for(int i=1;i<VBOID_NUM;i++)
	{
		if(MaxCharNoDrawTime<CharVBO[i].NoDrawTimes) CharVBOIndexTMP=i;
		MaxCharNoDrawTime=max(MaxCharNoDrawTime,CharVBO[i].NoDrawTimes);
		if(!CharVBO[i].Face)
		{
			CharVBOIndexTMP=i;
			break;
		}
	}
	unsigned int VecDataBuffer=(unsigned int)CharSetTMP->VecData+(unsigned int)pTAMFT3D_FileHead;
	unsigned int FaceDataBuffer=(unsigned int)VecDataBuffer+CharSetTMP->VecNum*3*sizeof(float);
	float * TestData=(float *)VecDataBuffer;
	unsigned int * TestData2=(unsigned int *)FaceDataBuffer;
	ClearOneCharVBO(CharVBOIndexTMP);
	glGenBuffersARB( 1,&CharVBO[CharVBOIndexTMP].Vec);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, CharVBO[CharVBOIndexTMP].Vec );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, CharSetTMP->VecNum*3*sizeof(float), (void*)VecDataBuffer, GL_STATIC_DRAW_ARB );
	glGenBuffersARB( 1,&CharVBO[CharVBOIndexTMP].Face);
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, CharVBO[CharVBOIndexTMP].Face );
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, CharSetTMP->FaceNum*3*sizeof(int), (void*)FaceDataBuffer, GL_STATIC_DRAW_ARB );
	CharVBO[CharVBOIndexTMP].NoDrawTimes=1;
	return CharVBOIndexTMP;
}


void CTAMFT3D::ClearOneCharVBO(unsigned int VBOIndex)
{
	if(CharVBO[VBOIndex].Face)
	{
		if(glIsBufferARB(CharVBO[VBOIndex].Face))
			glDeleteBuffersARB(1,&(CharVBO[VBOIndex].Face));
		CharVBO[VBOIndex].Face=0;
	}
	if(CharVBO[VBOIndex].Vec)
	{
		if(glIsBufferARB(CharVBO[VBOIndex].Vec))
			glDeleteBuffersARB(1,&(CharVBO[VBOIndex].Vec));
		CharVBO[VBOIndex].Vec=0;
	}
	CharVBO[VBOIndex].NoDrawTimes=0;
}



void CTAMFT3D::ClearAllVBO(void)
{
	for(int i=0;i<VBOID_NUM;i++)
	{
		ClearOneCharVBO(i);
	}
}
