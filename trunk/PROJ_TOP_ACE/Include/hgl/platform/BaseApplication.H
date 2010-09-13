#ifndef HGL_BASE_APPLICATION_INCLUDE
#define HGL_BASE_APPLICATION_INCLUDE

#include<hgl/Str.H>
#include<hgl/FlowObject.H>
#include<hgl/FlowControl.H>
#include<hgl/platform/SystemInfo.H>
namespace hgl
{
	class SystemInitInfo;

	/**
	* 应用程序基类
	*/
	class BaseApplication																			///应用程序基类
	{		
	protected:

		SystemInitInfo *sii;

		double cur_time;

		bool active;

	protected:

		SystemInitInfo *GetSII		()		{return sii;}
		double			GetTime		()		{return cur_time;}

		void			UpdateTime	();
		void			CheckSystem	(bool);

		bool			GetActive	()		{return active;}
		void 			SetActive	(bool);

		void			ProcActiveObject(FlowObject *);

	public: //需要用户在启动游戏前设置的数据

		String						ProjectName;													///<游戏名称
		String						ProjectCode;                                                	///<游戏代码

	public: //属性

		SystemInfo      			si;                                                         	///<系统信息
		FlowControl *   			flow;                                                       	///<流程控制器

		Property<SystemInitInfo *>	SII;															///<系统初始化信息
		Property<double>			Time;															///<当前时间(秒)

		Property<bool>				Active;                                         				///<当前程序是否处于活动状态
		bool						WaitActive;                                        				///<是否等待活动状态,默认为false

	public:	//事件

		DefEvent(void,OnActive,(bool));																///<程序活动状态变更事件

	public:

		BaseApplication(bool=true);
		virtual ~BaseApplication();

		virtual bool Init(SystemInitInfo *)=0;														///<初始化当前应用程序

		virtual void SetStart(FlowObject *);														///<设定起始流程对象

        virtual void Update()                                                                       ///<刷新当前流程
        {
            flow->Update();             //流程刷新
            flow->ProcCurState();       //处理流程状态
        }

        virtual void Frame()                                                                        ///<更新一帧
        {
            UpdateTime();           //更新时间
            Update();               //处理刷新
        }

		virtual void Run()																		    ///<运行当前应用程序
        {
            do
            {
                Frame();                                                                            ///<调用一帧刷新
            }
		    while(flow->ObjectState!=FlowObject::fosExitGame);
        }
	};
}//namespace hgl
#endif//HGL_BASE_APPLICATION_INCLUDE;
