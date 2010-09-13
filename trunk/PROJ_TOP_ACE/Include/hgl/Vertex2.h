#ifndef HGL_VERTEX_2_INCLUDE
#define HGL_VERTEX_2_INCLUDE

#include<hgl/CompOperator.H>
namespace hgl
{
	/**
	* 2D顶点坐标类模板
	*/
	template<typename T> class Vertex2                                                              ///XY 2D顶点坐标类模板
	{
	public:

		T x,y;                                                                                  		///<坐标值

	public:

		Vertex2<T>(){x=0,y=0;}					  												    ///<本类构造函数
		Vertex2<T>(T nx,T ny){x=nx,y=ny;}  												    		///<本类构造函数

		void    Zero(){x=0,y=0;}															        ///<将x和y全清为0
		void    One(){x=1,y=1;}                                                                     ///<将x和y全清为1

		void    Set(T nx,T ny){x=nx,y=ny;}											        		///<设置坐标值为nx,ny

		void    Flip(T vx,T vy){FlipX(vy);FlipY(vx);}								        		///<对应vx,vy做翻转
		void    Flip(const Vertex2<T> &v){Flip(v.x,v.y);}											        ///<对应v做翻转
		void    FlipX(){y=-y;}                                                                      ///<对应X轴翻转
		void    FlipY(){x=-x;}                                                                      ///<对应Y轴翻转
		void    FlipX(T v){y=v-(y-v);} 													        	///<对应指定X轴做翻转
		void    FlipY(T v){x=v-(x-v);}													        	///<对应指定Y轴做翻转

		void    Scale(double,double,double);														///<相对某一点做缩放
		void    Scale(double,double,double,double);													///<相对某一点做缩放
		void    Scale(const Vertex2<T> &,double);													///<相对某一点做缩放
		void    Scale(const Vertex2<T> &,double,double);											///<相对某一点做指定比例的缩放
		void    Rotate(double,double,double);                                                       ///<绕指定坐标旋转指定角度
		void    Rotate(const Vertex2<T> &v,double ang){Rotate(v.x,v.y,ang);}						///<绕指定坐标旋转指定角度

		void    Move(T vx,T vy){x+=vx;y+=vy;}										        		///<移动
		void    Scale(const Vertex2<T> &v,const Vertex2<T> &l){Scale(v,l.x,l.y);}					///<相对某一点做指定比例的缩放

		T		Length()const{return (x * x) + (y * y);}											///<计算当前点与零点之间的距离
		T		Length(T vx,T vy)const;                                                          	///<计算当前点与指定点之间的距离
		T		Angle(T vx,T vy)const;                                                           	///<计算当前点与指定点之间的角度

		T		Length(const Vertex2<T> &v)const{return(Length(v.x,v.y));}							///<计算当前点与指定点之间的距离
		T		Angle(const Vertex2<T> &v)const{return(Angle(v.x,v.y));}							///<计算当前点与指定点之间的角度
		void    Normalize();

		Vertex2<T>	ResizeLength(const Vertex2<T> &,double)const;									///<调整这个方向上两点的距离
		Vertex2<T>	ToLength(const Vertex2<T> &,double)const;										///<按这个方向将两点的距离调到指定长度

		Vertex2<T>	To(const Vertex2<T> &,double)const;

		//操作符重载
		int Comp(const Vertex2<T> &)const;

		CompOperator(const Vertex2<T> &,Comp);

		Vertex2<T> &operator =  (const T *v){x=*v++;y=*v;return *this;}

		template<typename N> Vertex2<T> &operator = (const Vertex2<N> &v){x=v.x;y=v.y;return *this;}///<不同类型Vertex2之间的转换赋值

		Vertex2<T> &operator += (const Vertex2<T> &v){x+=v.x;y+=v.y;return *this;}
		Vertex2<T> &operator -= (const Vertex2<T> &v){x-=v.x;y-=v.y;return *this;}
		Vertex2<T> &operator *= (const Vertex2<T> &v){x*=v.x;y*=v.y;return *this;}
		Vertex2<T> &operator /= (const Vertex2<T> &v){x/=v.x;y/=v.y;return *this;}

		Vertex2<T> &operator *= (const T v){x*=v;y*=v;return *this;}
		Vertex2<T> &operator /= (const T v){x/=v;y/=v;return *this;}

		Vertex2<T>  operator + (const Vertex2<T> &v)const{return(Vertex2<T>(x+v.x,y+v.y));}
		Vertex2<T>  operator - (const Vertex2<T> &v)const{return(Vertex2<T>(x-v.x,y-v.y));}
		Vertex2<T>  operator * (const Vertex2<T> &v)const{return(Vertex2<T>(x*v.x,y*v.y));}
		Vertex2<T>  operator / (const Vertex2<T> &v){constreturn(Vertex2<T>(x/v.x,y/v.y));}

		Vertex2<T>  operator * (const T v)const{return(Vertex2<T>(x*v,y*v));}
		Vertex2<T>  operator / (const T v)const{return(Vertex2<T>(x/v,y/v));}

		Vertex2<T>  operator - () const {return(Vertex2<T>(-x,-y));}

		operator       T *() const {return((      T *)this);}						//使得本类可以直接当做T *使用
		operator const T *() const {return((const T *)this);}						//使得本类可以直接当做const T *使用
	};

	typedef Vertex2<float>	Vertex2f;
	typedef Vertex2<double>	Vertex2d;
	typedef Vertex2<int>	Vertex2i;
}//namespace hgl
#include<hgl/Template/Vertex2.CPP>
#endif//HGL_VERTEX_2_INCLUDE
