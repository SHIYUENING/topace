#ifndef HGL_STREAM_INCLUDE
#define HGL_STREAM_INCLUDE

#include<hgl/DataType.H>
namespace hgl
{
	class String;
	class DataObject;

	enum SeekOrigin             /// 资源偏移方向枚举
	{
		soBegin,                ///<从资源最开始处开始，offset必须大于0。移到资源的offset位置
		soCurrent,              ///<从资源当前位置开始，移到资源的Position+offset位置
		soEnd                   ///<从资源的结束位置开始，offset必须小于0，表示结束前的字符数
	};

	/**
	* Stream是可以从各种存储介质(内存、文件、网络等等)中读出与写入流式数据的抽象基类。
	*
	* Stream类不能被实例化，它必须依靠子类中重载的各种抽象方法来实现所有的功能。
	*/
	class Stream                                                                                    ///流式数据访问基类
	{
	protected:

		virtual int _Read(void *,int)=0;
		virtual int _Write(const void *,int)=0;

	public:	//属性

		Property<int64> Position;                                                                   ///<该属性可以访问流的当前位置，如果是-1表示无法操作
		Property<int64> Size;                                                                       ///<该属性可以访问流的大小，如果为-1表示无法控制

	public:	//方法

		Stream();
		virtual ~Stream();

		int Read(void *ptr,int size)
		{
			if(!ptr||size<0)return(-1);
			
			if(size)
				return(_Read(ptr,size));
			else
				return(0);
		}

		int Write(const void *ptr,int size)
		{
			if(!ptr||size<0)return(-1);
			
			if(size)
				return(_Write(ptr,size));
			else
				return(0);
		}

	public:	//定位函数

		virtual int64 	Seek(int64,SeekOrigin=soBegin);

				bool	Eof(){return Position>=Size;}

	public:	//读写函数

		#define STREAM_RW(type,name)	bool Read##name(type &value){return(Read(&value,sizeof(type))==int(sizeof(type)));}	\
										bool Write##name(type value){return(Write(&value,sizeof(type))==int(sizeof(type)));}

		STREAM_RW(bool,	 Bool	);
		STREAM_RW(int8,	 Int8	);
		STREAM_RW(int16, Int16	);
		STREAM_RW(int32, Int32	);
		STREAM_RW(int64, Int64	);
		STREAM_RW(uint8, Uint8	);
		STREAM_RW(uint16,Uint16	);
		STREAM_RW(uint32,Uint32	);
		STREAM_RW(uint64,Uint64	);
		STREAM_RW(float, Float	);
		STREAM_RW(double,Double	);

		#undef STREAM_RW

		bool ReadString(wchar_t *,int);
		bool WriteString(const wchar_t *);

		bool ReadString(String &);
		bool WriteString(const String &);

		bool ReadObject(DataObject *);
		bool WriteObject(DataObject *);
		
	public:	//自适应类型读写函数

		template<typename T> bool Read(T &value){return(Read(&value,sizeof(value))==sizeof(value));}
		template<typename T> bool Read(T *);							//禁止读取指针

		template<typename T> bool Write(const T &value){return(Write(&value,sizeof(value))==sizeof(value));}
		template<typename T> bool Write(T *);							//禁止写入指针
		template<typename T> bool Write(const T *);						//禁止写入指针

		template<typename T> bool ReadArray(T *value,int count){return(Read(value,count*sizeof(T))==count*sizeof(T));}
		template<typename T> bool ReadArray(T **,int count);			//禁止读取指针

		template<typename T> bool WriteArray(T *value,int count){return(Write(value,conut*sizeof(T))==conut*sizeof(T));}
		template<typename T> bool WriteArray(T **,int count);			//禁止写入指针
		template<typename T> bool WriteArray(const T **,int count);		//禁止写入指针

	public:	//自适应类型操作符重载

		template<typename T> void operator >>(T &value){Read(&value,sizeof(value));}
		template<typename T> void operator >>(T *);						//禁止读取指针

		template<typename T> void operator <<(const T &value){Write(&value,sizeof(value));}
		template<typename T> void operator <<(T *);						//禁止写入指针
		template<typename T> void operator <<(const T *);				//禁止写入指针
	};
}//namespace hgl
#endif//HGL_STREAM_INCLUDE
