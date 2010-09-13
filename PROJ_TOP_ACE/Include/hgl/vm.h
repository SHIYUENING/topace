#ifndef HGL_VM_INCLUDE
#define HGL_VM_INCLUDE

#include<string.h>
/**
* 虚拟机共用要素
*/

namespace hgl
{
	#define vm_method(c,m) vm_method_ptr<sizeof(void (c::*)())>::Convert((void (c::*)())(&c::m))

	template <int>
	struct vm_method_ptr
	{
		template<class M>
		static void *Convert(M obj)
		{
			union u
			{
				M m;
				void *v;
			};

			return ((u *)(&obj))->v;
		}
	};
	
	//全局用
	#define MapMemberFunc(name,this_pointer,class,func)		MapFunc(name,this_pointer,vm_method(class,func))
	#define MapCppFunc(name,this_pointer,class,func)		MapMemberFunc(name,this_pointer,class,func)

	//对象用
	#define MapObject(name,class,create,clear)  			CreateObjectMap(name,sizeof(class),create,clear)
	#define MapObjectProperty(name,class,value) 			MapProperty(name,offsetof(class,class::value))
	#define MapObjectFunc(name,class,func) 					MapFunc(name,vm_method(class,func))
}//namespace hgl
#endif//HGL_VM_INCLUDE
