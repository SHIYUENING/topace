// TOP_ACE_SETDoc.h : CTOP_ACE_SETDoc 类的接口
//


#pragma once


class CTOP_ACE_SETDoc : public CDocument
{
protected: // 仅从序列化创建
	CTOP_ACE_SETDoc();
	DECLARE_DYNCREATE(CTOP_ACE_SETDoc)

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CTOP_ACE_SETDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};


