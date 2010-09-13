#ifndef HGL_STRINGLIST_INCLUDE
#define HGL_STRINGLIST_INCLUDE

#include<hgl/List.H>
#include<hgl/Str.H>
#include<hgl/DataObject.H>
namespace hgl
{
	class StringList;
	class Stream;
	class HAC;

	/**
	* 字符串列表处理类，用于保存字符串列表。
	*/
	class StringList:public DataObject                                                              ///字符串列表处理类
	{
		void InitPrivate();
		
	private:

		ObjectList<String> Items;

		int GetCount(){return Items.Count;}															///<字符串列表行数虚拟变量

	public:	//属性

		Property<int> Count;

	public:	//操作符重载

		String &operator[](int n)const{return *(Items[n]);}

		StringList &operator = (const StringList *);
		StringList &operator = (const StringList &list){return operator=(&list);}

	public: //方法

		StringList();                                                                               ///<本类构造函数
		StringList(const wchar_t *,CCP=ccpNone);                                                    ///<本类构造函数
		StringList(HAC *,const wchar_t *,CCP=ccpNone);                                              ///<本类构造函数
		StringList(const String &list){InitPrivate();operator=(&list);}								///<本类构造函数
		StringList(const String *list){InitPrivate();operator=(list);}								///<本类构造函数
		~StringList();                                                                              ///<本类析构函数

		int  Add(const char *,CCP=ccpNone);
		int  Add(const char *,int,CCP=ccpNone);
		int  Add(const wchar_t *);
		int  Add(const wchar_t *,int);

		int  AddFormat(CCP,const char *,...);														///<使用printf格式添加一行(ansi)
		int  AddFormat(const wchar_t *,...);														///<使用printf格式添加一行(unicode)

		int  Add(const String &);                                                                   ///<添加字符串
		int  Add(const String &,int);                                                               ///<添加字符串
		void AddStrings(const StringList &);                                                   		///<添加字符串
		void Clear();                                                                               ///<删除列表中的所有字符串
		void Delete(int);                                                                           ///<删除列表中指定的字符串
		int  Find(const String &);                                                                  ///<查找字符串,未找到返回-1
		void Insert(int,const String &);                                                            ///<在指定位置插入一个字符串
		void Exchange(int,int);                                                                     ///<交换字符串

		String &GetString(int n)const{return *(Items[n]);}											///<取得指定行字符串

	public: //方法

		void LoadTxt(Stream *,CCP=ccpNone);                                                        	///<从流中加载一个字符串列表
		bool LoadTxt(const wchar_t *,CCP=ccpNone);                                                  ///<从文件中加载字符串列表
		bool LoadTxt(HAC *,const wchar_t *,CCP=ccpNone);											///<从HAC包的文件中加载字符串列表

		void SaveTxt(Stream *);                                                          			///<向流中写入当前字符串列表
		bool SaveTxt(const wchar_t *);                                                           	///<保存当前字符串列表到文件

	public:	//DataObject兼容方法(使用二进制流)

		bool LoadFromStream(Stream *);															///<从流中加载
		bool SaveToStream(Stream *);															///<保存到流中
	};
}//namespace hgl
#endif//HGL_STRINGLIST_INCLUDE
