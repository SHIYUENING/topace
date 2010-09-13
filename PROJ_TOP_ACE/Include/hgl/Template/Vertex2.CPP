#ifndef HGL_VERTEX_2_CPP
#define HGL_VERTEX_2_CPP

#include<hgl/Vertex2.H>
#include<hgl/Other.H>
#include<string.h>

namespace hgl
{
    template<typename T>
	void Vertex2<T>::Scale(double vx,double vy,double scale)
	{
		x=vx+double(x-vx)*scale;
		y=vy+double(y-vy)*scale;
	}

	template<typename T>
	void Vertex2<T>::Scale(double vx,double vy,double sx,double sy)
	{
		x=vx+double(x-vx)*sx;
		y=vy+double(y-vy)*sy;
	}
	
	template<typename T>
	void Vertex2<T>::Scale(const Vertex2<T> &v,double scale)
	{
		x=v.x+double(x-v.x)*scale;
		y=v.y+double(y-v.y)*scale;
	}
	//--------------------------------------------------------------------------------------------------
    template<typename T>
	void Vertex2<T>::Scale(const Vertex2<T> &v,double sx,double sy)
	{
		x=v.x+double(x-v.x)*sx;
		y=v.y+double(y-v.y)*sy;
	}
	//--------------------------------------------------------------------------------------------------
    template<typename T>
	void Vertex2<T>::Rotate(double vx,double vy,double ang)
	{
		double as,ac;
		double nx,ny;

        fm_sincos(ang*M_PI/180.0f,&as,&ac);

		nx=vx+(double(x-vx)*ac-double(y-vy)*as);
		ny=vy+(double(x-vx)*as+double(y-vy)*ac);

		x=nx;y=ny;
	}
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	T Vertex2<T>::Length(T vx,T vy) const
	{
		T w=x-vx;
        T h=y-vy;

		return T(fm_sqrt(w*w+h*h));
    }
    //--------------------------------------------------------------------------------------------------
    template<typename T>
	T Vertex2<T>::Angle(T vx,T vy) const
	{
		if(vx==x)
		{
			if(vy>y)return(90);
			else return(270);
		}

		if(vy==y)
		{
			if(vx>x)return(0);
            	else return(180);
		}

		// asin 参数范围必须在 -1 到 +1 之间，否则会报错
		//

		double xx=vx-x;
		double yy=vy-y;

		double ang = fm_atan(yy/xx)/M_PI*180.0f;

		if(xx<0)
			return(ang+180);
		else
		{
			if(yy<0)
				return(ang+360);
			else
				return(ang);
		}
	}
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	Vertex2<T> Vertex2<T>::To(const Vertex2<T> &target,double pos)const
	{
		if(pos==0)return(*this);else
		if(pos==1)return(target);else
		{
			Vertex2<T> result;

			result.x=x+(target.x-x)*pos;
			result.y=y+(target.y-y)*pos;

			return(result);
		}
	}
	//--------------------------------------------------------------------------------------------------
    template<typename T>
	void Vertex2<T>::Normalize()
    {
        double size=fm_sqrt(x*x+y*y);

        if(size>0)
        {
            x/=size;
            y/=size;
        }

        x=0;y=0;
	}
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	Vertex2<T> Vertex2<T>::ResizeLength(const Vertex2<T> &target,double scale)const
	{
		Vertex2<T> result;

		result.x=target.x+(x-target.x)*scale;
		result.y=target.y+(y-target.y)*scale;

		return(result);
	}
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	Vertex2<T> Vertex2<T>::ToLength(const Vertex2<T> &target,double new_length)const
	{
		return ResizeLength(target,new_length/Length(target));
	}
	//--------------------------------------------------------------------------------------------------
	template<typename T>
	int Vertex2<T>::Comp(const Vertex2<T> &v)const
    {
        return memcmp(this,&v,sizeof(Vertex2<T>));
    }
}//namespace hgl
#endif//HGL_VERTEX_2_CPP
