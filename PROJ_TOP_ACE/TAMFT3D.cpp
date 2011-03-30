#include "TAMFT3D.h"
#include "TALogSys.h"

CTAMFT3D::CTAMFT3D(void)
	: Font3DFile(NULL)
	, pTAMFT3D_FileHead(NULL)
	, isRAM(false)
	, isVRAM(false)
	, VBOID(0)
	, TotelVecNum(0)
	, TotelFaceNum(0)
{
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
	return true;
}


bool CTAMFT3D::ToVRAM(void)
{
	for(int i=0;i<0x10000;i++)
	{
		TotelVecNum=TotelVecNum+pTAMFT3D_FileHead->CharSet[i].VecNum;
		TotelFaceNum=TotelFaceNum+pTAMFT3D_FileHead->CharSet[i].FaceNum;
	}
	float * VecBufferTMP=new float[TotelVecNum*3];
	//glGenBuffersARB (1,&VBOID);
	//glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOID );
	//glBufferDataARB( GL_ARRAY_BUFFER_ARB, pTAMFT3D_FileHead->FontFileSize-sizeof(_TAMFT3D_FileHead), pTAMFT3D_FileHead+sizeof(_TAMFT3D_FileHead), GL_STATIC_DRAW_ARB );
	return false;
}
