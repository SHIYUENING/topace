
#include "stdafx.h"
#include"IniFile.h"
tGameSet GameSet;
tSoundSet SoundSet;
tJoyStictSet JoyStictSet;
tKeyBoardSet KeyBoardSet;

wchar_t Writeini[64]={0};
void loadIniFile()
{
	FILE *IntFile=NULL;
	fopen_s(&IntFile,".\\gameset.ini","r");
	if (IntFile)
	{
		fclose(IntFile);

	}
	else
	{
		WritePrivateProfileString(_T("GameSet"),_T("winW"),_T("800"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("winH"),_T("600"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("bits"),_T("32"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("depth"),_T("24"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("isFullScreem"),_T("0"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("SYNC"),_T("0"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("LOW"),_T("0"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("AA"),_T("0"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("Light"),_T("0"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("Water"),_T("0"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("Bloom"),_T("0"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("Shadow"),_T("0"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("MoveBlur"),_T("0"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("GameSet"),_T("Cloud"),_T("0"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("SoundSet"),_T("BGM"),_T("100"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("SoundSet"),_T("Effect"),_T("100"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("SoundSet"),_T("Voice"),_T("100"),_T(".\\gameset.ini"));

		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_UP"),_T("32"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_DOWN"),_T("22"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_LEFT"),_T("12"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_RIGHT"),_T("2"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_MAIN_WEAPON"),_T("11"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SUB_WEAPON"),_T("1"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_LOCK"),_T("31"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_MAP"),_T("21"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SPEED_UP"),_T("41"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SPEED_DOWN"),_T("51"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_L"),_T("61"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_R"),_T("71"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_UP"),_T("52"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_DOWN"),_T("42"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_LEFT"),_T("112"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_RIGHT"),_T("102"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_RESET"),_T("111"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SELECT"),_T("81"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_START"),_T("91"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_NO_USE"),_T("101"),_T(".\\gameset.ini"));


		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_UP"),_T("119"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_DOWN"),_T("115"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_LEFT"),_T("97"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_RIGHT"),_T("100"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_MAIN_WEAPON"),_T("102"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_SUB_WEAPON"),_T("101"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_LOCK"),_T("113"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_MAP"),_T("116"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_SPEED_UP"),_T("38"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_SPEED_DOWN"),_T("40"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_L"),_T("37"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_R"),_T("39"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_UP"),_T("56"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_DOWN"),_T("50"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_LEFT"),_T("52"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_RIGHT"),_T("54"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_RESET"),_T("53"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_SELECT"),_T("118"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_START"),_T("98"),_T(".\\gameset.ini"));
		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_NO_USE"),_T("96"),_T(".\\gameset.ini"));
	}

		GameSet.winW=GetPrivateProfileInt(_T("GameSet"),_T("winW"),800,_T(".\\gameset.ini"));
		GameSet.winH=GetPrivateProfileInt(_T("GameSet"),_T("winH"),600,_T(".\\gameset.ini"));
		GameSet.bits=GetPrivateProfileInt(_T("GameSet"),_T("bits"),32,_T(".\\gameset.ini"));
		GameSet.depth=GetPrivateProfileInt(_T("GameSet"),_T("depth"),24,_T(".\\gameset.ini"));
		if(GetPrivateProfileInt(_T("GameSet"),_T("isFullScreem"),0,_T(".\\gameset.ini"))>0)
			GameSet.isFullScreem=true;
		else
			GameSet.isFullScreem=false;
		if(GetPrivateProfileInt(_T("GameSet"),_T("SYNC"),0,_T(".\\gameset.ini"))>0)
			GameSet.SYNC=true;
		else
			GameSet.SYNC=false;
		if(GetPrivateProfileInt(_T("GameSet"),_T("LOW"),0,_T(".\\gameset.ini"))>0)
			GameSet.LOW=true;
		else
			GameSet.LOW=false;
		GameSet.AA=GetPrivateProfileInt(_T("GameSet"),_T("AA"),0,_T(".\\gameset.ini"));
		GameSet.Light=GetPrivateProfileInt(_T("GameSet"),_T("Light"),0,_T(".\\gameset.ini"));
		GameSet.Water=GetPrivateProfileInt(_T("GameSet"),_T("Water"),0,_T(".\\gameset.ini"));
		GameSet.Bloom=GetPrivateProfileInt(_T("GameSet"),_T("Bloom"),0,_T(".\\gameset.ini"));
		GameSet.Shadow=GetPrivateProfileInt(_T("GameSet"),_T("Shadow"),0,_T(".\\gameset.ini"));
		GameSet.MoveBlur=GetPrivateProfileInt(_T("GameSet"),_T("MoveBlur"),0,_T(".\\gameset.ini"));
		GameSet.Cloud=GetPrivateProfileInt(_T("GameSet"),_T("Cloud"),0,_T(".\\gameset.ini"));

		SoundSet.BGM=GetPrivateProfileInt(_T("SoundSet"),_T("BGM"),100,_T(".\\gameset.ini"));
		SoundSet.Effect=GetPrivateProfileInt(_T("SoundSet"),_T("Effect"),100,_T(".\\gameset.ini"));
		SoundSet.Voice=GetPrivateProfileInt(_T("SoundSet"),_T("Voice"),100,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_UP]			=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_UP"),			32,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_DOWN]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_DOWN"),			22,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_LEFT]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_LEFT"),			12,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_RIGHT]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_RIGHT"),		2,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_MAIN_WEAPON]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_MAIN_WEAPON"),	11,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_SUB_WEAPON]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_SUB_WEAPON"),	1,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_LOCK]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_LOCK"),			31,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_MAP]			=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_MAP"),			21,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_SPEED_UP]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_SPEED_UP"),		41,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_SPEED_DOWN]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_SPEED_DOWN"),	51,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_L]			=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_L"),			61,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_R]			=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_R"),			71,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_VIEW_UP]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_VIEW_UP"),		52,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_VIEW_DOWN]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_VIEW_DOWN"),	42,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_VIEW_LEFT]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_VIEW_LEFT"),	112,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_VIEW_RIGHT]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_VIEW_RIGHT"),	102,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_VIEW_RESET]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_VIEW_RESET"),	111,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_SELECT]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_SELECT"),		81,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_START]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_START"),		91,_T(".\\gameset.ini"));
		JoyStictSet.KeySet[JOY_KEY_NO_USE]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_NO_USE"),		101,_T(".\\gameset.ini"));

		KeyBoardSet.KeySet[JOY_KEY_UP]			=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_UP"),			119,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_DOWN]		=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_DOWN"),			115,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_LEFT]		=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_LEFT"),			97,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_RIGHT]		=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_RIGHT"),		100,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_MAIN_WEAPON]	=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_MAIN_WEAPON"),	102,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_SUB_WEAPON]	=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_SUB_WEAPON"),	101,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_LOCK]		=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_LOCK"),			113,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_MAP]			=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_MAP"),			116,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_SPEED_UP]	=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_SPEED_UP"),		38,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_SPEED_DOWN]	=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_SPEED_DOWN"),	40,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_L]			=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_L"),			37,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_R]			=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_R"),			39,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_VIEW_UP]		=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_UP"),		56,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_VIEW_DOWN]	=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_DOWN"),	50,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_VIEW_LEFT]	=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_LEFT"),	52,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_VIEW_RIGHT]	=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_RIGHT"),	54,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_VIEW_RESET]	=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_RESET"),	53,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_SELECT]		=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_SELECT"),		118,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_START]		=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_START"),		98,_T(".\\gameset.ini"));
		KeyBoardSet.KeySet[JOY_KEY_NO_USE]		=GetPrivateProfileInt(_T("KeyBoardSet"),_T("JOY_KEY_NO_USE"),		96,_T(".\\gameset.ini"));
}

void SaveIniFile()
{
	//char Writeini[256]={0};
	//sprintf_s(Writeini,sizeof(Writeini),"%d",GameSet.winW);
	//CString Writeini;
	//Writeini.Format(_T("%d"),GameSet.winW);
	_itow_s(GameSet.winW,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("winW"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.winH,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("winH"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.bits,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("bits"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.depth,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("depth"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.isFullScreem,Writeini,sizeof(Writeini),10);	WritePrivateProfileString(_T("GameSet"),_T("isFullScreem"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.SYNC,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("SYNC"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.LOW,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("LOW"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.AA,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("AA"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.Light,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("Light"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.Water,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("Water"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.Bloom,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("Bloom"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.Shadow,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("Shadow"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.MoveBlur,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("MoveBlur"),Writeini,_T(".\\gameset.ini"));
	_itow_s(GameSet.Cloud,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("Cloud"),Writeini,_T(".\\gameset.ini"));

	_itow_s(SoundSet.BGM,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("SoundSet"),_T("BGM"),Writeini,_T(".\\gameset.ini"));
	_itow_s(SoundSet.Effect,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("SoundSet"),_T("Effect"),Writeini,_T(".\\gameset.ini"));
	_itow_s(SoundSet.Voice,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("SoundSet"),_T("Voice"),Writeini,_T(".\\gameset.ini"));

	_itow_s(JoyStictSet.KeySet[JOY_KEY_UP],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_UP"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_DOWN],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_DOWN"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_LEFT],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_LEFT"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_RIGHT],Writeini,sizeof(Writeini),10);	WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_RIGHT"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_MAIN_WEAPON],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_MAIN_WEAPON"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_SUB_WEAPON],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SUB_WEAPON"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_LOCK],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_LOCK"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_MAP],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_MAP"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_SPEED_UP],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SPEED_UP"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_SPEED_DOWN],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SPEED_DOWN"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_L],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_L"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_R],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_R"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_VIEW_UP],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_UP"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_VIEW_DOWN],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_DOWN"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_VIEW_LEFT],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_LEFT"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_VIEW_RIGHT],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_RIGHT"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_VIEW_RESET],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_RESET"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_SELECT],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SELECT"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_START],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_START"),Writeini,_T(".\\gameset.ini"));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_NO_USE],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_NO_USE"),Writeini,_T(".\\gameset.ini"));

	_itow_s(KeyBoardSet.KeySet[JOY_KEY_UP],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_UP"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_DOWN],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_DOWN"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_LEFT],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_LEFT"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_RIGHT],Writeini,sizeof(Writeini),10);	WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_RIGHT"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_MAIN_WEAPON],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_MAIN_WEAPON"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_SUB_WEAPON],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_SUB_WEAPON"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_LOCK],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_LOCK"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_MAP],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_MAP"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_SPEED_UP],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_SPEED_UP"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_SPEED_DOWN],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_SPEED_DOWN"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_L],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_L"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_R],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_R"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_VIEW_UP],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_UP"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_VIEW_DOWN],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_DOWN"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_VIEW_LEFT],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_LEFT"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_VIEW_RIGHT],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_RIGHT"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_VIEW_RESET],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_VIEW_RESET"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_SELECT],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_SELECT"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_START],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_START"),Writeini,_T(".\\gameset.ini"));
	_itow_s(KeyBoardSet.KeySet[JOY_KEY_NO_USE],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("KeyBoardSet"),_T("JOY_KEY_NO_USE"),Writeini,_T(".\\gameset.ini"));
}