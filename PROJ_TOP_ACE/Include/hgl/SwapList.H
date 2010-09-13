#ifndef HGL_SWAP_LIST_INCLUDE
#define HGL_SWAP_LIST_INCLUDE

#include<hgl/List.H>
#include<hgl/ThreadMutex.H>
namespace hgl
{
	template<typename T,typename BList> class _MTSwapList
	{
	protected:

		ThreadMutex lock;

		BList list0,list1;
		BList *active,*use;

	public:

		_MTSwapList()
		{
			active	=&list0;
			use		=&list1;
		}

		virtual ~_MTSwapList(){}

		virtual void Swap()																			///<交换列表
		{
			lock.Lock();

			BList *tmp;

			tmp=active;
			active=use;
			use=tmp;

			lock.Unlock();
		}

		BList &GetList()																			///<取得非锁定列表
		{
			return *use;
		}
	};

	/**
	* 多线程数据交换列表<br>
	* 用于在多线程环境中交替处理数据
	*/
	template<typename T> class MTSwapList:public _MTSwapList<T,List<T> >
	{
	public:

		void Add(const T &data)
		{
			lock.Lock();
			active->Add(data);
			lock.Unlock();
		}

		void Add(T *data,int n)
		{
			lock.Lock();
			active->Add(data,n);
			lock.Unlock();
		}
	};

	/**
	* 多线程对象交换列表<br>
	* 用于在多线程环境中交替处理数据
	*/
	template<typename T> class MTSwapObjectList:public _MTSwapList<T,ObjectList<T> >
	{
	public:

		void Add(T *data)
		{
			lock.Lock();
			active->Add(data);
			lock.Unlock();
		}

		void Add(T **data,int n)
		{
			lock.Lock();
			active->Add(data,n);
			lock.Unlock();
		}
	};
}//namespace hgl
#endif//HGL_SWAP_LIST_INCLUDE
