// GamePadSet.cpp : implementation file
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"
#include "GamePadSet.h"
#include"IniFile.h"

// CGamePadSet dialog

IMPLEMENT_DYNAMIC(CGamePadSet, CDialog)
extern tGameSet GameSet;
extern tSoundSet SoundSet;
extern tJoyStictSet JoyStictSet;
extern tKeyBoardSet KeyBoardSet;
CGamePadSet::CGamePadSet(CWnd* pParent /*=NULL*/)
	: CDialog(CGamePadSet::IDD, pParent)
{

}

CGamePadSet::~CGamePadSet()
{
}

void CGamePadSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEY1, m_Edit_KEY_UP);
}


BEGIN_MESSAGE_MAP(CGamePadSet, CDialog)
END_MESSAGE_MAP()


// CGamePadSet message handlers
