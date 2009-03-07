//Cpuid.h ������

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
 
 //string  GetVID();  //��ȡcpu������
 string  GetBrand();  //��ȡcpu�ͺ�
 //LONGLONG GetFrequency(DWORD sleepTime = 1000);//��ȡcpu��Ƶ

private:
 void  Executecpuid(DWORD veax); //����ִ��cpuidָ��
 DWORD  m_eax;   // �洢���ص�eax
 DWORD  m_ebx;   // �洢���ص�ebx
 DWORD  m_ecx;   // �洢���ص�ecx
 DWORD  m_edx;   // �洢���ص�edx
};

#endif