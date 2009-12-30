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
	, ResolutionSet(-1)
{

}

CSystemSetDLG::~CSystemSetDLG()
{
}

void CSystemSetDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_COMBOBOX_Resolution);
	DDX_Control(pDX, IDC_EDIT1, m_EDIT_w);
	DDX_Control(pDX, IDC_EDIT2, m_EDIT_h);
	DDX_Control(pDX, IDC_COMBO3, m_COMBOBOX_ColorBit);
	DDX_Control(pDX, IDC_CHECK2, m_CHECK_SYNC);
	DDX_Control(pDX, IDC_COMBO2, m_COMBOBOX_AA);
}


BEGIN_MESSAGE_MAP(CSystemSetDLG, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CSystemSetDLG::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSystemSetDLG::OnBnClickedRadio2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSystemSetDLG::OnCbnSelchangeCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CSystemSetDLG::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CSystemSetDLG::OnEnKillfocusEdit2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CSystemSetDLG::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_CHECK2, &CSystemSetDLG::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CSystemSetDLG message handlers

void CSystemSetDLG::InitUI(void)
{
	ResolutionSet=-1;
	
	Init_COMBOBOX_Resolution();
	Init_COMBOBOX_ColorBit();
	CString cSetEdit;
	cSetEdit.Format(_T("%d"),GameSet.winW);
	m_EDIT_w.SetWindowTextW(cSetEdit);
	cSetEdit.Empty();
	cSetEdit.Format(_T("%d"),GameSet.winH);
	m_EDIT_h.SetWindowTextW(cSetEdit);

	m_CHECK_SYNC.SetCheck(GameSet.SYNC);
	if(ResolutionSet>=0)
	{
		m_COMBOBOX_Resolution.SetCurSel(ResolutionSet);
		CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);
		m_COMBOBOX_Resolution.EnableWindow(true);
		m_EDIT_w.EnableWindow(false);
		m_EDIT_h.EnableWindow(false);
		m_COMBOBOX_ColorBit.EnableWindow(false);
	}
	else
	{
		m_COMBOBOX_Resolution.SetCurSel(0);
		CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO2);
		OnBnClickedRadio2();
	}
	
}

void CSystemSetDLG::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	GameSet.isFullScreem=true;
	m_COMBOBOX_Resolution.EnableWindow(true);
	m_EDIT_w.EnableWindow(false);
	m_EDIT_h.EnableWindow(false);
	m_COMBOBOX_ColorBit.EnableWindow(false);
	OnCbnSelchangeCombo1();
}

void CSystemSetDLG::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	ResolutionSet=-1;
	GameSet.isFullScreem=false;
	m_COMBOBOX_Resolution.EnableWindow(false);
	m_EDIT_w.EnableWindow(true);
	m_EDIT_h.EnableWindow(true);
	m_COMBOBOX_ColorBit.EnableWindow(true);
	OnEnKillfocusEdit1();
	OnEnKillfocusEdit2();
}

void CSystemSetDLG::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	CString getResolutionSet;
	ResolutionSet=m_COMBOBOX_Resolution.GetCurSel();
	if(ResolutionSet<0)
	{
		ResolutionSet=0;
		m_COMBOBOX_Resolution.SetCurSel(0);
	}
	m_COMBOBOX_Resolution.GetLBText(ResolutionSet,getResolutionSet);
	if(getResolutionSet.IsEmpty())
		return;
	swscanf_s(getResolutionSet.GetBuffer(),_T("%d X %d %dbit"),&GameSet.winW,&GameSet.winH,&GameSet.bits);
}

void CSystemSetDLG::OnEnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
	CString getResolutionSet;
	m_EDIT_w.GetWindowTextW(getResolutionSet);
	if(getResolutionSet.IsEmpty())
		return;
	swscanf_s(getResolutionSet.GetBuffer(),_T("%d"),&GameSet.winW);
}

void CSystemSetDLG::OnEnKillfocusEdit2()
{
	// TODO: Add your control notification handler code here
	CString getResolutionSet;
	m_EDIT_h.GetWindowTextW(getResolutionSet);
	if(getResolutionSet.IsEmpty())
		return;
	swscanf_s(getResolutionSet.GetBuffer(),_T("%d"),&GameSet.winH);
}

void CSystemSetDLG::Init_COMBOBOX_Resolution(void)
{
	DEVMODE   lpDevMode;
	int iModeNum=0;
	unsigned int ResolutionPels=0;
	m_COMBOBOX_Resolution.ResetContent();
	while( EnumDisplaySettings(NULL,iModeNum,&lpDevMode))
	{
		iModeNum=iModeNum+1;
		CString cDevMode;
		if(lpDevMode.dmBitsPerPel>8)
		{
			if(ResolutionPels!=lpDevMode.dmBitsPerPel)
			{
				cDevMode.Format(_T("%d X %d %dbit"),lpDevMode.dmPelsWidth,lpDevMode.dmPelsHeight,lpDevMode.dmBitsPerPel);
				if(ResolutionPels>(lpDevMode.dmPelsWidth*lpDevMode.dmPelsHeight))
					m_COMBOBOX_Resolution.AddString(cDevMode);
				else
					m_COMBOBOX_Resolution.InsertString(0,cDevMode);
				ResolutionPels=lpDevMode.dmBitsPerPel;
			}
		}
	}
	iModeNum=0;
	if(GameSet.isFullScreem)
	for(int i=0;i<m_COMBOBOX_Resolution.GetCount();i++)
	{
		CString ctestResolutionSet1,ctestResolutionSet12;
		ctestResolutionSet1.Format(_T("%d X %d %dbit"),GameSet.winW,GameSet.winH,GameSet.bits);
		m_COMBOBOX_Resolution.GetLBText(i,ctestResolutionSet12);
		if(ctestResolutionSet12.IsEmpty())
			break;
		if(ctestResolutionSet1==ctestResolutionSet12)
		{
			ResolutionSet=i;
			break;
		}
	}
}

void CSystemSetDLG::Init_COMBOBOX_ColorBit(void)
{
	m_COMBOBOX_ColorBit.AddString(_T("32bit"));
	m_COMBOBOX_ColorBit.AddString(_T("16bit"));
	for(int i=0;i<m_COMBOBOX_ColorBit.GetCount();i++)
	{
		CString ctestColorBitSet1,ctestColorBitSet12;
		ctestColorBitSet1.Format(_T("%dbit"),GameSet.bits);
		m_COMBOBOX_ColorBit.GetLBText(i,ctestColorBitSet12);
		if(ctestColorBitSet12.IsEmpty())
			break;
		if(ctestColorBitSet1==ctestColorBitSet12)
		{
			m_COMBOBOX_ColorBit.SetCurSel(i);
			break;
		}
	}
}

void CSystemSetDLG::OnCbnSelchangeCombo3()
{
	CString getColorBitSet;
	int ColorBitSet=m_COMBOBOX_ColorBit.GetCurSel();
	if(ColorBitSet<0)
		return;
	m_COMBOBOX_ColorBit.GetLBText(ColorBitSet,getColorBitSet);
	if(getColorBitSet.IsEmpty())
		return;
	swscanf_s(getColorBitSet.GetBuffer(),_T("%dbit"),&GameSet.bits);
}

void CSystemSetDLG::OnBnClickedCheck2()
{
	if(m_CHECK_SYNC.GetCheck()>0)
		GameSet.SYNC=true;
	else
		GameSet.SYNC=false;
}
