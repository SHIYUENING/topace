#ifndef HGL_WIN_INCLUDE
#define HGL_WIN_INCLUDE

#include<hgl/hgl.h>
#include<hgl/platform/WinOpenGLApplication.H>

#ifdef GameApplication
#error repeated the definition of "GameApplication"
#else
#define GameApplication WinOpenGLApplication
#endif//GameApplication

#if !defined(__MAKE_HGL__) && !defined(__MAKE_PLUGIN__)
	#pragma comment(lib,HGL_LIB_Base)         	//连入基础库文件
	#pragma comment(lib,HGL_LIB_BaseObject)   	//连入基础对象库文件
	#pragma comment(lib,HGL_LIB_Network)      	//连入网络库文件
	#pragma comment(lib,HGL_LIB_OpenALEE)		//连入OpenALEE音频库文件
	#pragma comment(lib,HGL_LIB_Graphics)		//连入图形库文件
	//#pragma comment(lib,HGL_LIB_SceneGraph)	//连入场景图形库文件
	#pragma comment(lib,HGL_LIB_GUI)			//连入图形用户界面库文件
	#pragma comment(lib,HGL_LIB_UtilityTools) 	//连入实用工具库文件
	#pragma comment(lib,HGL_LIB_WinExternal)	//连入标准Windows平台接口库文件

    #ifdef _MSC_VER                             //如果是Visual C++
        #pragma comment(lib,"OpenGL32.LIB")		//连入OpenGL库
        #pragma comment(lib,"GLU32.LIB")		//连入GLU库
    #endif//_MSC_VER

    #ifndef _WINDLL								//如果是DLL则不连入WinMain接口库文件
        #pragma comment(lib,HGL_LIB_WinGame)	//加入标准Windows平台WinMain接口库文件
    #endif//_WINDLL
#endif//__MAKE_HGL__ && __MAKE_PLUGIN__
#endif//HGL_WIN_INCLUDE
