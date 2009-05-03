#ifndef HGL_OBJECT_BUFFER_CPP
#define HGL_OBJECT_BUFFER_CPP

#include<hgl/ObjectBuffer.H>
#include<hgl/Stream.H>

#ifdef _DEBUG
#include<hgl/Loginfo.H>
#endif//_DEBUG

namespace hgl
{                       
	template<typename T>
    bool ObjectBuffer<T>::Create(const String &name,T *&item)
    {
    	item=new T(name);

        return(true);
    }
    
	template<typename T>
	void ObjectBuffer<T>::Clear(const String &,T *&item)
    {
		delete item;
	}

	template<typename T>
	ObjectBuffer<T>::~ObjectBuffer()
	{
		fud_class::Clear();
    }
}

namespace hgl
{
	template<typename T>
	void ObjectBufferFromHAC<T>::InitPrivate()
	{
		hglSetPropertyRead(hac,this,ObjectBufferFromHAC<T>::GetHac);
	}

	template<typename T>
	ObjectBufferFromHAC<T>::ObjectBufferFromHAC(int max):ObjectBuffer<T>(max)
	{
		hac_data=NULL;
		hac_private=false;

		InitPrivate();
	}

	template<typename T>
	ObjectBufferFromHAC<T>::ObjectBufferFromHAC(HAC *_hac,int max):ObjectBuffer<T>(max)
	{
    	SetHac(_hac);
		InitPrivate();
	}

	template<typename T>
	ObjectBufferFromHAC<T>::ObjectBufferFromHAC(const String &fn,int max):ObjectBuffer<T>(max)
	{
		SetHac(fn);		
		InitPrivate();
	}

	template<typename T>
	ObjectBufferFromHAC<T>::~ObjectBufferFromHAC()
	{
		if(hac_private)
			delete hac_data;
	}
	                 
	template<typename T>
	bool ObjectBufferFromHAC<T>::Create(const String &name,T *&item)
	{
		if(!hac_data)return(false);

		if(hac_data->FindFile(name))
		{
			item=new T(hac_data,name);

			return(true);
		}
		else
		{
        	ErrorHint(L"要取得的资源没有找到:%s",name.wc_str());
			return(false);
		}
	}
	
	template<typename T>
	void ObjectBufferFromHAC<T>::SetHac(HAC *_hac)
	{
		hac_data=_hac;

		hac_private=false;
	}

	template<typename T>
	void ObjectBufferFromHAC<T>::SetHac(const String &fn)
	{
		hac_data=OpenHAC(fn);

		hac_private=true;
	}
}

#endif//HGL_OBJECT_BUFFER_CPP