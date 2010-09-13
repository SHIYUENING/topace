#ifndef HGL_EVENT_FUNC_INCLUDE
#define HGL_EVENT_FUNC_INCLUDE

#include<hgl/_Object.H>
namespace hgl
{
	#ifdef __BORLANDC__	
	
		#define	SetEventCall(event_obj,obj_this,event_func)		event_obj=obj_this->event_func
		#define SafeCallEvent(event_obj,intro)					{if(event_obj)event_obj intro;}
		#define CallEvent(event_obj,intro)						event_obj intro
		#define DefEvent(result,name,intro)				    	result (__closure *name)intro

	#else
	
		template <typename T> struct EventFunc
		{
			union
			{
				void *vp_this;
				_Object *This;
			};

			union
			{
				void *vp;
				T Func;
				ObjectMemberFunc omf;
			};

			void operator = (void *v)
			{
				if(v==0)
					vp=0;
			}

			bool operator == (void *v)
			{
				return(vp==v);
			}

			bool operator != (void *v)
			{
				return(vp!=v);
			}
		};

		#define SetEventCall(event_obj,obj_this,event_func)	{	\
																event_obj.vp_this=obj_this;	\
																void *tmp=&(event_obj.vp);	\
																__asm mov esi,tmp	\
																__asm mov eax,event_func	\
																__asm mov [esi],eax	\
															}

															//event_obj.Func=(&event_func);
															//event_obj.omf=ObjectMemberFunc(&event_func);
															
		#define CallEvent(event_obj,intro)					((event_obj.This->*(event_obj.Func))intro)				//(*(event_obj.This).*(event_obj.Func))

		#define SafeCallEvent(event_obj,intro)				{if(event_obj.vp)CallEvent(event_obj,intro);}

		#define DefEvent(result,name,intro)					EventFunc<result (_Object:: *)intro> name;

	#endif//

	/*

	使用方法:

		class Example
		{
			//原Borland/CodeGear方式
			void (__closure *OnClick)(Object *);

			//现通用方式
			DefEvent(void,OnClick,(Object *));
		};

		void Test::ClickProc(Object *);

		void Test::func()
		{
			Example *exp;

			{
				//原Borland/CodeGear方式
				exp->OnClick=this->ClickProc;
				或
				exp->OnClick=ClickProc;

				//现通用方式
				SetEventCall(exp,this,Test::ClickProc);
			}

			{
				//原Borland/CodeGear方式
				exp->OnClick(NULL);

				//现通用方式
				CallEvent(exp->OnClick,(NULL));
			}
		}

	*/
};
#endif//HGL_EVENT_FUNC_INCLUDE
