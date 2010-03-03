#include "StdAfx.h"
#include "Key.h"

class CKeytable
{
	TCHAR* m_keyTable[0xffff];
public:
	inline CKeytable()
	{
		int i;
		for(i = 0; i < 0xffff; i++)
		{
			m_keyTable[i] = _T("KEY_NONE");
		}

		m_keyTable[KEY_LBUTTON] = _T("KEY_LBUTTON");
		m_keyTable[KEY_RBUTTON] = _T("KEY_RBUTTON");
		m_keyTable[KEY_CANCEL] = _T("KEY_CANCEL");
		m_keyTable[KEY_MBUTTON] = _T("KEY_MBUTTON");
		m_keyTable[KEY_XBUTTON1] = _T("KEY_XBUTTON1");
		m_keyTable[KEY_XBUTTON2] = _T("KEY_XBUTTON2");
		m_keyTable[KEY_BACK] = _T("KEY_BACK");
		m_keyTable[KEY_TAB] = _T("KEY_TAB");
		m_keyTable[KEY_CLEAR] = _T("KEY_CLEAR");
		m_keyTable[KEY_RETURN] = _T("KEY_RETURN");
		m_keyTable[KEY_SHIFT] = _T("KEY_SHIFT");
		m_keyTable[KEY_CONTROL] = _T("KEY_CONTROL");
		m_keyTable[KEY_MENU] = _T("KEY_MENU");
		m_keyTable[KEY_PAUSE] = _T("KEY_PAUSE");
		m_keyTable[KEY_CAPITAL] = _T("KEY_CAPITAL");
		m_keyTable[KEY_KANA] = _T("KEY_KANA");
		m_keyTable[KEY_HANGEUL] = _T("KEY_HANGEUL");
		m_keyTable[KEY_HANGUL] = _T("KEY_HANGUL");
		m_keyTable[KEY_JUNJA] = _T("KEY_JUNJA");
		m_keyTable[KEY_FINAL] = _T("KEY_FINAL");
		m_keyTable[KEY_HANJA] = _T("KEY_HANJA");
		m_keyTable[KEY_KANJI] = _T("KEY_KANJI");
		m_keyTable[KEY_ESCAPE] = _T("KEY_ESCAPE");
		m_keyTable[KEY_CONVERT] = _T("KEY_CONVERT");
		m_keyTable[KEY_NONCONVERT] = _T("KEY_NONCONVERT");
		m_keyTable[KEY_ACCEPT] = _T("KEY_ACCEPT");
		m_keyTable[KEY_MODECHANGE] = _T("KEY_MODECHANGE");
		m_keyTable[KEY_SPACE] = _T("KEY_SPACE");
		m_keyTable[KEY_PRIOR] = _T("KEY_PRIOR");
		m_keyTable[KEY_NEXT] = _T("KEY_NEXT");
		m_keyTable[KEY_END] = _T("KEY_END");
		m_keyTable[KEY_HOME] = _T("KEY_HOME");
		m_keyTable[KEY_LEFT] = _T("KEY_LEFT");
		m_keyTable[KEY_UP] = _T("KEY_UP");
		m_keyTable[KEY_RIGHT] = _T("KEY_RIGHT");
		m_keyTable[KEY_DOWN] = _T("KEY_DOWN");
		m_keyTable[KEY_SELECT] = _T("KEY_SELECT");
		m_keyTable[KEY_PRINT] = _T("KEY_PRINT");
		m_keyTable[KEY_EXEC] = _T("KEY_EXEC");
		m_keyTable[KEY_SNAPSHOT] = _T("KEY_SNAPSHOT");
		m_keyTable[KEY_INSERT] = _T("KEY_INSERT");
		m_keyTable[KEY_DELETE] = _T("KEY_DELETE");
		m_keyTable[KEY_HELP] = _T("KEY_HELP");
		m_keyTable[KEY_0] = _T("KEY_0");
		m_keyTable[KEY_1] = _T("KEY_1");
		m_keyTable[KEY_2] = _T("KEY_2");
		m_keyTable[KEY_3] = _T("KEY_3");
		m_keyTable[KEY_4] = _T("KEY_4");
		m_keyTable[KEY_5] = _T("KEY_5");
		m_keyTable[KEY_6] = _T("KEY_6");
		m_keyTable[KEY_7] = _T("KEY_7");
		m_keyTable[KEY_8] = _T("KEY_8");
		m_keyTable[KEY_9] = _T("KEY_9");
		m_keyTable[KEY_A] = _T("KEY_A");
		m_keyTable[KEY_B] = _T("KEY_B");
		m_keyTable[KEY_C] = _T("KEY_C");
		m_keyTable[KEY_D] = _T("KEY_D");
		m_keyTable[KEY_E] = _T("KEY_E");
		m_keyTable[KEY_F] = _T("KEY_F");
		m_keyTable[KEY_G] = _T("KEY_G");
		m_keyTable[KEY_H] = _T("KEY_H");
		m_keyTable[KEY_I] = _T("KEY_I");
		m_keyTable[KEY_J] = _T("KEY_J");
		m_keyTable[KEY_K] = _T("KEY_K");
		m_keyTable[KEY_L] = _T("KEY_L");
		m_keyTable[KEY_M] = _T("KEY_M");
		m_keyTable[KEY_N] = _T("KEY_N");
		m_keyTable[KEY_O] = _T("KEY_O");
		m_keyTable[KEY_P] = _T("KEY_P");
		m_keyTable[KEY_Q] = _T("KEY_Q");
		m_keyTable[KEY_R] = _T("KEY_R");
		m_keyTable[KEY_S] = _T("KEY_S");
		m_keyTable[KEY_T] = _T("KEY_T");
		m_keyTable[KEY_U] = _T("KEY_U");
		m_keyTable[KEY_V] = _T("KEY_V");
		m_keyTable[KEY_W] = _T("KEY_W");
		m_keyTable[KEY_X] = _T("KEY_X");
		m_keyTable[KEY_Y] = _T("KEY_Y");
		m_keyTable[KEY_Z] = _T("KEY_Z");
		m_keyTable[KEY_LWIN] = _T("KEY_LWIN");
		m_keyTable[KEY_RWIN] = _T("KEY_RWIN");
		m_keyTable[KEY_APPS] = _T("KEY_APPS");
		m_keyTable[KEY_SLEEP] = _T("KEY_SLEEP");
		m_keyTable[KEY_NUMPAD0] = _T("KEY_NUMPAD0");
		m_keyTable[KEY_NUMPAD1] = _T("KEY_NUMPAD1");
		m_keyTable[KEY_NUMPAD2] = _T("KEY_NUMPAD2");
		m_keyTable[KEY_NUMPAD3] = _T("KEY_NUMPAD3");
		m_keyTable[KEY_NUMPAD4] = _T("KEY_NUMPAD4");
		m_keyTable[KEY_NUMPAD5] = _T("KEY_NUMPAD5");
		m_keyTable[KEY_NUMPAD6] = _T("KEY_NUMPAD6");
		m_keyTable[KEY_NUMPAD7] = _T("KEY_NUMPAD7");
		m_keyTable[KEY_NUMPAD8] = _T("KEY_NUMPAD8");
		m_keyTable[KEY_NUMPAD9] = _T("KEY_NUMPAD9");
		m_keyTable[KEY_MULTIPLY] = _T("KEY_MULTIPLY");
		m_keyTable[KEY_ADD] = _T("KEY_ADD");
		m_keyTable[KEY_SEPARATOR] = _T("KEY_SEPARATOR");
		m_keyTable[KEY_SUBTRACT] = _T("KEY_SUBTRACT");
		m_keyTable[KEY_DECIMAL] = _T("KEY_DECIMAL");
		m_keyTable[KEY_DIVIDE] = _T("KEY_DIVIDE");
		m_keyTable[KEY_F1] = _T("KEY_F1");
		m_keyTable[KEY_F2] = _T("KEY_F2");
		m_keyTable[KEY_F3] = _T("KEY_F3");
		m_keyTable[KEY_F4] = _T("KEY_F4");
		m_keyTable[KEY_F5] = _T("KEY_F5");
		m_keyTable[KEY_F6] = _T("KEY_F6");
		m_keyTable[KEY_F7] = _T("KEY_F7");
		m_keyTable[KEY_F8] = _T("KEY_F8");
		m_keyTable[KEY_F9] = _T("KEY_F9");
		m_keyTable[KEY_F10] = _T("KEY_F10");
		m_keyTable[KEY_F11] = _T("KEY_F11");
		m_keyTable[KEY_F12] = _T("KEY_F12");
		m_keyTable[KEY_F13] = _T("KEY_F13");
		m_keyTable[KEY_F14] = _T("KEY_F14");
		m_keyTable[KEY_F15] = _T("KEY_F15");
		m_keyTable[KEY_F16] = _T("KEY_F16");
		m_keyTable[KEY_F17] = _T("KEY_F17");
		m_keyTable[KEY_F18] = _T("KEY_F18");
		m_keyTable[KEY_F19] = _T("KEY_F19");
		m_keyTable[KEY_F20] = _T("KEY_F20");
		m_keyTable[KEY_F21] = _T("KEY_F21");
		m_keyTable[KEY_F22] = _T("KEY_F22");
		m_keyTable[KEY_F23] = _T("KEY_F23");
		m_keyTable[KEY_F24] = _T("KEY_F24");
		m_keyTable[KEY_NUMLOCK] = _T("KEY_NUMLOCK");
		m_keyTable[KEY_SCROLL] = _T("KEY_SCROLL");
		m_keyTable[KEY_LSHIFT] = _T("KEY_LSHIFT");
		m_keyTable[KEY_RSHIFT] = _T("KEY_RSHIFT");
		m_keyTable[KEY_LCONTROL] = _T("KEY_LCONTROL");
		m_keyTable[KEY_RCONTROL] = _T("KEY_RCONTROL");
		m_keyTable[KEY_LMENU] = _T("KEY_LMENU");
		m_keyTable[KEY_RMENU] = _T("KEY_RMENU");
		m_keyTable[KEY_BROWSER_BACK] = _T("KEY_BROWSER_BACK");
		m_keyTable[KEY_BROWSER_FORWARD] = _T("KEY_BROWSER_FORWARD");
		m_keyTable[KEY_BROWSER_REFRESH] = _T("KEY_BROWSER_REFRESH");
		m_keyTable[KEY_BROWSER_STOP] = _T("KEY_BROWSER_STOP");
		m_keyTable[KEY_BROWSER_SEARCH] = _T("KEY_BROWSER_SEARCH");
		m_keyTable[KEY_BROWSER_FAVORITES] = _T("KEY_BROWSER_FAVORITES");
		m_keyTable[KEY_BROWSER_HOME] = _T("KEY_BROWSER_HOME");
		m_keyTable[KEY_VOLUME_MUTE] = _T("KEY_VOLUME_MUTE");
		m_keyTable[KEY_VOLUME_DOWN] = _T("KEY_VOLUME_DOWN");
		m_keyTable[KEY_VOLUME_UP] = _T("KEY_VOLUME_UP");
		m_keyTable[KEY_MEDIA_NEXT_TRACK] = _T("KEY_MEDIA_NEXT_TRACK");
		m_keyTable[KEY_MEDIA_PREV_TRACK] = _T("KEY_MEDIA_PREV_TRACK");
		m_keyTable[KEY_MEDIA_STOP] = _T("KEY_MEDIA_STOP");
		m_keyTable[KEY_MEDIA_PLAY_PAUSE] = _T("KEY_MEDIA_PLAY_PAUSE");
		m_keyTable[KEY_LAUNCH_MAIL] = _T("KEY_LAUNCH_MAIL");
		m_keyTable[KEY_LAUNCH_MEDIA_SELECT] = _T("KEY_LAUNCH_MEDIA_SELECT");
		m_keyTable[KEY_LAUNCH_APP1] = _T("KEY_LAUNCH_APP1");
		m_keyTable[KEY_LAUNCH_APP2] = _T("KEY_LAUNCH_APP2");
		m_keyTable[KEY_OEM_1] = _T("KEY_OEM_1");
		m_keyTable[KEY_OEM_PLUS] = _T("KEY_OEM_PLUS");
		m_keyTable[KEY_OEM_COMMA] = _T("KEY_OEM_COMMA");
		m_keyTable[KEY_OEM_MINUS] = _T("KEY_OEM_MINUS");
		m_keyTable[KEY_OEM_PERIOD] = _T("KEY_OEM_PERIOD");
		m_keyTable[KEY_OEM_2] = _T("KEY_OEM_2");
		m_keyTable[KEY_OEM_3] = _T("KEY_OEM_3");
		m_keyTable[KEY_OEM_4] = _T("KEY_OEM_4");
		m_keyTable[KEY_OEM_5] = _T("KEY_OEM_5");
		m_keyTable[KEY_OEM_6] = _T("KEY_OEM_6");
		m_keyTable[KEY_OEM_7] = _T("KEY_OEM_7");
		m_keyTable[KEY_OEM_8] = _T("KEY_OEM_8");
		m_keyTable[KEY_OEM_102] = _T("KEY_OEM_102");
		m_keyTable[KEY_PROCESSKEY] = _T("KEY_PROCESSKEY");
		m_keyTable[KEY_PACKET] = _T("KEY_PACKET");
		m_keyTable[KEY_ATTN] = _T("KEY_ATTN");
		m_keyTable[KEY_CRSEL] = _T("KEY_CRSEL");
		m_keyTable[KEY_EXSEL] = _T("KEY_EXSEL");
		m_keyTable[KEY_EREOF] = _T("KEY_EREOF");
		m_keyTable[KEY_PLAY] = _T("KEY_PLAY");
		m_keyTable[KEY_ZOOM] = _T("KEY_ZOOM");
		m_keyTable[KEY_NONAME] = _T("KEY_NONAME");
		m_keyTable[KEY_PA1] = _T("KEY_PA1");
		m_keyTable[KEY_OEM_CLEAR] = _T("KEY_OEM_CLEAR");
		m_keyTable[KEY_NONE] = _T("KEY_NONE");
	}

	inline const TCHAR *getKeyString(unsigned int key)const
	{
		if(key > 0xffff || m_keyTable[key][0] == 0) //keep in this order or will cause bugs
			return _T("KEY_NONE");

		return m_keyTable[key];
	}
};

static const CKeytable g_Keytable;


// unsigned int getKeyNumber(char *key)
// {
// 	int i;
// 	for(i = 0; i <= 0xffff; i++)
// 	{
// 		if(i == 0xffff || !stricmp(key, keyTable[i])) //keep in this order or will cause bugs
// 		{
// 			return i;
// 		}
// 	}
// 
// 	return i;
// }

const TCHAR *getKeyString(unsigned int key)
{
	return g_Keytable.getKeyString(key);
}
