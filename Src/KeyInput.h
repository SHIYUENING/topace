//#pragma once
#ifndef _KEYINPUT_H
#define _KEYINPUT_H
#include "SDL.h"
class CKeyInput
{
public:
	CKeyInput(void);
	~CKeyInput(void);
	bool initJoyStick(void);
	SDL_Joystick *joystick;
	bool m_IsUseJoyStick;
	int m_keyUp;
	int m_keyDown;
	int m_keyLeft;
	int m_keyRight;
	int m_keyMissle;
	int m_keyGun;
	int m_keyMap;
	int m_keyLock;
	int m_keySpeedUp;
	int m_keySpeedDown;
	int m_keyL;
	int m_keyR;

	//int m_keyboardtmp;
	int m_keyboardUp;
	int m_keyboardDown;
	int m_keyboardLeft;
	int m_keyboardRight;
	int m_keyboardMissle;
	int m_keyboardGun;
	int m_keyboardMap;
	int m_keyboardLock;
	int m_keyboardSpeedUp;
	int m_keyboardSpeedDown;
	int m_keyboardL;
	int m_keyboardR;

	bool m_IskeyUp;
	bool m_IskeyDown;
	bool m_IskeyLeft;
	bool m_IskeyRight;
	bool m_IskeyMissle;
	bool m_IskeyGun;
	bool m_IskeyMap;
	bool m_IskeyLock;
	bool m_IskeySpeedUp;
	bool m_IskeySpeedDown;
	bool m_IskeyL;
	bool m_IskeyR;

	float m_Up;
	float m_Down;
	float m_Left;
	float m_Right;
	float m_Missle;
	float m_Gun;
	float m_Map;
	float m_Lock;
	float m_SpeedUp;
	float m_SpeedDown;
	float m_L;
	float m_R;
	int UpData(void);
	int de(void);
	void initKeyboard(void);
};
#endif