// TOP_ACE_SETDoc.h : CTOP_ACE_SETDoc ��Ľӿ�
//


#pragma once


class CTOP_ACE_SETDoc : public CDocument
{
protected: // �������л�����
	CTOP_ACE_SETDoc();
	DECLARE_DYNCREATE(CTOP_ACE_SETDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CTOP_ACE_SETDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


