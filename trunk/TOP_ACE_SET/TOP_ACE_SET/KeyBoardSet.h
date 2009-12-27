#pragma once
#include "afxwin.h"


// CKeyBoardSet dialog

class CKeyBoardSet : public CDialog
{
	DECLARE_DYNAMIC(CKeyBoardSet)

public:
	CKeyBoardSet(CWnd* pParent = NULL);   // standard constructor
	virtual ~CKeyBoardSet();

// Dialog Data
	enum { IDD = IDD_DIALOG_KEYSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnEnChangeEdit3();
//	afx_msg void OnEnChangeEdit6();
};
