#ifndef HGL_AUDIO_MANAGE_INCLUDE
#define HGL_AUDIO_MANAGE_INCLUDE

#include<hgl/List.H>
namespace hgl
{
	class AudioSource;
	class AudioBuffer;

	/**
	* 简单的音频播放管理，为一般应用的简单操作工具
	*/
	class AudioManage
	{
		struct AudioItem
		{
			AudioSource *source;
			AudioBuffer *buffer;

			AudioItem();
			~AudioItem();

			bool Check();
			void Play(const wchar_t *,float);
		};

		ObjectList<AudioItem> Items;

	public:

		/**
		* 本类构造函数
		* @param count 创建的音源数量,默认为8
		*/
		AudioManage(int count=8);	
		~AudioManage();

		/**
		* 播放一个音效
		* @param filename 文件名
		* @param gain 音量，默认为1
		*/
		bool Play(const wchar_t *filename,float gain=1);
	};
}//namespace hgl
#endif//HGL_AUDIO_MANAGE_INCLUDEE
