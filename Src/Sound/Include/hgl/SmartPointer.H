#ifndef HGL_SMARTPOINTER_INCLUDE
#define HGL_SMARTPOINTER_INCLUDE

namespace hgl
{
	/**
	* SmartPointer 被称为灵巧的指针，使用它可以很方便的定义会自动释放的数据类型<br>
	* 具体可参请SmartPointer示例。<br>
	* 如“SmartPointer<T> data=new T;”不通过，可使用“SmartPointer<T> data(new T)”
	*/
	template <class T> class SmartPointer                                                           ///灵巧指针类
	{
		SmartPointer<T> &operator =(SmartPointer<T> &)
		{
			return(*this);
		}

		SmartPointer(SmartPointer<T> &){}

	protected:

		T *ThisPointer;

	public:

		SmartPointer(T *ptr=0):ThisPointer(ptr){}

		virtual ~SmartPointer()
		{
        	if(ThisPointer)
				delete ThisPointer;
		}

		T &operator *() const
		{
			return *ThisPointer;
		}

		T *operator =(T *ptr)
		{
			if(ThisPointer)
				delete ThisPointer;

			ThisPointer=ptr;
			return(ptr);
		}

		operator T *()const{return ThisPointer;}

		T *operator ->() const
		{
			return(ThisPointer);
		}

		bool operator == (T *ptr) const
		{
        	return ThisPointer == ptr;
		}

		bool operator != (T *ptr) const
		{
        	return !(operator ==(ptr));
		}
	};

	template <class T> class SmartArray                                                           ///灵巧指针类
	{
		SmartArray<T> &operator =(SmartArray<T> &)
		{
			return(*this);
		}

		SmartArray(SmartArray<T> &){}

	protected:

		T *ThisPointer;

	public:

		SmartArray(T *ptr=0):ThisPointer(ptr){}

		virtual ~SmartArray()
		{
        	if(ThisPointer)
				delete[] ThisPointer;
		}

		T &operator *() const
		{
			return *ThisPointer;
		}

		T *operator =(T *ptr)
		{
			if(ThisPointer)
				delete[] ThisPointer;

			ThisPointer=ptr;
			return(ptr);
		}

		operator T *()const{return ThisPointer;}

//		operator const T [](int n)const{return ThisPointer[n];}

		T *operator ->() const
		{
			return(ThisPointer);
		}

		bool operator == (T *ptr) const
		{
        	return ThisPointer == ptr;
		}

		bool operator != (T *ptr) const
		{
        	return !(operator ==(ptr));
		}
	};

	typedef SmartArray<char> SmartAnsiString;
	typedef SmartArray<wchar_t> SmartWideString;
	typedef SmartArray<wchar_t> SmartUnicodeString;
}

#endif//HGL_SMARTPOINTER_INCLUDE