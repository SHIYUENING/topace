#ifndef HGL_HTP_PART_LAYER_INCLUDE
#define HGL_HTP_PART_LAYER_INCLUDE

#include<hgl/HTPBaseLayer.H>
#include<hgl/RectScope.H>
namespace hgl
{
	class Texture2D;
	class TileLibrary;

	class HTPPartLayer:public HTPBaseLayer
	{
        friend class HTPPart;

		Texture2D *		tex;

        RectScope2i     tile_scope;
        RectScope2i     tex_scope;
        RectScope2i     view_scope;
		RectScope2i		clip_view_scope;

		int				off_left;
		int				off_top;

		float       	tex_left;
		float       	tex_top;
		float       	tex_width;
		float       	tex_height;

        void CreateTexture();
        void CompuTexCoord(const RectScope2i &);
        void Build();

    public:

        HTPPartLayer();
		HTPPartLayer(TileLibrary *,Stream *);
		~HTPPartLayer();

        void SetViewScope(const RectScope2i &);

        void Draw(float l,float t,float sw,float sh);
        void DrawRect(float l,float t,float r,float b)
            {Draw(l,t,(r-l)/float(view_scope.Width),(b-t)/float(view_scope.Height));}

        void Draw(float l,float t){Draw(l,t,1,1);}
    };//class HTPPartLayer
}//namespace hgl
#endif//HGL_HTP_PART_LAYER_INCLUDE

