#ifndef HGL_DISPLAY_LIST_INCLUDE
#define HGL_DISPLAY_LIST_INCLUDE

namespace hgl
{
	/**
	* 显示列表封装类
	*/
	class DisplayList                                                                               ///显示列表类
	{
		int index;                                                                                  ///<索引

	public:

		DisplayList();                                                                              ///<本类构造函数
		virtual ~DisplayList();                                                                     ///<本类析构函数

		bool Compile(bool=false);                                                                   ///<开始制作显示列表
		void End();                                                                                 ///<结束编译

		void Execute();                                                                             ///<运行
	};
}//namespace hgl
#endif//HGL_DISPLAY_LIST_INCLUDE
