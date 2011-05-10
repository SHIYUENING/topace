#include "TamScene.h"

WIN32_FIND_DATAW   filedata; 
wchar_t * FindFileWithExtName(wchar_t * ExtName)
{
	if(!ExtName) return 0;
	if(!GetCharLenth(ExtName)) return 0;
	HANDLE   filehandle;
	filehandle=FindFirstFileW(ExtName,&filedata);
	if(filehandle==INVALID_HANDLE_VALUE) 
	{
		FindClose(filehandle);
		return 0;
	}
	FindClose(filehandle);
	return filedata.cFileName;
}

CTamScene::CTamScene(void)
	:Tams(NULL)
	,ModelNum(0)
{
}


CTamScene::~CTamScene(void)
{
}


void CTamScene::LoadFile(void)
{
	HANDLE   filehandle;
	filehandle=FindFirstFileW(L"data\\model\\*.*",&filedata);
	if(filehandle==INVALID_HANDLE_VALUE) 
	{
		FindClose(filehandle);
		return;
	}
	if((wcscmp(filedata.cFileName,L".")!=0)&&(wcscmp(filedata.cFileName,L"..")!=0))
		ModelNum++;
	while(FindNextFileW(filehandle,&filedata))
	{
		if(filehandle==INVALID_HANDLE_VALUE)
			continue;
		if(filedata.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		if((wcscmp(filedata.cFileName,L".")!=0)&&(wcscmp(filedata.cFileName,L"..")!=0))
			ModelNum++;
	}
	FindClose(filehandle);
}
