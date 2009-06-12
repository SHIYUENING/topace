#pragma once


#include "Mathematics.h"
#include <windows.h>
#include<hgl/OpenALEE.H>
//#include <stdio.h>												// Header File For Standard Input / Output
//#include <stdarg.h>
//#include   <time.h>
//#include <conio.h>
//#include "fmod.hpp"
//#include "fmod_errors.h"

//#pragma comment( lib, "fmodex_vc.lib" )	
/*
FMOD_SYSTEM* sys;
FMOD_SOUND* sound1;
FMOD_SOUND* sound2;
FMOD_SOUND* soundLock;
FMOD_SOUND* soundLockOn;
FMOD_SOUND* soundLocked;
FMOD_SOUND* soundGunFire;
FMOD_SOUND* soundGunHited;
//FMOD_SOUND* voice1;
//FMOD_SOUND* voice2;
//FMOD_SOUND* voice3;
//FMOD_SOUND* voice4;
//FMOD_SOUND* voice5;
FMOD_SOUND* missleWarning[10];
FMOD_SOUND* fox2voice[3];
FMOD_SOUND* hitvoice[4];
FMOD_SOUND* killvoice[7];
FMOD_SOUND* missvoice[4];
FMOD_SOUND* BGMsound;
FMOD_CHANNEL* channel1;
FMOD_CHANNEL* channel2;
FMOD_CHANNEL* channelLock;
FMOD_CHANNEL* channelLockOn;
FMOD_CHANNEL* channelLocked;
FMOD_CHANNEL* channelGunFire;
FMOD_CHANNEL* channelGunHited;


FMOD_CHANNEL* missleWarningchannel;
FMOD_CHANNEL* fox2voicechannel;
FMOD_CHANNEL* hitvoicechannel;
FMOD_CHANNEL* killvoicechannel;
FMOD_CHANNEL* missvoicechannel;
FMOD_CHANNEL* BGMchannel;
FMOD_VECTOR pos;
*/

#define MAX_missleWarning 10
#define MAX_fox2voice 3
#define MAX_hitvoice 4
#define MAX_killvoice 10
#define MAX_missvoice 4
#define MAX_sounds 7
#define MAX_soundSource 20
using namespace hgl;
struct tSoundSourceDate
{
	int soundType;//0导弹 1飞机 2警告 3其他
	int Num;
 
};

void initsound();
bool AddSound(int Num,const Vector3d& pos);
void MoveSound(Transform& would,float LookRenge);
void PlaymissleWarning(int Num);
void Playfox2voice(int Num);
void Playhitvoice(int Num);
void Playkillvoice(int Num);
void Playmissvoice(int Num);
void SoundPause();