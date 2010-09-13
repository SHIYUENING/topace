#ifndef HGL_CONST_DATA_TEMPLATE
#define HGL_CONST_DATA_TEMPLATE

#include<hgl/const/ConstObject.H>
#include<hgl/List.H>
namespace hgl
{
	namespace Const
	{
		/**
		* Const 定长数据模板
		*/
		template<typename T> class ConstFixedData:public ConstObject
		{
		protected:

			uint32 Count;

            T *DataList;

		protected:

			bool Parse()
			{
				if(!data||data_size<4)return(false);

				Count=*((uint32 *)data);				//取四个字节的数据数量

				DataList=(T *)(data+4);					//移到数据区

				return(true);
			}

			const T operator[](int n)
			{
				return DataList[n];
			}
		};

		/**
		* Const 非定长数据模板
		*/
		template<typename T> class ConstData:public ConstObject
		{
		protected:

			List<T> DataList;

		protected:

			bool Parse()
			{
				Lines.Clear();

				if(!data||data_size<4)return(false);

				T *tp;
				char *sp;
				uint32 *length;
				uint32 count;

				count=*((uint32 *)data);			//四个字节，代表数据数量

				length=(uint32 *)(data+4);			//数量*4，取得每个数据的长度

				sp=data+4+count*4;					//移到数据区

				Lines.Count=count;

				tp=Lines.Data;

				while(count--)
				{
					*tp++=(T)sp;					//给指针赋值

					sp+=*length++;					//移到下一个数据的起始位置
				}

				return(true);
			}

			const T operator[](int n)
			{
				return DataList[n];
			}
		};

        typedef ConstData<wchar_t *> ConstStringList;
	}

	using namespace Const;
}
#endif//HGL_CONST_DATA_TEMPLATE
