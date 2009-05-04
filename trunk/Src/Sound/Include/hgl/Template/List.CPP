#ifndef HGL_LIST_CPP
#define HGL_LIST_CPP

#include<hgl/List.H>
#include<hgl/Other.H>
#include<string.h>
//--------------------------------------------------------------------------------------------------
namespace hgl
{
	template<typename T>
	List<T>::List()
	{		
		hglSetProperty(Count,this,List<T>::GetCount,List<T>::SetCount);
		hglSetPropertyRead(Data,this,List<T>::GetData);

		count=0;
	}

	template<typename T>
	List<T>::~List()
	{
		Clear();
	}

	template<typename T>
	T &List<T>::Get(int index) const
	{
		#ifdef _DEBUG
			if(index<0||index>=count)
			{
				ErrorHint(L"访问列表，数据索引超出正常范围！\n<index=%d,count=%d>",index,count);
				return(*(T *)NULL);
			}
		#endif//_DEBUG

		return(items[index]);
	}

	template<typename T>
	void List<T>::Set(int index,const T &val)
	{
		#ifdef _DEBUG
			if(index<0||index>=count)
			{
            	PutError(L"List<T>::Set(%d,...),count=%d",index,count);
			}
			else
				hgl_memcpy(items+index,&val,sizeof(T));//items[index]=val;
		#else
			if(index>=0&&index<count)
				hgl_memcpy(items+index,&val,sizeof(T));//items[index]=val;
		#endif//_DEBUG
	}

	/**
	* 向列表中添加一个数据对象
	* @param data 要添加的数据对象
	* @return 这个数据的索引号
	*/
	template<typename T>
	int List<T>::Add(const T &data)
	{
		if(count==0)items=(T *)hgl_malloc(sizeof(T));
			else items=(T *)hgl_realloc(items,(count+1)*sizeof(T));

		hgl_memcpy(items+count,&data,sizeof(T));//items[count]=data;
		return(count++);
	}

	/**
	* 清除整个列表
	*/
	template<typename T>
	void List<T>::Clear()
	{
		if(count)
		{
			hgl_free(items);
			count=0;
		}
	}

	template<typename T>
	void List<T>::DeleteClear()
	{
		if(count)
		{
			while(count--)
				delete items[count];

			hgl_free(items);
			count=0;
		}
	}

	/**
	* 删除列表中的指定项
	* @param index 要删除的数据项的索引值
	* @return 是否成功
	*/
	template<typename T>
	bool List<T>::Delete(int index)
	{
		if(count>0&&index>=0&&index<count)
		{
			count--;

			if(index<count)
				hgl_memcpy(items+index,items+index+1,(count-index)*sizeof(T));

			if(count==0)hgl_free(items);

			return(true);
		}
		else
        	return(false);
	}

	/**
	* 交换列表中两个数据的位置
	* @param a 第一个数据的位置
	* @param b 第二个数据的位置
	*/
	template<typename T>
	void List<T>::Exchange(int a,int b)
	{
		T t;
		
//		t=items[a];

//		items[a]=items[b];
//		items[b]=t;

		hgl_memcpy(&t,items+a,sizeof(T));
		hgl_memcpy(items+a,items+b,sizeof(T));
		hgl_memcpy(items+b,&t,sizeof(T));
	}

	/**
	* 在列表的指定位置中插入一个数据
	* @param index 插入数据的位置
	* @param data 要插入的数据
	*/
	template<typename T>
	void List<T>::Insert(int index,const T &data)
	{
    	if(index<0)index=0;

		if(index<count)
		{
			if(count==0)items=(T *)hgl_malloc(sizeof(T));
				else items=(T *)hgl_realloc(items,(count+1)*sizeof(T));

			hgl_memmove(items+index+1,items+index,(count-index)*sizeof(T));
			
			hgl_memcpy(items+index,&data,sizeof(T));//items[index]=data;

			count++;
		}
		else
			Add(data);
	}

	/**
	* 移动列表中的某一项到新的位置
	* @param index 要移动的数据位置
	* @param newindex 新的位置
	*/
	template<typename T>
	void List<T>::Move(int index,int newindex)
	{
		if(index==newindex)return;
		if(index<=0||index>=count)return;
		if(newindex<0)newindex=0;
		if(newindex>=count)newindex=count-1;

		T t;

		hgl_memcpy(&t,items+index,sizeof(T));//t=items[index];

		if(index<newindex)hgl_memcpy(items+index      ,items+index+1  ,(newindex-index)*sizeof(T));
					else hgl_memmove(items+newindex+1 ,items+newindex ,(index-newindex)*sizeof(T));

		hgl_memcpy(items+newindex,&t,sizeof(T));//items[newindex]=t;
	}

	/**
	* 在列表中查找指定的数据项
	* @param data 要查找的数据项
	* @return 数据在列表中的位置
	*/
	template<typename T>
	int List<T>::Find(const T &data)
	{
		int n=count;

		while(n--)
//			if(items[n]==data)return(n);
        	if(hgl_memcmp(items+n,&data,sizeof(T))==0)
        		return(n);

		return(-1);
	}

	template<typename T>
	bool List<T>::Delete(const T &dat)
	{
		int index=Find(dat);

		if(index!=-1)
		{
			Delete(index);
			return(true);
		}
		else
        	return(false);
	}

	template<typename T>
	void List<T>::SetCount(int new_count)
	{
		if(count==new_count)return;

		if(new_count<=0)
		{
			Clear();
		}
		else
		{
			if(count)
				items=(T *)hgl_realloc(items,new_count*sizeof(T));
			else
				items=(T *)hgl_malloc(new_count*sizeof(T));

			count=new_count;
		}
	}

	template<typename T>
	int List<T>::CompFunc(void *data1,void *data2,uint)
	{
		return CallEvent(lcf,(*(T *)data1,*(T *)data2));
	}

	template<typename T>
	void List<T>::Sort(ListCompFunc func)
	{
		lcf=func;

		COMPFUNC cf;

		SetEventCall(cf,this,List<T>::CompFunc);
		
		HeapSort(items,count,sizeof(T),cf);
	}
}
#endif//HGL_LIST_CPP
