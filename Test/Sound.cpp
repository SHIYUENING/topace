#include "Sound.h"
#pragma comment( lib, "fmodex_vc.lib" )
FMOD_SYSTEM* sys;
FMOD_SOUND* BGM1;
FMOD_SOUND* BGM2;
FMOD_SOUND* BGM3;
FMOD_CHANNEL* BGMchannel;
void InitSound()
{
	FMOD_RESULT r = FMOD_System_Create(&sys);
	FMOD_System_Init(sys, 32, FMOD_INIT_NORMAL, 0);
	FMOD_System_CreateSound(sys, "Data/BGM1.mp3", FMOD_LOOP_NORMAL | FMOD_2D | FMOD_CREATECOMPRESSEDSAMPLE, 0, &BGM1);
	FMOD_System_CreateSound(sys, "Data/BGM2.mp3", FMOD_LOOP_NORMAL | FMOD_2D | FMOD_CREATECOMPRESSEDSAMPLE, 0, &BGM2);
	FMOD_System_CreateSound(sys, "Data/BGM3.mp3", FMOD_LOOP_NORMAL | FMOD_2D | FMOD_CREATECOMPRESSEDSAMPLE, 0, &BGM3);
	FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, BGM1, 0, &BGMchannel);
}
void DeinitSound()
{
	FMOD_Sound_Release(BGM1);
	FMOD_Sound_Release(BGM2);
	FMOD_Sound_Release(BGM3);
	FMOD_System_Close(sys);
}
void PlaySound1()
{
	FMOD_Channel_Stop(BGMchannel);
	FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, BGM1, 0, &BGMchannel);
}
void PlaySound2()
{
	FMOD_Channel_Stop(BGMchannel);
	FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, BGM2, 0, &BGMchannel);
}
void PlaySound3()
{
	FMOD_Channel_Stop(BGMchannel);
	FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, BGM3, 0, &BGMchannel);
}
void StopSound()
{
	FMOD_Channel_Stop(BGMchannel);
}