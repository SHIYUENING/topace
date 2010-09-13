#ifndef HGL_CONSOLE_INCLUDE
#define HGL_CONSOLE_INCLUDE

#include<hgl/hgl.h>
#include<hgl/platform/ConsoleApplication.H>

#ifdef GameApplication
#error repeated the definition of "GameApplication"
#else
#define GameApplication ConsoleApplication
#endif//GameApplication

#if !defined(__MAKE_HGL__) && !defined(__MAKE_PLUGIN__)

	#pragma comment(lib,HGL_LIB_Base)         		//连入基础库文件
	#pragma comment(lib,HGL_LIB_BaseObject)   		//连入基础对象库文件
	#pragma comment(lib,HGL_LIB_Network)      		//连入网络库文件
	#pragma comment(lib,HGL_LIB_UtilityTools) 		//连入实用工具库文件

	#if HGL_OS == HGL_OS_Windows
	
	    #ifndef _WINDLL								//如果是DLL则不连入main接口文件
	        #pragma comment(lib,HGL_LIB_WinConsole)	//连入标准Windows平台main接口库文件
	    #endif//_WINDLL
	#elif (HGL_OS==HGL_OS_Linux)||(HGL_OS==HGL_OS_BSD)||(HGL_OS==HGL_OS_MacOS)||(HGL_OS==HGL_OS_Solaris)
	    #pragma comment(lib,HGL_LIB_UnixConsole)	//连入标准Unix平台main接口库文件
	#endif//HGL_OS

#endif//__MAKE_HGL__ && __MAKE_PLUGIN__
#endif//HGL_CONSOLE_INCLUDE
