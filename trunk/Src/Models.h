#pragma once
#include "VBMD.h"
#include "MD5Model.h"
//#include "ACMD.h"
//CLoadACMD *m_nj;//ACMD模型对象
CLoadVBMD *m_VBMD = NULL;//VBMD模型对象
unsigned int PlayerMainModel = 0;
#define ModelID_Mave
tModelID ModelID[100];
int ModelID_hud=0;
int ModelID_redarUI=0;
int ModelID_smoke=0;
int ModelID_SHAN=0;
int ModelID_MavePart_Main=0;
/*
int ModelID_MavePart_BackL=0;
int ModelID_MavePart_BackR=0;
int ModelID_MavePart_FL=0;
int ModelID_MavePart_FR=0;
int ModelID_MavePart_WL=0;
int ModelID_MavePart_WR=0;
*/
int ModelID_MavePart_Glass=0;
int ModelID_MavePart_Normal=0;
int ModelID_Stage1Ship_Normal=0;
int ShowHPmodel=0;
MD5Model md5_weiyiL;
MD5Model md5_weiyiR;
MD5Model md5_wingL;
MD5Model md5_wingR;
MD5Model md5_yayiL;
MD5Model md5_yayiR;
MD5Model md5_yinqingL;
MD5Model md5_yinqingR;
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
	char ModelName[128];
	

	ModelID[1].Normal	=	m_VBMD ->Init("Data/models/Y-15/Normal");
#ifndef ModelID_Mave
	sprintf(ModelName,"neo1");
#endif
#ifdef ModelID_Mave
	sprintf(ModelName,"mave");
#endif
	ModelID[2].Normal	=	m_VBMD ->Init("Data/models/neo1/Normal");
	ModelID[2].Low		=	m_VBMD ->Init("Data/models/neo1/Low");
	ModelID[3].Normal	=	m_VBMD ->Init("Data/models/aim7_t/Normal");

	ModelID_hud			=	m_VBMD ->Init("Data/hud",false);
	ModelID_redarUI		=	m_VBMD ->Init("Data/redarUI",false);
	ModelID_smoke		=	m_VBMD ->Init("Data/smoke",false);
	ShowHPmodel			=	ModelID[2].Normal;

	sprintf(ModelFileName,"Data/models/%s/%s",ModelName,"Main");	ModelID_MavePart_Main	= m_VBMD ->Init(ModelFileName,true,0,true);
	//sprintf(ModelFileName,"Data/models/%s/%s",ModelName,"BackL");	ModelID_MavePart_BackL	= m_VBMD ->Init(ModelFileName,false,0,true);
	//sprintf(ModelFileName,"Data/models/%s/%s",ModelName,"BackR");	ModelID_MavePart_BackR	= m_VBMD ->Init(ModelFileName,false,0,true);
	//sprintf(ModelFileName,"Data/models/%s/%s",ModelName,"FL");		ModelID_MavePart_FL		= m_VBMD ->Init(ModelFileName,false,0,true);
	//sprintf(ModelFileName,"Data/models/%s/%s",ModelName,"FR");		ModelID_MavePart_FR		= m_VBMD ->Init(ModelFileName,false,0,true);
	//sprintf(ModelFileName,"Data/models/%s/%s",ModelName,"WL");		ModelID_MavePart_WL		= m_VBMD ->Init(ModelFileName,false,0,true);
	//sprintf(ModelFileName,"Data/models/%s/%s",ModelName,"WR");		ModelID_MavePart_WR		= m_VBMD ->Init(ModelFileName,false,0,true);
	sprintf(ModelFileName,"Data/models/%s/%s",ModelName,"Glass");	ModelID_MavePart_Glass	= m_VBMD ->Init(ModelFileName,false,0,true);
	sprintf(ModelFileName,"Data/models/%s/%s",ModelName,"Normal");	ModelID_MavePart_Normal	= m_VBMD ->Init(ModelFileName);

	md5_weiyiL.loadMesh("Data/models/mave/weiyiL.md5mesh");
	md5_weiyiR.loadMesh("Data/models/mave/weiyiR.md5mesh");
	md5_wingL.loadMesh("Data/models/mave/wingL.md5mesh");
	md5_wingR.loadMesh("Data/models/mave/wingR.md5mesh");
	md5_yayiL.loadMesh("Data/models/mave/yayiL.md5mesh");
	md5_yayiR.loadMesh("Data/models/mave/yayiR.md5mesh");
	md5_yinqingL.loadMesh("Data/models/mave/yinqingL.md5mesh");
	md5_yinqingR.loadMesh("Data/models/mave/yinqingR.md5mesh");

	md5_weiyiL.loadAnim("Data/models/mave/weiyiL.md5anim");
	md5_weiyiR.loadAnim("Data/models/mave/weiyiR.md5anim");
	md5_wingL.loadAnim("Data/models/mave/wingL.md5anim");
	md5_wingR.loadAnim("Data/models/mave/wingR.md5anim");
	md5_yayiL.loadAnim("Data/models/mave/yayiL.md5anim");
	md5_yayiR.loadAnim("Data/models/mave/yayiR.md5anim");
	md5_yinqingL.loadAnim("Data/models/mave/yinqingL.md5anim");
	md5_yinqingR.loadAnim("Data/models/mave/yinqingR.md5anim");

	md5_weiyiL.setAnim(0);
	md5_weiyiR.setAnim(0);
	md5_wingL.setAnim(0);
	md5_wingR.setAnim(0);
	md5_yayiL.setAnim(0);
	md5_yayiR.setAnim(0);
	md5_yinqingL.setAnim(0);
	md5_yinqingR.setAnim(0);

	ShowHPmodel=ModelID_MavePart_Normal;
	PlayerMainModel=ModelID_MavePart_Main;

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