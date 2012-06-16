#ifndef HGL_CLASLIST_CPP
#define HGL_CLASLIST_CPP

#include<hgl/ClasList.H>
namespace hgl
{
	/**
	* 本类构造函数
	* @param type_count 数据类型数量
	* @param mt 是否允许数据多类型
	*/
	template<typename T>
	ClasList<T>::ClasList(int type_count,bool mt)
	{
		MultiType=mt;
		TypeCount=type_count;

		clas_object=new List<T *>[type_count];
	}

	template<typename T>
	ClasList<T>::~ClasList()
	{
		delete[] clas_object;
	}

	template<typename T>
	int ClasList<T>::CheckObjectType(T *)
	{
		return(-1);
	}

	template<typename T>
	bool ClasList<T>::CheckObjectAttrib(T *,int)
	{
		return(false);
	}

	template<typename T>
	void ClasList<T>::Clear()
	{
		int n=TypeCount;

		while(n--)
			clas_object[n].Clear();

		all_object.Clear();
	}

	template<typename T>
	bool ClasList<T>::Unlink(T *obj)
	{
		if(MultiType)
		{
			int n=TypeCount;

			while(n--)
				clas_object[n].Delete(obj);
		}
		else
			clas_object[CheckObjectType(obj)].Delete(obj);

		return all_object.Unlink(obj);
	}

	template<typename T>
	void ClasList<T>::UnlinkAll()
	{
		int n=TypeCount;

		while(n--)
			clas_object[n].Clear();

		all_object.UnlinkAll();
	}

	template<typename T>
	bool ClasList<T>::Delete(T *obj)
	{
		if(MultiType)
		{
			int n=TypeCount;

			while(n--)
				clas_object[n].Delete(obj);
		}
		else
			clas_object[CheckObjectType(obj)].Delete(obj);

		return all_object.Delete(obj);
	}

	template<typename T>
	void ClasList<T>::Add(T *obj)
	{
		if(MultiType)
		{
			int n=TypeCount;

			while(n--)
				if(CheckObjectAttrib(obj,n))
					clas_object[n].Add(obj);
		}
		else
			clas_object[CheckObjectType(obj)].Add(obj);

		all_object+=obj;
	}
}
#endif//HGL_CLASLIST_CPP
