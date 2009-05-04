#ifndef HGL_STRING_INCLUDE
#define HGL_STRING_INCLUDE

#include<hgl/CodePage.H>
#include<hgl/DataType.H>
#include<hgl/String.Private.H>
#include<hgl/CompOperator.H>
namespace hgl
{
	/**
	* 字符串处理类，在《古月v18》中几乎所有的字符串部分都会用到的一个类，对中文有着非常好的支持。<br>
	* 它使用UNICODE编码
	*/
	class String																					///字符串处理类
	{        
		#include<hgl/String.Operator.H>

	public:	//内部函数，请不要调用

    	void Init();

		void Constructor();
		void AddRef();

	protected:

		PrivateString *data;

		wchar_t *GetString()const {return(this?(data?data->str:NULL):NULL);}
		const int GetLength()const {return(this?(data?data->length:NULL):0);}

		void SetString(const wchar_t *,int=-1);
		void EquString(const wchar_t *,int);
		void ClearString();
		void CopyString(const String &);

	public: //属性

		Property<const int> Length;                                            							///<字符串长度虚拟变量

	public: //函数

		//构造函数
		String();
        String(const char);
		String(const char *);
		String(const wchar_t);
		String(const wchar_t *);
		String(const char *,int);
		String(const wchar_t *,int);
		String(CCP,const char *,int=-1);
		String(const String &);
		String(int);
		String(uint);
		String(int64);
		String(uint64);
		String(double);

		//析构函数
		~String();

	public: //方法

		void Unlink();                                                                              ///<和其它同内容的String断开连接

		/**
		* 此函数返回一个C风格(UNICODE编码)的字符串指针
		*/
		wchar_t *w_str()const{return GetString();}													///<返回一个wchar_t *类型的字符串指针(同wc_str())
		wchar_t *wc_str()const{return GetString();}                                       			///<返回一个wchar_t *类型的字符串指针(同w_str())
		wchar_t *wc_copy()const;																	///<返回一个wchar_t *类型的字符串指针，需要自己delete[]掉

		wchar_t *wc_offset(int off)const{return GetString()+off;}									///<返回一个wchar_t *类型的字符串指针

		//赋值用函数
		void Clear(){ClearString();}                                                                ///<清除字符串的数据

		void ConvertString(CCP,const char *,int=-1);                                   				///<转换一个指定代码的ANSI字符串到本类中

		void Strcpy(const char *);                                                                  ///<复制一个字符串到本类中来(ANSI)
		void Strcpy(CCP ccp,const char *as){ConvertString(ccp,as);}                                 ///<复制一个字符串到本类中来(ANSI)
		void Strcpy(const wchar_t *);                                                               ///<复制一个字符串到本类中来(UNICODE)
		void Strcpy(const String &str){Strcpy(str.wc_str());}                                  		///<复制一个字符串到本类中来

		void Strcpy(const char *,int);                                                              ///<复制一个字符串到本类中来(ANSI)
		void Strcpy(const wchar_t *,int);                                                           ///<复制一个字符串到本类中来(UNICODE)
		void Strcpy(const String &str,int len){Strcpy(str.wc_str(),len);}                           ///<复制一个字符串到本类中来
		void Strcpy(const String &str,int start,int len)											///<复制一个字符串到本类中来
		{
			if(start<str.Length)
				Strcpy(str.wc_str()+start,len);
		}

		void Strcat(const char *);                                                                  ///<连接一个字符串到本类字符串的后面(ANSI)
		void Strcat(const wchar_t *);                                                               ///<连接一个字符串到本类字符串的后面(UNICODE)
		void Strcat(const String &str){Strcat(str.wc_str());}                                       ///<连接一个字符串到本类字符串的后面

		void Strcat(const char *,int);                                                              ///<连接一个字符串到本类字符串的后面(ANSI)
		void Strcat(const wchar_t *,int);                                                           ///<连接一个字符串到本类字符串的后面(UNICODE)
		void Strcat(const String &str,int len){Strcat(str.wc_str(),len);}                           ///<连接一个字符串到本类字符串的后面
		void Strcat(const String &str,int start,int len)											///<连接一个字符串到本类字符串的后面
		{
			if(start<str.Length)
				Strcat(str.wc_str()+start,len);
		}

		void Sprintf(const char *,...);                                                             ///<对本类进行格式化赋值(ANSI)
		void CatSprintf(const char *,...);                                                          ///<产生一个格式化字符串并添加到本类的字符串后面(ANSI)

		void Sprintf(CCP,const char *,...);                                                         ///<对本类进行格式化赋值(ANSI)
		void CatSprintf(CCP,const char *,...);                                                      ///<产生一个格式化字符串并添加到本类的字符串后面(ANSI)

		void Sprintf(const wchar_t *,...);                                                          ///<对本类进行格式化赋值(UNICODE)
		void CatSprintf(const wchar_t *,...);                                                       ///<产生一个格式化字符串并添加到本类的字符串后面(UNICODE)

		//比较
		int Strcmp(const wchar_t *) const;                                                          ///<与另一个字符串比较
		int Strcmp(const String &) const;                                                           ///<与另一个字符串比较
		int Strcmp(const wchar_t *,int) const;                                                      ///<与另一个字符串比较
		int Strcmp(const String &,int) const;                                                       ///<与另一个字符串比较

		//转换至
		int    	ToAnsi(char *str=0,int=0,CCP ccp=ccpGBK)const;                                     	///<将当前字符串转换成ANSI格式
		int		ToAnsi(char **,CCP ccp=ccpGBK)const;		  										///<将当前字符串转换成ANSI格式
		int   	ToInt();                                                                            ///<将本类中的字符串转换成整型数值并返回
		uint	ToUInt();																			///<将本类中的字符串转换成整型数值并返回
		double  ToFloat();                                                                          ///<将本类中的字符串转换成浮点数值并返回

		//转换
		void LowerCase();                                                                           ///<将本类中的字母全部转为小写
		void UpperCase();                                                                           ///<将本类中的字母全部转为大写

		//编辑用函数
		void Insert(int,const wchar_t);                                                             ///<在指定位置插入一个字符
		void Insert(int,const wchar_t *);                                                           ///<在指定位置插入一个字符串
		void Insert(int,const String &);                                                            ///<在指定位置插入一个字符串
		void Delete(int,int);                                                                       ///<删除指定位置的指定个字符

		void Write(int,const wchar_t *,int len=-1);													///<在指定位置写入一个字符串
		void Write(int,const String &);			   													///<在指定位置写入一个字符串

		void Trim();                                                                                ///<删除字符串前后的空格
		void TrimLeft();                                                                            ///<删除字符串前面的空格
		void TrimRight();                                                                           ///<删除字符串后面的空格

		void TrimLeft(int n){Delete(0,n);}                                                          ///<删除字符串前面的若干字符
		void TrimRight(int n){Delete(Length-n,n);}                                                  ///<删除字符串后面的若干字符

		void Clip(int,int); 																		///<截取从指定位置开始的指定个字符
		void ClipLeft(int);                                                                         ///<从前方截取指定个字符
		void ClipRight(int);                                                                        ///<从结尾截取指定个字符

        wchar_t GetChar(int) const;
		void SetChar(int,wchar_t);

		wchar_t operator [](int n){return GetChar(n);}

		int StatChar(wchar_t) const;                                                                ///<统计字符串中某个字符的个数
		int StatLine() const;                                                                       ///<统计行数

		int FindChar(wchar_t) const;																///<返回当前字符串中指定字符开始的索引(从左至右)
		int FindChar(int,wchar_t) const;															///<返回当前字符串中指定字符开始的索引(从左至右)
		int FindRightChar(wchar_t) const;															///<返回当前字符串中指定字符开始的索引(从右至左)
		int FindString(const String &) const;                                                       ///<返回当前字符串中指定子串开始的索引
		bool ClearSubString(const String &);														///<清除当前字符串中指定子串

		void ReplaceChar(wchar_t,wchar_t);															///<替换字符
	};

	
	#define oper_over(type)	inline String operator + (const type val,const String &str) \
							{	\
								String new_str(val);	\
								\
								new_str.Strcat(str.wc_str());	\
								\
								return(new_str);	\
							}

//	oper_over(char);
//	oper_over(wchar_t);
//	oper_over(int);
//	oper_over(uint);
//	oper_over(int64);
//	oper_over(uint64);
//	oper_over(double);
	oper_over(char *);
	oper_over(wchar_t *);

	#undef oper_over

	/**
	* 将整型数转换成字符串
	* @param n 要转换的数值
	* @return 转换后的字符串
	*/
	inline String IntToStr   (int64  n){return(String(n));}                                         ///转换整型数到String

	/**
	* 将整型数转换成字符串
	* @param n 要转换的数值
	* @return 转换后的字符串
	*/
	inline String UIntToStr   (uint64 n){return(String(n));}                                        ///转换整型数到String

	/**
	* 将一个浮点数转换成字符串
	* @param n 要转换的数值
	* @return 转换后的字符串
	*/
	inline String FloatToStr (double n){return(String(n));}                                         ///转换浮点数到String

	/**
	* 该函数将一个计算资料容量值转换成字符串
	* 依次使用B,K,M,G,T
	*/
	void IntToSize(String &,unsigned __int64);

	/**
	* 转换ANSI字符串到UNICODE字符串
	* @param ccp 代码页
	* @param ws unicode字符串缓冲区
	* @param ws_size 缓冲区长度
	* @param as ansi字符串
	* @param as_size 字符串长度,-1表示全部
	* @return 是否转换成功
	*/
	bool AnsiToUnicode(CCP ccp,wchar_t *ws,int ws_size,char *as,int as_size=-1);

	class PropertyString
	{
		String *true_str;

		const int GetLength(){return true_str?true_str->Length:0;}

	public:	//事件

		DefEvent(void,OnGet,());
		DefEvent(void,OnSet,());

	public:	//属性

		Property<const int> Length;                                            						///<字符串长度虚拟变量

	public:

		PropertyString()
		{
			OnGet=NULL;
			OnSet=NULL;

			true_str=NULL;

			hglSetPropertyRead(Length,this,PropertyString::GetLength);
		}

		PropertyString(String &str)
		{
			OnGet=NULL;
			OnSet=NULL;

			true_str=&str;

			hglSetPropertyRead(Length,this,PropertyString::GetLength);
		}

		void Set(String &str)
		{
        	true_str=&str;
		}

		String *operator ->()const{return true_str;}

		#define oper_over(type) bool operator type (const PropertyString &str) const	\
								{ \
									if(!true_str)	\
									{	\
										if(!str.true_str)	\
											return 0 type 1;	\
										else	\
											return 0 type 0;	\
									}	\
									else \
									{	\
										if(!str.true_str)	\
											return 1 type 0;	\
										else	\
											return *true_str type *str.true_str;	\
									} \
								}

		oper_over(==);
		oper_over(!=);
		oper_over(> );
		oper_over(< );
		oper_over(>=);
		oper_over(<=);

		#undef oper_over

		#define ps_oper(type)	void operator = (type val){if(true_str)*true_str=val;SafeCallEvent(OnSet,());}	

		ps_oper(const char);
		ps_oper(const char *);
		ps_oper(const wchar_t);
		ps_oper(const wchar_t *);
		ps_oper(const String &);
		ps_oper(int);
		ps_oper(uint);
		ps_oper(int64);
		ps_oper(uint64);
		ps_oper(double);

		#undef ps_oper

		operator const wchar_t *()	const{SafeCallEvent(OnGet,());if(true_str)return true_str->wc_str();else return NULL;}
		operator int()				const{SafeCallEvent(OnGet,());if(true_str)return true_str->ToInt();else return 0;}
		operator double()			const{SafeCallEvent(OnGet,());if(true_str)return true_str->ToFloat();else return 0;}
		operator String &() 	const
		{
			SafeCallEvent(OnGet,());

			if(!true_str)
				PutError(L"读取了一个尚未赋值的PropertyString，这是一个严重错误，必须立即修正!");

			return *true_str;
		}
	};

	#define hglSetPropertyString(prop,str,pointer,get_func,set_func)	prop.Set(str);	\
																		SetEventCall(prop.OnGet,pointer,get_func);	\
																		SetEventCall(prop.OnSet,pointer,set_func);


	#define hglSetPropertyStringRead(prop,str,pointer,get_func)			prop.Set(str);	\
																		SetEventCall(prop.OnGet,pointer,get_func);


	#define hglSetPropertyStringWrite(prop,str,pointer,set_func)		prop.Set(str);	\
																		SetEventCall(prop.OnSet,pointer,set_func);
}
#endif//HGL_STRING_INCLUDE