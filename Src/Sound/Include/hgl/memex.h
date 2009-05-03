#ifndef HGL_MEMEX_INCLUDE
#define HGL_MEMEX_INCLUDE

#include<hgl/DataType.H>
namespace hgl
{
	//����4�������Ĵ��ڲ���Ϊ׷��Ч�ܣ�����Ϊ������
	void hgl_memcpy(void *,const void *,uint32);
	void hgl_memset(void *,uint8,uint32);
	void hgl_memmove(void *,const void *,uint32);
	int hgl_memcmp(const void *,const void *,uint32);

	uint32 memcount(const void *,uint32);                                                       	//8λ�ڴ��ۼ�
	uint32 memjumpcount(const void *,uint32,uint32);												//8λ�ڴ���Ծ�ۼ�

	void memset16(const void *,uint16,uint32);                                                      //16λ�ڴ���ֵ���ú���
	void memjumpset16(const void *,uint16,uint32,uint32);                                           //��Ծ����16λ�ڴ���ֵ
	void memcpy16(const void *,const void *,uint32);                                                //16λ�ڴ渴�ƺ���
	void memmove16(const void *,const void *,uint32);                                               //16λ�ڴ��ƶ�����
	void memnegative16(const void *,uint32);                                                        //16λ�ڴ�ȡ������

	void memset32(const void *,uint32,uint32);                                                      //32λ�ڴ���ֵ���ú���
	void memjumpset32(const void *,uint32,uint32,uint32);                                           //��Ծ����32λ�ڴ���ֵ
	void memcpy32(const void *,const void *,uint32);                                                //32λ�ڴ渴�ƺ���
	void memmove32(const void *,const void *,uint32);                                               //32λ�ڴ��ƶ�����
	void memnegative32(const void *,uint32);                                                        //32λ�ڴ�ȡ������
}
#endif//HGL_MEMEX_INCLUDE