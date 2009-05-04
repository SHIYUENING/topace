	friend class RadioItem;

public:

	/**
	* ��������λö��
	*/
	enum ObjectAttrib
	{
		oaUpdate        = 1<<0,                     ///<������Ҫˢ��
		oaVisual        = 1<<1,                     ///<������Ҫ����
		oaProcEvent     = 1<<2,                     ///<����ɽ����¼�
		oaFlow          = 1<<3,                     ///<���������̶���

		oaControl       = 1<<4,                     ///<�����ǿ�����

		oaRes           = 1<<5,                     ///<��������Դ����

		oaGUI           = 1<<6,                     ///<�����Ƿ���GUI����
		oaRadio   		= 1<<7,                     ///<����������������

		oaKeyFocus		= 1<<8,						///<�����Ƿ��п��Լ��̽���
	};

	/**
	* �������ö��
	*/
	enum ObjectClas
	{
		ocName=0,           ///<������Ч

		ocControl,          ///<������
		ocUpdate,           ///<��Ҫˢ��
		ocVisual,           ///<��Ҫ����
		ocProcEvent,        ///<��Ҫ�����¼�

		ocRes,              ///<��Դ����

		ocGUI,              ///<GUI����
		ocAlign,            ///<��Ҫ����������
		ocRadio,      		///<����������
		ocKeyFocus,			///<���̽���

		ocEnd               ///<�������壬������
	};

protected:

	ObjectControl *super_object;

	uint object_attrib;                                                                     ///<��ǰ��������

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
