#ifndef HGL_OBJECT_BUFFER_INCLUDE
#define HGL_OBJECT_BUFFER_INCLUDE

#include<hgl/FinUseData.H>
#include<hgl/Str.H>
#include<hgl/HAC.H>
namespace hgl
{
	template<typename T> class ObjectBuffer:public FinUseData<String,T *>
    {
		typedef FinUseData<String,T *> fud_class;

        virtual bool Create(const String &,T *&);
    	void Clear(const String &,T *&);

    public:

    	ObjectBuffer(int max):fud_class(max){};
    	virtual ~ObjectBuffer();
	};

	template<typename T> class ObjectBufferFromHAC:public ObjectBuffer<T>
	{
    	bool hac_private;    

		HAC *hac_data;

		virtual bool Create(const String &,T *&);

		HAC *GetHac(){return hac_data;}
		void InitPrivate();

	public:

		Property<HAC *> hac;

	public:

    	ObjectBufferFromHAC(int max);
		ObjectBufferFromHAC(HAC *,int max);
		ObjectBufferFromHAC(const String &,int max);
		virtual ~ObjectBufferFromHAC();

		void SetHac(HAC *);
		void SetHac(const String &);
    };
}//namespace hgl
#include<hgl/template/ObjectBuffer.CPP>
#endif//HGL_OBJECT_BUFFER_INCLUDE
