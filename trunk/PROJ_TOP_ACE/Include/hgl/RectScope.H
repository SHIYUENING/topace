#ifndef HGL_RECTSCOPE_INCLUDE
#define HGL_RECTSCOPE_INCLUDE

#include <hgl/DataType.H>
#include <hgl/ScopeBase.H>
namespace hgl
{
	class GUIObject;

	/**
	* 这个类用于描述和处理一个矩形范围
	*/
	template<typename T>
	class RectScope2:public ScopeBase2D<T>                                                           ///矩形范围类
	{
		T GetBottom()const{return Height+Top;}
		T GetRight()const{return Width+Left;}
		void SetBottom(T v){Top=v-Height;}
		void SetRight(T v){Left=v-Width;}

        void InitPrivate();

	public:

		T Left;                                                                                 ///<矩形左边所在的坐标
		T Top;                                                                                  ///<矩形上边所在的坐标
		T Width;                                                                                ///<矩形的宽度
		T Height;                                                                               ///<矩形的高度

        Property<T> Right;
        Property<T> Bottom;

	public:

		RectScope2();
		RectScope2(T,T,T,T);
		RectScope2(GUIObject *);
		RectScope2(const RectScope2<T> &);

		void Clear()
		{
			Left=0;
			Top=0;
			Width=0;
			Height=0;
		}

		void Set(T,T,T,T);

		bool PointIn(T,T)const;

		void operator = (const RectScope2<T> &rs)
		{
			Left	=rs.Left;
			Top		=rs.Top;
			Width	=rs.Width;
			Height	=rs.Height;
		}

		void operator = (GUIObject *);

		bool operator == (const RectScope2<T> &rs) const
		{
			if((Left	==rs.Left	)
			 &&(Top		==rs.Top	)
			 &&(Width	==rs.Width	)
			 &&(Height	==rs.Height	))return(true);
			else
            	return(false);
		}
		
		bool operator != (const RectScope2<T> &rs) const
		{
        	return(!operator==(rs));
		}
	};

	typedef RectScope2<double>	RectScope2d;
	typedef RectScope2<float>	RectScope2f;
	typedef RectScope2<int>		RectScope2i;
}//namespace hgl
#include<hgl/Template/ScopeRect.CPP>
#endif//HGL_RECTSCOPE_INCLUDE
