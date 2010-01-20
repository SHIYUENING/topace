#ifndef KEYINPUT_H
#define KEYINPUT_H
#include"IniFile.h"
struct tKeyInput
{
	float KeyVal[MAX_JOY_KEYS];
	int KeyStats[MAX_JOY_KEYS];
};
void UpdataKeyInput(int* KeyBoardkeys);
#endif