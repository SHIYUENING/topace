#ifndef HGL_FIXEDLIST_CPP
#define HGL_FIXEDLIST_CPP

#include<hgl/FixedList.H>
#include<hgl/Other.H>
#include<string.h>

#ifdef _DEBUG
#include<hgl/loginfo.H>
#endif//_DEBUG
namespace hgl
{
	template<typename T>
	void FixedList<T>::InitPrivate()
	{
		count=0;
		max_count=0;
		items=NULL;
		
		OnClear=NULL;

		hglSetPropertyRead(Data,this,FixedList<T>::GetData);
	}

	template<typename T>
	FixedList<T>::FixedList()
	{
		InitPrivate();
	}

	template<typename T>
	FixedList<T>::FixedList(int value)
	{
		InitPrivate();

		Create(value);
	}

	template<typename T>
	FixedList<T>::~FixedList()
	{
		SAFE_CLEAR_ARRAY(items);
	}

	template<typename T>
	void FixedList<T>::Create(int value)
	{
		SAFE_CLEAR_ARRAY(items);

		if(value>0)
		{
			max_count=value;

			items=new T[max_count];

			hgl_memset(items,0,max_count*sizeof(T));
		}
	}

	template<typename T>
	T &FixedList<T>::operator [](int n)
	{
		if(n<0||n>=count)
		{
			ErrorHint(L"FixedList<T>::operator[] 数据索引超出正常范围：index=%d,count=%d",n,count);
			return(*(T *)NULL);
		}

		return(items[n]);
	}

	template<typename T>
	bool FixedList<T>::Append(const T &data)
	{
		if(count>=max_count)
		{
			DebugLog(L"FixedList<T>::Append(data); 数据已满！");
			return(false);
		}

		items[count++]=data;

		return(true);
	}

	template<typename T>
	bool FixedList<T>::Append(const T *data,int n)
	{
		if(count+n>max_count)
		{
			DebugLog(L"FixedList<T>::Append(data,n); 数据已满！");
			return(false);
		}

		hgl_memcpy(items+count,data,n*sizeof(T));
		count+=n;
		return(true);
	}

	template<typename T>
	int  FixedList<T>::Find(const T &data)
	{
		int n=count;
		T *p=items+n-1;

		while(n--)
		{
			if((*p--)==data)
				return n;
		}

		return -1;
	}

	template<typename T>
	bool FixedList<T>::Delete(int n)
	{
		if(n<0||n>=count)
		{
			ErrorHint(L"FixedList<T>::Delete 数据索引超出正常范围：index=%d,count=%d",n,count);
			return(false);
		}

		if(OnClear)
			OnClear(items[n]);

		count--;

		if(count)
		{
			if(n<count)					//将最后一个数据移到当前位置
				items[n]=items[count];
		}

		return(true);
	}

	template<typename T>
	void FixedList<T>::Delete(const T *data,int n)
	{
		while(n--)
		{
			int index=Find(*data);

			if(index!=-1)
				Delete(index);

			data++;
		}
	}

	template<typename T>
	void FixedList<T>::Clear()
	{
		if(OnClear)
		{
			int n=count;

			while(n--)
				OnClear(items[n]);
		}

		hgl_memset(items,0,max_count*sizeof(T));
		count=0;
	}
	
	template<typename T>
	T *FixedList<T>::CreateCopy(int &c)
	{
		c=count;
		T *copy=new T[count];
		hgl_memcpy(copy,items,count*sizeof(T));

		return copy;
	}
}//namespace hgl

namespace hgl
{
	template<typename T>
	bool FixedObjectList<T>::Delete(int n)
	{
		if(n<0||n>=count)
		{
			ErrorHint(L"ObjectFixedList<T>::Delete 数据索引超出正常范围：n=%d,count=%d",n,count);
			return(false);
		}

		delete items[n];

		count--;

		if(count)
		{
			if(n<count)					//将最后一个数据移到当前位置
				items[n]=items[count];
		}

		return(true);
	}

	template<typename T>
	void FixedObjectList<T>::Clear()
	{
		int n=count;

		while(n--)
			delete items[n];        //delete NULL;不会出错,所以不必检测

		FixedList<T *>::Clear();
	}
}//namespace hgl

namespace hgl
{
	template<typename T>
	bool MTFixedObjectList<T>::Delete(int n)
	{
		if(n<0||n>=count)
		{
			ErrorHint(L"MTObjectFixedList<T>::Delete 数据索引超出正常范围：n=%d,count=%d",n,count);
			return(false);
		}

		delete items[n];

		count--;

		if(count)
		{
			if(n<count)					//将最后一个数据移到当前位置
				items[n]=items[count];
		}

		return(true);
	}

	template<typename T>
	void MTFixedObjectList<T>::Clear()
	{
		int n=count;

		while(n--)
			delete items[n];        //delete NULL;不会出错,所以不必检测

		FixedList<T *>::Clear();
	}
}//namespace hgl
#endif//HGL_FIXEDLIST_CPP
