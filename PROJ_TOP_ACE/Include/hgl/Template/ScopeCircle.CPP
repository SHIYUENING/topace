#ifndef HGL_SCOPE_CIRCLE_CPP
#define HGL_SCOPE_CIRCLE_CPP

#include <hgl/CircleScope.h>

namespace hgl
{
	/**
	* 本类构造函数
	*/
	template<typename T>
	CircleScope2<T>::CircleScope2()
	{
		X=Y=0;
		R=0;

        hglSetProperty(Radius,this,CircleScope2<T>::GetRadius,CircleScope2<T>::SetRadius);
	}

	/**
	* 本类构造函数
	* @param x,y 圆心坐标
	* @param r 圆半径
	*/
	template<typename T>
	CircleScope2<T>::CircleScope2(T x,T y,T r)
	{
		X=x;
		Y=y;
		R=r;
	}

	/**
	* 求指定点是否在圆范围内
	* @param x,y 点坐标
	* @return 点是否在范围内
	*/
	template<typename T>
	bool CircleScope2<T>::PointIn(T x,T y) const
	{
		return(((x-X)*(x-X)+(y-Y)*(y-Y))<=distance);
	}

	template<typename T>
	const Vertex2<T> &CircleScope2<T>::RandPoint()const
	{

	}
}

namespace hgl
{
	/**
	* 本类构造函数
	*/
	template<typename T>
	EllipseScope2<T>::EllipseScope2()
	{
		X=Y=TR=VR=0;
	}

	/**
	* 本类构造函数
	* @param x,y 圆心坐标
	* @param r 圆半径
	*/
	template<typename T>
	EllipseScope2<T>::EllipseScope2(T x,T y,T r)
	{
		X=x;
		Y=y;
		TR=r;
		VR=r;
	}

	/**
	* 本类构造函数
	* @param x,y 圆心坐标
	* @param hr 横半径
	* @param vr 纵半径
	*/
	template<typename T>
	EllipseScope2<T>::EllipseScope2(T x,T y,T tr,T vr)
	{
		X=x;
		Y=y;
		TR=tr;
		VR=vr;
	}

	/**
	* 求指定点是否在圆范围内
	* @param x,y 点坐标
	* @return 点是否在范围内
	*/
	template<typename T>
	bool EllipseScope2<T>::PointIn(T x,T y) const
	{
		if(TR==VR)
		{
			return(((x-X)*(x-X)+(y-Y)*(y-Y))<=TR*TR);
		}
		else
		{
			double t=TR/VR;

			return(((x-X)*(x-X)/t/t+(y-Y)*(y-Y))<=VR*VR);
		}
	}
/*
	template<typename T>
	void EllipseScope2<T>::RandPoint(Vertex2f *)
	{
	}*/
}
#endif//HGL_SCOPE_CIRCLE_CPP

