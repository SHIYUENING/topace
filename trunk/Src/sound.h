#pragma once
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>
#include   <time.h>
#include <conio.h>
#include "fmod.hpp"
#include "fmod_errors.h"

#pragma comment( lib, "fmodex_vc.lib" )	

FMOD_SYSTEM* sys;
FMOD_SOUND* sound1;
FMOD_SOUND* sound2;
FMOD_SOUND* voice1;
FMOD_SOUND* voice2;
FMOD_SOUND* voice3;
FMOD_SOUND* voice4;
FMOD_SOUND* voice5;
FMOD_SOUND* missleWarning[10];
FMOD_SOUND* fox2voice[3];
FMOD_SOUND* hitvoice[4];
FMOD_SOUND* killvoice[7];
FMOD_SOUND* missvoice[4];
FMOD_SOUND* BGMsound;
FMOD_CHANNEL* channel1;
FMOD_CHANNEL* channel2;
FMOD_CHANNEL* channelvoice1;
FMOD_CHANNEL* channelvoice2;
FMOD_CHANNEL* channelvoice3;
FMOD_CHANNEL* channelvoice4;
FMOD_CHANNEL* missleWarningchannel;
FMOD_CHANNEL* fox2voicechannel;
FMOD_CHANNEL* hitvoicechannel;
FMOD_CHANNEL* killvoicechannel;
FMOD_CHANNEL* missvoicechannel;
FMOD_CHANNEL* BGMchannel;
FMOD_VECTOR pos;

void initsound()
{
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
	FMOD_System_CreateSound(sys, "Data/voice/hit.WAV", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE, 0, &voice1);
	FMOD_System_CreateSound(sys, "Data/voice/fox.WAV", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE, 0, &voice2);
	FMOD_System_CreateSound(sys, "Data/voice/miss.WAV", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE, 0, &voice3);
	FMOD_System_CreateSound(sys, "Data/voice/destroy.wav", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE, 0, &voice4);
	FMOD_System_CreateSound(sys, "Data/voice/midi.mp3", FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE|FMOD_CREATESAMPLE, 0, &voice5);
	FMOD_System_CreateSound(sys, "Data/BGM.mp3", FMOD_LOOP_NORMAL | FMOD_2D | FMOD_CREATECOMPRESSEDSAMPLE, 0, &BGMsound);
	FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, BGMsound, 0, &BGMchannel);
	//FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound, 0, &channel);

}