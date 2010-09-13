#ifndef HGL_VERTEX_3_INCLUDE
#define HGL_VERTEX_3_INCLUDE

#include<hgl/Matrix.H>
#include<hgl/CompOperator.H>
namespace hgl
{
	/**
	* 3D顶点坐标类模板
	*/
	template<typename T> class Vertex3                                                              ///XYZ 3D顶点坐标类模板
	{
	public:

		T x,y,z;																					///<坐标值

	public:

		Vertex3(){x=0,y=0,z=0;}							 								        	///<本类构造函数
		Vertex3(T nx,T ny,T nz){x=nx,y=ny,z=nz;}								        			///<本类构造函数

		void        Zero(){x=0,y=0,z=0;}													        ///<x,y,z全清为0
		void        One() {x=1,y=1,z=1;}                                                            ///<x,y,z全清为1

		void        Set(T nx,T ny,T nz){x=nx,y=ny,z=nz;}						        			///<设置坐标值

		void        Flip(T vx,T vy,T vz){FlipXY(vz);FlipXZ(vy);FlipYZ(vx);}		        			///<对应指定坐标做翻转
		void        Flip(const Vertex3<T> &v){Flip(v.x,v.y,v.z);}									        ///<对应指定坐标做翻转
		void        FlipXY(T v){z=v+(v-z);}												        	///<对应指定XY平面做翻转
		void        FlipXZ(T v){y=v+(v-y);}												        	///<对应指定XZ平面做翻转
		void        FlipYZ(T v){x=v+(v-x);}												        	///<对应指定YZ平面做翻转

		void        Move(T vx,T vy,T vz){x+=vx;y+=vy;z+=vz;}					        			///<移动坐标
		void        Scale(const Vertex3<T> &,double);                                               ///<相对指定点做缩放处理
		void        Scale(const Vertex3<T> &,double,double,double);                                 ///<相对指定点做缩放处理
		void        Scale(const Vertex3<T> &r,Vertex3<T> &v){Scale(r,v.x,v.y,v.z);}                 ///<相对指定点做缩放处理
		void        Rotate(const Vertex3<T> &,double,double,double);	   							///<绕指定坐标旋转指定角度
		void 		RotateX(const Vertex3<T> &,double);												///<绕X坐标轴旋转指定角度
		void 		RotateY(const Vertex3<T> &,double);                                             ///<绕Y坐标轴旋转指定角度
		void 		RotateZ(const Vertex3<T> &,double);                                             ///<绕Z坐标轴旋转指定角度

		T			Length()const{return (x * x) + (y * y) + (z * z);}								///<计算当前点与零点之间的距离
		T       	Length(T vx,T vy,T vz)const;                                             		///<计算当前点与指定点之间的距离
		T       	Length(const Vertex3<T> &v)const{return(Length(v.x,v.y,v.z));}					///<计算当前点与指定点之间的距离
		void        Normalize();
        T           InnerProduct(const Vertex3<T> &) const;

		Vertex3<T>	ResizeLength(const Vertex3<T> &,double)const;									///<调整这个方向上两点的距离
		Vertex3<T>	ToLength(const Vertex3<T> &,double)const;	 									///<按这个方向将两点的距离调到指定长度

		Vertex3<T>	To(const Vertex3<T> &,double)const;

		//操作符重载
		int Comp(const Vertex3<T> &)const;

		CompOperator(const Vertex3<T> &,Comp);

		Vertex3<T> &operator = (T *v){x=*v++;y=*v++;z=*v;return *this;}

		template<typename N> Vertex3<T> &operator = (const Vertex3<N> &v){x=v.x;y=v.y;return *this;}///<不同类型Vertex3之间的转换赋值

		Vertex3<T> &operator += (const Vertex3<T> &v){x+=v.x;y+=v.y;z+=v.z;return *this;}
		Vertex3<T> &operator -= (const Vertex3<T> &v){x-=v.x;y-=v.y;z-=v.z;return *this;}
		Vertex3<T> &operator *= (const Vertex3<T> &v){x*=v.x;y*=v.y;z*=v.z;return *this;}
		Vertex3<T> &operator /= (const Vertex3<T> &v){x/=v.x;y/=v.y;z/=v.z;return *this;}

		Vertex3<T> &operator *= (T v){x*=v;y*=v;z*=v;return *this;}
		Vertex3<T> &operator /= (T v){x/=v;y/=v;z/=v;return *this;}

		Vertex3<T>  operator + (const Vertex3<T> &v)const{return(Vertex3<T>(x+v.x,y+v.y,z+v.z));}
		Vertex3<T>  operator - (const Vertex3<T> &v)const{return(Vertex3<T>(x-v.x,y-v.y,z-v.z));}
		Vertex3<T>  operator * (const Vertex3<T> &v)const{return(Vertex3<T>(x*v.x,y*v.y,z*v.z));}
		Vertex3<T>  operator / (const Vertex3<T> &v)const{return(Vertex3<T>(x/v.x,y/v.y,z/v.z));}

		Vertex3<T>  operator * (T v)const{return(Vertex3<T>(x*v,y*v,z*v));}
		Vertex3<T>  operator / (T v)const{return(Vertex3<T>(x/v,y/v,z/v));}

		Vertex3<T> &operator *= (const Matrix<T> &);
		Vertex3<T>	operator * (const Matrix<T> &);

		Vertex3<T>  operator - () const {return(Vertex3<T>(-x,-y,-z));}

		operator T *() const {return((T *)this);}													//使得本类可以直接当做T *使用
		operator const T *() const {return((const T *)this);}										//使得本类可以直接当做const T *使用
	};

	typedef Vertex3<float>	Vertex3f;
	typedef Vertex3<double>	Vertex3d;
	typedef Vertex3<int>	Vertex3i;
}//namespace hgl
#include<hgl/Template/Vertex3.CPP>
#endif//HGL_VERTEX_3_INCLUDE
