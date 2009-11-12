// VRView.h : interface of the CVRView class
//


#pragma once

#include <gl\gl.h>

#include <gl\glu.h>   

#include <gl\glaux.h>
class CVRView : public CView
{
protected: // create from serialization only
	CVRView();
	DECLARE_DYNCREATE(CVRView)

// Attributes
public:
	CVRDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CVRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool SetupPixFormat(CDC * pDC);
	bool InitialGL(void);
	CClientDC* m_pDC;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	bool DrawScene(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	float turnX;
	afx_msg void OnAaaXxxx();
};

#ifndef _DEBUG  // debug version in VRView.cpp
inline CVRDoc* CVRView::GetDocument() const
   { return reinterpret_cast<CVRDoc*>(m_pDocument); }
#endif

