#include "SoundSys.h"

#include <hgl/OpenALEE.h>
using namespace openal;
hgl::AudioBuffer * ABTest;
hgl::AudioSource * ASTest;
hgl::AudioPlayer * APTest;
CSoundSys::CSoundSys(void)
: InitOK(false)
{
	InitOK=openal::InitOpenAL((const wchar_t *)0,(const wchar_t *)0);
	const char *ALDeviceList=alcGetDeviceList();	

	APTest=new hgl::AudioPlayer;
	InitOK=APTest->Load(L"Data/bgm.ogg",hgl::aftOGG);
	APTest->Play(true);
	ABTest=new hgl::AudioBuffer;
	InitOK=ABTest->Load(L"Data/GunFire.ogg",hgl::aftOGG);

	ASTest=new hgl::AudioSource(ABTest);
	ASTest->Loop=true;
	ASTest->Play(true);
}


CSoundSys::~CSoundSys(void)
{
	ASTest->Stop();
	ASTest->Unlink();
	delete ASTest;
	delete ABTest;
	openal::CloseOpenAL();
}
