#ifndef HGL_VERTEX_3_CPP
#define HGL_VERTEX_3_CPP

#include<hgl/DataType.H>
#include<hgl/Vertex3.H>
#include<hgl/Other.H>
#include<string.h>

namespace hgl
{
	template<typename T>
	void Vertex3<T>::Scale(const Vertex3<T> &v,double l)
	{
		x=v.x+(x-v.x)*l;
		y=v.y+(y-v.y)*l;
		z=v.z+(z-v.z)*l;
	}
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	void Vertex3<T>::Scale(const Vertex3<T> &v,double lx,double ly,double lz)
	{
		x=double(v.x)+double(x-v.x)*lx;
		y=double(v.y)+double(y-v.y)*ly;
		z=double(v.z)+double(z-v.z)*lz;
	}
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	void Vertex3<T>::Rotate(const Vertex3<T> &v,double ax,double ay,double az)
	{
		RotateX(v,ax);
		RotateY(v,ay);
		RotateZ(v,az);
    }
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	void Vertex3<T>::RotateX(const Vertex3<T> &v,double ang)
	{
		double as,ac;
		double nz,ny;

		fm_sincos(ang*M_PI/180.0f,&as,&ac);

		ny=v.y+(double(y-v.y)*ac-double(z-v.z)*as);
		nz=v.z+(double(y-v.y)*as+double(z-v.z)*ac);

		z=nz;y=ny;
	}

	template<typename T>
	void Vertex3<T>::RotateY(const Vertex3<T> &v,double ang)
	{
		double as,ac;
		double nx,nz;

		fm_sincos(ang*M_PI/180.0f,&as,&ac);

		nz=v.z+(double(z-v.z)*ac-double(x-v.x)*as);
		nx=v.x+(double(z-v.z)*as+double(x-v.x)*ac);

		x=nx;z=nz;
	}

	template<typename T>
	void Vertex3<T>::RotateZ(const Vertex3<T> &v,double ang)
	{
		double as,ac;
		double nx,ny;

		fm_sincos(ang*M_PI/180.0f,&as,&ac);

		nx=v.x+(double(x-v.x)*ac-double(y-v.y)*as);
		ny=v.y+(double(x-v.x)*as+double(y-v.y)*ac);

		x=nx;y=ny;
	}
    //--------------------------------------------------------------------------------------------------
    template<typename T>
	T Vertex3<T>::Length(T vx,T vy,T vz)const
    {
        vx-=x;
        vy-=y;
        vz-=z;

        return(fm_sqrt(vx*vx+vy*vy+vz*vz));
    }
    //--------------------------------------------------------------------------------------------------
    template<typename T>
	void Vertex3<T>::Normalize()
    {
        float size=(float)fm_sqrt(x*x+y*y+z*z);

        if (size>0.000f)
        {
            x=x/size;
            y=y/size;
            z=z/size;
        }
        else x=y=z=0;
    }
	//--------------------------------------------------------------------------------------------------
	template<typename T>
    T Vertex3<T>::InnerProduct(const Vertex3<T> &v) const
    {
	    return (x * v.x + y * v.y + z * v.z);
    }
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	Vertex3<T> Vertex3<T>::To(const Vertex3<T> &target,double pos) const
	{
		if(pos==0)return(*this);else
		if(pos==1)return(target);else
		{
			Vertex3<T> result;

			result.x=T(x+(target.x-x)*pos);
			result.y=T(y+(target.y-y)*pos);
			result.z=T(z+(target.z-z)*pos);

			return(result);
		}
	}
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	Vertex3<T> Vertex3<T>::ResizeLength(const Vertex3<T> &target,double scale) const
	{
		Vertex3<T> result;

		result.x=T(target.x+(x-target.x)*scale);
		result.y=T(target.y+(y-target.y)*scale);
		result.z=T(target.z+(z-target.z)*scale);

		return(result);
	}
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	Vertex3<T> Vertex3<T>::ToLength(const Vertex3<T> &target,double new_length) const
	{
		return ResizeLength(target,new_length/Length(target));
	}
    //--------------------------------------------------------------------------------------------------
	template<typename T>
	int Vertex3<T>::Comp(const Vertex3<T> &v)const
    {
        return memcmp(this,&v,sizeof(Vertex3<T>));
    }
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	Vertex3<T> &Vertex3<T>::operator *=(const Matrix<T> &m)
	{
		T _x=x, _y=y, _z=z;// ,w;

		x = m[0] * _x + m[4] * _y + m[8]  * _z + m[12];
		y = m[1] * _x + m[5] * _y + m[9]  * _z + m[13];
		z = m[2] * _x + m[6] * _y + m[10] * _z + m[14];
//		w = m[3] * _x + m[7] * _y + m[11] * _z + m[15];	//这个值永远等于1，所以不做处理

//		x/=w;
//		y/=w;
//		z/=w;

		return *this;
	}
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	Vertex3<T> Vertex3<T>::operator *(const Matrix<T> &m)
	{
		Vertex3<T> result;

		result.x = m[0] * _x + m[4] * _y + m[8]  * _z + m[12];
		result.y = m[1] * _x + m[5] * _y + m[9]  * _z + m[13];
		result.z = m[2] * _x + m[6] * _y + m[10] * _z + m[14];
//		result.w = m[3] * _x + m[7] * _y + m[11] * _z + m[15];	//这个值永远等于1，所以不做处理

//		result.x/=w;
//		result.y/=w;
//		result.z/=w;

		return result;
	}
}
#endif//HGL_VERTEX_3_CPP
