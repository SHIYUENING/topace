#ifndef HGL_MOVIE_INCLUDE
#define HGL_MOVIE_INCLUDE

#include<hgl/Texture2D.H>
#include<hgl/AudioSource.H>
#include<hgl/AudioBuffer.H>
#include<hgl/EnumObject.H>
namespace hgl
{                                 
	/**
	* 影片类型枚举
	*/
	enum MovieType          ///影片类型枚举
	{
		mtNone=0,           ///<起始定义，未知类型

		mtAuto,             ///<自动识别

		mtAVI,              ///<AVI(.avi)

		mtTheora,           ///<Theora(.ogm .ogg .theora)

//		mtQuickTime,        ///<QuickTime(.mov)
//		mtReal,             ///<RealVideo(.rm .rmvb)

		//以下仅对有相应授权的用户提供
//		mtBink,             ///<Bink(*.bik)
//		mtCRI,				///<CRI Sofdec(*.sfd)

		mtEnd               ///<结束定义，未知类型
	};

	/**
	* 影片控制类,提供对于影片的基本控制行为<br>
	*/
	class Movie:public EnumObject                                                                   ///影片控制类
	{
		#include<hgl/Movie.Private.H>
		
	public:

		PropertyRead(Texture2D *,	MovieTexture,		movie_texture);								///<影片用贴图
		PropertyRead(AudioSource *,	MovieAudioSource,	movie_audio_source);						///<影片用音源

	public:

		Movie();
		Movie(const wchar_t *,MovieType mt=mtAuto,TextureType=tt2D,GLuint format=GL_RGB8);
		virtual ~Movie();

		bool Load(const wchar_t *,MovieType mt=mtAuto,TextureType=tt2D,GLuint format=GL_RGB8);
		void Clear();

		void Restart();																				///<复位影片
		void Update();																				///<更新影片
		void Draw(float,float,float=1,float=1);														///<绘制影片
	};
}//namespace hgl
#endif//HGL_MOVIE_INCLUDE
