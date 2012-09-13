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

