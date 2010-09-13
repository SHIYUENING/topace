#ifndef HGL_FLOWOBJECT_INCLUDE
#define HGL_FLOWOBJECT_INCLUDE

#include<hgl/EventObject.H>
#include<hgl/ObjectControl.H>
namespace hgl
{
	/**
	* 流程对象是指可以放在流程控制器里的一种特殊对象，它类似于HGLv17和HGLv16加强版中的GameProgram。<br>
	* 需要注意的是在HGLv18中，画面绘制和刷新是分离的，刷新是在不停的运行的，而画面绘制只在时间到达时才会被调用。<br>
	* 另：KeyPreview默认为false,其为true时键盘事件先传给FlowObject的事件处理函数，为false时先传给Control内的控件
	*/
	class FlowObject:public EventObject                                         	                ///流程对象基类
	{
		#include<hgl/FlowObject.State.H>

	public: //属性

		bool KeyPreview;                                                                            ///<键盘事件预览

		ObjectControl Control;                                                                      ///<对象控制器

		Property<FlowObjectState> ObjectState;                                                      ///<当前对象状态虚拟变量

	public:	//事件

		DefEvent(void,OnDestroy,(FlowObject *));													///<销毁事件

		DefEvent(void,OnFlowReturn,(FlowObject *));													///<流程返回事件

	public: //方法

		FlowObject();                                                                               //本类构造函数
		virtual ~FlowObject();                                                                    	//本类析构函数

		virtual FlowObject *GetNextObject();                                                        //取得下一个对象
		virtual void ObjectReturn(FlowObject *);                                                  	//对象返回函数

		virtual void Update(){};                                                                    //刷新函数
		virtual void Draw(){};                                                                      //画面绘制
		virtual void LastlyDraw(){};                                                                //最终画面绘制(当对象都绘制完成后会被调用)

		virtual void UpdateObject()
		{
			Update();

			if(Control.Enabled)
				Control.Update();
		}

		virtual void DrawObject()
		{
			Draw();

			if(Control.Visible)
				Control.DrawObject();

			LastlyDraw();
		}
	};
}//namespace hgl
#endif//HGL_FLOWOBJECT_INCLUDE
