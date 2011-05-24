#include "TABTN.h"
#include "IniFile.h"


CTABTN::CTABTN(void)
{
}


CTABTN::~CTABTN(void)
{
}


void CTABTN::loadfile(wchar_t * filename)
{
	Tex.loadfile(filename);
	Tex.LoadToVRAM();
	size[0]=Tex.TexW;
	size[1]=Tex.TexH;
}


void CTABTN::ScaleSize(float W,float H)
{
	size[0]=int(float(Tex.TexW)*W);
	size[1]=int(float(Tex.TexH)*H);
}


void CTABTN::Draw(void)
{
	if(Tex.TexType==IS_DDS)
	DrawQUADEX(
		Tex.TexID,
		Pos[0],
		Pos[0]+size[0],
		Pos[1],
		Pos[1]+size[1],
		GameSet.winW,
		GameSet.winH);
	if(Tex.TexType==IS_TGA)
	DrawQUADEX(
		Tex.TexID,
		Pos[0],
		Pos[0]+size[0],
		Pos[1]+size[1],
		Pos[1],
		GameSet.winW,
		GameSet.winH);
}


void CTABTN::SetPos(int W,int H)
{
	Pos[0]=W;
	Pos[1]=H;
}


bool CTABTN::GetCheck(int x,int y)
{
	if(x<Pos[0]) return false;
	if(y<Pos[1]) return false;
	if(x>Pos[0]+size[0]) return false;
	if(y>Pos[1]+size[1]) return false;
	return true;
}
