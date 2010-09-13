public: //事件

	DefEvent(bool,OnMouseMove            ,(int,int,uint));                ///<鼠标移动了
	DefEvent(bool,OnMouseWheel           ,(int,int, int));                ///<鼠标滚轮转动了
	DefEvent(bool,OnMouseLeftDown        ,(int,int,uint));                ///<鼠标左键按下了
	DefEvent(bool,OnMouseLeftUp          ,(int,int,uint));                ///<鼠标左键弹起了
	DefEvent(bool,OnMouseLeftDoubleClick ,(int,int,uint));                ///<鼠标左键双击了
	DefEvent(bool,OnMouseMidDown         ,(int,int,uint));                ///<鼠标中键按下了
	DefEvent(bool,OnMouseMidUp           ,(int,int,uint));                ///<鼠标中键弹起了
	DefEvent(bool,OnMouseMidDoubleClick  ,(int,int,uint));                ///<鼠标中键双击了
	DefEvent(bool,OnMouseRightDown       ,(int,int,uint));                ///<鼠标右键按下了
	DefEvent(bool,OnMouseRightUp         ,(int,int,uint));                ///<鼠标右键弹起了
	DefEvent(bool,OnMouseRightDoubleClick,(int,int,uint));                ///<鼠标右键双击了

	DefEvent(bool,OnJoystickDown,	(uint));								///<游戏杆按钮按下了
	DefEvent(bool,OnJoystickPress,	(uint));								///<游戏杆按钮按下了
	DefEvent(bool,OnJoystickUp,		(uint));								///<游戏杆按钮弹起了

	DefEvent(bool,OnKeyDown          ,(uint));                            ///<有按键按下了
	DefEvent(bool,OnKeyPress         ,(uint));                            ///<有按键按下了
	DefEvent(bool,OnKeyUp            ,(uint));                            ///<有按键弹起了

	DefEvent(bool,OnChar             ,(wchar_t));                           ///<有字符输入了

	DefEvent(bool,OnEvent            ,(int,void *));                        ///<有自定义事件了
