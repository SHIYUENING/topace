#ifndef HGL_DevilVM_INCLUDE
#define HGL_DevilVM_INCLUDE

#include<hgl/Object.H>
#include<hgl/vm.h>
#include<hgl/Str.H>
namespace hgl
{
	class Stream;
	
	/**
	* 虚拟机状态
	*/
	enum DevilVMState
	{
		dvsRun,		//运行
		dvsPause,	//暂停
		dvsStop,	//停止
	};

	/**
	* 《魔鬼》虚拟机,一种微型脚本虚拟机.使用类ASM格式语法
	*/
	class DevilVM:public Object																		///《魔鬼》虚拟机类
	{
	protected:
	
		DevilVMState State;							   												///<虚拟机状态

	public:	//事件

		DefEvent(bool,OnTrueFuncCall,(const wchar_t *));											///<真实函数呼叫

	public:

		DevilVM(){State=dvsStop;OnTrueFuncCall=NULL;}
		virtual ~DevilVM(){};

		virtual bool MapProperty(const wchar_t *,void *)=0;						///<映射属性变量
		virtual bool MapFunc(const wchar_t *,void *)=0;							///<映射C函数
		virtual bool MapFunc(void *,const wchar_t *,void *)=0;					///<映射C函数,并传入一个对像
		virtual bool MapFunc(const wchar_t *,void *,void *)=0;					///<映射C++成员函数

		virtual bool AddScript(const wchar_t *,int=-1)=0;						///<添加脚本并编译

		virtual void Clear()=0;													///<清除所有模块和映射

		virtual bool Start(const wchar_t *)=0;									///<开始运行虚拟机
		virtual bool Start(const wchar_t *,const wchar_t *)=0;					///<开始运行虚拟机
		virtual bool Run(const wchar_t *func_name=0)=0;							///<运行虚拟机，如Start或End状态则从开始运行，Pause状态会继续运行
		virtual void Pause()=0;													///<暂停虚拟机，仅能从Run状态变为Pause，其它情况会失败
		virtual void Stop()=0;													///<终止虚拟机，从任何状况变为Start状态

		virtual bool Goto(const wchar_t *)=0;									///<跳转到指定位置
		virtual bool Goto(const wchar_t *,const wchar_t *)=0;					///<跳转到指定位置

		virtual bool GetCurrentState(String &,int &)=0;							///<取得当前状态						

		virtual bool SaveState(Stream *)=0;										///<保存状态
		virtual bool LoadState(Stream *)=0;										///<加载状态

	public:	//调试用函数

		#ifdef _DEBUG

		virtual void LogPropertyList()=0;										///<输出属性变量列表
		virtual void LogMapFuncList()=0;										///<输出映射函数列表
		virtual void LogScriptFuncList()=0;										///<输出脚本函数列表

		#endif//_DEBUG
	};

	/**
	* 创建一个《魔鬼》虚拟机引擎
	*/
	DevilVM *CreateDevilEngine();

	const int DevilScriptMinLength=sizeof(L"func main(){}");					///<《魔鬼》最小脚本长度
}//namespace hgl
#endif//HGL_DevilVM_INCLUDE
