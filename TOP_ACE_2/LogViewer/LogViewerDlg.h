
// LogViewerDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#define MAXSHOWLOG 50
// CLogViewerDlg dialog
class CLogViewerDlg : public CDialogEx
{
// Construction
public:
	CLogViewerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LOGVIEWER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ShowNum;
	afx_msg void OnBnClickedButtonSaveLogFile();
	CListCtrl m_ListShow;
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};
