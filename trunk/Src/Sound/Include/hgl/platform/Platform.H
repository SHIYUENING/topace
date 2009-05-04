#ifndef HGL_PLATFORM_INCLUDE
#define HGL_PLATFORM_INCLUDE

#define HGL_MERGE32(a,b,c,d)		(a|b<<8|c<<16|d<<24)

#define HGL_OS_Windows				HGL_MERGE32('W','i','n',' ')
#define HGL_OS_MacOS				HGL_MERGE32('M','a','c',' ')
#define HGL_OS_BSD					HGL_MERGE32('B','S','D',' ')
#define HGL_OS_Linux				HGL_MERGE32('L','i','n','u')
#define HGL_OS_Solaris				HGL_MERGE32('S','o','l','a')
#define HGL_OS_PS2					HGL_MERGE32('P','S','2',' ')
#define HGL_OS_PSP					HGL_MERGE32('P','S','P',' ')
#define HGL_OS_PS3					HGL_MERGE32('P','S','3',' ')
#define HGL_OS_AIX					HGL_MERGE32('A','I','X',' ')
#define HGL_OS_HPUX					HGL_MERGE32('H','P','U','X')
#define HGL_OS_IRIX					HGL_MERGE32('I','R','I','X')

#define HGL_CPU_X86_32				HGL_MERGE32('8','6','3','2')
#define HGL_CPU_X86_64				HGL_MERGE32('8','6','6','4')
#define HGL_CPU_Itanium				HGL_MERGE32('I','A','6','4')
#define HGL_CPU_MIPS				HGL_MERGE32('M','I','P','S')
#define HGL_CPU_PowerPC				HGL_MERGE32('P','P','C',' ')
#define HGL_CPU_Cell				HGL_MERGE32('C','E','L','L')
#define HGL_CPU_ARM					HGL_MERGE32('A','R','M',' ')
#define HGL_CPU_SH					HGL_MERGE32('S','H',' ',' ')
#define HGL_CPU_Sparc				HGL_MERGE32('S','P','A','R')

#define HGL_COMPILER_CodeGear		HGL_MERGE32('C','o','G','e')
#define HGL_COMPILER_Microsoft		HGL_MERGE32('M','S','V','C')
#define HGL_COMPILER_OpenWatcom		HGL_MERGE32('W','a','t','c')
#define HGL_COMPILER_GNU			HGL_MERGE32('G','N','U',' ')
#define HGL_COMPILER_Intel			HGL_MERGE32('I','n','t','e')
#define HGL_COMPILER_SUN			HGL_MERGE32('S','U','N',' ')
#define HGL_COMPILER_IBM			HGL_MERGE32('I','B','M',' ')
#define HGL_COMPILER_Pathscale		HGL_MERGE32('P','a','S','c')
#define HGL_COMPILER_Pelles			HGL_MERGE32('P','e','l','l')
#define HGL_COMPILER_DigitalMars	HGL_MERGE32('D','i','M','a')
#define HGL_COMPILER_Vector			HGL_MERGE32('V','e','c','t')

#if defined(i386) || defined(__i386__) || defined(__i386) ||defined(_M_IX86)
	#if defined(__LP64__) || defined(__amd64__) || defined(_M_AMD64)|| defined(__x86_64__)
		#define HGL_CPU			HGL_CPU_X86_64
	#else
		#define HGL_CPU			HGL_CPU_X86_32
	#endif//
#elif defined(__ia64__) || defined(__ia64) || defined(_M_IA64)
	#define		HGL_CPU			HGL_CPU_Itanium
#elif defined(_MIPS_ARCH) || defined(_mips) || defined(__mips__) || defined(__MIPSEL__)
	#define		HGL_CPU			HGL_CPU_MIPS
#elif defined(__powerpc__) || defined(__powerpc) || defined(__ppc__) || defined(__PPC__) || defined(_M_PPC) || defined(_ARCH_PPC) || defined(_ARCH_PWR)
	#ifdef(__PPU__)
		#define HGL_CPU			HGL_CPU_Cell
	#else
		#define HGL_CPU			HGL_CPU_PowerPC
	#endif
#elif defined(_M_ARM)
	#define		HGL_CPU			HGL_CPU_ARM
#elif defined(__sh__) || defined(_M_SH)
	#define		HGL_CPU			HGL_CPU_SH
#elif defined(__sparc__) || defined(__sparc) || defined(__sparcv8)
	#define		HGL_CPU			HGL_CPU_SPARC
#else
	#error 无法识别的CPU类型
#endif

#if defined(__WIN32__)||defined(_WIN32)||defined(WIN32)||defined(__WINDOWS__)||defined(__WIN64__)||defined(_WIN64)||defined(WIN64)
	#define HGL_OS 			HGL_OS_Windows
#elif defined(__APPLE__)||defined(__MAC__)||defined(macintosh)
	#define HGL_OS			HGL_OS_MacOS
#elif defined(__FreeBSD__)||defined(__NetBSD__)||defined(__OpenBSD__)
	#define HGL_OS 			HGL_OS_BSD
#elif defined(__linux__)||defined(__LINUX__)
	#define HGL_OS			HGL_OS_Linux
#elif defined(sun) || defined(__sun)||defined(__solaris__)
	#define HGL_OS			HGL_OS_Solaris
#elif defined(_PS2)||defined(__MIPS_PSX2__)
	#define HGL_OS			HGL_OS_PS2
#elif defined(__PSP__)||defined(__psp__)||defined(_PSP)
	#define HGL_OS			HGL_OS_PSP
#elif defined(__PS3__)||defined(__ps3__)||defined(_PS3)
	#define HGL_OS			HGL_OS_PS3
#elif defined(_AIX) || defined(__AIX__) || defined(__aix__)
	#define HGL_OS			HGL_OS_AIX
#elif defined(__hpux__) || defined(__hpux)
	#define HGL_OS			HGL_OS_HPUX
#elif defined(__IRIX__) || defined(__irix__)
	#define HGL_OS			HGL_OS_IRIX
#else
	#error 无法识别的操作系统
#endif//

#if defined(__BORLANDC__)||defined(__TURBOC__)
	#define HGL_COMPILER 	HGL_COMPILER_CodeGear
#elif defined(_MSC_VER)
	#define HGL_COMPILER	HGL_COMPILER_Microsoft
#elif defined(__WATCOMC__)
	#define HGL_COMPILER	HGL_COMPILER_Watcom
#elif defined(__GNUC__)
	#define HGL_COMPILER	HGL_COMPILER_GNU
#elif defined(__INTELC__)||defined(__INTEL_COMPILER)
	#define HGL_COMPILER	HGL_COMPILER_Intel
#elif defined(_FORTEC_) 
	#define HGL_COMPILER	HGL_COMPILER_SUN
#elif defined(__IBMC__)||defined(__IBMCPP__)
	#define HGL_COMPILER	HGL_COMPILER_IBM
#elif defined(__PATHSCALE__)
	#define HGL_COMPILER	HGL_COMPILER_Pathscale
#elif defined(__POCC__)
	#define HGL_COMPILER	HGL_COMPILER_Pelles
#elif defined(__DMC__) && defined(__SC__)
	#define HGL_COMPILER	HGL_COMPILER_DigitalMars
#else
	#error 无法识别的编译器
#endif//

#if defined(SetEventCall)||defined(SafeCallEvent)||defined(CallEvent)||defined(DefEvent)
	#error SetEventCall,SafeCallEvent,CallEvent,DefEvent 其中之一已经定义
#endif//

#if defined(Property)||defined(PropertyRead)||defined(PropertyWrite)
	#error Property,PropertyRead,PropertyWrite 其中之一已经定义
#endif//

#ifndef UNICODE
	#define UNICODE                     //定义使用UNICODE编码
#endif//UNICODE

#if HGL_OS == HGL_OS_Windows

	#include<hgl/platform/os/Windows.H>

	#if HGL_COMPILER == HGL_COMPILER_CodeGear
		#include<hgl/platform/compiler/CodeGear.H>
	#elif HGL_COMPILER == HGL_COMPILER_Microsoft
		#include<hgl/platform/compiler/Microsoft.H>
	#elif HGL_COMPILER == HGL_COMPILER_Intel
		#include<hgl/platform/compiler/Intel.H>
	#elif HGL_COMPILER == HGL_COMPILER_IBM
		#include<hgl/platform/compiler/IBM.H>
	#elif HGL_COMPILER == HGL_COMPILER_Watcom
		#include<hgl/platform/compiler/Watcom.H>
	#elif HGL_COMPILER == HGL_COMPILER_GNU
		#include<hgl/platform/compiler/GNU.H>
	#else
		#error 无法识别匹配的编译器
	#endif

#elif HGL_OS == HGL_OS_BSD

	#include<hgl/platform/os/BSD.H>

	#if HGL_COMPILER == HGL_COMPILER_GNU
		#include<hgl/platform/compiler/GNU.H>
	#else
		#error 无法识别匹配的编译器
	#endif//GNU

#elif HGL_OS == HGL_OS_Linux

	#include<hgl/platform/os/Linux.H>

	#if HGL_COMPILER == HGL_COMPILER_Borland
		#include<hgl/platform/compiler/CodeGear.H>
	#elif HGL_COMPILER == HGL_COMPILER_Intel
		#include<hgl/platform/compiler/Intel.H>
	#elif HGL_COMPILER == HGL_COMPILER_IBM
		#include<hgl/platform/compiler/IBM.H>
	#elif HGL_COMPILER == HGL_COMPILER_Watcom
		#include<hgl/platform/compiler/Watcom.H>
	#elif HGL_COMPILER == HGL_COMPILER_GNU
		#include<hgl/platform/compiler/GNU.H>
	#else
		#error 无法识别匹配的编译器
	#endif

#elif HGL_OS == HGL_OS_MacOS

	#include<hgl/platform/os/MacOS.H>

	#if HGL_COMPILER == HGL_COMPILER_Intel              
		#include<hgl/platform/compiler/Intel.H>
	#else
		#include<hgl/platform/compiler/GNU.H>
	#else
		#error 无法识别匹配的编译器
	#endif//Intel

#elif HGL_OS == HGL_OS_Solaris

	#include<hgl/platform/os/Solaris.H>

	#if HGL_COMPILER == HGL_COMPILER_SUN
		#include<hgl/platform/compiler/SUN.H>
	#else
		#include<hgl/platform/compiler/GNU.H>
	#else
		#error 无法识别匹配的编译器
	#endif//Intel 

#elif HGL_OS == HGL_OS_PSP

	#include<hgl/platform/os/psp.h>
	
	#if HGL_COMPILER == HGL_COMPILER_GNU
		#include<hgl/platform/compiler/GNU.H>
	#else
		#error 无法识别匹配的编译器
	#endif//GNU

#elif HGL_OS == HGL_OS_PS2

	#include<hgl/platform/os/ps2.h>
	
	#if HGL_COMPILER == HGL_COMPILER_GNU
		#include<hgl/platform/compiler/GNU.H>
	#else
		#error 无法识别匹配的编译器
	#endif//GNU
	
#elif HGL_OS == HGL_OS_PS3

	#include<hgl/platform/os/ps3.h>
	
	#if HGL_COMPILER == HGL_COMPILER_IBM
		#include<hgl/platform/compiler/IBM.H>
	#elif HGL_COMPILER == HGL_COMPILER_GNU
		#include<hgl/platform/compiler/GNU.H>
	#else
		#error 无法识别匹配的编译器
	#endif//GNU

#elif (HGL_OS == HGL_OS_AIX) || (HGL_OS == HGL_OS_HPUX) ||(HGL_OS == HGL_OS_IRIX)

	#include<hgl/platform/os/ps3.h>
	
	#if HGL_COMPILER == HGL_COMPILER_IBM
		#include<hgl/platform/compiler/IBM.H>
	#elif HGL_COMPILER == HGL_COMPILER_GNU
		#include<hgl/platform/compiler/GNU.H>
	#else
		#error 无法识别匹配的编译器
	#endif//GNU
	
#endif

#endif//HGL_PLATFORM_INCLUDE
