#ifndef HGL_FIXEDLIST_INCLUDE
#define HGL_FIXEDLIST_INCLUDE

#include<hgl/DataType.H>
#include<hgl/RWLock.H>
namespace hgl
{
	/**
	* 定长列表用于保存固定长度的数据
	*/
	template<typename T> class FixedList                                                            ///定长列表
	{
	protected:

		T *items;
		int max_count,count;

		T *GetData(){return items;}                                                                 ///<提供原始数据项
		void InitPrivate();

	public:	//属性

		Property<T *> Data;                                                                         ///<直接访问数据内存指针

	public:	//事件

		void (*OnClear)(const T &);																	///<清除事件

	public: //方法

		FixedList();																				///<本类构造函数
		FixedList(int);                                                                             ///<本类构造函数
		virtual ~FixedList();                                                                       ///<本类析构函数

		virtual void Create(int);																	///<创建数据列表

		//为在派生类中区分安全方法与非安全方法，不可以将下面三个函数改为属性
		virtual int	 GetMaxCount(){return max_count;}												///<取得最大数据个数
		virtual int	 GetCount(){return count;}														///<取得当前数据个数
		virtual bool IsFull(){return count>=max_count;}												///<是否是满的

		virtual bool Append(const T &);                                                             ///<压入一个数据
		virtual bool Append(const T *,int);															///<压入一批数据

		virtual int  Find(const T &);																///<查找数据

		virtual bool Delete(int);																	///<删除指定数据
		virtual bool Delete(const T &v){return Delete(Find(v));}									///<删除指定数据
		virtual void Delete(const T *,int);															///<删除指定数据

		virtual void Clear();                                                                       ///<清除所有数据(全部清0)

		virtual T *CreateCopy(int &);																///<创建一个拷贝

		virtual T &operator[](int n);
	};

	template<typename T> class FixedObjectList:public FixedList<T *>                                ///定长对象列表
	{
	public:

		FixedObjectList():FixedList<T *>(){};
		FixedObjectList(int n):FixedList<T *>(n){}

		virtual ~FixedObjectList(){Clear();}

		virtual bool Delete(int);
		virtual void Clear();
	};

	template<typename T> class MTFixedList:public FixedList<T>										///<多线程定长数据列表
	{
		RWLock lock;

	public:

		MTFixedList():FixedList<T>(){};
		MTFixedList(int n):FixedList<T>(n){}
		virtual ~MTFixedList()
		{
			SafeClear();
		}

	public:

		bool ReadLock()		{return lock.ReadLock();	}											///<读列表锁定(用于访问整个列表)
		bool WriteLock()	{return lock.WriteLock();	}											///<写列表锁定(用于访问整个列表)
		bool TryReadLock()	{return lock.TryReadLock();	}											///<尝试读列表并锁定(用于访问整个列表)
		bool TryWriteLock()	{return lock.TryWriteLock();}											///<尝试写列表并锁定(用于访问整个列表)

		bool Unlock()		{return lock.Unlock();		}											///<解锁

	public:	//安全方法

		virtual void SafeCreate(int c)
		{
			lock.WriteLock();
			Create(c);
			lock.Unlock();
		}

		virtual T *SafeCreateCopy(int &c)
		{
			T *copy;

			lock.ReadLock();
			copy=FixedList<T>::CreateCopy(c);
			lock.Unlock();

			return copy;
		}

		int SafeGetCount()	
		{
			int result;

			lock.ReadLock();
			result=count;
			lock.Unlock();

			return result;
		}

		int SafeGetMaxCount()	
		{
			int result;

			lock.ReadLock();
			result=max_count;
			lock.Unlock();

			return result;
		}

		void SafeGetCount(int &c,int &m)
		{
			lock.ReadLock();
			c=count;
			m=max_count;
			lock.Unlock();
		}

		bool SafeIsFull()
		{
			bool result;

			lock.ReadLock();
			result=IsFull();
			lock.Unlock();

			return result;
		}

		virtual bool SafeAppend(const T &data)
		{
			bool result;

			lock.WriteLock();
			result=Append(data);
			lock.Unlock();

			return(result);
		}

		virtual bool SafeAppend(const T *data,int n)
		{
			bool result;

			lock.WriteLock();
			result=Append(data,n);
			lock.Unlock();

			return(result);
		}

		virtual int  SafeFind(const T &data)
		{
			int result;

			lock.ReadLock();
			result=Find(data);
			lock.Unlock();

			return(result);
		}

		virtual bool SafeDelete(int n)
		{
			bool result;

			lock.WriteLock();
			result=Delete(n);
			lock.Unlock();

			return(result);
		}

		virtual bool SafeDelete(const T &data)
		{
			int index;
			bool result;

			lock.WriteLock();
			index=Find(data);
			result=Delete(index);
			lock.Unlock();

			return(result);
		}

		virtual void SafeDelete(const T *data,int n)
		{
			lock.WriteLock();
			Delete(data,n);
			lock.Unlock();
		}

		virtual void SafeClear()
		{
			lock.WriteLock();
			Clear();
			lock.Unlock();
		}

		virtual T SafeGetItem(int n)
		{
			T result;

			lock.ReadLock();
			result=operator[](n);
			lock.Unlock();

			return result;
		}
	};

	template<typename T> class MTFixedObjectList:public MTFixedList<T *>							///<多线程定长对象列表
	{
	public:

		MTFixedObjectList():MTFixedList<T *>(){}
		MTFixedObjectList(int n):MTFixedList<T *>(n){}
		virtual ~MTFixedObjectList()
		{
			SafeClear();
		}

		virtual bool Delete(int);
		virtual void Clear();
	};
}//namespace hgl
#include<hgl/Template/FixedList.CPP>
#endif//HGL_FIXEDLIST_INCLUDE
