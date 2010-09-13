#ifndef HGL_OPENGL_APPLICATION_INCLUDE
#define HGL_OPENGL_APPLICATION_INCLUDE

#include<hgl/platform/GraphicsApplication.H>
namespace hgl
{
	/**
	* OpenGL图形应用程序基类
	*/
	class OpenGLApplication:public GraphicsApplication
	{
	protected:

		void InitOpenGL();

	public:

        virtual void SwapBuffer()=0;

        virtual void Frame()
        {
            GraphicsApplication::Frame();

            SwapBuffer();
        }

        virtual void Run(){GraphicsApplication::Run();}
	};
}//namespace hgl
#endif//HGL_OPENGL_APPLICATION_INCLUDE
