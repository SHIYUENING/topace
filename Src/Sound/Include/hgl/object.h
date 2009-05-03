#ifndef HGL_OBJECT_INCLUDE
#define HGL_OBJECT_INCLUDE

#include<hgl/_Object.H>
#include<hgl/String.H>
namespace hgl
{
	class ObjectControl;
	/**
	* Object����HGL�����������Ϸ������Ļ���,���ṩ����þ߱������л���Ҫ�ء�
	*/
	class Object:public _Object                                                                     ///�������
	{
		#include<hgl/Object.Attrib.H>

	public:	//����

		String      					Name;                                                       ///<��������

		PropertyObject<ObjectControl>	SuperObject;                                                ///<�ϼ�����

		Property<uint>					Attrib;                                                     ///<��������

		Property<bool>					Enabled;                                                    ///<�����Ƿ�����

	public: //�¼�

		//����/�Ͽ��¼�,��ʽΪ OnLink(�ϼ�����,������)

		DefEvent(void,OnLink,(Object *,Object *));													///<�����¼�
		DefEvent(void,OnUnlink,(Object *,Object *));												///<�Ͽ������¼�

	public:

		Object();                                                                                   //���๹�캯��
		Object(const String &);																		//���๹�캯��
		virtual ~Object();                                                                          //������������

		virtual void Destroy();                                                                     //<���ٵ�ǰ����
	};
}
#endif//HGL_OBJECT_INCLUDE