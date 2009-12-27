// TOP_ACE_SETDoc.cpp : CTOP_ACE_SETDoc 类的实现
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


// CTOP_ACE_SETDoc 构造/析构

CTOP_ACE_SETDoc::CTOP_ACE_SETDoc()
{
	// TODO: 在此添加一次性构造代码

}

CTOP_ACE_SETDoc::~CTOP_ACE_SETDoc()
{
}

BOOL CTOP_ACE_SETDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CTOP_ACE_SETDoc 序列化

void CTOP_ACE_SETDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CTOP_ACE_SETDoc 诊断

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


// CTOP_ACE_SETDoc 命令
