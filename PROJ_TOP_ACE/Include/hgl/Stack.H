#ifndef HGL_STACK_INCLUDE
#define HGL_STACK_INCLUDE

#include<hgl/datatype.h>
namespace hgl
{
	/**
	* Stack模板类用于保存一个先进后出、后进先出的数据堆栈
	*
	* 注：这个类还在测试中，请不要修改这个类的源代码，如有修改意见，请致电作者。
	*/
	template<typename T> class Stack                                                                ///堆栈顺序数据访问类
	{
	protected:

		int max_count;
		int mem_count;
		int count;
		T *items;

	protected:

		int GetCount(){return count;}
		int GetMax(){return max_count;}

		void SetMax(int);
		T &GetItem(int);

	public: //属性
                                                       
		Property<int> Count;                                                                        ///<堆栈中数据的个数
		Property<int> MaxCount;                                                                     ///<堆栈中的最大数据个数

	public: //方法

		Stack(int=0);
		virtual ~Stack();

				bool Peek(T &);
		virtual bool Pop(T &);
				bool Push(T &);

		virtual void Clear();                                                                       ///<清除所有数据

		T &operator[](int n){return GetItem(n);}

		virtual void operator =(const Stack<T> &);
	};

	template<typename T> class StackObject:public Stack<T *>										///堆栈对象
	{
	public:

		StackObject(int n=0):Stack<T *>(n){};
		virtual ~StackObject(){Clear();};

		void Clear();    	
	};
}//namespace hgl
#include <hgl/Template/Stack.CPP>
#endif//HGL_STACK_INCLUDE
