#ifndef HGL_DIAMOND_INCLUDE
#define HGL_DIAMOND_INCLUDE

#include <hgl/ScopeBase.H>
namespace hgl
{
	/**
	* 菱形范围类，这个类用于描述和处理一个菱形范围
	*/
	template<typename T>
	class DiamondScope2:public ScopeBase2D<T>                                                       ///菱形范围类
	{
	public:

		T X;                                                                                    	///<菱形中心X坐标
		T Y;                                                                                    	///<菱形中心Y坐标
		T TSize;                                                                                	///<菱形中心距左右两点的距离
		T VSize;                                                                                	///<菱形中心距上下两点的距离

	public:

		DiamondScope2();
		DiamondScope2(T,T,T);
		DiamondScope2(T,T,T,T);

		bool PointIn(T,T) const;
	};

	typedef DiamondScope2<double>	DiamondScope2d;
	typedef DiamondScope2<float>	DiamondScope2f;
	typedef DiamondScope2<int>		DiamondScope2i;
}//namespace hgl
#include<hgl/Template/ScopeDiamond.CPP>
#endif//HGL_DIAMOND_INCLUDE
