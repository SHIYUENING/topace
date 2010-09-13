#ifndef HGL_WIN_OPENGL_APPLICATION_INCLUDE
#define HGL_WIN_OPENGL_APPLICATION_INCLUDE

#include<hgl/platform/OpenGLApplication.H>
namespace hgl
{
	class WinGLWindow;

	/**
	* 标准Windows OpenGL图形应用程序类
	*/
	class WinOpenGLApplication:public OpenGLApplication
	{
		WinGLWindow *glwin;

		double prev_time;

		bool InitVideoMode();
		bool InitOpenGLforWindows();

		void RunSync();
		void RunASync();
		void RunFast();

	public:

		AppRunMode  RunMode;                                                                        ///<运行模式

		bool        BackNotDraw;                                                                    ///<当程序位于后台不刷新画面
		bool        WaitActive;                                                                     ///<等待程序被切换至活动状态

	public:

		WinOpenGLApplication();
		~WinOpenGLApplication();

		bool Init(SystemInitInfo *);                                                                ///<初始化系统
		WinGLWindow * GetOpenGLWindow(){ return glwin; }


        void ProcMessage();                                                                         ///<处理Windows消息
        void SwapBuffer();                                                                          ///<交换Windows OpenGL缓冲区

        virtual void Frame()
        {
            OpenGLApplication::Frame();                     //调用OpenGL应用一帧刷新函数

            ProcMessage();                                  //处理Windows消息
        }

		virtual void Run()
        {
            do
            {
                UpdateTime();                               //更新时间

                ProcMessage();                              //处理Windows消息
                                                            //调用相应的运行处理函数
                if(RunMode==armASync)RunASync();else
                if(RunMode==armFast	)RunFast();else
                    RunSync();
            }
            while(flow->ObjectState!=FlowObject::fosExitGame);
        }

        //如不使用标准Run函数，请按如下格式编写自己的Run函数，或是自行调用UpdateTime/ProcMessage/Update/Draw/SwapBuffer函数
        /*void Run()
         {
            do
            {
                UpdateTime();       //更新时间
                ProcMessage();      //处理Windows消息
                Update();           //调用流程刷新函数
                Draw();             //调用流程绘制函数
                SwapBuffer();       //交换OpenGL缓冲区
            }flow->ObjectState!=FlowObject::fosExitGame);
         }*/
	};//class WinOpenGLApplication
}//namespace hgl
#endif//HGL_WIN_OPENGL_APPLICATION_INCLUDE
