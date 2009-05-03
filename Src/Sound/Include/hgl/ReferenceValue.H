#ifndef HGL_REFERENCEVALUE_INCLUDE
#define HGL_REFERENCEVALUE_INCLUDE

namespace hgl
{
	class ReferenceValue                                                                            ///参考量
	{
	public:

		float cur;      ///<当前量
		float max;      ///<最大量

	public:

		ReferenceValue()
		{
			cur=0;
			max=0;
		}
	};
}

#endif//HGL_REFERENCEVALUE_INCLUDE