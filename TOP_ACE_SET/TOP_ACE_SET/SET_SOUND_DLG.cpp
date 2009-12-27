// SET_SOUND_DLG.cpp : implementation file
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"
#include "SET_SOUND_DLG.h"
#include"IniFile.h"

// CSET_SOUND_DLG dialog

IMPLEMENT_DYNAMIC(CSET_SOUND_DLG, CDialog)
extern tGameSet GameSet;
extern tSoundSet SoundSet;
extern tJoyStictSet JoyStictSet;
extern tKeyBoardSet KeyBoardSet;
CSET_SOUND_DLG::CSET_SOUND_DLG(CWnd* pParent /*=NULL*/)
	: CDialog(CSET_SOUND_DLG::IDD, pParent)
{

}

CSET_SOUND_DLG::~CSET_SOUND_DLG()
{
}

void CSET_SOUND_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSET_SOUND_DLG, CDialog)
END_MESSAGE_MAP()


// CSET_SOUND_DLG message handlers
