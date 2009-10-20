#include"IniFile.h"
#include <windows.h>
#include <stdio.h>	
tGameSet GameSet;
tSoundSet SoundSet;
tJoyStictSet JoyStictSet;
void loadIniFile()
{
	FILE *IntFile=NULL;
	IntFile=fopen(".\\set.ini","r");
	if (IntFile)
	{
		fclose(IntFile);
		GameSet.winW=GetPrivateProfileInt("GameSet","winW",800,".\\set.ini");
		GameSet.winH=GetPrivateProfileInt("GameSet","winH",600,".\\set.ini");
		GameSet.bits=GetPrivateProfileInt("GameSet","bits",32,".\\set.ini");
		GameSet.depth=GetPrivateProfileInt("GameSet","depth",24,".\\set.ini");
		if(GetPrivateProfileInt("GameSet","isFullScreem",0,".\\set.ini")>0)
			GameSet.isFullScreem=true;
		else
			GameSet.isFullScreem=false;
		if(GetPrivateProfileInt("GameSet","LOW",0,".\\set.ini")>0)
			GameSet.LOW=true;
		else
			GameSet.LOW=false;
		GameSet.AA=GetPrivateProfileInt("GameSet","AA",0,".\\set.ini");
		GameSet.Light=GetPrivateProfileInt("GameSet","Light",0,".\\set.ini");
		GameSet.Water=GetPrivateProfileInt("GameSet","Water",0,".\\set.ini");
		GameSet.Bloom=GetPrivateProfileInt("GameSet","Bloom",0,".\\set.ini");
		GameSet.Shadow=GetPrivateProfileInt("GameSet","Shadow",0,".\\set.ini");
		GameSet.MoveBlur=GetPrivateProfileInt("GameSet","MoveBlur",0,".\\set.ini");
		GameSet.Cloud=GetPrivateProfileInt("GameSet","Cloud",0,".\\set.ini");

		SoundSet.BGM=GetPrivateProfileInt("SoundSet","BGM",100,".\\set.ini");
		SoundSet.Effect=GetPrivateProfileInt("SoundSet","Effect",100,".\\set.ini");
		SoundSet.Voice=GetPrivateProfileInt("SoundSet","Voice",100,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_UP]			=GetPrivateProfileInt("JoyStictSet","JOY_KEY_UP",			32,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_DOWN]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_DOWN",			22,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_LEFT]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_LEFT",			12,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_RIGHT]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_RIGHT",		2,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_MAIN_WEAPON]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_MAIN_WEAPON",	11,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_SUB_WEAPON]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_SUB_WEAPON",	1,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_LOCK]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_LOCK",			31,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_MAP]			=GetPrivateProfileInt("JoyStictSet","JOY_KEY_MAP",			21,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_SPEED_UP]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_SPEED_UP",		41,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_SPEED_DOWN]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_SPEED_DOWN",	51,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_L]			=GetPrivateProfileInt("JoyStictSet","JOY_KEY_L",			61,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_R]			=GetPrivateProfileInt("JoyStictSet","JOY_KEY_R",			71,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_VIEW_UP]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_VIEW_UP",		52,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_VIEW_DOWN]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_VIEW_DOWN",	42,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_VIEW_LEFT]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_VIEW_LEFT",	112,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_VIEW_RIGHT]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_VIEW_RIGHT",	102,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_VIEW_RESET]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_VIEW_RESET",	111,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_SELECT]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_SELECT",		81,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_START]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_START",		91,".\\set.ini");
		JoyStictSet.KeySet[JOY_KEY_NO_USE]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_NO_USE",		101,".\\set.ini");
	}
	else
	{
		WritePrivateProfileString("GameSet","winW","800",".\\set.ini");
		WritePrivateProfileString("GameSet","winH","600",".\\set.ini");
		WritePrivateProfileString("GameSet","bits","32",".\\set.ini");
		WritePrivateProfileString("GameSet","depth","24",".\\set.ini");
		WritePrivateProfileString("GameSet","isFullScreem","0",".\\set.ini");
		WritePrivateProfileString("GameSet","LOW","0",".\\set.ini");
		WritePrivateProfileString("GameSet","AA","0",".\\set.ini");
		WritePrivateProfileString("GameSet","Light","0",".\\set.ini");
		WritePrivateProfileString("GameSet","Water","0",".\\set.ini");
		WritePrivateProfileString("GameSet","Bloom","0",".\\set.ini");
		WritePrivateProfileString("GameSet","Shadow","0",".\\set.ini");
		WritePrivateProfileString("GameSet","MoveBlur","0",".\\set.ini");
		WritePrivateProfileString("GameSet","Cloud","0",".\\set.ini");
		WritePrivateProfileString("SoundSet","BGM","100",".\\set.ini");
		WritePrivateProfileString("SoundSet","Effect","100",".\\set.ini");
		WritePrivateProfileString("SoundSet","Voice","100",".\\set.ini");

		WritePrivateProfileString("JoyStictSet","JOY_KEY_UP","32",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_DOWN","22",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_LEFT","12",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_RIGHT","2",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_MAIN_WEAPON","11",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_SUB_WEAPON","1",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_LOCK","31",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_MAP","21",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_SPEED_UP","41",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_SPEED_DOWN","51",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_L","61",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_R","71",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_VIEW_UP","52",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_VIEW_DOWN","42",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_VIEW_LEFT","112",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_VIEW_RIGHT","102",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_VIEW_RESET","111",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_SELECT","81",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_START","91",".\\set.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_NO_USE","101",".\\set.ini");
	}
}