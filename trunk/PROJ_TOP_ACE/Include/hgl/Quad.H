#ifndef HGL_QUAD_INCLUDE
#define HGL_QUAD_INCLUDE

#include<hgl/Vertex2.H>
namespace hgl
{
	/**
	* 四边形类
	*/
	template<typename T> class Quad
	{
	public:

		Vertex2<T> Vertex[4];
	};

	typedef Quad<float>		Quad2f;
	typedef Quad<double> 	Quad2d;
	typedef Quad<int>		Quad2i;
}//namespace hgl
#endif//HGL_QUAD_INCLUDE
