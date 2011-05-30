//#pragma once
#ifndef _GFXUI_H
#define _GFXUI_H
#define USEGFX 1

#ifdef USEGFX
#include "GTimer.h"
#include "GFxEvent.h"
#include "GFxPlayer.h"
#include "GFxFontLib.h"

#include "GFxLog.h"
//#include "FxPlayerLog.h"
#include "GRendererOGL.h"
#endif
#include <windows.h>
#include "IniFile.h"
class CGFXUI
{
public:
	CGFXUI(void);
	~CGFXUI(void);
	static void Init(void);
	#ifdef USEGFX
	GFxLoader gfxLoader;
	GPtr<GFxMovieDef>   pUIMovieDef;
	GPtr<GFxMovieDef>   pUIMovieDefStandBy;
	GPtr<GRendererOGL>   pRenderer;
	GPtr<GFxMovieView>  pUIMovie;
	GPtr<GFxMovieView>  pUIMovieStandBy;
	#endif
	DWORD  MovieLastTime;
	bool InitGFX(void);
	void ChangeWin(int gfxx,int gfxy ,int gfxw,int gfxh);
	void Draw(void);
	void SetInput(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void GetCommend(void);
};

#endif