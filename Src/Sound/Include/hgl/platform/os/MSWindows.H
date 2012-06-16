#ifndef HGL_OS_WIN_INCLUDE
#define HGL_OS_WIN_INCLUDE
//--------------------------------------------------------------------------------------------------
#define HGL_OS_NAME				L"Windows"
#define HGL_LIB_OS_NAME			"Windows"

#if HGL_CPU == HGL_CPU_X86_32
	#if (!defined(_WIN32_WINNT))||(_WIN32_WINNT<0x0501)
		#undef _WIN32_WINNT
		#define _WIN32_WINNT 0x0501			//声明可以使用Windows XP级别的Windows API
	#endif//_WIN32_WINNT
#elif HGL_CPU == HGL_CPU_X86_64
	#if (!defined(_WIN32_WINNT))||(_WIN32_WINNT<0x0502)
		#undef _WIN32_WINNT
		#define _WIN32_WINNT 0x0502			//声明可以使用Windows Server 2003/XP-64级别的Windows API
	#endif//_WIN32_WINNT
#endif//HGL_CPU
//--------------------------------------------------------------------------------------------------
#define HGL_PLUGIN_EXTNAME	    		L".DLL"											//插件文件扩展名
#define HGL_PLUGIN_FUNC					extern "C" __declspec(dllexport)				//插件函数定义

#define HGL_DIRECTORY_SEPARATOR 		L'\\'											//目录分隔符

#define HGL_MEM_ALIGN					16												//内存对齐字节数
//--------------------------------------------------------------------------------------------------
#endif//HGL_OS_WIN_INCLUDE
