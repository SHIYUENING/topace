// KeyBoardSet.cpp : implementation file
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"
#include "KeyBoardSet.h"
#include"IniFile.h"

// CKeyBoardSet dialog

IMPLEMENT_DYNAMIC(CKeyBoardSet, CDialog)
extern tGameSet GameSet;
extern tSoundSet SoundSet;
extern tJoyStictSet JoyStictSet;
extern tKeyBoardSet KeyBoardSet;
CKeyBoardSet::CKeyBoardSet(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyBoardSet::IDD, pParent)
{
	for(int i=1;i<256;i++)
	{
		cKeycharList[i]=KeySetIntToChar(i);
	}
}

CKeyBoardSet::~CKeyBoardSet()
{
}

void CKeyBoardSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD1, m_EDIT[JOY_KEY_UP]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD2, m_EDIT[JOY_KEY_DOWN]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD3, m_EDIT[JOY_KEY_LEFT]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD4, m_EDIT[JOY_KEY_RIGHT]);

	DDX_Control(pDX, IDC_EDIT_KEYBOARD5, m_EDIT[JOY_KEY_VIEW_UP]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD6, m_EDIT[JOY_KEY_VIEW_DOWN]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD7, m_EDIT[JOY_KEY_VIEW_LEFT]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD8, m_EDIT[JOY_KEY_VIEW_RIGHT]);

	DDX_Control(pDX, IDC_EDIT_KEYBOARD9, m_EDIT[JOY_KEY_SPEED_UP]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD10, m_EDIT[JOY_KEY_SPEED_DOWN]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD11, m_EDIT[JOY_KEY_L]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD12, m_EDIT[JOY_KEY_R]);

	DDX_Control(pDX, IDC_EDIT_KEYBOARD13, m_EDIT[JOY_KEY_MAIN_WEAPON]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD14, m_EDIT[JOY_KEY_SUB_WEAPON]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD15, m_EDIT[JOY_KEY_MAP]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD16, m_EDIT[JOY_KEY_LOCK]);

	DDX_Control(pDX, IDC_EDIT_KEYBOARD17, m_EDIT[JOY_KEY_SELECT]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD18, m_EDIT[JOY_KEY_START]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD19, m_EDIT[JOY_KEY_VIEW_RESET]);
}


BEGIN_MESSAGE_MAP(CKeyBoardSet, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_KEYBOARD1, &CKeyBoardSet::OnEnKillfocusEditKeyboard1)
END_MESSAGE_MAP()

void CKeyBoardSet::OnEnKillfocusEditKeyboard1()
{
	WCHAR GetWindowText[16];
	m_EDIT[JOY_KEY_UP].GetWindowTextW(GetWindowText,10);
	KeyBoardSet.KeySet[JOY_KEY_UP]=_wtoi(GetWindowText);
	// TODO: Add your control notification handler code here
}

void CKeyBoardSet::InitUI(void)
{
	for(int i=1;i<20;i++)
	{
		m_EDIT[i].SetWindowTextW(KeySetIntToChar(KeyBoardSet.KeySet[i]));
	}
	//_itow_s(KeyBoardSet.KeySet[JOY_KEY_UP],SetChar,sizeof(SetChar),10);
/*	CString CSetWindowText;
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_UP]);
	m_EDIT[JOY_KEY_UP].SetWindowTextW(KeySetIntToChar(KeyBoardSet.KeySet[JOY_KEY_UP]));
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_DOWN]);
	m_EDIT[JOY_KEY_DOWN].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_LEFT]);
	m_EDIT[JOY_KEY_LEFT].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_RIGHT]);
	m_EDIT[JOY_KEY_RIGHT].SetWindowTextW(CSetWindowText);

	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_MAIN_WEAPON]);
	m_EDIT[JOY_KEY_MAIN_WEAPON].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_SUB_WEAPON]);
	m_EDIT[JOY_KEY_SUB_WEAPON].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_LOCK]);
	m_EDIT[JOY_KEY_LOCK].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_MAP]);
	m_EDIT[JOY_KEY_MAP].SetWindowTextW(CSetWindowText);

	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_SPEED_UP]);
	m_EDIT[JOY_KEY_SPEED_UP].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_SPEED_DOWN]);
	m_EDIT[JOY_KEY_SPEED_DOWN].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_L]);
	m_EDIT[JOY_KEY_L].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_R]);
	m_EDIT[JOY_KEY_R].SetWindowTextW(CSetWindowText);

	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_VIEW_UP]);
	m_EDIT[JOY_KEY_VIEW_UP].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_VIEW_DOWN]);
	m_EDIT[JOY_KEY_VIEW_DOWN].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_VIEW_LEFT]);
	m_EDIT[JOY_KEY_VIEW_LEFT].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_VIEW_RIGHT]);
	m_EDIT[JOY_KEY_VIEW_RIGHT].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_VIEW_RESET]);
	m_EDIT[JOY_KEY_VIEW_RESET].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_SELECT]);
	m_EDIT[JOY_KEY_SELECT].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_START]);
	m_EDIT[JOY_KEY_START].SetWindowTextW(CSetWindowText);
*/
}

CString CKeyBoardSet::KeySetIntToChar(int KeyInt)
{
	wchar_t IntToChar[2];
	IntToChar[1]=0;
	if(KeyInt==VK_BACK)
		return CString(_T("VK_BACK"));

	if(KeyInt==VK_TAB)
		return CString(_T("VK_TAB"));

	if(KeyInt==VK_CLEAR)
		return CString(_T("VK_CLEAR"));

	if(KeyInt==VK_RETURN)
		return CString(_T("VK_RETURN"));

	if(KeyInt==VK_SHIFT)
		return CString(_T("VK_SHIFT"));

	if(KeyInt==VK_CONTROL)
		return CString(_T("VK_CONTROL"));

	if(KeyInt==VK_MENU)
		return CString(_T("VK_MENU"));

	if(KeyInt==VK_PAUSE)
		return CString(_T("VK_PAUSE"));

	if(KeyInt==VK_CAPITAL)
		return CString(_T("VK_CAPITAL"));

	if(KeyInt==VK_KANA)
		return CString(_T("VK_KANA"));

	if(KeyInt==VK_HANGUL)
		return CString(_T("VK_HANGUL"));

	if(KeyInt==VK_JUNJA)
		return CString(_T("VK_JUNJA"));

	if(KeyInt==VK_FINAL)
		return CString(_T("VK_FINAL"));

	if(KeyInt==VK_HANJA)
		return CString(_T("VK_HANJA"));

	if(KeyInt==VK_KANJI)
		return CString(_T("VK_KANJI"));

	if(KeyInt==VK_ESCAPE)
		return CString(_T("VK_ESCAPE"));

	if(KeyInt==VK_CONVERT)
		return CString(_T("VK_CONVERT"));

	if(KeyInt==VK_NONCONVERT)
		return CString(_T("VK_NONCONVERT"));

	if(KeyInt==VK_ACCEPT)
		return CString(_T("VK_ACCEPT"));

	if(KeyInt==VK_MODECHANGE)
		return CString(_T("VK_MODECHANGE"));

	if(KeyInt==VK_SPACE)
		return CString(_T("VK_SPACE"));

	if(KeyInt==VK_PRIOR)
		return CString(_T("VK_PRIOR"));

	if(KeyInt==VK_NEXT)
		return CString(_T("VK_NEXT"));

	if(KeyInt==VK_END)
		return CString(_T("VK_END"));

	if(KeyInt==VK_HOME)
		return CString(_T("VK_HOME"));

	if(KeyInt==VK_LEFT)
		return CString(_T("VK_LEFT"));

	if(KeyInt==VK_UP)
		return CString(_T("VK_UP"));

	if(KeyInt==VK_RIGHT)
		return CString(_T("VK_RIGHT"));

	if(KeyInt==VK_DOWN)
		return CString(_T("VK_DOWN"));

	if(KeyInt==VK_SELECT)
		return CString(_T("VK_SELECT"));

	if(KeyInt==VK_PRINT)
		return CString(_T("VK_PRINT"));

	if(KeyInt==VK_EXECUTE)
		return CString(_T("VK_EXECUTE"));

	if(KeyInt==VK_SNAPSHOT)
		return CString(_T("VK_SNAPSHOT"));

	if(KeyInt==VK_INSERT)
		return CString(_T("VK_INSERT"));

	if(KeyInt==VK_DELETE)
		return CString(_T("VK_DELETE"));

	if(KeyInt==VK_HELP)
		return CString(_T("VK_HELP"));

	if((KeyInt>=0x30)&&(KeyInt<=0x5A))
	{
		IntToChar[0]=KeyInt;
		CString cIntToChar(IntToChar);
		return cIntToChar;
	}

	if(KeyInt==VK_SLEEP)
		return CString(_T("VK_SLEEP"));

	if(KeyInt==VK_NUMPAD0)
		return CString(_T("VK_NUMPAD0"));

	if(KeyInt==VK_NUMPAD1)
		return CString(_T("VK_NUMPAD1"));

	if(KeyInt==VK_NUMPAD2)
		return CString(_T("VK_NUMPAD2"));

	if(KeyInt==VK_NUMPAD3)
		return CString(_T("VK_NUMPAD3"));

	if(KeyInt==VK_NUMPAD4)
		return CString(_T("VK_NUMPAD4"));

	if(KeyInt==VK_NUMPAD5)
		return CString(_T("VK_NUMPAD5"));

	if(KeyInt==VK_NUMPAD6)
		return CString(_T("VK_NUMPAD6"));

	if(KeyInt==VK_NUMPAD7)
		return CString(_T("VK_NUMPAD7"));

	if(KeyInt==VK_NUMPAD8)
		return CString(_T("VK_NUMPAD8"));

	if(KeyInt==VK_NUMPAD9)
		return CString(_T("VK_NUMPAD9"));

	if(KeyInt==VK_MULTIPLY)
		return CString(_T("VK_MULTIPLY"));

	if(KeyInt==VK_ADD)
		return CString(_T("VK_ADD"));

	if(KeyInt==VK_SEPARATOR)
		return CString(_T("VK_SEPARATOR"));

	if(KeyInt==VK_SUBTRACT)
		return CString(_T("VK_SUBTRACT"));

	if(KeyInt==VK_DECIMAL)
		return CString(_T("VK_DECIMAL"));

	if(KeyInt==VK_DIVIDE)
		return CString(_T("VK_DIVIDE"));

	if(KeyInt==VK_LSHIFT)
		return CString(_T("VK_LSHIFT"));

	if(KeyInt==VK_RSHIFT)
		return CString(_T("VK_RSHIFT"));

	if(KeyInt==VK_LCONTROL)
		return CString(_T("VK_LCONTROL"));

	if(KeyInt==VK_RCONTROL)
		return CString(_T("VK_RCONTROL"));

	return CString(_T("None"));
}

int CKeyBoardSet::KeySetCharToInt(CString KeyChar)
{
	for(int i=1;i<256;i++)
	{
		if(cKeycharList[i]==KeyChar);
		return i;
	}
	return 0;
}

BOOL CKeyBoardSet::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	return CDialog::PreTranslateMessage(pMsg);
}
