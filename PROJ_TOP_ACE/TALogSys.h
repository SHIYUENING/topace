﻿//#pragma once
#ifndef TALOGSYS_H
#define TALOGSYS_H
#define DEFLOGFileName L ## "TOP_ACE_SYS.htm"
class CTALogSys
{
public:
	CTALogSys(void);
	~CTALogSys(void);
	bool AddLOG(const char * LOGStr,bool NoN=false);
	bool ADDhtmLog(const char * LOGStr,const char * LogColor=0 ,const char * LogLink=0);
	bool ADDLinkLOG(const char * LOGStr,const char * LogColor ,const char * LogLink);
	char * LOGString;
	wchar_t * LOGFileName;
	wchar_t * LOGFilePath;
	void ClearLOG();
	bool WriteLOGFile(bool ADD);
	void SetFileNameAndPath(wchar_t * FileName,wchar_t * FilePath);
};

#endif