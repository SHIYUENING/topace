#ifndef HGL_PART_STREAM_INCLUDE
#define HGL_PART_STREAM_INCLUDE

#include<hgl/Stream.H>
namespace hgl
{
	/**
	* PartStream是指定访问某个流中的某一部分，它从Stream派生
	*/
	class PartStream:public Stream																	///小块流
	{
		Stream *fs;

		int64 start_pos;
		int64 file_length;

		int64 cur_pos;

		bool only_read;
		                
	protected:

		int64 GetPosition();
		void SetPosition(int64);

		int64 GetSize();
		void SetSize(int64);

		int _Read(void *,int);
		int _Write(const void *,int);

	public:

		PartStream(Stream *,int64,int64,bool=true);
		~PartStream(){};
	};
}//namespace hgl
#endif//HGL_PART_STREAM_INCLUDE
