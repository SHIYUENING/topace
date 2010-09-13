#ifndef HGL_INDEX_DATA_CPP
#define HGL_INDEX_DATA_CPP

#include<hgl/IndexData.H>
#include<hgl/Stream.H>
#include<hgl/TDF.H>
namespace hgl
{
	template<typename F,typename T,typename DataStruct>
	_IndexData<F,T,DataStruct>::_IndexData()
	{
		OnSaveToStream=NULL;
		OnLoadFromStream=NULL;

		hglSetPropertyRead(Count,this,this_calss::GetCount);
	}

	/**
	* 查找数据是否存在
	* @param flag 数据标识
	* @return 数据所在索引，-1表示不存在
	*/
	template<typename F,typename T,typename DataStruct>
	int _IndexData<F,T,DataStruct>::Find(const F &flag)const
	{
		int left=0,right=data_list.Count-1;				//使用left,right而不使用min,max是为了让代码能够更好的阅读。
		int mid;

		while(left<=right)
		{
			if(data_list[left ]->flag==flag)return(left);
			if(data_list[right]->flag==flag)return(right);

			mid=(right+left)/2;

			if(data_list[mid]->flag==flag)return(mid);

			if(data_list[mid]->flag>flag)
			{
				left++;
				right=mid-1;
			}
			else
			{
				right--;
				left=mid+1;
			}
		}

		return(-1);
	}
	
	template<typename F,typename T,typename DataStruct>
	int _IndexData<F,T,DataStruct>::FindPos(const F &flag)const
	{
		int left=0,right=data_list.Count-1;
		int mid;

		while(left<=right)
		{
			if(flag<=data_list[left ]->flag)return(left);
			if(flag>=data_list[right]->flag)return(right+1);

			mid=(right+left)/2;

			if(data_list[mid]->flag==flag)return(mid);

			if(data_list[mid]->flag>flag)
			{
				if(data_list[mid-1]->flag<=flag)return(mid);

				left++;
				right=mid-1;
			}
			else
			{
				if(data_list[mid+1]->flag>=flag)return(mid+1);

				right--;
				left=mid+1;
			}
		}

		return(-1);
	}

	template<typename F,typename T,typename DataStruct>
	int _IndexData<F,T,DataStruct>::FindByData(const T &data)const
	{
		int n=data_list.Count;

		while(n--)
			if(data_list[n]->data==data)
				return(n);

		return -1;
	}

	/**
	* 添加一个数据
	* @param flag 数据标识
	* @param data 数据
    * @return 新创建好的数据结构
	*/
	template<typename F,typename T,typename DataStruct>
	DataStruct *_IndexData<F,T,DataStruct>::Add(const F &flag,const T &data)
	{
		DataStruct *ds=data_list.Insert(FindPos(flag));

		ds->flag	=flag;
		ds->data	=data;

		return(ds);
	}
	
	/**
	* 添加一个数据
	* @param flag 数据标识
	* @return 创建好的数据
	*/
	template<typename F,typename T,typename DataStruct>
	T &_IndexData<F,T,DataStruct>::Add(const F &flag)
	{
		DataStruct *ds=data_list.Insert(FindPos(flag));

		ds->flag	=flag;

		return ds->data;
	}

	/**
	* 添加一个数据
	* @param obj 数据
	*/
	template<typename F,typename T,typename DataStruct>
	void _IndexData<F,T,DataStruct>::Add(DataStruct *obj)
	{
		data_list.Insert(FindPos(obj->flag),obj);
	}
	
 	/**
	* 根据标识取得数据
	* @param flag 数据标识
	* @param data 数据存放处
	* @return 是否取得成功
	*/
	template<typename F,typename T,typename DataStruct>
	bool _IndexData<F,T,DataStruct>::Get(const F &flag,T &data)const
	{
		int index=Find(flag);

		if(index==-1)return(false);
		
		data=data_list[index]->data;

		return(true);
	}

	/**
	* 根据索引取得数据
	* @param index 索引
	* @param f 数据标识存放处
	* @param t 数据存放处
	* @return 是否取得成功
	*/
	template<typename F,typename T,typename DataStruct>
	bool _IndexData<F,T,DataStruct>::Get(int index,F &f,T &t) const
	{
		if(index<0||index>=data_list.Count)return(false);

		DataStruct *ds=data_list[index];

		f=ds->flag;
		t=ds->data;

		return(true);
	}

	/**
	* 设置数据,如果指定标识的数据不存在，则创建数据
	* @param flag 数据标识
	* @param data 数据
	*/
	template<typename F,typename T,typename DataStruct>
	void _IndexData<F,T,DataStruct>::Set(const F &flag,T &data)
	{
		int index=Find(flag);

		if(index!=-1)
			data_list[index]->data=data;
		else
			Add(flag,data);
	}
	
	/**
	* 将指定数据从列表中移除同时取得这个数据，但并不删除它
	* @param flag 数据标识
	* @param data 数据存放位处
	* @return 是否成功
	*/
	template<typename F,typename T,typename DataStruct>
	bool _IndexData<F,T,DataStruct>::Unlink(const F &flag,T &data)
	{
		int index=Find(flag);

		if(index==-1)return(false);

		data=data_list[index]->data;

		data_list.Unlink(index);

		return(true);
	}

	/**
	* 将指定数据从列表中移除同时取得这个数据，但并不删除它
	* @param data 数据
	* @return 是否成功
	*/
	template<typename F,typename T,typename DataStruct>
	bool _IndexData<F,T,DataStruct>::Unlink(const T &data)
	{
		int index=FindByData(data);

		if(index==-1)return(false);

		data_list.Unlink(index);

		return(true);
	}

	/**
	* 删除一个数据
	* @param flag 要删除的数据标识
	*/
	template<typename F,typename T,typename DataStruct>
	void _IndexData<F,T,DataStruct>::DeleteByIndex(const F &flag)
	{
		int result=Find(flag);

		if(result!=-1)
			data_list.Delete(result);
	}

	/**
	* 删除一个数据
	* @param tp 要删除的数据
	*/
	template<typename F,typename T,typename DataStruct>
	void _IndexData<F,T,DataStruct>::DeleteByData(T &tp)
	{
		int n=data_list.Count;

		while(n--)
			if(data_list[n]->data==tp)
			{
				data_list.Delete(n);
				return;
			}
	}


	/**
	* 删除一个数据
	* @param index 要删除的数据索引
	*/
	template<typename F,typename T,typename DataStruct>
	void _IndexData<F,T,DataStruct>::DeleteBySerial(int index)
	{
    	data_list.Delete(index);
	}

	/**
	* 更改数据,这个更改和Set不同,它要求指定标识的数据必须存在，则否就会更改失败
	* @param flag 数据标识
	* @param data 新的数据内容
	* @param return 是否更改成功
	*/
	template<typename F,typename T,typename DataStruct>
	bool _IndexData<F,T,DataStruct>::Change(const F &flag,T &data)
	{
		int result=Find(flag);

		if(result!=-1)
		{
			data_list[result]->data=data;

			return(true);
		}
		else
        	return(false);
	}

	/**
	* 清除所有数据
	*/
	template<typename F,typename T,typename DataStruct>
	void _IndexData<F,T,DataStruct>::Clear()
	{
		data_list.Clear();
	}
	
	/**
	* 保存整个列表到流中
	* @param str 要保存的流
	* @return 是否保存成功
	*/
	template<typename F,typename T,typename DataStruct>
	bool _IndexData<F,T,DataStruct>::SaveToStream(Stream *str)const
	{
		if(!str||OnSaveToStream==NULL)return(false);

		int n=data_list.Count;

		str->WriteInt32(n);
		for(int i=0;i<n;i++)
		{
			DataStruct *obj=data_list[i];

			if(OnSaveToStream(str,obj->flag,obj->data)==false)
            	return(false);
		}

		return(true);
	}

	/**
	* 从流中加载整个列表
	* @param str 要保存的流
	* @return 是否保存成功
	*/
	template<typename F,typename T,typename DataStruct>
	bool _IndexData<F,T,DataStruct>::LoadFromStream(Stream *str)
	{
		Clear();
		
		if(!str||OnLoadFromStream==NULL)return(false);

		int n;

		str->ReadInt32(n);

		if(n<0)return(false);
		
		for(int i=0;i<n;i++)
		{
			F flag;
			T data;

			if(OnLoadFromStream(str,flag,data))
				Add(flag,data);
			else
            	return(false);
		}

		return(true);
	}
	
	template<typename F,typename T,typename DataStruct>
	void _IndexData<F,T,DataStruct>::operator=(const _IndexData<F,T,DataStruct> &ftd)
	{
		Clear();

		data_list=ftd.data_list;
	}
}

namespace hgl
{
	/**
	* 添加一个数据,如果指定的标记存在，则返回已存在的数据
	* @param flag 标记
	* @return 该标记的数据指针
	*/                         
	template<typename F,typename T,typename DataStruct>
	T *_IndexObject<F,T,DataStruct>::Create(const F &flag)
	{                
		int index=Find(flag);

		if(index!=-1)
		{
			return data_list[index]->data;
		}
		else
		{
			T *result=new T;
			
			Add(flag,result);

			return result;
		}
	}

	/**
	* 设置数据,如果指定标识的数据不存在，则创建数据
	* @param flag 数据标识
	* @param data 数据
	*/
	template<typename F,typename T,typename DataStruct>
	void _IndexObject<F,T,DataStruct>::Set(const F &flag,T *data)
	{
		int index=Find(flag);

		if(index!=-1)
		{
			delete data_list[index]->data;

			data_list[index]->data=data;
		}
		else
			Add(flag,data);
	}

	/**
	* 删除一个数据
	* @param flag 要删除的数据标识
	*/
	template<typename F,typename T,typename DataStruct>
	void _IndexObject<F,T,DataStruct>::DeleteByIndex(const F &flag)
	{
		int index=Find(flag);

		if(index!=-1)
		{
			delete data_list[index]->data;
			
			data_list.Delete(index);
		}
	}

 	template<typename F,typename T,typename DataStruct>
	int _IndexObject<F,T,DataStruct>::FindByData(T *tp)const
	{
		int n=data_list.Count;

		while(n--)
			if(data_list[n]->data==tp)
				return(n);

		return(-1);
	}

	/**
	* 删除一个数据
	* @param tp 要删除的数据
	*/
	template<typename F,typename T,typename DataStruct>
	void _IndexObject<F,T,DataStruct>::DeleteByData(T *tp)
	{
		int index=FindByData(tp);

		if(index!=-1)
		{
			delete data_list[index]->data;

			data_list.Delete(index);
		}
	}

	/**
	* 删除一个数据
	* @param index 要删除的数据的序列号
	*/
	template<typename F,typename T,typename DataStruct>
	void _IndexObject<F,T,DataStruct>::DeleteBySerial(int index)
	{
		if(index>=0||index<data_list.Count)
		{
			delete data_list[index]->data;

			data_list.Delete(index);
		}
	}

	/**
	* 更改数据,这个更改和Set不同,它要求指定标识的数据必须存在，则否就会更改失败
	* @param flag 数据标识
	* @param data 新的数据内容
	* @param return 是否更改成功
	*/
	template<typename F,typename T,typename DataStruct>
	bool _IndexObject<F,T,DataStruct>::Change(const F &flag,T *data)
	{
		int index=Find(flag);

		if(index!=-1)
		{                              
			delete data_list[index]->data;
			
			data_list[index]->data=data;

			return(true);
		}
		else
        	return(false);
	}

	/**
	* 清除所有数据
	*/
	template<typename F,typename T,typename DataStruct>
	void _IndexObject<F,T,DataStruct>::Clear()
	{
		int n=data_list.Count;

		while(n--)
			delete data_list[n]->data;

		data_list.Clear();
	}
}
#endif//HGL_INDEX_DATA_CPP
