#include "EXTLIBS.h"
#include<hgl/platform/SystemInfo.H>
#include <hgl/external.h>
#include <hgl/OpenALEE.h>
namespace hgl
{
	bool InitCore(SystemInfo &si,bool create_log);			///<初始化核心
	void CloseCore();										///<关闭核心
}
/*
CEXTLIBS::CEXTLIBS(void)
: InitOK(false)
{
	hgl::SystemInfo si;
	InitOK=hgl::InitCore(si,true);

}


CEXTLIBS::~CEXTLIBS(void)
{
	hgl::CloseCore();
}
*/
bool InitOK=false;
bool CEXTLIBS_init()
{
	if(InitOK)
		return false;
	hgl::SystemInfo si;
	InitOK=hgl::InitCore(si,true);
	if(!InitOK)
		return false;
	InitOK=InitOpenAL((const wchar_t *)0,(const wchar_t *)0);
	//const char *ALDeviceList=alcGetDeviceList();	
	return InitOK;
}

void CEXTLIBS_deinit()
{
	CloseOpenAL();
	hgl::CloseCore();
	InitOK=false;
}