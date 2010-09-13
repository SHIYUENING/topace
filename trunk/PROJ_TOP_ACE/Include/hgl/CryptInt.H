#ifndef HGL_CRYPTINT_INCLUDE
#define HGL_CRYPTINT_INCLUDE
namespace hgl
{
	/**
	* 加密int型变量类，这个类型可以直接替代int使用，由于它在内存中将数据以加密形式保存，所以可以防止一些内存修改工具对本身应用程序数据的监视。
	*/
	class CryptInt                                                                                  ///加密型int变量类
	{
	protected:

		int value;
		int key;

	protected:

		virtual int GetValue();
		virtual void SetValue(int);

	public:

		CryptInt();
		CryptInt(int);

		operator int () {return(GetValue());}

		void operator = (int v){SetValue(v);}

		int operator + (int v){return(GetValue()+v);}
		int operator - (int v){return(GetValue()-v);}
		int operator * (int v){return(GetValue()*v);}
		int operator / (int v){return(GetValue()/v);}
		int operator % (int v){return(GetValue()%v);}

		void operator += (int v){SetValue(GetValue()+v);}
		void operator -= (int v){SetValue(GetValue()-v);}
		void operator *= (int v){SetValue(GetValue()*v);}
		void operator /= (int v){SetValue(GetValue()/v);}

		int operator ++ (int) {int r=GetValue();SetValue(r+1);return(r);}                           ///<后置++
		int operator -- (int) {int r=GetValue();SetValue(r-1);return(r);}                           ///<后置--

		int operator ++ () {SetValue(GetValue()+1);return(GetValue());}                             ///<前置++
		int operator -- () {SetValue(GetValue()-1);return(GetValue());}                             ///<前置--

		bool operator > (int v){return(GetValue()> v);}
		bool operator >=(int v){return(GetValue()>=v);}
		bool operator < (int v){return(GetValue()< v);}
		bool operator <=(int v){return(GetValue()<=v);}

		bool operator ==(int v){return(GetValue()==v);}
		bool operator !=(int v){return(GetValue()!=v);}
	};
}//namespace hgl
#endif//HGL_CRYPTINT_INCLUDE
