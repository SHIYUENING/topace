#ifndef HGL_AUDIO_BUFFER_INCLUDE
#define HGL_AUDIO_BUFFER_INCLUDE

#include<hgl/stream.h>
#include<hgl/HAC.H>
#include<hgl/ObjectBuffer.H>
namespace hgl
{
	/**
	* 音频文件格式
	*/
	enum AudioFileType
	{
		aftNone=0,			///<起始定义，如使用表示自动根据扩展名识别

		aftWAV,             ///<Wav音波文件
		aftOGG,             ///<Vorbis OGG文件

		aftEnd
	};

	typedef AudioFileType AFT;

	/**
	* AudioBuffer是一个简单的音频数据管理类
	*/
	class AudioBuffer                                                                               ///音频数据缓冲区类
	{
		bool ok;

		void InitPrivate();

	public:

		uint 	Index;
		double 	Time;                                                                          		///<缓冲区中音频数据可以播放的时间(秒)
		uint 	Size;																				///<缓冲区中音频数据的总字节数

	public:

		AudioBuffer(void *,int,AFT);                                                                ///<本类构造函数
		AudioBuffer(Stream *,AFT);                                                                  ///<本类构造函数
		AudioBuffer(const wchar_t *filename=0,AFT=aftNone);                                         ///<本类构造函数
		AudioBuffer(HAC *,const wchar_t *,AFT=aftNone);	   											///<本类构造函数
		virtual ~AudioBuffer();                                                                     ///<本类析构函数

		bool SetData(uint format, const void* data, uint size, uint freq );

		bool Load(void *,int,AFT);                                                        			///<从内存中加载音频数据
		bool Load(Stream *,AFT);                                                          			///<从流中加载音频数据
		bool Load(const wchar_t *,AFT=aftNone);                                                     ///<从文件中加载音频数据
		bool Load(HAC *,const wchar_t *,AFT=aftNone);												///<从HAC包的文件中加载音频数据

		void Clear();                                                                               ///<清除数据
	};

	typedef ObjectBuffer<AudioBuffer> 			AudioBufferBuffer;									///<AudioBuffer缓冲管理器
	typedef ObjectBufferFromHAC<AudioBuffer> 	AudioBufferHAC;										///<AudioBuffer缓冲管理器(从HAC名中取得文件)
}//namespace hgl
#endif//AUDIO_BUFFER_INCLUDE
