#include"IniFile.h"
#include <windows.h>
#include <stdio.h>	
tGameSet GameSet;
tSoundSet SoundSet;
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
	}
}