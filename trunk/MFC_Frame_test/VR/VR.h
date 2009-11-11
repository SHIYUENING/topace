// VR.h : main header file for the VR application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CVRApp:
// See VR.cpp for the implementation of this class
//

class CVRApp : public CWinApp
{
public:
	CVRApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVRApp theApp;