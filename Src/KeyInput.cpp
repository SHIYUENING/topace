#include "KeyInput.h"
#include <windows.h>
CKeyInput::CKeyInput(void)
: m_IsUseJoyStick(false)
, m_IskeyUp(false)
, m_IskeyDown(false)
, m_IskeyLeft(false)
, m_IskeyRight(false)
, m_IskeyMissle(false)
, m_IskeyGun(false)
, m_IskeyMap(false)
, m_IskeyLock(false)
, m_IskeySpeedUp(false)
, m_IskeySpeedDown(false)
, m_IskeyL(false)
, m_IskeyR(false)
, m_IskeyViewUp(false)
, m_IskeyViewDown(false)
, m_IskeyViewLeft(false)
, m_IskeyViewRight(false)
, m_IskeyViewReset(false)
, m_IskeySetHUD(false)
, isAnyKeyDown(false)
, m_keyUp(0)
{
}

CKeyInput::~CKeyInput(void)
{
	
}

bool CKeyInput::initJoyStick(void)
{
	initKeyboard();
	if ( SDL_Init( SDL_INIT_JOYSTICK )>-1 )
    {
		if(SDL_NumJoysticks()>0)
		{
			joystick = SDL_JoystickOpen(GetPrivateProfileInt( "JoyStick" , "JoyNum"	 , 0 , ".\\set.ini" ));
			m_keyUp			= GetPrivateProfileInt( "JoyStick" , "UP"	 , 103 , ".\\set.ini" );
			m_keyDown		= GetPrivateProfileInt( "JoyStick" , "Down"	 , 102 , ".\\set.ini" );
			m_keyLeft		= GetPrivateProfileInt( "JoyStick" , "Left"	 , 101 , ".\\set.ini" );
			m_keyRight		= GetPrivateProfileInt( "JoyStick" , "Right" , 100 , ".\\set.ini" );
			m_keyMissle		= GetPrivateProfileInt( "JoyStick" , "Missle", 1 , ".\\set.ini" );
			m_keyGun		= GetPrivateProfileInt( "JoyStick" , "Gun"	 , 2 , ".\\set.ini" );
			m_keyMap		= GetPrivateProfileInt( "JoyStick" , "Map"	 , 3 , ".\\set.ini" );
			m_keyLock		= GetPrivateProfileInt( "JoyStick" , "Lock"	 , 0 , ".\\set.ini" );
			m_keySpeedUp	= GetPrivateProfileInt( "JoyStick" , "SpeedUp"	 , 7 , ".\\set.ini" );
			m_keySpeedDown	= GetPrivateProfileInt( "JoyStick" , "SpeedDown"	 , 6 , ".\\set.ini" );
			m_keyL			= GetPrivateProfileInt( "JoyStick" , "L"	 , 4 , ".\\set.ini" );
			m_keyR			= GetPrivateProfileInt( "JoyStick" , "R"	 , 5 , ".\\set.ini" );
			m_keyViewUp			= GetPrivateProfileInt( "JoyStick" , "ViewUP"	 , 107 , ".\\set.ini" );
			m_keyViewDown		= GetPrivateProfileInt( "JoyStick" , "ViewDown"	 , 106 , ".\\set.ini" );
			m_keyViewLeft		= GetPrivateProfileInt( "JoyStick" , "ViewLeft"	 , 105 , ".\\set.ini" );
			m_keyViewRight		= GetPrivateProfileInt( "JoyStick" , "ViewRight" , 104 , ".\\set.ini" );
			m_keyViewReset		= GetPrivateProfileInt( "JoyStick" , "ViewReset" , 0 , ".\\set.ini" );
			m_keySetHUD		= GetPrivateProfileInt( "JoyStick" , "SetHUD" , 9 , ".\\set.ini" );
			m_IsUseJoyStick	= true;
		}
		return true;
    }
	MessageBox (HWND_DESKTOP, SDL_GetError(), "Error", MB_OK | MB_ICONEXCLAMATION);
	return false;
}

int CKeyInput::UpData(void)
{

	if(m_IsUseJoyStick)
	{
		 m_IskeyUp=false;
		 m_IskeyDown=false;
		 m_IskeyLeft=false;
		 m_IskeyRight=false;
		 m_IskeyMissle=false;
		 m_IskeyGun=false;
		 m_IskeyMap=false;
		 m_IskeyLock=false;
		 m_IskeySpeedUp=false;
		 m_IskeySpeedDown=false;
		 m_IskeyL=false;
		 m_IskeyR=false;
		 m_IskeyViewUp=false;
		 m_IskeyViewDown=false;
		 m_IskeyViewLeft=false;
		 m_IskeyViewRight=false;
		 m_IskeyViewReset=false;
		 m_IskeySetHUD=false;
		SDL_JoystickUpdate();
		if(m_keyUp>999)
		{
			m_Up=SDL_JoystickGetHat(joystick,m_keyUp-1000);
		}
		else
		{
			if(m_keyUp>99)
			{
				if((m_keyUp-100)%2==0)
					m_Up=(float)SDL_JoystickGetAxis(joystick,(m_keyUp-100)/2)/32500.0f;
				else
					m_Up=-(float)SDL_JoystickGetAxis(joystick,(m_keyUp-100-1)/2)/32500.0f;
			}
			else
			{
				m_Up=SDL_JoystickGetButton(joystick,m_keyUp);
			}
		}
		if(m_Up>0.1f)
			m_IskeyUp=true;

		if(m_keyDown>999)
		{
			m_Down=SDL_JoystickGetHat(joystick,m_keyDown-1000);
		}
		else
		{
			if(m_keyDown>99)
			{
				if((m_keyDown-100)%2==0)
					m_Down=(float)SDL_JoystickGetAxis(joystick,(m_keyDown-100)/2)/32500.0f;
				else
					m_Down=-(float)SDL_JoystickGetAxis(joystick,(m_keyDown-100-1)/2)/32500.0f;
			}
			else
			{
				m_Down=SDL_JoystickGetButton(joystick,m_keyDown);
			}
		}
		if(m_Down>0.1f)
			m_IskeyDown=true;

		
		if(m_keyLeft>999)
		{
			m_Left=SDL_JoystickGetHat(joystick,m_keyLeft-1000);
		}
		else
		{
			if(m_keyLeft>99)
			{
				if((m_keyLeft-100)%2==0)
					m_Left=(float)SDL_JoystickGetAxis(joystick,(m_keyLeft-100)/2)/32500.0f;
				else
					m_Left=-(float)SDL_JoystickGetAxis(joystick,(m_keyLeft-100-1)/2)/32500.0f;
			}
			else
			{
				m_Left=SDL_JoystickGetButton(joystick,m_keyLeft);
			}
		}
		if(m_Left>0.1f)
			m_IskeyLeft=true;

		
		if(m_keyRight>999)
		{
			m_Right=SDL_JoystickGetHat(joystick,m_keyRight-1000);
		}
		else
		{
			if(m_keyRight>99)
			{
				if((m_keyRight-100)%2==0)
					m_Right=(float)SDL_JoystickGetAxis(joystick,(m_keyRight-100)/2)/32500.0f;
				else
					m_Right=-(float)SDL_JoystickGetAxis(joystick,(m_keyRight-100-1)/2)/32500.0f;
			}
			else
			{
				m_Right=SDL_JoystickGetButton(joystick,m_keyRight);
			}
		}
		if(m_Right>0.1f)
			m_IskeyRight=true;
		
		if(m_keyMissle>999)
		{
			m_Missle=SDL_JoystickGetHat(joystick,m_keyMissle-1000);
		}
		else
		{
			if(m_keyMissle>99)
			{
				if((m_keyMissle-100)%2==0)
					m_Missle=(float)SDL_JoystickGetAxis(joystick,(m_keyMissle-100)/2)/32500.0f;
				else
					m_Missle=-(float)SDL_JoystickGetAxis(joystick,(m_keyMissle-100-1)/2)/32500.0f;
			}
			else
			{
				m_Missle=SDL_JoystickGetButton(joystick,m_keyMissle);
			}
		}
		if(m_Missle>0.1f)
			m_IskeyMissle=true;

		if(m_keyGun>999)
		{
			m_Gun=SDL_JoystickGetHat(joystick,m_keyGun-1000);
		}
		else
		{
			if(m_keyGun>99)
			{
				if((m_keyGun-100)%2==0)
					m_Gun=(float)SDL_JoystickGetAxis(joystick,(m_keyGun-100)/2)/32500.0f;
				else
					m_Gun=-(float)SDL_JoystickGetAxis(joystick,(m_keyGun-100-1)/2)/32500.0f;
			}
			else
			{
				m_Gun=SDL_JoystickGetButton(joystick,m_keyGun);
			}
		}
		if(m_Gun>0.1f)
			m_IskeyGun=true;
		
		if(m_keyMap>999)
		{
			m_Map=SDL_JoystickGetHat(joystick,m_keyMap-1000);
		}
		else
		{
			if(m_keyMap>99)
			{
				if((m_keyMap-100)%2==0)
					m_Map=(float)SDL_JoystickGetAxis(joystick,(m_keyMap-100)/2)/32500.0f;
				else
					m_Map=-(float)SDL_JoystickGetAxis(joystick,(m_keyMap-100-1)/2)/32500.0f;
			}
			else
			{
				m_Map=SDL_JoystickGetButton(joystick,m_keyMap);
			}
		}
		if(m_Map>0.1f)
			m_IskeyMap=true;
		
		if(m_keyLock>999)
		{
			m_Lock=SDL_JoystickGetHat(joystick,m_keyLock-1000);
		}
		else
		{
			if(m_keyLock>99)
			{
				if((m_keyLock-100)%2==0)
					m_Lock=(float)SDL_JoystickGetAxis(joystick,(m_keyLock-100)/2)/32500.0f;
				else
					m_Lock=-(float)SDL_JoystickGetAxis(joystick,(m_keyLock-100-1)/2)/32500.0f;
			}
			else
			{
				m_Lock=SDL_JoystickGetButton(joystick,m_keyLock);
			}
		}
		if(m_Lock>0.1f)
			m_IskeyLock=true;
		
		if(m_keySpeedUp>999)
		{
			m_SpeedUp=SDL_JoystickGetHat(joystick,m_keySpeedUp-1000);
		}
		else
		{
			if(m_keySpeedUp>99)
			{
				if((m_keySpeedUp-100)%2==0)
					m_SpeedUp=(float)SDL_JoystickGetAxis(joystick,(m_keySpeedUp-100)/2)/32500.0f;
				else
					m_SpeedUp=-(float)SDL_JoystickGetAxis(joystick,(m_keySpeedUp-100-1)/2)/32500.0f;
			}
			else
			{
				m_SpeedUp=SDL_JoystickGetButton(joystick,m_keySpeedUp);
			}
		}
		if(m_SpeedUp>0.1f)
			m_IskeySpeedUp=true;
		
		if(m_keySpeedDown>999)
		{
			m_SpeedDown=SDL_JoystickGetHat(joystick,m_keySpeedDown-1000);
		}
		else
		{
			if(m_keySpeedDown>99)
			{
				if((m_keySpeedDown-100)%2==0)
					m_SpeedDown=(float)SDL_JoystickGetAxis(joystick,(m_keySpeedDown-100)/2)/32500.0f;
				else
					m_SpeedDown=-(float)SDL_JoystickGetAxis(joystick,(m_keySpeedDown-100-1)/2)/32500.0f;
			}
			else
			{
				m_SpeedDown=SDL_JoystickGetButton(joystick,m_keySpeedDown);
			}
		}
		if(m_SpeedDown>0.1f)
			m_IskeySpeedDown=true;

		
		if(m_keyL>999)
		{
			m_L=SDL_JoystickGetHat(joystick,m_keyL-1000);
		}
		else
		{
			if(m_keyL>99)
			{
				if((m_keyL-100)%2==0)
					m_L=(float)SDL_JoystickGetAxis(joystick,(m_keyL-100)/2)/32500.0f;
				else
					m_L=-(float)SDL_JoystickGetAxis(joystick,(m_keyL-100-1)/2)/32500.0f;
			}
			else
			{
				m_L=SDL_JoystickGetButton(joystick,m_keyL);
			}
		}
		if(m_L>0.1f)
			m_IskeyL=true;
		
		if(m_keyR>999)
		{
			m_R=SDL_JoystickGetHat(joystick,m_keyR-1000);
		}
		else
		{
			if(m_keyR>99)
			{
				if((m_keyR-100)%2==0)
					m_R=(float)SDL_JoystickGetAxis(joystick,(m_keyR-100)/2)/32500.0f;
				else
					m_R=-(float)SDL_JoystickGetAxis(joystick,(m_keyR-100-1)/2)/32500.0f;
			}
			else
			{
				m_R=SDL_JoystickGetButton(joystick,m_keyR);
			}
		}
		if(m_R>0.1f)
			m_IskeyR=true;


		if(m_keyViewUp>999)
		{
			m_ViewUp=SDL_JoystickGetHat(joystick,m_keyViewUp-1000);
		}
		else
		{
			if(m_keyViewUp>99)
			{
				if((m_keyViewUp-100)%2==0)
					m_ViewUp=(float)SDL_JoystickGetAxis(joystick,(m_keyViewUp-100)/2)/32500.0f;
				else
					m_ViewUp=-(float)SDL_JoystickGetAxis(joystick,(m_keyViewUp-100-1)/2)/32500.0f;
			}
			else
			{
				m_ViewUp=SDL_JoystickGetButton(joystick,m_keyViewUp);
			}
		}
		if(m_ViewUp>0.1f)
			m_IskeyViewUp=true;

		if(m_keyViewDown>999)
		{
			m_ViewDown=SDL_JoystickGetHat(joystick,m_keyViewDown-1000);
		}
		else
		{
			if(m_keyViewDown>99)
			{
				if((m_keyViewDown-100)%2==0)
					m_ViewDown=(float)SDL_JoystickGetAxis(joystick,(m_keyViewDown-100)/2)/32500.0f;
				else
					m_ViewDown=-(float)SDL_JoystickGetAxis(joystick,(m_keyViewDown-100-1)/2)/32500.0f;
			}
			else
			{
				m_ViewDown=SDL_JoystickGetButton(joystick,m_keyViewDown);
			}
		}
		if(m_ViewDown>0.1f)
			m_IskeyViewDown=true;

		
		if(m_keyViewLeft>999)
		{
			m_ViewLeft=SDL_JoystickGetHat(joystick,m_keyViewLeft-1000);
		}
		else
		{
			if(m_keyViewLeft>99)
			{
				if((m_keyViewLeft-100)%2==0)
					m_ViewLeft=(float)SDL_JoystickGetAxis(joystick,(m_keyViewLeft-100)/2)/32500.0f;
				else
					m_ViewLeft=-(float)SDL_JoystickGetAxis(joystick,(m_keyViewLeft-100-1)/2)/32500.0f;
			}
			else
			{
				m_ViewLeft=SDL_JoystickGetButton(joystick,m_keyViewLeft);
			}
		}
		if(m_ViewLeft>0.1f)
			m_IskeyViewLeft=true;

		
		if(m_keyViewRight>999)
		{
			m_ViewRight=SDL_JoystickGetHat(joystick,m_keyViewRight-1000);
		}
		else
		{
			if(m_keyViewRight>99)
			{
				if((m_keyViewRight-100)%2==0)
					m_ViewRight=(float)SDL_JoystickGetAxis(joystick,(m_keyViewRight-100)/2)/32500.0f;
				else
					m_ViewRight=-(float)SDL_JoystickGetAxis(joystick,(m_keyViewRight-100-1)/2)/32500.0f;
			}
			else
			{
				m_ViewRight=SDL_JoystickGetButton(joystick,m_keyViewRight);
			}
		}
		if(m_ViewRight>0.1f)
			m_IskeyViewRight=true;
		
		if(m_keyViewReset>999)
		{
			m_ViewReset=SDL_JoystickGetHat(joystick,m_keyViewReset-1000);
		}
		else
		{
			if(m_keyViewReset>99)
			{
				if((m_keyViewReset-100)%2==0)
					m_ViewReset=(float)SDL_JoystickGetAxis(joystick,(m_keyViewReset-100)/2)/32500.0f;
				else
					m_ViewReset=-(float)SDL_JoystickGetAxis(joystick,(m_keyViewReset-100-1)/2)/32500.0f;
			}
			else
			{
				m_ViewReset=SDL_JoystickGetButton(joystick,m_keyViewReset);
			}
		}
		if(m_ViewReset>0.1f)
			m_IskeyViewReset=true;


		if(m_keySetHUD>999)
		{
			m_SetHUD=SDL_JoystickGetHat(joystick,m_keySetHUD-1000);
		}
		else
		{
			if(m_keySetHUD>99)
			{
				if((m_keySetHUD-100)%2==0)
					m_SetHUD=(float)SDL_JoystickGetAxis(joystick,(m_keySetHUD-100)/2)/32500.0f;
				else
					m_SetHUD=-(float)SDL_JoystickGetAxis(joystick,(m_keySetHUD-100-1)/2)/32500.0f;
			}
			else
			{
				m_SetHUD=SDL_JoystickGetButton(joystick,m_keySetHUD);
			}
		}
		if(m_SetHUD>0.1f)
			m_IskeySetHUD=true;
		if(m_IskeyUp||m_IskeyDown||m_IskeyLeft||m_IskeyRight||m_IskeyMissle||m_IskeyGun||m_IskeyMap||m_IskeyLock||m_IskeySpeedUp||m_IskeyViewDown||m_IskeyViewLeft||m_IskeyViewRight||m_IskeyViewReset||m_IskeySetHUD)
		
			isAnyKeyDown=true;
		else
			isAnyKeyDown=false;

	}

	return 0;
}

int CKeyInput::de(void)
{
	SDL_JoystickClose(joystick);
	SDL_Quit();
	return 0;
}

void CKeyInput::initKeyboard(void)
{
			m_keyboardUp		= GetPrivateProfileInt( "keyboard" , "UP"	 , 10087 , ".\\set.ini" )-10000;
			m_keyboardDown		= GetPrivateProfileInt( "keyboard" , "Down"	 , 10083 , ".\\set.ini" )-10000;
			m_keyboardLeft		= GetPrivateProfileInt( "keyboard" , "Left"	 , 10065 , ".\\set.ini" )-10000;
			m_keyboardRight		= GetPrivateProfileInt( "keyboard" , "Right" , 10068 , ".\\set.ini" )-10000;
			m_keyboardMissle	= GetPrivateProfileInt( "keyboard" , "Missle", 10070 , ".\\set.ini" )-10000;
			m_keyboardGun		= GetPrivateProfileInt( "keyboard" , "Gun"	 , 10071 , ".\\set.ini" )-10000;
			m_keyboardMap		= GetPrivateProfileInt( "keyboard" , "Map"	 , 10084 , ".\\set.ini" )-10000;
			m_keyboardLock		= GetPrivateProfileInt( "keyboard" , "Lock"	 , 10081 , ".\\set.ini" )-10000;
			m_keyboardSpeedUp	= GetPrivateProfileInt( "keyboard" , "SpeedUp"	 , 10038 , ".\\set.ini" )-10000;
			m_keyboardSpeedDown	= GetPrivateProfileInt( "keyboard" , "SpeedDown"	 , 10040 , ".\\set.ini" )-10000;
			m_keyboardL			= GetPrivateProfileInt( "keyboard" , "L"	 , 10037 , ".\\set.ini" )-10000;
			m_keyboardR			= GetPrivateProfileInt( "keyboard" , "R"	 , 10039 , ".\\set.ini" )-10000;
			m_keyboardViewUp		= GetPrivateProfileInt( "keyboard" , "ViewUP"	 , 10104 , ".\\set.ini" )-10000;
			m_keyboardViewDown		= GetPrivateProfileInt( "keyboard" , "ViewDown"	 , 10100 , ".\\set.ini" )-10000;
			m_keyboardViewLeft		= GetPrivateProfileInt( "keyboard" , "ViewLeft"	 , 10102 , ".\\set.ini" )-10000;
			m_keyboardViewRight		= GetPrivateProfileInt( "keyboard" , "ViewRight" , 10098 , ".\\set.ini" )-10000;
			m_keyboardViewReset		= GetPrivateProfileInt( "keyboard" , "ViewReset" , 10103 , ".\\set.ini" )-10000;
			m_keyboardSetHUD		= GetPrivateProfileInt( "keyboard" , "SetHUD"	 , 10090 , ".\\set.ini" )-10000;
}
