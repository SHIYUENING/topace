#ifndef HGL_HTP_VIEWER_INCLUDE
#define HGL_HTP_VIEWER_INCLUDE

#include<hgl/List.H>
#include<hgl/HTPBase.H>
#include<hgl/RectScope.H>
namespace hgl
{
    class TileLibrary;
    class HTPPartLayer;
	class HAC;

	/**
	* HTPPart是HTP文件的特殊应用方式，一般情况下用于超大图片显示。<br>
	* 它要求在一开始指定一个显示范围大小，在显示前再具体指定要显示的图片原始范围。
	*/
	class HTPPart:public HTPBase
	{
		TileLibrary *lib;

		List<HTPPartLayer *> htp_layer;

        RectScope2i view_scope;

	private:

		void InitPrivate();

		HTPBaseLayer *CreateLayer(Stream *);

	public:

		HTPPart(){InitPrivate();}
		HTPPart(TileLibrary *tlb)                                   {InitPrivate();lib=tlb;}
		HTPPart(TileLibrary *tlb,Stream *str)                       {InitPrivate();Load(tlb,str);}
		HTPPart(TileLibrary *tlb,const wchar_t *filename)           {InitPrivate();Load(tlb,filename);}
		HTPPart(TileLibrary *tlb,HAC *hac,const wchar_t *filename)  {InitPrivate();Load(tlb,hac,filename);}

		bool Load(TileLibrary *tlb,Stream *str)						{lib=tlb;return HTPBase::Load(str);}
		bool Load(TileLibrary *tlb,const wchar_t *filename)			{lib=tlb;return HTPBase::Load(filename);}
		bool Load(TileLibrary *tlb,HAC *hac,const wchar_t *filename){lib=tlb;return HTPBase::Load(hac,filename);}

		HTPPartLayer *	GetLayer(int n){return (HTPPartLayer *)HTPBase::GetLayer(n);}				///<根据编号取得层
		HTPPartLayer *	GetLayer(const wchar_t *n){return (HTPPartLayer *)HTPBase::GetLayer(n);}	///<根据名称取得层

		void            SetBlend    (BlendMode &);                                                  ///<设置所有层的混合模式

        RectScope2i &   GetViewScope(){return view_scope;}                                          ///<取得显示范围
        void            SetViewScope(const RectScope2i &);											///<设置显示范围
		void            SetViewScope(int l,int t,int w,int h){SetViewScope(RectScope2i(l,t,w,h));}  ///<设置显示范围

        void            Draw        (float l,float t,float sw,float sh);                            ///<显示当前图片并指定缩放值
        void            Draw        (float l,float t){Draw(l,t,1,1);}                               ///<显示当前图片
        void            DrawRect    (float l,float t,float w,float h)                               ///<显示当前图片并指定宽高
			{Draw(l,t,w/float(view_scope.Width),h/float(view_scope.Height));}
	};
}//namespace hgl
#endif//HGL_HTP_VIEWER_INCLUDE
