#ifndef HGL_RES_MANAGE_INCLUDE
#define HGL_RES_MANAGE_INCLUDE

#include<hgl/Object.H>
#include<hgl/IndexData.H>
#include<hgl/HAC.H>
namespace hgl
{
	template<typename F,typename T> struct RefFlagData
	{
		F flag;
		T *data;
		int count;
	};

	/**
	* 资源管理器,它没有缓冲管理，仅仅是管理数据，并保证不会被重复加载
	*/
	template<typename F,typename T> class ResManage:public Object
	{
	protected:

		typedef RefFlagData<F,T> ResItem;

		_IndexData<F,T *,ResItem> items;

		void ReleaseBySerial(int);

	protected:

		virtual T *Create(const F &)=0;			///<资源创建虚拟函数
		virtual void Clear(T *);				///<资源释放虚拟函数(缺省为直接delete对象)

	public:

		virtual ~ResManage();

		void Clear();

		T *Find(const F &);
		T *Get(const F &);

		void Release(const F &);
		void Release(T *);						 
	};

	template<typename T> class ResManageByName:public ResManage<String,T>
	{
	protected:

		virtual T *Create(const String &);
	};

	template<typename T> class ResManageHAC:public ResManageByName<T>
	{
    	bool hac_private;

		HAC *hac_data;

		HAC *GetHac(){return hac_data;}
		void InitPrivate();

	public:

		Property<HAC *> hac;

	public:

		ResManageHAC(HAC *);
		ResManageHAC(const String &);
		virtual ~ResManageHAC();

	protected:

		virtual T *Create(const String &);
	};
}//namespace hgl
#include<hgl/Template/ResManage.CPP>
#endif//HGL_RES_MANAGE_INCLUDE
