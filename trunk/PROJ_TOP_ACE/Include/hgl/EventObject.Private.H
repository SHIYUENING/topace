		friend class ObjectControl;

	public:

		virtual bool Proc_MouseMove             (int,int,uint){return(false);}
		virtual bool Proc_MouseWheel            (int,int, int){return(false);}
		virtual bool Proc_MouseLeftDown         (int,int,uint){return(false);}
		virtual bool Proc_MouseLeftUp           (int,int,uint){return(false);}
		virtual bool Proc_MouseLeftDoubleClick  (int,int,uint){return(false);}
		virtual bool Proc_MouseMidDown          (int,int,uint){return(false);}
		virtual bool Proc_MouseMidUp            (int,int,uint){return(false);}
		virtual bool Proc_MouseMidDoubleClick   (int,int,uint){return(false);}
		virtual bool Proc_MouseRightDown        (int,int,uint){return(false);}
		virtual bool Proc_MouseRightUp          (int,int,uint){return(false);}
		virtual bool Proc_MouseRightDoubleClick (int,int,uint){return(false);}

		virtual bool Proc_JoystickDown			(uint){return(false);}
		virtual bool Proc_JoystickPress			(uint){return(false);}
		virtual bool Proc_JoystickUp			(uint){return(false);}

		virtual bool Proc_KeyDown       (uint){return(false);}
		virtual bool Proc_KeyPress      (uint){return(false);}
		virtual bool Proc_KeyUp         (uint){return(false);}

		virtual bool Proc_Char          (wchar_t){return(false);}

		virtual bool Proc_Event         (int,void *);

	protected:

		bool active;

	protected:

		bool GetActive(){return active;}

		virtual void SetActive(bool);
