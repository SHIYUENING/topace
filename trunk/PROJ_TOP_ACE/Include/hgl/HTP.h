#ifndef HGL_HTP_INCLUDE
#define HGL_HTP_INCLUDE

#include<hgl/List.H>
#include<hgl/HTPBase.H>
namespace hgl
{
    class TileLibrary;
    class HTPLayer;
    class HAC;

	class HTP:public HTPBase
	{
		TileLibrary *lib;

		List<HTPLayer *> htp_layer;

	private:

		void InitPrivate();

		HTPBaseLayer *CreateLayer(Stream *);

	public:

		HTP(){InitPrivate();}
		HTP(TileLibrary *tlb)                                   {InitPrivate();lib=tlb;}
		HTP(TileLibrary *tlb,Stream *str)                       {InitPrivate();Load(tlb,str);}
		HTP(TileLibrary *tlb,const wchar_t *filename)           {InitPrivate();Load(tlb,filename);}
		HTP(TileLibrary *tlb,HAC *hac,const wchar_t *filename)	{InitPrivate();Load(tlb,hac,filename);}

		bool Load(TileLibrary *tlb,Stream *str)						{lib=tlb;return HTPBase::Load(str);}
		bool Load(TileLibrary *tlb,const wchar_t *filename)			{lib=tlb;return HTPBase::Load(filename);}
		bool Load(TileLibrary *tlb,HAC *hac,const wchar_t *filename){lib=tlb;return HTPBase::Load(hac,filename);}

		HTPLayer *GetLayer(int n){return (HTPLayer *)HTPBase::GetLayer(n);}							///<根据编号取得层
		HTPLayer *GetLayer(const wchar_t *n){return (HTPLayer *)HTPBase::GetLayer(n);}				///<根据名称取得层

		void SetBlend(BlendMode &);                                                         		///<设置所有层的混合模式

        void Draw(float l,float t,float sw,float sh);
        void DrawRect(float l,float t,float r,float b)
            {Draw(l,t,(r-l)/float(width),(b-t)/float(height));}

        void Draw(float l,float t){Draw(l,t,1,1);}
    };
}//namespace hgl
#include<hgl/template/HTPBuffer.CPP>
#endif//HGL_HTP_INCLUDE

