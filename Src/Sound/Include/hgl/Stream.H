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
	public:	//属性

		Property<int64> Position;                                                                   ///<该属性可以访问流的当前位置，如果是-1表示无法操作
		Property<int64> Size;                                                                       ///<该属性可以访问流的大小，如果为-1表示无法控制

	public:	//方法

		Stream();
		virtual ~Stream();

		virtual int 	Read(void *,int)=0;
		virtual int 	Write(const void *,int)=0;

		#define STREAM_RW(type,read,write)	bool read(type &value){return(Read(&value,sizeof(type))==int(sizeof(type)));}	\
											bool write(type value){return(Write(&value,sizeof(type))==int(sizeof(type)));}

		STREAM_RW(bool,	 ReadBool,	WriteBool	);
		STREAM_RW(int8,	 ReadInt8,	WriteInt8	);
		STREAM_RW(int16, ReadInt16,	WriteInt16	);
		STREAM_RW(int32, ReadInt32,	WriteInt32	);
		STREAM_RW(int64, ReadInt64,	WriteInt64	);
		STREAM_RW(uint8, ReadUint8,	WriteUint8	);
		STREAM_RW(uint16,ReadUint16,WriteUint16	);
		STREAM_RW(uint32,ReadUint32,WriteUint32	);
		STREAM_RW(uint64,ReadUint64,WriteUint64	);
		STREAM_RW(float, ReadFloat,	WriteFloat	);
		STREAM_RW(double,ReadDouble,WriteDouble	);

		#undef STREAM_RW
		
				int 	ReadString(wchar_t *);
				bool 	WriteString(const wchar_t *);

				int32 	ReadString(String &);
				bool 	WriteString(const String &);

				bool	ReadObject(DataObject *);
				bool	WriteObject(DataObject *);
		
				void 	printf(const char *,...);
				void 	printf(const wchar_t *,...);

				int 	ReadLine(wchar_t *);
				void	WriteLine(const wchar_t *);

		virtual int64 	Seek(int64,SeekOrigin=soBegin);

				bool	Eof(){return Position>=Size;}
	};
}
//--------------------------------------------------------------------------------------------------
#endif//HGL_STREAM_INCLUDE