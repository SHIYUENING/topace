// TOP_ACE_SETView.h : CTOP_ACE_SETView ��Ľӿ�
//


#pragma once
#include "SystemSetDLG.h"
#include "GamePadSet.h"
#include "KeyBoardSet.h"
#include "SET_SOUND_DLG.h"


#include "afxcmn.h"
#include"IniFile.h"
class CTOP_ACE_SETView : public CFormView
{
protected: // �������л�����
	CTOP_ACE_SETView();
	DECLARE_DYNCREATE(CTOP_ACE_SETView)

public:
	enum{ IDD = IDD_TOP_ACE_SET_FORM };

// ����
public:
	CTOP_ACE_SETDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CTOP_ACE_SETView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	CSystemSetDLG m_SystemSetDLG;
	CGamePadSet m_GamePadSetDLG;
	CKeyBoardSet m_KeyBoardSetDLG;
	CSET_SOUND_DLG m_SetSoundDLG;

	CTabCtrl m_TabCtrl;
//	afx_msg void OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_CurSelTab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
};

#ifndef _DEBUG  // TOP_ACE_SETView.cpp �еĵ��԰汾
inline CTOP_ACE_SETDoc* CTOP_ACE_SETView::GetDocument() const
   { return reinterpret_cast<CTOP_ACE_SETDoc*>(m_pDocument); }
#endif

