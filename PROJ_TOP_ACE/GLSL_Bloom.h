//#pragma once
#ifndef GLSL_BLOOM_H
#define GLSL_BLOOM_H
#include "GLSLLoader.h"
#define BMAP 0
#define TONE 1
#define BLUR 2
void Init_GLSL_Bloom();
void GLSL_Bloom_BindAttrib(GLhandleARB GLSL_PO);
void Deinit_GLSL_Bloom();
void Init_GLSL_Bloom_Uniform();
void GLSL_Enable_Bloom_Map(int WinW,int WinH);
void GLSL_Enable_Bloom_ToneMapping();
void GLSL_Enable_Bloom_BlurTex(int Size,bool WorH);
#endif