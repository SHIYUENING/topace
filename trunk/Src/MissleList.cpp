#include "MissleList.h"

MissleList::MissleList(void)
: MissleNum(0)
, totalMissleNum(0)
{
}

MissleList::~MissleList(void)
{
}

bool MissleList::Init(void)
{
	return false;
}

int MissleList::AddMissle(Transform & Fighter,int TGT,int onwer)
{
	//MissleNum
	

	if(MissleNum==MAXMISSLE)
	{
		MissleNum=0;
	}
	while(Missles[MissleNum].UDlife>0)
	{
		totalMissleNum=totalMissleNum+1;
		if(totalMissleNum>=MAXMISSLE)
			return -1;

		MissleNum=MissleNum+1;
		if(MissleNum>=MAXMISSLE)
		{
			MissleNum=0;
		}
	
	}
	Missles[MissleNum].UDMplane=Fighter;
	Missles[MissleNum].TGTnum=TGT;
	Missles[MissleNum].UDlife=240;
	Missles[MissleNum].onwer=onwer;
	if(onwer==0)
	{
		Missles[MissleNum].UDMplane.TranslateInternal(Vector3d(0.0f, -75.0f, -290.0f));
		Missles[MissleNum].UDMplane.RotateInternal(Vector3d(0.0f, 1.0f, 0.0f) * CRad(180.0));
	}
	
	return MissleNum;
	

}

void MissleList::DrawMissle(const Vector3d& m_world,int m_winwidth,int m_winheight,float m_tmpLookRenge)
{
	for(int i=0;i<MAXMISSLE;i++)
	{
		Missles[i].m_Draw(m_world,m_winwidth,m_winheight,m_tmpLookRenge);
	}
}


