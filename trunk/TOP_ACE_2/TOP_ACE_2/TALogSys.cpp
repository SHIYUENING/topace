#include"TALogSys.h"
#include <process.h>
list<string> LogList;
list<string> LogSendList;
string LogCharTMP;
volatile char LogCharBuffer[4096];
bool ExitLogThread=false;
bool LogThreadInited=false;
HANDLE LogThreadHANDLE=NULL;
HANDLE LogThreadMutex=NULL;
HWND LogWinHWND=NULL;
void InitLog()
{
	LogThreadHANDLE=(HANDLE)_beginthreadex(0,0,(unsigned int (__stdcall *)(void *))LogThread,0,CREATE_SUSPENDED,0);
	LogThreadMutex=CreateMutexW(NULL,false,L"LogThreadMutex");
	LogThreadInited=true;
}
void CloseLogThread()
{
	ExitLogThread=true;
}
void AddLog(char * LogChar )
{
	LogCharTMP=LogChar;
	AddLog(LogCharTMP);
}
void AddLog(string LogChar )
{
	if(!LogThreadInited)
		InitLog();
	WaitForSingleObject(LogThreadMutex,INFINITE);
	LogList.push_back(LogChar);
	ReleaseMutex(LogThreadMutex);
	ResumeThread(LogThreadHANDLE);
}
LRESULT CALLBACK WndProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc (hWnd, uMsg, wParam, lParam);					// Pass Unhandled Messages To DefWindowProc
}
ATOM RegLogWindow()
{
	WNDCLASSEX wcex;
	ZeroMemory (&wcex, sizeof (WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);//结构的大小

	wcex.style = CS_HREDRAW | CS_VREDRAW; 
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	//wcex.cbClsExtra = 0;
	//wcex.cbWndExtra = 0;
	wcex.hInstance = Hnst;
	//wcex.hIcon = NULL;//LoadIcon(Hnst, (LPCTSTR)IDI_EXAMPLE);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	//wcex.lpszMenuName =NULL;// (LPCSTR)IDC_EXAMPLE;
	wcex.lpszClassName = "TOP_ACE2_LOG";
	//wcex.hIconSm = NULL;//LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}
bool CreateLogWin()
{
	if(!RegLogWindow()) return false;
	LogWinHWND=CreateWindow(
			"TOP_ACE2_LOG",
			"TOP_ACE2_LOG",
			WS_POPUP,
			0,0,96,32,
			HWND_DESKTOP,
			NULL,
			Hnst,
			NULL);
	if(!LogWinHWND) return false;
	SendMessage(LogWinHWND,0x410,NULL,256);
	return true;
}
unsigned int __stdcall LogThread(LPVOID lpvoid)
{
	CreateLogWin();
	//LogWinHWND=
	while (!ExitLogThread)
	{
		LogSendList.clear();
		WaitForSingleObject(LogThreadMutex,INFINITE);
		LogSendList.swap(LogList);
		ReleaseMutex(LogThreadMutex);
		HWND LogViewerHWND=NULL;
		while((!ExitLogThread)&&(!LogViewerHWND))
		{
			LogViewerHWND=FindWindow(NULL,"LogViewer");
			Sleep(500);
		}
		for (list <string>::iterator it = LogSendList.begin (); it != LogSendList.end (); it ++)
		{
			for(unsigned int i=0;i<it->size();i++ )
			{
				LogCharBuffer[i]=it->at(i);
			}
			LogCharBuffer[it->size()]='\0'; 
			COPYDATASTRUCT SendData;
			SendData.cbData=it->size()+1;
			SendData.dwData=0;
			SendData.lpData=(PVOID)LogCharBuffer;
			SendMessage(LogViewerHWND,WM_COPYDATA,NULL,(LPARAM)&SendData);
		}
		SuspendThread(LogThreadHANDLE);
	}
	ReleaseMutex(LogThreadMutex);
	CloseHandle(LogThreadMutex);
	LogThreadInited=false;
	return 0;
}