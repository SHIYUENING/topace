#include "System.h"
#include"TALogSys.h"
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	Hnst=hInstance;
	ShellExecute(NULL,"open","LogViewer.exe","","", SW_SHOW );
	AddLog("test");
	Sleep(10);AddLog("test1");
	Sleep(10);AddLog("test2");
	Sleep(10);AddLog("test3");
	Sleep(10);AddLog("test4");
	Sleep(10);AddLog("test5");
	Sleep(100);
	while(1)
	{
		AddLog("test");
		Sleep(100);
	}
	void CloseLogThread();
	return 0;
}	