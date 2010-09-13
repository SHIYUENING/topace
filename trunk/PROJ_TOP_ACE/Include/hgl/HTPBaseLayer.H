#ifndef HGL_HTP_BASE_LAYER_INCLUDE
#define HGL_HTP_BASE_LAYER_INCLUDE

#include<hgl/Str.H>
#include<hgl/Color4f.H>
#include<hgl/BlendMode.H>

namespace hgl
{
	class Stream;
	class TileLibrary;

	class HTPBaseLayer
	{
    protected:

        String		name;

        int         left;
        int         top;
        int         width;
        int         height;
        int         color_num;          ///<色彩成份
		
		char		blendmode[4];

		int32      *data;

	protected:

		int GetLeft()	{return left;}
		int GetTop()	{return top;}
		int GetWidth()	{return width;}
		int GetHeight()	{return height;}

		void SetLeft(int n){left=n;}
		void SetTop(int n){top=n;}

		void InitPrivate();

	protected:

		TileLibrary *	lib;

		int			    tile_width;
		int			    tile_height;

		int        	    tile_cols;
		int        	    tile_rows;

    public:

    	PropertyString	Name;																		///<名称属性

        Color4f			Color;																		///<色彩
        bool			Visible;																	///<是否显示

		Property<int>	Left;																		///<层相对左边界坐标
		Property<int>	Top;																		///<层相对上边界坐标
		Property<int>	Width;																		///<层宽度
		Property<int>	Height;																		///<层高度

	public:

		BlendMode		Blend;																		///<混合方式

	public:
		
		HTPBaseLayer();
        HTPBaseLayer(TileLibrary *,Stream *);
		virtual ~HTPBaseLayer();
	};
}//namespace hgl
#endif//HGL_HTP_BASE_LAYER_INCLUDE
