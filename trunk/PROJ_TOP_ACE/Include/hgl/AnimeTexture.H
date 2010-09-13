#ifndef HGL_ANIME_TEXTURE_INCLUDE
#define HGL_ANIME_TEXTURE_INCLUDE

#include<hgl/HAC.H>
#include<hgl/TDF.H>
#include<hgl/Texture2D.H>
namespace hgl
{
	/**
	* 贴图动画<br>
	* 为动画的每一帧都创建一张贴图
	*/
	class AnimeTexture:public Texture2D
	{
	protected:
	
		struct Frame
		{
			uchar *data;
			uint color;
			uint time;

			Frame()	{data=0;time=0;}
			~Frame(){if(data)delete[] data;}                                                          
		};

		Frame *PicList;

		uint FrameTime;			//首帧时间
		uint TotalTime;			//总计时间
		int CurFrame;			//当前帧
		int FrameCount;			//帧数

	protected:
	
		void InitPrivate();

	public:
                                                                   
		bool Loop;				///<是否循环播放

		float Speed;			///<播放速度,默认为1

	public:

    	AnimeTexture();
		AnimeTexture(TDFNode *,uint=0,uint=1);
		AnimeTexture(Stream *,uint=0,uint=1);
		AnimeTexture(const wchar_t *,uint=0,uint=1);
		AnimeTexture(HAC *,const wchar_t *,uint=0,uint=1);
		virtual ~AnimeTexture(){Clear();};
		
		virtual bool Load(TDFNode *,uint=0,uint=1);
		virtual void Clear();

		virtual void Bind();
	};
}//namespace hgl
#endif//HGL_TEXTURE_ANIME_INCLUDE
