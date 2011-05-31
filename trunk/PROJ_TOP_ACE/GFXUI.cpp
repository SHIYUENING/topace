#include "GFXUI.h"
#ifdef USEGFX
#endif
#ifdef USEGFX
#pragma comment( lib, "expat.lib" )
#pragma comment( lib, "libgfx.lib" )	
#pragma comment( lib, "libgfx_expat.lib" )	
#pragma comment( lib, "libgrenderer_gl.lib" )	
#pragma comment( lib, "libjpeg.lib" )	
#pragma comment( lib, "libpng.lib" )	
#pragma comment( lib, "zlib.lib" )		
#pragma comment( lib, "nvtt.lib" )
#pragma comment( lib, "winmm.lib" )	
char * Commandchar=NULL;
char * pargchar=NULL;
float blurSet[4]={-1.0f};
float notouchtime=0.0f;
bool DrawStandby=true;
extern float GFXPosMove[2];
class OurFSCommandHandler : public GFxFSCommandHandler
{
public:
    virtual void Callback(GFxMovieView* pmovie,
        const char* pcommand, const char* parg)
    {
		if(strcmp(pcommand,"blur")==0)
		{
			sscanf_s(parg,"%f,%f,%f",&(blurSet[0]),&(blurSet[1]),&(blurSet[2]));
			blurSet[0]=blurSet[0]*0.5f;
			blurSet[1]=blurSet[1]*0.5f;
			blurSet[3]=blurSet[2];
			return;
		}//
		
		if(strcmp("Move",pcommand)==0)
		{
			if(strcmp("up",parg)==0)
			{
				GFXPosMove[1]=10.0f;
			}
			if(strcmp("down",parg)==0)
			{
				GFXPosMove[1]=-10.0f;
			}
			if(strcmp("left",parg)==0)
			{
				GFXPosMove[0]=-10.0f;
			}
			if(strcmp("right",parg)==0)
			{
				GFXPosMove[0]=10.0f;
			}
		}
		if(strcmp("MoveEnd",pcommand)==0)
		{
			GFXPosMove[0]=GFXPosMove[0]*0.925f;
			GFXPosMove[1]=GFXPosMove[1]*0.925f;
		}
		if(strcmp("StandBy",parg)==0)
		{
			DrawStandby=false;
			return;
		}

		if(Commandchar ) delete[] Commandchar;
		if(pargchar ) delete[] pargchar;
		Commandchar=new char[strlen(pcommand)+1];Commandchar[strlen(pcommand)]=0;
		pargchar=new char[strlen(parg)+1];pargchar[strlen(parg)]=0;
		strcpy(Commandchar,pcommand);
		strcpy(pargchar,parg);
		
    }
};
#endif
CGFXUI::CGFXUI(void)
	:MovieLastTime(0)
{
}


CGFXUI::~CGFXUI(void)
{
	#ifdef USEGFX
	GMemory::DetectMemoryLeaks();
	#endif
}


void CGFXUI::Init(void)
{
	#ifdef USEGFX
	GFxSystem::Init();
	#endif
}


bool CGFXUI::InitGFX(void)
{
	#ifdef USEGFX
	GPtr<GFxRenderConfig> pRenderConfig;
	GPtr<GFxRenderStats>  pRenderStats;
	GFxLog * m_gfxlog = new GFxLog;
	gfxLoader.SetLog(m_gfxlog);
	GPtr<GFxFSCommandHandler> pcommandHandler = *new OurFSCommandHandler;
	gfxLoader.SetFSCommandHandler(pcommandHandler);
	GPtr<GFxFileOpener> pfileOpener = *new GFxFileOpener;
	gfxLoader.SetFileOpener(pfileOpener);
	pRenderer = *GRendererOGL::CreateRenderer();
	pRenderer->SetDependentVideoMode();
	pRenderConfig = *new GFxRenderConfig(pRenderer);
	if(!pRenderer || !pRenderConfig)
		return false;
	gfxLoader.SetRenderConfig(pRenderConfig);
	pRenderConfig->SetRenderFlags(GFxRenderConfig::RF_EdgeAA);
	pUIMovieDef = *(gfxLoader.CreateMovie("window.swf",
		                                  GFxLoader::LoadKeepBindData |
										  GFxLoader::LoadWaitFrame1));
	pUIMovieDefStandBy = *(gfxLoader.CreateMovie("bg2.swf",
		                                  GFxLoader::LoadKeepBindData |
										  GFxLoader::LoadWaitFrame1));
	if(!pUIMovieDef)
		return false;
	if(!pUIMovieDefStandBy) return false;
	pUIMovie = *pUIMovieDef->CreateInstance(GFxMovieDef::MemoryParams(), true);
	pUIMovieStandBy = *pUIMovieDefStandBy->CreateInstance(GFxMovieDef::MemoryParams(), true);
	if(!pUIMovie)
		return false;
	if(!pUIMovieStandBy)
		return false;
	ChangeWin(0,0,GameSet.winW,GameSet.winH);
	//ChangeWin(0,0,GameSet.winW/2,GameSet.winH/2);
		// Advance the movie to the first frame
	pUIMovie->Advance(0.0f, 0);
	pUIMovieStandBy->Advance(0.0f, 0);

	// Note the time to determine the amount of time elapsed between this frame and the next
	MovieLastTime = timeGetTime();

	// Set the background stage color to alpha blend with the underlying 3D environment
	pUIMovie->SetBackgroundAlpha(0.0f);
	pUIMovieStandBy->SetBackgroundAlpha(0.0f);
	return true;
	#else
	return false;
	#endif
	
}


void CGFXUI::ChangeWin(int gfxx,int gfxy ,int gfxw,int gfxh)
{
	#ifdef USEGFX
	if(!pUIMovieDef)
		return;
	if(!pUIMovie)
		return;
	pRenderer->SetDependentVideoMode();
	pUIMovie->SetViewport(gfxw,gfxh,gfxx,gfxy,gfxw,gfxh);
	pUIMovie->SetViewScaleMode(GFxMovieView::SM_ExactFit);
	pUIMovie->SetViewAlignment(GFxMovieView::Align_CenterRight);
	pUIMovieStandBy->SetViewport(gfxw,gfxh,gfxx,gfxy,gfxw,gfxh);
	pUIMovieStandBy->SetViewScaleMode(GFxMovieView::SM_ExactFit);
	pUIMovieStandBy->SetViewAlignment(GFxMovieView::Align_CenterRight);
	#endif
}


void CGFXUI::Draw(void)
{
	#ifdef USEGFX
	if(!pUIMovieDef)
		return;
	if(!pUIMovie)
		return;
	DWORD mtime = timeGetTime();
    float deltaTime = ((float)(mtime - MovieLastTime)) / 1000.0f;
	MovieLastTime = mtime;
	notouchtime=notouchtime+deltaTime;
	if(notouchtime>(15.0f*60.0f))
	{
		DrawStandby=true;
		pUIMovieStandBy->Restart();
	}
	//deltaTime=min(pUIMovie->GetFrameRate(),deltaTime);
	if(!DrawStandby)
	{
	pUIMovie->Advance(deltaTime);
	pUIMovie->Display();
	}
	else
	{
		pUIMovieStandBy->Advance(deltaTime);
		pUIMovieStandBy->Display();
	}
	#endif
}


void CGFXUI::SetInput(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	#ifdef USEGFX
	int mx,my;
	switch (uMsg)	
	{
		case WM_MOUSEMOVE:
			{
			 mx = LOWORD(lParam), my = HIWORD(lParam);
			 GFxMouseEvent mevent(GFxEvent::MouseUp, 0,(float) mx,(float) my); 
			if(pUIMovie)
			pUIMovie->HandleEvent(mevent);
			return ;
		}
		case WM_LBUTTONUP:
			{
				GFXPosMove[0]=GFXPosMove[0]*0.925f;
			GFXPosMove[1]=GFXPosMove[1]*0.925f;
			 mx = LOWORD(lParam), my = HIWORD(lParam);
			GFxMouseEvent mevent(GFxEvent::MouseUp, 0, (float)mx, (float)my); 
			if(pUIMovie)
			pUIMovie->HandleEvent(mevent);
			if(pUIMovieStandBy)
			pUIMovieStandBy->HandleEvent(mevent);
			return ;
		}
		case WM_LBUTTONDOWN:
		{
			GFXPosMove[0]=GFXPosMove[0]*0.925f;
			GFXPosMove[1]=GFXPosMove[1]*0.925f;
			 mx = LOWORD(lParam), my = HIWORD(lParam);
			GFxMouseEvent mevent(GFxEvent::MouseDown, 0, (float)mx, (float)my); 
			if(pUIMovie)
			pUIMovie->HandleEvent(mevent);
			if(pUIMovieStandBy)
			pUIMovieStandBy->HandleEvent(mevent);
			return ;
		}
	
	}
	#endif
}


void CGFXUI::GetCommend(void)
{
}
