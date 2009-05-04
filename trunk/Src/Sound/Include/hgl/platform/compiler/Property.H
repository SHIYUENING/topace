#ifndef HGL_PROPERTY_INCLUDE
#define HGL_PROPERTY_INCLUDE

#include<hgl/platform/compiler/EventFunc.H>
#include<hgl/LogInfo.H>
namespace hgl
{
	template<typename T> class Property
	{
	protected:
	
		typedef DefEvent(T,GetPropertyFunc,());
		typedef	DefEvent(void,SetPropertyFunc,(T));

		GetPropertyFunc Get;
		SetPropertyFunc Set;

	public:

		#ifdef __BORLANDC__
			Property()
			{
				Get=0;
				Set=0;
			}

			void Map(GetPropertyFunc OnGet,SetPropertyFunc OnSet)
			{
				Get=OnGet;
				Set=OnSet;
			}

			void MapGet(GetPropertyFunc OnGet)
			{
				Get=OnGet;
			}

			void MapSet(SetPropertyFunc OnSet)
			{
				Set=OnSet;
			}
		#else
			Property()
			{
				Get.This=0;Get.vp=0;
				Set.This=0;Set.vp=0;
			}

			void Map(void *tp,ObjectMemberFunc OnGet,ObjectMemberFunc OnSet)
			{
				Get.This=(_Object *)tp;	Get.omf=OnGet;
				Set.This=(_Object *)tp;	Set.omf=OnSet;
			}

			void MapGet(void *tp,ObjectMemberFunc OnGet)
			{
				Get.This=(_Object *)tp;	Get.omf=OnGet;
			}

			void MapSet(void *tp,ObjectMemberFunc OnSet)
			{
				Set.This=(_Object *)tp;	Set.omf=OnSet;
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

		void operator ++ ()	{	CallEvent(Set,(++(operator T())));	}
		void operator -- ()	{	CallEvent(Set,(++(operator T())));	}
		T operator ++ (int)	{	T v=operator T(); ++v; CallEvent(Set,(v)); return v;	}
		T operator -- (int)	{	T v=operator T(); --v; CallEvent(Set,(v)); return v;	}

		void operator += (T v)	{	CallEvent(Set,(operator T() + v));	}
		void operator -= (T v)	{	CallEvent(Set,(operator T() - v));	}
		void operator *= (T v)	{	CallEvent(Set,(operator T() * v));	}
		void operator /= (T v)	{	CallEvent(Set,(operator T() / v));	}
		void operator %= (T v)	{	CallEvent(Set,(operator T() % v));	}
	};

	template<typename T> class PropertyObject:public Property<T *>
	{
	public:

		T *operator ->()const
		{
			return CallEvent(Get,());
		}

		void operator =(void *pointer)
		{
            CallEvent(Set,((T *)pointer));
		}
	};

	#ifdef __BORLANDC__
		#define hglSetProperty(name,tp,get,set)		name.Map(tp->get,tp->set);
		#define hglSetPropertyRead(name,tp,get)		name.MapGet(tp->get);
		#define hglSetPropertyWrite(name,tp,set)	name.MapSet(tp->set);
	#else
		#define hglSetProperty(name,tp,get,set)		name.Map(tp,ObjectMemberFunc(&get),ObjectMemberFunc(&set))
		#define hglSetPropertyRead(name,tp,get)		name.MapGet(tp,ObjectMemberFunc(&get))
		#define hglSetPropertyWrite(name,tp,set)	name.MapSet(tp,ObjectMemberFunc(&set))
	#endif//

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
}
#endif//HGL_PROPERTY_INCLUDE
