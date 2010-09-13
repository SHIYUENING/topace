#ifndef HGL_PROPERTY_INCLUDE
#define HGL_PROPERTY_INCLUDE

#include<hgl/platform/compiler/EventFunc.H>
#include<hgl/LogInfo.H>
namespace hgl
{
	template<typename T> class Property
	{
	public:

		DefEvent(T,Get,());
		DefEvent(void,Set,(T));

	public:

		#ifdef __BORLANDC__
			Property()
			{
				Get=0;
				Set=0;
			}
		#else
			Property()
			{
				Get.This=0;Get.vp=0;
				Set.This=0;Set.vp=0;
			}
		#endif//

		virtual ~Property()	{}

		operator T() const
		{
			#ifdef _DEBUG
				#ifdef __BORLANDC__
				if(Get==0)
				#else
				if(Get.omf==0)
				#endif//				
					PutError(L"错误的属性调用，Get==NULL");
			#endif//

			return CallEvent(Get,());
		}
		
		void operator = (T v)
		{
			CallEvent(Set,(v));
		}

		void operator = (const Property<T> &v)
		{
        	CallEvent(Set,(v.operator T()));
		}

        T operator !(){ return !(operator T());}
        T operator ~(){ return ~(operator T());}

		T operator ++ ()	{	T v=operator T();   CallEvent(Set,(++v));   return v;	}           ///<前置++
		T operator -- ()	{	T v=operator T();   CallEvent(Set,(--v));	return v;   }           ///<前置--

		T operator ++ (int)	{	T r,v;  v=operator T(); r=v; CallEvent(Set,(++v)); return r;	}   ///<后置++
		T operator -- (int)	{	T r,v;  v=operator T(); r=v; CallEvent(Set,(--v)); return r;	}   ///<后置--

		T operator >> (int n)	{	return (operator T())>>n;}
		T operator << (int n)	{	return (operator T())<<n;}

		void operator += (T v)	{	if(v){CallEvent(Set,(operator T() + v));}	}
		void operator -= (T v)	{	if(v){CallEvent(Set,(operator T() - v));}	}
		void operator *= (T v)	{	CallEvent(Set,(operator T() * v));	}
		void operator /= (T v)	{	CallEvent(Set,(operator T() / v));	}
		void operator %= (T v)	{	CallEvent(Set,(operator T() % v));	}

        void operator &= (T v)	{	CallEvent(Set,(operator T() & v));	}
        void operator |= (T v)	{	CallEvent(Set,(operator T() | v));	}

		void operator >>= (int n)	{	CallEvent(Set,((operator T())>>n));}
		void operator <<= (int n)	{	CallEvent(Set,((operator T())<<n));}
	};

	template<typename T> class PropertyObject:public Property<T *>
	{
	public:

		T *operator ->()const
		{
			return CallEvent(Property<T *>::Get,());
		}

		void operator =(void *pointer)
		{
            CallEvent(Property<T *>::Set,((T *)pointer));
		}
	};

	#ifdef __BORLANDC__
		#define hglSetPropertyRead(name,tp,get)		{name.Get=tp->get;}
		#define hglSetPropertyWrite(name,tp,set)	{name.Set=tp->set;}
	#else
		#define hglSetPropertyRead(name,tp,get)		{	\
														name.Get.vp_this=tp;	\
														name.Get.omf=ObjectMemberFunc(&get);	\
													}

		#define hglSetPropertyWrite(name,tp,set)	{	\
														name.Set.vp_this=tp;	\
														name.Set.omf=ObjectMemberFunc(&set);	\
													}
	#endif//

		#define hglSetProperty(name,tp,get,set)		{	\
														hglSetPropertyRead(name,tp,get);	\
														hglSetPropertyWrite(name,tp,set);	\
                                                	}

	template<typename T> class OnlyReadProperty
	{
    	T *data_pointer;

	public:

		OnlyReadProperty(){data_pointer=0;}
		OnlyReadProperty(T &dp){data_pointer=&dp;}
		OnlyReadProperty(T *dp){data_pointer=dp;}
		virtual ~OnlyReadProperty(){}

		void MapGet(T *dp){data_pointer=dp;}

		operator T() const{return *data_pointer;}

		T *operator ->()const{return data_pointer;}
	};
}//namespace hgl
#endif//HGL_PROPERTY_INCLUDE
