#ifndef HGL_SCOPE_DIAMOND_CPP
#define HGL_SCOPE_DIAMOND_CPP
#include<hgl/DiamondScope.H>
#include<hgl/Other.h>
namespace hgl
{
	/**
	* 本类构造函数
	*/
	template<typename T>
	DiamondScope2<T>::DiamondScope2()
	{
		X=0;
		Y=0;
		TSize=0;
		VSize=0;
	}
	/**
	* 本类构造函数
	* @param x,y 菱形中心的坐标
	* @param size 菱形中心距顶点的距离
	*/
	template<typename T>
	DiamondScope2<T>::DiamondScope2(T x,T y,T size)
	{
		X=x;
		Y=y;
		TSize=size;
		VSize=size;
	}
	/**
	* 本类构造函数
	* @param x,y 菱形中心的坐标
	* @param tsize 菱形中心距左右两个顶点的距离
	* @param vsize 菱形中心距上下两个顶点的距离
	*/
	template<typename T>
	DiamondScope2<T>::DiamondScope2(T x,T y,T tsize,T vsize)
	{
		X=x;
		Y=y;
		TSize=tsize;
		VSize=vsize;
	}
	/**
	* 求一个点是否在菱形范围内
	* @param x,y 点的坐标
	* @return 指定点是否在菱形范围内
	*/
	template<typename T>
	bool DiamondScope2<T>::PointIn(T x,T y) const
	{
		return(((x-X)/(TSize/VSize)+(y-Y))<VSize);
	}
/*
	template<typename T>
	void DiamondScope2<T>::RandPoint(Vertex2f *v)
	{
		int temp=FastRand()%int(VSize);
		v->x=(VSize-temp)*(TSize/VSize);
		v->y=temp;
		v->x*=(FastRand()%2)?1:-1;
		v->y*=(FastRand()%2)?1:-1;
		v->x+=X;
		v->y+=Y;
	}*/
}
#endif//HGL_SCOPE_DIAMOND_CPP

