#ifndef HGL_OTHER_INCLUDE
#define HGL_OTHER_INCLUDE

#include<hgl/file.h>
#include<hgl/memex.h>
#include<hgl/String.H>

namespace hgl   //ϵͳ�Ի���
{
//	bool SelectColorDialog(uint8 &,uint8 &,uint8 &);                        						//�Ի���: ѡ��һ����ɫ
//	bool SelectFontDialog(wchar_t *,int);															//�Ի���: ѡ��һ������

//	bool SelectFolderDialog(wchar_t *,int);															//�Ի���: ѡ��һ���ļ���

	bool OpenFileDialog(wchar_t *,int,const wchar_t *filter=NULL,int=0);							//�Ի���: ��һ���ļ�
	bool SaveFileDialog(wchar_t *,int,const wchar_t *filter=NULL,int=0,const wchar_t *def_ext=0);	//�Ի���: ����һ���ļ�
}

namespace hgl
{
	/**
	* ��Щ����һ�������׼��C�⺯��������ͬ�����ṩ������Ϊ�˸��ߵİ�ȫ�Ժ������ԡ�<br>
	* �����ֿռ��ѱ��Զ����������������ֶ����á������޷�������SDKͬ����������ʱ�����ֶ���ʶ���ֿռ䡣
	*/
	namespace str	///�ַ�����ش�������ռ���ֿռ�
	{
		int strlen(const wchar_t *);																///<�����ַ�������
		void strcpy(wchar_t *,const wchar_t *);														///<�����ַ���
		void strcpy(wchar_t *,const wchar_t *,int);													///<�����ַ�������ָ����󳤶�
		void strcat(wchar_t *,const wchar_t *);														///<���������ַ���
		void strcat(wchar_t *,const wchar_t *,int);													///<���������ַ���
		wchar_t *strchr(const wchar_t *,const wchar_t);												///<���ַ����в���ĳ���ַ�
		wchar_t *strchr(const wchar_t *,const wchar_t,int);											///<���ַ����в���ĳ���ַ�
		wchar_t *strrchr(const wchar_t *,const wchar_t);											///<�ӽ�����ʼ��ǰ����ĳ���ַ�
		int strcmp(const wchar_t *,const wchar_t *);												///<�Ƚ��ַ���
		int strcmp(const wchar_t *,const wchar_t *,int);											///<�Ƚ��ַ���
		wchar_t *strstr(wchar_t *,const wchar_t *);													///<��һ���ַ����в���ĳ���ַ���
		void sprintf(wchar_t *,const wchar_t *,...);												///<��ʽ���ַ���

		bool ReplaceExtName(const wchar_t *,wchar_t *,wchar_t *);									///<�滻��չ��
		bool ReplaceExtName(wchar_t *,wchar_t *);													///<�滻��չ��

		wchar_t *ReplaceChar(wchar_t *,const wchar_t,const wchar_t);                                ///<�滻һ���ַ����е�ĳ���ַ�

		wchar_t *UpperString(wchar_t *);                                                            ///<���ַ����е�Сд��ĸȫ��תΪ��д
		wchar_t *LowerString(wchar_t *);                                                            ///<���ַ����еĴ�д��ĸȫ��תΪСд

		void UpperString(const wchar_t *,wchar_t *);                                                ///<���ַ����е�Сд��ĸȫ��תΪ��д
		void LowerString(const wchar_t *,wchar_t *);                                                ///<���ַ����еĴ�д��ĸȫ��תΪСд

		wchar_t *CreateCopy(const wchar_t *,int=-1);												///<����һ������

		int StatChar(wchar_t *,wchar_t);                                                            ///<ͳ�����ַ�����ĳ���ַ��ĳ��ִ���
		int StatLine(wchar_t *);                                                                    ///<ͳ���ַ���������

		int 	wtoi	(const wchar_t *);															///<ת��һ���ַ�����int��
		uint 	wtou	(const wchar_t *);															///<ת��һ���ַ�����uint��
		int64 	wtoi64	(const wchar_t *);															///<ת��һ���ַ�����int64��
		uint64 	wtou64	(const wchar_t *);															///<ת��һ���ַ�����uint64��
		float	wtof	(const wchar_t *);															///<ת��һ���ַ�����float��
		double	wtod	(const wchar_t *);															///<ת��һ���ַ�����double��
		bool 	wtob	(const wchar_t *);															///<ת��һ���ַ�����bool��

		wchar_t *itow(wchar_t *,int,int64);															///<ת��һ��int����ֵ���ַ���
		wchar_t *utow(wchar_t *,int,uint64);														///<ת��һ��uint����ֵ���ַ���
		wchar_t *ftow(wchar_t *,int,double);														///<ת��һ��double����ֵ���ַ���

		bool __inline isdigit(wchar_t ch){return((ch>=L'0'&&ch<=L'9')?true:false);}

		void ConvertNumber(wchar_t *,uint64);
	}
	using namespace str;
}

namespace hgl   //У��/�����㷨
{
	struct MD5Context;

	typedef uint8 MD5Code[16];				//MD5����
	
	void MD5Init(struct MD5Context *ctx);       
	void MD5Update(struct MD5Context *ctx, unsigned char const *buf, unsigned len);
	void MD5Final(unsigned char digest[16], struct MD5Context *ctx);

	void CountMD5(const void *,uint32,MD5Code &);
	bool GetMD5(const wchar_t *,MD5Code &);

	void StrToMD5(const wchar_t *,MD5Code &);
	void MD5ToStr(const MD5Code &,wchar_t *);

	void CountSHA1(uint8 *,uint32,uint8 [20]);

	void AesEncrypt(uint8 [16],uint8 *,int);					//AES����
	void AesDecrypt(uint8 [16],uint8 *,int);					//AES����

	void RC4Encrypt(uint8 *,int,uint8 *,int);

	void OverflowEncrypt(void *,void *,int,void *,int);			//�������(��ȼ���)
	void OverflowDecrypt(void *,void *,int,void *,int);			//�������
}         

namespace hgl   //����,����
{
	typedef DefEvent(int,COMPFUNC,(void *,void *,uint));

	void HeapSort(void *,int,int,COMPFUNC);                                                      	//�������㷨

	int DichFind(void *,int,int,void *);                                                            //2�ֲ���
	int DichFind(void *,int,int,void *,COMPFUNC);                                                   //2�ֲ���
}

namespace hgl   //��ֵ
{
	float SSE_Sqrt(float);																			///<SSEָ�����ƽ����

    uint32 	FastRand();																				///<���ٲ���һ�������

	/**
    * ����һ�����������ָ�����ޡ�
	* @param max_value ����ֵ
	* @return ���ֵ,<max_value
	*/
	uint32 	__inline FastRand(uint32 max_value)														///<���ٲ���һ�����������ָ������
	{
		return FastRand()%max_value;
	}

	/**
	* ��ָ����Χ�ڲ���һ�����ֵ����ָ������
	* @param v1 ��Сֵ
	* @param v2 ���ֵ
	* @param p ����,Ĭ��Ϊ1
	* @return ���ֵ
	*/
	int 	__inline FastRand(int v1,int v2,int p=1)												///<���ٲ���һ�������(ָ����Χ����ָ������)
	{
		if(v1<v2)
			return v1+(FastRand()%((v2-v1)/p+1))*p;
		else
			return v2+(FastRand()%((v1-v2)/p+1))*p;
	}

	/**
	* ��ָ����Χ�ڲ���һ�����ֵ����ָ������
	* @param v1 ��Сֵ
	* @param v2 ���ֵ
	* @param p ����
	* @return ���ֵ
	*/
	double 	__inline FastRand(double v1,double v2,double p)											///<���ٲ���һ�������(ָ����Χ����ָ������)
	{
		if(v1<v2)
		{
			int pos=(v2-v1)/p+1;
			int val=FastRand()%pos;

			return v1+val*p;
		}
		else
		{       
			int pos=(v1-v2)/p+1;
			int val=FastRand()%pos;

			return v2+val*p;
		}
    }
}

namespace hgl   //ʱ��
{
	/**
	* ʱ����غ�����������ֿռ�<br>
	* ע�⣺GetTime/GetMicroTime/GetDoubleTime����ʱ�䲻���Ի���
	*/
	namespace time		///ʱ�����ֿռ�
	{
		uint64 GetTime();																			///<ȡ�õ�ǰʱ��(��λǧ��֮һ��)
		uint64 GetMicroTime();																		///<ȡ�õ�ǰʱ��(��λ�����֮һ��)
		double GetDoubleTime();																		///<ȡ�õ�ǰʱ��(˫���ȣ���λ��)
	}

    using namespace time;
}

namespace hgl   //����
{
	void SetExpendString(const String &,const String &);											///<����������չ�ַ���
	void ClearExpendString(const String &);															///<���������չ�ַ���
	bool GetExpendString(const String &,String &);													///<ȡ��������չ�ַ���

	bool ConvertExpendString(const String &,String &);												///<ת��������չ�ַ���

	/**
	* �뱾�ز���ϵͳ��ع��ܺ��������ֿռ�
	*/
	namespace os		///<����ϵͳ��ع������ֿռ�
	{
		void PopupWebBrowser(const wchar_t *);                                                      ///<������ҳ�����
		void PopupEmailClient(const wchar_t *,const wchar_t *sub=NULL);                             ///<���������ʼ��ͻ���

		void CreateTempFileName(String &);															///<������ʱ�ļ�����

		void CopyTextToClipboard(const wchar_t *);													///<�����ַ�����������
		const wchar_t *GetTextFromClipboard();														///<�Ӽ�����ȡ���ַ���

		bool CreateShortCut(const wchar_t *,const wchar_t *,const wchar_t *w=0,const wchar_t *p=0);	///<������ݷ�ʽ
	}

	using namespace os;

	class Stream;

	bool DiscCheck(Stream *,const wchar_t *,const wchar_t *);										///<��Ƭ���
}

#endif//HGL_OTHER_INCLUDE