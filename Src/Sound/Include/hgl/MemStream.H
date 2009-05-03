#ifndef HGL_MEMORYSTREAM_INCLUDE
#define HGL_MEMORYSTREAM_INCLUDE

#include<hgl/Stream.H>
namespace hgl
{
	/**
	* MemoryStream是一个在动态内存中存取其数据的流，它从Stream类派生。
	*/
	class MemStream:public Stream                                                                ///内存流操作类
	{
		bool link;

		int64 size;
		int64 pos;

	protected:

		int64 GetPosition();
		void SetPosition(int64);

		int64 GetSize();
		void SetSize(int64);

		void InitPrivate();

	public:	//属性

		bool FixedSize;                                                              				///<是否固定长度

		void *Data;																					///<原始数据

	public:	//方法

		MemStream();
		MemStream(int64,bool=false);
		MemStream(void *,int64);
		~MemStream();

		bool Create(int64,bool=false);
		void Clear();

		void Link(void *,int64);

		int Read(void *,int);
		int Write(const void *,int);

		bool SaveToStream(Stream *);
		bool LoadFromStream(Stream *);

		bool SaveToFile(const wchar_t *);
		bool LoadFromFile(const wchar_t *);
	};
}
//--------------------------------------------------------------------------------------------------
#endif//HGL_MEMORYSTREAM_INCLUDE