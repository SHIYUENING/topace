#include "MGroup.h"

#include "Common.h"
#include "IniFile.h"
CMGroup::CMGroup(void)
{
	GroupSetID=-1;
}


CMGroup::~CMGroup(void)
{
}


void CMGroup::LoadGroup(void)
{
	MGroup[0].BTN.loadfile(L"data\\Groups\\垃圾处理厂");
	MGroup[1].BTN.loadfile(L"data\\Groups\\污水处理厂");
	MGroup[2].BTN.loadfile(L"data\\Groups\\政府机构");
	MGroup[3].BTN.loadfile(L"data\\Groups\\重点监控企业名单");
	wstring SceneNameTMP;

	SceneNameTMP.clear();
	SceneNameTMP+=L"东部垃圾处理厂";
	MGroup[0].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"淮南市医疗废物处置中心";
	MGroup[0].ModelNames.push_back(SceneNameTMP);
	
	SceneNameTMP.clear();
	SceneNameTMP+=L"淮南市第一污水处理厂";
	MGroup[1].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"淮南市西部污水处理厂";
	MGroup[1].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"山南新区污水处理厂";
	MGroup[1].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"凤台县污水处理厂";
	MGroup[1].ModelNames.push_back(SceneNameTMP);
	
	SceneNameTMP.clear();
	SceneNameTMP+=L"淮南市政府";
	MGroup[2].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"淮南市环保局";
	MGroup[2].ModelNames.push_back(SceneNameTMP);
	//
	SceneNameTMP.clear();
	SceneNameTMP+=L"大唐淮南洛河发电厂";
	MGroup[3].ModelNames.push_back(SceneNameTMP);

	
	SceneNameTMP.clear();
	SceneNameTMP+=L"安徽电力股份有限公司淮南田家庵发电厂";
	MGroup[3].ModelNames.push_back(SceneNameTMP);

	SceneNameTMP.clear();
	SceneNameTMP+=L"安徽景丰纸业有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);

	
	SceneNameTMP.clear();
	SceneNameTMP+=L"淮南矿业集团有限责任公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"国投新集能源股份有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"安徽淮化集团有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"安徽淮南平圩发电有限责任公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"安徽德邦化工有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"安徽东盛制药有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"安徽永安制药有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"东芝堂药业（安徽）有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"安徽山河药用辅料有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"国药集团淮南国瑞药业有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"淮南巨石水泥有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"绿十字（中国）生物制品有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"安徽佳盟药业有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"淮南舜泰化工有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"安徽淮河化工股份有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	SceneNameTMP.clear();
	SceneNameTMP+=L"淮南舜岳水泥有限公司";
	MGroup[3].ModelNames.push_back(SceneNameTMP);
	for(int i=0;i<4;i++)
	MGroup[i].BTN.SetPos(
		GameSet.winW/2-MGroup[i].BTN.Tex.TexW/2,
		(i+1)*GameSet.winH/5-MGroup[i].BTN.Tex.TexH/2);
	/*
	WIN32_FIND_DATAW   filedata; 
	HANDLE   filehandle;
	wstring GroupPath(GROUP_PATH);
	GroupPath+=L"*.txt";
	filehandle=FindFirstFileW(GroupPath.c_str(),&filedata);
	if(filehandle==INVALID_HANDLE_VALUE) 
	{
		FindClose(filehandle);
		return;
	}
	
	wstring GroupPathTMP(GROUP_PATH);
	GroupPathTMP+=filedata.cFileName;
	AddOneGroup(GroupPathTMP);
	while(FindNextFileW(filehandle,&filedata))
	{
		if(filehandle==INVALID_HANDLE_VALUE)
			continue;
	}

	
	FindClose(filehandle);*/
}


int CMGroup::AddOneGroup(wstring GroupPath)
{
	return 0;
}


void CMGroup::DrawBTN(void)
{
	for(int i=0;i<4;i++)
		MGroup[i].BTN.Draw();
}


bool CMGroup::CheakName(wchar_t * SceneName)
{
	if(GroupSetID<0) return false;
	for(int i= 0;i<MGroup[GroupSetID].ModelNames.size();i++)
	{
		if(0==wcscmp(MGroup[GroupSetID].ModelNames[i].c_str(),SceneName)) return true;
	}
	return false;
}
bool CMGroup::CheakNameAll(wchar_t * SceneName)
{
	for(int j=0;j<3;j++)
	for(int i= 0;i<MGroup[j].ModelNames.size();i++)
	{
		if(0==wcscmp(MGroup[j].ModelNames[i].c_str(),SceneName)) return true;
	}
	return false;
}


int CMGroup::CheckBTN(int x,int y)
{
	for(int i=0;i<4;i++)
		if(MGroup[i].BTN.GetCheck(x,y))
		{
			GroupSetID=i;
			return i;
		}
	return -1;
}


int CMGroup::GetGroup(wchar_t * SceneName)
{
	for(int j=0;j<4;j++)
	for(int i= 0;i<MGroup[j].ModelNames.size();i++)
	{
		if(0==wcscmp(MGroup[j].ModelNames[i].c_str(),SceneName)) return j;
	}
	return -1;
}
