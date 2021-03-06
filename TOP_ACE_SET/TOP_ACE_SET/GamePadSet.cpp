// GamePadSet.cpp : implementation file
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"
#include "GamePadSet.h"
#include"IniFile.h"

// CGamePadSet dialog

IMPLEMENT_DYNAMIC(CGamePadSet, CTopAceDialog)
extern tGameSet GameSet;
extern tSoundSet SoundSet;
extern tJoyStictSet JoyStictSet;

CGamePadSet::CGamePadSet(CWnd* pParent /*=NULL*/)
	: CTopAceDialog(CGamePadSet::IDD, pParent)
{

}

CGamePadSet::~CGamePadSet()
{
}

void CGamePadSet::DoDataExchange(CDataExchange* pDX)
{
	CTopAceDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEY1, m_EDIT[JOY_KEY_UP]);
	DDX_Control(pDX, IDC_EDIT_KEY2, m_EDIT[JOY_KEY_DOWN]);
	DDX_Control(pDX, IDC_EDIT_KEY3, m_EDIT[JOY_KEY_LEFT]);
	DDX_Control(pDX, IDC_EDIT_KEY4, m_EDIT[JOY_KEY_RIGHT]);

	DDX_Control(pDX, IDC_EDIT_KEY5, m_EDIT[JOY_KEY_VIEW_UP]);
	DDX_Control(pDX, IDC_EDIT_KEY6, m_EDIT[JOY_KEY_VIEW_DOWN]);
	DDX_Control(pDX, IDC_EDIT_KEY7, m_EDIT[JOY_KEY_VIEW_LEFT]);
	DDX_Control(pDX, IDC_EDIT_KEY8, m_EDIT[JOY_KEY_VIEW_RIGHT]);

	DDX_Control(pDX, IDC_EDIT_KEY9, m_EDIT[JOY_KEY_SPEED_UP]);
	DDX_Control(pDX, IDC_EDIT_KEY10, m_EDIT[JOY_KEY_SPEED_DOWN]);
	DDX_Control(pDX, IDC_EDIT_KEY11, m_EDIT[JOY_KEY_L]);
	DDX_Control(pDX, IDC_EDIT_KEY12, m_EDIT[JOY_KEY_R]);

	DDX_Control(pDX, IDC_EDIT_KEY13, m_EDIT[JOY_KEY_MAIN_WEAPON]);
	DDX_Control(pDX, IDC_EDIT_KEY14, m_EDIT[JOY_KEY_SUB_WEAPON]);
	DDX_Control(pDX, IDC_EDIT_KEY15, m_EDIT[JOY_KEY_MAP]);
	DDX_Control(pDX, IDC_EDIT_KEY16, m_EDIT[JOY_KEY_LOCK]);

	DDX_Control(pDX, IDC_EDIT_KEY17, m_EDIT[JOY_KEY_SELECT]);
	DDX_Control(pDX, IDC_EDIT_KEY18, m_EDIT[JOY_KEY_START]);
	DDX_Control(pDX, IDC_EDIT_KEY19, m_EDIT[JOY_KEY_VIEW_RESET]);
}


BEGIN_MESSAGE_MAP(CGamePadSet, CTopAceDialog)
END_MESSAGE_MAP()


// CGamePadSet message handlers

void CGamePadSet::InitUI(void)
{
	CString CSetWindowText;
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_UP]);
	m_EDIT[JOY_KEY_UP].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_DOWN]);
	m_EDIT[JOY_KEY_DOWN].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_LEFT]);
	m_EDIT[JOY_KEY_LEFT].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_RIGHT]);
	m_EDIT[JOY_KEY_RIGHT].SetWindowText(CSetWindowText);

	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_MAIN_WEAPON]);
	m_EDIT[JOY_KEY_MAIN_WEAPON].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_SUB_WEAPON]);
	m_EDIT[JOY_KEY_SUB_WEAPON].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_LOCK]);
	m_EDIT[JOY_KEY_LOCK].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_MAP]);
	m_EDIT[JOY_KEY_MAP].SetWindowText(CSetWindowText);

	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_SPEED_UP]);
	m_EDIT[JOY_KEY_SPEED_UP].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_SPEED_DOWN]);
	m_EDIT[JOY_KEY_SPEED_DOWN].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_L]);
	m_EDIT[JOY_KEY_L].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_R]);
	m_EDIT[JOY_KEY_R].SetWindowText(CSetWindowText);

	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_VIEW_UP]);
	m_EDIT[JOY_KEY_VIEW_UP].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_VIEW_DOWN]);
	m_EDIT[JOY_KEY_VIEW_DOWN].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_VIEW_LEFT]);
	m_EDIT[JOY_KEY_VIEW_LEFT].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_VIEW_RIGHT]);
	m_EDIT[JOY_KEY_VIEW_RIGHT].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_VIEW_RESET]);
	m_EDIT[JOY_KEY_VIEW_RESET].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_SELECT]);
	m_EDIT[JOY_KEY_SELECT].SetWindowText(CSetWindowText);
	CSetWindowText.Format(_T("%d"),JoyStictSet.KeySet[JOY_KEY_START]);
	m_EDIT[JOY_KEY_START].SetWindowText(CSetWindowText);
}
