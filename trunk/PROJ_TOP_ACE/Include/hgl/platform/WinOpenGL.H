#ifndef HGL_WinOpenGL_INCLUDE
#define HGL_WinOpenGL_INCLUDE

#include<hgl/platform/WinWindow.H>
namespace hgl
{
	/**
	* 标准Window OpenGL窗口实现
	*/
	class WinGLWindow:public WinWindow
	{
    	void *gl_dll;

		int PixelFormat;

		HGLRC glrc;

		int color_bit;
		int alpha_bit;
		int depth_bit;
		int stencil_bit;
		int accum_bit;
		int multisample_level;

		bool multisample;
		int MultiSamplePixelFormat;

		bool InitOpenGL();
		bool InitMultiSample();

	public:

		WinGLWindow();
		virtual ~WinGLWindow();

		bool InitOpenGL(int,SystemInitInfo::Graphics::OpenGLSetup &);
		void CloseOpenGL();

//		bool ToFullScreen(int,int,int,int,bool=false);
//		bool ToWindow(int,int);

		void SetViewport(int,int,int,int);

	public:	//Windows操作系统独有部分

		HGLRC GetRC(){return glrc;}												///<取得HGLRC

	public:	//被实际操作系统接口层所调用的函数，请不要使用

		void SetSize(int,int);
	};
}//namespace hgl
#endif//HGL_WinOpenGL_INCLUDE
