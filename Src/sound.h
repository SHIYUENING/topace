#pragma once
#include<hgl/OpenALEE.H>
#include <windows.h>											// Header File For Windows
#include "Mathematics.h"
#include "Physics.h"
#include "MyFont.h"
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
extern CMyFont MyFont;
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
bool isinitsound=false;
AudioBuffer * missleWarning[MAX_missleWarning];
AudioBuffer * fox2voice[MAX_fox2voice];
AudioBuffer * hitvoice[MAX_hitvoice];
AudioBuffer * killvoice[MAX_killvoice];
AudioBuffer * missvoice[MAX_missvoice];
AudioBuffer * sounds[MAX_sounds];
AudioSource * voiceSource;
AudioSource * voiceSourceLock;
AudioSource * voiceSourceLockOn;
AudioSource * voiceSourceLocked;
AudioSource * voiceSourceGunFire;
AudioSource * voiceSourceAWACS;
AudioSource * soundSource[MAX_soundSource];
Vector3d soundSourcePos[MAX_soundSource];
AudioPlayer * BGMplayer;
tSoundSourceDate SoundSourceDate[MAX_soundSource];
void initsound()
{
	openal::InitOpenALEE();
	BGMplayer= new AudioPlayer;
	BGMplayer->Load(L"Data/bgm.ogg");
	BGMplayer->Gain=0.5f;
	
	
	missleWarning[0] = new AudioBuffer;missleWarning[0]->Load(L"Data/voice/missleWarning0.ogg");
	missleWarning[1] = new AudioBuffer;missleWarning[1]->Load(L"Data/voice/missleWarning1.ogg");
	missleWarning[2] = new AudioBuffer;missleWarning[2]->Load(L"Data/voice/missleWarning2.ogg");
	missleWarning[3] = new AudioBuffer;missleWarning[3]->Load(L"Data/voice/missleWarning3.ogg");
	missleWarning[4] = new AudioBuffer;missleWarning[4]->Load(L"Data/voice/missleWarning4.ogg");
	missleWarning[5] = new AudioBuffer;missleWarning[5]->Load(L"Data/voice/missleWarning5.ogg");
	missleWarning[6] = new AudioBuffer;missleWarning[6]->Load(L"Data/voice/missleWarning6.ogg");
	missleWarning[7] = new AudioBuffer;missleWarning[7]->Load(L"Data/voice/missleWarning7.ogg");
	missleWarning[8] = new AudioBuffer;missleWarning[8]->Load(L"Data/voice/missleWarning8.ogg");
	missleWarning[9] = new AudioBuffer;missleWarning[9]->Load(L"Data/voice/missleWarning9.ogg");
	fox2voice[0] = new AudioBuffer;fox2voice[0]->Load(L"Data/voice/fox20.ogg");
	fox2voice[1] = new AudioBuffer;fox2voice[1]->Load(L"Data/voice/fox21.ogg");
	fox2voice[2] = new AudioBuffer;fox2voice[2]->Load(L"Data/voice/fox22.ogg");
	hitvoice[0] = new AudioBuffer;hitvoice[0]->Load(L"Data/voice/hit0.ogg");
	hitvoice[1] = new AudioBuffer;hitvoice[1]->Load(L"Data/voice/hit1.ogg");
	hitvoice[2] = new AudioBuffer;hitvoice[2]->Load(L"Data/voice/hit2.ogg");
	hitvoice[3] = new AudioBuffer;hitvoice[3]->Load(L"Data/voice/hit3.ogg");
	killvoice[0] = new AudioBuffer;killvoice[0]->Load(L"Data/voice/kill0.ogg");
	killvoice[1] = new AudioBuffer;killvoice[1]->Load(L"Data/voice/kill1.ogg");
	killvoice[2] = new AudioBuffer;killvoice[2]->Load(L"Data/voice/kill2.ogg");
	killvoice[3] = new AudioBuffer;killvoice[3]->Load(L"Data/voice/kill3.ogg");
	killvoice[4] = new AudioBuffer;killvoice[4]->Load(L"Data/voice/kill4.ogg");
	killvoice[5] = new AudioBuffer;killvoice[5]->Load(L"Data/voice/kill5.ogg");
	killvoice[6] = new AudioBuffer;killvoice[6]->Load(L"Data/voice/kill6.ogg");
	killvoice[7] = new AudioBuffer;killvoice[7]->Load(L"Data/voice/kill7.ogg");
	killvoice[8] = new AudioBuffer;killvoice[8]->Load(L"Data/voice/kill8.ogg");
	killvoice[9] = new AudioBuffer;killvoice[9]->Load(L"Data/voice/kill9.ogg");
	missvoice[0] = new AudioBuffer;missvoice[0]->Load(L"Data/voice/miss0.ogg");
	missvoice[1] = new AudioBuffer;missvoice[1]->Load(L"Data/voice/miss1.ogg");
	missvoice[2] = new AudioBuffer;missvoice[2]->Load(L"Data/voice/miss2.ogg");
	missvoice[3] = new AudioBuffer;missvoice[3]->Load(L"Data/voice/miss3.ogg");
	sounds[0] = new AudioBuffer;sounds[0]->Load(L"Data/sound/Boom0.ogg");
	sounds[1] = new AudioBuffer;sounds[1]->Load(L"Data/sound/FireMissle.ogg");
	sounds[2] = new AudioBuffer;sounds[2]->Load(L"Data/sound/GunFire.ogg");
	sounds[3] = new AudioBuffer;sounds[3]->Load(L"Data/sound/GunHited.ogg");
	sounds[4] = new AudioBuffer;sounds[4]->Load(L"Data/sound/lock.ogg");
	sounds[5] = new AudioBuffer;sounds[5]->Load(L"Data/sound/locked.ogg");
	sounds[6] = new AudioBuffer;sounds[6]->Load(L"Data/sound/Lockon.ogg");
	voiceSource=new AudioSource;
	voiceSourceLock=new AudioSource;voiceSourceLock->Link(sounds[4]);
	voiceSourceLockOn=new AudioSource;voiceSourceLockOn->Link(sounds[6]);
	voiceSourceLocked=new AudioSource;voiceSourceLocked->Link(sounds[5]);
	voiceSourceGunFire=new AudioSource;voiceSourceGunFire->Link(sounds[2]);
	voiceSourceAWACS=new AudioSource;
	for(int i=0;i<MAX_soundSource;i++)
		soundSource[i]=new AudioSource;

	/*
	for(int i=0;i<MAX_missleWarning;i++)
	{
		char voicename[64]={};
		sprintf(voicename,"Data/voice/missleWarning%d.ogg",i);
		missleWarning[i]->Load(L voicename);
	
	}
	*/
	/*
	FMOD_RESULT r = FMOD_System_Create(&sys);
	FMOD_System_Init(sys, 32, FMOD_INIT_NORMAL, 0);

	

	for(int i=1;i<11;i++)
	{
		char voicename[64]={};
		sprintf(voicename,"Data/voice/missleWarning%d.mp3",i);
		FMOD_System_CreateSound(sys, voicename, FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE|FMOD_CREATESAMPLE, 0, &missleWarning[i-1]);
	
	}
	for(int i=1;i<4;i++)
	{
		char voicename[64]={};
		sprintf(voicename,"Data/voice/fox2%d.mp3",i);
		FMOD_System_CreateSound(sys, voicename, FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE|FMOD_CREATESAMPLE, 0, &fox2voice[i-1]);
	
	}
	for(int i=1;i<5;i++)
	{
		char voicename[64]={};
		sprintf(voicename,"Data/voice/hit%d.mp3",i);
		FMOD_System_CreateSound(sys, voicename, FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE|FMOD_CREATESAMPLE, 0, &hitvoice[i-1]);
	
	}
	for(int i=1;i<8;i++)
	{
		char voicename[64]={};
		sprintf(voicename,"Data/voice/kill%d.mp3",i);
		FMOD_System_CreateSound(sys, voicename, FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE|FMOD_CREATESAMPLE, 0, &killvoice[i-1]);
	
	}
	for(int i=1;i<5;i++)
	{
		char voicename[64]={};
		sprintf(voicename,"Data/voice/miss%d.mp3",i);
		FMOD_System_CreateSound(sys, voicename, FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE|FMOD_CREATESAMPLE, 0, &missvoice[i-1]);
	
	}
	
	FMOD_System_CreateSound(sys, "Data/sound/TOWERWEA.WAV", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE, 0, &sound1);
	FMOD_System_CreateSound(sys, "Data/sound/ZAP9.WAV", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE, 0, &sound2);
	FMOD_System_CreateSound(sys, "Data/sound/lock.wav", FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE, 0, &soundLock);
	FMOD_System_CreateSound(sys, "Data/sound/Lockon.wav", FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE, 0, &soundLockOn);
	FMOD_System_CreateSound(sys, "Data/sound/locked.wav", FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE, 0, &soundLocked);
	FMOD_System_CreateSound(sys, "Data/sound/GunFire.wav", FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE, 0, &soundGunFire);
	FMOD_System_CreateSound(sys, "Data/sound/GunHited.wav", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE, 0, &soundGunHited);
	//FMOD_System_CreateSound(sys, "Data/voice/hit.WAV", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE, 0, &voice1);
	//FMOD_System_CreateSound(sys, "Data/voice/fox.WAV", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE, 0, &voice2);
	//FMOD_System_CreateSound(sys, "Data/voice/miss.WAV", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE, 0, &voice3);
	//FMOD_System_CreateSound(sys, "Data/voice/destroy.wav", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE, 0, &voice4);
	//FMOD_System_CreateSound(sys, "Data/voice/midi.mp3", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE|FMOD_CREATESAMPLE, 0, &voice5);
	//FMOD_System_CreateSound(sys, "Data/BGM.mp3", FMOD_LOOP_NORMAL | FMOD_2D | FMOD_CREATECOMPRESSEDSAMPLE, 0, &BGMsound);
	//FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, BGMsound, 0, &BGMchannel);
*/



	isinitsound=true;

}
bool AddSound(int Num,const Vector3d& pos)
{
	if((Num<0)||(Num>=MAX_soundSource))
		return false;
	int i=0;
	while(soundSource[i]->State==AL_PLAYING)
	{
		i=i+1;
		if(i>=MAX_soundSource)
			return false;
	}
	soundSourcePos[i]=pos;
	soundSource[i]->Unlink();
	soundSource[i]->Link(sounds[Num]);
	soundSource[i]->Play();
	return true;


}
void MoveSound(Transform& would,float LookRenge)
{
	if(!isinitsound)
		return;
	for(int i=0;i<MAX_soundSource;i++)
	{
		if(soundSource[i]->State==AL_PLAYING)
		{
			Vertex3f FirstSoundPoint,lastSoundPoint,SoundVelocity;
			Vector3d Pos3d;
			Pos3d=would.Matrix() * soundSourcePos[i] + would.RefPos();
			FirstSoundPoint=Vertex3f((float)Pos3d(0)/LookRenge,(float)Pos3d(1)/LookRenge,(float)Pos3d(2)/LookRenge);
			lastSoundPoint=soundSource[i]->GetPosition();
			soundSource[i]->SetVelocity(FirstSoundPoint-lastSoundPoint);
			
			soundSource[i]->SetPosition(FirstSoundPoint);
		}
	}

}
void PlaymissleWarning(int Num)
{

	if((Num<0)||(Num>=MAX_missleWarning))
		return;
	if(missleWarning[Num]->Time<0.001)
		return;
	if(voiceSource->State==AL_PLAYING)
		return;
	voiceSource->Unlink();
	voiceSource->Link(missleWarning[Num]);
	voiceSource->Play();



}
void Playfox2voice(int Num)
{

	if((Num<0)||(Num>=MAX_fox2voice))
		return;
	if(fox2voice[Num]->Time<0.001)
		return;
	if(voiceSourceAWACS->State==AL_PLAYING)
		return;
	voiceSourceAWACS->Unlink();
	voiceSourceAWACS->Link(fox2voice[Num]);
	voiceSourceAWACS->Play();
	if(Num==0)
		MyFont.inputTxt("《ＦＯＸ２！》");
	if(Num==1)
		MyFont.inputTxt("《ＦＯＸ２！ＦＯＸ２！》");
	if(Num==2)
		MyFont.inputTxt("《ＦＯＸ２》");


}
void Playhitvoice(int Num)
{

	if((Num<0)||(Num>=MAX_hitvoice))
		return;
	if(hitvoice[Num]->Time<0.001)
		return;
	if(voiceSourceAWACS->State==AL_PLAYING)
		return;
	voiceSourceAWACS->Unlink();
	voiceSourceAWACS->Link(hitvoice[Num]);
	voiceSourceAWACS->Play();
	if(Num==0)
		MyFont.inputTxt("《导弹命中！》");
	if(Num==1)
		MyFont.inputTxt("《击中目标！》");
	if(Num==2)
		MyFont.inputTxt("《导弹命中！》");
	if(Num==3)
		MyFont.inputTxt("《目标命中！》");

}
void Playkillvoice(int Num)
{

	if((Num<0)||(Num>=MAX_killvoice))
		return;
	if(killvoice[Num]->Time<0.001)
		return;
	if(voiceSource->State==AL_PLAYING)
		return;
	voiceSource->Unlink();
	voiceSource->Link(killvoice[Num]);
	voiceSource->Play();


}
void Playmissvoice(int Num)
{

	if((Num<0)||(Num>=MAX_missvoice))
		return;
	if(missvoice[Num]->Time<0.001)
		return;
	if(voiceSourceAWACS->State==AL_PLAYING)
		return;
	voiceSourceAWACS->Unlink();
	voiceSourceAWACS->Link(missvoice[Num]);
	voiceSourceAWACS->Play();
	if(Num==0)
		MyFont.inputTxt("《没有命中，被躲开了》");
	if(Num==1)
		MyFont.inputTxt("《ＭＩＳＳ！》");
	if(Num==2)
		MyFont.inputTxt("《导弹丢失目标！》");
	if(Num==3)
		MyFont.inputTxt("《ＭＩＳＳ》");

}