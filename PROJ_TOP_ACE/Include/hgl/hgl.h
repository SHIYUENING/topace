#ifndef HGL_INCLUDE
#define HGL_INCLUDE

#include<hgl/DataType.H>
#include<hgl/LogInfo.H>
#include<hgl/InputState.H>
#include<hgl/FlowObject.H>
#include<hgl/platform/SystemInitInfo.H>
//--------------------------------------------------------------------------------------------------
#define HGL_LIB_Base			HGL_LIB_FRONT "Base"			HGL_LIB_END
#define HGL_LIB_BaseObject		HGL_LIB_FRONT "BaseObject"		HGL_LIB_END
#define HGL_LIB_Network			HGL_LIB_FRONT "Network"			HGL_LIB_END
#define HGL_LIB_OpenALEE		HGL_LIB_FRONT "OpenALEE"		HGL_LIB_END
#define HGL_LIB_Graphics		HGL_LIB_FRONT "Graphics"		HGL_LIB_END
#define HGL_LIB_SceneGraph		HGL_LIB_FRONT "SceneGraph"		HGL_LIB_END
#define HGL_LIB_GUI				HGL_LIB_FRONT "GUI"				HGL_LIB_END
#define HGL_LIB_UtilityTools	HGL_LIB_FRONT "UtilityTools"	HGL_LIB_END

#define HGL_LIB_WinExternal		HGL_LIB_FRONT "WinExternal"		HGL_LIB_END
#define HGL_LIB_WinConsole		HGL_LIB_FRONT "WinConsole"		HGL_LIB_END
#define HGL_LIB_WinGame			HGL_LIB_FRONT "WinGame"			HGL_LIB_END

#define HGL_LIB_WinVCL			HGL_LIB_FRONT "WinVCL"			HGL_LIB_END

#define HGL_LIB_UnixConsole		HGL_LIB_FRONT "UnixConsole"		HGL_LIB_END
//--------------------------------------------------------------------------------------------------
/**
* 游戏程序入口函数
* @param argc 由命令行中传来的参数个数
* @param argv 由命令行中传来的参数队列
*/
extern "C" void GameMain(int argc,wchar_t **argv);
//--------------------------------------------------------------------------------------------------
#endif //HGL_INCLUDE
