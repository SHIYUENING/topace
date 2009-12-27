#pragma once


// CSET_SOUND_DLG dialog

class CSET_SOUND_DLG : public CDialog
{
	DECLARE_DYNAMIC(CSET_SOUND_DLG)

public:
	CSET_SOUND_DLG(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSET_SOUND_DLG();

// Dialog Data
	enum { IDD = IDD_DIALOG_SET_SOUND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
