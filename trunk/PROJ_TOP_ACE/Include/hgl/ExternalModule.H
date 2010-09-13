#ifndef HGL_EXTERNAL_MODULE_INCLUDE
#define HGL_EXTERNAL_MODULE_INCLUDE
namespace hgl
{
	/**
	* 这个类用于对外部动态库的调用,支持Windows/Linux/BSD/MacOSX<br>
	* Windows 下动态库扩展名为.DLL<br>
	* FreeBSD/MacOSX 下动态库扩展名为.dylib<br>
	* Linux 下动态库扩展名为.so
	*/
	class ExternalModule                                                                            ///外部模块调用类
	{
		void *point;

	public: //方法

		ExternalModule();                                                                           ///<本类构造函数
		virtual ~ExternalModule();                                                                  ///<本类析构函数

		bool Load(const wchar_t *);                                                                 ///<加载一个外部模块
		void Clear();                                                                               ///<清除当前模块

		void *FindFunc(const char *);																///<查找函数
		void *GetFunc(const char *);																///<取得函数
	};
}//namespace hgl
#endif//HGL_EXTERNAL_MODULE_INCLUDE
