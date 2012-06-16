#ifndef HGL_COMPILER_CPlusPlusBuilder_INCLUDE
#define HGL_COMPILER_CPlusPlusBuilder_INCLUDE
//--------------------------------------------------------------------------------------------------
#  if __BORLANDC__ >= 0x0630
	#define HGL_COMPILER_NAME		L"Embarcadero C++"		//0x630 C++Builder XE
	#define HGL_LIB_COMPILER_NAME	"CBXE"
	#define enum_uint(name)	enum name:unsigned int
#elif __BORLANDC__ >= 0x0620
	#define HGL_COMPILER_NAME		L"Embarcadero C++"		//0x620 C++Builder 2010
	#define HGL_LIB_COMPILER_NAME	"CB2010"
	#define enum_uint(name)	enum name:unsigned int
#elif __BORLANDC__ >= 0x0610
	#define HGL_COMPILER_NAME		L"CodeGear C++"			//0x610 C++Builder 2009
	#define HGL_LIB_COMPILER_NAME	"CB2009"
	#define enum_uint(name)	enum name:unsigned int
#elif __BORLANDC__ >= 0x0590
	#define HGL_COMPILER_NAME		L"CodeGear C++"			//0x590 C++Builder 2007
	#define HGL_LIB_COMPILER_NAME	"CB2007"
	#define enum_uint(name)	enum name
#else
	//不支持更低版本的编译器
	#error Borland legend does not exist, please upgrade your compiler or development tools to C++Builder 2009 or later.
#endif//__BORLANDC__

#pragma option -K                       //强制char数据类型为无符号型
#pragma option -6                       //按Pentium Pro/PentiumII方式优化
#pragma option -b                       //强制将Enum转为int
//--------------------------------------------------------------------------------------------------
#include<hgl/platform/compiler/DataTypeTypedef.H>
#include<hgl/platform/compiler/Property.H>

#define hgl_malloc		malloc
#define hgl_realloc		realloc
#define hgl_free		free

#include<malloc.h>

#define HGL_LIB_FRONT	HGL_LIB_OS_NAME "_" HGL_LIB_CPU_NAME "_" HGL_LIB_COMPILER_NAME "_" HGL_LIB_DEBUG_NAME "_"
#define HGL_LIB_END		".LIB"
//--------------------------------------------------------------------------------------------------
#endif//HGL_COMPILER_CPlusPlusBuilder_INCLUDE

