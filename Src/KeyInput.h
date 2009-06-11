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
	int m_keyViewUp;
	int m_keyViewDown;
	int m_keyViewLeft;
	int m_keyViewRight;
	int m_keyViewReset;
	int m_keySetHUD;
	int m_keyStart;
	int m_keySelect;
	int m_keyOther;

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
	int m_keyboardViewUp;
	int m_keyboardViewDown;
	int m_keyboardViewLeft;
	int m_keyboardViewRight;
	int m_keyboardViewReset;
	int m_keyboardSetHUD;
	int m_keyboardStart;
	int m_keyboardSelect;
	int m_keyboardOther;


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
	bool m_IskeyViewUp;
	bool m_IskeyViewDown;
	bool m_IskeyViewLeft;
	bool m_IskeyViewRight;
	bool m_IskeyViewReset;
	bool m_IskeySetHUD;
	bool m_IskeyStart;
	bool m_IskeySelect;
	bool m_IskeyOther;

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
	float m_ViewUp;
	float m_ViewDown;
	float m_ViewLeft;
	float m_ViewRight;
	float m_ViewReset;
	float m_SetHUD;
	float m_Start;
	float m_Select;
	float m_Other;

	bool isAnyKeyDown;

	int UpData(void);
	int de(void);
	void initKeyboard(void);
};
#endif