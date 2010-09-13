protected:

    int hgp_width,hgp_height;
	int layer_number;                                                                           	//层次数量

	HGPLayer **layer;

	virtual HGPLayer *CreateLayer();

	void InitPrivate();

protected:

	int GetWidth(){return hgp_width;}
	int GetHeight(){return hgp_height;}
	int GetLayerNumber(){return layer_number;}	
                                              
	void SetFilter(TextureFilter);
	void SetAnisotropy(int);                                                                    	///<设置所有层的各向异性过滤级别

public:

	friend int CollComp(HGP *,int,int,float,float,HGP *,int,int,float,float);
	friend int CollComp(int,int,HGP *,int,int,float,float);	

