private:

	void PrevCreateLayer(ColorType,uint,uint8 *,uint);												///<创建预处理
                  
public:

	enum LayerType
    {
    	ltNone=0,			///<起始定义，无意义

        ltTexture2D,		///<单2D贴图图片层
        ltTextureRect,		///<单矩形贴图图片层
        ltMultiTexture,		///<多2D贴图图片层

        ltText,				///<文本层
        ltVector,			///<矢量层

        ltEnd				///<结束定义，无意义
    };
    
protected:

	uint gl_format;

	LayerType layer_type;
	ColorType orign_color;

	int layer_left,layer_top;
	int layer_width,layer_height;

	int hgp_width,hgp_height;

protected:

	LayerType GetType(){return layer_type;}
	ColorType GetOrignColor(){return orign_color;}

	int GetLeft()	{return layer_left;}
	int GetTop()	{return layer_top;}
	int GetWidth()	{return layer_width;}
	int GetHeight()	{return layer_height;}

	void SetLeft(int n){layer_left=n;}
	void SetTop(int n){layer_top=n;}

public:

	virtual void SetFilter(TextureFilter)=0;														///<设置层过滤方式
	virtual void SetAnisotropy(int)=0;                                                          	///<设置层各向异性过滤级别

	virtual void CreateLayer(ColorType,uint,uint8 *,uint)=0;										///<实质创建层虚拟函数
