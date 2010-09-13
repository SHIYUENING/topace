#ifndef HGL_HGP_INCLUDE
#define HGL_HGP_INCLUDE

#include<hgl/HGPLayer.H>
#include<hgl/Texture.H>
#include<hgl/ObjectBuffer.H>
#include<hgl/ResManage.H>
namespace hgl
{
	class HAC;

	/**
	* HGP图片管理类，它用于一般状态下2D图片的显示。不管显卡是否支持非2次幂贴图，它都能正常显示图片。但处理方式会有所不同。
	*/
	class HGP:public DataObject                                                                     ///HGP图片管理类
	{
		#include<hgl/hgp.Attrib.H>

	public: //属性

		Property<int>			Width;                                                              ///<图形宽度(只读)
		Property<int>			Height;                                                             ///<图形高度(只读)
		Property<int>			LayerNumber;                                                        ///<图片层数(只读)

		Property<TextureFilter>	Filter;                                                             ///<贴图过滤方式(只写)
		Property<int>			Anisotropy;                                                         ///<图片各向异性过滤级别(只写)

	public: 

		HGP();                                                                                      ///<本类构造函数
		HGP(TDFNode *,uint=0,uint=1);																///<本类构造函数
		HGP(Stream *,uint=0,uint=1);                                                                ///<本类构造函数
		HGP(const wchar_t *,uint=0,uint=1);                                                         ///<本类构造函数
		HGP(HAC *,const wchar_t *,uint=0,uint=1);                                                   ///<本类构造函数
		virtual ~HGP();                                                                             ///<本类析构函数

		virtual bool Load(TDFNode *,uint=0,uint=1);                                                 ///<从TDF中加载HGP
				bool Load(Stream *,uint=0,uint=1);                                                  ///<从流中加载HGP
				bool Load(const wchar_t *,uint=0,uint=1);                                           ///<加载一个HGP文件
				bool Load(HAC *,const wchar_t *,uint=0,uint=1);                                     ///<加载一个HGP文件

		virtual void Clear();                                                                       ///<清除HGP文件

	public:	//方法

		void Draw(double,double,double=1,double=1);                                                 ///<绘制图片(指定宽高缩放系数)
		bool Draw(const Vertex2f *);                                                                ///<绘制图片(指定四个顶点)
		void DrawRect(double l,double t,double w,double h)											///<绘制图片(指定范围)
			{Draw(l,t,w/double(hgp_width),h/double(hgp_height));}
			
		void Draw(const RectScope2f &rs){DrawRect(rs.Left,rs.Top,rs.Width,rs.Height);}				///<绘制图片(指定范围)

	public:	

		void DrawLayer(int,double,double,double=1,double=1);                                        ///<绘制某一层(指定宽高缩放系数)
		bool DrawLayer(int,const Vertex2f *);                                                       ///<绘制某一层(指定四个顶点)

		void DrawLayerRect(int n,double l,double t,double w,double h)								///<绘制某一层(指定范围)
			{DrawLayer(n,l,t,w/double(hgp_width),h/double(hgp_height));}

		void DrawLayer(int n,const RectScope2f &rs)													///<绘制某一层(指定范围)
			{DrawLayer(n,rs.Left,rs.Top,rs.Width,rs.Height);}

		void DrawTile(float,float,float,float,int=1,int=1);                                         ///<连续拼接绘制

	public:

		HGPLayer *CreateLayer(const wchar_t *);                                                   	///<创建一个新层
		HGPLayer *GetLayer(int);																	///<取图片指定层
		HGPLayer *GetLayer(const wchar_t *);														///<按名称查找层

	public:

		void SetShow(bool);                                                                         ///<设置所有层显示属性

		void SetBlend(BlendMode &);                                                         		///<设置所有层的混合模式
		void SetAlpha(float);                                                                       ///<设置所有层的Alpha值
        void SetColor3f(float,float,float);                                                         ///<设置所有层的颜色
		void SetColor4f(float,float,float,float);                                                   ///<设置所有层的颜色以及Alpha
		
		void SetColor4fv(float *v){SetColor4f(v[0],v[1],v[2],v[3]);}								///<设置所有层的颜色
		void SetColor(const Color4f &v){SetColor4f(v.r,v.g,v.b,v.a);}                      			///<设置所有层的颜色
		void SetColor4b(int r,int g,int b,int a)
			{SetColor4f(float(r)/255.0f,float(g)/255.0f,float(b)/255.0f,float(a)/255.0f);}          ///<设置所有层的颜色
	};

	typedef ObjectBuffer<HGP> HGPBuffer;															///<HGP图片缓冲管理器
	typedef ObjectBufferFromHAC<HGP> HGPBufferHAC;													///<HGP图片缓冲管理器(从HAC名中取得文件)

	typedef ResManageByName<HGP> HGPResManage;														///<HGP图片资源管理器
	typedef ResManageHAC<HGP> HGPResManageHAC;                                                      ///<HGP图片资源管理器(从HAC名中取得文件)

	HGP *CopyScreenToHGP(int,int,int,int,uint=GL_RGB8);                                             ///<根据当前屏幕图像生成一个HGP
	
	bool SaveBitmapToHGP(const wchar_t *,int,int,ColorType,void *,const wchar_t *ca=L"RLE",float=1);///<保存一个位图数据成HGP文件
	bool SaveScreenToHGP(const wchar_t *,int,int,int,int,const wchar_t *ca=L"RLE",float=1);			///<保存当前屏幕图像成HGP文件
	bool SaveScreenToHGP(const wchar_t *,int,int,int,int,int,int,const wchar_t *ca=L"RLE",float=1);	///<保存当前屏幕图像成HGP文件

	void SetSameColor(int);
	void SetClearSimplePixel(bool);																	///<设置色差容差

	bool ConvertMultiLayerImageToHGP	(const wchar_t *,const wchar_t *,ColorType=ctNone,const wchar_t *ca=L"RLE",float=1);				///<转换多层图片到HGP
	bool ConvertMonoLayerImageToHGP		(const wchar_t *,const wchar_t *,ColorType=ctNone,const wchar_t *ca=L"RLE",float=1);				///<转换单层图片到HGP
	bool ConvertSameLayerImageToHGP		(const wchar_t *,const wchar_t *,ColorType=ctNone,const wchar_t *ca=L"RLE",float=1);				///<转换多层图片到HGP(并自动裁剪掉每一层与底层相同内容的部分)
	bool ConvertSameLayerImageToHGPTest	(const wchar_t *,const wchar_t *,ColorType=ctNone,const wchar_t *ca=L"RLE",float=1);				///<转换多层图片到HGP(并自动裁剪掉每一层与底层相同内容的部分)
	bool ConvertPSDToMapHGP				(const wchar_t *,const wchar_t *,ColorType=ctNone,const wchar_t *ca=L"RLE",float=1);				///<转换PSD到地图用HGP

	void *LoadHGP(TDFNode *,uint &,int &,int &,int8 &);
	void *LoadHGP(Stream *,uint &,int &,int &,int8 &);
	void *LoadHGP(const wchar_t *,uint &,int &,int &,int8 &);
	void *LoadHGP(HAC *,const wchar_t *,uint &,int &,int &,int8 &);

	class Loader;

	Loader *ASyncLoadHGP(HGP **,HAC *,const wchar_t *);												///<异步加载HGP图片
	Loader *ASyncLoadHGPSame(HGP **,HAC *,const wchar_t *);											///<异步加载HGPSame图片
}//namespace hgl
#endif//HGL_HGP_INCLUDE

