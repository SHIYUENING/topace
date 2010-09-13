#ifndef HGL_OBJECT_LIST_CPP
#define HGL_OBJECT_LIST_CPP

#include<hgl/List.H>
namespace hgl
{
	template<typename T>
	ObjectList<T>::ObjectList()
	{
	}

	/**
	* 对象列表析构函数，会调用DeleteAll函数
	*/
	template<typename T>
	ObjectList<T>::~ObjectList()
	{
		DeleteAll();
	}

	/**
	* 生成一个对象，并返回它的指针
	*/
	template<typename T>
	T *ObjectList<T>::Append()
	{
		if(count==0)items=(T **)hgl_malloc(sizeof(T *));
			else items=(T **)hgl_realloc(items,(count+1)*sizeof(T *));

		return(items[count++]=new T);
	}

	/**
	* 在指定位置插入一个对象
	*/
	template<typename T>
	T *ObjectList<T>::Insert(int index)
	{
		if(index<0)index=0;

		if(index<count)
		{
			items=(T **)hgl_realloc(items,(count+1)*sizeof(T *));

			memmove32(items+index+1,items+index,count-index);

			count++;

			return(items[index]=new T);
		}
		else
			return(Append());
	}

	/**
	* 在指定位置插入一个对象
	*/
	template<typename T>
	void ObjectList<T>::Insert(int index,T *obj)
	{
		List<T *>::Insert(index,obj);
	}

	/**
	* 清除所有对象,作用和DeleteAll一样
	*/
	template<typename T>
	void ObjectList<T>::Clear()
	{
		DeleteAll();
	}

	/**
	* 将一个对象从列表中移除
	* @param index 对象在列表中的索引
	* @return 是否成功
	*/
	template<typename T>
	bool ObjectList<T>::Unlink(int index)
	{
		if(index>=0&&index<count)
		{
			count--;

			if(index<count)
				memcpy32(items+index,items+index+1,count-index);

			if(count==0)hgl_free(items);

			return(true);
		}
		else
        	return(false);
	}

	/**
	* 将一个对象从列表中移除
	* @param obj 要移除的对象
	* @return 是否成功
	*/
	template<typename T>
	bool ObjectList<T>::Unlink(T *obj)
	{
		int n=count;

		while(n--)
			if(items[n]==obj)
			{
				count--;

				if(n<count)
					memcpy32(items+n,items+n+1,count-n);

				if(count==0)hgl_free(items);

				return(true);
			}

		return(false);
	}

	/**
	* 将一批对象从列表中移除
	* @param obj 要移除的对象
	* @param n 要移除的对象个数
	*/
	template<typename T>
	void ObjectList<T>::Unlink(T **obj,int n)
	{
		while(n--)
		{
			int index=Find(*obj);

			obj++;

			if(index!=-1)
				Unlink(index);
		}
	}

	/**
	* 清空对象列表
	*/
	template<typename T>
	void ObjectList<T>::UnlinkAll()
	{
		if(count)
		{
			hgl_free(items);
			count=0;
		}
	}

	/**
	* 删除列表中的指定项
	*
	* 这个函数在删除指定对象时，附加使用delete方法
	* @param index 要删除的对象的索引值
	* @return 是否成功
	*/
	template<typename T>
	bool ObjectList<T>::Delete(int index)
	{
		if(index>=0&&index<count)
		{
			delete items[index];

			count--;

			if(index<count)
				memcpy32(items+index,items+index+1,count-index);

			if(count==0)hgl_free(items);

			return(true);
		}
		else
        	return(false);
	}

	/**
	* 删除列表中的指定项
	*
	* 这个函数在删除指定对象时，附加使用delete方法
	* @param obj 要删除的对象    
	* @return 是否成功
	*/
	template<typename T>
	bool ObjectList<T>::Delete(T *obj)
	{
		int n=count;

		while(n--)
		{
			if(items[n]==obj)
			{
				delete items[n];

				count--;
				
				if(n<count)
					memcpy32(items+n,items+n+1,count-n);

				if(count==0)hgl_free(items);
				
				return(true);
			}
		}

		return(false);
	}

	/**
	* 将一批对象从列表中删除
	* @param obj 要删除的对象
	* @param n 要删除的对象个数
	*/
	template<typename T>
	void ObjectList<T>::Delete(T **obj,int n)
	{
		while(n--)
		{
			int index=Find(*obj);

			obj++;

			if(index!=-1)
				Delete(index);
		}
	}
	/**
	* 删除整个列表中的所有对象
	*
	* 这个函数在删除每一个对象时，都会使用一次delete
	*/
	template<typename T>
	void ObjectList<T>::DeleteAll()
	{
		if(count)
		{
			int n=count;

			while(n--)
				delete items[n];

			hgl_free(items);
			count=0;
		}
	}
    
    template<typename T>
    void ObjectList<T>::SetCount(int new_count)
    {
        if(count==new_count)return;
        
        if(new_count<=0)
        {
            DeleteAll();
        }
        else
        {
            if(count)
            {
                if(new_count>count)
                {
					items=(T **)hgl_realloc(items,new_count*sizeof(T *));
                    
                    for(;count<new_count;count++)
                        items[count]=new T;
                }
                else
                {
                    while(count-->new_count)
                        delete items[count];
                        
                    items=(T **)hgl_realloc(items,new_count*sizeof(T *));
                }
            }
            else
            {
                items=(T **)hgl_malloc(new_count*sizeof(T *));
                
                while(new_count--)
                    items[count++]=new T;
            }
        }
	}

	template<typename T>
	int ObjectList<T>::CompFunc(void *data1,void *data2,uint)
	{
		return CallEvent(olcf,(*(T **)data1,*(T **)data2));
	}

	template<typename T>
	void ObjectList<T>::Sort(ObjectListCompFunc func)
	{
		olcf=func;

		COMPFUNC cf;

		SetEventCall(cf,this,ObjectList<T>::CompFunc);
		
    	HeapSort(items,count,sizeof(T *),cf);
	}
}//namespace hgl
#endif//HGL_OBJECT_LIST_CPP*/
