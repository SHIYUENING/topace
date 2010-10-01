#ifndef HGL_ONLYLIST_INCLUDE
#define HGL_ONLYLIST_INCLUDE

#include<hgl/List.H>
namespace hgl
{
	/**
	* 唯一数据列表中不允许数据出现重复性<br>
	* 注: 这个类还在测试中，如果您有修改意见，请将修改后的代码发给作者。
	*/
    template<typename T> class OnlyList
    {
        List<T> data_list;

		int FindPos(const T &);

		int	GetCount(){return data_list.Count;}														///<取得数据总量

	public:	//属性

    	Property<int> Count;                                                                        ///<数据个数

    public:

        OnlyList();
        virtual ~OnlyList(){};

	    int Find(const T &);                                                                        ///<查找数据位置
	    int Add(const T &);                                                                         ///<添加一个数据
		bool Delete(const T &);																		///<删除一个数据
		bool DeleteBySerial(int);																	///<删除一个数据
        void Clear();                                                                               ///<清除数据

        const T &operator[](int n)const{return data_list[n];}
    };
}//namespace hgl
#include<hgl/Template/OnlyList.CPP>
#endif//HGL_ONLYLIST_INCLUDE
