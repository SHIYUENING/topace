#ifndef HGL_ANIME_TEXTURE_CPP
#define HGL_ANIME_TEXTURE_CPP

#include<hgl/AnimeTexture.H>
#include<hgl/Other.H>
namespace hgl
{
	template<typename T>
	void AnimeTexture<T>::InitPrivate()
	{
		CurFrame=-1;

		Loop=true;
		Speed=1.0f;

		PicList=NULL;
	}

	template<typename T> AnimeTexture<T>::AnimeTexture(){  	InitPrivate();	}
	template<typename T> AnimeTexture<T>::AnimeTexture(TDFNode *tdf,				uint fmt,uint mip)	{  	InitPrivate();Load(tdf,fmt,mip);	}
	template<typename T> AnimeTexture<T>::AnimeTexture(Stream *str,					uint fmt,uint mip)	{  	InitPrivate();T::Load(str,fmt,mip);	}
	template<typename T> AnimeTexture<T>::AnimeTexture(			const wchar_t *fn,	uint fmt,uint mip)	{	InitPrivate();T::Load(fn,fmt,mip);		}
	template<typename T> AnimeTexture<T>::AnimeTexture(HAC *hac,const wchar_t *fn,	uint fmt,uint mip)	{ 	InitPrivate();T::Load(hac,fn,fmt,mip);	}

	template<typename T>
	bool AnimeTexture<T>::Load(TDFNode *tdf,uint fmt,uint mip)
	{
		uint format;

		tdf->ReadInt32(L"帧数",FrameCount);

		PicList=new AnimeTexture<T>::Frame[FrameCount];
		TotalTime=0;

		for(int i=0;i<FrameCount;i++)
		{
			String name;

			name.Sprintf(L"第%d帧",i);

			int w,h;
			int8 c;

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

			PicList[i].data=new uint8[w*h*c];

			tdfReadCompressData(node,L"象素数据",PicList[i].data,w*h*c);

			if(fmt==0)
				format=GLFormatByColorType[c];
			else
            	format=fmt;
		}

		Create(NULL,width,height,format,format);

		return(true);
	}

	template<typename T>
	void AnimeTexture<T>::Clear()
	{
		delete[] PicList;		//delete[] NULL 是不会报错的

		InitPrivate();
	}

	template<typename T>
	void AnimeTexture<T>::Bind()
	{
		if(!PicList)return;

		uint64 cur_time=GetTime();
		
		int cur_frame=CurFrame;

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

		if(CurFrame!=cur_frame)
			Change(PicList[CurFrame].data,GLFormatByColorType[PicList[CurFrame].color]);        	
	}
}
#endif//HGL_ANIME_TEXTURE_CPP
