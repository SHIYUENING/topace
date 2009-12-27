#pragma once
#include "afxwin.h"


// CSystemSetDLG dialog

class CSystemSetDLG : public CDialog
{
	DECLARE_DYNAMIC(CSystemSetDLG)

public:
	CSystemSetDLG(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSystemSetDLG();

// Dialog Data
	enum { IDD = IDD_DIALOG_SET_SYS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void InitUI(void);
	CComboBox m_COMBOBOX_Resolution;
	int ResolutionSet;
};
