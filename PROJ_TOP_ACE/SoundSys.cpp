#include "SoundSys.h"

#include <hgl/OpenALEE.h>
CSoundSys::CSoundSys(void)
: InitOK(false)
{
	InitOK=openal::InitOpenAL((const wchar_t *)0,(const wchar_t *)0,true);
	const char *ALDeviceList=alcGetDeviceList();	
}


CSoundSys::~CSoundSys(void)
{
	openal::CloseOpenAL();
}
