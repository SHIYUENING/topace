#ifndef HGL_INDEX_DATA_INCLUDE
#define HGL_INDEX_DATA_INCLUDE

#include<hgl/List.H>
namespace hgl
{
	class Stream;
	class TDFNode;

	template<typename F,typename T> struct IndexFlagData
	{
		F flag;
		T data;
	};

	/**
	* 索引数据模板
	*/
	template<typename F,typename T,typename data_struct> class _IndexData:public _Object
	{
	public:	//类型

		typedef data_struct DataStruct;

	protected:

		ObjectList<DataStruct> data_list;

		typedef _IndexData<F,T,DataStruct> this_calss;

	protected:
	
		int FindPos(const F &)const;

		int	GetCount(){return data_list.Count;}														///<取得数据总量

	public:	//属性

    	Property<int> Count;                                                                        ///<数据个数

    public: //事件

		bool (*OnSaveToStream)(Stream *,const F &,T &);												///<保存到流事件
		bool (*OnLoadFromStream)(Stream *,F &,T &);													///<从流加载事件

	public:	//方法

		_IndexData();
		virtual ~_IndexData(){};

		DataStruct *	Add(const F &,const T &);													///<添加一个数据
				T &  	Add(const F &);																///<添加一个数据
				void    Add(DataStruct *);															///<添加一个数据
				int		Find(const F &)const;														///<查找数据是否存在
				int		FindByData(const T &)const;													///<查找数据是否存在
				bool	Get(const F &,T &)const;													///<取得数据
		virtual	void	Set(const F &,T &);															///<设置数据(如不存在则创建)
		virtual bool	Unlink(const F &,T &);														///<将指定数据从列表中移除，但并不删除这个数据
		virtual bool	Unlink(const T &);															///<将指定数据从列表中移除，但并不删除这个数据
		virtual void 	DeleteByIndex(const F &);													///<删除一个数据(按索引)
		virtual void 	DeleteByData(T &);															///<删除一个数据(按数据)
		virtual void	DeleteBySerial(int);														///<删除一个数据(按序号)
		virtual	bool 	Change(const F &,T &);														///<更改一个数据的内容(如不存在则更改失效)
		virtual void 	Clear();																	///<清除所有数据

		DataStruct *	GetItem(int n)const{return data_list[n];}									///<取指定索引的数据
				bool 	Get(int,F &,T &)const;														///<取指定索引的数据

				bool	SaveToStream(Stream *)const;												///<保存到流
				bool	LoadFromStream(Stream *);													///<从流加载

				void	operator=(const _IndexData<F,T,DataStruct> &);								///<操作符重载，复制一个列表
	};

	template<typename F,typename T> class IndexData:public _IndexData<F,T,IndexFlagData<F,T> >
	{
	public:

    	typedef IndexFlagData<F,T> IndexItem;

	public:

		virtual ~IndexData(){};
	};

	template<typename F,typename T,typename data_struct> class _IndexObject:public _IndexData<F,T *,data_struct>
	{
		int FindByData(T *)const;

	public:

		_IndexObject(){};
		virtual ~_IndexObject(){Clear();}

		T *	 Create(const F &);
		void Set(const F &,T *);
		void DeleteByIndex(const F &);
		void DeleteByData(T *);
		void DeleteBySerial(int);
		bool Change(const F &,T *);
		void Clear();
	};

	template<typename F,typename T> class IndexObject:public _IndexObject<F,T,IndexFlagData<F,T *> >
	{
	public:

		virtual ~IndexObject(){};

		T *operator[](const F &flag)const
		{
			T *obj;

			if(Get(flag,obj))
				return(obj);
			else
            	return(NULL);
		};
	};
}//namespace hgl
#include<hgl/Template/IndexData.CPP>
#endif//HGL_INDEX_DATA_INCLUDE
