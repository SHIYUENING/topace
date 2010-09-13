#ifndef HGL_QUEUE_INCLUDE
#define HGL_QUEUE_INCLUDE

#include<hgl/DataType.H>
namespace hgl
{
	/**
	* Queue模板类用于保存一个先进先出、后进后出的数据队列
	*
	* 注：这个类还在测试中，请不要修改这个类的源代码，如有修改意见，请致电作者。
	*/
	template<typename T> class Queue                                                                ///队列顺序数据访问类
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
		T &GetItem(int n){return (n<0||n>=count)?NULL:items[n];}

	public: //属性

		Property<int> Count;                                                                        ///<队列中数据的个数
		Property<int> MaxCount;                                                                     ///<队列中的最大数据个数

	public: //方法

		Queue(int=0);
		virtual ~Queue();

		bool Peek(T &);
		bool Pop(T &);
		bool Push(const T &);

		void Clear();                                                                               ///<清除所有数据

		T &operator[](int n){return GetItem(n);}

		virtual void operator =(const Queue<T> &);
	};

	template<typename T> class QueueObject:public Queue<T *>										///堆栈对象
	{
	public:

		QueueObject(int n=0):Queue<T *>(n){};
		virtual ~QueueObject(){Clear();};

		void Clear();
	};
}//namespace hgl
#include <hgl/Template/Queue.CPP>
#endif//HGL_QUEUE_INCLUDE
