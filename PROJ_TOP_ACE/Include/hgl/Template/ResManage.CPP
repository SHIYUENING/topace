#ifndef HGL_RES_MANAGE_CPP
#define HGL_RES_MANAGE_CPP

#include<hgl/ResManage.H>
namespace hgl
{
	template<typename F,typename T>
	ResManage<F,T>::~ResManage()
	{
		Clear();
	}

	template<typename F,typename T>
	void ResManage<F,T>::Clear(T *obj)		///<资源释放虚拟函数
	{
#ifdef _DEBUG
		try
		{
			delete obj;
		}
		catch(...)
		{
			PutError(	L"ResManage::Clear() error! this=%p,obj=%p",this,obj);
		}
#else
		delete obj;
#endif//
	}

	template<typename F,typename T>
	void ResManage<F,T>::Clear()
	{
		int n=items.Count;

		while(n--)
		{
			ResItem *obj=items.GetItem(n);

			Clear(obj->data);
		}

		items.Clear();
	}

	template<typename F,typename T>
	T *ResManage<F,T>::Find(const F &flag)
	{
		int index=items.Find(flag);

		if(index==-1)
			return(NULL);
		else
			return(item[index]->data);
	}

	template<typename F,typename T>
	T *ResManage<F,T>::Get(const F &flag)
	{
		int index=items.Find(flag);

		if(index!=-1)
		{
			ResItem *obj=items.GetItem(index);

			//items[index]->count++;
			obj->count++;

//			return(items[index]->data);
			return obj->data;
		}

		T *data=Create(flag);

		if(data)
		{
			ResItem *obj=new ResItem;

			obj->flag	=flag;
			obj->count	=1;
			obj->data	=data;

			items.Add(obj);

			return(data);
		}

		return(NULL);
	}

	template<typename F,typename T>
	void ResManage<F,T>::ReleaseBySerial(int index)
	{
		if(index==-1)
		{
//        	ErrorHint(L"所释放的资源不存在");
			return;
		}

		ResItem *obj=items.GetItem(index);

		if(--obj->count<=0)       //正常应该==0
		{
			Clear(obj->data);

			items.DeleteBySerial(index);
		}
	}

	template<typename F,typename T>
	void ResManage<F,T>::Release(const F &flag)
	{
    	ReleaseBySerial(items.Find(flag));
	}

	template<typename F,typename T>
	void ResManage<F,T>::Release(T *td)
	{
		ReleaseBySerial(items.FindByData(td));
	}
}

namespace hgl
{
	template<typename T>
	T *ResManageByName<T>::Create(const String &name)
	{
		return(new T(name));
	}
}

namespace hgl
{
	template<typename T>
	void ResManageHAC<T>::InitPrivate()
	{
		hglSetPropertyRead(hac,this,ResManageHAC<T>::GetHac);
	}

	template<typename T>
	ResManageHAC<T>::ResManageHAC(HAC *_hac)
	{
		InitPrivate();

		hac_private=false;
		hac_data=_hac;
	}

	template<typename T>
	ResManageHAC<T>::ResManageHAC(const String &filename)
	{
		InitPrivate();

		hac_private=true;
		hac_data=OpenHAC(filename);
	}

	template<typename T>
	ResManageHAC<T>::~ResManageHAC()
	{
		if(hac_private&&hac_data)
			delete hac_data;
	}

	template<typename T>
	T *ResManageHAC<T>::Create(const String &name)
	{
		#ifdef _DEBUG
		if(!hac_data)
		{
        	PutError(L"创建资源时，HAC包还未加载。资源名称:%s",name.wc_str());
			return(NULL);
		}
		#endif//

		return(new T(hac_data,name));
	}
}
#endif//HGL_RES_MANAGE_CPP
