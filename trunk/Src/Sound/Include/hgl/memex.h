#ifndef HGL_MEMEX_INCLUDE
#define HGL_MEMEX_INCLUDE

#include<hgl/DataType.H>
namespace hgl
{
	//以下4个函数的存在并不为追求效能，而是为兼容性
	void hgl_memcpy(void *,const void *,uint32);
	void hgl_memset(void *,uint8,uint32);
	void hgl_memmove(void *,const void *,uint32);
	int hgl_memcmp(const void *,const void *,uint32);

	uint32 memcount(const void *,uint32);                                                       	//8位内存累加
	uint32 memjumpcount(const void *,uint32,uint32);												//8位内存跳跃累加

	void memset16(const void *,uint16,uint32);                                                      //16位内存数值设置函数
	void memjumpset16(const void *,uint16,uint32,uint32);                                           //跳跃设置16位内存数值
	void memcpy16(const void *,const void *,uint32);                                                //16位内存复制函数
	void memmove16(const void *,const void *,uint32);                                               //16位内存移动函数
	void memnegative16(const void *,uint32);                                                        //16位内存取反函数

	void memset32(const void *,uint32,uint32);                                                      //32位内存数值设置函数
	void memjumpset32(const void *,uint32,uint32,uint32);                                           //跳跃设置32位内存数值
	void memcpy32(const void *,const void *,uint32);                                                //32位内存复制函数
	void memmove32(const void *,const void *,uint32);                                               //32位内存移动函数
	void memnegative32(const void *,uint32);                                                        //32位内存取反函数
}
#endif//HGL_MEMEX_INCLUDE