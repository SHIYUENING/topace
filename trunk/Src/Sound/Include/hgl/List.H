#ifndef HGL_LIST_INCLUDE
#define HGL_LIST_INCLUDE

#include <hgl/Object.H>
#include <hgl/list.h>
#include <hgl/memex.h>
#include <hgl/other.h>
#include <hgl/loginfo.h>
namespace hgl
{
	/**
	* List类用于保存数据列表。可以在列表中添加、删除、查找、访问和排序数据。
	*
	* 注：这个类还在测试中，请不要修改这个类的源代码，如有修改意见，请致电作者。
	*/
	template <typename T> class List:public _Object                                                 ///列表处理类
	{
	protected:

		int count;
		T *items;

		int GetCount(){return count;}
		void SetCount(int);
		T *GetData(){return items;}                                                                 ///<提供原始数据项

	public:

		typedef DefEvent(int,ListCompFunc,(T &,T &));

		ListCompFunc lcf;

		virtual int CompFunc(void *,void *,uint);

	public: //属性

		Property<int> Count;                                                                        ///<数据对象个数
		Property<T *> Data;                                                                         ///<直接访问数据内存指针

	public: //方法

		List();                                                                                     ///<本类构造函数
		virtual ~List();                                                                            ///<本类析构函数

		virtual int  Add(const T &);
		virtual void Clear();
		virtual bool Delete(int);
		virtual	bool Delete(const T &);
		virtual	void Exchange(int,int);
		virtual void Insert(int,const T &);
		virtual	void Move(int,int);
		virtual int  Find(const T &);

            	void DeleteClear();

		virtual void operator += (const T &obj){Add(obj);}
		virtual void operator << (const T &obj){Add(obj);}

		T &Get(int)const;
		void Set(int,const T &);

		virtual void Sort(ListCompFunc);

		T &operator[](int n)const{return Get(n);}
	};
}

#include<hgl/Template/List.CPP>
//--------------------------------------------------------------------------------------------------
namespace hgl
{
	/**
	* 对象列表处理类与标准列表处理类的区别在于它对数据生成/清除时会多一遍new/delete操作
	*/
	template <typename T> class ObjectList:public List<T *>                                         ///对象列表处理类
	{
		virtual void SetCount(int);

	public:

		typedef DefEvent(int,ObjectListCompFunc,(T *,T *));

		ObjectListCompFunc olcf;

		virtual int CompFunc(void *,void *,uint);

	public: //方法

		ObjectList();
		virtual ~ObjectList();

		virtual T *		Append();
		virtual T *		Insert(int);
				void 	Insert(int,T *);

		virtual void 	Clear();

		virtual bool 	Unlink(int);
		virtual bool 	Unlink(T *);
		virtual void 	UnlinkAll();

		virtual bool 	Delete(int);
		virtual bool 	Delete(T *&);
		virtual void 	DeleteAll();

		virtual void 	Sort(ObjectListCompFunc);
	};
}

#include <hgl/Template/ObjectList.CPP>
//--------------------------------------------------------------------------------------------------
#endif//HGL_LIST_INCLUDE
