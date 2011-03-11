#ifndef _INIFILE_H
#define _INIFILE_H
#define IniFileName L".\\gameset.ini"
#define JOY_KEY_UP 1
#define JOY_KEY_DOWN 2
#define JOY_KEY_LEFT 3
#define JOY_KEY_RIGHT 4
#define JOY_KEY_MAIN_WEAPON 5
#define JOY_KEY_SUB_WEAPON 6
#define JOY_KEY_LOCK 7
#define JOY_KEY_MAP 8
#define JOY_KEY_SPEED_UP 9
#define JOY_KEY_SPEED_DOWN 10
#define JOY_KEY_L 11
#define JOY_KEY_R 12
#define JOY_KEY_VIEW_UP 13
#define JOY_KEY_VIEW_DOWN 14
#define JOY_KEY_VIEW_LEFT 15
#define JOY_KEY_VIEW_RIGHT 16
#define JOY_KEY_VIEW_RESET 17
#define JOY_KEY_SELECT 18
#define JOY_KEY_START 19
#define JOY_KEY_NO_USE 20
#define MAX_JOY_KEYS 128
#define MAX_KeyBoard_KEYS 256
struct tGameSet
{
	int winW;
	int winH;
	int bits;
	int depth;
	bool isFullScreem;
	bool SYNC;
	bool LOW;
	int AA;
	float AF;
	int FPS;
	int Light;
	int Water;
	int Bloom;
	int SSAO;
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
struct tJoyStictSet
{
	int KeySet[MAX_JOY_KEYS];
};
struct tKeyBoardSet
{
	int KeySet[MAX_KeyBoard_KEYS];
};

void loadIniFile();
#endif
