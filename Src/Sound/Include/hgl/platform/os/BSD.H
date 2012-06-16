#ifndef HGL_OS_FREEBSD_INCLUDE
#define HGL_OS_FREEBSD_INCLUDE

#if defined(__FreeBSD__)
	#define HGL_OS_NAME			L"FreeBSD"
#elif defined(__NetBSD__)
	#define HGL_OS_NAME			L"NetBSD"
#elif defined(__OpenBSD__)
 	#define HGL_OS_NAME			L"OpenBSD"
#else
	#define HGL_OS_NAME			L"BSD"
#endif//

#define HGL_PLUGIN_EXTNAME		L".dylib"										//插件文件扩展名
#define HGL_PLUGIN_FUNC 														//插件函数定义

#define HGL_DIRECTORY_SEPARATOR L'/'											//目录分隔符

#endif//HGL_OS_FREEBSD_INCLUDE
