public:

	virtual bool Proc_MouseMove             (int,int,uint);
	virtual bool Proc_MouseWheel            (int,int, int);
	virtual bool Proc_MouseLeftDown         (int,int,uint);
	virtual bool Proc_MouseLeftUp           (int,int,uint);
	virtual bool Proc_MouseLeftDoubleClick  (int,int,uint);
	virtual bool Proc_MouseMidDown          (int,int,uint);
	virtual bool Proc_MouseMidUp            (int,int,uint);
	virtual bool Proc_MouseMidDoubleClick   (int,int,uint);
	virtual bool Proc_MouseRightDown        (int,int,uint);
	virtual bool Proc_MouseRightUp          (int,int,uint);
	virtual bool Proc_MouseRightDoubleClick (int,int,uint);

	virtual bool Proc_JoystickDown			(uint);
	virtual bool Proc_JoystickPress			(uint);
	virtual bool Proc_JoystickUp			(uint);

	virtual bool Proc_KeyDown       (uint);
	virtual bool Proc_KeyPress      (uint);
	virtual bool Proc_KeyUp         (uint);

	virtual bool Proc_Char          (wchar_t);

	virtual bool Proc_Event         (int,void *);
