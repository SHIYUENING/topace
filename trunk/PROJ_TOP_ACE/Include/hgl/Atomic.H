#ifndef HGL_ATOMIC_INCLUDE
#define HGL_ATOMIC_INCLUDE

#include<hgl/DataType.H>
namespace hgl
{
    /**
    * 原子整型数据，基于原子操作的uint32型变量模拟封装
    */
    class atom_uint32                                                                                  ///原子整型数据
    {
        volatile uint32 value;

    public:

        atom_uint32();
        atom_uint32(const uint32);
        ~atom_uint32();

        operator const uint32 ()const{return value;}

        const uint32 operator =  (const uint32);

        const uint32 operator += (const uint32);
        const uint32 operator -= (const uint32);

        const uint32 operator  *= (const uint32 v){return operator=(value *=v);}
        const uint32 operator  /= (const uint32 v){return operator=(value /=v);}
        const uint32 operator  %= (const uint32 v){return operator=(value %=v);}
        const uint32 operator  &= (const uint32 v){return operator=(value &=v);}
        const uint32 operator  |= (const uint32 v){return operator=(value |=v);}
        const uint32 operator >>= (const uint32 v){return operator=(value>>=v);}
        const uint32 operator <<= (const uint32 v){return operator=(value<<=v);}

        const uint32 operator ~ (){return operator=(~value);}
        const uint32 operator ! (){return operator=(!value);}

        const uint32 operator ++ (int);    //后置++
        const uint32 operator -- (int);    //后置--

        const uint32 operator ++ ();       //前置++
        const uint32 operator -- ();       //前置--
    };//class atom_uint32

#if (HGL_CPU == HGL_CPU_X86_64)
    /**
    * 64位原子整型数据，基于原子操作的uint64型变量模拟封装<br>
	* 本类Windows版最低需要Windows Server 2003
    */
	class atom_uint64
	{
		volatile uint64 value;

    public:

        atom_uint64();
        atom_uint64(const uint64);
        ~atom_uint64();

        operator const uint64 ()const{return value;}

        const uint64 operator =  (const uint64);

        const uint64 operator += (const uint64);
        const uint64 operator -= (const uint64);

        const uint64 operator  *= (const uint64 v){return operator=(value *=v);}
        const uint64 operator  /= (const uint64 v){return operator=(value /=v);}
        const uint64 operator  %= (const uint64 v){return operator=(value %=v);}
        const uint64 operator  &= (const uint64 v){return operator=(value &=v);}
        const uint64 operator  |= (const uint64 v){return operator=(value |=v);}
        const uint64 operator >>= (const uint64 v){return operator=(value>>=v);}
        const uint64 operator <<= (const uint64 v){return operator=(value<<=v);}

        const uint64 operator ~ (){return operator=(~value);}
        const uint64 operator ! (){return operator=(!value);}

        const uint64 operator ++ (int);    //后置++
        const uint64 operator -- (int);    //后置--

        const uint64 operator ++ ();       //前置++
        const uint64 operator -- ();       //前置--
	};
#endif//HGL_CPU_X86_64
}//namespace hgl
#endif//HGL_ATOMIC_INCLUDE
