#ifndef HGL_STRING_PROPERTY_INCLUDE
#define HGL_STRING_PROPERTY_INCLUDE

#include<hgl/Str.H>
namespace hgl
{
	class StringProperty:public _Property<String &,String &,const String &>
	{
	public:

		void operator = (const wchar_t *str);
	};
}//namespace hgl
#endif//HGL_STRING_PROPERTY_INCLUDE
