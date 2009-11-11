// VRDoc.cpp : implementation of the CVRDoc class
//

#include "stdafx.h"
#include "VR.h"

#include "VRDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVRDoc

IMPLEMENT_DYNCREATE(CVRDoc, CDocument)

BEGIN_MESSAGE_MAP(CVRDoc, CDocument)
END_MESSAGE_MAP()


// CVRDoc construction/destruction

CVRDoc::CVRDoc()
{
	// TODO: add one-time construction code here

}

CVRDoc::~CVRDoc()
{
}

BOOL CVRDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CVRDoc serialization

void CVRDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CVRDoc diagnostics

#ifdef _DEBUG
void CVRDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVRDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CVRDoc commands
