	protected:	//内部属性

		bool join;																					///<是否是关联进来的

		int vsWidth,vsHeight;
		ColorType vsColorType;

		uint8 *pixel_buffer;																		///<数据缓冲区
		uint8 **scanline;                                                                			///<扫描线数据

		void *vs;

	protected:  //内部方法

		virtual bool CreateBuffer(int,int,int);

				int CheckTarget(VSBase *,int &,int &,int &,int &,int &,int &);
				int CheckSource(int &,int &,int &,int &,int &,int &);

		virtual void _PutPixel(int,int)=0;
		virtual void _HLine(int,int,int)=0;
		virtual void _VLine(int,int,int)=0;

		virtual void SplitToRGB(uint8 *,uint8 *,uint8 *,int,int,int)=0;
		virtual void SplitToRGBA(uint8 *,uint8 *,uint8 *,uint8 *,int,int,int)=0;
		
		virtual void DrawRGB(uint8 *,uint8 *,uint8 *,int,int,int)=0;
		virtual void DrawRGBA(uint8 *,uint8 *,uint8 *,uint8 *,int,int,int)=0;

	protected:

		int GetWidth(){return vsWidth;}
		int GetHeight(){return vsHeight;}

		ColorType GetColor(){return vsColorType;}

		uint8 *GetData(){return pixel_buffer;}

		void InitPrivate();
