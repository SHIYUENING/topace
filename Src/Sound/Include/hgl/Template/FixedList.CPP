#ifndef HGL_FIXEDLIST_CPP
#define HGL_FIXEDLIST_CPP

#include<hgl/FixedList.H>
#include<string.h>

#ifdef _DEBUG
#include<hgl/loginfo.H>
#endif//_DEBUG
namespace hgl
{
	template<typename T>
	FixedList<T>::FixedList(int value)
	{
		hglSetPropertyRead(MaxCount,this,FixedList<T>::GetCount);

		count=value;
		pos=0;

		items=new T[count];

		hgl_memset(items,0,count*sizeof(T));
	}

	template<typename T>
	FixedList<T>::~FixedList()
	{
		if(count)
			delete[] items;
	}

	template<typename T>
	T &FixedList<T>::GetItem(int n)
	{
		#ifdef _DEBUG
		if(n<0||n>=count)
		{
			ErrorHint(L"访问列表，数据索引超出正常范围！");
			return(*(T *)NULL);
		}
		#endif//_DEBUG

		n+=pos;

		return(n<count?items[n]:items[n-count]);
	}

	template<typename T>
	void FixedList<T>::Push(const T &data)
	{
		items[pos++]=data;

		if(pos==count)pos=0;
	}

	template<typename T>
	void FixedList<T>::Push(const T &data,int n)
	{
		while(n--)
			Push(data);
	}

	template<typename T>
	void FixedList<T>::Clear()
	{
		hgl_memset(items,0,count*sizeof(T));
		pos=0;
	}

	template<typename T>
	void ObjectFixedList<T>::Push(const T &data)
	{
		if(items[pos])
			delete items[pos];

		FixedList<T *>::Push(data);
	}

	template<typename T>
	void ObjectFixedList<T>::Clear()
	{
		int n=count;
		while(n--)
			delete items[n];        //delete NULL;不会出错,所以不必检测

		delete[] items;

		items=new T[count];

		FixedList<T *>::Clear();
	}
}
#endif//HGL_FIXEDLIST_CPP