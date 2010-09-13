#ifndef HGL_POOL_INCLUDE
#define HGL_POOL_INCLUDE

#include<hgl/List.H>
#include<hgl/Queue.H>
#include<hgl/RWLock.H>
namespace hgl
{
	/**
	* 数据池模板用于管于两个队列，一个在用的，一个空闲的
	*/
	template<typename T> class Pool																	///数据池
	{
	protected:

		List<T> Active;
		Queue<T> Inactive;

		int count;
		int history_max;

	protected:

		virtual int GetActiveCount()	{return Active.Count;	}
		virtual int GetInactiveCount()	{return Inactive.Count;	}
		virtual int GetHistoryMaxCount(){return history_max;	}

		void InitPrivate();

	protected:

		virtual T Create()=0;																		///<创建数据
		virtual void Clear(T)=0;																	///<清除数据

	public:	//属性

		Property<int> ActiveCount;																	///<活动数据数量
		Property<int> InactiveCount;																///<非活动数据数量
		Property<int> HistoryMaxCount;																///<历史性最大数据数量

	public:

		Pool(){count=0;history_max=0;InitPrivate();}
		virtual ~Pool(){}

		virtual T		Acquire();																	///<申请一个数据
		virtual void	Append(T);																	///<添加一个数据
		virtual bool	Release(T);																	///<释放一个数据

		virtual void	ClearInactive();															///<清除所有空闲的
		virtual void	ClearAll();																	///<清除所有的

		virtual T operator[](int n){return Active[n];}
	};

	template<typename T> class MultiThreadPool:public Pool<T>										///多线程数据池
	{
		RWLock lock;

		int GetActiveCount()	{int r;lock.ReadLock();r=Active.Count;	lock.Unlock();return r;}
		int GetInactiveCount()	{int r;lock.ReadLock();r=Inactive.Count;lock.Unlock();return r;}
		int GetHistoryMaxCount(){int r;lock.ReadLock();r=history_max;	lock.Unlock();return r;}

	protected:

		virtual T Create()=0;																		///<创建数据
		virtual void Clear(T)=0;																	///<清除数据

	public:
		
#undef MT_ACCESS_FUNC
#define MT_ACCESS_FUNC(name)	virtual T *name(int &c)	\
		{	\
			if(!lock.name())	\
				return(NULL);	\
			\
			c=ActiveCount;	\
			return(Active.Data);	\
		}

		MT_ACCESS_FUNC(ReadLock);																	///<读列表锁定(用于访问整个列表)
		MT_ACCESS_FUNC(WriteLock);																	///<写列表锁定(用于访问整个列表)
		MT_ACCESS_FUNC(TryReadLock);																///<尝试读列表并锁定(用于访问整个列表)
		MT_ACCESS_FUNC(TryWriteLock);																///<尝试写列表并锁定(用于访问整个列表)
#undef MT_ACCESS_FUNC
		
		virtual bool Unlock()		{	return lock.Unlock();		}								///<解锁(用于访问整个列表)

		virtual T SafeAcquire()                                                                     ///<申请一个数据
		{
			T tmp;

			lock.WriteLock();
            tmp=Pool<T>::Acquire();
			lock.Unlock();

			return tmp;
		}

		virtual void SafeAppend(T tmp)																///<添加一个数据
		{
			lock.WriteLock();
			Pool<T>::Append(tmp);
			lock.Unlock();
		}

		virtual bool SafeRelease(T tmp)																///<释放一个数据
		{
			bool result;

			lock.WriteLock();
			result=Pool<T>::Release(tmp);
			lock.Unlock();

			return result;
		}

		virtual void SafeClearInactive()															///<清除所有空闲的
		{
			lock.WriteLock();
			Pool<T>::ClearInactive();
			lock.Unlock();
		}

		virtual void SafeClearAll()																	///<清除所有的
		{
			lock.WriteLock();
			Pool<T>::ClearAll();
			lock.Unlock();
		}
	};

	template<typename T> class ObjectPool:public Pool<T *>											///对象池
	{
		virtual T *Create()	{  	return(new T);	}

		virtual void Clear(T *obj)	{	if(obj)delete obj;	}

	public:

		virtual ~ObjectPool(){ClearAll();}
	};

	template<typename T> class MTObjectPool:public MultiThreadPool<T *>								///多线程对象池
	{
		virtual T *Create()	{  	return(new T);	}

		virtual void Clear(T *obj)	{	if(obj)delete obj;	}

	public:

		virtual ~MTObjectPool(){ClearAll();}
	};

	class MemBlockPool:public Pool<void *>															///内存块池
	{
    	int memblock_size;

		void *Create()			{  	return(new char[memblock_size]);	}

		void Clear(void *obj)	{	if(obj)delete[] obj;	}

	public:

		MemBlockPool(int size){SetSize(size);}
		virtual ~MemBlockPool(){ClearAll();}

		void SetSize(int size){memblock_size=size;}
		int GetSize(){return memblock_size;}
	};

	class MTMemBlockPool:public MultiThreadPool<void *>												///多线程内存块池
	{
		int memblock_size;

		void *Create()			{  	return(new char[memblock_size]);	}

		void Clear(void *obj)	{	if(obj)delete[] obj;	}

	public:

		MTMemBlockPool(int size){SetSize(size);}
		virtual ~MTMemBlockPool(){ClearAll();}

		void SetSize(int size){memblock_size=size;}
		int GetSize(){return memblock_size;}
	};
}//namespace hgl
#include<hgl/Template/Pool.CPP>
#endif//HGL_POOL_INCLUDE
