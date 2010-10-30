#include "TALogSys.h"
#include "FileSysBace.h"
#include "CharSysBace.h"
CTALogSys::CTALogSys(void)
	:LOGString(NULL)
	,LOGFileName(NULL)
	,LOGFilePath(NULL)
{
}


CTALogSys::~CTALogSys(void)
{
	ClearLOG();
}


bool CTALogSys::AddLOG(const char * LOGStr)
{
	if(!LOGStr)
		return false;
	if(GetCharLenth(LOGStr)==0)
		return false;
	char * StrTmp;
	StrTmp=ADDTwoChar(LOGString," \n ");
	delete [] LOGString;
	LOGString=StrTmp;
	StrTmp=ADDTwoChar(LOGString,LOGStr);
	delete [] LOGString;
	LOGString=StrTmp;
	return true;
}
void CTALogSys::ClearLOG()
{
	delete [] LOGString;
	delete [] LOGFileName;
	delete [] LOGFilePath;
	LOGString=NULL;
	LOGFileName=NULL;
	LOGFilePath=NULL;
}
bool CTALogSys::WriteLOGFile(bool ADD)
{
	if(LOGFileName)
		return WriteLocFile(LOGFileName,LOGFilePath,(unsigned char *)LOGString,GetCharLenth(LOGString),ADD);
	else
		return WriteLocFile(L"LOG.log",LOGFilePath,(unsigned char *)LOGString,GetCharLenth(LOGString),ADD);
}
void CTALogSys::SetFileNameAndPath(wchar_t * FileName,wchar_t * FilePath)
{
	if(FileName)
	{
		if(LOGFileName)
			delete [] LOGFileName;
		LOGFileName = FileName;
	}
	if(FilePath)
	{
		if(LOGFilePath)
			delete [] LOGFilePath;
		LOGFilePath = FilePath;
	}
}