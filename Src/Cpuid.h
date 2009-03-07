//Cpuid.h 类声明

#ifndef _CPUID_H
#define _CPUID_H

#include <string>
#include <windows.h>

using namespace std;
typedef unsigned long DWORD;
typedef __int64 LONGLONG;

class CPUID
{
public:
 CPUID();
 virtual ~CPUID();
 
 //string  GetVID();  //获取cpu制造商
 string  GetBrand();  //获取cpu型号
 //LONGLONG GetFrequency(DWORD sleepTime = 1000);//获取cpu主频

private:
 void  Executecpuid(DWORD veax); //用以执行cpuid指令
 DWORD  m_eax;   // 存储返回的eax
 DWORD  m_ebx;   // 存储返回的ebx
 DWORD  m_ecx;   // 存储返回的ecx
 DWORD  m_edx;   // 存储返回的edx
};

#endif