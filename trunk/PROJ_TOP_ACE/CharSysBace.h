//#pragma once
#ifndef CHARSYSBACE_H
#define CHARSYSBACE_H
unsigned int GetCharLenth(const char * Char);
unsigned int GetCharLenth(const wchar_t * Char);
char * ADDTwoChar(const char * Char1,const char * Char2);
wchar_t * ADDTwoChar(const wchar_t * Char1,const wchar_t * Char2);// Need delete wchar_t[]
int ADDTwoChar(wchar_t *ResultsChar,int ResultsCharArrayMAXSize,const wchar_t * Char1,const wchar_t * Char2);
int ADDTwoChar(char *ResultsChar,int ResultsCharArrayMAXSize,const char * Char1,const char * Char2);
#endif