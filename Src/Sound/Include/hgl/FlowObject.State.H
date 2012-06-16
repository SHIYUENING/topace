	friend class FlowControl;
	#include<hgl/Object.ProcEvent.H>
	#include<hgl/Object.OnEvent.H>

public:
	/** \releates FlowObject
	* 流程对象状态枚举
	* @see FlowObject
	*/
	enum FlowObjectState
	{
		fosNotInit=0,                   ///<未初始化
		fosOK,                          ///<正常

		fosExitNotClear,                ///<退出，但不清除
		fosExitToBack,                  ///<退出到后台，继续绘制和刷新，但不接收事件
		fosReturn,                      ///<返回上一个状态为ExitNotClear/ExitToBack的对象

		fosExit,                        ///<退出，进入下一个对象
		fosExitFlow,                    ///<退出当前流程控制中的所有流程，并进入指定的下一个流程
		fosExitGame,                    ///<退出整个游戏
	};

protected:

	FlowObject *NextObject;                                                                     ///<下一个对象

	FlowObjectState fos;                                                                        ///<当前对象状态

	FlowObjectState GetState(){return fos;}
