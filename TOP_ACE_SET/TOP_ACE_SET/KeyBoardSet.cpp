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

}

CKeyBoardSet::~CKeyBoardSet()
{
}

void CKeyBoardSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CKeyBoardSet, CDialog)
//	ON_EN_CHANGE(IDC_EDIT3, &CKeyBoardSet::OnEnChangeEdit3)
//ON_EN_CHANGE(IDC_EDIT6, &CKeyBoardSet::OnEnChangeEdit6)
END_MESSAGE_MAP()


// CKeyBoardSet message handlers

//void CKeyBoardSet::OnEnChangeEdit3()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialog::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//}

//void CKeyBoardSet::OnEnChangeEdit6()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialog::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//}
