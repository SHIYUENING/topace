	friend class ObjectControl;

  	void SetSuperObject(ObjectControl *);

protected:

	VAlign align;                           //对齐属性
	float left,top,width,height;            //控件坐标
	float menux,menuy;                      //屏幕绝对坐标
	int scissor[4];                         //裁剪坐标
	bool mouse_focus;                       //鼠标是否在内部

//	String hint;                            //提示字串

protected:

//	const 	wchar_t *GetHint(){return hint.wc_str();}

			VAlign GetAlign(){return align;}

			float GetLeft(){return left;}
			float GetTop(){return top;}
	virtual float GetWidth(){return width;}
	virtual float GetHeight(){return height;}

			float GetRight(){return left+width;}
			float GetBottom(){return top+height;}

			float GetCenterX(){return left+width/2.0;}
			float GetCenterY(){return top+height/2.0;}

			void SetCenterX(float cx){left=cx-width/2.0;}
			void SetCenterY(float cy){top=cy-height/2.0;}

			float GetMenuX(){return menux;}
			float GetMenuY(){return menuy;}

			bool GetFocus(){return mouse_focus;}

//			void SetHint(const wchar_t *str){hint=str;}

	virtual void SetAlign(VAlign);

	virtual void SetLeft(float);
	virtual void SetTop(float);
	virtual void SetWidth(float);
	virtual void SetHeight(float);

	void InitPrivate();

public:

	virtual bool Proc_MouseMove             (int,int,uint32);
