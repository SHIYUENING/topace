#ifndef HGL_TDF_INCLUDE
#define HGL_TDF_INCLUDE

#include<hgl/DataType.H>
#include<hgl/IndexData.H>
#include<hgl/Compress.H>
#include<hgl/Str.H>
#include<hgl/StringList.H>
#include<hgl/MemStream.H>
namespace hgl
{
	class HAC;

	/**
	* TDF节点，一种类似BinaryXML,注册表的数据节点.<br>
	* 强烈建议不要在TDF节点中放置大块的数据，虽然你可以放置。
	*/
	class TDFNode                                                                                   ///HyzTDF节点类
	{
	public: //属性

		String Name;                                                                                ///<节点名称
		MemStream Data;                                                                             ///<节点数据

		ObjectList<TDFNode> Node;                                                                   ///<子节点

	public: //方法,节点操作

		TDFNode();
		virtual ~TDFNode();

		TDFNode *Create();																			///<创建一个节点
		TDFNode *Create(const String &);                                                           	///<创建一个节点
		TDFNode *FindNode(const String &);															///<查找一个节点
		void Add(TDFNode *n){Node<<n;}																///<增加一个节点
		void Delete(const String &);                                                               	///<删除一个节点
		void Delete(TDFNode *);                                                                     ///<删除一个节点
		void Clear();                                                                               ///<清除当前节点的数据

		bool ReadBool   	(const wchar_t *,bool &);
		bool ReadInt8   	(const wchar_t *,int8 &);
		bool ReadInt16  	(const wchar_t *,int16 &);
		bool ReadInt32  	(const wchar_t *,int32 &);
		bool ReadInt64  	(const wchar_t *,int64 &);
		bool ReadUint8  	(const wchar_t *,uint8 &);
		bool ReadUint16 	(const wchar_t *,uint16 &);
		bool ReadUint32 	(const wchar_t *,uint32 &);
		bool ReadUint64 	(const wchar_t *,uint64 &);
		bool ReadFloat  	(const wchar_t *,float &);
		bool ReadDouble 	(const wchar_t *,double &);
		bool ReadString 	(const wchar_t *,String &);
		bool ReadString 	(const wchar_t *,wchar_t *,int);
		bool ReadData   	(const wchar_t *,void *,int);
		bool ReadObject		(const wchar_t *,DataObject *);

		TDFNode *WriteBool  	(const wchar_t *,bool);
		TDFNode *WriteInt8  	(const wchar_t *,int8);
		TDFNode *WriteInt16 	(const wchar_t *,int16);
		TDFNode *WriteInt32 	(const wchar_t *,int32);
		TDFNode *WriteInt64 	(const wchar_t *,int64);
		TDFNode *WriteUint8 	(const wchar_t *,uint8);
		TDFNode *WriteUint16	(const wchar_t *,uint16);
		TDFNode *WriteUint32	(const wchar_t *,uint32);
		TDFNode *WriteUint64	(const wchar_t *,uint64);
		TDFNode *WriteFloat 	(const wchar_t *,float);
		TDFNode *WriteDouble	(const wchar_t *,double);
		TDFNode *WriteString	(const wchar_t *,const String &);
		TDFNode *WriteData  	(const wchar_t *,const void *,int);
		TDFNode *WriteObject	(const wchar_t *,DataObject *);

	public: //方法

		bool LoadFromStream(Stream *);                                                              ///<从流中载入节点数据
		bool LoadFromFile(const wchar_t *);                                                         ///<从文件中载入节点数据
		bool LoadFromFile(HAC *,const wchar_t *);													///<从HAC包中的文件载入节点数据

		bool SaveToStream(Stream *);                                                                ///<保存当前节点到流中
		bool SaveToFile(const wchar_t *);                                                           ///<保存当前节点到文件
	};

	int	 	tdfReadCompressData(TDFNode *,const String &,const String &,void *,int);				///<读取压缩数据
	void 	tdfWriteCompressData(TDFNode *,const String &,const String &,void *,int,const String &);///<存入压缩数据
	void 	tdfWriteCompressData(TDFNode *,const String &,const String &,void *,int,CA);			///<存入压缩数据

	int	 	tdfReadCompressData(TDFNode *,const String &,void *,int);								///<读取压缩数据
	void 	tdfWriteCompressData(TDFNode *,const String &,void *,int,const String &);				///<存入压缩数据
	void 	tdfWriteCompressData(TDFNode *,const String &,void *,int,CA=caRLE);						///<存入压缩数据

	int		tdfReadCompressImage(TDFNode *,const String &,const String &,void *,int,int,int);
	void	tdfWriteCompressImage(TDFNode *,const String &,const String &,void *,int,int,int,const String &,float);

	int		tdfReadCompressImage(TDFNode *,const String &,void *,int,int,int);
	void	tdfWriteCompressImage(TDFNode *,const String &,void *,int,int,int,const String &,float);
}//namespace hgl
#endif//HGL_TDF_INCLUDE
