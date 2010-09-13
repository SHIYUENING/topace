#ifndef HGL_HGPLAYER_INCLUDE
#define HGL_HGPLAYER_INCLUDE

#include<hgl/OpenGL.H>
#include<hgl/Str.H>
#include<hgl/Compress.H>
#include<hgl/Color4f.H>
#include<hgl/BlendMode.H>
#include<hgl/RectScope.H>

namespace hgl
{
	class TDFNode;
	
	/**
	* HGPLayer是HGP图片中一个图层的控制类，可以用于控制这一层是否显示、整体透明度、混合模式等等
	*/
	class HGPLayer                                                                                  ///HGP图层类
	{
		#include<hgl/HGPLayer.Attrib.H>

	public:	//属性

		Property<LayerType>		Type;                                                               ///<层类型
		Property<ColorType>		OrignColor;                                                         ///<原始色彩类型(只读)

		String					Name;                                                       		///<图层名称
		bool					Visible;                                                    		///<本层是否显示

		BlendMode				Blend;                                                      		///<混合设置
		Color4f					Color;                                                      		///<颜色系数

		Property<int>			Left;                                                               ///<层相对左边界坐标
		Property<int>			Top;                                                                ///<层相对上边界坐标
		Property<int>			Width;                                                              ///<层宽度
		Property<int>			Height;                                                             ///<层高度

		Property<TextureFilter>	Filter;                                                             ///<贴图过滤方式设置虚拟变量
		Property<int>			Anisotropy;                                                         ///<各向异性过滤设置

	public:

		HGPLayer(int,int);
		virtual ~HGPLayer();

				void Load(TDFNode *,uint=0,uint=1);                                      			///<加载数据
				void Create(int,int,int,int,ColorType,uint,void *,uint=1);                          ///<创建层数据
		virtual void Clear()=0;                                                                     ///<清除数据

		virtual void Change(ColorType,void *)=0;													///<更改图像
		virtual void Change(int,int,int,int,ColorType,void *)=0;									///<更改图像

		virtual void Draw(double,double,double=1,double=1)=0;                                       ///<绘制当前层(指定宽高缩放系数)
		virtual bool Draw(const Vertex2f *)=0;                                                      ///<绘制当前层(指定四个顶点)

				void DrawRect(double l,double t,double w,double h)                                  ///<绘制当前层(指定范围)
						{Draw(l,t,w/double(Width),h/float(Height));}
				void Draw(const RectScope2f &rs){DrawRect(rs.Left,rs.Top,rs.Width,rs.Height);}			///<绘制当前层(指定范围)
	};
}//namespace hgl
#endif//HGL_HGPLAYER_INCLUDE
