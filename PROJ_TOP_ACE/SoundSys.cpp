#include "SoundSys.h"

#include <hgl/OpenALEE.h>
using namespace hgl;
AudioBuffer * ABTest;
AudioSource * ASTest;
//AudioPlayer * APTest;
CSoundSys::CSoundSys(void)
: InitOK(false)
{
	//APTest=new AudioPlayer;
	//InitOK=APTest->Load(L"Data/bgm.ogg",aftOGG);
	//APTest->Play(true);
	ABTest=new hgl::AudioBuffer;
	InitOK=ABTest->Load(L"Data/GunFire.wav");

	ASTest=new AudioSource(ABTest);
	ASTest->Loop=true;
	ReferenceValue tmp;
	tmp.cur=0.0001f;
	tmp.max=0.00011f;
	ASTest->SetDistance(tmp);
	ASTest->Play(true);
}


CSoundSys::~CSoundSys(void)
{
	ASTest->Stop();
	ASTest->Unlink();
	delete ASTest;
	delete ABTest;
	//delete APTest;
}


void CSoundSys::SetTestPos(float x,float y,float z)
{
	ASTest->SetPosition(Vertex3f(x,y,z));
}
