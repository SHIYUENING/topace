#ifndef HGL_VERTEX_2_CPP
#define HGL_VERTEX_2_CPP

#include<hgl/Vertex2.H>
#include<math.h>

namespace hgl
{
    template<typename T>
	void Vertex2<T>::Scale(double vx,double vy,double len)
	{
		x=vx+double(x-vx)*len;
		y=vy+double(y-vy)*len;
	}
	
	template<typename T>
	void Vertex2<T>::Scale(const Vertex2<T> &v,double len)
	{
		x=v.x+double(x-v.x)*len;
		y=v.y+double(y-v.y)*len;
	}
	//--------------------------------------------------------------------------------------------------
    template<typename T>
	void Vertex2<T>::Scale(const Vertex2<T> &v,double vx,double vy)
	{
		x=v.x+double(x-v.x)*vx;
		y=v.y+double(y-v.y)*vy;
	}
	//--------------------------------------------------------------------------------------------------
    template<typename T>
	void Vertex2<T>::Rotate(double vx,double vy,double ang)
	{
		double as=sin(ang*M_PI/180.0f);
		double ac=cos(ang*M_PI/180.0f);
		double nx,ny;

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

        return(sqrt(w*w+h*h));
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

		double ang = atan(yy/xx)/M_PI*180.0f;

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
        double size=sqrt(x*x+y*y);

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
	bool Vertex2<T>::operator == (const Vertex2<T> &v)const
    {
        if(x!=v.x)return(false);
        if(y!=v.y)return(false);

        return(true);
    }
    //--------------------------------------------------------------------------------------------------
    template<typename T>
    bool Vertex2<T>::operator != (const Vertex2<T> &v)const
    {
        if(x!=v.x)return(true);
        if(y!=v.y)return(true);

        return(false);
    }
}
#endif//HGL_VERTEX_2_CPP
