//#pragma once
#ifndef CHARSYSBACE_H
#define CHARSYSBACE_H
unsigned int GetWcharLenth(const char * Wchar);
unsigned int GetWcharLenth(const wchar_t * Wchar);
char * ADDTwoWchar(const char * Wchar1,const char * Wchar2);
wchar_t * ADDTwoWchar(const wchar_t * Wchar1,const wchar_t * Wchar2);// Need delete wchar_t[]
int ADDTwoWchar(wchar_t *ResultsWchar,int ResultsWcharArrayMAXSize,const wchar_t * Wchar1,const wchar_t * Wchar2);
int ADDTwoWchar(char *ResultsWchar,int ResultsWcharArrayMAXSize,const char * Wchar1,const char * Wchar2);
#endif