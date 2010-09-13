#ifndef HGL_ONLYLIST_CPP
#define HGL_ONLYLIST_CPP

#include<hgl/OnlyList.H>
#include<hgl/Stream.H>
#include<malloc.h>
namespace hgl
{
	template<typename T>
    OnlyList<T>::OnlyList()
    {
		hglSetPropertyRead(Count,this,OnlyList<T>::GetCount);
    }

	/**
	* 查找数据是否存在
	* @param data 数据
	* @return 数据所在索引，-1表示不存在
	*/
	template<typename T>
	int OnlyList<T>::Find(const T &flag)
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

	template<typename T>
	int OnlyList<T>::FindPos(const T &flag)
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

	/**
	* 添加一个数据
	* @param data 数据
    * @return 位置
	*/
	template<typename T>
	int OnlyList<T>::Add(const T &data)
	{
		int pos;
		data_struct *ds;

		if(data_list.Count<=0)
		{
			ds=data_list.Append();

			pos=0;
		}
		else
		{
			pos=Find(data);

			if(pos!=-1)						//数据已存在
				return pos;

			pos=FindPos(data);

			ds=data_list.Insert(pos);
		}

		ds->flag	=data;

        return(pos);
	}

    /**
    * 清除所有数据
    */
    template<typename T>
    void OnlyList<T>::Clear()
    {
        data_list.Clear();
    }
}
#endif//HGL_ONLYLIST_CPP
