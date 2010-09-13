#ifndef HGL_TIME_INCLUDE
#define HGL_TIME_INCLUDE

#include<hgl/DataType.H>
#include<hgl/DataObject.H>
namespace hgl
{
	/**
	* 时间类，这个类用来保存和计算时间。
	*
	* 当您对Hours,Minutes,Seconds中任何一个值进行加减时，其它值都会自动计算。如：11:30这个值，使用Minutes+=55。会自动计算出55分钟后的时间，值为12:25
	*/
	class Time:public DataObject                                                                    ///时间类
	{
		int hours;
		int minutes;
		int seconds;
		int mill;

	protected:

		int GetHours(){return hours;}
		int GetMinutes(){return minutes;}
		int GetSeconds(){return seconds;}
		int GetMill(){return mill;}

		void SetHours(int);
		void SetMinutes(int);
		void SetSeconds(int);
		void SetMill(int);

		void InitPrivate();

	public:

		Property<int> Hour;                                                                         ///<时
		Property<int> Minute;                                                                       ///<分
		Property<int> Second;                                                                       ///<秒
		Property<int> MilliSecond;                                                                  ///<千分秒

	public:

		Time(int=0);
		Time(int,int,int,int);

		void Sync();                                                                                ///<和系统时间同步

		bool SaveToStream(Stream *);
		bool LoadFromStream(Stream *);
	};

	/**
	* 日期类，这个类用来保存和计算日期。带有闰年的处理
	*
	* 当您对Year,Month,Day中任意一个值进行修改时，其它值都会自动跟着计算。如1981-4-17,如果使用Day+=400，会自动计算出400天之后的日期，结果是1982-5-21
	*/
	class Date:public DataObject                                                                    ///日期类
	{
		int year;
		int month;
		int day;

		int max_days;

	protected:

		int GetYear(){return year;}
		int GetMonth(){return month;}
		int GetDay(){return day;}
		int GetMaxDays(){return max_days;}

		void SetYear(int y){year=y;}
		void SetMonth(int);
		void SetDay(int);

		void InitPrivate();

	public:

		Property<int> Year;                                                                         ///<年
		Property<int> Month;                                                                        ///<月
		Property<int> Day;                                                                          ///<日

		Property<int> MaxDays;                                                                      ///<本月最大天数

	public:

		Date();
		Date(int,int,int);

		void Sync();                                                                                ///<和系统日期同步

		bool SaveToStream(Stream *);
		bool LoadFromStream(Stream *);
	};
}//namespace hgl
#endif//HGL_TIME_INCLUDE
