//--------------------------------------------------------------------------------------------------
// OpenAL ExtEdition SDK
//
// 这是一个根据标准OpenAL SDK所编写的特殊增强版本，它支持目前所有的OpenAL扩展。
//
//           作者: 胡颖卓
//           版本: 1.13
// 对应OpenAL版本: 1.1
//       对应语言: C/C++
//   适用开发工具: Borland C++ Compiler 5.5 或更高
//                 Borland C++ Builder 5 或更高
//                 Borland C++ BuilderX 1.0 或更高
//				   Microsoft C++ 15.0 (Visual C++ 9.0)或更高
//				   GNU C/C++ 4.0 或更高
//
// 第一版编写时间: 2003年10月5日
// 当前版完成时间: 2009年4月16日
//
//       官方网站: http://www.hyzgame.com.cn/openalee
// OpenAL官方网站: http://www.openal.org
//--------------------------------------------------------------------------------------------------
#ifndef OpenALH
#define OpenALH

#ifdef __al_h_
	#error 请不要使用原始的OpenAL头文件
#else
	#define __al_h_
#endif //__al_h_

#include<hgl/al/al.h>
#include<hgl/al/alc.h>
#include<hgl/al/xram.h>
#include<hgl/al/efx.h>

namespace openal                                                									///OpenAL EE所使用的名字空间
{
	bool LoadOpenAL(const wchar_t * =0);															//加载OpenAL,参数为驱动名称

	const char *alcGetDeviceList();																	//取得设备列表
	const char *alcGetDefaultDevice();																//取得缺省设备
	void alcSetDefaultContext();																	//设置缺省上下文

	wchar_t *alGetErrorInfo(char *,int);                                                            //取得最近的错误

	bool InitOpenAL(const wchar_t *driver_name=0,const char *device_name=0,bool=false);				//初始化OpenAL,参数为设备名称,返回AL_TRUE或AL_FALSE
	bool InitOpenAL(const wchar_t *driver_name=0,const wchar_t *device_name=0,bool=false);			//初始化OpenAL,参数为设备名称,返回AL_TRUE或AL_FALSE
	void CloseOpenAL();                                                                             //关闭OpenAL

	unsigned int AudioTime(ALenum,ALsizei);
	double AudioDataTime(ALuint,ALenum,ALsizei);
	//--------------------------------------------------------------------------------------------------
	#define alLastError()   alGetErrorInfo(__FILE__,__LINE__)
}//namespace openal
#endif //OpenALH
