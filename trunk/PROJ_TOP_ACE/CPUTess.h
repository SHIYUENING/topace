//#pragma once
#ifndef _CPUTESS_H
#define _CPUTESS_H
#include "EasyMatrix.h"
class CCPUTess
{
public:
	CCPUTess(void);
	~CCPUTess(void);
	bool AddModel(float * vertices,float * Normals,float * texcos,unsigned int Count);
};
#endif