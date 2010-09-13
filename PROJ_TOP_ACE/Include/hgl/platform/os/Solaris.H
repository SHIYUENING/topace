#ifndef HGL_OS_Solaris_INCLUDE
#define HGL_OS_Solaris_INCLUDE
//--------------------------------------------------------------------------------------------------
#if HGL_CPU == HGL_CPU_X86_32
	#define HGL_OS_NAME				L"Solaris(x86-32)"
#elif HGL_CPU == HGL_CPU_X86_64
	#define HGL_OS_NAME				L"Solaris(x86-64)"
#elif HGL_CPU == HGL_CPU_Sparc
	#define HGL_OS_NAME				L"Solaris(Sparc)"
#else
	#error 未知类型 Solaris
#endif//

//--------------------------------------------------------------------------------------------------
#define HGL_PLUGIN_EXTNAME		L".dylib"										//插件文件扩展名
#define HGL_PLUGIN_FUNC 		

#define HGL_DIRECTORY_SEPARATOR L'/'											//目录分隔符
//--------------------------------------------------------------------------------------------------
#if !defined(__MAKE_HGL__) && !defined(__MAKE_PLUGIN__)
#endif//__MAKE_PLUGIN__
//--------------------------------------------------------------------------------------------------
#endif//HGL_OS_Solaris_INCLUDE
