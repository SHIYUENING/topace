#ifndef HGL_HTP_BASE_INCLUDE
#define HGL_HTP_BASE_INCLUDE

#include<hgl/List.H>
#include<hgl/HTPBaseLayer.H>
namespace hgl
{
	class HAC;

	/**
	* HTPBase负责HTP的数据处理
	*/
	class HTPBase
	{
	private:

		ObjectList<HTPBaseLayer> layer;

	protected:

		int width,height;

	protected:

        void InitPrivate();

        int GetWidth(){return width;}
        int GetHeight(){return height;}
		int GetLayerNumber(){return layer.Count;}

		virtual HTPBaseLayer *CreateLayer(Stream *)=0;

    public:

        Property<int>           Width;
        Property<int>           Height;
        Property<int>           LayerNumber;

		void SetShow(bool);                                                                         ///<设置所有层显示属性
		void SetAlpha(float);                                                                       ///<设置所有层的Alpha值

        void SetColor3f(float,float,float);                                                         ///<设置所有层的颜色
		void SetColor4f(float,float,float,float);                                                   ///<设置所有层的颜色以及Alpha
		void SetColor4fv(float *v){SetColor4f(v[0],v[1],v[2],v[3]);}								///<设置所有层的颜色
		void SetColor(const Color4f &v){SetColor4f(v.r,v.g,v.b,v.a);}                      			///<设置所有层的颜色
		void SetColor4b(int r,int g,int b,int a)
			{SetColor4f(float(r)/255.0f,float(g)/255.0f,float(b)/255.0f,float(a)/255.0f);}          ///<设置所有层的颜色

		HTPBaseLayer *GetLayer(int n){return layer[n];}												///<根据编号取得层
		HTPBaseLayer *GetLayer(const wchar_t *);													///<根据名称取得层

	public:

		HTPBase(){InitPrivate();}
		virtual ~HTPBase(){};

		bool Load(Stream *);
		bool Load(const wchar_t *filename);
		bool Load(HAC *hac,const wchar_t *filename);
	};
}//namespace hgl
#endif//HGL_HTP_BASE_INCLUDE
