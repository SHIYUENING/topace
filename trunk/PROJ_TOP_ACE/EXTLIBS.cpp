#include "EXTLIBS.h"
#include<hgl/platform/SystemInfo.H>
#include <hgl/external.h>
namespace hgl
{
	bool InitCore(SystemInfo &si,bool create_log);			///<��ʼ������
	void CloseCore();										///<�رպ���
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
