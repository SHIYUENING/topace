#ifndef HGL_TEXTURE_ANIME_CPP
#define HGL_TEXTURE_ANIME_CPP

#include<hgl/TextureAnime.H>
#include<hgl/Other.H>
namespace hgl
{
	template<typename T>
	void TextureAnime<T>::InitPrivate()
	{
		CurFrame=-1;

		Loop=true;
		Speed=1.0f;

		PicList=NULL;
	}

	template<typename T> TextureAnime<T>::TextureAnime(){  	InitPrivate();	}
	template<typename T> TextureAnime<T>::TextureAnime(TDFNode *tdf,				uint fmt,int mip)	{  	InitPrivate();Load(tdf,fmt,mip);	}
	template<typename T> TextureAnime<T>::TextureAnime(Stream *str,					uint fmt,int mip)	{  	InitPrivate();T::Load(str,fmt,mip);	}
	template<typename T> TextureAnime<T>::TextureAnime(			const wchar_t *fn,	uint fmt,int mip)	{	InitPrivate();T::Load(fn,fmt,mip);		}
	template<typename T> TextureAnime<T>::TextureAnime(HAC *hac,const wchar_t *fn,	uint fmt,int mip)	{ 	InitPrivate();T::Load(hac,fn,fmt,mip);	}

	template<typename T>
	bool TextureAnime<T>::Load(TDFNode *tdf,uint fmt,int mip)
	{
		tdf->ReadInt32(L"帧数",FrameCount);

		PicList=new TextureAnime<T>::Frame[FrameCount];
		TotalTime=0;

		for(int i=0;i<FrameCount;i++)
		{
			String name;

			name.Sprintf(L"第%d帧",i);

			int w,h;
			int8 c;
			uint8 *data;
			uint format;

			TDFNode *node=tdf->FindNode(name);

			if(!node)
            	return(false);

			node->ReadUint32(L"时间",PicList[i].time);

			TotalTime+=PicList[i].time;

			node->ReadInt32(L"宽",  w );
			node->ReadInt32(L"高",  h);
			node->ReadInt8 (L"色彩",c );

			width=w;
			height=h;
			orign_color=(ColorType)c;

			data=new uint8[w*h*c];

			tdfReadCompressData(node,L"象素数据",data,w*h*c);

			if(fmt==0)
				format=GLFormatByColorType[c];
			else
            	format=fmt;

			PicList[i].pic=new T(data,w,h,GLFormatByColorType[c],format,mip);

			delete[] data;
		}

		return(true);
	}

	template<typename T>
	void TextureAnime<T>::Clear()
	{
		delete[] PicList;		//delete[] NULL 是不会报错的

		InitPrivate();
	}

	template<typename T>
	void TextureAnime<T>::Bind()
	{
		if(!PicList)return;

		uint64 cur_time=GetTime();

		if(CurFrame==-1||CurFrame>=FrameCount)
		{
			FrameTime=cur_time;

			CurFrame=0;
		}
		else
		{
			if(cur_time-FrameTime>PicList[CurFrame].time/Speed)
			{
				FrameTime=cur_time;

				CurFrame++;
				if(CurFrame>=FrameCount)
				{
					if(Loop)
						CurFrame=0;
					else
                    	CurFrame--;
				}
			}
		}

		PicList[CurFrame].pic->Bind();
	}

	template<typename T>
	void TextureAnime<T>::SetMinFilter(TextureFilter tf)
	{
		if(!PicList||FrameCount<=0)return;

		int n=FrameCount;

		while(n--)
			PicList[n].pic->MinFilter=tf;
	}

	template<typename T>
	void TextureAnime<T>::SetMagFilter(TextureFilter tf)
	{
		if(!PicList||FrameCount<=0)return;

		int n=FrameCount;

		while(n--)
			PicList[n].pic->MagFilter=tf;
	}

	template<typename T>
	void TextureAnime<T>::SetFilter(TextureFilter tf)
	{
		if(!PicList||FrameCount<=0)return;

		int n=FrameCount;

		while(n--)
			PicList[n].pic->Filter=tf;
	}

	template<typename T>
	void TextureAnime<T>::SetAni(int a)
	{
		if(!PicList||FrameCount<=0)return;

		int n=FrameCount;

		while(n--)
			PicList[n].pic->Anisotropy=a;
	}

	template<typename T>
	void TextureAnime<T>::Draw(float l,float t,float w,float h)
	{
		if(!PicList||CurFrame<0||CurFrame>=FrameCount)return;

		Bind();
		PicList[CurFrame].pic->Draw(l,t,w,h);
	}

	template<typename T>
	bool TextureAnime<T>::Draw(const Vertex2f *v)
	{
		if(!PicList||CurFrame<0||CurFrame>=FrameCount)return(false);

		Bind();
		return PicList[CurFrame].pic->Draw(v);
	}
}
#endif//HGL_TEXTURE_ANIME_CPP
