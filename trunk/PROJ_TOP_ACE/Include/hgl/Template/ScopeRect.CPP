#ifndef HGL_SCOPE_RECT_CPP
#define HGL_SCOPE_RECT_CPP

#include<hgl/RectScope.H>
#include<hgl/GUIObject.H>
namespace hgl
{
    template<typename T>
    void RectScope2<T>::InitPrivate()
    {
        hglSetProperty(Right,   this,RectScope2<T>::GetRight,   RectScope2<T>::SetRight  );
        hglSetProperty(Bottom,  this,RectScope2<T>::GetBottom,  RectScope2<T>::SetBottom );
    }

	/**
	* 本类构造函数
	*/
	template<typename T>
	RectScope2<T>::RectScope2()
	{
        InitPrivate();
		Left=0;
		Top=0;
		Width=0;
		Height=0;
	}

	/**
	* 本类构造函数
	* @param obj 要取其范围的GUI对象指针
	*/
	template<typename T>
	RectScope2<T>::RectScope2(GUIObject *obj)
	{
        InitPrivate();
    	operator=(obj);
	}

	/**
	* 本类构造函数
	* @param l 矩形最左边的坐标值
	* @param t 矩形最上边的坐标值
	* @param w 矩形的宽度
	* @param h 矩形的高度
	*/
	template<typename T>
	RectScope2<T>::RectScope2(T l,T t,T w,T h)
	{
        InitPrivate();
		Left=l;
		Top=t;
		Width=w;
		Height=h;
	}
	
	template<typename T>
	RectScope2<T>::RectScope2(const RectScope2<T> &rs)
	{
		InitPrivate();

		Left	=rs.Left;
		Top		=rs.Top;
		Width	=rs.Width;
		Height	=rs.Height;
	}

	/**
	* 设置数据
	* @param l 矩形最左边的坐标值
	* @param t 矩形最上边的坐标值
	* @param w 矩形的宽度
	* @param h 矩形的高度
	*/
	template<typename T>
	void RectScope2<T>::Set(T l,T t,T w,T h)
	{
		Left=l;
		Top=t;
		Width=w;
		Height=h;
	}

	/**
	* 求坐标点x,y,z是否在这个矩形内
	* @param x X坐标
	* @param y Y坐标
	* @return 点x,y,z是否在矩形范围内
	*/
	template<typename T>
	bool RectScope2<T>::PointIn(T x,T y) const
	{
		T pos;
		pos=x-Left;
		if(pos<0||pos>=Width)return(false);
		pos=y-Top;
		if(pos<0||pos>=Height)return(false);
		return(true);
	}

	template<typename T>
	void RectScope2<T>::operator = (GUIObject *obj)
	{
		Left=obj->Left;
		Top	=obj->Top;
		Width=obj->Width;
		Height=obj->Height;
	}
}//namespace hgl
#endif//HGL_SCOPE_RECT_CPP
