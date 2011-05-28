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
class OurFSCommandHandler : public GFxFSCommandHandler
{
public:
    virtual void Callback(GFxMovieView* pmovie,
        const char* pcommand, const char* parg)
    {
		if(Commandchar ) delete[] Commandchar;
		if(pargchar ) delete[] pargchar;
		Commandchar=new char[strlen(pcommand)+1];Commandchar[strlen(pcommand)]=0;
		pargchar=new char[strlen(parg)+1];pargchar[strlen(parg)]=0;
		strcpy(Commandchar,pcommand);
		strcpy(pargchar,parg);
		if(strcmp(Commandchar,"blur")==0)
		{
			sscanf_s(pargchar,"%f,%f,%f",&(blurSet[0]),&(blurSet[1]),&(blurSet[2]));
			blurSet[0]=blurSet[0]*0.5f;
			blurSet[1]=blurSet[1]*0.5f;
			blurSet[3]=blurSet[2];
		}
		//MessageBox(NULL,Commandchar,parg,MB_OK);
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
	if(!pUIMovieDef)
		return false;
	pUIMovie = *pUIMovieDef->CreateInstance(GFxMovieDef::MemoryParams(), true);
	if(!pUIMovie)
		return false;
	ChangeWin(0,0,GameSet.winW,GameSet.winH);
	//ChangeWin(0,0,GameSet.winW/2,GameSet.winH/2);
		// Advance the movie to the first frame
	pUIMovie->Advance(0.0f, 0);

	// Note the time to determine the amount of time elapsed between this frame and the next
	MovieLastTime = timeGetTime();

	// Set the background stage color to alpha blend with the underlying 3D environment
	pUIMovie->SetBackgroundAlpha(0.0f);
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
	deltaTime=min(pUIMovie->GetFrameRate(),deltaTime);
	pUIMovie->Advance(deltaTime);
	pUIMovie->Display();
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
			GFxMouseEvent mevent(GFxEvent::MouseMove, 0,(float) mx,(float) my); 
		//	pUIMovie->HandleEvent(mevent);
			return ;
		}
		case WM_LBUTTONUP:
			{
			 mx = LOWORD(lParam), my = HIWORD(lParam);
			GFxMouseEvent mevent(GFxEvent::MouseUp, 0, (float)mx, (float)my); 
			pUIMovie->HandleEvent(mevent);
			return ;
		}
		case WM_LBUTTONDOWN:
		{
			 mx = LOWORD(lParam), my = HIWORD(lParam);
			GFxMouseEvent mevent(GFxEvent::MouseDown, 0, (float)mx, (float)my); 
			pUIMovie->HandleEvent(mevent);
			return ;
		}
	
	}
	#endif
}


void CGFXUI::GetCommend(void)
{
}
