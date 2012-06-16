#ifndef HGL_CONST_OBJECT_INCLUDE
#define HGL_CONST_OBJECT_INCLUDE

namespace hgl
{
	class String;
	class Stream;

	/**
	* Const 名字空间<br>
	* 该名字空间内所有对象均以最佳效能为目标设计，所以很多对象将无法修改
	*/
	namespace Const																					///Const 名字空间
	{
		class ConstObject
		{
		protected:

			char *	data;
			int 	data_size;
			bool	data_private;

			void InitConstPrivate()
			{
				data=0;
				data_size=0;
				data_private=false;
			}

			virtual bool Parse()=0;

		public:

			ConstObject()
			{
				InitConstPrivate();
			}

			/**
			* @param in 输入数据指针
			* @param in_size 输入数据长度
			* @param in_data_private 输入数据是否私有,可以由ConstObject来释放
			*/
			ConstObject(void *in,int in_size,bool in_data_private)
			{
				InitConstPrivate();

				Load(in,in_size,in_data_private);
			}

			virtual ~ConstObject()
			{
				Clear();
			}

			/**
			* 加载数据
			* @param in 输入数据指针
			* @param in_size 输入数据长度
			* @param in_data_private 输入数据是否私有,可以由ConstObject来释放
			* @return 是否加载成功
			*/
			virtual bool Load(void *in,int in_size,bool in_data_private)
			{
				Clear();

				if(!in)return(false);

				data=(char *)in;
				data_size=in_size;
				data_private=in_data_private;

				return Parse();
			}

			/**
			* 从文件加载数据
			* @param filename 文件名
			* @return 是否成功
			*/
			virtual bool LoadFromFile(const String &filename);

			/**
			* 从文件中加载数据
			* @param filename 文件名
			* @param offset 起始位置
			* @param length 数据长度
			* @return 是否成功
			*/
			virtual bool LoadFromFile(const String &filename,int offset,int length);

			/**
			* 从文件加载数据
			* @param str 流指针
			* @param length 要读取的长度
			* @return 是否成功
			*/
			virtual bool LoadFromStream(Stream *str,int length);

			/**
			* 保存数据到文件
			* @param filename 文件名
			* @return 是否成功
			*/
			bool SaveToFile(const String &filename);

			/**
			* 保存数据到文件的指定位置
			* @param filename
			* @param offset 起始位置
			* @param length 保存长度
			* @return 是否成功
			*/
			bool SaveToFile(const String &filename,int offset,int length);

			/**
			* 保存数据到流
			* @param str 流指针
			* @return 是否成功
			*/
			bool SaveToStream(Stream *str);

			/**
			* 保存数据到流指定位置
			* @param str 流指针
			* @param offset 起始位置
			* @param length 保存长度
			* @return 是否成功
			*/
			bool SaveToStream(Stream *str,int offset,int length);

			/**
			* 清除数据
			*/
			virtual void Clear()
			{
				if(data_private&&data)
					delete[] data;

				InitConstPrivate();
			}
		};
	}

	using namespace Const;
}
#endif//HGL_CONST_OBJECT_INCLUDE
