// TOP_ACE_SET.h : TOP_ACE_SET 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CTOP_ACE_SETApp:
// 有关此类的实现，请参阅 TOP_ACE_SET.cpp
//

class CTOP_ACE_SETApp : public CWinApp
{
public:
	CTOP_ACE_SETApp();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTOP_ACE_SETApp theApp;