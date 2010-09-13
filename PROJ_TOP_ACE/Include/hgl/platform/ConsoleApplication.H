#ifndef HGL_CONSOLE_APPLICATION_INCLUDE
#define HGL_CONSOLE_APPLICATION_INCLUDE

#include<hgl/platform/BaseApplication.H>
namespace hgl
{
	/**
	* 控制台应用程序基类<br>
	* 控制台应用程序基类被设计为必须输出日志
	*/
	class ConsoleApplication:public BaseApplication
	{
	public:

		ConsoleApplication();
		virtual ~ConsoleApplication();

		virtual bool Init(SystemInitInfo *);														///<初始化当前应用程序
	};
}//namespace hgl
#endif//HGL_CONSOLE_APPLICATION_INCLUDE
