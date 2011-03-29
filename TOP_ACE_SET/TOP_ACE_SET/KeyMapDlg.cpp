// KeyMapDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"
#include "KeyMapDlg.h"

// CKeyMapDlg 对话框

IMPLEMENT_DYNAMIC(CKeyMapDlg, CDialog)

CKeyMapDlg::CKeyMapDlg( UINT a_uMapKey , const TCHAR* a_szTitle , CWnd* pParent /*=NULL*/)
: CDialog(CKeyMapDlg::IDD, pParent)
, m_strMapOld(_T(""))
, m_uMapKeyOld(a_uMapKey)
, m_uMapKey(a_uMapKey)
, m_strTitle(a_szTitle)
{

}

CKeyMapDlg::~CKeyMapDlg()
{
}

void CKeyMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_cEdit);
	DDX_Text(pDX, IDC_EDIT2, m_strMapOld);
	DDX_Control(pDX, IDC_STATIC_KEY_NOW, m_LTEXT_KEY_NOW);
	DDX_Control(pDX, IDC_STATIC_KEY_NEXT, m_LTEXT_KEY_NEXT);
}


BEGIN_MESSAGE_MAP(CKeyMapDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CKeyMapDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CKeyMapDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CKeyMapDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CKeyMapDlg 消息处理程序

BOOL CKeyMapDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if( pMsg->message == WM_KEYDOWN && GetFocus() == &m_cEdit )
	{
		SetMapKey( pMsg->wParam );

		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CKeyMapDlg::OnCancel(){}
void CKeyMapDlg::OnOK(){}

BOOL CKeyMapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_LTEXT_KEY_NOW.SetWindowText(_T("当前按键"));
	m_LTEXT_KEY_NEXT.SetWindowText(_T("新按键"));
	
	((CButton *)GetDlgItem(IDC_BUTTON1))->SetWindowText(_T("清除"));
	((CButton *)GetDlgItem(IDOK))->SetWindowText(_T("确定"));
	((CButton *)GetDlgItem(IDCANCEL))->SetWindowText(_T("取消"));
	// TODO:  在此添加额外的初始化
	SetWindowText( m_strTitle );

	m_cEdit.SetFocus();

	m_strMapOld = GetKeyName( m_uMapKey );
	UpdateData(FALSE);

	SetMapKey( m_uMapKey );
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CKeyMapDlg::SetMapKey( UINT a_uMapKey )
{
	m_cEdit.SetWindowText(_T(""));

	const unsigned short uKey16 = (unsigned short)(a_uMapKey & 0x0000FFFF);

	m_cEdit.SetWindowText(GetKeyName( a_uMapKey ));
	m_uMapKey = a_uMapKey;
}

void CKeyMapDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog( IDOK );
}

void CKeyMapDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog( IDCANCEL );
}

CString GetKeyName( UINT a_uMapKey )
{
	CString str;
	const unsigned short uKey16 = (unsigned short)(a_uMapKey & 0x0000FFFF);

	switch( a_uMapKey >> 24 )
	{
	case 1:
		str.Format( _T("鼠标X(%d)") , (short)uKey16 );
		break;
	case 2:
		str.Format( _T("鼠标Y(%d)") , (short)uKey16 );
		break;
	default:
		str = getKeyString(a_uMapKey);
	}

	return str;
}

void CKeyMapDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	SetMapKey( KEY_NONE );
}
