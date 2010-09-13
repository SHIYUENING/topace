#ifndef HGL_MEM_MANAGE_INCLUDE
#define HGL_MEM_MANAGE_INCLUDE

#include<hgl/hgl.h>
namespace hgl
{
	/**
	* 内存管理器，用于管理内存的使用。
	*/
	class MemManage																					///内存管理
	{
	protected:

		uint32 mem_block_count;																		///<块数量

	protected:

		virtual void *AllocMemory(int)=0;
		virtual void *ReallocMemory(void *,int)=0;
		virtual bool FreeMemory(void *)=0;

	public:

		MemManage(){Init();}
		virtual ~MemManage(){}

		virtual void Init();
		virtual void FreeAll()=0;

				int GetBlockCount(){return mem_block_count;}                                        ///<已分配的内存块数

		virtual uint64 GetMemoryTotal()=0;															///<已分配内存总量
		virtual void PutLog()=0;																	///<输出日志

	public:

		void *malloc(int);
		void *malloc(int num,int size){return MemManage::malloc(num*size);}
		void *realloc(void *,int);
		void free(void *);

		virtual void *log_malloc(int size,const char *,const char *,const ulong){return this->malloc(size);}
		virtual void *log_realloc(void *ptr,int size,const char *,const char *,const ulong){return this->realloc(ptr,size);}
		virtual void  log_free(void *ptr,const char *,const char *,const ulong){return this->free(ptr);}

		void *log_malloc(int num,int size,const char *file,const char *func,const ulong line){return this->log_malloc(num*size,file,func,line);}
	};

	MemManage *CreateCMemManage();																	///<创建一个使用C内存函数的内存管理器
//	MemManage *CreateFixedMemManage(int);                                                           ///<创建一个定长数据块的内存管理器
//	MemManage *CreateBitmapMemManage();																///<创建一个位图式内存管理器
}//namespace hgl
#endif//HGL_MEM_MANAGE_INCLUDE
