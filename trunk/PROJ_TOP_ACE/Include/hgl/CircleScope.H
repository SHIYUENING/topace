#ifndef HGL_CIRCLESCOPE_INCLUDE
#define HGL_CIRCLESCOPE_INCLUDE

#include <hgl/Datatype.H>
#include <hgl/ScopeBase.H>
namespace hgl
{
	/**
	* 圆形范围处理类，这个类用于描述和处理一个圆形范围
	*/
	template<typename T>
	class CircleScope2:public ScopeBase2D<T>                                                        ///圆形范围类
	{
	protected:

		T radius;
		T distance;

		T GetRadius(){return radius;}
		void SetRadius(T r)
		{
			radius=r;
			distance=r*r;
		}

	public: //属性

		T X;                                                                                    	///<圆心X坐标
		T Y;                                                                                    	///<圆心Y坐标

        Property<T> Radius;

	public: //方法

		CircleScope2();                                                                             //本类构造函数
		CircleScope2(T,T,T);

		bool PointIn(T,T) const;
		
		const Vertex2<T> &RandPoint()const;															///<随机产生一个点
	};

	/**
	* 椭圆范围处理类
	*/
	template<typename T>
	class EllipseScope2:public ScopeBase2D<T>                                                       ///椭圆范围类
	{
	public: //属性

		T X;                                                                                    	///<圆心X坐标
		T Y;                                                                                    	///<圆心Y坐标
		T TR;                                                                                   	///<横半径
		T VR;                                                                                   	///<纵半径

	public: //方法

		EllipseScope2();                                                                            ///<本类构造函数
		EllipseScope2(T,T,T);
		EllipseScope2(T,T,T,T);

		bool PointIn(T,T) const;
	};

	typedef CircleScope2<double>	CircleScope2d;
	typedef CircleScope2<float>		CircleScope2f;
	typedef CircleScope2<int>		CircleScope2i;

	typedef EllipseScope2<double>	EllipseScope2d;
	typedef EllipseScope2<float>	EllipseScope2f;
	typedef EllipseScope2<int>		EllipseScope2i;
}//namespace hgl
#include<hgl/template/ScopeCircle.CPP>
#endif//CIRCLESCOPE_INCLUDE
