#include "EXTLIBS.h"
#include<hgl/platform/SystemInfo.H>
#include <hgl/external.h>
namespace hgl
{
	bool InitCore(SystemInfo &si,bool create_log);			///<初始化核心
	void CloseCore();										///<关闭核心
}
CEXTLIBS::CEXTLIBS(void)
{
	hgl::SystemInfo si;
	hgl::InitCore(si,true);

}


CEXTLIBS::~CEXTLIBS(void)
{
	hgl::CloseCore();
}
