#ifndef HGL_SET_INCLUDE
#define HGL_SET_INCLUDE

#include<hgl/BitArray.H>
namespace hgl
{
	/**
	* 选择设置用模板
	*/
	template<typename E,unsigned int Start,unsigned int End> class Set
	{
		BitArray bit;

	public:

		Set():bit(End-Start+1){}

		virtual ~Set(){};

		/**
		* 取得数据访问指针
		* @param buf 数据指针
		* @return 字节长度
		*/
		int GetData(void **buf)
		{
			int byte_size=(bit.Count+7>>3);

			*buf=bit.Data;

			return byte_size;
		}

		Set &operator=(const Set &rhs)
		{
			if(this!=&rhs)
				bit=rhs.bit;

			return *this;
		}

		Set &operator+=(const Set &rhs)
		{
			if(this!=&rhs)
				bit+=rhs.bit;

			return *this;
		}

		Set &operator-=(const Set &rhs)
		{
			if(this!=&rhs)
				bit-=rhs.bit;

			return *this;
		}

		Set &operator*=(const Set &rhs)
		{
			if(this!=&rhs)
				bit*=rhs.bit;

			return *this;
		}

		Set operator+(const Set &rhs)const
		{
			Set<E,Start,End> s=this;

			s+=rhs;

			return s;
		}

		Set operator-(const Set &rhs)const
		{
			Set<E,Start,End> s=this;

			s-=rhs;

			return s;
		}

		Set operator*(const Set &rhs)const
		{
			Set<E,Start,End> s=this;

			s+=rhs;

			return s;
		}

		Set& operator <<(const E el)
		{
			bit.WritePos(el-Start,true);

			return *this;
		}

		Set& operator >>(const E el)
		{
			bit.WritePos(el-Start,false);

			return *this;
		}

		void Clear(bool all_select=false)
		{
        	bit.Fill(all_select);
		}

		bool Check(const E el)const
		{
			return bit.ReadPos(el-Start);
		}

		bool operator == (const Set &rhs) const
		{
            return bit==rhs.bit;
		}

    	bool operator !=(const Set& rhs) const {return !operator==(rhs);}

		bool SaveToStream	(Stream *str){return bit.SaveToStream(str);}							///<保存当前位阵列数据到流
		bool LoadFromStream	(Stream *str){return bit.LoadFromStream(str);}                          ///<从流中读取位阵列数据
		bool SaveToFile		(const wchar_t *fn){return bit.SaveToFile(fn);}                         ///<保存当前位阵列数据到文件
		bool LoadFromFile	(const wchar_t *fn){return bit.LoadFromFile(fn);}                       ///<从文件中读取位阵列数据
	};
}//namespace hgl
#endif//HGL_SET_INCLUDE
