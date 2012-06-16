public: //操作符重载

	String  	operator  +  (const String &) const;
	String		operator  +	 (const wchar_t *) const;
	String		operator  +	 (const wchar_t) const;

	String &	operator  =  (const String &);	
	String &	operator  += (const String &);
	String &	operator  << (const String &);

	String &	operator  += (const wchar_t);
	String &	operator  += (const wchar_t *);
	String &	operator  << (const wchar_t);
	String &	operator  << (const wchar_t *);

	CompOperator(const wchar_t *,Strcmp);
	CompOperator(const String &,Strcmp);
/*	#define oper_over(type) bool operator type (const wchar_t *) const;	\
                        	bool operator type (const String &) const

    oper_over(==);
    oper_over(!=);
    oper_over(> );
    oper_over(< );
    oper_over(>=);
    oper_over(<=);

	#undef oper_over
*/
	operator const wchar_t * ()const {return GetString();}
    
