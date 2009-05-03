	enum PlayerState        //播放器状态
	{
		psNone=0,
		psPlay,
		psPause,
		psExit
	};

protected:

	ALbyte *audio_data;
	int audio_data_size;

	void *audio_ptr;                                                                                ///<音频数据指针

	char *audio_buffer;
	int audio_buffer_size;
	uint audio_buffer_count;																		///<播放数据计数

	AudioPlugInInterface *decode;

	ALenum format;                                                                                  ///<音频数据格式
	ALsizei rate;                                                                                   ///<音频数据采样率

	struct
	{
		bool open;
		uint64 time;
		float gap;

		struct
		{
			float gain;
			double time;
		}start,end;
	}auto_gain;																						///<自动增益

	bool ReadData(ALuint);
	bool UpdateBuffer();
	void ClearBuffer();

	bool Playback();
	virtual void Execute();

	void InitPrivate();
	bool Load(AudioFileType);

protected:

	volatile bool loop;
	volatile PlayerState ps;

	AudioSource audiosource;
	ALuint source;
	ALuint buffer[3];
	double time;
	double wait_time;

	bool GetLoop();
	void SetLoop(bool);

protected:

	uint    		GetIndex(){return audiosource.index;}
	double			GetTime(){return time;}
	int             GetState(){return audiosource.GetState();}
	float           GetMinGain(){return audiosource.GetMinGain();}
	float           GetMaxGain(){return audiosource.GetMaxGain();}

	float           GetPitch(){return audiosource.pitch;}
	void            SetPitch(float val){audiosource.SetPitch(val);}

	float           GetGain(){return audiosource.gain;}
	void            SetGain(float val){audiosource.SetGain(val);}

	float           GetConeGain(){return audiosource.cone_gain;}
	void            SetConeGain(float val){audiosource.SetConeGain(val);}

	float           GetRolloffFactor(){return audiosource.rolloff_factor;}
	void            SetRolloffFactor(float rf){audiosource.SetRolloffFactor(rf);}
