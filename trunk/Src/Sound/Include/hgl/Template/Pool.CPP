#ifndef HGL_POOL_CPP
#define HGL_POOL_CPP

#include<hgl/DataType.H>
#include<hgl/pool.h>
namespace hgl
{
	template<typename T>
	void Pool<T>::InitPrivate()
	{
		hglSetPropertyRead(ActiveCount,		this,Pool<T>::GetActiveCount);
		hglSetPropertyRead(InactiveCount,	this,Pool<T>::GetInactiveCount);
		hglSetPropertyRead(HistoryMaxCount,	this,Pool<T>::GetHistoryMaxCount);
	}

	template<typename T>
	T Pool<T>::Acquire()
	{
		T result;

		if(!Inactive.Pop(result))
		{
			result=Create();

			count++;

			if(count>history_max)
				history_max=count;
		}

		Active.Add(result);

		return(result);
	}

	template<typename T>
	bool Pool<T>::Release(T value)
	{
		int index=Active.Find(value);

		if(index!=-1)
		{
			Active.Delete(index);

			Inactive.Push(value);

			return(true);
		}

		return(false);
	}

	template<typename T>
	void Pool<T>::ClearInactive()
	{
		T result;

		count-=Inactive.Count;
		
		while(Inactive.Pop(result))
			Clear(result);
	}

	template<typename T>
	void Pool<T>::ClearAll()
	{
		{					//不能直接调ClearInactive
			T result;

			count-=Inactive.Count;

			while(Inactive.Pop(result))
				Clear(result);
		}

		{
			int n=Active.Count;
			while(n--)
				Clear(Active[n]);

			Active.Clear();
		}

		count=0;
	}
}

#endif//HGL_POOL_CPP
