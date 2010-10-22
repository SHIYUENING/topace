#include "CharSysBace.h"

unsigned int GetWcharLenth(const wchar_t * Wchar)
{
	if(!Wchar)
		return 0;
	int WcharLenth=0;
	while(Wchar[WcharLenth]!=0)
		WcharLenth++;
	return WcharLenth;
}

wchar_t * ADDTwoWchar(const wchar_t * Wchar1,const wchar_t * Wchar2)
{
	int WcharLenth1=GetWcharLenth(Wchar1);
	int WcharLenth2=GetWcharLenth(Wchar2);
	if(WcharLenth1+WcharLenth2<=0)
		return 0;
	wchar_t * ResultsWchar=new wchar_t [WcharLenth1+WcharLenth2+1];
	for(int i=0;i<WcharLenth1;i++)
	{
		ResultsWchar[i]=Wchar1[i];
	}
	for(int i=0;i<WcharLenth2;i++)
	{
		ResultsWchar[i+WcharLenth1]=Wchar2[i];
	}
	ResultsWchar[WcharLenth1+WcharLenth2]=0;
	return ResultsWchar;
}

int ADDTwoWchar(wchar_t *ResultsWchar,int ResultsWcharArrayMAXSize,const wchar_t * Wchar1,const wchar_t * Wchar2)
{
	if((!ResultsWchar)||(ResultsWcharArrayMAXSize<2))
		return 0;
	int WcharLenth1=GetWcharLenth(Wchar1);
	int WcharLenth2=GetWcharLenth(Wchar2);
	if(WcharLenth1+WcharLenth2<=0)
		return 0;
	for(int i=0;i<WcharLenth1;i++)
	{
		if(i>=(ResultsWcharArrayMAXSize-1))
		{
			ResultsWchar[i]=0;
			return i;
		}
		ResultsWchar[i]=Wchar1[i];
	}
	for(int i=0;i<WcharLenth2;i++)
	{
		if(i>=(ResultsWcharArrayMAXSize-1))
		{
			ResultsWchar[i]=0;
			return i;
		}
		ResultsWchar[i+WcharLenth1]=Wchar2[i];
	}
	ResultsWchar[WcharLenth1+WcharLenth2]=0;
	return WcharLenth1+WcharLenth2;
}