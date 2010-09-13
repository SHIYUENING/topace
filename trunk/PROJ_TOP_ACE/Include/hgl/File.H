#ifndef HGL_FILE_INCLUDE
#define HGL_FILE_INCLUDE

namespace hgl
{
	wchar_t *MergeFilename(const wchar_t *,const wchar_t *);										///<组合路径名与文件名
	bool MergeFilename(wchar_t *,int,const wchar_t *,const wchar_t *);								///<组合路径名与文件名

	bool FileCopy(const wchar_t *,const wchar_t *);                                                 ///<文件复制
	bool FileDelete(const wchar_t *);                                                               ///<文件删除
	bool FileMove(const wchar_t *,const wchar_t *);                                                 ///<文件移动
	bool FileRename(const wchar_t *,const wchar_t *);                                               ///<文件改名
	bool FileConfirm(const wchar_t *);                                                              ///<文件确认是否存在
	bool FileComp(const wchar_t *,const wchar_t *);                                                 ///<文件比较

	bool FileCheckOpen(const wchar_t *);															///<尝试打开文件
	bool FileCheckOpen(const wchar_t *,const wchar_t *);											///<尝试打开文件

	int LoadFileToMemory(const wchar_t *,void **);                                                  ///<加载一个文件到内存
	bool SaveMemoryToFile(const wchar_t *,void *,int);                                              ///<保存一块内存成文件

	void *LoadFileToMemory(const wchar_t *,unsigned int,unsigned int,void *buf=0);					///<加载一个文件的一部分到内存
	bool SaveMemoryToFile(const wchar_t *,unsigned int,unsigned int,void *);						///<保存一块内存到一个文件

	int LoadTxtToMemory(const wchar_t *,wchar_t **);												///<加载文本文件到内存

	bool IsDirectory(const wchar_t *);                                                              ///<判断这个名称是否是目录

	bool MakePath(const wchar_t *);                                                                 ///<创建一个路径
	bool DeletePath(const wchar_t *);                                                               ///<删除一个路径
	void DeleteTree(const wchar_t *);																///<删除一个路径(包含所有文件)
	void GetCurrentPath(wchar_t *);                                                                 ///<取当前路径

	/**
	* 文件信息数据结构
	*/
	struct FileInfo								///文件信息
	{
		wchar_t name[1024];						///<文件名(不包含路径)
		wchar_t fullname[1024];					///<完整名称(包含路径)

		union
		{
			unsigned __int64 size;				///<文件长度

			struct
			{                                                           
				unsigned __int32 size_low;		///<文件长度低32位      
				unsigned __int32 size_high;		///<文件长度高32位
			};
		};

		union
		{
			unsigned __int32 attrib;			///<文件属性

			struct
			{
				bool directory:1;				///<是目录
				bool only_read:1;				///<是只读
			};
		};
	};


	/**
	* 枚举一个目录内的所有文件
	* @param folder_name 目录名称
	* @param find_name 查找用名称
	* @param data 自定义回传数据
	* @param proc_folder 处理目录
	* @param proc_file 处理文件
	* @param sub_folder 是否处理子目录
	* @param func 回调函数
	* @return 查找到文件数据,-1表示失败
	*/
	int EnumFile(const wchar_t *folder_name,const wchar_t *find_name,void *data,bool proc_folder,bool proc_file,bool sub_folder,void (__cdecl *func)(void *,hgl::FileInfo &));

	/**
	* 枚举一个目录内的所有文件
	* @param folder_name 目录名称
	* @param find_name 查找用名称
	* @param data 自定义回传数据
	* @param func 回调函数
	* @return 查找到文件数据,-1表示失败
	*/
	int EnumFile(const wchar_t *folder_name,const wchar_t *find_name,void *data,void (__cdecl *func)(void *,hgl::FileInfo &));

	/**
	* 卷信息数据结构
	*/
	struct VolumeInfo
	{
		enum DriverType
		{
			dtNone=0,				//未知类型

			dtRemovable,			//可移动设备
			dtFixed,				//固定设备
			dtRemote,				//远程设备
			dtCDROM,				//光盘驱动器
			dtRamDisk,				//内存虚拟设备

			dtVirtualCDROM,			//虚拟光盘驱动器

			dtEnd					//结束定义
		};

		wchar_t 			name[1024];			//卷名称

		wchar_t 			path[1024];			//卷所对应的路径名(注意:不是所有卷都有对应路径)

		DriverType 			driver_type;		//驱动器类型(注意:不是所有的卷都对应驱动器)

		unsigned __int32 	serial;				//卷序列号

		wchar_t				volume_label[256];	//卷标名称	

		wchar_t 			file_system[256];	//文件系统名称

		unsigned __int32 	filename_max_length;//文件名最大长度

		bool 				unicode;			//文件名支持UNICODE

		unsigned __int64	available_space;	//有效容量
		unsigned __int64 	total_space;		//总空量
		unsigned __int64 	free_space;			//自由容量
	};

	/**
	* 枚举当前计算机所有卷
	* @param data 用户自定义回传信息
	* @param func 回调函数
	* @param check_removable 检测可移除设备
	* @param check_remote 检测远程驱动器
	* @param check_cd 检测光盘
	* @return 查找到的卷数量，-1表示失败
	*/
	int EnumVolume(void *data,void (__cdecl *func)(void *,hgl::VolumeInfo &),bool check_removable=false,bool check_remote=false,bool check_cd=false);
}//namespace hgl
#endif//HGL_FILE_INCLUDE
