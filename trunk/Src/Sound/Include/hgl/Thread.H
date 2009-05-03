#ifndef HGL_THREAD_INCLUDE
#define HGL_THREAD_INCLUDE

#include<hgl/DataType.H>
#include<hgl/Mutex.H>
namespace hgl
{
	enum ThreadPriority     ///线程优先级枚举
	{
		tpIdle,             ///<线程只在系统空闲时执行。操作系统不会中断其它线程来执行带有tpIdle优先级的线程
		tpLowest,           ///<非常低
		tpLower,            ///<低
		tpNormal,           ///<标准
		tpHigher,           ///<高
		tpHighest,          ///<非常高
		tpTimeCritical      ///<实时，最高优先级
	};

	/**
	* 线程类.本类用于建立一个线程并管理它。<br>
	* Sleep和Exit函数是给线程内的程序使用的；而Start,Close,Pause,Rewind是给线程外的程序使用的。<br>
	* 使用本类只需要重载本类，并将代码写在Execute函数内即可。
	*/
	class Thread:public Mutex																		///线程类
	{
		friend void WaitThread(Thread **,int,uint32);
		friend void WaitMultiThread(Thread **,int,uint32);

	protected:

		unsigned long threadid;
		void *threadptr;

		ThreadPriority tp;

	protected:

		ThreadPriority GetPriority();
		void SetPriority(ThreadPriority);

		bool GetCur();
		bool GetRun();

		void Sleep(unsigned int);                                                                   ///<暂停指定时间
		void Exit(int=0);                                                                           ///<退出当前线程

	public: //属性

		Property<ThreadPriority> 	Priority;                                                       ///<线程优先级
		Property<bool>				CurThread;                                                      ///<是否是当前线程
		Property<bool> 				IsRun;															///<当前线程是否在运行

	public: //事件

		DefEvent(void,OnEnd,(Thread *));															///<线程运行结束事件

	public:

		Thread();
		virtual ~Thread();

		virtual void Execute()=0;                                                                   ///<线程的运行函数

		virtual void Start(ThreadPriority=tpNormal);	                                            ///<开始运行当前线程
		virtual void Close();                                                                       ///<关闭当前线程
		virtual void Pause();                                                                       ///<暂停执行当前线程
		virtual void Rewind();                                                                      ///<继续运行当前线程
		virtual void Wait(uint32 time=0);                                                 			///<等待当前线程
	};

	void WaitThread(Thread **,int,uint32 time=0);													///<等待多个线程中的一个完成
	void WaitMultiThread(Thread **,int,uint32 time=0);												///<等待多个线程全部完成
}

#endif//HGL_THREAD_INCLUDE