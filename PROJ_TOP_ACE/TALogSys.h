//#pragma once
#ifndef TALOGSYS_H
#define TALOGSYS_H

class CTALogSys
{
public:
	CTALogSys(void);
	~CTALogSys(void);
	bool AddLOG(const char * LOGStr);
	char * LOGString;
	wchar_t * LOGFileName;
	wchar_t * LOGFilePath;
	void ClearLOG();
	bool WriteLOGFile(bool ADD);
	void SetFileNameAndPath(wchar_t * FileName,wchar_t * FilePath);
};

#endif