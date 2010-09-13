#ifndef HGL_MATRIX_INCLUDE
#define HGL_MATRIX_INCLUDE

#include<hgl/CompOperator.H>
namespace hgl
{
	/**
	 * OpenGL Matrix 数据类<br>
	 * 算法参照Mesa
	 */
	template<typename T> class Matrix
	{
	public:

		T m[16];

	public:

		Matrix();
		Matrix(	float,float,float,float,
				float,float,float,float,
				float,float,float,float,
				float,float,float,float);

		void LoadIdentity();                                                                        ///<加载缺省矩阵

		void Scale(T x,T y,T z);                                                        			///<缩放
		void Rotate(T angle,T x,T y,T z);                                           				///<旋转
		void Translate(T x,T y,T z);                                                    			///<移动

		void Scale(const float *v){Scale(v[0],v[1],v[2]);}
		void Rotate(float ang,const float *v){Rotate(ang,v[0],v[1],v[2]);}
		void Translate(const float *v){Translate(v[0],v[1],v[2]);}

		void Transpose();
		void Transpose(const Matrix<T> &);															///<

		bool CreateInvert(const Matrix<T> &);														///<产生当前矩阵的相反矩阵

	public:	//操作符重载
		
		int Comp(const Matrix<T> &)const;

		CompOperator(const Matrix<T> &,Comp);

		Matrix<T> &operator =(const Matrix<T> &);
		Matrix<T> &operator *=(const Matrix<T> &);

		Matrix<T>  operator *(const Matrix<T> &)const;

		operator T *(){return m;}
		operator const T *()const{return m;}
		const T operator[](int index)const{return m[index];}
	};

	typedef Matrix<float> Matrixf;
	typedef Matrix<double> Matrixd;
}//namespace hgl
#include<hgl/Template/Matrix.CPP>
#endif//HGL_MATRIX_INCLUDE
