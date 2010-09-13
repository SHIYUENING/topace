#ifndef HGL_PSEUDO_RANDOM_NUMBER_INCLUDE
#define HGL_PSEUDO_RANDOM_NUMBER_INCLUDE

#include<hgl/stream.h>
namespace hgl
{
	/**
	* 假随机数是一种常用技术，用于需要回放的环境，或是需要快速产生随机数的环境。<br>
	* 注: 一般的随机数请使用hgl/other.h中的FastRand()
	* @see FastRand
	*/
	class PseudoRandom                                                                              ///假随机数
	{
	protected:

		uint8 *data;
		uint32 count,pos;

	public:

		PseudoRandom(uint32=1024);                                                                  ///<本类构造函数
		virtual ~PseudoRandom();                                                                    ///<本类析构函数

	public:

		virtual void Init(uint32=1024);                                                             ///<初始化随机数
		virtual void Clear();                                                                       ///<清除

		virtual bool SaveToStream(Stream *);                                                        ///<保存当前状态到流
		virtual bool LoadFromStream(Stream *);                                                      ///<从流中加载状态

		virtual bool Rand8(uint8 &);                                                                ///<产生一个8位随机数
		virtual bool Rand16(uint16 &);                                                              ///<产生一个16位随机数
		virtual bool Rand32(uint32 &);                                                              ///<产生一个32位随机数
	};
}//namespace hgl
#endif//HGL_PSEUDO_RANDOM_NUMBER_INCLUDE
