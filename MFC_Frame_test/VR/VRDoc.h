// VRDoc.h : interface of the CVRDoc class
//


#pragma once


class CVRDoc : public CDocument
{
protected: // create from serialization only
	CVRDoc();
	DECLARE_DYNCREATE(CVRDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CVRDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


