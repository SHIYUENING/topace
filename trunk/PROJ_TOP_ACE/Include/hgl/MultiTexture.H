#ifndef HGL_MULTI_TEXTURE_INCLUDE
#define HGL_MULTI_TEXTURE_INCLUDE

#include<hgl/List.H>
#include<hgl/Texture.H>
namespace hgl
{
	/**
	* 多重贴图管理器
	*/
	class MultiTexture:public Texture																///多重贴图
	{
    	void SetAllWrap(unsigned int){}

	public:

		List<Texture *> Array;

	public:

		MultiTexture(){tex_type=ttMulti;}
		virtual ~MultiTexture(){};

		Texture *operator[](int n){return Array[n];}

		void Bind();
	};
}//namespace hgl
#endif//HGL_MULTI_TEXTURE_INCLUDE
