#include "LockFPS.h"

CLockFPS::CLockFPS(void)
: oneframetimelimit(0.0)
, oneframetime(0.0)
{
}

CLockFPS::~CLockFPS(void)
{
}

void CLockFPS::Init(int LimitFPS)
{
	if(LimitFPS<=0)
		oneframetimelimit=0.0;
	else
		oneframetimelimit=(( double)1.0)/(( double)LimitFPS);
	QueryPerformanceCounter(&t1);
	QueryPerformanceFrequency(&feq);
}

void CLockFPS::Delay(__int64 Us)
{
	LARGE_INTEGER CurrTicks, TicksCount; 

    QueryPerformanceFrequency(&TicksCount);
    QueryPerformanceCounter(&CurrTicks); 

    TicksCount.QuadPart = TicksCount.QuadPart * Us / 1000000i64;
    TicksCount.QuadPart += CurrTicks.QuadPart; 

    while(CurrTicks.QuadPart<TicksCount.QuadPart)
        QueryPerformanceCounter(&CurrTicks);
}

void CLockFPS::LockFPS(void)
{
	 double waitTime=0.0;
	QueryPerformanceFrequency(&feq);
	QueryPerformanceCounter(&t2);
    if (t2.QuadPart >= t1.QuadPart)
	{
	    oneframetime=(( double)(t2.QuadPart-t1.QuadPart))/(( double)feq.QuadPart);
		
    }
	else
		return;
	//QueryPerformanceCounter(&t1);

	 double SleepTime=(oneframetimelimit*1000.0-oneframetime*1000.0);
	if(SleepTime>=1.5)
	{
		Sleep(max(int(SleepTime-1.5),0));
		QueryPerformanceFrequency(&feq);
		QueryPerformanceCounter(&t2);
		if (t2.QuadPart >= t1.QuadPart)
			waitTime=(( double)(t2.QuadPart-t1.QuadPart))/(( double)feq.QuadPart);
		else
			return;
		SleepTime=(oneframetimelimit-waitTime)*1000.0;
	}
	QueryPerformanceFrequency(&feq);
	QueryPerformanceCounter(&t2);
    if (t2.QuadPart >= t1.QuadPart)
	{
	    waitTime=(( double)(t2.QuadPart-t1.QuadPart))/(( double)feq.QuadPart);
		
    }
	else
		return;

	Delay(__int64((oneframetimelimit-waitTime)*1000000));
	QueryPerformanceCounter(&t1);
}
