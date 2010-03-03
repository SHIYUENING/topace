#pragma once

#include "Key.h"
// CKeyMapDlg 对话框

class CKeyMapDlg : public CDialog
{
	DECLARE_DYNAMIC(CKeyMapDlg)

public:
	CKeyMapDlg(UINT a_uMapKey , const TCHAR* a_szTitle , CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CKeyMapDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_KEYMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnCancel();
	virtual void OnOK();
private:
	CEdit m_cEdit;
public:
	virtual BOOL OnInitDialog();
private:
	CString m_strTitle;

	CString m_strMapOld;
	UINT m_uMapKeyOld;

	UINT m_uMapKey;

	void SetMapKey( UINT a_uMapKey );
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	inline UINT GetKey()const
	{
		return m_uMapKey;
	}
	afx_msg void OnBnClickedButton1();
};

CString GetKeyName( UINT a_uMapKey );
