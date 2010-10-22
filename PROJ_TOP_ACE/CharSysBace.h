//#pragma once
#ifndef CHARSYSBACE_H
#define CHARSYSBACE_H

unsigned int GetWcharLenth(const wchar_t * Wchar);
wchar_t * ADDTwoWchar(const wchar_t * Wchar1,const wchar_t * Wchar2);// Need delete wchar_t[]
int ADDTwoWchar(wchar_t *ResultsWchar,int ResultsWcharArrayMAXSize,const wchar_t * Wchar1,const wchar_t * Wchar2);
#endif