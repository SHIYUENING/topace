#ifndef HGL_PROBSELECT_INCLUDE
#define HGL_PROBSELECT_INCLUDE

#include<hgl/list.h>
namespace hgl
{
	/**
	* 机率选择器，用于按一定机率选择结果
	*/
	class ProbSelect                                                                                ///机率选择器
	{
		uint total;

		List<uint> val;

   	private:

		uint GetCount(){return val.Count;}
		uint GetTotal(){return total;}

		void InitPrivate();

	public:

		Property<uint> Count;                                                                       ///<数据数量
		Property<uint> Total;                                                                       ///<总量值

	public:

		uint GetValue(uint n){return val.Get(n);}
		void SetValue(uint,uint);

		float GetProp(uint n){return float(val.Get(n))/float(total);}

	public:

		ProbSelect(const uint *,const uint);
		ProbSelect();
		virtual ~ProbSelect(){};

		void Add(const uint *,const uint);
		void Add(const uint);

		uint Select();
	};
}//namespace hgl
#endif//HGL_PROBSELECT_INCLUDE
