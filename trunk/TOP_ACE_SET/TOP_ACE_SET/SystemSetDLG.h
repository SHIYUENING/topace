#pragma once


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
};
