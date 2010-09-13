#ifndef HGL_DATATYPE_INCLUDE
#define HGL_DATATYPE_INCLUDE

#include<hgl/platform/Platform.H>				// 平台定义
#include<hgl/Smart.H>

#define HGL_CONVER_TO_MEM_ALIGN(x)		((((x)+HGL_MEM_ALIGN-1)/HGL_MEM_ALIGN)*HGL_MEM_ALIGN)					//内存对齐转换宏

#ifndef NULL
#define NULL 0
#endif//

#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif//

#define SAFE_CLEAR(name)	{	\
								if(name)	\
								{	\
									delete name;	\
									name=NULL;	\
								}	\
							}

#define SAFE_CLEAR_ARRAY(name)	{	\
									if(name)	\
									{	\
										delete[] name;	\
										name=NULL;	\
									}	\
                            	}

#define CLEAR_OBJECT_ARRAY(name,num)	{	\
											int clear_object_array_number=num;	\
											\
											while(clear_object_array_number--)	\
												delete name[clear_object_array_number];	\
											\
											delete[] name;	\
											name=NULL;	\
										}

#define SAFE_CLEAR_OBJECT_ARRAY(name,num)	{	\
												if(name)	\
												{	\
													int safe_clear_object_array_number=num;	\
													\
													while(safe_clear_object_array_number--)	\
														delete name[safe_clear_object_array_number];	\
													\
													delete[] name;	\
													name=NULL;	\
												}	\
											}

#define FREE_OBJECT_ARRAY(name,num)	{	\
										int free_object_array_number=num;	\
										\
										while(free_object_array_number--)	\
											delete name[free_object_array_number];	\
										\
										hgl_free(name);	\
										name=NULL;	\
									}

#define SAFE_FREE_OBJECT_ARRAY(name,num)	{	\
												if(name)	\
													FREE_OBJECT_ARRAY(name,num);	\
											}

#define SAFE_RECREATE(name,code)	{	\
										if(name)	\
											delete name;	\
										\
										name=code;	\
									}

#define ARRAY_CALL(name,num,code)	{	\
										int array_call_number=num;	\
										\
										while(array_call_number--)	\
											name[array_call_number]->code;	\
									}

#define LOAD_FUNC(type,func)	type func(void *buf,int buf_size)	\
								{	\
									if(!buf||buf_size<=0)return 0;	\
									\
									MemStream ms(buf,buf_size);	\
									\
									return(func(&ms));	\
								}	\
								\
								type func(const String &filename)	\
								{	\
									FileStream fs;	\
									\
									if(fs.Open(filename))	\
										return(func(&fs));	\
									else	\
										return 0;	\
								}	\
								\
								type func(HAC *hac,const String &filename)	\
								{	\
									if(!hac)return 0;	\
									\
									Stream *s=hac->LoadFile(filename);	\
									\
									if(s)	\
									{	\
										type result=func(s);	\
										\
										delete s;	\
										return(result);	\
									}	\
									\
									return 0;	\
								}

#define SAVE_FUNC(type,func)	bool func(type data,void *buf,int buf_size)	\
								{	\
									if(!buf||buf_size<=0)return(false);	\
									\
									MemStream ms(buf,buf_size);	\
									\
									return(func(data,&ms));	\
								}	\
								\
								bool func(type data,const String &filename)	\
								{	\
									FileStream fs;	\
									\
									if(fs.Create(filename))	\
										return(func(data,&fs));	\
									else	\
										return(false);	\
								}	
//--------------------------------------------------------------------------------------------------
namespace hgl                           				///古月游戏开发库所使用的名字空间
{
	namespace info										//内部功能，请不要使用
	{
		void InitString();								//初始化标志字符串
		void ClearString();								//清除标志字符串
		void SetString(int,const wchar_t *);			//设置标志字符串

		void InitPointer();								//初始化标志指针
		void SetPointer(int,void *);					//设置标志指针
	}

	namespace info
	{
		/**
		* 古月标志字串枚举
		* @see GetString
		*/
		enum_uint(HGLFlagString)
		{
			hfsNone=0,				///<起始定义，无意义

			hfsName,              	///<中文名称
			hfsEnglishName,         ///<英文名称
			hfsVersion,             ///<版本字串

			hfsAuthor,              ///<开发者

			hfsCMGDKPath,			///<CMGDK路径
			hfsPlugInPath,			///<CMGDK插件路径
			hfsGUIPath,				///<CMGDK GUI路径
			hfsStartPath,			///<程序启动路径
			
			hfsOSPath,				///<用户操作系统
			hfsDesktopPath,			///<用户桌面路径
			hfsTempPath,			///<用户临时文件路径
			hfsUserDataPath,		///<用户文件路径(我的数据),(Win2000/XP/2003:Application Data,WinVista/2008/7:AppData\Roaming)
			hfsUserProgramPath,		///<用户程序路径(开始菜单)

			hfsAppFileName,			///<当前程序文件名

			hfsEnd,					///<结束定义，无意义
		};

		const wchar_t *GetString(HGLFlagString);                                                    ///<取得古月标记字符串

		/**
		* 古月标志指针枚举
		* @see GetPointer
		*/
		enum_uint(HGLFlagPointer)
		{
			hfpNone=0,				///<起始定义，无意义

			hfpSII,					///<SystemInitInfo *
			hfpApplication,			///<应用程序类(BaseApplication *)
            hfpWindow,              ///<窗口管理类(Window *)
			hfpFont,				///<缺省字体(TileFont *)
			hfpFlow,				///<当前活动流程(FlowObject *)
			hfpRootFlowControl,		///<根流程控制器(FlowControl *);

			hfpEnd					///<结束定义，无意义
		};

		const void *GetPointer(HGLFlagPointer);
	}
	
	using namespace info;
}//namespace hgl

//#ifndef _DEBUG

//	#define hgl_malloc(size)		_aligned_malloc(size,HGL_MEM_ALIGN)
//	#define hgl_realloc(ptr,size)	_aligned_realloc(ptr,size,HGL_MEM_ALIGN)
//	#define hgl_free				_aligned_free
//
//	#include<malloc.h>
/*
#else

	void *hgl_log_malloc(unsigned int);
	void *hgl_log_realloc(void *,unsigned int);
	void  hgl_log_free(void *);

	void *hgl_log_malloc(unsigned int,const char *,const char *,unsigned long);
	void *hgl_log_realloc(void *,unsigned int,const char *,const char *,unsigned long);
	void  hgl_log_free(void *,const char *,const char *,unsigned long);

	#define hgl_malloc(size) 		hgl_log_malloc(size,__FILE__,__FUNC__,__LINE__)
	#define hgl_realloc(ptr,size)	hgl_log_realloc(ptr,size,__FILE__,__FUNC__,__LINE__)
	#define hgl_free(ptr)           hgl_log_free(ptr,__FILE__,__FUNC__,__LINE__)

	void * operator new(unsigned int s){return hgl_log_malloc(s);}
	void * operator new[](unsigned int s){return hgl_log_malloc(s);}
	void operator delete(void *p){hgl_log_free(p);}
	void operator delete[](void *p){hgl_log_free(p);}
#endif//_DEBUG
*/
//--------------------------------------------------------------------------------------------------
#endif//HGL_DATATYPE_INCLUDE;
