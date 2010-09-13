#ifndef HGL_SCOPEBASE_INCLUDE
#define HGL_SCOPEBASE_INCLUDE

#include <hgl/Vertex2.h>
#include <hgl/Vertex3.h>

namespace hgl
{
	/**
	* 范围处理基类，这个类是所有范围处理类的基类。
	*
	* 范围处理类用于处理各种和范围相关的情况，比如一个点是否在范围内，两个范围的相对关系
	*/
	template<typename T>
	class ScopeBase2D                                                                               ///范围处理基类
	{
	public:

		virtual ~ScopeBase2D(){};                                                                   ///<本类析构函数

		virtual bool PointIn(T,T)const{return false;}                                         		///<一个点是否在其上
				bool PointIn(Vertex2<T> &v)const{return PointIn(v.x,v.y);}                    		///<一个点是否在其上
	};
}//namespace hgl
#endif//HGL_SCOPEBASE_INCLUDE
