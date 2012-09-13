//Cpuid.cpp 类实现

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
 // 因为嵌入式的汇编代码不能识别 类成员变量
 // 所以定义四个临时变量作为过渡
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

 m_eax = deax; // 把临时变量中的内容放入类成员变量
 m_ebx = debx;
 m_ecx = decx;
 m_edx = dedx;
}


string CPUID::GetBrand()
{
 const DWORD BRANDID = 0x80000002;  // 从0x80000002开始，到0x80000004结束
 char cBrand[S*4*3+1];    // 用来存储商标字符串，48个字符
 memset(cBrand, 0, sizeof(cBrand));    // 初始化为0

 for (DWORD i = 0; i < 3; i++)   // 依次执行3个指令
 {
  Executecpuid(BRANDID + i);  
  // 每次执行结束后，保存四个寄存器里的asc码到数组
  memcpy(cBrand + i*S*4 + S*0, &m_eax, S);
  memcpy(cBrand + i*S*4 + S*1, &m_ebx, S);
  memcpy(cBrand + i*S*4 + S*2, &m_ecx, S);
  memcpy(cBrand + i*S*4 + S*3, &m_edx, S);
 }
 return string(cBrand);  // 以string的形式返回
}

