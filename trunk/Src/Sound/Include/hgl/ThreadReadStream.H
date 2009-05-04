#ifndef HGL_THREAD_READ_STREAM_INCLUDE
#define HGL_THREAD_READ_STREAM_INCLUDE

#include<hgl/Thread.H>
namespace hgl
{
	class Stream;
	class Semaphore;

	/**
	* 多线程输入流
	*/
	class ThreadReadStream:public Thread															///多线程输入流
	{
		Semaphore *sem;

		Stream *str;

		int size;		//缓冲区长度
		int count;		//缓冲区个数

		uint8 **buffer;	//缓冲区
		int *length;	//缓冲区长度

		int64 read_index;		//当前该问的缓冲区索引
		int64 write_index;		//写索引

	protected:

		void Execute();

	public:

		/**
		* 本类构造函数
		* @param in 数据的原始输入流
		* @param size 每次读取的数据长度
		* @param count 缓冲区内保持的数据数量
		*/
		ThreadReadStream(Stream *in,int size,int count);
		~ThreadReadStream();

		/**
		* 取得一个数据块的指针
		* @param pointer 用于保存数据块指针的指针
		* @return 数据块长度
		*/
		int Get(void **pointer);																	///<取得数据

		void Restart();																				///<复位到最开始
	};
}
#endif//HGL_THREAD_READ_STREAM_INCLUDE
