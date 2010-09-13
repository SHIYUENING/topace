#ifndef HGL_THREAD_MUTEX_INCLUDE
#define HGL_THREAD_MUTEX_INCLUDE
namespace hgl
{
	/**
	* 排斥(线程)访问类可以判断数据在被一个代码段访问时，不能被另一代码段访问<br>
    * 注：此排斥仅在当前进程内有效
	*/
	class ThreadMutex                                                                               ///排斥访问类(仅当前进程)
	{
		void *ptr;

	public:

		ThreadMutex();                                                                              ///<本类构造函数
		virtual ~ThreadMutex();                                                                     ///<本类析构函数

		virtual void Lock();																		///<取得的控制权(如果对象处于排斥状态，则等待)
		virtual bool TryLock();																		///<尝试取得控制权
		virtual bool WaitLock(unsigned int=0);														///<等待并取得控制权
		virtual void Unlock();																		///<放弃控制权
	};//class Mutex
}//namespace hgl
#endif//HGL_THREAD_MUTEX_INCLUDE
