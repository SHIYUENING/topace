#include "SoundSys.h"

#include <hgl/OpenALEE.h>
CSoundSys::CSoundSys(void)
{
	openal::InitOpenALEE();
}


CSoundSys::~CSoundSys(void)
{
	openal::CloseOpenALEE();
}
