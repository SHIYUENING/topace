#ifndef HGL_OS_WIN_INCLUDE
#define HGL_OS_WIN_INCLUDE
//--------------------------------------------------------------------------------------------------
#if HGL_CPU == HGL_CPU_X86_32
	#define HGL_OS_NAME				L"Windows(x86-32)"
#elif HGL_CPU == HGL_CPU_X86_64
	#define HGL_OS_NAME				L"Windows(x86-64)"
#elif HGL_CPU == HGL_CPU_IA64
	#define HGL_OS_NAME				L"Windows(Itanium)"
#else
	#error 未知类型 Windows
#endif//

#if (!defined(_WIN32_WINNT))||(_WIN32_WINNT<0x0500)
	#undef _WIN32_WINNT
	#define _WIN32_WINNT 0x0500			//声明可以使用Windows 2000级别的Windows API
#endif//_WIN32_WINNT

//--------------------------------------------------------------------------------------------------
#define PIExtName	L".DLL"										//插件文件扩展名
#define PIAPI 		extern "C" __declspec(dllexport)			//插件函数定义
//--------------------------------------------------------------------------------------------------
#endif//HGL_OS_WIN_INCLUDE