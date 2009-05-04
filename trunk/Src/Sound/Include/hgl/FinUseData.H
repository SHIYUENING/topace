#ifndef HGL_FIN_USE_DATA_INCLUDE
#define HGL_FIN_USE_DATA_INCLUDE

#include<hgl/List.H>
namespace hgl
{
	template<typename F,typename T> struct FudItem
	{
		F flag;					//识别标识

		T data;					//数据

		FudItem<F,T> 	*prev,		//前一数据
						*next;		//后一数据
	};

	/**
	* 缓冲区管理模板(当缓冲区满时，将最长时间没有使用的清除)<br>
	* 现这个模板使用双头链表，每次添加或使用的数据会被移到链表的最前端。<br>
	* 这样使用率最低的数据会被存在链表的最末端，当缓冲区满时，最末端的数据将会被清除。
	*/
	template<typename F,typename T> class FinUseData:public Object									///缓冲区管理模板(以最终使用时间为基准)
	{
		typedef FinUseData<F,T> this_class;

	protected:

		FudItem<F,T> 	*start_item,	//首数据
						*end_item;		//尾数据

		int count,max_count;

				int GetCount(){return count;}

				int  GetMaxCount(){return max_count;}
		virtual void SetMaxCount(int);

	protected:

		virtual bool Create(const F &,T &);															///<创建数据
		virtual void Clear(const F &,T &);															///<清除数据

				void MoveToStart(FudItem<F,T> *);													///<移动某一个数据到最前面

				void Delete(FudItem<F,T> *);														///<清除某一个数据

            	void ClearEnd();																	///<清除最后一个数据

	public:	//属性

		Property<int> Count;        																///<当前缓冲区数据数量
		Property<int> MaxCount;                                                                     ///<当前缓冲区最大值

    public:

        FinUseData(int);
        virtual ~FinUseData();

		virtual FudItem<F,T> *	Add		(const F &,const T &);	  									///<增加一个数据
		virtual bool			Find	(const F &,T &,bool=true);									///<取得一个数据(如果没有不会自动创建)
		virtual bool 			Get		(const F &,T &,bool=true); 									///<取得一个数据(如果没有会自动创建)
				void 			Clear	();						  									///<清除所有数据

				void			DeleteByFlag(const F &);
				void 			DeleteByData(T &);
				bool			Update		(const F &,T &);										///<更新数据
	};
}

#include<hgl/template/FinUseData.CPP>
#endif//HGL_FIN_USE_DATA_INCLUDE
