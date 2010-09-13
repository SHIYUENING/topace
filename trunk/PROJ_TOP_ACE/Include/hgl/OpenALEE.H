#ifndef HGL_OPENAL_EXT_EDITION_INCLUDE
#define HGL_OPENAL_EXT_EDITION_INCLUDE

/**
* 注：仅独立使用OpenAL/EE才需要使用此头文件
*/

#include<hgl/OpenAL.H>
#include<hgl/AudioBuffer.H>
#include<hgl/AudioSource.H>
#include<hgl/AudioPlayer.H>
#include<hgl/AudioManage.H>

//#pragma comment(lib,"Base.LIB")
//#pragma comment(lib,"OpenALEEStandAlone.LIB")
/*
namespace openal
{
	bool InitOpenALEE(const wchar_t *driver_name=0,const char *device_name=0,bool log=true);
	void CloseOpenALEE();
}
*/
//初始化OpenAL/EE

//方式一：全部默认
//if(openal::InitOpenALEE())
//{
//	init ok
//}

//方式二：指定驱动程序，强制软件驱动
//if(openal::InitOpenALEE(L"wrap_oal.dll",NULL))
//{
//	init ok
//}

//输出OpenAL/EE信息
//	openal::PutOpenALInfo();

//关闭OpenAL/EE
//	openal::CloseOpenALEE();

//使用推荐

//背景音乐: AudioPlayer，独立线程解码与播放，独占一个音源
//普通音效: AudioManage，自动大量音源管理
//高阶应用: AudioSource/AudioBuffer

#endif//HGL_OPENAL_EXT_EDITION_INCLUDE
