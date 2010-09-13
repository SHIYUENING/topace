#ifndef HGL_CIRECLE_STREAM_INCLUDE
#define HGL_CIRECLE_STREAM_INCLUDE

#include<hgl/Stream.H>
#include<hgl/ThreadMutex.H>
#include<hgl/Int128.H>
namespace hgl
{
	/**
	* 环形数据流,用于随时被读或写的情况以及在多线程应用中同时被读与写的情况。
	*/
	class CircleStream:public Stream																///环形数据流
	{
		ThreadMutex lock;

		char *buf;
		int buf_size;
		int read_pos,write_pos;

		int _Read(void *data,int size){return Peek(data,size,true);}								///<从流中读取数据

		int _Write(const void *,int);																///<向流中写入数据

	public:

		CircleStream(int);                                                                          ///<本类构造函数
		virtual ~CircleStream();                                                                    ///<本类析构函数

	public:	//原生方法

		bool TryLock(){return lock.TryLock();}														///<尝试获取访问权
		void Lock(){lock.Lock();}																	///<获取访问权
		void Unlock(){lock.Unlock();}																///<释放访问权

		int GetReadSize();																			///<取得可读取数据长度
		int GetWriteSize();																			///<取得可写入数据长度

		int Peek(void *,int,bool=false);															///<访问数据
		int Peek(int size){return Peek(NULL,size,true);}											///<后移访问指针

		virtual void Clear();                                                                       ///<清空状态

	public:	//安全方法

		int64 SafeGetReadSize()
		{
			int result;

			lock.Lock();
			result=GetReadSize();
			lock.Unlock();

			return(result);
		}

		int64 SafeGetWriteSize()
		{
			int result;

			lock.Lock();
			result=GetWriteSize();
			lock.Unlock();

			return(result);
		}
	
		int SafeRead(void *data,int size)
		{
			int result;
			lock.Lock();
			result=Read(data,size);
			lock.Unlock();
			return result;
		}

		int SafeWrite(const void *data,int size)
		{
			int result;
			lock.Lock();
			result=Write(data,size);
			lock.Unlock();
			return result;
		}

		int SafePeek(void *data,int size,bool move=false)
		{
			int result;
			lock.Lock();
			result=Peek(data,size,move);
			lock.Unlock();
			return result;
		}

		int SafePeek(int size)
		{
			int result;
			lock.Lock();
			result=Peek(NULL,size,true);
			lock.Unlock();
			return result;
		}

		void SafeClear()
		{
			lock.Lock();
			Clear();
			lock.Unlock();
		}
	};
}//namespace hgl
#endif//HGL_CIRECLE_STREAM_INCLUDE
