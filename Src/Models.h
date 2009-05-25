#pragma once
#include "VBMD.h"
//#include "ACMD.h"
//CLoadACMD *m_nj;//ACMD模型对象
CLoadVBMD *m_VBMD = NULL;//VBMD模型对象
unsigned int PlayerMainModel = 0;
//#define ModelID_Mave
tModelID ModelID[100];
int ModelID_hud=0;
int ModelID_redarUI=0;
int ModelID_smoke=0;
int ModelID_SHAN=0;
int ModelID_MavePart_Main=0;
int ModelID_MavePart_BackL=0;
int ModelID_MavePart_BackR=0;
int ModelID_MavePart_FL=0;
int ModelID_MavePart_FR=0;
int ModelID_MavePart_WL=0;
int ModelID_MavePart_WR=0;
int ModelID_MavePart_Glass=0;
int ModelID_MavePart_Normal=0;
int ModelID_Stage1Ship_Normal=0;
//int ModelID_MavePart_Low=0;
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
	char ModelFileName[256];
	

	ModelID[1].Normal	=	m_VBMD ->Init("Data/models/Y-15/Normal");
#ifndef ModelID_Mave
	ModelID[2].Main		=	m_VBMD ->Init("Data/models/neo1/Main",true,0,true);
	PlayerMainModel		=	ModelID[2].Main;
#endif
	ModelID[2].Normal	=	m_VBMD ->Init("Data/models/neo1/Normal");
	ModelID[2].Low		=	m_VBMD ->Init("Data/models/neo1/Low");
	ModelID[3].Normal	=	m_VBMD ->Init("Data/models/aim7_t/Normal");

	ModelID_hud			=	m_VBMD ->Init("Data/hud",false);
	ModelID_redarUI		=	m_VBMD ->Init("Data/redarUI",false);
	ModelID_smoke		=	m_VBMD ->Init("Data/smoke",false);
#ifdef ModelID_Mave
	sprintf(ModelFileName,"Data/models/%s/%s","mave","Main");	ModelID_MavePart_Main	= m_VBMD ->Init(ModelFileName,true,0,true);
	sprintf(ModelFileName,"Data/models/%s/%s","mave","BackL");	ModelID_MavePart_BackL	= m_VBMD ->Init(ModelFileName,false,0,true);
	sprintf(ModelFileName,"Data/models/%s/%s","mave","BackR");	ModelID_MavePart_BackR	= m_VBMD ->Init(ModelFileName,false,0,true);
	sprintf(ModelFileName,"Data/models/%s/%s","mave","FL");		ModelID_MavePart_FL		= m_VBMD ->Init(ModelFileName,false,0,true);
	sprintf(ModelFileName,"Data/models/%s/%s","mave","FR");		ModelID_MavePart_FR		= m_VBMD ->Init(ModelFileName,false,0,true);
	sprintf(ModelFileName,"Data/models/%s/%s","mave","WL");		ModelID_MavePart_WL		= m_VBMD ->Init(ModelFileName,false,0,true);
	sprintf(ModelFileName,"Data/models/%s/%s","mave","WR");		ModelID_MavePart_WR		= m_VBMD ->Init(ModelFileName,false,0,true);
	sprintf(ModelFileName,"Data/models/%s/%s","mave","Glass");	ModelID_MavePart_Glass	= m_VBMD ->Init(ModelFileName,false,0,true);
	sprintf(ModelFileName,"Data/models/%s/%s","mave","Normal");	ModelID_MavePart_Normal	= m_VBMD ->Init(ModelFileName);


	PlayerMainModel=ModelID_MavePart_Main;
#endif
	ModelID_Stage1Ship_Normal = m_VBMD ->Init("Data/models/Stage1/Ship");
	//ModelID_MavePart_Low	= m_VBMD ->Init("Data/models/mave/Low");


}

/*
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
	//ModelID[2].MainDD1	=	m_VBMD ->Init("Data/models/neo1/MainDD1");
	//ModelID[2].MainDD2	=	m_VBMD ->Init("Data/models/neo1/MainDD2");
	ModelID[2].Normal	=	m_VBMD ->Init("Data/models/neo1/Normal");
	ModelID[2].Low		=	m_VBMD ->Init("Data/models/neo1/Low");
	ModelID[3].Normal	=	m_VBMD ->Init("Data/models/aim7_t/Normal");
	PlayerMainModel		=	ModelID[2].Main;
	//ModelID_SHAN		=	m_VBMD ->Init("Data/SHAN");
	ModelID_hud			=	m_VBMD ->Init("Data/hud",false);
	ModelID_redarUI		=	m_VBMD ->Init("Data/redarUI",false);
	ModelID_smoke		=	m_VBMD ->Init("Data/smoke",false);


}
*/