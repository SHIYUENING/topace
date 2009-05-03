#ifndef HGL_VERTEX_3_INCLUDE
#define HGL_VERTEX_3_INCLUDE

#include<hgl/Matrix.H>
namespace hgl
{
	/**
	* 3D����������ģ��
	*/
	template<typename T> class Vertex3                                                              ///XYZ 3D����������ģ��
	{
	public:

		T x,y,z;																					///<����ֵ

	public:

		Vertex3(){x=0,y=0,z=0;}							 								        	///<���๹�캯��
		Vertex3(T nx,T ny,T nz){x=nx,y=ny,z=nz;}								        			///<���๹�캯��

		void        Zero(){x=0,y=0,z=0;}													        ///<x,y,zȫ��Ϊ0
		void        One() {x=1,y=1,z=1;}                                                            ///<x,y,zȫ��Ϊ1

		void        Set(T nx,T ny,T nz){x=nx,y=ny,z=nz;}						        			///<��������ֵ

		void        Flip(T vx,T vy,T vz){FlipXY(vz);FlipXZ(vy);FlipYZ(vx);}		        			///<��Ӧָ����������ת
		void        Flip(const Vertex3<T> &v){Flip(v.x,v.y,v.z);}									        ///<��Ӧָ����������ת
		void        FlipXY(T v){z=v+(v-z);}												        	///<��Ӧָ��XYƽ������ת
		void        FlipXZ(T v){y=v+(v-y);}												        	///<��Ӧָ��XZƽ������ת
		void        FlipYZ(T v){x=v+(v-x);}												        	///<��Ӧָ��YZƽ������ת

		void        Move(T vx,T vy,T vz){x+=vx;y+=vy;z+=vz;}					        			///<�ƶ�����
		void        Scale(const Vertex3<T> &,double);                                               ///<���ָ���������Ŵ���
		void        Scale(const Vertex3<T> &,double,double,double);                                 ///<���ָ���������Ŵ���
		void        Scale(const Vertex3<T> &r,Vertex3<T> &v){Scale(r,v.x,v.y,v.z);}                 ///<���ָ���������Ŵ���
		void        Rotate(const Vertex3<T> &,double,double,double);	   							///<��ָ��������תָ���Ƕ�
		void 		RotateX(const Vertex3<T> &,double);												///<��X��������תָ���Ƕ�
		void 		RotateY(const Vertex3<T> &,double);                                             ///<��Y��������תָ���Ƕ�
		void 		RotateZ(const Vertex3<T> &,double);                                             ///<��Z��������תָ���Ƕ�

		T			Length()const{return (x * x) + (y * y) + (z * z);}								///<���㵱ǰ�������֮��ľ���
		T       	Length(T vx,T vy,T vz)const;                                             		///<���㵱ǰ����ָ����֮��ľ���
		T       	Length(const Vertex3<T> &v)const{return(Length(v.x,v.y,v.z));}					///<���㵱ǰ����ָ����֮��ľ���
		void        Normalize();

		Vertex3<T>	ResizeLength(const Vertex3<T> &,double)const;									///<�����������������ľ���
		Vertex3<T>	ToLength(const Vertex3<T> &,double)const;	 									///<�������������ľ������ָ������

		Vertex3<T>	To(const Vertex3<T> &,double)const;

		//����������
		Vertex3<T> &operator = (T *v){x=*v++;y=*v++;z=*v;return *this;}

		bool        operator == (const Vertex3<T> &)const;
		bool        operator != (const Vertex3<T> &)const;

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

		operator T *() const {return((T *)this);}													//ʹ�ñ������ֱ�ӵ���T *ʹ��
		operator const T *() const {return((const T *)this);}										//ʹ�ñ������ֱ�ӵ���const T *ʹ��
	};

	typedef Vertex3<float>	Vertex3f;
	typedef Vertex3<double>	Vertex3d;
	typedef Vertex3<int>	Vertex3i;
}

#include<hgl/Template/Vertex3.CPP>
#endif//HGL_VERTEX_3_INCLUDE