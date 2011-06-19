#ifndef _TALOGSYS_H
#define _TALOGSYS_H
#include"common.h"
#include <list>
#include<xstring>
using namespace std;
void AddLog(char * LogChar );
void AddLog(string LogChar );
unsigned int __stdcall LogThread(LPVOID lpvoid);
void CloseLogThread();
#endif