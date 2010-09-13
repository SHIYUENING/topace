#ifndef HGL_VSBASE_INCLUDE
#define HGL_VSBASE_INCLUDE

#include<hgl/_Object.H>
#include<hgl/DataType.H>
#include<hgl/ColorType.H>
namespace hgl
{
    class HAC;

	/**
	* 虚拟屏幕基类提供统一的虚拟屏幕操作功能<br>
	* 别把它改成从Object派生，会出问题
	*/
	class VSBase:public _Object                                                                     ///虚拟屏幕基类
	{
		#include<hgl/VSBase.Attrib.H>
		
	public: //属性

		Property<uint8 *>	Data;                                                                   ///<通用格式的象素数据

		Property<int>		Width;                                                                  ///<虚拟屏幕宽度
		Property<int>		Height;                                                                 ///<虚拟屏幕高度

    	Property<ColorType>	Color;																	///<色彩类型

	public: //通用，高速方法

		void Clear()                                                                       			///<清除画面
		{
			int n=vsHeight;
			while(n--)
				_HLine(0,n,vsWidth);
		}

		void PutPixel(int,int);                                                             		///<画点
		void HLine(int,int,int);                                                            		///<画水平线
		void VLine(int,int,int);                                                            		///<画垂直线
		void Line(int,int,int,int);                                                         		///<画直线
		void Rectangle(int,int,int,int);                                                    		///<画矩形框
		void Bar(int,int,int,int);                                                          		///<画矩形块
		void Circle(int,int,int);                                                           		///<画正圆
		void Ellipse(int,int,int,int);                                                      		///<画椭圆
		void Sector(int,int,int,int,int);                                                   		///<画扇形

		virtual void SetColor(int,int,int,int=255)=0;												///<设置颜色	

	public:	//方法

		VSBase();																					///<本类构造函数
		virtual ~VSBase();                                                            				///<本类析构函数

		virtual bool Create(int,int)=0;                                                             ///<创建虚拟屏幕
            	void CreateFromScreen(int,int,int,int);												///<创建基于真实屏幕内容
		virtual bool JoinCreate(uint8 **,int,int);													///<关联虚拟屏幕
		virtual bool JoinCreate(uint8 *,int,int,int);												///<关联虚拟屏幕
		virtual void Close();                                                                     	///<关闭虚拟屏幕

				uint8 *GetPointer(){return pixel_buffer;}											///<取得数据缓冲指针(效果和Data一样，用于不便于使用Data的情况下)
		virtual uint8 *GetPointer(int,int)=0;														///<取某一位置的数据缓冲区指针

            	void FlipUP();																		///<上面翻转

		virtual bool DrawTo(VSBase *,int,int,int,int,int,int);										///<绘制当前VS内容到指定vs
				bool DrawTo(VSBase *vs,int x,int y){return DrawTo(vs,x,y,0,0,vsWidth,vsHeight);}	///<绘制当前VS内容到指定vs

				void Draw(int,int,float=1,float=1);													///<绘制当前虚拟屏幕图片

	public:	//方法

				bool SaveToHGP(const wchar_t *,const wchar_t *ca=L"RLE",float level=1);				///<保存成HGP
				bool SaveToTEX(const wchar_t *,const wchar_t *ca=L"RLE",float level=1);             ///<保存成TEX
				bool SaveToFile(const wchar_t *);                                                   ///<保存成其它格式
	};

	VSBase *CreateVS(ColorType);																	///<根据色彩类型创建一个虚拟屏幕
	VSBase *CreateVS(int,int,ColorType);															///<根据尺寸和色彩类型创建一个虚拟屏幕
	VSBase *CreateVSFromFile(const wchar_t *,bool=true,bool=true);									///<从贴图文件(*.TEX)加载一个虚拟屏幕
	VSBase *CreateVSFromFile(HAC *,const wchar_t *);							                    ///<从贴图文件(*.TEX)加载一个虚拟屏幕
	VSBase *CreateVSFromPixelBuffer(uint8 *,int,int,ColorType);										///<关联象素缓冲区为虚拟屏幕
};//namespace hgl
#endif//HGL_VSBASE_INCLUDE
