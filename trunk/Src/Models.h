#pragma once
#include "VBMD.h"
#include "ACMD.h"
CLoadACMD *m_nj;//ACMD模型对象
CLoadVBMD *m_VBMD = NULL;//VBMD模型对象

void LoadVBMDModels(void)
{
	m_VBMD ->Init("Data/df133b", 0);
	m_VBMD ->Init("Data/SHAN", 1);
	m_VBMD ->Init("Data/Y-15CM", 2);
	m_VBMD ->Init("Data/CY-SKY", 3);
	m_VBMD ->Init("Data/aim7_t", 4);

	m_VBMD ->BuildVBO(0);
	m_VBMD ->BuildVBO(1);
	m_VBMD ->BuildVBO(2);
	m_VBMD ->BuildVBO(3);
	m_VBMD ->BuildVBO(4);

}