#ifndef HGL_COMPILER_CODEGEAR_INCLUDE
#define HGL_COMPILER_CODEGEAR_INCLUDE
//--------------------------------------------------------------------------------------------------
#define HGL_COMPILER_NAME	L"CodeGear C/C++"

#if __BORLANDC__ < 0x0590
	#error 编译器版本太低，不被支持
#endif//

#if __BORLANDC__ >= 0x610
	#define __cplusplus_0x__		//支持C++0x

	#define enum_uint(name)	enum name:unsigned int
#else
	#define enum_uint(name)	enum name
#endif//

#pragma option -K                       //强制char数据类型为无符号型
#pragma option -6                       //按Pentium Pro/PentiumII方式优化
#pragma option -b                       //强制将Enum转为int
//--------------------------------------------------------------------------------------------------
#include<hgl/platform/compiler/DataTypeTypedef.H>     
#include<hgl/platform/compiler/Property.H>
//--------------------------------------------------------------------------------------------------
#endif//HGL_COMPILER_CODEGEAR_INCLUDE
