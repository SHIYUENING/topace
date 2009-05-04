#ifndef HGL_MUTEX_INCLUDE
#define HGL_MUTEX_INCLUDE

namespace hgl
{
	/**
	* 排斥访问类可以判断数据在被一个代码段访问时，不能被另一代码段访问
	*/
	class Mutex                                                                                     ///排斥访问类
	{
		void *ptr;

	public:

		Mutex();                                                                                    ///<本类构造函数
		virtual ~Mutex();                                                                           ///<本类析构函数

		virtual void Acquire();                                                                     ///<取得的控制权(如果对象处于排斥状态，则等待)
		virtual bool TryAcquire();                                                                  ///<尝试取得控制权
		virtual bool WaitAcquire(unsigned int=0);                                                   ///<等待并取得控制权
		virtual void Release();                                                                     ///<放弃控制权
	};
}
#endif//HGL_MUTEX_INCLUDE