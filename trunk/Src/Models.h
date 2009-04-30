#pragma once
#include "VBMD.h"
//#include "ACMD.h"
//CLoadACMD *m_nj;//ACMD模型对象
CLoadVBMD *m_VBMD = NULL;//VBMD模型对象
unsigned int PlayerMainModel = 0;

tModelID ModelID[100];
int ModelID_hud=0;
int ModelID_redarUI=0;
int ModelID_smoke=0;
int ModelID_SHAN=0;
void LoadVBMDModels(bool IsSupportFBO)
{
	for(int i=0;i<100;i++)
	{
		ModelID[i].Main=-1;
		ModelID[i].MainDD1=-1;
		ModelID[i].MainDD2=-1;
		ModelID[i].Normal=-1;
		ModelID[i].Low=-1;
	
	}
	m_VBMD = new CLoadVBMD;
	m_VBMD->m_IsSupportFBO=IsSupportFBO;

	ModelID[1].Normal	=	m_VBMD ->Init("Data/models/Y-15/Normal");
	ModelID[2].Main		=	m_VBMD ->Init("Data/models/neo1/Main",true,0,true);
	ModelID[2].MainDD1	=	m_VBMD ->Init("Data/models/neo1/MainDD1");
	ModelID[2].MainDD2	=	m_VBMD ->Init("Data/models/neo1/MainDD2");
	ModelID[2].Normal	=	m_VBMD ->Init("Data/models/neo1/Normal");
	ModelID[2].Low		=	m_VBMD ->Init("Data/models/neo1/Low");
	ModelID[3].Normal	=	m_VBMD ->Init("Data/models/aim7_t/Normal");
	PlayerMainModel		=	ModelID[2].Main;
	ModelID_SHAN		=	m_VBMD ->Init("Data/SHAN");
	ModelID_hud			=	m_VBMD ->Init("Data/hud",false);
	ModelID_redarUI		=	m_VBMD ->Init("Data/redarUI",false);
	ModelID_smoke		=	m_VBMD ->Init("Data/smoke",false);


}