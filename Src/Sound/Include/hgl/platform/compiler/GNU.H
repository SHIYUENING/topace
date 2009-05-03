#ifndef HGL_COMPILER_GNU_INCLUDE
#define HGL_COMPILER_GNU_INCLUDE
                                               
//--------------------------------------------------------------------------------------------------
#define HGL_COMPILER_NAME	L"GNU C/C++"

#if __GNUC__ < 4
	#error 编译器版本太低，不被支持
#endif//

#define enum_uint(name)	enum name

//--------------------------------------------------------------------------------------------------   
#include<hgl/platform/compiler/DataTypeTypedef.H>
#include<hgl/platform/compiler/Property.H>
//--------------------------------------------------------------------------------------------------
#endif//HGL_COMPILER_GNU_INCLUDE
