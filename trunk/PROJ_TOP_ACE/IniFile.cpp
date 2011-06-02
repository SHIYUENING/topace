#include"IniFile.h"
#include <windows.h>
#include <stdio.h>	
tGameSet GameSet;
tSoundSet SoundSet;
tJoyStictSet JoyStictSet;
tKeyBoardSet KeyBoardSet;
float GetIniFloat2(wchar_t * lpAppName,wchar_t * lpKeyName,const wchar_t * lpFileName,const wchar_t * DefChar)
{
	wchar_t ReadIniTMP[512];
	float IniFloat=0.0f;
	GetPrivateProfileStringW(lpAppName,lpKeyName,DefChar,ReadIniTMP,512,lpFileName);
	swscanf_s(ReadIniTMP,L"%f",&IniFloat);
	return IniFloat;
}
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
		WritePrivateProfileStringW(L"other",L"TouchMoveOverride",L"1",IniFileName);
		WritePrivateProfileStringW(L"other",L"TouchZoomOverride",L"1",IniFileName);

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

		GameSet.winW=GetPrivateProfileIntW(L"GameSet",L"winW",800,IniFileName);GameSet.winW=GameSet.winW-GameSet.winW%4;
		GameSet.winH=GetPrivateProfileIntW(L"GameSet",L"winH",600,IniFileName);GameSet.winH=GameSet.winH-GameSet.winH%4;
		GameSet.bits=GetPrivateProfileIntW(L"GameSet",L"bits",32,IniFileName);
		GameSet.depth=GetPrivateProfileIntW(L"GameSet",L"depth",24,IniFileName);
		if(GetPrivateProfileIntW(L"GameSet",L"isFullScreem",0,IniFileName)>0)
			GameSet.isFullScreem=true;
		else
			GameSet.isFullScreem=false;
		if(GetPrivateProfileIntW(L"GameSet",L"SYNC",0,IniFileName)>0)
			GameSet.SYNC=true;
		else
			GameSet.SYNC=false;
		if(GetPrivateProfileIntW(L"GameSet",L"LOW",0,IniFileName)>0)
			GameSet.LOW=true;
		else
			GameSet.LOW=false;
		
		GameSet.AA=GetPrivateProfileIntW(L"GameSet",L"AA",0,IniFileName);
		GameSet.AF=float(GetPrivateProfileIntW(L"GameSet",L"AF",1,IniFileName));
		GameSet.FPS=GetPrivateProfileIntW(L"GameSet",L"FPS",60,IniFileName);
		GameSet.Light=GetPrivateProfileIntW(L"GameSet",L"Light",0,IniFileName);
		GameSet.Water=GetPrivateProfileIntW(L"GameSet",L"Water",0,IniFileName);
		GameSet.Bloom=GetPrivateProfileIntW(L"GameSet",L"Bloom",0,IniFileName);
		GameSet.SSAO=GetPrivateProfileIntW(L"GameSet",L"SSAO",0,IniFileName);
		GameSet.Shadow=GetPrivateProfileIntW(L"GameSet",L"Shadow",0,IniFileName);
		GameSet.MoveBlur=GetPrivateProfileIntW(L"GameSet",L"MoveBlur",0,IniFileName);
		GameSet.Cloud=GetPrivateProfileIntW(L"GameSet",L"Cloud",0,IniFileName);
		
		//GameSet.TouchMoveOverride=(float)GetPrivateProfileIntW(L"other",L"TouchMoveOverride",1,IniFileName);
		//GameSet.TouchZoomOverride=(float)GetPrivateProfileIntW(L"other",L"TouchZoomOverride",1,IniFileName);
		GameSet.TouchMoveOverride=GetIniFloat2(L"other",L"TouchMoveOverride",IniFileName,L"1.0f");
		GameSet.TouchZoomOverride=GetIniFloat2(L"other",L"TouchZoomOverride",IniFileName,L"1.0f");
		GameSet.TouchPosFixX=GetIniFloat2(L"other",L"TouchPosFixX",IniFileName,L"0.0");
		GameSet.TouchPosFixY=GetIniFloat2(L"other",L"TouchPosFixY",IniFileName,L"0.0");
		GameSet.TouchPosFixRange=GetIniFloat2(L"other",L"TouchPosFixRange",IniFileName,L"20.0");

		SoundSet.BGM=GetPrivateProfileIntW(L"SoundSet",L"BGM",100,IniFileName);
		SoundSet.Effect=GetPrivateProfileIntW(L"SoundSet",L"Effect",100,IniFileName);
		SoundSet.Voice=GetPrivateProfileIntW(L"SoundSet",L"Voice",100,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_UP]			=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_UP",			32,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_DOWN]		=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_DOWN",			22,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_LEFT]		=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_LEFT",			12,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_RIGHT]		=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_RIGHT",		2,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_MAIN_WEAPON]	=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_MAIN_WEAPON",	11,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_SUB_WEAPON]	=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_SUB_WEAPON",	1,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_LOCK]		=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_LOCK",			31,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_MAP]			=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_MAP",			21,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_SPEED_UP]	=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_SPEED_UP",		41,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_SPEED_DOWN]	=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_SPEED_DOWN",	51,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_L]			=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_L",			61,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_R]			=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_R",			71,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_VIEW_UP]		=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_VIEW_UP",		52,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_VIEW_DOWN]	=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_VIEW_DOWN",	42,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_VIEW_LEFT]	=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_VIEW_LEFT",	112,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_VIEW_RIGHT]	=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_VIEW_RIGHT",	102,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_VIEW_RESET]	=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_VIEW_RESET",	111,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_SELECT]		=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_SELECT",		81,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_START]		=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_START",		91,IniFileName);
		JoyStictSet.KeySet[JOY_KEY_NO_USE]		=GetPrivateProfileIntW(L"JoyStictSet",L"JOY_KEY_NO_USE",		101,IniFileName);

		KeyBoardSet.KeySet[JOY_KEY_UP]			=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_UP",			119,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_DOWN]		=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_DOWN",			115,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_LEFT]		=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_LEFT",			97,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_RIGHT]		=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_RIGHT",		100,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_MAIN_WEAPON]	=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_MAIN_WEAPON",	102,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_SUB_WEAPON]	=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_SUB_WEAPON",	101,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_LOCK]		=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_LOCK",			113,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_MAP]			=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_MAP",			116,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_SPEED_UP]	=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_SPEED_UP",		38,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_SPEED_DOWN]	=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_SPEED_DOWN",	40,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_L]			=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_L",			37,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_R]			=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_R",			39,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_VIEW_UP]		=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_VIEW_UP",		56,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_VIEW_DOWN]	=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_VIEW_DOWN",	50,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_VIEW_LEFT]	=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_VIEW_LEFT",	52,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_VIEW_RIGHT]	=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_VIEW_RIGHT",	54,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_VIEW_RESET]	=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_VIEW_RESET",	53,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_SELECT]		=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_SELECT",		118,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_START]		=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_START",		98,IniFileName);
		KeyBoardSet.KeySet[JOY_KEY_NO_USE]		=GetPrivateProfileIntW(L"KeyBoardSet",L"JOY_KEY_NO_USE",		96,IniFileName);
}
