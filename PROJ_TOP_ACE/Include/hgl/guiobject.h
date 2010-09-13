#ifndef HGL_GUI_OBJECT_INCLUDE
#define HGL_GUI_OBJECT_INCLUDE

#include<hgl/EventObject.H>
#include<hgl/Str.H>
#include<hgl/Align.H>
namespace hgl
{
	class TileFont;

	/**
	* GUI对象是所有GUI控件的基类，它主要是使用了相对坐标设计，并且支持对齐属性，以及一些通用自动事件
	*/
	class GUIObject:public EventObject                                                              ///GUI对象
	{
		#include<hgl/guiObject.Attrib.H>

	public: //属性

		TileFont *			DrawFont;																///<绘制用字体

		bool    			Cutout;                                                     			///<是否做范围裁剪

		Property<VAlign>	Align;                                                                  ///<控件对齐方式

		Property<float>		Left;                                                                   ///<控件左边坐标
		Property<float>		Top;                                                                    ///<控件上边坐标
		Property<float>		Width;                                                                  ///<控件宽度
		Property<float>		Height;                                                                 ///<控件高度
		
		Property<float>		Right;                                                                  ///<控件右边界
		Property<float>		Bottom;                                                                 ///<控件底边界
		
		Property<float>		CenterX;                                                                ///<控件中心X
		Property<float>		CenterY;                                                                ///<控件中心Y
		
		Property<float>		MenuX;                                                                  ///<画面坐标X
		Property<float>		MenuY;                                                                  ///<画面坐标Y

		Property<bool>		MouseFocus;                                                             ///<鼠标是否在上面

//		PropertyString		Hint;                                                                   ///<提示信息

		bool    			AutoActive;                                                 			///<自动切换到活动状态

		void *				CustomizeData;

	public: //事件

		DefEvent(void,OnEnter,(GUIObject *));                                                     	///<鼠标进入事件
		DefEvent(void,OnLeave,(GUIObject *));                                                     	///<鼠标离开事件
		DefEvent(bool,OnHint,(GUIObject *));                                                      	///<产生提示信息

	public:

		GUIObject();                                                                                ///<本类构造函数
		GUIObject(float,float,float,float);                                                         ///<本类构造函数
		virtual ~GUIObject(){};                                                                     ///<本类析构函数

		virtual void SetMenuCoord(float,float);
		virtual void DrawObject();
		virtual void SetScissor(int *);
	};

	#define ON_DRAW_AND_RETURN(param)		if(OnDraw){OnDraw(param);return;}
}//namespace hgl
#endif//HGL_GUI_OBJECT_INCLUDE
