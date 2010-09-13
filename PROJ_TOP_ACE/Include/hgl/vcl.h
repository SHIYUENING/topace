#ifndef HGL_VCL_INCLUDE
#define HGL_VCL_INCLUDE

#ifndef __HGL_VCL__
#define __HGL_VCL__
#endif//__HGL_VCL__

#include<hgl/hgl.h>

#if !defined(__MAKE_HGL__) && !defined(__MAKE_PLUGIN__)
	#pragma comment(lib,HGL_LIB_Base)         	//连入基础库文件
	#pragma comment(lib,HGL_LIB_BaseObject)   	//连入基础对象库文件
	#pragma comment(lib,HGL_LIB_Network)      	//连入网络库文件
	#pragma comment(lib,HGL_LIB_OpenALEE)		//连入OpenALEE音频库文件
	#pragma comment(lib,HGL_LIB_Graphics)		//连入图形库文件
	//#pragma comment(lib,HGL_LIB_SceneGraph)	//连入场景图形库文件
	#pragma comment(lib,HGL_LIB_GUI)			//连入图形用户界面库文件
	#pragma comment(lib,HGL_LIB_UtilityTools) 	//连入实用工具库文件
	#pragma comment(lib,HGL_LIB_WinVCL)			//连入Windows平台VCL控制程序接口库文件
#endif

namespace Controls
{
	class TCustomControl;
}
using namespace Controls;

namespace hgl
{
	//《古月》for VCL 专用函数，非VCL程序请不要使用

	bool InitSystem(bool=true,bool=true);					///<初始化系统
	void CloseSystem();										///<关闭系统

	bool InitGraphics(TCustomControl *);					///<初始化图形模式,不显示
	bool InitGraphics(TCustomControl *,int,int,int,int);    ///<初始化图形模式
	void ChangeViewport(int=0,int=0,int=0,int=0);           ///<更改显示位置
	void CloseGraphics();                                   ///<关闭图形模式
	void RedrawScreen();                                    ///<刷新整个屏幕

	void ChangeViewport();									///<更改显示位置

	bool InitAudio(const char *device_name=0);              ///<初始化音频
	void CloseAudio();                                      ///<关闭音频
}//namespace hgl
#endif//HGL_VCL_INCLUDE
