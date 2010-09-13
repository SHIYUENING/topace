#ifndef HGL_ENUM_OBJECT_INCLUDE
#define HGL_ENUM_OBJECT_INCLUDE

#include<hgl/Object.H>
namespace hgl
{
	/**
	* 枚举对象是指每个回合都会被调用刷新(Update函数)的对象
	*/
	class EnumObject:public Object
	{
	public:

		EnumObject(bool=true);
		virtual ~EnumObject(){};

		virtual void Update();
	};
}//namespace hgl
#endif//HGL_ENUM_OBJECT_INCLUDE
