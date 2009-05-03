#ifndef HGL_VERTEX_2_INCLUDE
#define HGL_VERTEX_2_INCLUDE

namespace hgl
{
	/**
	* 2D����������ģ��
	*/
	template<typename T> class Vertex2                                                              ///XY 2D����������ģ��
	{
	public:

		T x,y;                                                                                  		///<����ֵ

	public:

		Vertex2<T>(){x=0,y=0;}					  												    ///<���๹�캯��
		Vertex2<T>(T nx,T ny){x=nx,y=ny;}  												    		///<���๹�캯��

		void    Zero(){x=0,y=0;}															        ///<��x��yȫ��Ϊ0
		void    One(){x=1,y=1;}                                                                     ///<��x��yȫ��Ϊ1

		void    Set(T nx,T ny){x=nx,y=ny;}											        		///<��������ֵΪnx,ny

		void    Flip(T vx,T vy){FlipX(vy);FlipY(vx);}								        		///<��Ӧvx,vy����ת
		void    Flip(const Vertex2<T> &v){Flip(v.x,v.y);}											        ///<��Ӧv����ת
		void    FlipX(){y=-y;}                                                                      ///<��ӦX�ᷭת
		void    FlipY(){x=-x;}                                                                      ///<��ӦY�ᷭת
		void    FlipX(T v){y=v-(y-v);} 													        	///<��Ӧָ��X������ת
		void    FlipY(T v){x=v-(x-v);}													        	///<��Ӧָ��Y������ת

		void    Scale(double,double,double);														///<���ĳһ��������
		void    Scale(const Vertex2<T> &,double);													///<���ĳһ��������
		void    Scale(const Vertex2<T> &,double,double);											///<���ĳһ����ָ������������
		void    Rotate(double,double,double);                                                       ///<��ָ��������תָ���Ƕ�
		void    Rotate(const Vertex2<T> &v,double ang){Rotate(v.x,v.y,ang);}						///<��ָ��������תָ���Ƕ�

		void    Move(T vx,T vy){x+=vx;y+=vy;}										        		///<�ƶ�
		void    Scale(const Vertex2<T> &v,const Vertex2<T> &l){Scale(v,l.x,l.y);}					///<���ĳһ����ָ������������

		T		Length()const{return (x * x) + (y * y);}											///<���㵱ǰ�������֮��ľ���
		T		Length(T vx,T vy)const;                                                          	///<���㵱ǰ����ָ����֮��ľ���
		T		Angle(T vx,T vy)const;                                                           	///<���㵱ǰ����ָ����֮��ĽǶ�

		T		Length(const Vertex2<T> &v)const{return(Length(v.x,v.y));}							///<���㵱ǰ����ָ����֮��ľ���
		T		Angle(const Vertex2<T> &v)const{return(Angle(v.x,v.y));}							///<���㵱ǰ����ָ����֮��ĽǶ�
		void    Normalize();

		Vertex2<T>	ResizeLength(const Vertex2<T> &,double)const;									///<�����������������ľ���
		Vertex2<T>	ToLength(const Vertex2<T> &,double)const;										///<�������������ľ������ָ������

		Vertex2<T>	To(const Vertex2<T> &,double)const;

		//����������
		Vertex2<T> &operator =  (const T *v){x=*v++;y=*v;return *this;}

		bool        operator == (const Vertex2<T> &)const;
		bool        operator != (const Vertex2<T> &)const;

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

		operator       T *() const {return((      T *)this);}						//ʹ�ñ������ֱ�ӵ���T *ʹ��
		operator const T *() const {return((const T *)this);}						//ʹ�ñ������ֱ�ӵ���const T *ʹ��
	};

	typedef Vertex2<float>	Vertex2f;
	typedef Vertex2<double>	Vertex2d;
	typedef Vertex2<int>	Vertex2i;
}

#include<hgl/Template/Vertex2.CPP>
#endif//HGL_VERTEX_2_INCLUDE
