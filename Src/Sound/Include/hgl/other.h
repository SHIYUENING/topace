#ifndef HGL_OTHER_INCLUDE
#define HGL_OTHER_INCLUDE

#include<hgl/file.h>
#include<hgl/memex.h>
#include<hgl/Str.H>

namespace hgl   //系统对话框
{
//	bool SelectColorDialog(uint8 &,uint8 &,uint8 &);                        						//对话框: 选择一个颜色
//	bool SelectFontDialog(wchar_t *,int);															//对话框: 选择一个字体

//	bool SelectFolderDialog(wchar_t *,int);															//对话框: 选择一个文件夹

	bool OpenFileDialog(wchar_t *,int,const wchar_t *filter=NULL,int=0);							//对话框: 打开一个文件
	bool SaveFileDialog(wchar_t *,int,const wchar_t *filter=NULL,int=0,const wchar_t *def_ext=0);	//对话框: 保存一个文件
}//namespace hgl

namespace hgl
{
	namespace ansi
	{
		char *	strstr	(char *,const char *);														///<在一个字符串中查找某个字符串
	}

	/**
	* 这些函数一部分与标准的C库函数功能相同，但提供它们是为了更高的安全性和易用性。<br>
	* 该名字空间已被自动启动，所以无需手动启用。仅在无法与其它SDK同名函数区分时，需手动标识名字空间。
	*/
	namespace utf16	///字符串相关处理函数所占名字空间
	{
		int			strlen	(const wchar_t *);														///<计算字符串长度
		void		strcpy	(wchar_t *,const wchar_t *);											///<复制字符串
		void		strcpy	(wchar_t *,const wchar_t *,int);										///<复制字符串，并指定最大长度
		void		strcat	(wchar_t *,const wchar_t);                                              ///<复制连接字符
		void		strcat	(wchar_t *,const wchar_t *);											///<复制连接字符串
		void		strcat	(wchar_t *,const wchar_t *,int);										///<复制连接字符串
		wchar_t *	strchr	(const wchar_t *,const wchar_t);										///<在字符串中查找某个字符
		wchar_t *	strchr	(const wchar_t *,const wchar_t,int);									///<在字符串中查找某个字符
		wchar_t *	strrchr	(const wchar_t *,const wchar_t);										///<从结束开始向前查找某个字符
		int			strcmp	(const wchar_t *,const wchar_t *);										///<比较字符串
		int			strcmp	(const wchar_t *,const wchar_t *,int);									///<比较字符串
		int			stricmp	(const wchar_t *,const wchar_t *);										///<比较字符串(英文不区分大小字)
		int			stricmp	(const wchar_t *,const wchar_t *,int);									///<比较字符串(英文不区分大小字)
		wchar_t *	strstr	(wchar_t *,const wchar_t *);											///<在一个字符串中查找某个字符串
		void		sprintf	(wchar_t *,const wchar_t *,...);										///<格式化字符串

		void ReplaceExtName(const wchar_t *,wchar_t *,const wchar_t *);								///<替换扩展名
		void ReplaceExtName(wchar_t *,const wchar_t *);												///<替换扩展名

		wchar_t *ReplaceChar(wchar_t *,const wchar_t,const wchar_t);                                ///<替换一个字符串中的某个字符

		wchar_t *UpperString(wchar_t *);                                                            ///<将字符串中的小写字母全部转为大写
		wchar_t *LowerString(wchar_t *);                                                            ///<将字符串中的大写字母全部转为小写

		void UpperString(const wchar_t *,wchar_t *);                                                ///<将字符串中的小写字母全部转为大写
		void LowerString(const wchar_t *,wchar_t *);                                                ///<将字符串中的大写字母全部转为小写

		wchar_t *CreateCopy(const wchar_t *,int=-1);												///<创建一个复制

		int StatChar(wchar_t *,wchar_t);                                                            ///<统计在字符串中某个字符的出现次数
		int StatLine(wchar_t *);                                                                    ///<统计字符串的行数

		int 	wtoi	(const wchar_t *);															///<转换一个字符串到int型
		uint 	wtou	(const wchar_t *);															///<转换一个字符串到uint型
		int64 	wtoi64	(const wchar_t *);															///<转换一个字符串到int64型
		uint64 	wtou64	(const wchar_t *);															///<转换一个字符串到uint64型
		float	wtof	(const wchar_t *);															///<转换一个字符串到float型
		double	wtod	(const wchar_t *);															///<转换一个字符串到double型
		bool 	wtob	(const wchar_t *);															///<转换一个字符串到bool型

		wchar_t *itow(wchar_t *,int,int64);															///<转换一个int型数值到字符串
		wchar_t *utow(wchar_t *,int,uint64);														///<转换一个uint型数值到字符串
		wchar_t *ftow(wchar_t *,int,double);														///<转换一个double型数值到字符串

		bool __inline isdigit(wchar_t ch){return((ch>=L'0'&&ch<=L'9')?true:false);}

		void ConvertNumber(wchar_t *,uint64);
	}
	using namespace utf16;
}//namespace hgl

namespace hgl   //校验/加密算法
{
	struct MD5Context;

	typedef uint8 MD5Code[16];				//MD5编码
	
	void MD5Init(struct MD5Context *ctx);       
	void MD5Update(struct MD5Context *ctx, unsigned char const *buf, unsigned len);
	void MD5Final(unsigned char digest[16], struct MD5Context *ctx);

	void CountMD5(const void *,uint32,MD5Code &);
	bool GetMD5(const wchar_t *,MD5Code &);

	void StrToMD5(const wchar_t *,MD5Code &);
	void MD5ToStr(const MD5Code &,wchar_t *);

	uint CountAdler32(uint,const uchar *,uint);

	void CountSHA1(uint8 *,uint32,uint8 [20]);

	void AesEncrypt(uint8 [16],uint8 *,int);					//AES加密
	void AesDecrypt(uint8 [16],uint8 *,int);					//AES解密

	void RC4Encrypt(uint8 *,int,uint8 *,int);

	void OverflowEncrypt(void *,void *,int,void *,int);			//溢出加密(轻度加密)
	void OverflowDecrypt(void *,void *,int,void *,int);			//溢出解密
}//namespace hgl

namespace hgl   //排序,查找
{
	typedef DefEvent(int,COMPFUNC,(void *,void *,uint));

    void QuickSort(void *,int,int,COMPFUNC);                                                        //快速排序
	void HeapSort(void *,int,int,COMPFUNC);                                                      	//堆排序

	int DichFind(void *,int,int,void *);                                                            //2分查找
	int DichFind(void *,int,int,void *,COMPFUNC);                                                   //2分查找
}//namespace hgl

namespace hgl   //数学
{
				double  fm_atan2	(double y, double x);
				double  fm_cos		(double x);
				double  fm_cosh		(double x);
				double  fm_exp		(double x);
				double  fm_fabs		(double x);
				double  fm_frexp	(double x, int *exponent);
				double  fm_hypot	(double x, double y);
				double  fm_ldexp	(double x, int exponent);
				double  fm_log		(double x);
				double  fm_log10	(double x);
				double  fm_sin		(double x);
				double  fm_sinh		(double x);
				double  fm_sqrt		(double x);
				double  fm_tan		(double x);
				double  fm_tanh		(double x);

				void	fm_sincos	(double a, double *x, double *y);

	__inline 	double	fm_acos		(double x){return fm_atan2(fm_sqrt(1 - x*x), x);}
	__inline 	double	fm_asin		(double x){return fm_atan2(x, fm_sqrt(1 - x*x));}
	__inline 	double	fm_atan		(double x){return fm_atan2(x, 1);				}

				double	fm_acosh	(double x);
				double	fm_asinh	(double x);
				double	fm_atanh	(double x);
}//namespace hgl

namespace hgl	//数值
{
    uint32 	FastRand();																				///<快速产生一个随机数

	/**
    * 产生一个随机数，并指定上限。
	* @param max_value 上限值
	* @return 随机值,<max_value
	*/
	uint32 	__inline FastRand(uint32 max_value)														///<快速产生一个随机数，并指定上限
	{
		return FastRand()%max_value;
	}

	/**
	* 在指定范围内产生一个随机值，并指定精度
	* @param v1 最小值
	* @param v2 最大值
	* @param p 精度,默认为1
	* @return 随机值
	*/
	int 	__inline FastRand(int v1,int v2,int p=1)												///<快速产生一个随机数(指定范围，并指定精度)
	{
		if(v1<v2)
			return v1+(FastRand()%((v2-v1)/p+1))*p;
		else
			return v2+(FastRand()%((v1-v2)/p+1))*p;
	}

	/**
	* 在指定范围内产生一个随机值，并指定精度
	* @param v1 最小值
	* @param v2 最大值
	* @param p 精度
	* @return 随机值
	*/
	double 	__inline FastRand(double v1,double v2,double p)											///<快速产生一个随机数(指定范围，并指定精度)
	{
		if(v1<v2)
		{
			int pos=(v2-v1)/p+1;
			int val=FastRand()%pos;

			return v1+val*p;
		}
		else
		{       
			int pos=(v1-v2)/p+1;
			int val=FastRand()%pos;

			return v2+val*p;
		}
    }
}//namespace hgl

namespace hgl   //时间
{
	/**
	* 时间相关函数和类的名字空间<br>
	* 注意：GetTime/GetMicroTime/GetDoubleTime三种时间不可以混用
	*/
	namespace time		///时间名字空间
	{
		uint64 GetTime();																			///<取得当前时间(单位千分之一秒)
		uint64 GetMicroTime();																		///<取得当前时间(单位百万分之一秒)
		double GetDoubleTime();																		///<取得当前时间(双精度，单位秒)
	}

    using namespace time;
}//namespace hgl

namespace hgl   //其它
{
	void SetExpendString(const String &,const String &);											///<设置特殊扩展字符串
	void ClearExpendString(const String &);															///<清除特殊扩展字符串
	bool GetExpendString(const String &,String &);													///<取得特殊扩展字符串

	bool ConvertExpendString(const String &,String &);												///<转换特殊扩展字符串

	/**
	* 与本地操作系统相关功能函数的名字空间
	*/
	namespace os		///<操作系统相关功能名字空间
	{
		bool GetOSVersion(int &,int &);																///<取得操作系统版本

		void PopupWebBrowser(const wchar_t *);                                                      ///<弹出网页浏览器
		void PopupEmailClient(const wchar_t *,const wchar_t *sub=NULL);                             ///<弹出电子邮件客户端

		void CreateTempFileName(String &);															///<创建临时文件名称

		void CopyTextToClipboard(const wchar_t *);													///<复制字符串到剪贴板
		const wchar_t *GetTextFromClipboard();														///<从剪贴板取得字符串

		bool CreateShortCut(const wchar_t *,const wchar_t *,const wchar_t *w=0,const wchar_t *p=0,const wchar_t *icon=0);	///<创建快捷方式

//        void *GetFileIcon(const wchar_t *,int &,int &,int &);										///<取得文件的系统图标(仅Vista以上可用)
	}

	using namespace os;

	class Stream;

	bool DiscCheck(Stream *,const wchar_t *,const wchar_t *);										///<盘片检测
}//namespace hgl
#endif//HGL_OTHER_INCLUDE
