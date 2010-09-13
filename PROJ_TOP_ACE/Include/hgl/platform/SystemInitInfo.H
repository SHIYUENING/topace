#ifndef HGL_SYSTEMINITINFO_INCLUDE
#define HGL_SYSTEMINITINFO_INCLUDE

#include<hgl/Font.H>
namespace hgl
{
	/**
	* 应用程序运行模式枚举
	*/
	enum AppRunMode     ///应用程序运行模式枚举
	{
		armNone=0,      ///<起始定义,无意义

		armASync,       ///<异步模式,Draw按FPS数量执行,Update只要有空闲就运行
		armSync,        ///<同步模式,Draw/Update均按FPS数量执行

		armFast,        ///<高速模式,Draw/Update都运行相同数量,但不做延时,一般用于测试最大fps

		armExternal,	///<外部Hinstance/hwnd模式,自身不控制主循环

		armServer,      ///<服务器程序专用运行模式

		armEnd          ///<结束定义,无意义
	};

	/**
	* 这个类用于填充系统初始化信息，当不使用.cmproj工程文件时，需要使用这个类，而其也会自动将设置保存成.cmproj工程文件。
	*
	* ProjectPath会在这个类构造时自动写入当前路径，如果当前路径不等于游戏路径，才需要重新写入它(比如从注册表中取得游戏路径)。
	*/
	class SystemInitInfo                                                                            ///系统初始化信息类
	{
		void *mutex;

	public:

		String ProjectPath;                                                                         ///<工程路径

		struct Info
		{
			String ProjectName;                                                                     ///<工程名称,必须填写
			String ProjectCode;                                                                     ///<工程代码名称,必须填写
			String ProjectVersion;                                                                  ///<工程版本
			String ProjectDeveloper;                                                                ///<工程开发者
		}info;

		AppRunMode RunMode;                                                                         ///<运行模式,默认armASync

		bool CheckSystem;																			///<是否检测系统

		bool MultiStartup;                                                                          ///<是否允许多重启动
		bool ShowError;																				///<是否显示错误

		bool WaitActive;                                                                            ///<等待应用程序进入活动状态,默认为false
		bool BackNotDraw;                                                                           ///<当程序窗口位于后台时不绘制画面,默认为true
		bool DisableScreenSave;																		///<禁止屏幕保护程序运行,默认为true

		bool UseJoystick;																			///<是否使用游戏杆

		uint KeyPressTime;																			///<按键产生一个press触发所需的时间

		struct Graphics
		{
			bool FullScreen;                                                                        ///<是否全屏,默认false,即窗口模式

			int32 Width,Height;                                                                     ///<游戏画面大小
			int32 Bit;                                                                              ///<色彩位数,默认32
			int32 VSync;                                                                            ///<屏幕垂直刷新率,默认75Hz

			int32 FPS;                                                                              ///<期望的FPS,默认60

			struct Safe																				///<安全模式画面大小(当全屏进入失败时的选项)
			{
				int32 Width,Height;                                                                 ///<游戏画面大小
			}safe;

			struct OpenGLSetup
			{
				int32 AlphaBits;                                                                    ///<Alpha缓冲区位深度,默认8位
				int32 DepthBits;                                                                    ///<Depth缓冲区位深度,默认16
				int32 StencilBits;                                                                  ///<Stencil缓冲区位深度,默认0
				int32 AccumBits;                                                                    ///<Accum缓冲区位深度,默认0

				int32 MultiSample;                                                                  ///<多重采样级别(全屏抗矩齿级别)

				bool NicestTextureCompress;															///<高质量贴图压缩,默认为真

				bool texture_rectangle;																///<是否启用矩形贴图
				bool texture_non_power_of_two;														///<是否启用非2次幂贴图
				bool vbo;																			///<是否启用vbo
				bool pbo;																			///<是否启用pbo
				bool fbo;																			///<是否启用fbo
				bool glsl;																			///<是否启用glsl
				bool multi_texture;																	///<是否启用多重贴图

				bool debug;																			///<产生硬件Debug信息(默认不产生，并且此功能不对所有显卡有效)
			}gl;

			struct GUI
			{
				bool use;																			///<是否使用GUI，默认不使用

				String pack;																		///<缺省GUI包
			}gui;

			struct 
			{
				bool use;																			///<默认不使用

				Font eng_fnt;																		///<缺省英文字体
				Font chs_fnt;																		///<缺省中文字体
				uint32 fnt_buf;																		///<缺省字体缓冲区大小,默认2000
			}fnt;
		}graphics;

		struct Audio
		{
			bool enum_device;																		///<是否枚举设备
			String DeviceName;																		///<设备名称
		}audio;

		struct WindowSetup
		{
			String Name;                                                                            ///<窗口标题
			String ClassName;																		///<类名(windows用)
			String IconFilename;                                                                    ///<图标文件名称
			String CursorFilename;                                                                  ///<光标文件名称
                                                                                                                                      
			bool Edge;																				///<是否显示边框

			bool SysMenu;                                                                           ///<是否显示系统菜单
			bool Right;                                                                             ///<窗口是否使用靠右风格

			bool Resize;                                                                            ///<窗口大小是否可调整
			bool Minimize;                                                                          ///<窗口是否可以最小化
			bool Maximize;                                                                          ///<窗口是否可以最大化

			bool TopMost;                                                                           ///<永远在最上面
			bool AppTaskBar;                                                                        ///<程序项在任务栏显示
		}win;

	public:

		SystemInitInfo();                                                                           //本类构造函数
		virtual ~SystemInitInfo();                                                                  //本类析构函数

		bool CheckMultiStartup();                                                                   ///<检查多重启动

		virtual void ProcBlankValue();                                                              ///<处理未填写的值
	};//class SystemInitInfo
}//namespace hgl
#endif//HGL_SYSTEMINITINFO_INCLUDE
