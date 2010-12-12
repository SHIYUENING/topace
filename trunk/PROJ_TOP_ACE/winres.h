// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

// winres.h - Windows resource definitions
//  extracted from WINUSER.H and COMMCTRL.H

#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, off)
#endif

#define VS_VERSION_INFO     1

#ifdef APSTUDIO_INVOKED
#define APSTUDIO_HIDDEN_SYMBOLS // Ignore following symbols
#endif

#ifndef WINVER
#ifndef _WIN32_WCE
#define WINVER 0x0500   // default to Windows 2000
#else // _WIN32_WCE
#define WINVER 0x0400   // default appropriate value for Windows CE, although this is not strongly correlated to the OS version
#endif // _WIN32_WCE
#endif

#ifndef _WIN32_WCE
#include <winresrc.h>
#else // _WIN32_WCE
#include <dlgs.h>
#include <winbase.h>
#include <commctrl.h>
#include <resdefce.h>
#endif // _WIN32_WCE

// operation messages sent to DLGINIT
#ifndef LB_ADDSTRING 
#define LB_ADDSTRING    (WM_USER+1)
#endif
#ifndef CB_ADDSTRING
#define CB_ADDSTRING    (WM_USER+3)
#endif

#ifdef APSTUDIO_INVOKED
#undef APSTUDIO_HIDDEN_SYMBOLS
#endif

#ifdef IDC_STATIC
#undef IDC_STATIC
#endif
#define IDC_STATIC      (-1)

#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, on)
#endif
