#ifndef HGL_BLEND_INCLUDE
#define HGL_BLEND_INCLUDE

#include<hgl/Platform/Platform.H>
namespace hgl
{
	/**
	* 混合模式
	*/
	enum_uint(BlendModeEnum)            	///混合模式枚举
	{
		bmNone      =0,                 ///<无,起始定义,无意义

		bmNormal,                       ///<一般模式

		bmSrc,                          ///<仅原图
		bmDst,                          ///<仅目标图

		bmAdditive,                     ///<饱合相加
		bmSubtractive,                  ///<饱合相减

		bmShadow,                       ///<原图阴影

		bmLight,                        ///<光线图

		bmNegativeColor,				///<反色							

		bmEnd                           ///<结束定义,无意义
	};

	/**
	* 混合模式类用于实现对各种混合效果的设置
	*/
	class BlendMode                                                                                 	///混合模式类
	{
	public: //属性

		unsigned int sfactor,dfactor;                                                               ///<OpenGL 1.0混合因子

		bool Enable;                                                                                ///<是否使用混合

	public:

		BlendMode();
		virtual ~BlendMode();

		void Setup();                                                                               ///<使用这个混合设置

		void Set(BlendModeEnum);                                                                    ///<设置混合模式
		void Set(unsigned int s,unsigned int d){sfactor=s;dfactor=d;Enable=true;}                   ///<混合模式

		void Set(const char *);																		///<设置混合模式(使用Photoshop简写字串)
		
		void operator = (BlendModeEnum bm){Set(bm);}
		bool operator == (BlendModeEnum);
		bool operator != (BlendModeEnum bm){return !(this->operator ==(bm));}
	};
}//namespace hgl
#endif//HGL_BLEND_INCLUDE
