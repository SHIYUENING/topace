#ifndef HGL_OBJECTCONTROL_INCLUDE
#define HGL_OBJECTCONTROL_INCLUDE

#include<hgl/GUIObject.H>
#include<hgl/Stack.H>
#include<hgl/ClasList.H>
namespace hgl
{
	/**
	* 对象控制器，这是一个最基本的对象控制器，可以添加若干个对象到里面。然后由它控制显示、刷新、清除。它也可以被继承。
	*/
	class ObjectControl:public ClasList<Object>,public GUIObject                                    ///对象控制器
	{
		#include<hgl/Object.ProcEvent.H>
        #include<hgl/ObjectControl.Private.H>

	public: //方法

		ObjectControl();
		virtual ~ObjectControl();

        virtual void Add(Object *);

		virtual void Clear();
		virtual bool Unlink(Object *);
		virtual bool Delete(Object *);

		virtual void UnlinkAll();
		virtual void DeleteAll(){Clear();}

		virtual void operator += (Object *obj){Add(obj);}											///<向控制器中添加一个对象
		virtual void operator -= (Object *obj){Unlink(obj);}										///<从控制器中移除一个对象

		virtual void Update();                                                                      ///<刷新
		virtual void Draw();                                                                        ///<绘制
		virtual void DrawObject();                                                                  ///<绘制对象
		virtual void LastlyDraw(){};                                                                ///<最终绘制

	public: //方法 层次

		virtual void MoveToTopLevel(Object *);                                                      ///<将一个对象移到最上层
		virtual void MoveToBottomLevel(Object *);                                                   ///<将一个对象移到最下层
		virtual void MoveUpLevel(Object *);                                                         ///<将一个对象上移一层
		virtual void MoveDownLevel(Object *);                                                       ///<将一个对象下移一层
		virtual void MoveUpLevel(Object *,Object *);												///<将一个对象移到某个对象之上一层
		virtual void MoveDownLevel(Object *,Object *);												///<将一个对象移到某个对象之下一层

	public: //方法 对齐

		virtual void RowCenter(GUIObject *,int=-1);                                                 ///<将对像行居中(左右置中)
		virtual void ColCenter(GUIObject *,int=-1);                                                 ///<将对像列居中(上下置中)
            	void Center(GUIObject *,int=-1,int=-1);												///<将对象居中

	public:	//方法 键盘焦点

		virtual GUIObject *PrevKeyFocus();															///<键盘焦点移动到前一个
		virtual GUIObject *NextKeyFocus();															///<键盘焦点移动到下一个

		virtual GUIObject *KeyFocusUpMove();														///<键盘焦点上移
		virtual GUIObject *KeyFocusDownMove();                                                      ///<键盘焦点下移
		virtual GUIObject *KeyFocusLeftMove();                                                      ///<键盘焦点左移
		virtual GUIObject *KeyFocusRightMove();                                                     ///<键盘焦点右移

	public:	//方法 活动对象

		EventObject *ActiveObject(){return active_obj;}												///<当前活动对象
		GUIObject *GetKeyFocus(){return keyfocus_obj;}												///<取得键盘焦点
		void SetKeyFocus(GUIObject *);																///<设置键盘焦点

		virtual void PushActiveObject();															///<将当前活动对象压入堆栈
		virtual EventObject *PopActiveObject();														///<弹出上一个活动对象

	public: //方法 查找

		virtual Object *FindObject(wchar_t *);                                                		///<查找对象
		virtual bool FindObject(Object *);															///<查找对象

		#ifdef _DEBUG
		virtual void PutDebugInfo(const String &);													///<输出调试信息
		#endif//_DEBUG
	};//class ObjectControl
}//namespace hgl
#endif//HGL_OBJECTCONTROL_INCLUDE
