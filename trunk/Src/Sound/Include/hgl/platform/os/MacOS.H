#ifndef HGL_OS_MACOS_INCLUDE
#define HGL_OS_MACOS_INCLUDE

#if HGL_CPU == HGL_CPU_PowerPC
	#define HGL_OS_NAME				L"MacOS(PowerPC)"
#elif (HGL_CPU == HGL_CPU_X86_32) || (HGL_CPU == HGL_CPU_X86_64)
	#define HGL_OS_NAME				L"MacOS(Intel)"
#elif HGL_CPU == HGL_CPU_Cell
	#define HGL_OS_NAME				L"MacOS(PlayStation3)"
#elif HGL_CPU == HGL_CPU_MIPS
	#define HGL_OS_NAME				L"MacOS(MIPS)"
	
	#error 不支持这个版本的MacOS
#else
	#error 未知版本的MacOS
#endif//

#define PIExtName	L".dylib"							//插件文件扩展名
#define PIAPI 											//插件函数定义

#endif//HGL_OS_MACOS_INCLUDE