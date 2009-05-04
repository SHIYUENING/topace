	friend class RadioItem;

public:

	/**
	* 对象属性位枚举
	*/
	enum ObjectAttrib
	{
		oaUpdate        = 1<<0,                     ///<对象需要刷新
		oaVisual        = 1<<1,                     ///<对象需要绘制
		oaProcEvent     = 1<<2,                     ///<对象可接收事件
		oaFlow          = 1<<3,                     ///<对象是流程对象

		oaControl       = 1<<4,                     ///<对象是控制器

		oaRes           = 1<<5,                     ///<对象是资源对象

		oaGUI           = 1<<6,                     ///<对象是否是GUI对象
		oaRadio   		= 1<<7,                     ///<对象是收音机对象

		oaKeyFocus		= 1<<8,						///<对象是否有可以键盘焦点
	};

	/**
	* 对象分类枚举
	*/
	enum ObjectClas
	{
		ocName=0,           ///<名字有效

		ocControl,          ///<控制器
		ocUpdate,           ///<需要刷新
		ocVisual,           ///<需要绘制
		ocProcEvent,        ///<需要处理事件

		ocRes,              ///<资源对象

		ocGUI,              ///<GUI对象
		ocAlign,            ///<需要做对齐运算
		ocRadio,      		///<收音机对象
		ocKeyFocus,			///<键盘焦点

		ocEnd               ///<结束定义，无意义
	};

protected:

	ObjectControl *super_object;

	uint object_attrib;                                                                     ///<当前对象属性

	bool destroy;

	bool enabled;

protected:
	
	ObjectControl *GetSuperObject(){return super_object;}
	uint GetObjectAttrib(){return object_attrib;}
	bool GetEnabled(){return enabled;}
	
	virtual void SetSuperObject(ObjectControl *);
	virtual void SetEnabled(bool);

	void InitPrivate();

public:

	bool is_update()        {return(object_attrib&oaUpdate		);}
	bool is_visual()        {return(object_attrib&oaVisual		);}
	bool is_proc_event()    {return(object_attrib&oaProcEvent	);}
	bool is_flow()          {return(object_attrib&oaFlow		);}
	bool is_control()       {return(object_attrib&oaControl		);}

	bool is_res()           {return(object_attrib&oaRes			);}

	bool is_gui()           {return(object_attrib&oaGUI			);}
	bool is_radio()			{return(object_attrib&oaRadio		);}

	bool is_key()			{return(object_attrib&oaKeyFocus	);}
