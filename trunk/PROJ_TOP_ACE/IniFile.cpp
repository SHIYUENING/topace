#include"IniFile.h"
#include <windows.h>
#include <stdio.h>	
tGameSet GameSet;
tSoundSet SoundSet;
tJoyStictSet JoyStictSet;
tKeyBoardSet KeyBoardSet;
void loadIniFile()
{

	FILE *IntFile=NULL;
	//IntFile=fopen(".\\gameset.ini","r");
	IntFile=_wfopen(IniFileName,L"r");
	if (IntFile)
	{
		fclose(IntFile);

	}
	else
	{
		WritePrivateProfileStringW(L"GameSet",L"winW",L"800",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"winH",L"600",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"bits",L"32",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"depth",L"24",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"isFullScreem",L"0",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"SYNC",L"0",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"LOW",L"0",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"AA",L"0",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"AF",L"1",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"FPS",L"60",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"Light",L"0",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"Water",L"0",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"Bloom",L"0",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"SSAO",L"0",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"Shadow",L"0",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"MoveBlur",L"0",IniFileName);
		WritePrivateProfileStringW(L"GameSet",L"Cloud",L"0",IniFileName);
		WritePrivateProfileStringW(L"SoundSet",L"BGM",L"100",IniFileName);
		WritePrivateProfileStringW(L"SoundSet",L"Effect",L"100",IniFileName);
		WritePrivateProfileStringW(L"SoundSet",L"Voice",L"100",IniFileName);

		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_UP",L"32",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_DOWN",L"22",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_LEFT",L"12",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_RIGHT",L"2",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_MAIN_WEAPON",L"11",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_SUB_WEAPON",L"1",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_LOCK",L"31",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_MAP",L"21",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_SPEED_UP",L"41",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_SPEED_DOWN",L"51",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_L",L"61",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_R",L"71",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_VIEW_UP",L"52",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_VIEW_DOWN",L"42",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_VIEW_LEFT",L"112",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_VIEW_RIGHT",L"102",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_VIEW_RESET",L"111",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_SELECT",L"81",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_START",L"91",IniFileName);
		WritePrivateProfileStringW(L"JoyStictSet",L"JOY_KEY_NO_USE",L"101",IniFileName);


		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_UP",L"119",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_DOWN",L"115",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_LEFT",L"97",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_RIGHT",L"100",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_MAIN_WEAPON",L"102",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_SUB_WEAPON",L"101",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_LOCK",L"113",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_MAP",L"116",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_SPEED_UP",L"38",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_SPEED_DOWN",L"40",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_L",L"37",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_R",L"39",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_VIEW_UP",L"56",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_VIEW_DOWN",L"50",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_VIEW_LEFT",L"52",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_VIEW_RIGHT",L"54",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_VIEW_RESET",L"53",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_SELECT",L"118",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_START",L"98",IniFileName);
		WritePrivateProfileStringW(L"KeyBoardSet",L"JOY_KEY_NO_USE",L"96",IniFileName);
	}

		GameSet.winW=GetPrivateProfileInt(L"GameSet",L"winW",800,IniFileName);GameSet.winW=GameSet.winW-GameSet.winW%4;
		GameSet.winH=GetPrivateProfileInt(L"GameSet",L"winH",600,IniFileName);GameSet.winH=GameSet.winH-GameSet.winH%4;
		GameSet.bits=GetPrivateProfileInt(L"GameSet",L"bits",32,IniFileName);
		GameSet.depth=GetPrivateProfileInt(L"GameSet",L"depth",24,IniFileName);
		if(GetPrivateProfileInt(L"GameSet",L"isFullScreem",0,IniFileName)>0)
			GameSet.isFullScreem=true;
		else
			GameSet.isFullScreem=false;
		if(GetPrivateProfileInt(L"GameSet",L"SYNC",0,IniFileName)>0)
			GameSet.SYNC=true;
		else
			GameSet.SYNC=false;
		if(GetPrivateProfileInt(L"GameSet",L"LOW",0,IniFileName)>0)
			GameSet.LOW=true;
		else
			GameSet.LOW=false;
		GameSet.AA=GetPrivateProfileInt(L"GameSet",L"AA",0,IniFileName);
		GameSet.AF=float(GetPrivateProfileInt(L"GameSet",L"AF",1,IniFileName));
		GameSet.FPS=GetPrivateProfileInt(L"GameSet",L"FPS",60,IniFileName);
		GameSet.Light=GetPrivateProfileInt(L"GameSet",L"Light",0,IniFileName);
		GameSet.Water=GetPrivateProfileInt(L"GameSet",L"Water",0,IniFileName);
		GameSet.Bloom=GetPrivateProfileInt(L"GameSet",L"Bloom",0,IniFileName);
		GameSet.SSAO=GetPrivateProfileInt(L"GameSet",L"SSAO",0,IniFileName);
		GameSet.Shadow=GetPrivateProfileInt(L"GameSet",L"Shadow",0,IniFileName);
		GameSet.MoveBlur=GetPrivateProfileInt(L"GameSet",L"MoveBlur",0,IniFileName);
		GameSet.Cloud=GetPrivateProfileInt(L"GameSet",L"Cloud",0,IniFileName);

		SoundSet.BGM=GetPrivateProfileInt(L"SoundSet",L"BGM",100,IniFileName);
		SoundSet.Effect=GetPrivateProfileInt(L"SoundSet",L"Effect",100,IniFileName);
		SoundSet.Voice=GetPrivateProfileInt(L"SoundSet",L"Voice",100,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_UP]			=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_UP",			32,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_DOWN]		=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_DOWN",			22,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_LEFT]		=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_LEFT",			12,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_RIGHT]		=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_RIGHT",		2,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_MAIN_WEAPON]	=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_MAIN_WEAPON",	11,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_SUB_WEAPON]	=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_SUB_WEAPON",	1,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_LOCK]		=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_LOCK",			31,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_MAP]			=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_MAP",			21,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_SPEED_UP]	=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_SPEED_UP",		41,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_SPEED_DOWN]	=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_SPEED_DOWN",	51,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_L]			=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_L",			61,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_R]			=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_R",			71,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_VIEW_UP]		=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_VIEW_UP",		52,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_VIEW_DOWN]	=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_VIEW_DOWN",	42,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_VIEW_LEFT]	=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_VIEW_LEFT",	112,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_VIEW_RIGHT]	=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_VIEW_RIGHT",	102,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_VIEW_RESET]	=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_VIEW_RESET",	111,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_SELECT]		=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_SELECT",		81,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_START]		=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_START",		91,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_NO_USE]		=GetPrivateProfileInt(L"JoyStictSet",L"JOY_KEY_NO_USE",		101,IniFileName);

		KeyBoardSet.KeySet[JOY_KEY_UP]			=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_UP",			119,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_DOWN]		=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_DOWN",			115,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_LEFT]		=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_LEFT",			97,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_RIGHT]		=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_RIGHT",		100,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_MAIN_WEAPON]	=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_MAIN_WEAPON",	102,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_SUB_WEAPON]	=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_SUB_WEAPON",	101,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_LOCK]		=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_LOCK",			113,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_MAP]			=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_MAP",			116,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_SPEED_UP]	=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_SPEED_UP",		38,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_SPEED_DOWN]	=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_SPEED_DOWN",	40,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_L]			=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_L",			37,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_R]			=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_R",			39,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_VIEW_UP]		=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_VIEW_UP",		56,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_VIEW_DOWN]	=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_VIEW_DOWN",	50,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_VIEW_LEFT]	=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_VIEW_LEFT",	52,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_VIEW_RIGHT]	=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_VIEW_RIGHT",	54,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_VIEW_RESET]	=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_VIEW_RESET",	53,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_SELECT]		=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_SELECT",		118,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_START]		=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_START",		98,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_NO_USE]		=GetPrivateProfileInt(L"KeyBoardSet",L"JOY_KEY_NO_USE",		96,IniFileName);
}
