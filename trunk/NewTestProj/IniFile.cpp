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
	IntFile=fopen(".\\gameset.ini","r");
	if (IntFile)
	{
		fclose(IntFile);

	}
	else
	{
		WritePrivateProfileString("GameSet","winW","800",".\\gameset.ini");
		WritePrivateProfileString("GameSet","winH","600",".\\gameset.ini");
		WritePrivateProfileString("GameSet","bits","32",".\\gameset.ini");
		WritePrivateProfileString("GameSet","depth","24",".\\gameset.ini");
		WritePrivateProfileString("GameSet","isFullScreem","0",".\\gameset.ini");
		WritePrivateProfileString("GameSet","LOW","0",".\\gameset.ini");
		WritePrivateProfileString("GameSet","AA","0",".\\gameset.ini");
		WritePrivateProfileString("GameSet","Light","0",".\\gameset.ini");
		WritePrivateProfileString("GameSet","Water","0",".\\gameset.ini");
		WritePrivateProfileString("GameSet","Bloom","0",".\\gameset.ini");
		WritePrivateProfileString("GameSet","Shadow","0",".\\gameset.ini");
		WritePrivateProfileString("GameSet","MoveBlur","0",".\\gameset.ini");
		WritePrivateProfileString("GameSet","Cloud","0",".\\gameset.ini");
		WritePrivateProfileString("SoundSet","BGM","100",".\\gameset.ini");
		WritePrivateProfileString("SoundSet","Effect","100",".\\gameset.ini");
		WritePrivateProfileString("SoundSet","Voice","100",".\\gameset.ini");

		WritePrivateProfileString("JoyStictSet","JOY_KEY_UP","32",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_DOWN","22",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_LEFT","12",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_RIGHT","2",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_MAIN_WEAPON","11",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_SUB_WEAPON","1",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_LOCK","31",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_MAP","21",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_SPEED_UP","41",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_SPEED_DOWN","51",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_L","61",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_R","71",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_VIEW_UP","52",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_VIEW_DOWN","42",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_VIEW_LEFT","112",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_VIEW_RIGHT","102",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_VIEW_RESET","111",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_SELECT","81",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_START","91",".\\gameset.ini");
		WritePrivateProfileString("JoyStictSet","JOY_KEY_NO_USE","101",".\\gameset.ini");


		WritePrivateProfileString("KeyBoardSet","JOY_KEY_UP","119",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_DOWN","115",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_LEFT","97",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_RIGHT","100",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_MAIN_WEAPON","102",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_SUB_WEAPON","101",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_LOCK","113",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_MAP","116",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_SPEED_UP","38",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_SPEED_DOWN","40",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_L","37",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_R","39",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_VIEW_UP","56",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_VIEW_DOWN","50",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_VIEW_LEFT","52",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_VIEW_RIGHT","54",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_VIEW_RESET","53",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_SELECT","118",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_START","98",".\\gameset.ini");
		WritePrivateProfileString("KeyBoardSet","JOY_KEY_NO_USE","96",".\\gameset.ini");
	}

		GameSet.winW=GetPrivateProfileInt("GameSet","winW",800,".\\gameset.ini");
		GameSet.winH=GetPrivateProfileInt("GameSet","winH",600,".\\gameset.ini");
		GameSet.bits=GetPrivateProfileInt("GameSet","bits",32,".\\gameset.ini");
		GameSet.depth=GetPrivateProfileInt("GameSet","depth",24,".\\gameset.ini");
		if(GetPrivateProfileInt("GameSet","isFullScreem",0,".\\gameset.ini")>0)
			GameSet.isFullScreem=true;
		else
			GameSet.isFullScreem=false;
		if(GetPrivateProfileInt("GameSet","LOW",0,".\\gameset.ini")>0)
			GameSet.LOW=true;
		else
			GameSet.LOW=false;
		GameSet.AA=GetPrivateProfileInt("GameSet","AA",0,".\\gameset.ini");
		GameSet.Light=GetPrivateProfileInt("GameSet","Light",0,".\\gameset.ini");
		GameSet.Water=GetPrivateProfileInt("GameSet","Water",0,".\\gameset.ini");
		GameSet.Bloom=GetPrivateProfileInt("GameSet","Bloom",0,".\\gameset.ini");
		GameSet.Shadow=GetPrivateProfileInt("GameSet","Shadow",0,".\\gameset.ini");
		GameSet.MoveBlur=GetPrivateProfileInt("GameSet","MoveBlur",0,".\\gameset.ini");
		GameSet.Cloud=GetPrivateProfileInt("GameSet","Cloud",0,".\\gameset.ini");

		SoundSet.BGM=GetPrivateProfileInt("SoundSet","BGM",100,".\\gameset.ini");
		SoundSet.Effect=GetPrivateProfileInt("SoundSet","Effect",100,".\\gameset.ini");
		SoundSet.Voice=GetPrivateProfileInt("SoundSet","Voice",100,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_UP]			=GetPrivateProfileInt("JoyStictSet","JOY_KEY_UP",			32,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_DOWN]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_DOWN",			22,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_LEFT]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_LEFT",			12,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_RIGHT]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_RIGHT",		2,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_MAIN_WEAPON]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_MAIN_WEAPON",	11,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_SUB_WEAPON]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_SUB_WEAPON",	1,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_LOCK]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_LOCK",			31,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_MAP]			=GetPrivateProfileInt("JoyStictSet","JOY_KEY_MAP",			21,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_SPEED_UP]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_SPEED_UP",		41,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_SPEED_DOWN]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_SPEED_DOWN",	51,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_L]			=GetPrivateProfileInt("JoyStictSet","JOY_KEY_L",			61,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_R]			=GetPrivateProfileInt("JoyStictSet","JOY_KEY_R",			71,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_VIEW_UP]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_VIEW_UP",		52,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_VIEW_DOWN]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_VIEW_DOWN",	42,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_VIEW_LEFT]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_VIEW_LEFT",	112,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_VIEW_RIGHT]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_VIEW_RIGHT",	102,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_VIEW_RESET]	=GetPrivateProfileInt("JoyStictSet","JOY_KEY_VIEW_RESET",	111,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_SELECT]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_SELECT",		81,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_START]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_START",		91,".\\gameset.ini");
		JoyStictSet.KeySet[JOY_KEY_NO_USE]		=GetPrivateProfileInt("JoyStictSet","JOY_KEY_NO_USE",		101,".\\gameset.ini");

		KeyBoardSet.KeySet[JOY_KEY_UP]			=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_UP",			119,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_DOWN]		=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_DOWN",			115,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_LEFT]		=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_LEFT",			97,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_RIGHT]		=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_RIGHT",		100,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_MAIN_WEAPON]	=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_MAIN_WEAPON",	102,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_SUB_WEAPON]	=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_SUB_WEAPON",	101,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_LOCK]		=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_LOCK",			113,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_MAP]			=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_MAP",			116,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_SPEED_UP]	=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_SPEED_UP",		38,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_SPEED_DOWN]	=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_SPEED_DOWN",	40,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_L]			=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_L",			37,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_R]			=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_R",			39,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_VIEW_UP]		=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_VIEW_UP",		56,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_VIEW_DOWN]	=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_VIEW_DOWN",	50,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_VIEW_LEFT]	=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_VIEW_LEFT",	52,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_VIEW_RIGHT]	=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_VIEW_RIGHT",	54,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_VIEW_RESET]	=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_VIEW_RESET",	53,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_SELECT]		=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_SELECT",		118,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_START]		=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_START",		98,".\\gameset.ini");
		KeyBoardSet.KeySet[JOY_KEY_NO_USE]		=GetPrivateProfileInt("KeyBoardSet","JOY_KEY_NO_USE",		96,".\\gameset.ini");
}
