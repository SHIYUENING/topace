#ifndef  __JOYSTICK_H__
#define  __JOYSTICK_H__
#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>
#include "dinput.h"
#include "dinputd.h"
#include <math.h>
#include <strsafe.h>
BOOL CALLBACK    EnumObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext );
BOOL CALLBACK    EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );
HRESULT InitDirectInput( HWND hDlg );
VOID FreeDirectInput();
HRESULT UpdateInputState( HWND hDlg );
HRESULT SetDeviceForcesXY();
HRESULT SetupForIsXInputDevice();
bool IsXInputDevice( const GUID* pGuidProductFromDirectInput );
void CleanupForIsXInputDevice();

#endif
