// TOP_ACE_SET.h : TOP_ACE_SET Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CTOP_ACE_SETApp:
// �йش����ʵ�֣������ TOP_ACE_SET.cpp
//

class CTOP_ACE_SETApp : public CWinApp
{
public:
	CTOP_ACE_SETApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTOP_ACE_SETApp theApp;