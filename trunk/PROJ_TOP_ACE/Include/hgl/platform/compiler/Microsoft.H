#ifndef HGL_COMPILER_MICROSOFT_INCLUDE
#define HGL_COMPILER_MICROSOFT_INCLUDE
//--------------------------------------------------------------------------------------------------            
#define HGL_COMPILER_NAME	L"Microsoft C/C++"

#if _MSC_VER < 1400							//Visual C++ 2005(8.0)
	#error Please upgrade your compiler or development tools to Microsoft C/C++ 15.0 (Visual C++ 2008) or later.
#else
	#if _MSC_VER == 1600
		#define HGL_LIB_COMPILER_NAME	"VC2010"
	#elif _MSC_VER == 1500					//如果是Visual C++ 2008则要求必须有SP1
		#if _MSC_FULL_VER < 150030729		//Visual C++ 2008 SP1
		#error Please install Visual C++ 2008 Service Pack 1 and Windows SDK v7.1.
		#endif//_MSC_FULL_VER

		#define HGL_LIB_COMPILER_NAME	"VC2008"
	#elif _MSC_VER == 1400
		#define HGL_LIB_COMPILER_NAME	"VC2005"
	#endif//_MSC_VER

	#define enum_uint(name)	enum name:unsigned int	
#endif//_MSC_VER

#define vsnwprintf _vsnwprintf
//--------------------------------------------------------------------------------------------------
#include<hgl/platform/compiler/DataTypeTypedef.H>
#include<hgl/platform/compiler/Property.H>
//--------------------------------------------------------------------------------------------------
#define _USE_MATH_DEFINES				// 使用数学常数定义
//--------------------------------------------------------------------------------------------------
#pragma warning(disable:4311)			// 模板警告
#pragma warning(disable:4800)			// int -> bool 性能损失警告
#pragma warning(disable:4244)			// double -> int 精度丢失警告
#pragma warning(disable:4804)			// 不安全的类型比较
#pragma warning(disable:4805)			// 不安全的类型比较

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif//

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif//

#ifndef _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_NON_CONFORMING_SWPRINTFS
#endif//

#define hgl_malloc(size)		_aligned_malloc(size,HGL_MEM_ALIGN)
#define hgl_realloc(ptr,size)	_aligned_realloc(ptr,size,HGL_MEM_ALIGN)
#define hgl_free				_aligned_free

#include<malloc.h>

#ifdef _DLL
	#define HGL_LIB_CRT	"Dynamic"
#else
	#define HGL_LIB_CRT	"Static"
#endif//_DLL

#define HGL_LIB_FRONT	HGL_LIB_OS_NAME "_" HGL_LIB_CPU_NAME "_" HGL_LIB_COMPILER_NAME "_" HGL_LIB_DEBUG_NAME "_" HGL_LIB_CRT "_"
#define HGL_LIB_END		".LIB"
//--------------------------------------------------------------------------------------------------
#endif//HGL_COMPILER_MICROSOFT_INCLUDE

