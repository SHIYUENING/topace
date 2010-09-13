#ifndef HGL_LIST_INCLUDE
#define HGL_LIST_INCLUDE

#include<hgl/Object.H>
#include<hgl/List.H>
#include<hgl/MemEx.H>
#include<hgl/Other.H>
#include<hgl/ThreadMutex.H>
#include<hgl/LogInfo.H>

#if defined(__BORLANDC__)||defined(__TURBOC__)||defined(__CODEGEARC__)
#pragma warn -8022						//使hides vitual function警告无效
#endif//

namespace hgl
{
	class Stream;

	/**
	* List类用于保存数据列表。可以在列表中添加、删除、查找、访问和排序数据。
	*/
	template <typename T> class List:public _Object                                                 ///列表处理类
	{
	protected:

		int count;
		T *items;

		int GetCount(){return count;}
		virtual void SetCount(int);
		T *GetData(){return items;}                                                                 ///<提供原始数据项
		int GetBytes(){return count*sizeof(T);}

	public:

		typedef DefEvent(int,ListCompFunc,(T &,T &));

		ListCompFunc lcf;

		virtual int CompFunc(void *,void *,uint);

	public: //属性

		Property<int> Count;                                                                        ///<数据对象个数
		Property<T *> Data;                                                                         ///<直接访问数据内存指针
		Property<int> Bytes;																		///<数据字节数

    public: //事件

		bool (*OnSaveToStream)(Stream *,const T &);													///<保存到流事件
		bool (*OnLoadFromStream)(Stream *,T &);													    ///<从流加载事件

	public: //方法

		List();                                                                                     ///<本类构造函数
		List(const List<T> &lt){operator=(lt);}														///<本类构造函数
		virtual ~List();                                                                            ///<本类析构函数

		virtual int  Add(const T &);																///<增加一个数据
		virtual int  Add(const T *,int n);															///<增加一批数据
		virtual void Clear();																		///<清除所有数据
		virtual int  Find(const T &);																///<查找指定数据的索引
		virtual bool Delete(int);																	///<删除指定索引的数据
		virtual	bool Delete(const T &);																///<删除一个指定数据
		virtual void Delete(const T *,int);															///<删除一批指定的数据
		virtual	void Exchange(int,int);																///<根据索引交换两个数据
		virtual void Insert(int,const T &);															///<在指定索引处插入一个数据
		virtual	void Move(int,int);																	///<移动一个数据到移指索引处

            	void DeleteClear();																	///<清除所有数据并全部调用delete

		virtual void operator = (const List<T> &);													///<操作符重载复制一个列表

		virtual void operator += (const T &obj){Add(obj);}											///<操作符重载添加一个数据
		virtual void operator << (const T &obj){Add(obj);}											///<操作符重载添加一个数据
		virtual void operator -= (const T &obj){Delete(obj);}										///<操作符重载删除一个数据

		virtual bool SaveToStream(Stream *,int=0,int=0)const;										///<保存当前列表数据到流
		virtual bool LoadFromStream(Stream *,int=-1);												///<从流中加载数据到列表

		T &Get(int)const;																			///<取得指定索引处的数据
		void Set(int,const T &);																	///<设置指定索引处的数据

		virtual void Sort(ListCompFunc);															///<排序数据

		T &operator[](int n)const{return Get(n);}													///<操作符重载取得指定索引处的数据
	};
}//namespace hgl

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

		virtual T *		Append();																	///<追加一个数据
		virtual T *		Insert(int);																///<在指定索引处创建一个数据
				void 	Insert(int,T *);															///<在指定索引处插入一个数据

		virtual void 	Clear();																	///<清除所有数据

		virtual bool 	Unlink(int);																///<将指定索引处的数据与列表断开
		virtual bool 	Unlink(T *);																///<将一个指定数据与列表断开
		virtual void	Unlink(T **,int);															///<将一批指定数据与列表断开
		virtual void 	UnlinkAll();																///<断开所有数据

		virtual bool 	Delete(int);																///<删除指定索引处的数据
		virtual bool 	Delete(T *);																///<删除指定的一个数据
		virtual void	Delete(T **,int);															///<删除指定的一批数据
		virtual void 	DeleteAll();																///<删除所有数据

		virtual void 	Sort(ObjectListCompFunc);													///<排序数据		
	};
}//namespace hgl
#include <hgl/Template/ObjectList.CPP>
#endif//HGL_LIST_INCLUDE
