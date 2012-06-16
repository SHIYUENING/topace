#ifndef CIRCLELIST_CPP
#define CIRCLELIST_CPP

#include<hgl/CircleList.H>
#include<malloc.h>
namespace hgl
{
    template<typename T>
	CircleList<T>::CircleList(int m)
	{
		hglSetProperty(MaxCount,this,CircleList<T>::GetMax,CircleList<T>::SetMax);
		
		max_count=m;
        rpos=0;
        wpos=0;

        if(max_count)
			item=(T *)hgl_malloc(max_count*sizeof(T));
        else item=NULL;
    }

    template<typename T>
    CircleList<T>::~CircleList()
    {
		if(max_count)
        {
            hgl_free(item);
            item=NULL;
            rpos=0;
            wpos=0;
        }
    }

    template<typename T>
    void CircleList<T>::SetMax(int n)
    {
		if(max_count)
        {
			if(n==max_count)return;

            if(n)
            {
				max_count=n;
				if(rpos>=max_count)rpos=0;
				if(wpos>=max_count)wpos=0;

				item=(T *)hgl_realloc(item,max_count*sizeof(T));
            }
            else Clear();
        }
        else if(n>0)
        {
			max_count=n;
            rpos=0;
            wpos=0;

			item=(T *)hgl_malloc(max_count*sizeof(T));
        }
    }

    template<typename T>
    void CircleList<T>::Clear()
    {
        if(item)
        {
			max_count=0;
            rpos=0;
            wpos=0;

            hgl_free(item);
            item=NULL;
        }
    }

    template<typename T>
    void CircleList<T>::SetItem(int n,T &t)
    {
		if(n>=max_count)return;

		item[n]=t;
    }

    template<typename T>
    T &CircleList<T>::GetItem(int n)
    {
		if(n>=max_count)return(*(T *)NULL);

        return(item[n]);
    }

    template<typename T>
    bool CircleList<T>::Push(T &t)
    {
		if(max_count==0)return(false);

		item[wpos++]=t;

		if(wpos>=max_count)wpos=0;
        	
        return(true);
    }

    template<typename T>
    bool CircleList<T>::Pop(T &t)
    {
		if(max_count==0)return(false);

		t=item[rpos++];
		
		if(rpos>=max_count)rpos=0;
        	
        return(true);
    }

    template<typename T>
    bool CircleList<T>::Peek(T &t)
    {
		if(max_count==0)return(false);

		t=item[rpos];
		
		return(true);
    }
}

#endif//CIRCLELIST_CPP᷀ň        return(true);
