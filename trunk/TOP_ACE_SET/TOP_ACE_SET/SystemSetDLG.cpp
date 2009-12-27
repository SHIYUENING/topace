// SystemSetDLG.cpp : implementation file
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"
#include "SystemSetDLG.h"
#include"IniFile.h"

// CSystemSetDLG dialog

IMPLEMENT_DYNAMIC(CSystemSetDLG, CDialog)
extern tGameSet GameSet;
extern tSoundSet SoundSet;
extern tJoyStictSet JoyStictSet;
extern tKeyBoardSet KeyBoardSet;
CSystemSetDLG::CSystemSetDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemSetDLG::IDD, pParent)
{

}

CSystemSetDLG::~CSystemSetDLG()
{
}

void CSystemSetDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSystemSetDLG, CDialog)
END_MESSAGE_MAP()


// CSystemSetDLG message handlers
