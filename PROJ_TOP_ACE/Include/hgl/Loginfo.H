#ifndef HGL_LOGINFO_INCLUDE
#define HGL_LOGINFO_INCLUDE

#ifndef __MAKE_PLUGIN__
namespace hgl
{
	class PlugIn;

	namespace loginfo
	{                
		PlugIn *InitLog();																			///<初始化日志系统
		void CloseLog();																			///<关闭日志系统

		//------------------------------------------------------------------------------------------
		
		void PutInfo();																				///<无内容输出(断行)

		void PutInfo(const wchar_t *,...);                                                          ///<输出日志信息(UNICODE版本)
		void PutError(const wchar_t *,...);                                                         ///<输出错误信息(UNICODE版本)
		void ShowMessage(const wchar_t *,...);                                                      ///<显示信息(UNICODE版本)

		void PutInfo(unsigned int,const char *,...);                                                ///<输出日志信息(ANSI版本)
		void PutError(unsigned int,const char *,...);                                               ///<输出错误信息(ANSI版本)
		void ShowMessage(unsigned int,const char *,...);											///<显示信息(ANSI版本)

		bool ShowSelectDialog(const wchar_t *);														///<显示YES/NO对话框

		#ifdef _DEBUG
			#define ErrorHint   PutError            //debug版错误提示使用PutError
			#define DebugLog	PutInfo				//debug版输出信息
		#else
			#define ErrorHint   PutInfo             //release版错误提示使用PutInfo
			#define DebugLog						//release版不出输信息
		#endif//_DEBUG
	}

	using namespace loginfo;
}//namespace hgl
#endif//__MAKE_PLUGIN__
#endif//HGL_LOGINFO_INCLUDE
