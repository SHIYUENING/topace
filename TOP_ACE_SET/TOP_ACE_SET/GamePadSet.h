#pragma once
#include "afxwin.h"


// CGamePadSet dialog

class CGamePadSet : public CDialog
{
	DECLARE_DYNAMIC(CGamePadSet)

public:
	CGamePadSet(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGamePadSet();

// Dialog Data
	enum { IDD = IDD_DIALOG_KEYBOARDSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit_KEY_UP;
};
