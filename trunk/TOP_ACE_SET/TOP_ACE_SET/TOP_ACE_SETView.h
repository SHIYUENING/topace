// TOP_ACE_SETView.h : CTOP_ACE_SETView 类的接口
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
protected: // 仅从序列化创建
	CTOP_ACE_SETView();
	DECLARE_DYNCREATE(CTOP_ACE_SETView)

public:
	enum{ IDD = IDD_TOP_ACE_SET_FORM };

// 属性
public:
	CTOP_ACE_SETDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CTOP_ACE_SETView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // TOP_ACE_SETView.cpp 中的调试版本
inline CTOP_ACE_SETDoc* CTOP_ACE_SETView::GetDocument() const
   { return reinterpret_cast<CTOP_ACE_SETDoc*>(m_pDocument); }
#endif

