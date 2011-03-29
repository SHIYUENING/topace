// KeyMapDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"
#include "KeyMapDlg.h"

// CKeyMapDlg �Ի���

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


// CKeyMapDlg ��Ϣ�������

BOOL CKeyMapDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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

	m_LTEXT_KEY_NOW.SetWindowText(_T("��ǰ����"));
	m_LTEXT_KEY_NEXT.SetWindowText(_T("�°���"));
	
	((CButton *)GetDlgItem(IDC_BUTTON1))->SetWindowText(_T("���"));
	((CButton *)GetDlgItem(IDOK))->SetWindowText(_T("ȷ��"));
	((CButton *)GetDlgItem(IDCANCEL))->SetWindowText(_T("ȡ��"));
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText( m_strTitle );

	m_cEdit.SetFocus();

	m_strMapOld = GetKeyName( m_uMapKey );
	UpdateData(FALSE);

	SetMapKey( m_uMapKey );
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog( IDOK );
}

void CKeyMapDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog( IDCANCEL );
}

CString GetKeyName( UINT a_uMapKey )
{
	CString str;
	const unsigned short uKey16 = (unsigned short)(a_uMapKey & 0x0000FFFF);

	switch( a_uMapKey >> 24 )
	{
	case 1:
		str.Format( _T("���X(%d)") , (short)uKey16 );
		break;
	case 2:
		str.Format( _T("���Y(%d)") , (short)uKey16 );
		break;
	default:
		str = getKeyString(a_uMapKey);
	}

	return str;
}

void CKeyMapDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetMapKey( KEY_NONE );
}
