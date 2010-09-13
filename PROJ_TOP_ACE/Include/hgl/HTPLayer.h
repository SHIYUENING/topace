#ifndef HGL_HTP_LAYER_INCLUDE
#define HGL_HTP_LAYER_INCLUDE

#include<hgl/HTPBaseLayer.H>
namespace hgl
{
	class Texture2D;
	class TileLibrary;

	class HTPLayer:public HTPBaseLayer
	{
		Texture2D *		tex;

		bool        	build;

		float       	tex_right;
		float       	tex_bottom;

	protected:

        void Build();

    public:

        HTPLayer();
        HTPLayer(TileLibrary *,Stream *);
        ~HTPLayer();

        /**
        * 取得贴图
        * @param r 贴图绘制用的右边界纹理坐标
        * @param b 贴图绘制用的底边界纹理坐标
        * @return 贴图指针
        */
        Texture2D *GetTexture(float &r,float &b){r=tex_right;b=tex_bottom;return tex;}

        void Draw(float l,float t,float sw,float sh);
        void DrawRect(float l,float t,float r,float b)
            {Draw(l,t,(r-l)/float(width),(b-t)/float(height));}

        void Draw(float l,float t){Draw(l,t,1,1);}
    };//class HTPLayer
}//namespace hgl
#endif//HGL_HTP_LAYER_INCLUDE

