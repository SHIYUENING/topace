private:

	void InitPrivate();

protected:

	void *mov;
	
	void *	(__cdecl *MovieLoad		)(const wchar_t *);
	void	(__cdecl *MovieClear	)(void *);
	bool	(__cdecl *MovieGetInfo	)(void *,int &,int &,int &,bool &);
	void	(__cdecl *MovieRestart	)(void *,uint);
	bool	(__cdecl *MovieUpdate	)(void *,uint,uint8 **);
	
protected:	//图像部分

	TextureType 	movie_texture_type;					//贴图类型
	GLuint 			movie_texture_format;				//贴图格式
	ColorType		movie_texture_color;				//贴图色彩格式

	Texture2D *		movie_texture;						//影片贴图

	bool			movie_flip;							//是否需要翻转

	int 			movie_width,
					movie_height;						//影片大小

	float			movie_float_width,					//影片在贴图中占的大小
					movie_float_height;

protected:	//声音部分

	AudioSource *	movie_audio_source;					//影片用音源
	AudioBuffer *	movie_audio_buffer[2];				//影片用音频数据缓冲

protected:	//共用部分

	uint32 time;
	uint32 next_time;
