#ifndef _INIFILE_H
#define _INIFILE_H

struct tGameSet
{
	int winW;
	int winH;
	int bits;
	int depth;
	bool isFullScreem;
	bool LOW;
	int AA;
	int Light;
	int Water;
	int Bloom;
	int Shadow;
	int MoveBlur;
	int Cloud;
};
struct tSoundSet
{
	int Effect;
	int Voice;
	int BGM;
};
void loadIniFile();
#endif