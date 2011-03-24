#include "TALogSys.h"
#include "FileSysBace.h"
#include "CharSysBace.h"
#include <string.h>
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


bool CTALogSys::AddLOG(const char * LOGStr,bool NoN)
{
	if(!LOGStr)
		return false;
	if(GetCharLenth(LOGStr)==0)
		return false;
	char * StrTmp;
	if(!NoN)
	{
		StrTmp=ADDTwoChar(LOGString,"\n");
		delete [] LOGString;
		LOGString=StrTmp;
	}
	StrTmp=ADDTwoChar(LOGString,LOGStr);
	delete [] LOGString;
	LOGString=StrTmp;
	return true;
}
bool CTALogSys::ADDLinkLOG(const char * LOGStr,const char * LogColor ,const char * LogLink)
{
	if(!LOGStr) return false;
	if(GetCharLenth(LOGStr)==0) return false;
	if(!LogColor) return false;
	if(GetCharLenth(LogColor)==0) return false;
	if(!LogLink) return false;
	if(GetCharLenth(LogLink)==0) return false;
	char LogLinkPath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH,LogLinkPath);
	
	int StrTmpSize=
		GetCharLenth(LOGStr)+
		GetCharLenth(LogColor)+
		GetCharLenth(LogLink)*2+
		GetCharLenth(LogLinkPath)*2+
		GetCharLenth("<p><font color=%s>%s</font><a href=\"File%s%s\\%s\">%s\\%s</a></p>")+
		GetCharLenth(":\\localhost")+
		10;

	char * StrTmp= new char[StrTmpSize+1];StrTmp[StrTmpSize]=0;
	sprintf_s(
		StrTmp,
		StrTmpSize,
		"<p><font color=%s>%s</font><a href=\"File%s%s\\%s\">%s\\%s</a></p>",
		LogColor,
		LOGStr,
		":\\localhost\\",
		LogLinkPath,
		LogLink,
		LogLinkPath,
		LogLink
		);
	for(unsigned int i=0;i<GetCharLenth(StrTmp);i++)
	{
		if(StrTmp[i]=='\\') StrTmp[i]='/';
	}
	AddLOG(StrTmp);
	delete [] StrTmp;
	return true;
}

bool CTALogSys::ADDhtmLog(const char * LOGStr,const char * LogColor ,const char * LogLink)
{
	if(!LOGStr)
		return false;
	if(GetCharLenth(LOGStr)==0)
		return false;

	int StrTmpSize=GetCharLenth(LOGStr)+GetCharLenth(LogColor)+GetCharLenth(LogLink)+GetCharLenth("\n<p><a href=\"\"><font color=></font></a></p>")+5;
	char * StrTmp= new char[StrTmpSize+1];StrTmp[StrTmpSize]=0;
	//<p><a href="123"><font color=#FF0000>测试</font></a> </p>
	bool UseLogLink=false;
	if(LogLink) if(GetCharLenth(LogLink)) UseLogLink=true;
	bool UseLogColor=false;
	if(LogColor) if(GetCharLenth(LogColor)) UseLogColor=true;
	if(UseLogLink&&UseLogColor)		sprintf_s(StrTmp,StrTmpSize,"\n<p><a href=\"%s\"><font color=%s>%s</font></a></p>",LogLink,LogColor,LOGStr);
	if(UseLogLink)					sprintf_s(StrTmp,StrTmpSize,"\n<p><a href=\"%s\">%s</a></p>",LogLink,LOGStr);
	if(UseLogColor)					sprintf_s(StrTmp,StrTmpSize,"\n<p><font color=%s>%s</font></p>",LogColor,LOGStr);
	if((!UseLogLink)&&(!UseLogColor)) sprintf_s(StrTmp,StrTmpSize,"\n<p>%s</p>",LOGStr);
	AddLOG(StrTmp);
	delete [] StrTmp;
	return true;
}
bool ADD_LOG_Q(const wchar_t * LOGStr,const char * LogColor=0 ,const char * LogLink=0,wchar_t * LOGFileName=0,wchar_t * LOGFilePath=0,bool ADD=true)
{
	if(!LOGStr) return false;
	if(GetCharLenth(LOGStr)==0) return false;

	return true;
}
bool ADD_LOG_Q(const char * LOGStr,const char * LogColor ,const char * LogLink,wchar_t * LOGFileName,wchar_t * LOGFilePath,bool ADD)
{
	if(!LOGStr)
		return false;
	if(GetCharLenth(LOGStr)==0)
		return false;

	int StrTmpSize=GetCharLenth(LOGStr)+GetCharLenth(LogColor)+GetCharLenth(LogLink)+GetCharLenth("\n<p><a href=\"\"><font color=></font></a></p>")+5;
	char * StrTmp= new char[StrTmpSize+1];StrTmp[StrTmpSize]=0;
	//<p><a href="123"><font color=#FF0000>测试</font></a> </p>
	bool UseLogLink=false;
	if(LogLink) if(GetCharLenth(LogLink)) UseLogLink=true;
	bool UseLogColor=false;
	if(LogColor) if(GetCharLenth(LogColor)) UseLogColor=true;
	if(UseLogLink&&UseLogColor)		sprintf_s(StrTmp,StrTmpSize,"\n<p><a href=\"%s\"><font color=%s>%s</font></a></p>",LogLink,LogColor,LOGStr);
	if(UseLogLink)					sprintf_s(StrTmp,StrTmpSize,"\n<p><a href=\"%s\">%s</a></p>",LogLink,LOGStr);
	if(UseLogColor)					sprintf_s(StrTmp,StrTmpSize,"\n<p><font color=%s>%s</font></p>",LogColor,LOGStr);
	if((!UseLogLink)&&(!UseLogColor)) sprintf_s(StrTmp,StrTmpSize,"\n<p>%s</p>",LOGStr);
	if(LOGFileName)
		return WriteLocFile(LOGFileName,LOGFilePath,(unsigned char *)StrTmp,GetCharLenth(StrTmp),ADD);
	else
		return WriteLocFile(DEFLOGFileName,LOGFilePath,(unsigned char *)StrTmp,GetCharLenth(StrTmp),ADD);
	delete [] StrTmp;
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
		return WriteLocFile(DEFLOGFileName,LOGFilePath,(unsigned char *)LOGString,GetCharLenth(LOGString),ADD);
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





