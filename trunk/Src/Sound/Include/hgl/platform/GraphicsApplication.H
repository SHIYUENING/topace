#ifndef HGL_GRAPHICS_APPLICATION_INCLUDE
#define HGL_GRAPHICS_APPLICATION_INCLUDE

#include<hgl/platform/BaseApplication.H>
#include<hgl/platform/Window.H>
namespace hgl
{
	class TileFont;

	/**
	* 图形应用程序基类
	*/
	class GraphicsApplication:public BaseApplication                                                ///图形应用序基类
	{
	protected:

		#include<hgl/Object.ProcEvent.H>

	public:

		virtual void SetSize(int,int);

	protected:

		Window *win;

		TileFont *default_font;

		uint cur_fps;
		double interval_time;

		void InitGraphics();

	protected:
		
		Window *	GetWin()		{return win;}

		uint		GetFPS()		{return cur_fps;}
		void		SetFPS(uint);

		TileFont *	GetDefaultFont(){return default_font;}

	public:	//属性

		Property<Window *>		Win;																///<当前窗口
		Property<uint32>		FPS;																///<当前刷新频率
		Property<TileFont *>	DefaultFont;														///<缺省字体(GUI模块使用)

	public:	//事件

		DefEvent(void,OnResize,(int,int));															///<窗口大小被调整了

	public:

		GraphicsApplication(bool=true);
		virtual ~GraphicsApplication();

        virtual void Draw()
        {
            if(win->Width==0)return;    //如果窗口大小为0不显示
            if(win->Height==0)return;

            flow->Draw();               //调用流程绘制代码
            flow->ProcCurState();       //处理流程状态
        }

        virtual void Frame()
        {
            BaseApplication::Frame();

            Draw();
        }

		virtual void Run(){BaseApplication::Run();}

		virtual bool ToMinimize();																	//窗口最小化(全屏模式无效)
		virtual bool ToMaximize();																	//窗口最大化(全屏模式无效)
	};//GraphicsApplication
}//namespace hgl
#endif//HGL_GRAPHICS_APPLICATION_INCLUDE
