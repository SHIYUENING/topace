public: //²Ù×÷·ûÖØÔØ

	String &	operator  =  (const String &);	
	String &	operator  += (const String &);
	String &	operator  << (const String &);
//	String  	operator  +  (const String &) const;


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
    
