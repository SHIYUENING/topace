// TOP_ACE_SETDoc.cpp : CTOP_ACE_SETDoc ���ʵ��
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"

#include "TOP_ACE_SETDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTOP_ACE_SETDoc

IMPLEMENT_DYNCREATE(CTOP_ACE_SETDoc, CDocument)

BEGIN_MESSAGE_MAP(CTOP_ACE_SETDoc, CDocument)
END_MESSAGE_MAP()


// CTOP_ACE_SETDoc ����/����

CTOP_ACE_SETDoc::CTOP_ACE_SETDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CTOP_ACE_SETDoc::~CTOP_ACE_SETDoc()
{
}

BOOL CTOP_ACE_SETDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CTOP_ACE_SETDoc ���л�

void CTOP_ACE_SETDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CTOP_ACE_SETDoc ���

#ifdef _DEBUG
void CTOP_ACE_SETDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTOP_ACE_SETDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTOP_ACE_SETDoc ����
