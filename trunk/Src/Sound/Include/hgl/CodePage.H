#ifndef HGL_CODE_PAGE_INCLUDE
#define HGL_CODE_PAGE_INCLUDE

namespace hgl
{
	/**
	* 代码页枚举
	*/
	enum CharacterCodePage              ///代码页枚举
	{
		ccpNone=0,                                          ///<起始定义，无意义

		//中文
		ccpGBK                          =936,               ///<中国GBK标准中文
		ccpBig5                         =950,               ///<中国台湾Big5标准繁体中文
		ccpGB2312                       =20936,             ///<中国GB2312标准简体中文
		ccpHZGB2312                     =52936,             ///<中国香港HZ-GB2312标准简体中文
		ccpGB18030                      =54936,             ///<中国GB18030-2000标准中文

		//日文
		ccpShiftJIS                     =932,               ///<日文ShiftJIS
		ccpJISX                         =50222,             ///<日文ISO-2022 JIS X 0201-1989

		ccpUTF7							=65000,				///<utf-7
		ccpUTF8							=65001,				///<utf-8

		ccpEnd                          ///<结束定义，无意义
	};

	typedef unsigned int CCP;
}
#endif//HGL_CODE_PAGE_INCLUDE
