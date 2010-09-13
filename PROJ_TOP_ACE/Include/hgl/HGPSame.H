#ifndef HGL_HGPSame_INCLUDE
#define HGL_HGPSame_INCLUDE

#include<hgl/HGP.H>
namespace hgl
{
	/**
	* HGPSame是一种特殊应用的HGP，它仅用于加载数据时的特殊处理。<br>
	* 它自动将每一层图片与底层数据混合，用于还原转换工具转换前的图片。
	*/
	class HGPSame:public HGP
	{
		HGPLayer *CreateLayer();

	public:

		HGPSame();       
		HGPSame(TDFNode *,uint=0,uint=1);															///<本类构造函数
		HGPSame(Stream *,uint=0,uint=1);                                                            ///<本类构造函数
		HGPSame(const wchar_t *,uint=0,uint=1);                                                     ///<本类构造函数
		HGPSame(HAC *,const wchar_t *,uint=0,uint=1);                                               ///<本类构造函数
		~HGPSame();

		bool Load(TDFNode *,uint=0,uint=1);                                                 		///<从TDF中加载HGP
	};
	
	typedef ObjectBuffer<HGPSame> HGPSameBuffer;													///<HGPSame图片缓冲管理器
	typedef ObjectBufferFromHAC<HGPSame> HGPSameBufferHAC;											///<HGPSame图片缓冲管理器(从HAC名中取得文件)
}//namespace hgl
#endif//HGL_HGPSame_INCLUDE
