#ifndef HGL_OS_FREEBSD_INCLUDE
#define HGL_OS_FREEBSD_INCLUDE

#if defined(__FreeBSD__)
	#define HGL_OS_NAME				L"FreeBSD"
#elif defined(__NetBSD__)
	#define HGL_OS_NAME				L"NetBSD"
#elif defined(__OpenBSD__)
 	#define HGL_OS_NAME				L"OpenBSD"
#else
	#define  HGL_OS_NAME			L"unknown BSD"
#endif//

#define PIExtName	L".so"								//插件文件扩展名
#define PIAPI 											//插件函数定义

#endif//HGL_OS_FREEBSD_INCLUDE