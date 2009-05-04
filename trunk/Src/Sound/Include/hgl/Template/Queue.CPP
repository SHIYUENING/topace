#ifndef HGL_QUEUE_CPP
#define HGL_QUEUE_CPP

#include<hgl/Queue.H>
namespace hgl
{
	/**
	* 本类构造函数
	* @param m 如果m的值不为0，则表示使用固定的队列大小。固定大小的队列会在一开始即分配好内存。
	*/
    template<typename T>
	Queue<T>::Queue(int m)
	{
		hglSetPropertyRead(Count,this,Queue<T>::GetCount);
		hglSetProperty(MaxCount,this,Queue<T>::GetMax,Queue<T>::SetMax);

        count=0;

        if(m)
        {
			max_count=m;

			items=(T *)hgl_malloc(max_count*sizeof(T));
        }
		else max_count=0;

		mem_count=max_count;
	}

    template<typename T>
    Queue<T>::~Queue()
    {
		if(count||max_count)hgl_free(items);
    }

    /**
    * 修改队列的最大值
    */
    template<typename T>
    void Queue<T>::SetMax(int m)
    {
		if(max_count||(!max_count&&count))
			items=(T *)hgl_realloc(items,m*sizeof(T));
		else
			items=(T *)hgl_malloc(m*sizeof(T));

		max_count=m;
		mem_count=m;

		if(count>=max_count)count=max_count-1;
    }

    /**
    * 清除队列中的所有数据
    */
    template<typename T>
    void Queue<T>::Clear()
    {
		if(max_count==0)
			if(count)
			{
				hgl_free(items);
				mem_count=0;
			}

		count=0;
    }

	/**
	* 访问队列中的一个数据，但不清除它
	* @param t 取出的数据保存地
	* @return 是否成功取出数据
    */
    template<typename T>
	bool Queue<T>::Peek(T &t)
	{
		if(count)
		{
        	t=items[0];
//			hgl_memcpy(&t,items,sizeof(T));
			return(true);
		}
		else
			return(false);
	}

	/**
	* 从队列中取出一个数据
	* @param t 取出的数据保存地
	* @return 是否成功取出数据
    */
    template<typename T>
	bool Queue<T>::Pop(T &t)
	{
        if(count)
		{
        	t=items[0];
//			hgl_memcpy(&t,items,sizeof(T));

            count--;

			if(max_count==0)
            {
				if(count==0)
				{
					hgl_free(items);

					mem_count=0;
				}
                else
                {
                    hgl_memcpy(items,items+1,count*sizeof(T));
//                    items=(T *)hgl_realloc(items,count*sizeof(T));
                }
			}
			else
			{
                hgl_memcpy(items,items+1,count*sizeof(T));
			}
			
			return(true);
		}
		else
			return(false);
	}

	/**
	* 向队列中放入一个数据
	* @param data 要放入的数据指针
	* @return true 放入数据成功
	* @return false 放入数据失败
    */
    template<typename T>
	bool Queue<T>::Push(T &data)
	{
		if(max_count)
		{
			if(count>=max_count)return(false);
		}
		else
		{
			if(count)
			{
				if(count+1>mem_count)
				{
					mem_count=count+1;

					items=(T *)hgl_realloc(items,mem_count*sizeof(T));
				}
			}
			else
			{
				items=(T *)hgl_malloc(sizeof(T));

				mem_count=1;
			}
		}

		items[count++]=data;
//		hgl_memcpy(items+count,&data,sizeof(T));
//		count++;

        return(true);
	}

	template<typename T>
	void Queue<T>::operator =(const Queue<T> &ori)
	{
		if(ori.count==0)return;

		Clear();

		max_count=ori.count;
		count=ori.count;

		if(max_count==0)
			mem_count=count;
		else
			mem_count=max_count;

		items=(T *)hgl_malloc(mem_count*sizeof(T));

		hgl_memcpy(items,ori.items,mem_count*sizeof(T));
	}
}

namespace hgl
{
	template<typename T>
	void QueueObject<T>::Clear()
	{
		int n=count;
		while(n--)
			delete items[n];

		Queue<T *>::Clear();
	}
}
#endif//HGL_QUEUE_CPP