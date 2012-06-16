#ifndef HGL_CLASLIST_INCLUDE
#define HGL_CLASLIST_INCLUDE

#include<hgl/List.H>
namespace hgl
{
	/**
	* 分类对象模板<br>
	* 允许将一批数据分成几类保存，而且允许一个数据在好几个类别的列表中均存在。
	*/
	template<typename T> class ClasList                                                             ///分类对象模板
	{
	protected:

		bool MultiType;                                                                             ///<是否允许一个数据多类型
		int TypeCount;                                                                              ///<分类数量

		ObjectList<T> all_object;                                                                   ///<全部对象列表
		List<T *> *clas_object;                                                                     ///<分类对象列表

		virtual int CheckObjectType(T *);                                               			///<对象类型过滤函数，用于返回对象属于那一个类型
		virtual bool CheckObjectAttrib(T *,int);                                     				///<对象类型过滤函数，用于检测对象是否符合这一类型

	public:

		ClasList(int,bool);
		virtual ~ClasList();

		virtual void Add(T *);																		//添加一个对象到当前控制器器
		virtual void Clear();                                                                       //清除所有对象

		virtual bool Unlink(T *);                                                                   //将指定对象与当前控制器断开关联
		virtual bool Delete(T *);                                                                   //将指定对象从当前控制器删除

		virtual void UnlinkAll();																	//解除所有对象关联
				void DeleteAll(){Clear();}															//删除所有对象

				void operator += (T *obj){Add(obj);}                                                //添加一个对象到当前控制器器
				void operator << (T *obj){Add(obj);}
	};
}//namespace hgl
#include<hgl/Template/ClasList.CPP>
#endif//HGL_CLASLIST_INCLUDE
