#include "CharSysBace.h"

unsigned int GetCharLenth(const wchar_t * Char)
{
	if(!Char)
		return 0;
	int CharLenth=0;
	while(Char[CharLenth]!=0)
		CharLenth++;
	return CharLenth;
}
unsigned int GetCharLenth(const char * Char)
{
	if(!Char)
		return 0;
	int CharLenth=0;
	while(Char[CharLenth]!=0)
		CharLenth++;
	return CharLenth;
}
wchar_t * ADDTwoChar(const wchar_t * Char1,const wchar_t * Char2)
{
	int CharLenth1=GetCharLenth(Char1);
	int CharLenth2=GetCharLenth(Char2);
	if(CharLenth1+CharLenth2<=0)
		return 0;
	wchar_t * ResultsChar=new wchar_t [CharLenth1+CharLenth2+1];
	for(int i=0;i<CharLenth1;i++)
	{
		ResultsChar[i]=Char1[i];
	}
	for(int i=0;i<CharLenth2;i++)
	{
		ResultsChar[i+CharLenth1]=Char2[i];
	}
	ResultsChar[CharLenth1+CharLenth2]=0;
	return ResultsChar;
}
char * ADDTwoChar(const char * Char1,const char * Char2)
{
	int CharLenth1=GetCharLenth(Char1);
	int CharLenth2=GetCharLenth(Char2);
	if(CharLenth1+CharLenth2<=0)
		return 0;
	char * ResultsChar=new char [CharLenth1+CharLenth2+1];
	for(int i=0;i<CharLenth1;i++)
	{
		ResultsChar[i]=Char1[i];
	}
	for(int i=0;i<CharLenth2;i++)
	{
		ResultsChar[i+CharLenth1]=Char2[i];
	}
	ResultsChar[CharLenth1+CharLenth2]=0;
	return ResultsChar;
}
int ADDTwoChar(wchar_t *ResultsChar,int ResultsCharArrayMAXSize,const wchar_t * Char1,const wchar_t * Char2)
{
	if((!ResultsChar)||(ResultsCharArrayMAXSize<2))
		return 0;
	int CharLenth1=GetCharLenth(Char1);
	int CharLenth2=GetCharLenth(Char2);
	if(CharLenth1+CharLenth2<=0)
		return 0;
	for(int i=0;i<CharLenth1;i++)
	{
		if(i>=(ResultsCharArrayMAXSize-1))
		{
			ResultsChar[i]=0;
			return i;
		}
		ResultsChar[i]=Char1[i];
	}
	for(int i=0;i<CharLenth2;i++)
	{
		if((i+CharLenth1)>=(ResultsCharArrayMAXSize-1))
		{
			ResultsChar[i+CharLenth1]=0;
			return i;
		}
		ResultsChar[i+CharLenth1]=Char2[i];
	}
	ResultsChar[CharLenth1+CharLenth2]=0;
	return CharLenth1+CharLenth2;
}
int ADDTwoChar(char *ResultsChar,int ResultsCharArrayMAXSize,const char * Char1,const char * Char2)
{
	if((!ResultsChar)||(ResultsCharArrayMAXSize<2))
		return 0;
	int CharLenth1=GetCharLenth(Char1);
	int CharLenth2=GetCharLenth(Char2);
	if(CharLenth1+CharLenth2<=0)
		return 0;
	for(int i=0;i<CharLenth1;i++)
	{
		if(i>=(ResultsCharArrayMAXSize-1))
		{
			ResultsChar[i]=0;
			return i;
		}
		ResultsChar[i]=Char1[i];
	}
	for(int i=0;i<CharLenth2;i++)
	{
		if((i+CharLenth1)>=(ResultsCharArrayMAXSize-1))
		{
			ResultsChar[i+CharLenth1]=0;
			return i;
		}
		ResultsChar[i+CharLenth1]=Char2[i];
	}
	ResultsChar[CharLenth1+CharLenth2]=0;
	return CharLenth1+CharLenth2;
}
