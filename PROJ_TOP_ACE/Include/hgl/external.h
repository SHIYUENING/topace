#ifndef HGL_EXTERNAL_INCLUDE
#define HGL_EXTERNAL_INCLUDE

#include<hgl/hgl.h>
#include<hgl/platform/platform.h>

#if !defined(__MAKE_HGL__) && !defined(__MAKE_PLUGIN__)
	#pragma comment(lib,HGL_LIB_Base)         	//连入基础库文件
	//#pragma comment(lib,HGL_LIB_BaseObject)   	//连入基础对象库文件
	//#pragma comment(lib,HGL_LIB_Network)      	//连入网络库文件

	#pragma comment(lib,HGL_LIB_OpenALEE)		//连入OpenALEE音频库文件
	//#pragma comment(lib,HGL_LIB_Graphics)		//连入图形库文件
	//#pragma comment(lib,HGL_LIB_SceneGraph)	//连入场景图形库文件
	//#pragma comment(lib,HGL_LIB_GUI)			//连入图形用户界面库文件
	//#pragma comment(lib,HGL_LIB_UtilityTools) 	//连入实用工具库文件
	//#pragma comment(lib,HGL_LIB_WinExternal)	//连入标准Windows平台接口库文件
#endif
#endif//HGL_EXTERNAL_INCLUDE
