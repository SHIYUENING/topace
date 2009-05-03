#ifndef HGL__OBJECT_INCLUDE
#define HGL__OBJECT_INCLUDE

namespace hgl
{
	/**
	* 最终基类,无任何作用
	*/
	class _Object                                                                                     ///最终基类
	{
	public:

		virtual ~_Object(){};                                                                           ///<本类析构函数
	};
	
	typedef void (_Object::*ObjectMemberFunc)();
}

#endif//HGL__OBJECT_INCLUDE