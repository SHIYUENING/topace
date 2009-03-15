#pragma once
#include "VBMD.h"
#include "ACMD.h"
CLoadACMD *m_nj;//ACMD模型对象
CLoadVBMD *m_VBMD = NULL;//VBMD模型对象
unsigned int PlayerMainModel = 0;
unsigned int EnemyModel1Nomal = 0;
unsigned int EnemyModel1Low = 0;
unsigned int TotelModels = 0;

void LoadVBMDModels(void)
{
	m_VBMD ->Init("Data/df133b", PlayerMainModel);
	m_VBMD ->Init("Data/SHAN", 1);
	m_VBMD ->Init("Data/Y-15CM", 2);
	m_VBMD ->Init("Data/CY-SKY", 3);
	m_VBMD ->Init("Data/aim7_t", 4);

	m_VBMD ->BuildVBO(PlayerMainModel);
	m_VBMD ->BuildVBO(1);
	m_VBMD ->BuildVBO(2);
	m_VBMD ->BuildVBO(3);
	m_VBMD ->BuildVBO(4);

}