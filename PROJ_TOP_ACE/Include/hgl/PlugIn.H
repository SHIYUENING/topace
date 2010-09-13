#ifndef HGL_PLUGIN_INCLUDE
#define HGL_PLUGIN_INCLUDE
//--------------------------------------------------------------------------------------------------
#include<hgl/DataType.H>
using namespace hgl;

/**
* 插件类型枚举
*/
enum PlugInType			///插件类型枚举
{
	pitNormal=0,		///<普通插件

	pitLog,				///<日志
	pitPlatform,		///<平台
	pitOpenGL,			///<OpenGL
	pitOpenAL,			///<OpenAL

	pitEnd
};

typedef void 		(__cdecl *InitPlugInPROC)();										//初始化插件
typedef void 		(__cdecl *ClosePlugInPROC)();										//关闭插件

typedef uint32	    (__cdecl *GetPlugInVersionPROC)();					                //取得插件版本号
typedef wchar_t *   (__cdecl *GetPlugInIntroPROC)();				                    //取得插件介绍信息

typedef bool		(__cdecl *GetPlugInInterfacePROC)(uint32,void *);			        //取得插件接口
typedef void	    (__cdecl *SetPlugInInterfacePROC)(void *,void *);	                //设置插件接口

typedef bool		(__cdecl *LoadInterfaceByNamePROC)(const wchar_t *,uint32,void *);	//取得接口
typedef bool		(__cdecl *LoadInterfaceByIndexPROC)(uint32,uint32,void *);			//取得接口

#ifndef __MAKE_PLUGIN__
#include<hgl/Str.H>
#include<hgl/IndexData.H>
#include<hgl/ExternalModule.H>
#include<hgl/LogInfo.H>
#include<string.h>
namespace hgl
{
	/**
	* 插件基类
	*/
	class PlugIn                                                                                    ///插件
	{
	protected:

		int RefCount;    

		uint ver;
		wchar_t *intro;

	public:

		PlugInType Type;																			///<插件类型

		String Name;                                                                                ///<插件名称
		String FileName;                                                                            ///<插件文件名

		uint GetVersion(){return ver;}																///<插件版本
		wchar_t *GetIntro(){return intro;}															///<插件介绍

	public:

		PlugIn();
		virtual ~PlugIn();

		virtual void AddRef(){RefCount++;}
		virtual int Release(){return(--RefCount);}

		GetPlugInInterfacePROC GetInterface;                                             			///<取得接口函数指针
	};

	/**
	* 外部插件
	*/
	class ExternalPlugIn:public PlugIn                                                              ///外部插件
	{
	protected:

		ExternalModule module;                                                                      ///<插件模块

		bool Load();

	public:

		ExternalPlugIn(const wchar_t *);
		virtual ~ExternalPlugIn();
	};

	void InitPlugIn();																				///<初始化插件管理
	void ClearAllPlugIn();                                                                          ///<清除所有插件

	void SetPlugIn(PlugIn *,PlugInType);															///<设置一个插件

	PlugIn * 	__cdecl LoadPlugIn(const wchar_t *,PlugInType=pitNormal);                           ///<加载一个插件
	void 		__cdecl UnloadPlugIn(PlugIn *);                                                     ///<释放一个插件

	void * 		__cdecl LoadInterface(const wchar_t *,int);											///<加载一个插件，并取得指定接口
	//--------------------------------------------------------------------------------------------------
	template<typename T> struct PlugInFlagData
	{
		String flag;
		T data;

		PlugIn *pi;
	};

	template<typename T>
	T *CheckPlugIn(_IndexObject<String,T,PlugInFlagData<T *> > &PIM,const String &front,uint ver,const String &name)
	{
		T *iface;

		if(PIM.Get(name,iface))					//接口可能本身就为NULL,所以不能直接用PIM[name]
			return(iface);

		PlugIn *pi=LoadPlugIn(front+L"."+name);	//加载插件

		if(pi)	//加载插件成功
		{
			if(pi->GetVersion()<ver)
			{
				PutError(L"插件<%s>的版本太低！",name.wc_str());
			}
			else
			{
				iface=new T;

				hgl_memset(iface,0,sizeof(T));

				if(pi->GetInterface(ver,iface))
				{
					PIM.Add(name,iface)->pi=pi;

					return(iface);
				}
				else
				{
                	delete iface;

					PutError(L"获取插件<%s>接口<ver:%d>失败!",name.wc_str(),ver);
				}
			}
		}

		PIM.Add(name,NULL);

		if(pi)
			UnloadPlugIn(pi);

		PutError(L"加载插件<%s>失败!",name.wc_str());
		return(NULL);
	}

	void RegistryPIMClear(void (*)());		//注册清除函数

	#define	PlugInManage(name,ver) 	static _IndexObject<String,name##PlugInInterface,PlugInFlagData<name##PlugInInterface *> > name##Interface;	\
									\
									void name##PlugInClear()	\
									{	\
										int n=name##Interface.Count;	\
										\
										if(!n)return;	\
										\
										DebugLog(0,"Clear<" #name "> Plug-Ins,number=%d.",n);	\
										\
										while(n--)	\
										{	\
											PlugInFlagData<name##PlugInInterface *> *pifd=name##Interface.GetItem(n);	\
											\
											if(pifd)	\
												UnloadPlugIn(pifd->pi);	\
										}	\
										\
										name##Interface.Clear();	\
									}	\
									\
									name##PlugInInterface *name##InterfaceCheck(const String &plugin_name)	\
									{	\
										static bool first=true;	\
										\
										if(first)	\
										{	\
											first=false;	\
											\
											DebugLog(0,"Registry <" #name "> Plug-In Manager.");	\
											RegistryPIMClear(name##PlugInClear);	\
										}	\
										\
										return CheckPlugIn<name##PlugInInterface>(name##Interface,#name,ver,plugin_name);	\
									}
}//namespace hgl
#endif//__MAKE_PLUGIN__
#endif//HGL_PLUGIN_INCLUDE
