#ifndef HGL_COMPILER_MICROSOFT_INCLUDE
#define HGL_COMPILER_MICROSOFT_INCLUDE
//--------------------------------------------------------------------------------------------------            
#define HGL_COMPILER_NAME	L"Microsoft C/C++"

#if _MSC_VER < 1500						//Visual C++ 2008(9.0)
	#error 编译器版本太低，不被支持
#endif//

#define enum_uint(name)	enum name
#define vsnwprintf _vsnwprintf
//--------------------------------------------------------------------------------------------------
#include<hgl/platform/compiler/DataTypeTypedef.H>
#include<hgl/platform/compiler/Property.H>
//--------------------------------------------------------------------------------------------------
#define _USE_MATH_DEFINES				//使用数学常数定义
//--------------------------------------------------------------------------------------------------
#pragma warning(disable:4311)			// 模板警告
#pragma warning(disable:4800)			// int -> bool 性能损失警告
#pragma warning(disable:4244)			// double -> int 精度丢失警告
#pragma warning(disable:4804)			// 不安全的类型比较
#pragma warning(disable:4805)			// 不安全的类型比较

#pragma comment(lib,"OpenGL32.LIB")		// 连入OpenGL库
#pragma comment(lib,"GLU32.LIB")		// 连入OpenGL库

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif//

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif//

#ifndef _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_NON_CONFORMING_SWPRINTFS
#endif//
//--------------------------------------------------------------------------------------------------
#endif//HGL_COMPILER_MICROSOFT_INCLUDE
