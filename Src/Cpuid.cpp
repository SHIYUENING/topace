//Cpuid.cpp ��ʵ��

#include "Cpuid.h"

static const int S = sizeof(DWORD);

CPUID::CPUID()
:m_eax(0),m_ebx(0),m_ecx(0),m_edx(0)
{

}

CPUID::~CPUID()
{

}

void CPUID::Executecpuid(DWORD veax)
{
 // ��ΪǶ��ʽ�Ļ����벻��ʶ�� ���Ա����
 // ���Զ����ĸ���ʱ������Ϊ����
 DWORD deax;
 DWORD debx;
 DWORD decx;
 DWORD dedx;

 __asm
 {
  mov eax, veax
  cpuid 
  mov deax, eax
  mov debx, ebx
  mov decx, ecx
  mov dedx, edx
 }

 m_eax = deax; // ����ʱ�����е����ݷ������Ա����
 m_ebx = debx;
 m_ecx = decx;
 m_edx = dedx;
}

/*
string CPUID::GetVID()
{
 char cVID[S*3+1];   // �ַ����������洢��������Ϣ
 memset(cVID, 0, sizeof(cVID));  // ��������0
 Executecpuid(0);  // ִ��cpuidָ�ʹ��������� eax = 0
 memcpy(cVID+S*0, &m_ebx, S); // ����ǰ�ĸ��ַ�������
 memcpy(cVID+S*1, &m_edx, S); // �����м��ĸ��ַ�������
 memcpy(cVID+S*2, &m_ecx, S); // ��������ĸ��ַ�������

 return string(cVID);  // ��string����ʽ����
}*/

string CPUID::GetBrand()
{
 const DWORD BRANDID = 0x80000002;  // ��0x80000002��ʼ����0x80000004����
 char cBrand[S*4*3+1];    // �����洢�̱��ַ�����48���ַ�
 memset(cBrand, 0, sizeof(cBrand));    // ��ʼ��Ϊ0

 for (DWORD i = 0; i < 3; i++)   // ����ִ��3��ָ��
 {
  Executecpuid(BRANDID + i);  
  // ÿ��ִ�н����󣬱����ĸ��Ĵ������asc�뵽����
  memcpy(cBrand + i*S*4 + S*0, &m_eax, S);
  memcpy(cBrand + i*S*4 + S*1, &m_ebx, S);
  memcpy(cBrand + i*S*4 + S*2, &m_ecx, S);
  memcpy(cBrand + i*S*4 + S*3, &m_edx, S);
 }
 return string(cBrand);  // ��string����ʽ����
}

/*
LONGLONG CPUID:: GetFrequency(DWORD sleepTime)
{
 HANDLE hp = ::GetCurrentProcess(); //��ȡ��ǰ����
 HANDLE ht = ::GetCurrentThread(); //��ȡ��ǰ�߳�

 DWORD  pc = ::GetPriorityClass( hp ); //��ȡ��ǰ�������ȶ�
 DWORD  tp = ::GetThreadPriority( ht ); //��ȡ��ǰ�߳����ȶ�

 BOOL   flag1 = FALSE , flag2 = FALSE;
 DWORD  low1  = 0 , high1 = 0 , low2 = 0 , high2 = 0;

 flag1 = ::SetPriorityClass( hp , REALTIME_PRIORITY_CLASS );  //����ǰ�������ȶ��������
 flag2 = ::SetThreadPriority( ht , THREAD_PRIORITY_HIGHEST ); //����ǰ�߳����ȶ��������

 ::Sleep( 10 );
 LARGE_INTEGER fq,st,ed;
 ::QueryPerformanceFrequency(&fq); //��ȷ��ʱ
 ::QueryPerformanceCounter(&st);  //�����ʼʱ��
 __asm        //��õ�ǰcpu��ʱ��������
 {
  rdtsc
  mov low1 , eax
  mov high1 , edx
 }
 ::Sleep( sleepTime );     //���̹߳���Ƭ��
 ::QueryPerformanceCounter(&ed);  //��ý���ʱ��
 __asm        //��õ�ǰcpu��ʱ��������
 {
  rdtsc
  mov low2  ,eax
  mov high2 ,edx
 }
 

 if( flag1 )
  ::SetPriorityClass( hp , pc );  //����ǰ�������ȶȻָ�ԭ��
 if( flag2 )
  ::SetThreadPriority( ht , tp );  //����ǰ�߳����ȶȻָ�ԭ��

 ::CloseHandle( hp );
 ::CloseHandle( ht );

 //��cpu��ʱ��������ת����64λ����
 LONGLONG begin = (LONGLONG)high1<<32 | low1;
 LONGLONG end = (LONGLONG)high2<<32 | low2;

 //�����λ�õ�cpuʱ�����������Լ��ʱ�䣬���õ�cpu��Ƶ�ʡ�
 //����windows��Sleep�����д�Լ15�����������windows�ľ�ȷ��ʱΪ׼
 return (end - begin)*fq.QuadPart/(ed.QuadPart-st.QuadPart);
}*/