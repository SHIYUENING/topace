#ifndef HGL_MEM_MANAGE_CPP
#define HGL_MEM_MANAGE_CPP

#include<hgl/MemManage.H>
#include<hgl/LogInfo.H>

namespace hgl
{
	template<typename T>
	void MemManageInterface<T>::Init()
	{
		if(ok)return;

		mmi.Init();

		mem_block_count=0;

		ok=true;
	}

	template<typename T>
	void *MemManageInterface<T>::malloc(int size)
	{
		if(!ok)Init();

		if(size<=0)
		{
			ErrorHint(L"分配了<%d>个字节的内存，可能是个错误！",size);
			return(NULL);
		}

		void *p=mmi.AllocMemory(size);

		if(!p)
		{
			ErrorHint(L"内存<%d>个字节的内存失败！",size);
			return(NULL);
		}

		mem_block_count++;

		return(p);
	}

	template<typename T>
	void *MemManageInterface<T>::realloc(void *mem_block,int new_size)
	{
		if(!ok)Init();

		if(!mem_block)
		{
			ErrorHint(L"调整内存块大小，旧的内存块为NULL，新长度为<%d>可能是个错误！",new_size);
			return(NULL);
		}

		if(new_size<=0)
		{
			ErrorHint(L"调整内存块<addr:%p>大小，新的容量为<%d>个字节的内存，可能是个错误！",mem_block,new_size);
			return(NULL);
		}

		return mmi.ReallocMemory(mem_block,new_size);
	}

	template<typename T>
	void MemManageInterface<T>::free(void *mem_block)
	{
		if(!ok)Init();

		if(!mem_block)
		{
        	//按C++标准,delete/delete[] NULL不会出错，所以不做处理
			return;
		}

		mem_block_count--;

		mmi.FreeMemory(mem_block);
	}
}
#endif//HGL_MEM_MANAGE_CPP
