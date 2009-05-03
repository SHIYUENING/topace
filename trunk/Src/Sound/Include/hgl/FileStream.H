#ifndef HGL_FILESTREAM_INCLUDE
#define HGL_FILESTREAM_INCLUDE

#include<hgl/Stream.H>
namespace hgl
{
	enum FileOpenMode                   			///文件访问模式枚举
	{
		fomCreate		=0x01,         			///<创建一个文件,只写方式
		fomOpenRead     =0x02,         			///<打开一个文件,只读方式
		fomOpenWrite    =0x04,         			///<打开一个文件,只写方式
		fomOpenReadWrite=fomOpenRead|fomOpenWrite, ///<打开一个文件,可读可写

		fomRead			=fomOpenRead,
		fomWrite		=fomOpenWrite,
		fomReadWrite	=fomOpenReadWrite
	};

	/**
	* FileStream是一个针对文件的流式访问类，它从Stream类派生
	*/
	class FileStream:public Stream                                                                  ///文件流操作类
	{
		friend class PartFileStream;
	
		wchar_t *filename;
		void *fp;
		unsigned long result;

	protected:

		int64 GetPosition();
		void SetPosition(int64);

		int64 GetSize();
		void SetSize(int64);

		void InitPrivate();

	public: //方法

		FileStream();
		FileStream(void *);
		FileStream(const wchar_t *,FileOpenMode=fomOpenRead);
		~FileStream();

		bool Create(const wchar_t *);
		bool Open(const wchar_t *,FileOpenMode=fomOpenRead);
		void Close();

		int Read(void *,int);
		int Write(const void *,int);

		int64 Seek(int64,SeekOrigin=soBegin);
	};
}
//--------------------------------------------------------------------------------------------------
#endif//HGL_FILESTREAM_INCLUDE