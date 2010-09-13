#ifndef HGL_INT128_INCLUDE
#define HGL_INT128_INCLUDE

#include<hgl/datatype.h>
namespace hgl
{
	/**
	* 128位整型数据变量,用于超大数运算
	*/
	class int128                                                                                    ///int128位整型数
	{
	public:

		uint64 LowPart;
		uint64 HighPart;
		
	public:

		int128();
		int128(uint64 n);
		int128(uint64 HighPart,uint64 LowPart);

	//    int128 operator = (int128 n);
		int128 operator << (int n);
		int128 operator >> (int n);

		friend int128 operator / (int128 n1,int128 n2);
		friend int128 operator * (int128 n1,int128 n2);
		friend int128 operator % (int128 n1,int128 n2);
		friend int128 operator + (int128 n1,int128 n2);
		friend int128 operator - (int128 n1,int128 n2);
		friend int128 operator += (int128 &n1,int128 n2);
		friend int128 operator -= (int128 &n1,int128 n2);
		friend int128 operator *= (int128 &n1,int128 n2);
		friend int128 operator /= (int128 &n1,int128 n2);
		friend int128 operator | (int128 n1,int128 n2);
		friend int128 operator & (int128 n1,int128 n2);
		inline friend void operator -= (int128 &n1,unsigned int n2)
		{
		  if (n1.LowPart<n2)
			n1.HighPart--;
		  n1.LowPart-=n2;
		}
		inline friend void operator ++ (int128 &n)
		{
		  if (++n.LowPart == 0)
			++n.HighPart;
		}
		inline friend void operator -- (int128 &n)
		{
		  if (n.LowPart-- == 0)
			n.HighPart--;
		}
		friend bool operator == (int128 n1,int128 n2);
		friend bool operator > (int128 n1,int128 n2);
		friend bool operator < (int128 n1,int128 n2);
		friend bool operator != (int128 n1,int128 n2);
		friend bool operator >= (int128 n1,int128 n2);
		friend bool operator <= (int128 n1,int128 n2);

		void Set(uint64 HighPart,uint64 LowPart);
		uint64 GetLowPart() {return(LowPart);}
	};

	inline uint64 int128to64(int128 n) {return(n.GetLowPart());}
	#define int64to128(high,low) (int128((high),(low)))
	#define is128plus(x) ((int)(x).HighPart>=0)

	#define INT128ERR int64to128(0x8000000000000000,0)
	#define INT128MAX int64to128(0x7fffffffffffffff,0)

	void itow(int128,wchar_t *);
	int128 wtoi(wchar_t *);
}//namespace hgl
#endif//HGL_INT128_INCLUDE
