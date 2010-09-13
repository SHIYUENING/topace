#ifndef HGL_ANGEL_VM_INCLUDE
#define HGL_ANGEL_VM_INCLUDE

#include<hgl/vm.h>
#include<hgl/List.H>
#include<hgl/Stream.H>
namespace hgl
{
	struct AngelPlugInsInterface;

	/**
	* 《天使》虚拟机，这个虚拟机提供对脚本的运行控制，以及与其它程序的交接<br>
	* 需要注意的是，天使支持在多线程中多个线程同时调用一个脚本，每个线程都将有自己的运行上下文控制，互不干涉。<br>
	* 本虚拟机使用改进版的《天使》脚本引擎，仅支持UNICODE脚本，并支持__closure形式呼叫<br>
	* 《天使》脚本引擎官方网站: http://www.angelcode.com/angelscript
	*/
	class AngelVM                                                                                   ///《天使》虚拟机类
	{
	protected:

		AngelPlugInsInterface *ScriptPlugIn;

		void *vm;

		void InfoOut(int,int,int,wchar_t *,wchar_t *);

	public:

		class Context                       //运行上下文控制类
		{
        	friend class AngelVM;
            
        private:

			AngelVM *Super;

			AngelPlugInsInterface *ScriptPlugIn;

			void *vm;
			void *context;

		public:

			Context();
			Context(AngelVM *,AngelPlugInsInterface *,void *,void *);
			~Context();

			bool Run();                     //运行
			void Pause();                   //暂停运行
			void Stop();                    //停止运行
		};

		class Object                        //对象
		{
        	friend class AngelVM;
            
        private:

			AngelVM *Super;

			AngelPlugInsInterface *ScriptPlugIn;

			void *vm;

			wchar_t *object_name;

		public:

			Object(){vm=NULL;}
			Object(AngelVM *,AngelPlugInsInterface *,void *,wchar_t *);
			~Object();

			bool MapProperty(wchar_t *,int);
			bool MapFunc(wchar_t *,void *);
		};

		class Module                        //模块
		{
        	friend class AngelVM;
            
        private:

			AngelVM *Super;

			AngelPlugInsInterface *ScriptPlugIn;

			void *vm;

			wchar_t *module_name;

		public:

			Module(){vm=NULL;}
			Module(AngelVM *,AngelPlugInsInterface *,void *,wchar_t *);
			~Module();

			void Restart();                             //复位模块
			void Clear();                               //清除内容

			bool AddScript(wchar_t *,wchar_t *,int=-1); //添加脚本
			bool Build();                               //编译脚本

			bool RunFunc(wchar_t *);                    //运行指定的函数
			bool RunScript(wchar_t *);                  //运行指定的脚本

			AngelVM::Context *CreateContext(wchar_t *); //创建一个可控制运行的上下文

            //以下为编译后的节字码操作函数
            void SaveToStream(Stream *);                                                        	///<保存虚拟机中的程序到流
            void LoadFromStream(Stream *);                                                      	///<加载流中的程序到虚拟机
		};

	public:	//属性

		ObjectList<AngelVM::Object> OList;
		ObjectList<AngelVM::Module> MList;     
		ObjectList<AngelVM::Context> CList;

	public:	//事件

		DefEvent(void,OnInfoOut,(int,int,int,const wchar_t *,const wchar_t *));						///<虚拟机信息输出事件函数

	public:	//方法

		AngelVM();
		~AngelVM();

		AngelVM::Module *CreateModule(wchar_t *);                                                	///<创建一个模块

		bool MapProperty(wchar_t *,void *);                                                      	///<设置全局属性(变量)映射
		bool MapFunc(wchar_t *,void *);                                                          	///<设置全局函数映射(映射一个C函数)
		bool MapFunc(wchar_t *,void *,void *);														///<设置全局函数映射(映射一个C++函数)

		AngelVM::Object *CreateObjectMap(wchar_t *,int,void *init=NULL,void *clear=NULL);        	///<创建一个对象映射
	};
}//namespace hgl
#endif//HGL_ANGEL_VM_INCLUDE
